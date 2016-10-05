#include "..\Headers\Space Colony.h"
#include "..\Modules\Combat Module\Headers\Combat Module.h"
#include "..\Modules\World Module\Headers\World Module.h"

__int32 main() {
	return 0;
}

__int32 Space_Colony::SpaceColony_load() {
	Combat_Module::CombatModule_load();
	World_Module::WorldModule_load();
	return 0;
}
