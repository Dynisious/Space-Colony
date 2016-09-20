#include "..\Interface Headers\Combat Module.h"
#include "..\Headers\Ship Types\ShipType Collection.h"

namespace Combat_Module {

	/*
	The Module which handles conflicts within the Space Colony game.*/
	struct CombatModule {
	public:
		/*
		A collection of all ShipTypes loaded into the game.*/
		Ship_Types::ShipTypeCollection allShipTypes;

	};

}

Combat_Module::CombatModule instance;

__int32 Combat_Module::Ship_Types::loadedShipTypes() {
	return instance.allShipTypes.loadedTypes();
}

bool Combat_Module::Ship_Types::getShipType_ByID(const Space_Colony::Ships::Type_ID ID, ShipType & type) {
	return instance.allShipTypes.getFromID(ID, type);
}

void Combat_Module::Ship_Types::iterateShipTypes_ByID(ShipType_IdMap::const_iterator & start, ShipType_IdMap::const_iterator & end) {
	instance.allShipTypes.iterateByID(start, end);
}
