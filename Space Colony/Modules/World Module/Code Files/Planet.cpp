#include "World Module\Headers\Galactic\Planet.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galactic;

Space_Colony::World_Module::Galactic::Planet::Planet()
	: Planet(Game_Factions::no_faction, "Unnamed Planet", 0, 0, 0) {}

Space_Colony::World_Module::Galactic::Planet::Planet(const Planet & orig)
	: Planet(orig.faction, orig.name, orig.resources, orig.naturalCapacity,
			 orig.sites, orig.satellites) {}

Space_Colony::World_Module::Galactic::Planet::Planet(
	const faction_type fctn, const std::string & nm, const TypeCounter & rsrcs,
	const TypeCounter & ntrlCpcty, const size_t sts)
	: faction(fctn), name(nm), resources(rsrcs), naturalCapacity(ntrlCpcty),
	sites(sts), satellites() {}

Space_Colony::World_Module::Galactic::Planet::Planet(
	const faction_type fctn, const std::string & nm, const TypeCounter & rsrcs,
	const TypeCounter & ntrlCpcty, const ConstructVector sts,
	const ConstructList stlts)
	: faction(fctn), name(nm), resources(rsrcs), naturalCapacity(ntrlCpcty),
	sites(sts), satellites(stlts) {}

const TypeCounter & Space_Colony::World_Module::Galactic::Planet::getResources() const {
	return resources;
}

TypeCounter Space_Colony::World_Module::Galactic::Planet::setResources(
	const TypeCounter & rsrcs, const ConstructTypeVector types) {
	//Save the resources of the planet as a result.
	TypeCounter res(resources);
	//Check if the new resources are positive.
	if (!rsrcs.isPos())
		//If the new resources are not positive, throw an error.
		throw Invalid_Counter_Exception;
	//Check if the new resources are within the capacity of the planet.
	if (rsrcs >= getResourceCapacity(types))
		//If the new resource exceed the capacity, throw an error.
		throw Resource_Capacity_Exceeded;
	//Set the new resources.
	resources = rsrcs;
	//Return the old resources as the result.
	return res;
}

const TypeCounter & Space_Colony::World_Module::Galactic::Planet::getNaturalCapacity() const {
	return naturalCapacity;
}

TypeCounter Space_Colony::World_Module::Galactic::Planet::setNaturalCapacity(
	const TypeCounter & ntrlCpcty, const ConstructTypeVector types) {
	//Save the resources of the planet as a result.
	TypeCounter res(naturalCapacity);
	//Set the new capacity.
	naturalCapacity = ntrlCpcty;
	//Check if the new capacity is less than the resources.
	if (resources >= getResourceCapacity(types)) {
		//If the new capaicty is less than the resources...
		//Reset the old capacity.
		naturalCapacity = res;
		//Throw an error.
		throw Resource_Capacity_Exceeded;
	}
	//Return the old resources as the result.
	return res;
}

const Planet::ConstructVector & Space_Colony::World_Module::Galactic::Planet::getSites() const {
	return sites;
}

Planetary::Construct & Space_Colony::World_Module::Galactic::Planet::getSite(const size_t site) {
	return sites.at(site);
}

const Planetary::Construct & Space_Colony::World_Module::Galactic::Planet::getSite(const size_t site) const {
	return sites.at(site);
}

Planet::ConstructVector Space_Colony::World_Module::Galactic::Planet::setSites(
	const ConstructVector &sts, const ConstructTypeVector types) {
	//Save the old sites as the result.
	ConstructVector res(sites);
	//Check if the sizes for the sites are the same.
	if (sts.size() != sites.size())
		//If the sizes are not the same, throw an error.
		throw Site_Size_Exception;
	//Set the new sites.
	sites = sts;
	//Check if the new resources capacity is less than the resources.
	if (resources > getResourceCapacity(types)) {
		//If the new resources capacity is less than the resources...
		//Reset the sites.
		sites = res;
		//Throw an error.
		throw Resource_Capacity_Exceeded;
	}
	//Return the old sites.
	return res;
}

Planet::ConstructList & Space_Colony::World_Module::Galactic::Planet::getSatellites() {
	return satellites;
}

const Planet::ConstructList & Space_Colony::World_Module::Galactic::Planet::getSatellites() const {
	return satellites;
}

Planet::ConstructList Space_Colony::World_Module::Galactic::Planet::setSatellites(
	const ConstructList & stlts, const ConstructTypeVector types) {
	//Save the satellites as the result.
	ConstructList res(satellites);
	//Set the new satellites.
	satellites = stlts;
	//Check if the new resources capacity is less than the resources.
	if (resources > getResourceCapacity(types)) {
		//If the new resources capacity is less than the resources...
		//Reset the satellites.
		satellites = res;
		//Throw an error.
		throw Resource_Capacity_Exceeded;
	}
	//Return the old satellites.
	return res;
}

