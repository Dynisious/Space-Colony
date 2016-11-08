#include "ShipType.h"

using namespace Space_Colony;

Space_Colony::ShipType::ShipType() {}

Space_Colony::ShipType::ShipType(const ShipType & orig)
	: combat(orig.combat), world(orig.world) {}

ShipType Space_Colony::ShipType::operator=(const ShipType & right) {
	combat = right.combat;
	world = right.world;
	return *this;
}

bool Space_Colony::ShipType::operator==(const ShipType & right) const {
	return (this == &right)
		|| (combat == right.combat
			&& world == right.world);
}

bool Space_Colony::ShipType::operator!=(const ShipType & right) const {
	return !operator==(right);
}

Space_Colony::ShipType::CombatStats::CombatStats() {}

Space_Colony::ShipType::CombatStats::CombatStats(const CombatStats & orig)
	: glance(orig.glance), evade(orig.evade), size(orig.size), target_min(orig.target_min),
	target_max(orig.target_max), attacks(orig.attacks), accuracy(orig.accuracy) {}

Space_Colony::ShipType::CombatStats & Space_Colony::ShipType::CombatStats::operator=(const CombatStats & right) {
	glance = right.glance;
	evade = right.evade;
	size = right.size;
	target_min = right.target_min;
	target_max = right.target_max;
	attacks = right.attacks;
	accuracy = right.accuracy;
	return *this;
}

bool Space_Colony::ShipType::CombatStats::operator==(const CombatStats & right) const {
	return (this == &right)
		|| (glance == right.glance
			&& evade == right.evade
			&& size == right.size
			&& target_min == right.target_min
			&& target_max == right.target_max
			&& attacks == right.attacks
			&& accuracy == right.accuracy);
}

bool Space_Colony::ShipType::CombatStats::operator!=(const CombatStats & right) const {
	return !operator==(right);
}

Space_Colony::ShipType::WorldStats::WorldStats() {}

Space_Colony::ShipType::WorldStats::WorldStats(const WorldStats & orig)
	: name(orig.name), cost(orig.cost), mass(orig.mass), fuel_capacity(orig.fuel_capacity),
	fuel_efficiency(orig.fuel_efficiency), cargo_capacity(orig.cargo_capacity), rollTags(orig.rollTags) {}

Space_Colony::ShipType::WorldStats & Space_Colony::ShipType::WorldStats::operator=(const WorldStats & right) {
	name = right.name;
	cost = right.cost;
	mass = right.mass;
	fuel_capacity = right.fuel_capacity;
	fuel_efficiency = right.fuel_efficiency;
	cargo_capacity = right.cargo_capacity;
	rollTags = right.rollTags;
	return *this;
}

bool Space_Colony::ShipType::WorldStats::operator==(const WorldStats & right) const {
	return (this == &right)
		|| (name == right.name
			&& cost == right.cost
			&& mass == right.mass
			&& fuel_capacity == right.fuel_capacity
			&& fuel_efficiency == right.fuel_efficiency
			&& cargo_capacity == right.cargo_capacity
			&& rollTags == right.rollTags);
}

bool Space_Colony::ShipType::WorldStats::operator!=(const WorldStats & right) const {
	return !operator==(right);
}

std::unordered_set<ShipType_ID> ShipType_All_IDs;

bool Space_Colony::ShipType_isLoaded(ShipType_ID id) {
	return ShipType_All_IDs.count(id) != 0;
}

const ShipType & Space_Colony::ShipType_get(ShipType_ID id) {
	if (!ShipType_isLoaded(id))
		throw std::runtime_error("The passed ID is not a loaded ID.");
	return *( ShipType_Pointer ) id;
}

ShipType_ID Space_Colony::ShipType_load(const ShipType & type) {
	for (auto iter(ShipType_All_IDs.begin()), end(ShipType_All_IDs.end()); iter != end; ++iter)
		if (type == *( ShipType_Pointer ) *iter)
			//This type is already loaded.
			return ( ShipType_ID ) *iter;
	return *ShipType_All_IDs.insert((ShipType_ID) new ShipType(type)).first;
}

bool Space_Colony::ShipType_unload(ShipType_ID id) {
	if (ShipType_isLoaded(id)) {
		ShipType_All_IDs.erase(id);
		delete ( ShipType_Pointer ) id;
		return true;
	} else {
		return false;
	}
}
