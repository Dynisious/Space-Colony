#include "Galactic\Solar\Space Craft\Floatila.h"

unsigned __int32 Space_Colony::Galactic::Solar::SpaceCraft::Floatila::FuelCowCapacity = 0;

Space_Colony::Galactic::Solar::SpaceCraft::Floatila::Floatila()
	: hostileTerrertory(false) {}

Space_Colony::Galactic::Solar::SpaceCraft::Floatila::Floatila(unsigned __int32 * const cft)
	: hostileTerrertory(false), fuel(0), fuel_max(FuelCowCapacity * cft[FuelCow]) {
	FILL_ARRAY(craft, cft, CraftTypes_max, i, unsigned __int32 i(0))
}

Space_Colony::Galactic::Solar::SpaceCraft::Floatila::Floatila(const FloatilaTemplate & orig) {
	operator=(orig);
}

const unsigned __int32 * Space_Colony::Galactic::Solar::SpaceCraft::Floatila::getCraft() {
	return craft;
}

void Space_Colony::Galactic::Solar::SpaceCraft::Floatila::incrementCraft(CraftTypes type, __int32 incr) {
	if (type == FuelCow)
		fuelCowIncrement(incr);
	else
		stdIncrement(type, incr);
}

bool Space_Colony::Galactic::Solar::SpaceCraft::Floatila::canMove() {
	if (fuel)
		return true;
	else
		return !(craft[Carrier] || craft[Dreadnought]);
}

Space_Colony::Galactic::Solar::SpaceCraft::Floatila & Space_Colony::Galactic::Solar::SpaceCraft::Floatila::operator=(FloatilaTemplate & const orig) {
	FILL_ARRAY(craft, orig.craft_prop, CraftTypes_max, i, unsigned __int32 i(0))
		return (Floatila&) *this;
}

void Space_Colony::Galactic::Solar::SpaceCraft::Floatila::stdIncrement(CraftTypes type, __int32 incr) {
	craft[type] += incr;
}

void Space_Colony::Galactic::Solar::SpaceCraft::Floatila::fuelCowIncrement(__int32 incr) {
	fuel_max += FuelCowCapacity * incr;
	if (incr < 0)
		fuel = fuel * (craft[FuelCow] + incr) / craft[FuelCow];
	craft[FuelCow]--;
}
