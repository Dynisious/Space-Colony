#include "..\Headers\Galactic\StarCluster.h"

World_Module::Galactic::StarCluster::StarCluster()
	: StarCluster(0) {}

World_Module::Galactic::StarCluster::StarCluster(const StarCluster & orig)
	: vector(orig) {}

World_Module::Galactic::StarCluster::StarCluster(const __int32 systms)
	: vector(systms) {}

World_Module::tagSet World_Module::Galactic::StarCluster::get_tags() const {
	tagSet res;
	for (__int32 i(0); i < size(); i++)
		res.insert(operator[](i)._tags.begin(), operator[](i)._tags.end());
	return res;
}

Space_Colony::faction_t World_Module::Galactic::StarCluster::get_faction() const {
	Space_Colony::faction_t res(operator[](0)._faction);
	for (__int32 i(1); i < size(); i++)
		if (operator[](i)._faction != res
			&& operator[](i)._faction != Space_Colony::Faction_Neutral)
			return Space_Colony::Faction_Contested;
	return res;
}
