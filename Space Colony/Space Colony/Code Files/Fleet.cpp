#include "..\Shared Headers\Ships\Fleet.h"

Space_Colony::Ships::Fleet::Fleet() {}

Space_Colony::Ships::Fleet::Fleet(const Fleet & orig)
	: Fleet(orig.faction, orig.ships) {}

Space_Colony::Ships::Fleet::Fleet(const Space_Colony::faction_t fac, const ShipTypeCount & shps)
	: faction(fac), ships(shps) {}

Space_Colony::Ships::ShipTypeCount & Space_Colony::Ships::Fleet::get_Ships() {
	return ships;
}

const Space_Colony::Ships::ShipTypeCount & Space_Colony::Ships::Fleet::get_Ships() const {
	return ships;
}
