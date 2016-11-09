#include "World Module\Headers\Galactic\Planet.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galacitc;

Space_Colony::World_Module::Galacitc::Planet::Planet()
	: faction(( faction_type ) Game_Factions::no_faction) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const Planet & orig)
	: Planet(orig, orig.faction, orig.name) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const Planet & orig, const faction_type fctn)
	: Planet(orig, fctn, orig.name) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const Planet & orig, const std::string & nm)
	: Planet(orig, orig.faction, nm) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const Planet & orig, const faction_type fctn, const std::string & nm)
	: Planet(fctn, nm, orig.resources, orig.naturalCapacity, orig.sites, orig.satellites) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const faction_type fctn, const std::string & nm, const TypeCounter & rsrcs,
													 const TypeCounter & ntrlCpcty, const size_t bldngs)
	: faction(fctn), name(nm), resources(rsrcs), naturalCapacity(ntrlCpcty), sites(bldngs) {}

Space_Colony::World_Module::Galacitc::Planet::Planet(const faction_type fctn, const std::string & nm, const TypeCounter & rsrcs,
													 const TypeCounter & ntrlCpcty, const ConstructVector & bldngs,
													 const ConstructList & stlts)
	: faction(fctn), name(nm), resources(rsrcs), naturalCapacity(ntrlCpcty), sites(bldngs), satellites(stlts) {}

bool Space_Colony::World_Module::Galacitc::Planet::isSuperConstruct() const {
	//Take the first site to compare the others against.
	const Planetary::Construct &cmpr(sites.front());
	if (cmpr.check() && !cmpr.active) {
		//The first site is filled and active.
		for (auto iter(++sites.begin()), end(sites.end()); iter != end; ++iter)
			//Iterate all other sites.
			if (cmpr != *iter)
				//The two sites are not the same, this is not a SuperConstruct Planet.
				return false;
	} else
		//The first site is not filled or is not active, this is not a SuperConstruct Planet.
		return false;
	//This Planet hosts a SuperConstruct.
	return true;
}

std::pair<Planetary::Construct *const, bool> Space_Colony::World_Module::Galacitc::Planet::findConstruct(const Planetary::Construct & cnstrct) {
	if (cnstrct.check()) {
		//The passed Construct is loaded.
		for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
			//Iterate all the sites.
			if (cnstrct == *iter)
				//The Construct has been found, return it's pointer.
				return std::pair<Planetary::Construct *const, bool>(&*iter, true);
		for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
			//Iterate all the satallites.
			if (cnstrct == *iter)
				//The Construct has been found, return it's pointer.
				return std::pair<Planetary::Construct *const, bool>(&*iter, true);
	}
	//The Construct is not a part of this Planet, return nullptr.
	return std::pair<Planetary::Construct *const, bool>(nullptr, false);
}

std::pair<const Planetary::Construct *const, bool> Space_Colony::World_Module::Galacitc::Planet::findConstruct(const Planetary::Construct & cnstrct) const {
	if (cnstrct.check()) {
		//The passed Construct is loaded.
		for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
			//Iterate all the sites.
			if (cnstrct == *iter)
				//The Construct has been found, return it's pointer.
				return std::pair<const Planetary::Construct *const, bool>(&*iter, true);
		for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
			//Iterate all the satallites.
			if (cnstrct == *iter)
				//The Construct has been found, return it's pointer.
				return std::pair<const Planetary::Construct *const, bool>(&*iter, true);
	}
	//The Construct is not a part of this Planet, return nullptr.
	return std::pair<const Planetary::Construct *const, bool>(nullptr, false);
}

Planet::ConstructList Space_Colony::World_Module::Galacitc::Planet::getConstructsByTags(
	const Planetary::ConstructType::ConstructTags & tags, const Planetary::ConstructType::ConstructTags & exclude) const {
	ConstructList res;
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter) {
		bool load(true);
		for (auto tag_iter(tags.begin()), tag_end(tags.end()); tag_iter != tag_end; ++tag_iter)
			//Check all include tags.
			if ((*iter)->tags.count(*tag_iter) == 0) {
				//This tag is not included.
				load = false;
				goto LoadSite;
			}
		for (auto exclude_iter(tags.begin()), exclude_end(tags.end()); exclude_iter != exclude_end; ++exclude_iter)
			//Check all include tags.
			if ((*iter)->tags.count(*exclude_iter) != 0) {
				//This tag is not included.
				load = false;
				goto LoadSite;
			}
LoadSite:
		if (load)
			res.push_back(*iter);
	}
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter) {
		bool load(true);
		for (auto tag_iter(tags.begin()), tag_end(tags.end()); tag_iter != tag_end; ++tag_iter)
			//Check all include tags.
			if ((*iter)->tags.count(*tag_iter) == 0) {
				//This tag is not included.
				load = false;
				goto LoadSatallite;
			}
		for (auto exclude_iter(tags.begin()), exclude_end(tags.end()); exclude_iter != exclude_end; ++exclude_iter)
			//Check all include tags.
			if ((*iter)->tags.count(*exclude_iter) != 0) {
				//This tag is not included.
				load = false;
				goto LoadSatallite;
			}
LoadSatallite:
		if (load)
			res.push_back(*iter);
	}
	return res;
}

