#include "..\Headers\CombatFleet.h"

Combat_Module::CombatFleet::CombatFleet()
	: CombatFleet(-1, Space_Colony::TypeCounter()) {}

Combat_Module::CombatFleet::CombatFleet(const CombatFleet & orig)
	: CombatFleet(orig.faction, orig) {}

Combat_Module::CombatFleet::CombatFleet(Space_Colony::faction_t fctn, const TypeCounter & shpCntr)
	: TypeCounter(shpCntr), faction(fctn) {}

Combat_Module::CombatFleet & Combat_Module::CombatFleet::operator=(const CombatFleet & right) {
	faction = right.faction;
	TypeCounter::operator=(right);
	return *this;
}

bool Combat_Module::CombatFleet::operator==(const CombatFleet & right) const {
	if (this == &right)
		return true;
	if (faction == right.faction && TypeCounter::operator==(right))
		return true;
	return false;
}

bool Combat_Module::CombatFleet::operator!=(const CombatFleet & right) const {
	return !operator==(right);
}
