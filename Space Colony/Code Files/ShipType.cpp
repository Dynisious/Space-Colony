#include "ShipType.h"

using namespace Space_Colony;

Space_Colony::ShipType::WorldStats::WorldStats()
	: WorldStats(0, 0, 0, 0, 0, "Unamed ShipType") {}

Space_Colony::ShipType::WorldStats::WorldStats(const WorldStats & orig)
	: WorldStats(orig.resourceCost, orig.mass, orig.fuelCapacity,
				 orig.fuelEfficiency, orig.cargoCapacity, orig.name) {}

Space_Colony::ShipType::WorldStats::WorldStats(
	const TypeCounter & rsrcCst, const size_t ms, const size_t flCpcty,
	const double flEfcncy, const size_t crgCpcty, const std::string & nm)
	: resourceCost(rsrcCst), mass(ms), fuelCapacity(flCpcty),
	fuelEfficiency(flEfcncy), cargoCapacity(crgCpcty), name(nm) {}

ShipType::WorldStats & Space_Colony::ShipType::WorldStats::operator=(const WorldStats & right) {
	resourceCost = right.resourceCost;
	mass = right.mass;
	fuelCapacity = right.fuelCapacity;
	fuelEfficiency = right.fuelEfficiency;
	cargoCapacity = right.cargoCapacity;
	name = right.name;
	return *this;
}

bool Space_Colony::ShipType::WorldStats::operator==(const WorldStats & right) const {
	return resourceCost == right.resourceCost
		&& mass == right.mass
		&& fuelCapacity == right.fuelCapacity
		&& fuelEfficiency == right.fuelEfficiency
		&& cargoCapacity == right.cargoCapacity
		&& name == right.name;
}

bool Space_Colony::ShipType::WorldStats::operator!=(const WorldStats & right) const {
	return !operator==(right);
}

Space_Colony::ShipType::ShipType() {}

Space_Colony::ShipType::ShipType(const ShipType & orig)
	: ShipType(orig.combat, orig.world) {}

Space_Colony::ShipType::ShipType(const CombatStats & cmbt, const WorldStats & wrld)
	: combat(cmbt), world(wrld) {}

ShipType & Space_Colony::ShipType::operator=(const ShipType & right) {
	combat = right.combat;
	world = right.world;
	return *this;
}

bool Space_Colony::ShipType::operator==(const ShipType & right) const {
	return combat == right.combat
		&& world == right.world;
}

bool Space_Colony::ShipType::operator!=(const ShipType & right) const {
	return !operator==(right);
}