size_t Space_Colony::World_Module::Galactic::Planet::setResource(
	const size_t resource_type, const size_t val, const ConstructTypeVector types) {
	//Check if the new resource is less than the resource capacity.
	if (val > getResourceCapacity(resource_type, types))
		//If the new resource is less than the resource capacity, throw an error.
		throw Resource_Capacity_Exceeded;
	//Set the new resource value and return the old resource value.
	return resources.setCounter(resource_type, val);
}

void Space_Colony::World_Module::Galactic::Planet::addSatellite(const Planetary::Construct & cnstrct) {
	//Add the new satellite.
	satellites.push_back(cnstrct);
}

void Space_Colony::World_Module::Galactic::Planet::removeSatellite(
	const Planetary::Construct & cnstrct, const ConstructTypeVector types) {
	//Iterate all satellites.
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Check if the satellite matches the passed construct.
		if (cnstrct == *iter) {
			//If the satellite matches the passed construct...
			//Remove the satellite from the satellites on the planet.
			satellites.erase(iter);
			//Check if the new resources capacity is less than the resources.
			if (resources > getResourceCapacity(types)) {
				//If the new resource capacity is less than the resources...
				//Re-add the satellite to the planet.
				satellites.push_back(cnstrct);
				//Throw an error.
				throw Resource_Capacity_Exceeded;
			}
			//Satellite removed, exit the function.
			return;
		}
}

bool Space_Colony::World_Module::Galactic::Planet::isSuperConstruct() const {
	//Check if the first site is active.
	if (!sites.front().active)
		//If the first site is not active, return false.
		return false;
	//Iterate all remaining sites.
	for (auto iter(++sites.begin()), end(sites.end()); iter != end; ++iter)
		//Check if the type ids allign for the sites...
		if (sites.front().typeId != iter->typeId 
			//And the construct is active.
			|| !iter->active)
			//If the construct does not allign with the first or it's
			//not active, return false.
			return false;
	//This is a super construct, return true.
	return true;
}

size_t Space_Colony::World_Module::Galactic::Planet::setNaturalCapacity(
	const size_t resource_type, const size_t val, const ConstructTypeVector types) {
	//Check if the value is less than the resource capacity.
	if (val < getResourceCapacity(resource_type, types))
		//If the value is less than the resource capacity, throw an error.
		throw Resource_Capacity_Exceeded;
	//Set the new resource counter and return the old counter.
	return naturalCapacity.setCounter(resource_type, val);
}

TypeCounter Space_Colony::World_Module::Galactic::Planet::getResourceCapacity(
	const ConstructTypeVector types) const {
	//Save the natural resources capacity as the result.
	TypeCounter res(naturalCapacity);
	//Iterate all the sites.
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		//Check if the construct is active.
		if (iter->active)
			//Accumulate the resources capacity to the result.
			res += types.at(iter->typeId).resourceCapacity;
	//Iterate all the satellites.
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Check if the construct is active.
		if (iter->active)
			//Accumulate the resources capacity to the result.
			res += types.at(iter->typeId).resourceCapacity;
	//Return the cummulative resources capacity.
	return res;
}

size_t Space_Colony::World_Module::Galactic::Planet::getResourceCapacity(
	const size_t resource_type, const ConstructTypeVector types) const {
	//Save the natural resource capacity as the result.
	size_t res(naturalCapacity.getCounter(resource_type));
	//Iterate all the sites.
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		//Check if the construct is active.
		if (iter->active)
			//Accumulate the resource capacity to the result.
			res += types.at(iter->typeId).resourceCapacity.getCounter(resource_type);
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Check if the construct is active.
		if (iter->active)
			//Accumulate the resource capacity to the result.
			res += types.at(iter->typeId).resourceCapacity.getCounter(resource_type);
	//Return the cummulative resource capacity.
	return res;
}

bool Space_Colony::World_Module::Galactic::Planet::isFilled(const size_t site) const {
	//Return true if the type id is -1 (a non filled site).
	return sites.at(site).typeId != -1;
}

void Space_Colony::World_Module::Galactic::Planet::emptySite(const size_t site) {
	//Set the site to be inactive.
	sites.at(site).active = false;
	//Set the type id to -1.
	sites.at(site).typeId = -1;
}

Planet & Space_Colony::World_Module::Galactic::Planet::operator=(const Planet & right) {
	faction = right.faction;
	name = right.name;
	resources = right.resources;
	naturalCapacity = right.naturalCapacity;
	sites = right.sites;
	satellites = right.satellites;
	return *this;
}

bool Space_Colony::World_Module::Galactic::Planet::operator==(const Planet & right) const {
	return faction == right.faction
		&& name == right.name
		&& resources == right.resources
		&& naturalCapacity == right.naturalCapacity
		&& sites == right.sites
		&& satellites == right.satellites;
}

bool Space_Colony::World_Module::Galactic::Planet::operator!=(const Planet & right) const {
	return !operator==(right);
}
