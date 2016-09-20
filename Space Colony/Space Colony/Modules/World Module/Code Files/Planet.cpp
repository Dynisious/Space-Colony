#include "..\Headers\Star System\Planet.h"

using namespace World_Module::Star_System;

Planet::Planet()
	: Planet(0, 0, BoundedResourceMap(0), -1) {}

Planet::Planet(const Planet & orig)
	: Planet(orig.sites, orig.satallites, orig.resourceDeposits, orig.faction) {}

Planet::Planet(const __int32 sts, const __int32 stlts, const BoundedResourceMap & rsrceDpsts, Space_Colony::faction_t fctn)
	: Planet(SiteVector(sts), ConstructVector(stlts), rsrceDpsts, fctn) {}

Planet::Planet(const SiteVector& sts, const ConstructVector& stlts, const BoundedResourceMap& rsrceDpsts, Space_Colony::faction_t fctn)
	: sites(sts), satallites(stlts), resourceDeposits(rsrceDpsts), faction(fctn) {}

void Planet::performTick() {
	unsigned __int32 i;
	bool error = false;
	BoundedResource rsrc;
	ResourceMap::const_iterator Resource_iter, Resource_end;
	for (i = 0; i < sites.size(); i++)
		if (sites[i]._state == ConstructionSite::state_city) {
			for (Resource_iter = sites[i]._site.city._resourceChange.begin(),
				 Resource_end = sites[i]._site.city._resourceChange.end();
				 Resource_iter != Resource_end; Resource_iter++) {
				rsrc = resourceDeposits[Resource_iter->first].safeAddition(Resource_iter->second, error);
				if (error)
					throw std::exception("The resource bounds were exceeded.");
				else
					resourceDeposits[Resource_iter->first] = rsrc;
			}
		} else if (sites[i]._state == ConstructionSite::state_city)
			for (Resource_iter = sites[i]._site.city._resourceChange.begin(),
				 Resource_end = sites[i]._site.city._resourceChange.end();
				 Resource_iter != Resource_end; Resource_iter++) {
				rsrc = resourceDeposits[Resource_iter->first].safeAddition(Resource_iter->second, error);
				if (error)
					throw std::exception("The resource bounds were exceeded.");
				else
					resourceDeposits[Resource_iter->first] = rsrc;
			}

		for (i = 0; i < satallites.size(); i++)
			for (Resource_iter = satallites[i]._resourceChange.begin(),
				 Resource_end = satallites[i]._resourceChange.end();
				 Resource_iter != Resource_end; Resource_iter++) {
				rsrc = resourceDeposits[Resource_iter->first].safeAddition(Resource_iter->second, error);
				if (error)
					throw std::exception("The resource bounds were exceeded.");
				else
					resourceDeposits[Resource_iter->first] = rsrc;
			}
}

Planet & Planet::operator=(const Planet & right) {
	sites = right.sites;
	satallites = right.satallites;
	resourceDeposits = right.resourceDeposits;
	faction = right.faction;
	return *this;
}

bool Planet::operator==(const Planet & right) const {
	if (this == &right)
		return true;
	return sites == right.sites
		&& satallites == right.satallites
		&& resourceDeposits == right.resourceDeposits
		&& faction == right.faction;
}

bool Planet::operator!=(const Planet & right) const {
	if (this != &right)
		return true;
	return sites != right.sites
		|| satallites != right.satallites
		|| resourceDeposits != right.resourceDeposits
		|| faction != right.faction;
}
