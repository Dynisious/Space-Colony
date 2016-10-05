#include "..\Headers\Ship Types\ShipTypeCollection.h"

Combat_Module::Ship_Types::ShipTypeCollection::ShipTypeCollection()
	: ShipTypeCollection(TemplateMap()) {}

Combat_Module::Ship_Types::ShipTypeCollection::ShipTypeCollection(const ShipTypeCollection & orig)
	: ShipTypeCollection(orig.templates) {}

Combat_Module::Ship_Types::ShipTypeCollection::ShipTypeCollection(const TemplateMap & tmplts)
	: templates(tmplts) {}

Combat_Module::Ship_Types::ShipTypeCollection::const_iterator Combat_Module::Ship_Types::ShipTypeCollection::begin() const {
	return templates.begin();
}

Combat_Module::Ship_Types::ShipTypeCollection::const_iterator Combat_Module::Ship_Types::ShipTypeCollection::end() const {
	return templates.end();
}

Combat_Module::Ship_Types::ShipTypeCollection::ModifyType Combat_Module::Ship_Types::ShipTypeCollection::addTemplate(const ShipTemplate & tmp) {
	return templates.insert(TemplateMap::value_type(tmp._ID, tmp));
}

Combat_Module::Ship_Types::ShipTypeCollection::ModifyType Combat_Module::Ship_Types::ShipTypeCollection::getTemplate(ShipTemplate::ShipTemplateID id) const {
	ModifyType res;
	if (templates.count(id) == 0)
		//The id is not mapped.
		res.second = false;
	else {
		//The id is mapped
		res.first = templates.find(id);
		res.second = true;
	}
	return res;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::removeTemplate(ShipTemplate::ShipTemplateID id) {
	return templates.erase(id) != 0;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::contains(const ShipTemplate::ShipTemplateID & id) const {
	return templates.count(id) != 0;
}

__int32 Combat_Module::Ship_Types::ShipTypeCollection::size() const {
	return templates.size();
}

Combat_Module::Ship_Types::ShipTypeCollection & Combat_Module::Ship_Types::ShipTypeCollection::operator=(const ShipTypeCollection & right) {
	templates = right.templates;
	return *this;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::operator==(const ShipTypeCollection & right) const {
	return (this == &right)
		|| (templates == right.templates);
}

bool Combat_Module::Ship_Types::ShipTypeCollection::operator!=(const ShipTypeCollection & right) const {
	return !operator==(right);
}

Combat_Module::Ship_Types::ShipTypeCollection::ModifyType Combat_Module::Ship_Types::ShipTypeCollection::operator[](ShipTemplate::ShipTemplateID id) const {
	return getTemplate(id);
}
