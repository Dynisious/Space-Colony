#include "..\Headers\Combat Module.h"
#include "..\Headers\Ship Types\ShipTypeCollection.h"
#include "..\Headers\ConflictInstance.h"
#include <unordered_map>

namespace Combat_Module {

	class CombatModule {
	public:
		Ship_Types::ShipTypeCollection templates;
		std::unordered_map<ConflictInstance::ConflictID, ConflictInstance> engagments;

	};

}

Combat_Module::CombatModule instance;

__int32 Combat_Module::CombatModule_load() {
	return 0;
}

bool Combat_Module::Ship_Types::ShipTemplate_getTemplate(ShipTemplate::ShipTemplateID ID, ShipTemplate & res) {
	if (instance.templates.contains(ID)) {
		res = instance.templates.getTemplate(ID).first->second;
		return true;
	}
	return false;
}