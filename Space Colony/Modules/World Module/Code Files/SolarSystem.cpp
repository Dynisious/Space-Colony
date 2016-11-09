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
															   const PlanetVector & plnts, const FleetSet & flts)
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

const SolarSystem::FleetSet & Space_Colony::World_Module::Galacitc::SolarSystem::getFleets() const {
	return fleets;
}

void Space_Colony::World_Module::Galacitc::SolarSystem::clean() {
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		iter->clean();
	std::unordered_set<FleetRef> removals;
	for (auto iter(fleets.begin()), end(fleets.end()); iter != end; ++iter)
		if (!iter->check())
			removals.insert(*iter);
	for (auto iter(removals.begin()), end(removals.end()); iter != end; ++iter)
		fleets.erase(*iter);
}

TypeCounter Space_Colony::World_Module::Galacitc::SolarSystem::getResources() const {
	TypeCounter res;
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		//Iterate and accumulate all the resources.
		res += iter->getResources();
	return res;
}

size_t Space_Colony::World_Module::Galacitc::SolarSystem::getResource(const __int32 rsrc) const {
	size_t res(0);
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		//Iterate and accumulate all the resource of the passed type.
		res += iter->getResources().getCounter(rsrc);
	return res;
}

SolarSystem::FleetSet Space_Colony::World_Module::Galacitc::SolarSystem::getFleetsByTags(
	const ShipType::RollTagSet & tags, const ShipType::RollTagSet & exclude) const {
	FleetSet res;
	for (auto iter(fleets.begin()), end(fleets.end()); iter != end; ++iter) {
		bool load(true);
		const ShipType::RollTagSet fleetTags((*iter)->getRollTags());
		for (auto tag_iter(tags.begin()), tag_end(tags.end()); tag_iter != tag_end; ++tag_iter)
			//Check all include tags.
			if (fleetTags.count(*tag_iter) == 0) {
				//This tag is not included.
				load = false;
				goto LoadFleet;
			}
		for (auto exclude_iter(tags.begin()), exclude_end(tags.end()); exclude_iter != exclude_end; ++exclude_iter)
			//Check all include tags.
			if (fleetTags.count(*exclude_iter) != 0) {
				//This tag is not included.
				load = false;
				goto LoadFleet;
			}
LoadFleet:
		if (load)
			//The Fleet meets all the conditions.
			res.insert(*iter);
	}
	return res;
}

void Space_Colony::World_Module::Galacitc::SolarSystem::addFleet(const FleetRef & flt) {
	fleets.insert(flt);
}

bool Space_Colony::World_Module::Galacitc::SolarSystem::removeFleet(const FleetRef & flt) {
	auto pos(fleets.begin());
	for (auto end(fleets.end()); pos != end; ++pos)
		//Iterate all the Fleets.
		if (flt == *pos) {
			//The fleets are the same, remove it.
			fleets.erase(pos);
			return true;
		}
	return false;
}

faction_type Space_Colony::World_Module::Galacitc::SolarSystem::getFaction() const {
	faction_type res(planets.front().faction);
	{
		auto iter(++planets.begin()), end(planets.end());
		for (; (res == ( faction_type ) Game_Factions::no_faction) && iter != end; ++iter)
			//Iterate all planets until an actual faction is found.
			res = iter->faction;
		for (; iter != end; ++iter)
			//Iterate the remaining planets.
			if (res != iter->faction &&
				(iter->faction != ( faction_type ) Game_Factions::no_faction))
				//The factions differ and the second faction is an actual
				//faction, this SolarSystem is contested.
				return ( faction_type ) Game_Factions::contested;
	}
	if (!fleets.empty()) {
		//There are Fleets to affect the faction.
		if (res == ( faction_type ) Game_Factions::no_faction)
			//The Planets have no faction so take the first Fleet as the
			//faction and compare the other Fleets to it.
			return (*fleets.begin())->faction;
		for (auto iter(fleets.begin()), end(fleets.end()); iter != end; ++iter)
			//Iterate all Fleets.
			if (res != (*iter)->faction)
				//The factions differ, this SolarSystem is contested.
				return ( faction_type ) Game_Factions::contested;
	}
	return res;
}

void Space_Colony::World_Module::Galacitc::SolarSystem::iterate() {
	clean();
	switch (getFaction()) {
	default:
#pragma region Standard Iteration
		for (auto planet_iter(planets.begin()), planet_end(planets.end()); planet_iter != planet_end; ++planet_iter) {
			//Iterate each planet.
			if (planet_iter->faction != ( faction_type ) Game_Factions::no_faction) {
				//The planet is aligned with a faction.
#pragma region Site Iterations
				for (auto cnstrct_iter(planet_iter->getSites().begin()), cnstrct_end(planet_iter->getSites().end());
					 cnstrct_iter != cnstrct_end; ++cnstrct_iter) {
					//Iterate every site on the Planet.
					if (cnstrct_iter->check()) {
						//The type is loaded.
						if (cnstrct_iter->active &&
							//The construct is active.
							((*cnstrct_iter)->tags.count(Planetary::ConstructType_FunctionTags::City) != 0
							|| (*cnstrct_iter)->tags.count(Planetary::ConstructType_FunctionTags::Agricultural) != 0
							|| (*cnstrct_iter)->tags.count(Planetary::ConstructType_FunctionTags::Constant_Drain) != 0)) {
							//The construct has city, agricultural or constant_drain tags.
							TypeCounter shift((*cnstrct_iter)->resourceShift);
							if (planet_iter->isSuperConstruct())
								//The Planet operates as a Super Construct; adjust the resource shifts.
								shift = ((shift.getPos() *= 2) += (shift.getNeg() /= 2));
							try {
								planet_iter->incResources(shift);
								//Increment the resources.
							} catch (...) {
								//The increment cannot be done, deactivate the construct.
								planet_iter->findConstruct(*cnstrct_iter).first->active = false;
							}
						}
					}
				}
#pragma endregion
#pragma region Satallite Iteration
				for (auto cnstrct_iter(planet_iter->getSatellites().begin()), cnstrct_end(planet_iter->getSatellites().end());
					 cnstrct_iter != cnstrct_end; ++cnstrct_iter) {
					//Iterate every site on the Planet.
					if (cnstrct_iter->check()) {
						//The type is loaded.
						if (cnstrct_iter->active &&
							//The construct is active.
							(*cnstrct_iter)->tags.count(Planetary::ConstructType_FunctionTags::Constant_Drain) != 0) {
							//The construct has constant_drain tag.
							try {
								planet_iter->incResources((*cnstrct_iter)->resourceShift);
								//Increment the resources.
							} catch (...) {
								//The increment cannot be done, deactivate the construct.
								planet_iter->findConstruct(*cnstrct_iter).first->active = false;
							}
						}
					}
				}
#pragma endregion
			}
		}
		break;
#pragma endregion
	}
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