Planetary::ConstructType::ConstructTags Space_Colony::World_Module::Galacitc::Planet::getTags() const {
	Planetary::ConstructType::ConstructTags res;
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		//Iterate all sites.
		if (iter->typeID != 0 && iter->active)
			//The site is filled and active, add the tags to the result set.
			res.insert((*iter)->tags.begin(), (*iter)->tags.end());
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Iterate all satallites.
		if (iter->active)
			//The satallite is active, add the tags to the result set.
			res.insert((*iter)->tags.begin(), (*iter)->tags.end());
	return res;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planet::getResourceCapacity() const {
	//Get the natural resource capacity of this Planet.
	TypeCounter res(naturalCapacity);
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		//Iterate all sites.
		if (iter->typeID != 0)
			//The site is filled, add it's capacity to the result.
			res += (*iter)->getResourceCapacity();
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Iterate and accumulate the capacity of all the satallites to the result.
		res += (*iter)->getResourceCapacity();
	return res;
}

size_t Space_Colony::World_Module::Galacitc::Planet::getResourceCapacity(const __int32 rsrc) const {
	//Get the natural resource capacity of this Planet for the type.
	size_t res(naturalCapacity.getCounter(rsrc));
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		//Iterate all sites.
		if (iter->typeID != 0)
			//The site is filled, add it's capacity to the result for the type.
			res += (*iter)->getResourceCapacity().getCounter(rsrc);
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		//Iterate and accumulate the capacity of all the satallites to the
		//result for the type.
		res += (*iter)->getResourceCapacity().getCounter(rsrc);
	return res;
}

const TypeCounter & Space_Colony::World_Module::Galacitc::Planet::getResources() const {
	return resources;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planet::setResources(const TypeCounter & rsrcs) {
	if (!rsrcs.isPos())
		throw std::exception("The new resources have negative values.");
	else if (rsrcs > getResourceCapacity())
		throw std::exception("The new resources exceed the capacity.");
	TypeCounter res(resources);
	resources = rsrcs;
	return res;
}

size_t Space_Colony::World_Module::Galacitc::Planet::setResources(const __int32 rsrcs, const size_t val) {
	if (rsrcs > getResourceCapacity(rsrcs))
		throw std::exception("The new resources exceed the capacity.");
	size_t res(resources.getCounter(rsrcs));
	resources.setCounter(rsrcs, val);
	return res;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planet::incResources(TypeCounter rsrcs) {
	return setResources(rsrcs += resources);
}

size_t Space_Colony::World_Module::Galacitc::Planet::incResources(const __int32 rsrcs, const size_t val) {
	return setResources(rsrcs, resources.getCounter(rsrcs) + val);
}

const Planet::ConstructVector & Space_Colony::World_Module::Galacitc::Planet::getSites() const {
	return sites;
}

bool Space_Colony::World_Module::Galacitc::Planet::isFilled(const size_t index) const {
	//The site is filled.
	return sites[index].typeID != 0;
}

Planetary::Construct & Space_Colony::World_Module::Galacitc::Planet::getSite(const size_t index) {
	if (!isFilled(index))
		throw std::exception("The site is empty.");
	return sites[index];
}

const Planetary::Construct & Space_Colony::World_Module::Galacitc::Planet::getSite(const size_t index) const {
	if (!isFilled(index))
		throw std::exception("The site is empty.");
	return sites[index];
}

const Planet::ConstructList & Space_Colony::World_Module::Galacitc::Planet::getSatellites() const {
	return satellites;
}

Planet::ConstructList & Space_Colony::World_Module::Galacitc::Planet::getSatellites() {
	return satellites;
}

Planet & Space_Colony::World_Module::Galacitc::Planet::operator=(const Planet & right) {
	faction = right.faction;
	resources = right.resources;
	naturalCapacity = right.naturalCapacity;
	sites = right.sites;
	satellites = right.satellites;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::Planet::operator==(const Planet & right) const {
	return (this == &right)
		|| (faction == right.faction
			&& resources == right.resources
			&& naturalCapacity == right.naturalCapacity
			&& sites == right.sites
			&& satellites == right.satellites);
}

bool Space_Colony::World_Module::Galacitc::Planet::operator!=(const Planet & right) const {
	return !operator==(right);
}
