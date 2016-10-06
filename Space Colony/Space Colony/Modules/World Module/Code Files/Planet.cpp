#include "..\Headers\Galactic\Solar\Planet.h"
#include <stdexcept>

World_Module::Galactic::Solar::Planet::Planet()
	: Planet(Space_Colony::TypeCounter(), Space_Colony::TypeCounter(), Space_Colony::Faction_Neutral, 0) {}

World_Module::Galactic::Solar::Planet::Planet(const Planet & orig)
	: Planet(orig.resources, orig.naturalStorage, orig.faction, orig.sitesCount, orig.sites) {}

World_Module::Galactic::Solar::Planet::Planet(Space_Colony::TypeCounter rsrcs, Space_Colony::TypeCounter ntrlStrg, Space_Colony::faction_t fctn, __int32 stsCnt)
	: Planet(rsrcs, ntrlStrg, fctn, stsCnt, ConstructMap(stsCnt)) {}

World_Module::Galactic::Solar::Planet::Planet(Space_Colony::TypeCounter rsrcs, Space_Colony::TypeCounter ntrlStrg, Space_Colony::faction_t fctn, __int32 stsCnt, ConstructMap sts)
	: resources(rsrcs), naturalStorage(ntrlStrg), faction(fctn), sitesCount(stsCnt), sites(stsCnt) {}

World_Module::Galactic::Solar::Planet::const_iterator World_Module::Galactic::Solar::Planet::begin_ground() const {
	return sites.begin();
}

World_Module::Galactic::Solar::Planet::const_iterator World_Module::Galactic::Solar::Planet::end_ground() const {
	return sites.end();
}

World_Module::Galactic::Solar::Planet::const_iterator World_Module::Galactic::Solar::Planet::begin_orbital() const {
	return orbital.begin();
}

World_Module::Galactic::Solar::Planet::const_iterator World_Module::Galactic::Solar::Planet::end_orbital() const {
	return orbital.end();
}

__int32 World_Module::Galactic::Solar::Planet::fillSite(const Construct & cnstrct) {
	if (emptySites() == 0 && cnstrct.tags.count(WorldTags::Ground_Construct) != 0)
		//There must be an empty site and it must be a ground construct being added.
		return -1;
	__int32 index(0);
	for (; sites.count(index) != 0; index++);
	//Find an index which is not in use.
	sites[index] = cnstrct;
	return index;
}

__int32 World_Module::Galactic::Solar::Planet::addOrbital(const Construct & cnstrct) {
	if (cnstrct.tags.count(WorldTags::Orbital_Construct) != 0)
		//It must be a ground construct being added.
		return -1;
	__int32 index(0);
	for (; orbital.count(index) != 0; index++);
	//Find an index which is not in use.
	orbital[index] = cnstrct;
	return index;
}

__int32 World_Module::Galactic::Solar::Planet::emptySites() const {
	return sitesCount - sites.size();
}

bool World_Module::Galactic::Solar::Planet::demolishConstruct(const __int32 index, Construct * const cnstrct) {
	if (exists(index))
		if (cnstrct != nullptr)
			//There is a return address for the construct.
			*cnstrct = sites[index];
	return sites.erase(index) != 0;
}

bool World_Module::Galactic::Solar::Planet::exists(const __int32 index) const {
	return sites.count(index) == 0;
}

const World_Module::Galactic::Solar::Planet::ConstructMap & World_Module::Galactic::Solar::Planet::get_sites() const {
	return sites;
}

const World_Module::Galactic::Solar::Planet::ConstructMap & World_Module::Galactic::Solar::Planet::get_orbital() const {
	return orbital;
}

World_Module::tagSet World_Module::Galactic::Solar::Planet::get_tags() const {
	tagSet res;
	const_iterator iter, end;
	for (iter = begin_ground(), end = end_ground(); iter != end; iter++)
		//Get ground tags.
		res.insert(iter->second.tags.begin(), iter->second.tags.end());
	for (iter = begin_orbital(), end = end_orbital(); iter != end; iter++)
		//Get orbital tags.
		res.insert(iter->second.tags.begin(), iter->second.tags.end());
	return res;
}

Space_Colony::TypeCounter World_Module::Galactic::Solar::Planet::get_totalStorage() const {
	Space_Colony::TypeCounter res(naturalStorage);
	const_iterator iter, end;
	for (iter = begin_ground(), end = end_ground(); iter != end; iter++)
		//Add the storage of each ground Construct onto the natural storage of
		//the Planet.
		res += iter->second.storage;
	for (iter = begin_orbital(), end = end_orbital(); iter != end; iter++)
		//Add the storage of each orbital Construct onto the cummulative storage.
		res += iter->second.storage;
	return res;
}

__int32 World_Module::Galactic::Solar::Planet::get_sitesCount() const {
	return sitesCount;
}

void World_Module::Galactic::Solar::Planet::set_sitesCount(const __int32 vl) {
	if (vl < sites.size())
		throw std::out_of_range("Trying to set the number of possible sites to less than the number of filled sites.");
	sitesCount = vl;
}

World_Module::Galactic::Solar::Planet & World_Module::Galactic::Solar::Planet::operator=(const Planet & right) {
	resources = right.resources;
	naturalStorage = right.naturalStorage;
	faction = right.faction;
	sites = right.sites;
	sitesCount = right.sitesCount;
	return *this;
}

bool World_Module::Galactic::Solar::Planet::operator==(const Planet & right) const {
	return (this == &right)
		|| (resources == right.resources
			&& naturalStorage == right.naturalStorage
			&& faction == right.faction
			&& sites == right.sites
			&& sitesCount == right.sitesCount);
}

bool World_Module::Galactic::Solar::Planet::operator!=(const Planet & right) const {
	return !operator==(right);
}
