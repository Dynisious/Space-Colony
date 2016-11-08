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

TypeCounter Space_Colony::World_Module::Galacitc::Planet::getResourceShift() const {
	TypeCounter res;
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		if (iter->TypeID != 0 && iter->active)
			res += iter->getType().resourceShift;
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		if (iter->active)
			res += iter->getType().resourceShift;
	return res;
}

__int32 Space_Colony::World_Module::Galacitc::Planet::getResourceShift(const __int32 rsrc) const {
	__int32 res(0);
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		if (iter->TypeID != 0 && iter->active)
			res += iter->getType().resourceShift.getCounter(rsrc);
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		if (iter->active)
			res += iter->getType().resourceShift.getCounter(rsrc);
	return res;
}

Planetary::ConstructType::ConstructTags Space_Colony::World_Module::Galacitc::Planet::getTags() const {
	Planetary::ConstructType::ConstructTags res;
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		if (iter->TypeID != 0 && iter->active)
			res.insert(iter->getType().tags.begin(), iter->getType().tags.end());
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		if (iter->active)
			res.insert(iter->getType().tags.begin(), iter->getType().tags.end());
	return res;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planet::getResourceCapacity() const {
	TypeCounter res(naturalCapacity);
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		if (iter->TypeID != 0)
			res += iter->getType().getResourceCapacity();
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		res += iter->getType().getResourceCapacity();
	return res;
}

size_t Space_Colony::World_Module::Galacitc::Planet::getResourceCapacity(const __int32 rsrc) const {
	size_t res(naturalCapacity.getCounter(rsrc));
	for (auto iter(sites.begin()), end(sites.end()); iter != end; ++iter)
		if (iter->TypeID != 0)
			res += iter->getType().getResourceCapacity().getCounter(rsrc);
	for (auto iter(satellites.begin()), end(satellites.end()); iter != end; ++iter)
		res += iter->getType().getResourceCapacity().getCounter(rsrc);
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

const Planet::ConstructVector & Space_Colony::World_Module::Galacitc::Planet::getSites() const {
	return sites;
}

bool Space_Colony::World_Module::Galacitc::Planet::isFilled(const size_t index) const {
	return sites[index].TypeID != 0;
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
