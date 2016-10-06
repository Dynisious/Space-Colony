#include "..\Headers\ConflictInstance.h"

Combat_Module::ConflictInstance::ConflictInstance()
	: ConflictInstance(FleetList()) {}

Combat_Module::ConflictInstance::ConflictInstance(const ConflictInstance & orig)
	: ConflictInstance(orig.fleets) {}

Combat_Module::ConflictInstance::ConflictInstance(const FleetList & flts) {
	for (FleetList::const_iterator iter(flts.begin()), end(flts.end()); iter != end; iter++)
		addFleet(*iter);
}

Combat_Module::ConflictInstance::ConflictInstance(const FleetMap & flts)
	: fleets(flts.size()), engagedShips(flts.size()), pendingHits(flts.size()) {
	FleetList::const_iterator Fleet_iter, Fleet_end;
	for (FleetMap::const_iterator Faction_iter(flts.begin()), Faction_end(flts.end()); Faction_iter != Faction_end; Faction_iter++)
		//Iterate each faction in the passed FleetMap.
		for (Fleet_iter = Faction_iter->second.begin(), Fleet_end = Faction_iter->second.end();
			 Fleet_iter != Fleet_end; Fleet_iter++)
			//Add the Fleets from the current Faction in the FleetMap.
			addFleet(*Fleet_iter);
}

void Combat_Module::ConflictInstance::addFleet(const Space_Colony::Fleet & flt) {
	fleets[flt.faction].push_back(flt);
	engagedShips[flt.faction] += flt;
	//Add the Fleets ships to the engaged ships.
}

__int32 Combat_Module::ConflictInstance::iterate() {
	CounterMap counter(getAllAttacks());
	//Get all the attacks for this iteration.
	counter = distributeAllAttacks(counter);
	//Distribute the attacks for this iteration.
	CounterMap::const_iterator iter, end;
	for (iter = counter.begin(), end = counter.end(); iter != end; iter++)
		//Add the distributed hits to the pending hits
		pendingHits[iter->first] += iter->second;
	counter = getAllDeaths();
	//Get all the deaths for this iteration.
	for (iter = counter.begin(), end = counter.end(); iter != end; iter++)
		//Remove all the dead ships for this iteration.
		engagedShips[iter->first] -= iter->second;
	return clean();
}

Combat_Module::ConflictInstance::FleetList Combat_Module::ConflictInstance::resolve() {
	while (iterate() == 0);
	return dispand();
}

__int32 Combat_Module::ConflictInstance::clean() {
	__int32 res = 0;
	std::vector<CounterMap::key_type> removals;
	for (CounterMap::iterator iter(engagedShips.begin()), end(engagedShips.end()); iter != end; iter++) {
		iter->second.clean();
		if (iter->second.size() == 0)
			//If there are no engaged ships remove the faction.
			removals.push_back(iter->first);
	}
	for (__int32 i(0); i < removals.size(); i++) {
		engagedShips.erase(removals[i]);
		//Remove the counter for the factions ships.
		fleets.erase(removals[i]);
		//Remove the Fleets for the faction.
	}
	return res;
}

Combat_Module::ConflictInstance::FleetList Combat_Module::ConflictInstance::dispand() {
	FleetList res;
	//ToDo!!!
	return res;
}

Combat_Module::ConflictInstance::ConflictID Combat_Module::ConflictInstance::get_ID() const {
	return id;
}

Combat_Module::ConflictInstance & Combat_Module::ConflictInstance::operator=(const ConflictInstance & right) {
	fleets = right.fleets;
	engagedShips = right.engagedShips;
	pendingHits = right.pendingHits;
	return *this;
}

bool Combat_Module::ConflictInstance::operator==(const ConflictInstance & right) const {
	return (this == &right)
		|| (fleets == right.fleets
			&& engagedShips == right.engagedShips
			&& pendingHits == right.pendingHits);
}

bool Combat_Module::ConflictInstance::operator!=(const ConflictInstance & right) const {
	return !operator==(right);
}

Combat_Module::ConflictInstance::CounterMap Combat_Module::ConflictInstance::getAllAttacks() {
	CounterMap res(engagedShips.size());
	for (CounterMap::const_iterator iter(engagedShips.begin()), end(engagedShips.end());
		 iter != end; iter++)
		//Get the attacks from each faction.
		res[iter->first] = getFactionAttacks(iter->first);
	return res;
}

Combat_Module::ConflictInstance::CounterMap::mapped_type Combat_Module::ConflictInstance::getFactionAttacks(Space_Colony::faction_t faction) {
	CounterMap::mapped_type res;
	Ship_Types::ShipTemplate type;
	for (CounterMap::mapped_type::const_iterator iter(engagedShips[faction].begin()), end(engagedShips[faction].end());
		 iter != end; iter++) {
		//Iterate the counters for the faction.
		Ship_Types::ShipTemplate_getTemplate(iter->first, type);
		//Get the ShipTemplate attacking.
		res.setCounter(iter->first, APPLYFRAC(type._attacks, type._hitChance, P100));
		//Get the accurate attacks from these ships.
	}
	return res;
}

