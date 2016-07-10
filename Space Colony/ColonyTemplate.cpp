#include "Galactic\Solar\Structures\ColonyTemplate.h"

unsigned __int32
Space_Colony::Galactic::Solar::Structures::ColonyTemplate::orbDefCosts[Space_Colony::ResourceType_max],
Space_Colony::Galactic::Solar::Structures::ColonyTemplate::harvestCosts[Space_Colony::ResourceType_max],
Space_Colony::Galactic::Solar::Structures::ColonyTemplate::civCosts[Space_Colony::ResourceType_max];

Space_Colony::Galactic::Solar::Structures::ColonyTemplate::ColonyTemplate()
	: ColonyTemplate(0, 0, 0) {}

Space_Colony::Galactic::Solar::Structures::ColonyTemplate::ColonyTemplate(const ColonyTemplate & orig)
	: orbitalDefences(orig.orbitalDefences), harvesters(orig.harvesters), civilisations(orig.civilisations) {
	for (unsigned __int32 i(0); i < ResourceType_max; i++)
		costs[i] = orig.costs[i];
}

Space_Colony::Galactic::Solar::Structures::ColonyTemplate::ColonyTemplate(const unsigned __int32 orbDef, const unsigned __int32 hrvsts, const unsigned __int32 civs)
	: orbitalDefences(orbDef), harvesters(hrvsts), civilisations(civs) {
	for (unsigned __int32 i(0); i < ResourceType_max; i++)
		costs[i] = (orbDefCosts[i] * orbitalDefences) + (harvestCosts[i] * harvesters) + (civCosts[i] * civilisations);
}

const unsigned __int32 * Space_Colony::Galactic::Solar::Structures::ColonyTemplate::getCosts() {
	return costs;
}
