#include "World Module\Headers\Galactic\SolarSystem.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galactic;

Space_Colony::World_Module::Galactic::SolarSystem::SolarSystem()
	: name("Unnamed SolarSystem"), stars(0), planets(0) {}

Space_Colony::World_Module::Galactic::SolarSystem::SolarSystem(const SolarSystem & orig)
	: SolarSystem(orig.name, orig.stars, orig.planets, orig.fleets) {}

Space_Colony::World_Module::Galactic::SolarSystem::SolarSystem(
	const std::string nm, const size_t strs, const PlanetVector & plnts,
	const FleetIdSet & flts)
	: name(nm), stars(strs), planets(plnts), fleets(flts) {}

size_t Space_Colony::World_Module::Galactic::SolarSystem::getStars() const {
	return stars;
}

const SolarSystem::PlanetVector & Space_Colony::World_Module::Galactic::SolarSystem::getPlanets() const {
	return planets;
}

SolarSystem::PlanetVector Space_Colony::World_Module::Galactic::SolarSystem::setPlanets(const PlanetVector & plnts) {
	//Save the planets as the result.
	PlanetVector res(planets);
	//Check if there are the same number of Planets.
	if (plnts.size() != planets.size())
		//If the planets are not the same dimensions, throw an error.
		throw Planets_Size_Exception;
	//Reassign the planets.
	planets = plnts;
	//Return the old planets.
	return res;
}

Planet & Space_Colony::World_Module::Galactic::SolarSystem::getPlanet(const size_t index) {
	return planets.at(index);
}

const Planet & Space_Colony::World_Module::Galactic::SolarSystem::getPlanet(const size_t index) const {
	return planets.at(index);
}

const SolarSystem::FleetIdSet & Space_Colony::World_Module::Galactic::SolarSystem::getFleets() const {
	return fleets;
}

SolarSystem::FleetIdSet Space_Colony::World_Module::Galactic::SolarSystem::setFleets(const FleetIdSet & flts) {
	//Save the old fleet set as the result.
	FleetIdSet res(fleets);
	//Reassign the fleets.
	fleets = flts;
	//Return the old fleet set.
	return res;
}

TypeCounter Space_Colony::World_Module::Galactic::SolarSystem::getResources() const {
	//Create an empty TypeCounter as the result.
	TypeCounter res;
	//Iterate all planets.
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		//Accumulate the resources from the planet into the result.
		res += iter->getResources();
	//Return the cummulative resources.
	return res;
}

size_t Space_Colony::World_Module::Galactic::SolarSystem::getResource(const size_t resource_type) const {
	//Create a 0 resource counter as the result.
	size_t res(0);
	//Iterate all planets.
	for (auto iter(planets.begin()), end(planets.end()); iter != end; ++iter)
		//Accumulate the resource from the planet into the result.
		res += iter->getResources().getCounter(resource_type);
	//Return the cummulative resource.
	return res;
}

void Space_Colony::World_Module::Galactic::SolarSystem::addFleet(const size_t fltId) {
	fleets.insert(fltId);
}

void Space_Colony::World_Module::Galactic::SolarSystem::moveFleet(const size_t fltId, SolarSystem & from, SolarSystem & to) {
	//Remove the fleet from the first solar system.
	from.removeFleet(fltId);
	//Add the fleet to the second solar system.
	to.addFleet(fltId);
}

void Space_Colony::World_Module::Galactic::SolarSystem::removeFleet(const size_t fltId) {
	//Check if the fleet exists in this SolarSystem.
	if (fleets.count(fltId) == 0)
		//If the fleet is not in this solar system, throw an error.
		throw Fleet_Not_Found_Exception;
	//Remove the fleet from the solar system.
	fleets.erase(fltId);
}

