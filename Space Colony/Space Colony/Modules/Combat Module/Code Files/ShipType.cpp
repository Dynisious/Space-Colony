#include "..\Headers\Ship Types\ShipType.h"

Combat_Module::Ship_Types::ShipType::ShipType()
	: ShipType("", ShipType_Stats(), -1) {}

Combat_Module::Ship_Types::ShipType::ShipType(const ShipType & orig)
	: ShipType(orig, orig.ID) {}

Combat_Module::Ship_Types::ShipType::ShipType(const ShipType & orig, const Space_Colony::Ships::Type_ID id)
	: stats(orig.stats), name(orig.name), ID(orig.ID) {}

Combat_Module::Ship_Types::ShipType::ShipType(const name_str & nm, const ShipType_Stats & sts, const Space_Colony::Ships::Type_ID id)
	: name(nm), stats(sts), ID(id) {}

Combat_Module::Ship_Types::ShipType_Stats const & Combat_Module::Ship_Types::ShipType::get_stats() {
	return stats;
}

const Combat_Module::Ship_Types::ShipType_Stats & Combat_Module::Ship_Types::ShipType::get_stats() const {
	return stats;
}

const Combat_Module::Ship_Types::ShipType::name_str & Combat_Module::Ship_Types::ShipType::get_name() const {
	return name;
}

Space_Colony::Ships::Type_ID Combat_Module::Ship_Types::ShipType::get_ID() const {
	return ID;
}

bool Combat_Module::Ship_Types::ShipType::discrepency(const ShipType & type) {
	return valueEquals(type) != (type.ID == ID);
}

bool Combat_Module::Ship_Types::ShipType::valueEquals(const ShipType & type) {
	if (this == &type)
		return true;
	return name == type.name
		&& stats == type.stats;
}

Combat_Module::Ship_Types::ShipType & Combat_Module::Ship_Types::ShipType::operator=(const ShipType & orig) {
	name = orig.name;
	stats = orig.stats;
	ID = orig.ID;
	return *this;
}

bool Combat_Module::Ship_Types::ShipType::operator==(const ShipType & type) {
	if (this == &type)
		return true;
	return name == type.name
		&& stats == type.stats
		&& ID == type.ID;
}

bool Combat_Module::Ship_Types::ShipType::operator!=(const ShipType & type) {
	if (this != &type)
		return true;
	return name != type.name
		|| stats != type.stats
		|| ID == type.ID;
}
