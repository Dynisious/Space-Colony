#include "..\Headers\Ship Types\ShipTemplate.h"

Combat_Module::Ship_Types::ShipTemplate::ShipTemplate()
	: ShipTemplate(-1, ShipStats()) {}

Combat_Module::Ship_Types::ShipTemplate::ShipTemplate(const ShipTemplate & orig)
	: ShipTemplate(orig.id, orig) {}

Combat_Module::Ship_Types::ShipTemplate::ShipTemplate(ShipTemplateID d) {
	ShipTemplate_getTemplate(id, *this);
}

Combat_Module::Ship_Types::ShipTemplate::ShipTemplate(ShipTemplateID d, const ShipStats & stats)
	: ShipStats(stats), id(d) {}

Combat_Module::Ship_Types::ShipTemplate::ShipTemplateID Combat_Module::Ship_Types::ShipTemplate::get_id() const {
	return id;
}

Combat_Module::Ship_Types::ShipTemplate & Combat_Module::Ship_Types::ShipTemplate::operator=(const ShipTemplate & right) {
	id = right.id;
	ShipStats::operator=(right);
	return *this;
}

bool Combat_Module::Ship_Types::ShipTemplate::operator==(const ShipTemplate & right) const {
	return id == right.id
		&& ShipStats::operator==(right);
}

bool Combat_Module::Ship_Types::ShipTemplate::operator!=(const ShipTemplate & right) const {
	return !operator==(right);
}

Combat_Module::Ship_Types::ShipTemplate::operator ShipStats&() {
	return *this;
}

Combat_Module::Ship_Types::ShipTemplate::operator const ShipStats&() const {
	return *this;
}
