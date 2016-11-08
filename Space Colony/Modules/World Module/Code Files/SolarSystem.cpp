#include "World Module\Headers\Galactic\SolarSystem.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galacitc;

Space_Colony::World_Module::Galacitc::SolarSystem::SolarSystem()
	: stars(0) {}

Space_Colony::World_Module::Galacitc::SolarSystem::SolarSystem(const SolarSystem & orig)
	: SolarSystem(orig, orig.name) {}

Space_Colony::World_Module::Galacitc::SolarSystem::SolarSystem(const SolarSystem & orig, const std::string & nm)
	: SolarSystem(nm, orig.stars, orig.planets, orig.fleets) {}

Space_Colony::World_Module::Galacitc::SolarSystem::SolarSystem(const std::string & nm, const size_t strs,
															   const PlanetVector & plnts)
	: name(nm), stars(strs), planets(plnts) {}

Space_Colony::World_Module::Galacitc::SolarSystem::SolarSystem(const std::string & nm, const size_t strs,
															   const PlanetVector & plnts, const FleetList & flts)
	: name(nm), stars(strs), planets(plnts), fleets(flts) {}

const SolarSystem::PlanetVector & Space_Colony::World_Module::Galacitc::SolarSystem::getPlanets() const {
	return planets;
}

Planet & Space_Colony::World_Module::Galacitc::SolarSystem::getPlanet(const size_t index) {
	return planets[index];
}

const Planet & Space_Colony::World_Module::Galacitc::SolarSystem::getPlanet(const size_t index) const {
	return planets[index];
}

const SolarSystem::FleetList & Space_Colony::World_Module::Galacitc::SolarSystem::getFleets() const {
	return fleets;
}

TypeCounter Space_Colony::World_Module::Galacitc::SolarSystem::getResources() const {
	TypeCounter res;
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		res += iter->getResources();
	return res;
}

size_t Space_Colony::World_Module::Galacitc::SolarSystem::getResource(const __int32 rsrc) const {
	size_t res(0);
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		res += iter->getResources().getCounter(rsrc);
	return res;
}

SolarSystem::FleetList Space_Colony::World_Module::Galacitc::SolarSystem::getFleetsByTags(const ShipType::RollTagSet & tags) const {
	FleetList res(fleets);
	for (auto iter(fleets.begin()), end(fleets.end()); iter != end; ++iter)
		for (auto tag(tags.begin()), tag_end(tags.end()); tag != tag_end; ++tag)
			if (iter->getRollTags().count(*tag) == 0)
				res.remove(*iter);
	return res;
}

void Space_Colony::World_Module::Galacitc::SolarSystem::addFleet(const Fleet & flt) {
	fleets.push_back(flt);
}

bool Space_Colony::World_Module::Galacitc::SolarSystem::removeFleet(const Fleet & flt) {
	auto pos(fleets.begin());
	for (auto end(fleets.end()); pos != end; ++pos)
		if (flt == *pos)
			goto fleetFound;
	return false;
fleetFound:
	fleets.erase(pos);
	return true;
}

faction_type Space_Colony::World_Module::Galacitc::SolarSystem::getFaction() const {
	faction_type res(( faction_type ) Game_Factions::no_faction);
	if (!planets.empty()) {
		res = planets.front().faction;
		auto iter(++planets.begin()), end(planets.end());
		for (; (res == ( faction_type ) Game_Factions::no_faction) && iter != end; ++iter)
			res = iter->faction;
		for (; iter != end; ++iter)
			if (res != iter->faction && (iter->faction != ( faction_type ) Game_Factions::no_faction))
				return ( faction_type ) Game_Factions::contested;
	}
	if (!fleets.empty()) {
		auto iter(fleets.begin()), end(fleets.end());
		for (; (res == ( faction_type ) Game_Factions::no_faction) && iter != end; ++iter)
			res = iter->faction;
		for (; iter != end; ++iter)
			if (res != iter->faction)
				return ( faction_type ) Game_Factions::contested;
	}
	return res;
}

void Space_Colony::World_Module::Galacitc::SolarSystem::iterate() {
	//	ToDo: implement the updating of this SolarSystem.
}

SolarSystem & Space_Colony::World_Module::Galacitc::SolarSystem::operator=(const SolarSystem & right) {
	name = right.name;
	stars = right.stars;
	planets = right.planets;
	fleets = right.fleets;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::SolarSystem::operator==(const SolarSystem & right) const {
	return (this == &right)
		|| (name == right.name
			&& stars == right.stars
			&& planets == right.planets
			&& fleets == right.fleets);
}

bool Space_Colony::World_Module::Galacitc::SolarSystem::operator!=(const SolarSystem & right) const {
	return !operator==(right);
}
