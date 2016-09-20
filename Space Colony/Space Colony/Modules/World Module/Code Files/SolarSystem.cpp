#include "..\Headers\Star System\SolarSystem.h"
#include <unordered_map>

using namespace World_Module::Star_System;

SolarSystem::SolarSystem()
	: SolarSystem(0, 0, BoundedResourceMap(0)) {}

SolarSystem::SolarSystem(const SolarSystem & orig)
	: SolarSystem(orig.fleets, orig.planets, orig.structures, orig.resources) {}

SolarSystem::SolarSystem(unsigned __int32 plnts, unsigned __int32 strctrs, const BoundedResourceMap& rsrcs)
	: SolarSystem(Space_Colony::Ships::FleetVector(0), Star_System::PlanetVector(plnts),
				  Star_System::ConstructVector(strctrs), rsrcs) {}

SolarSystem::SolarSystem(const Space_Colony::Ships::FleetVector & flts, const PlanetVector & plnts,
						 const ConstructVector & strctrs, const BoundedResourceMap & rsrcs)
	: fleets(flts), planets(plnts), structures(strctrs), resources(rsrcs) {}

void SolarSystem::performTick() {
	unsigned __int32 i;
	BoundedResource rsrc;
	bool error;
	ResourceMap::const_iterator Resource_iter, Resource_end;
	for (i = 0; i < planets.size(); i++)
		planets[i].performTick();
	for (i = 0; i < structures.size(); i++)
		for (Resource_iter = structures[i]._resourceChange.begin(),
			 Resource_end = structures[i]._resourceChange.end();
			 Resource_iter != Resource_end; Resource_iter++) {
			rsrc = resources[Resource_iter->first].safeAddition(Resource_iter->second, error);
			if (error)
				throw std::exception("The resources were pushed outside the bounds.");
			resources[Resource_iter->first] = rsrc;
		}
}

const Space_Colony::faction_t World_Module::Star_System::SolarSystem::get_faction() const {
	std::unordered_map<Space_Colony::faction_t, __int32> factionCount;
	unsigned __int32 i;
	for (i = 0; i < planets.size(); i++)
		factionCount[planets[i].faction] = 0;
	Space_Colony::faction_t res(planets[0].faction);
	for (i = 1; i < planets.size(); i++)
		if (factionCount[planets[i].faction] > factionCount[res])
			res = planets[i].faction;
	return res;
}

const PlanetVector & SolarSystem::get_planets() const {
	return planets;
}

const ConstructVector & SolarSystem::get_structures() const {
	return structures;
}

const World_Module::BoundedResourceMap & SolarSystem::get_resources() const {
	return resources;
}
