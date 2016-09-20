#include "..\Headers\Combat Instance.h"

Combat_Module::CombatInstance::CombatInstance()
	: CombatInstance(FactionFleetListMap(0)) {}

Combat_Module::CombatInstance::CombatInstance(const CombatInstance & orig)
	: fleets(orig.fleets), ships(orig.ships), pendingHits(orig.pendingHits) {}

Combat_Module::CombatInstance::CombatInstance(const FactionFleetListMap & flts)
	: fleets(flts) {
	FactionFleetListMap::mapped_type::const_iterator Fleet_iter, Fleet_end;
	FactionShipTypeMap::mapped_type::ShipTypeCounterMap::const_iterator Ship_iter, Ship_end;
	for (FactionFleetListMap::const_iterator Faction_iter(flts.begin()), Faction_end(flts.end());
		 Faction_iter != Faction_end; Faction_iter++)
		for (Fleet_iter = Faction_iter->second.begin(), Fleet_end = Faction_iter->second.end();
			 Fleet_iter != Fleet_end; Fleet_iter++) {
		Fleet_iter->_ships.iterateByID(Ship_iter, Ship_end);
		for (; Ship_iter != Ship_end; Ship_iter++)
			ships[Faction_iter->first].offsetCounter(Ship_iter->first, Ship_iter->second);
	}
}

__int32 Combat_Module::CombatInstance::iterate() {
	FactionShipTypeMap currentHits(calc_LandedHitsFromShipTypes());
	currentHits = calc_HitDistributionForShipTypes(currentHits);
	currentHits = calc_EvadedHitsForShipTypes(currentHits);
	applyHits(currentHits);
	calculateDeaths();
	cleanFields();
	if (ships.size() == 1)
		return 1;
	else
		return 0;
}

void Combat_Module::CombatInstance::resolve() {
	while (iterate() == 0);
}

__int32 calc_Hits(__int32 attackers, const Combat_Module::Ship_Types::ShipType& attackingType) {
	return APPLY_FRACTION((attackers * attackingType._stats.attacksCount), attackingType._stats.hitChance, CHANCE_1);
	//Number of attacker * number of attacks per attacker * %chance to hit
}

Combat_Module::CombatInstance::FactionShipTypeMap Combat_Module::CombatInstance::calc_LandedHitsFromShipTypes() {
	Combat_Module::CombatInstance::FactionShipTypeMap res;
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator TypeCount_iter, TypeCount_end;
	Ship_Types::ShipType type;
	for (FactionShipTypeMap::const_iterator Faction_iter(ships.begin()), Faction_end(ships.end());
		 Faction_iter != Faction_end; Faction_iter++) {
		Faction_iter->second.iterateByID(TypeCount_iter, TypeCount_end);
#pragma region For each ShipType calculate how many accurate shots they will produce
		for (; TypeCount_iter != TypeCount_end; TypeCount_iter++) {
			if (Ship_Types::getShipType_ByID(TypeCount_iter->first, type)) {
				res[Faction_iter->first].setCounter(TypeCount_iter->first,
													calc_Hits(TypeCount_iter->second, type)
				);
			}
		}
#pragma endregion
	}
	return res;
}

void Combat_Module::CombatInstance::calc_HitDistributionOnFaction(const __int32 landedHits, const Space_Colony::Ships::ShipTypeCount & targets,
																  const unsigned __int32 factionTargets, Space_Colony::Ships::ShipTypeCount & result) {
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator ID_iter, ID_end;
	targets.iterateByID(ID_iter, ID_end);
	for (; ID_iter != ID_end; ID_iter++)
		result.offsetCounter(ID_iter->first,
							 APPLY_FRACTION(landedHits, ID_iter->second, factionTargets
							 //Number of accurate hits * %of targets of this type out of all targets
		));
}

