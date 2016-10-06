#include "..\Headers\Galactic\StarSystem.h"

World_Module::Galactic::StarSystem::StarSystem()
	: StarSystem(Space_Colony::TypeCounter(), PlanetVector(0)) {}

World_Module::Galactic::StarSystem::StarSystem(const StarSystem & orig)
	: StarSystem(orig.freeResources, orig.planets, orig.fleets) {}

World_Module::Galactic::StarSystem::StarSystem(const Space_Colony::TypeCounter & frRsrcs, const PlanetVector & plnts)
	: freeResources(frRsrcs), planets(plnts), fleets() {}

World_Module::Galactic::StarSystem::StarSystem(const Space_Colony::TypeCounter & frRsrcs, const PlanetVector & plnts, const FleetList & flts)
	: freeResources(frRsrcs), planets(plnts), fleets(flts) {}

World_Module::tagSet World_Module::Galactic::StarSystem::get_tags() const {
	tagSet res;
	for (__int32 i(0); i < planets.size(); i++)
		//Collect the tags of this Planet.
		res.insert(planets[i]._tags.begin(), planets[i]._tags.end());
	return res;
}

Space_Colony::TypeCounter World_Module::Galactic::StarSystem::get_totalResources() const {
	Space_Colony::TypeCounter res(freeResources);
	for (__int32 i(0); i < planets.size(); i++)
		//Collect the resources of this Planet.
		res += planets[i].resources;
	return res;
}

Space_Colony::faction_t World_Module::Galactic::StarSystem::get_faction() const {
	Space_Colony::faction_t res(planets[0].faction);
	for (__int32 i(1); i < planets.size(); i++)
		if (planets[i].faction != res && planets[i].faction != Space_Colony::Faction_Neutral)
			//There is a conflict in factions.
			return Space_Colony::Faction_Contested;
	for (FleetList::const_iterator iter(fleets.begin()), end(fleets.end()); iter != end; iter++)
		if (iter->faction != res && iter->faction != Space_Colony::Faction_Neutral)
			//There is a conflict in factions.
			return Space_Colony::Faction_Contested;
	return res;
}

World_Module::Galactic::StarSystem & World_Module::Galactic::StarSystem::operator=(const StarSystem & right) {
	freeResources = right.freeResources;
	planets = right.planets;
	fleets = right.fleets;
	return *this;
}

bool World_Module::Galactic::StarSystem::operator==(const StarSystem & right) const {
	return (this == &right)
		|| (freeResources == right.freeResources
			&& planets == right.planets
			&& fleets == right.fleets);
}

bool World_Module::Galactic::StarSystem::operator!=(const StarSystem & right) const {
	return !operator==(right);
}
