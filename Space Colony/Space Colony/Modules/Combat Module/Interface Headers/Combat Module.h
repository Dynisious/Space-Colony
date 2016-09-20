#pragma once

#include "..\..\..\Headers\Space Colony.h"

/*
The namespace for all things within the Combat Module.*/
namespace Combat_Module {

	/*
	Loads the combat module.*/
	void loadCombatModule();

	namespace Ship_Types {

		/*
		The number of ShipTypes which are loaded in this Module.*/
		__int32 loadedShipTypes();

	}

}