void Combat_Module::CombatInstance::calc_HitDistributionForType(const __int32 landedHits, const Space_Colony::faction_t currentFaction,
																const Ship_Types::ShipType & attackingType, FactionShipTypeMap & result) {
	FactionShipTypeMap::const_iterator Faction_iter, Faction_end(ships.end());
	FactionShipTypeMap targetShips(ships.size());
	FactionCounter factionTargets(ships.size());
	unsigned __int32 totalTargets(0), hitFactor;
#pragma region Calculating Target Counts
	{
		Ship_Types::ShipType type;
		Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator ID_iter, ID_end;
		for (Faction_iter = ships.begin(); Faction_iter->first != currentFaction; Faction_iter++) {
			Faction_iter->second.iterateByID(ID_iter, ID_end);
			factionTargets[Faction_iter->first] = 0;

			for (; ID_iter != ID_end; ID_iter++) {
				Ship_Types::getShipType_ByID(ID_iter->first, type);
#pragma region Add to targets for this Faction if they are a valid size
				if (type._stats.sizeValue > attackingType._stats.minSize
					&& type._stats.sizeValue < attackingType._stats.maxSize) {
					targetShips[Faction_iter->first].setCounter(ID_iter->first, ID_iter->second);
					factionTargets[Faction_iter->first] += ID_iter->second;
				}
#pragma endregion
			}
		}
		for (Faction_iter++; Faction_iter->first != currentFaction; Faction_iter++) {
			Faction_iter->second.iterateByID(ID_iter, ID_end);
			for (; ID_iter != ID_end; ID_iter++) {
				Ship_Types::getShipType_ByID(ID_iter->first, type);
#pragma region Add to targets for this Faction if they are a valid size
				if (type._stats.sizeValue > attackingType._stats.minSize
					&& type._stats.sizeValue < attackingType._stats.maxSize) {
					targetShips[Faction_iter->first].setCounter(ID_iter->first, ID_iter->second);
					factionTargets[Faction_iter->first] += ID_iter->second;
				}
#pragma endregion
			}

			totalTargets += factionTargets[Faction_iter->first];
			if (factionTargets[Faction_iter->first] == 0)
				//If their are no targets for this faction remove this faction
				//from the target map.
				factionTargets.erase(Faction_iter->first);
		}
	}
#pragma endregion

#pragma region Distribute attacks across all factions and types
	for (Faction_iter = ships.begin(); Faction_iter->first != currentFaction; Faction_iter++) {
		if (factionTargets.count(Faction_iter->first) != 0) {
			hitFactor = APPLY_FRACTION(CHANCE_1, factionTargets[Faction_iter->first], totalTargets);
			//100% * %of targets in this faction compared to all factions.
			if (hitFactor != 0) //There are enough targets to attack.
				calc_HitDistributionOnFaction(
					APPLY_FRACTION(landedHits, hitFactor, CHANCE_1),
					//Number of accurate attacks * %of attacks aimed at this faction.
					targetShips[Faction_iter->first],
					//The ships being targeted.
					factionTargets[Faction_iter->first],
					//The total number of targets from this faction.
					result[Faction_iter->first]
					//The map of accumulative distributed hits to return.
				);
		}
	}
	for (Faction_iter++; Faction_iter->first != currentFaction; Faction_iter++) {
		if (factionTargets.count(Faction_iter->first) != 0) {
			hitFactor = APPLY_FRACTION(CHANCE_1, factionTargets[Faction_iter->first], totalTargets);
			//100% * %of targets in this faction compared to all factions.
			if (hitFactor != 0) //There are enough targets to attack.
				calc_HitDistributionOnFaction(
					APPLY_FRACTION(landedHits, hitFactor, CHANCE_1),
					//Number of accurate attacks * %of attacks aimed at this faction.
					targetShips[Faction_iter->first],
					//The ships being targeted.
					factionTargets[Faction_iter->first],
					//The total number of targets from this faction.
					result[Faction_iter->first]
					//The map of accumulative distributed hits to return.
				);
		}
	}
#pragma endregion


}

Combat_Module::CombatInstance::FactionShipTypeMap Combat_Module::CombatInstance::calc_HitDistributionForShipTypes(const FactionShipTypeMap & landedHits) {
	FactionShipTypeMap res;
	FactionShipTypeMap::const_iterator Faction_iter, Faction_end;
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator TypeCount_iter, TypeCount_end;
#pragma region Zero all attacks
	for (Faction_iter = ships.begin(), Faction_end = ships.end(); Faction_iter != Faction_end; Faction_iter++) {
		Faction_iter->second.iterateByID(TypeCount_iter, TypeCount_end);
		for (; TypeCount_iter != TypeCount_end; TypeCount_iter++) {
			res[Faction_iter->first].setCounter(TypeCount_iter->first, 0);
		}
	}
#pragma endregion


	Ship_Types::ShipType type;
	for (Faction_iter = ships.begin(), Faction_end = ships.end();
		 Faction_iter != Faction_end; Faction_iter++) {
		Faction_iter->second.iterateByID(TypeCount_iter, TypeCount_end);
		for (; TypeCount_iter != TypeCount_end; TypeCount_iter++) {
			Ship_Types::getShipType_ByID(TypeCount_iter->first, type);
			calc_HitDistributionForType(
				landedHits.at(Faction_iter->first).getCounter(TypeCount_iter->first),
				//Number of accurate attacks aimed at this type
				Faction_iter->first, type, res
				//The Faction attacking, the ShipType attacking, the map of
				//results to place attacks in.
			);
		}
	}
	return res;
}

Combat_Module::CombatInstance::FactionShipTypeMap Combat_Module::CombatInstance::calc_EvadedHitsForShipTypes(const FactionShipTypeMap & landedHits) {
	FactionShipTypeMap res;
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator ID_iter, ID_end;
	Ship_Types::ShipType type;
	for (FactionShipTypeMap::const_iterator Faction_iter(landedHits.begin()), Faction_end(landedHits.end());
		 Faction_iter != Faction_end; Faction_iter++) {
		Faction_iter->second.iterateByID(ID_iter, ID_end);
		Ship_Types::getShipType_ByID(ID_iter->first, type);
		for (; ID_iter != ID_end; ID_iter++) {
			res[Faction_iter->first].setCounter(ID_iter->first,
												APPLY_FRACTION(ID_iter->second, type._stats.evadeChance, CHANCE_1)
												//Number of Ships evading * %chance that this type will evade.
			);
		}
	}
	return res;
}

