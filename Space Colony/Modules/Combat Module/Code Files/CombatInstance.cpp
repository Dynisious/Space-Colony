#include "..\Headers\CombatInstance.h"
#include <list>

using namespace Space_Colony;
using namespace Space_Colony::Combat_Module;

Space_Colony::Combat_Module::CombatInstance::CombatInstance() {}

Space_Colony::Combat_Module::CombatInstance::CombatInstance(const CombatFrame & frm)
	: frame(frm) {}

void Space_Colony::Combat_Module::CombatInstance::iterate(FleetVector & fleets, const ShipTypeVector & ships,
														  const ResourceTypeVector & rsrc) {
	//Set the frame for the CombatInstance to be the next frame.
	frame = getNextFrame(fleets, ships, rsrc);
}

CombatFrame Space_Colony::Combat_Module::CombatInstance::getNextFrame(FleetVector & fleets, const ShipTypeVector &ships,
																	  const ResourceTypeVector & rsrc) const {
	//The next frame as the result, based off the current frame.
	CombatFrame result(frame);
	//The combined Ships of all the factions divided by faction.
	CombatFrame::FactionCounters factionShips(frame.fleets.size());
#pragma region Get all Ships by Faction
	//Iterate all factions.
	for (auto faction_iter(frame.fleets.begin()), faction_end(frame.fleets.end());
		 faction_iter != faction_end; ++faction_iter)
		//Iterate all Fleets in this faction.
		for (auto fleet_iter(faction_iter->second.begin()), fleet_end(faction_iter->second.end());
			 fleet_iter != fleet_end; ++fleet_iter)
			//Accumulate the Ships of this Fleet into the sum.
			factionShips[faction_iter->first] += fleets.at(*fleet_iter).getShips();
#pragma endregion
#pragma region Ship Combat
	{
		//The damage output against each Ship type from each faction.
		CombatFrame::FactionCounters factionDistributedDamage(factionShips.size());
#pragma region Get Attacks from each Faction
		{
			//The cummulative Ships which a faction is attacking.
			TypeCounter allEnemyShips;
			//Iterate each factions Ships.
			for (auto faction_iter(factionShips.begin()), faction_end(factionShips.end());
				 faction_iter != faction_end; ++faction_iter)
				//Accumlate the factions Ships.
				allEnemyShips += faction_iter->second;
			//A collection of ShipType Ids grouped by their ShipTypes size.
			std::unordered_map<size_t, std::list<size_t>> ShipTypes_bySize;
			//Iterate all Ship types in the accumulation of Ships.
			for (auto shipType_iter(allEnemyShips.begin()), shipType_end(allEnemyShips.end());
				 shipType_iter != shipType_end; ++shipType_iter)
				//Sort the ShipType Id into the group of it's ShipType size.
				ShipTypes_bySize[ships.at(shipType_iter->first).combat.size].push_back(shipType_iter->first);
#pragma region Distribute Damage for each Faction
			//Iterate the Ships of each faction.
			for (auto faction_iter(factionShips.begin()), faction_end(factionShips.end());
				 faction_iter != faction_end; ++faction_iter) {
				//Remove friendly Ships from the accumulation of enemy Ships.
				allEnemyShips -= faction_iter->second;
#pragma region Distribute Damage for each Ship type
#pragma region Distribute Damage
				//Iterate all Ship types in the current faction.
				for (auto shipType_iter(faction_iter->second.begin()), shipType_end(faction_iter->second.end());
					 shipType_iter != shipType_end; ++shipType_iter) {
					//The total number of attacks produced by the current Ship type.
					size_t attacks(ships.at(shipType_iter->first).combat.attacks * shipType_iter->second),
						//A sum of all the valid target Ships in the enemies Ships.
						targetsSum(0),
						//The damage done by each attack from the current Ship type.
						const typeDamage(ships.at(shipType_iter->first).combat.damage);
#pragma region Get the Sum of all Target Ships
					//Iterate all the ShipType sizes which the current Ship type can attack.
					for (size_t target_size(ships.at(shipType_iter->first).combat.minSize),
						 const target_max(ships.at(shipType_iter->first).combat.maxSize + 1);
						 target_size < target_max; ++target_size)
						//Iterate all the ShipType Ids which match the current target size.
						for (auto targetType_iter(ShipTypes_bySize.at(target_size).begin()),
							 targetType_end(ShipTypes_bySize.at(target_size).end());
							 targetType_iter != targetType_end; ++targetType_iter)
							//Accumulate the enemy Ships into the sum of targets.
							targetsSum += allEnemyShips.getCounter(*targetType_iter);
#pragma endregion
#pragma region Distribute the Damage from this Ship Type Across all Targeted Types.
					//Iterate all the ShipType sizes which the current Ship type can attack.
					for (size_t target_size(ships.at(shipType_iter->first).combat.minSize),
						 const target_max(ships.at(shipType_iter->first).combat.maxSize + 1);
						 target_size < target_max; ++target_size)
						//Iterate all the ShipType Ids which match the current target size.
						for (auto targetType_iter(ShipTypes_bySize.at(target_size).begin()),
							 targetType_end(ShipTypes_bySize.at(target_size).end());
							 targetType_iter != targetType_end; ++targetType_iter) {
							//The portion of the attack output produced by the current Ship
							//type which is directed at the Ship type with the current
							//ShipType id.
							size_t portionedAttackDmg(allEnemyShips.getCounter(*targetType_iter)
													  * attacks / targetsSum);
							//Remove the portion of attacks being used from the cumulative attacks.
							attacks -= portionedAttackDmg;
							//Remove the count of Ships if the current ShipType id from the
							//sum of target Ships.
							targetsSum -= allEnemyShips.getCounter(*targetType_iter);
							//A reference to the combat stats of the Ship type being attacked.
							const CombatStats &targetTypeCombatStats(ships.at(*targetType_iter).combat);
							//Scale the portion of attacks to account for the evasive
							//abilities of the targeted Ship type.
							portionedAttackDmg *= targetTypeCombatStats.evade;
							//Convert the portion of attacks into damage points for the
							//attacking Ship type.
							portionedAttackDmg *= typeDamage;
							//Remove the damage points which glance off the armour of the
							//targeted type.
							portionedAttackDmg -= ((portionedAttackDmg * targetTypeCombatStats.glance) / 2);
							//Increment the damage output against the current ShipType id
							//by the portion of the outputed damage against them.
							factionDistributedDamage[faction_iter->first].incCounter(
								*targetType_iter, portionedAttackDmg
							);
						}
#pragma endregion
				}
#pragma endregion
#pragma endregion
				//Return friendly Ships to the accumulation of enemy Ships.
				allEnemyShips += faction_iter->second;
			}
#pragma endregion
		}
#pragma endregion
#pragma region Distribute Damage Around each Faction
		//Iterate all the damage output from each faction.
		for (auto factionDamage_iter(factionDistributedDamage.begin()), factionDamage_end(factionDistributedDamage.end());
			 factionDamage_iter != factionDamage_end; ++factionDamage_iter) {
			//Iterate the damage output against each Ship type.
			for (auto shipTypeDamage_iter(factionDamage_iter->second.begin()), shipTypeDamage_end(factionDamage_iter->second.end());
				 shipTypeDamage_iter != shipTypeDamage_end; ++shipTypeDamage_iter) {
				//The sum for the number of enemy targets of this Ship type in
				//the conflict.
				size_t targetsSum(0);
#pragma region Get Sum of Target Ships
				{
					//An iterator for the Ships from each faction in the conflict.
					auto enemyFaction_iter(factionShips.begin());
					//Iterate until the current faction is reached.
					for (; enemyFaction_iter->first != factionDamage_iter->first; ++enemyFaction_iter)
						//Add the targets from this faction to the sum of targets.
						targetsSum += enemyFaction_iter->second.getCounter(shipTypeDamage_iter->first);
					//Skip the current faction.
					++enemyFaction_iter;
					//Iterate the remaining factions.
					for (auto const enemyFaction_end(factionShips.end());
						 enemyFaction_iter != enemyFaction_end; ++enemyFaction_iter)
						//Add the targets from this faction to the sum of targets.
						targetsSum += enemyFaction_iter->second.getCounter(shipTypeDamage_iter->first);
				}
#pragma endregion
#pragma region Distribute Damage around Factions
				{
					//An iterator for the Ships from each faction in the conflict.
					auto enemyShipType_iter(factionShips.begin());
					//Iterate until the current faction is reached.
					for (; enemyShipType_iter->first != factionDamage_iter->first; ++enemyShipType_iter) {
						//The number of targets of the attacked type in this factions Ships.
						const size_t factionTargets(enemyShipType_iter->second.getCounter(shipTypeDamage_iter->first));
						//The portion of damage points which are aimed at the targets
						//in this faction.
						const __int32 portionedDamage(shipTypeDamage_iter->second * factionTargets / targetsSum);
						//Remove the portion of damage points from the output against this
						//targeted Ship type.
						factionDamage_iter->second.incCounter(shipTypeDamage_iter->first, -portionedDamage);
						//Remove the targets in this faction from the sum of targets.
						targetsSum -= factionTargets;
						//Add the portion of damage to the damage points against the
						//targeted Ship type.
						result.shipDamage.at(enemyShipType_iter->first).incCounter(enemyShipType_iter->first, portionedDamage);
					}
					//Skip the current faction.
					++enemyShipType_iter;
					//Iterate the remaining factions.
					for (auto enemyShipType_end(factionShips.end());
						 enemyShipType_iter != enemyShipType_end; ++enemyShipType_iter) {
						//The number of targets of the attacked type in this factions Ships.
						const size_t factionTargets(enemyShipType_iter->second.getCounter(shipTypeDamage_iter->first));
						//The portion of damage points which are aimed at the targets
						//in this faction.
						const __int32 portionedDamage(shipTypeDamage_iter->second * factionTargets / targetsSum);
						//Remove the portion of damage points from the output against this
						//targeted Ship type.
						factionDamage_iter->second.incCounter(shipTypeDamage_iter->first, -portionedDamage);
						//Remove the targets in this faction from the sum of targets.
						targetsSum -= factionTargets;
						//Add the portion of damage to the damage points against the
						//targeted Ship type.
						result.shipDamage.at(enemyShipType_iter->first).incCounter(enemyShipType_iter->first, portionedDamage);
					}
				}
#pragma endregion
			}
		}
#pragma endregion
#pragma region Calculate Deaths
		//Iterate the damage against each factions Ships.
		for (auto factionDamage_iter(result.shipDamage.begin()), factionDamage_end(result.shipDamage.end());
			 factionDamage_iter != factionDamage_end; ++factionDamage_iter)
			//Iterate the damage against each Ship type of the current faction.
			for (auto shipTypeDamage_iter(factionDamage_iter->second.begin()), shipTypeDamage_end(factionDamage_iter->second.end());
				 shipTypeDamage_iter != shipTypeDamage_end; ++shipTypeDamage_iter) {
			//The negative of the number of Ships which are destroyed by the
			//damage against their Ship type.
			__int32 deaths(
				(-shipTypeDamage_iter->second)
				/ ships.at(shipTypeDamage_iter->first).combat.hull
			);
			//Remove the used damage points from the damage against this Ship type.
			factionDamage_iter->second.incCounter(
				shipTypeDamage_iter->first,
				ships.at(shipTypeDamage_iter->first).combat.hull * deaths
			);
			//The total number of Ships of this type in the conflict from the
			//current faction.
			size_t shipTypeSum(factionShips.at(factionDamage_iter->first).getCounter(shipTypeDamage_iter->first));
#pragma region Distribute Deaths Around Fleets
			//Iterate all Fleets from the current faction.
			for (auto fleet_iter(result.fleets.at(factionDamage_iter->first).begin()), fleet_end(result.fleets.at(factionDamage_iter->first).end());
				 fleet_iter != fleet_end; ++fleet_iter) {
				//The number of Ships of the current type in the current Fleet.
				const size_t shipCount(fleets.at(*fleet_iter).getShips().getCounter(shipTypeDamage_iter->first));
				//The negative of the portion of the deaths occouring in this Fleet.
				const __int32 portionedDeaths(deaths * shipCount / shipTypeSum);
				//Remove the portion of deaths from the deaths being distributed.
				deaths -= portionedDeaths;
				try {
					//Remove the portion of deaths from the current Fleet and
					//the old count of Ships of the current type from the sum.
					shipTypeSum -= fleets.at(*fleet_iter).setShips(
						shipTypeDamage_iter->first,
						shipCount + portionedDeaths,
						ships, rsrc
					);
				} catch (...) {
					exit(-1);
				}
			}
#pragma endregion
		}
#pragma endregion
	}
#pragma endregion
	//Return the new frame.
	return result;
}

