#include "Galactic\Solar\Space Craft\FloatilaTemplate.h"

Space_Colony::Galactic::Solar::SpaceCraft::FloatilaTemplate::FloatilaTemplate() {}

Space_Colony::Galactic::Solar::SpaceCraft::FloatilaTemplate::FloatilaTemplate(unsigned __int32 * const cft) {
	FILL_ARRAY(craft, cft, CraftTypes_max, i, unsigned __int32 i(0))
}

const unsigned __int32 * Space_Colony::Galactic::Solar::SpaceCraft::FloatilaTemplate::getCraft() {
	return craft;
}