void Combat_Module::CombatInstance::applyHits(const FactionShipTypeMap & hits) {
	for (FactionShipTypeMap::const_iterator iter(pendingHits.begin()), end(pendingHits.end()); iter != end; iter++)
		if (hits.count(iter->first) != 0)
			pendingHits[iter->first] += hits.at(iter->first);
}

void Combat_Module::CombatInstance::calculateDeaths() {
	__int32 deaths, shipsCount;
	Ship_Types::ShipType type;
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator ID_iter, ID_end;
	for (FactionShipTypeMap::const_iterator Hits_iter(pendingHits.begin()), Hits_end(pendingHits.end());
		 Hits_iter != Hits_end; Hits_iter++) {
		Hits_iter->second.iterateByID(ID_iter, ID_end);
		for (; ID_iter != ID_end; ID_iter++) {
			Ship_Types::getShipType_ByID(ID_iter->first, type);
			deaths = ID_iter->second / type._stats.hitPoints; //Number of
			//attacks / number of attacks needed for a kill.
			if (deaths != 0) {
				shipsCount = ships[Hits_iter->first].getCounter(ID_iter->first);
				deaths = (deaths * CHANCE_1) /
					(shipsCount * ((rand() % CHANCE_1) + 1)); //Number of
				//possible deaths / number of Ships attacked.
				//Number of Ships attacked = total number of Ships * %random
				//percent of Ships to be targeted.
#pragma region Subtract the resulting deaths and used Hits
				if (deaths != 0) {
					if (deaths > shipsCount) { //Cannot cause more deaths than
						//there are Ships.
						deaths = shipsCount;
					}
					pendingHits[Hits_iter->first].offsetCounter(ID_iter->first,
																-(ID_iter->second * deaths / shipsCount)
					);
					ships[Hits_iter->first].offsetCounter(ID_iter->first, -deaths);
				}
#pragma endregion
			}
		}
	}
}

void Combat_Module::CombatInstance::cleanFields() {
	typedef std::unordered_map<Space_Colony::faction_t, std::list<Space_Colony::Ships::Type_ID>> FactionTypeIdMap;
	typedef std::unordered_map<Space_Colony::faction_t, bool> FactionBool;

	FactionBool factionPopulations;
	FactionTypeIdMap removedTypes;
	FactionTypeIdMap::mapped_type::const_iterator Type_iter, Type_end;
	Space_Colony::Ships::ShipTypeCount::ShipTypeCounterMap::const_iterator ID_iter, ID_end;
	FactionFleetListMap::mapped_type::iterator Fleet_iter, Fleet_end;

#pragma region Calculate which Factions or ShipTypes within those factions need to be removed
	for (FactionShipTypeMap::const_iterator Factions_iter(ships.begin()), Factions_end(ships.end());
		 Factions_iter != Factions_end; Factions_iter++) {
		Factions_iter->second.iterateByID(ID_iter, ID_end);
		factionPopulations[Factions_iter->first] = false; //Factions should be
		//removed unless populated.
		for (; ID_iter != ID_end; ID_iter++) {
			if (ID_iter->second == 0) { //There are no Ships of this type left.
				removedTypes[Factions_iter->first].push_back(ID_iter->first);
				if (pendingHits.count(Factions_iter->first) != 0) //Ensure that
					//there are no attacks left against this type.
					pendingHits[Factions_iter->first].erase(ID_iter->first);
			} else { //There are Ships left of this type.
				factionPopulations[Factions_iter->first] = true;
				//Keep this Faction.
			}
		}
	}
#pragma endregion

#pragma region Remove obsolete Factions or Types
	for (FactionBool::const_iterator Factions_iter(factionPopulations.begin()),
		 Factions_end(factionPopulations.end());
		 Factions_iter != Factions_end; Factions_iter++) {
		if (Factions_iter->second == true) { //Keep this Faction.
#pragma region Remove Obselete ShipTypes
			for (Type_iter = removedTypes[Factions_iter->first].begin(),
				 Type_end = removedTypes[Factions_iter->first].end();
				 Type_iter != Type_end; Type_iter++) { //Remove obselete
				//ShipTypes from this faction.
				ships[Factions_iter->first].erase(*Type_iter);
				pendingHits[Factions_iter->first].erase(*Type_iter);
				for (Fleet_iter = fleets[Factions_iter->first].begin(),
					 Fleet_end = fleets[Factions_iter->first].end();
					 Fleet_iter != Fleet_end; Fleet_iter++) { //Remove this
					//ShipType from all engaged Fleets of this Faction.
					Fleet_iter->_ships.erase(*Type_iter);
				}
			}
#pragma endregion
		} else {
			ships.erase(Factions_iter->first);
			pendingHits.erase(Factions_iter->first);
			fleets.erase(Factions_iter->first);
		}
#pragma endregion
	}
}
