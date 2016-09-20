#include "..\Headers\StarCluster.h"

World_Module::StarCluster::StarCluster()
	: StarCluster(Star_System::SolarVector(0)) {}

World_Module::StarCluster::StarCluster(const StarCluster & orig)
	: StarCluster(orig.systems) {}

World_Module::StarCluster::StarCluster(const Star_System::SolarVector systms)
	: StarCluster(systms) {}

World_Module::Star_System::SolarVector & World_Module::StarCluster::get_systems() {
	return systems;
}

const World_Module::Star_System::SolarVector & World_Module::StarCluster::get_systems() const {
	return systems;
}

Space_Colony::faction_t World_Module::StarCluster::get_faction() const {
	std::unordered_map<Space_Colony::faction_t, __int32> factionCount;
	unsigned __int32 i;
	for (i = 0; i < systems.size(); i++)
		factionCount[systems[i].faction] = 0;
	Space_Colony::faction_t res(systems[0].faction);
	for (i = 1; i < systems.size(); i++)
		if (factionCount[systems[i].faction] > factionCount[res])
			res = systems[i].faction;
	return res;
}

World_Module::BoundedResourceMap World_Module::StarCluster::get_resources() const {
	BoundedResourceMap res;
	World_Module::BoundedResourceMap::const_iterator Resource_iter, Resource_end;
	for (Star_System::SolarVector::const_iterator Solar_iter(systems.begin()), Solar_end(systems.end());
		 Solar_iter != Solar_end; Solar_iter++)
		for (Resource_iter = Solar_iter->_resources.begin(), Resource_end = Solar_end->_resources.end();
			 Resource_iter != Resource_end; Resource_iter++)
			res[Resource_iter->first] += Resource_iter->second;
	return res;
}
