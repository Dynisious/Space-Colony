#pragma once

#include "Combat Module.h"
#include "..\..\..\Headers\TypeCounter.h"

namespace Combat_Module {

	/*
	A CombatFleet is a TypeCounter of ShipTemplateIDs with a faction value.*/
	class CombatFleet : public Space_Colony::TypeCounter {
	public:
		CombatFleet();
		CombatFleet(const CombatFleet& orig);
		CombatFleet(Space_Colony::faction_t fctn, const TypeCounter& shpCntr);

		/*
		The faction_t value which this CombatFleet is aligned with.*/
		Space_Colony::faction_t faction;

		CombatFleet& operator=(const CombatFleet& right);
		bool operator==(const CombatFleet& right) const;
		bool operator!=(const CombatFleet& right) const;

	};

}