faction_type Space_Colony::World_Module::Galactic::SolarSystem::getFaction(const Space_Colony::FleetVector &flts) const {
	//Get the faction of the first planet as a result.
	faction_type res(planets.front().faction);
	{
		//Create iterators for the remaining planets.
		auto iter(++planets.begin()), end(planets.end());
		//Check whether the current faction is alligned with a faction.
		if (res == Game_Factions::no_faction)
			//If the current faction is not alligned with a faction,
			//iterate remaining planets.
			for (; iter != end; ++iter) {
				//Get the new faction.
				res = iter->faction;
				//Check if the new faction is alligned with a faction.
				if (res != Game_Factions::no_faction)
					//If the new faction is alligned break the loop.
					break;
			}
		//Iterate remaining planets.
		for (; iter != end; ++iter)
			//Check whether this planets faction does not allign with
			//the result faction...
			if (res != iter->faction
				//And this planets faction alligns with a faction.
				&& iter->faction != Game_Factions::no_faction)
				//If there is another faction present, return conflicted.
				return Game_Factions::conflicted;
	}
	//Create iterators for the fleets in this solar system.
	auto iter(fleets.begin()), end(fleets.end());
	//Check whether the current faction is alligned with a faction.
	if (res == Game_Factions::no_faction) {
		//If the current faction is not alligned with a faction...
		//Get the faction of the first fleet.
		res = flts.at(*iter).faction;
		//Increment the iterator.
		++iter;
	}
	//Iterate the remaining fleets.
	for (; iter != end; ++iter)
		//Check whether the fleets faction differs from the current faction.
		if (flts.at(*iter).faction != res)
			//If the fleets faction differs from the current faction,
			//return conflicted.
			return Game_Factions::conflicted;
	//Return the resulting faction.
	return res;
}

void Space_Colony::World_Module::Galactic::SolarSystem::iterate(const FleetVector &flts, const ConstructTypeVector &cnstrct) {
	//Get the current faction as the state for the state machine.
	faction_type state(getFaction(flts));
	if (state >= Game_Factions::player) { 
		for (auto planet_iter(planets.begin()), planet_end(planets.end());
			 planet_iter != planet_end; ++planet_iter) {
			//Check whether the current planet is a super construct.
			if (planet_iter->isSuperConstruct()) {
				//If the planet is a super construct...
				//Generate the shift generated by a super construct.
				TypeCounter shift((cnstrct.at(planet_iter->getSite(0).typeId).resourceShift.getPos() * 2)
								  + (cnstrct.at(planet_iter->getSite(0).typeId).resourceShift.getNeg() / 2));
				//Create an index for the ground sites on this planet.
				size_t site(0);
				//Iterate all ground sites on this planet.
				for (; site < planet_iter->getSites().size(); ++site) {
					try {
						//Attempt to set the new resources.
						planet_iter->setResources(shift + planet_iter->getResources(), cnstrct);
					} catch (...) {
						//If the resources exceed limits, the new resources
						//will not be set; deactivate the construct.
						planet_iter->getSite(site).active = false;
					}
				}
				//Iterate the remaining ground sites on this planet.
				for (; site < planet_iter->getSites().size(); ++site)
					//deactivate the construct.
					planet_iter->getSite(site).active = false;
			} else {
				//Iterate all the ground sites on this planet.
				for (size_t site(0); site < planet_iter->getSites().size(); ++site) {
					//Check if the ground site is filled...
					if (planet_iter->isFilled(site)
						//And that the ground site is active.
						&& planet_iter->getSite(site).active) {
						try {
							//Attempt to set the new resources.
							planet_iter->setResources(
								cnstrct.at(planet_iter->getSite(site).typeId).resourceShift
								+ planet_iter->getResources(), cnstrct);
						} catch (...) {
							//If the resources exceed limits, the new resources
							//will not be set; deactivate the construct.
							planet_iter->getSite(site).active = false;
						}
					}
				}
			}
			//Iterate all the satellites.
			for (auto satellite_iter(planet_iter->getSatellites().begin()),
				 satellite_end(planet_iter->getSatellites().end());
				 satellite_iter != satellite_end; ++satellite_iter) {
				//Check if the satellite is active.
				if (satellite_iter->active) {
					try {
						//Attempt to set the new resources.
						planet_iter->setResources(
							cnstrct.at(satellite_iter->typeId).resourceShift
							+ planet_iter->getResources(), cnstrct);
					} catch (...) {
						//If the resources exceed limits, the new resources
						//will not be set; deactivate the construct.
						satellite_iter->active = false;
					}
				}
			}
		}
	} else {
		throw Update_State_Unhandled;
	}
}

SolarSystem Space_Colony::World_Module::Galactic::SolarSystem::operator=(const SolarSystem & right) {
	name = right.name;
	stars = right.stars;
	planets = right.planets;
	fleets = right.fleets;
	return *this;
}

bool Space_Colony::World_Module::Galactic::SolarSystem::operator==(const SolarSystem & right) const {
	return name == right.name
		&& stars == right.stars
		&& planets == right.planets
		&& fleets == right.fleets;
}

bool Space_Colony::World_Module::Galactic::SolarSystem::operator!=(const SolarSystem & right) const {
	return !operator==(right);
}
