#include "..\Headers\Fleet.h"

Space_Colony::Fleet::Fleet()
	: Fleet(-1, Space_Colony::TypeCounter()) {}

Space_Colony::Fleet::Fleet(const Fleet & orig)
	: Fleet(orig.faction, orig) {}

Space_Colony::Fleet::Fleet(Space_Colony::faction_t fctn, const TypeCounter & shpCntr)
	: TypeCounter(shpCntr), faction(fctn) {}

Space_Colony::Fleet & Space_Colony::Fleet::operator=(const Fleet & right) {
	faction = right.faction;
	TypeCounter::operator=(right);
	return *this;
}

bool Space_Colony::Fleet::operator==(const Fleet & right) const {
	if (this == &right)
		return true;
	if (faction == right.faction && TypeCounter::operator==(right))
		return true;
	return false;
}

bool Space_Colony::Fleet::operator!=(const Fleet & right) const {
	return !operator==(right);
}