bool Space_Colony::Combat_Module::CombatInstance::addFleet(const size_t fltId, const FleetVector & fleets) {
	//Check if the faction does not exist in the conflict.
	if (frame.fleets.count(fleets.at(fltId).faction) == 0) {
		//If the faction does not exist, add the Fleet.
		frame.fleets[fleets.at(fltId).faction].insert(fltId);
		return true;
	}
	//Return the result of the insert.
	return frame.fleets.at(fleets.at(fltId).faction).insert(fltId).second;
}

bool Space_Colony::Combat_Module::CombatInstance::removeFleet(const size_t fltId, const FleetVector & fleets) {
	//Check if the faction does not exist in the conflict.
	if (frame.fleets.count(fleets.at(fltId).faction) == 0)
		//If the faction does not exist, return false.
		return false;
	//Return the result of the erase.
	return frame.fleets.at(fleets.at(fltId).faction).erase(fltId) != 0;
}

CombatInstance & Space_Colony::Combat_Module::CombatInstance::operator=(const CombatFrame & right) {
	frame = right;
	return *this;
}

bool Space_Colony::Combat_Module::CombatInstance::operator==(const CombatFrame & right) const {
	return frame == right;
}

bool Space_Colony::Combat_Module::CombatInstance::operator!=(const CombatFrame & right) const {
	return !operator==(right);
}

Space_Colony::Combat_Module::CombatInstance::operator CombatFrame&() {
	return frame;
}

Space_Colony::Combat_Module::CombatInstance::operator const CombatFrame&() const {
	return frame;
}