Combat_Module::ConflictInstance::CounterMap Combat_Module::ConflictInstance::distributeAllAttacks(const CounterMap & attacks) {
	CounterMap res;
	for (CounterMap::const_iterator iter(attacks.begin()), end(attacks.end()); iter != end; iter++)
		//Iterate each faction and distribute their attacks.
		distributeFactionAttacks(iter->first, iter->second, res);
	return res;
}

void Combat_Module::ConflictInstance::distributeFactionAttacks(Space_Colony::faction_t faction, const CounterMap::mapped_type & attacks,
															   CounterMap & distributedHits) {
	for (CounterMap::mapped_type::const_iterator iter(attacks.begin()), end(attacks.end()); iter != end; iter++)
		//Iterate each attacking type and distribute its attacks for the faction.
		distributeTypeAttacksForFaction(iter->first, iter->second, faction, distributedHits);
}

void Combat_Module::ConflictInstance::filterAttackableTypes(const Ship_Types::ShipTemplate & type, const CounterMap::mapped_type & targets,
															CounterMap::mapped_type & attackable) {
	for (CounterMap::mapped_type::const_iterator iter(targets.begin()), end(targets.end()); iter != end; iter++)
		//Iterate each targeted type.
		if (iter->first > type.sizeMin && iter->first < type.sizeMax)
			//To be a valid target a type must have a size within the bounds of
			//the attacking type.
			attackable.setCounter(iter->first, iter->second);
}

void Combat_Module::ConflictInstance::distributeAttacks(const __int32 attacks, const CounterMap::mapped_type & targets,
														CounterMap::mapped_type & distributedHits) {
	const __int32 targetsSum(targets.sum());
	for (CounterMap::mapped_type::const_iterator iter(targets.begin()), end(targets.end()); iter != end; iter++)
		//Iterate each targeted type and increment the attacks against them by their proportion of targets.
		distributedHits.incrementCounter(iter->first, APPLYFRAC(attacks, iter->second, targetsSum));
}

void Combat_Module::ConflictInstance::distributeTypeAttacksForFaction(const __int32 typeID, __int32 attacks, Space_Colony::faction_t faction,
																	  CounterMap & distributedHits) {
	Ship_Types::ShipTemplate type;
	Ship_Types::ShipTemplate_getTemplate(typeID, type);
	CounterMap typeRatios;
	Space_Colony::TypeCounter factionRatios;

	CounterMap::const_iterator iter(engagedShips.begin()), end(engagedShips.end());
	for (; iter->first != faction; iter++)
		//Iterate each faction and filter their ships down to valid targets.
		filterAttackableTypes(type, iter->second, typeRatios[iter->first]);
	iter++;
	//Skip the attacking faction.
	for (; iter != end; iter++)
		//Iterate each faction and filter their ships down to valid targets.
		filterAttackableTypes(type, iter->second, typeRatios[iter->first]);

	for (iter = typeRatios.begin(); iter != end; iter++)
		//Iterate each faction and get the total number of targets they provide.
		factionRatios.setCounter(iter->first, iter->second.sum());

	const __int32 factionRatiosSum(factionRatios.sum());
	for (iter = typeRatios.begin(); iter != end; iter++)
		//Iterate each faction and distribute their portion of attacks against
		//them against their targeted ships.
		distributeAttacks(APPLYFRAC(attacks, factionRatios[iter->first], factionRatiosSum),
						  iter->second, distributedHits[iter->first]);
}

Combat_Module::ConflictInstance::CounterMap Combat_Module::ConflictInstance::getAllDeaths() {
	CounterMap res;
	for (CounterMap::const_iterator iter(pendingHits.begin()), end(pendingHits.end()); iter != end; iter++)
		res[iter->first] = getFactionDeaths(iter->second);
	return res;
}

Combat_Module::ConflictInstance::CounterMap::mapped_type Combat_Module::ConflictInstance::getFactionDeaths(const CounterMap::mapped_type & attacks) {
	CounterMap::mapped_type res;
	for (CounterMap::mapped_type::const_iterator iter(attacks.begin()), end(attacks.end()); iter != end; iter++)
		res.setCounter(iter->first, getTypeDeaths(iter->first, iter->second));
	return res;
}

__int32 Combat_Module::ConflictInstance::getTypeDeaths(__int32 typeID, const __int32 attacks) {
	Ship_Types::ShipTemplate type;
	Ship_Types::ShipTemplate_getTemplate(typeID, type);
	return type.deaths(attacks);
}
