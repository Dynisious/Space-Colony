#include "World Module\Headers\Galactic\Planetary\Construct.h"

using namespace Space_Colony::World_Module::Galacitc::Planetary;

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct()
	: Construct(0, false) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(const Construct & orig)
	: Construct(orig.typeID, orig.active) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(ConstructType_ID TpID, bool actv)
	: typeID(TpID), active(actv) {}

const ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::getType() const {
	return ConstructType_get(typeID);
}

Construct & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator=(const Construct & right) {
	typeID = right.typeID;
	active = right.active;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator==(const Construct & right) const {
	return (this == &right)
		|| (typeID == right.typeID
			&& active == right.active);
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}
