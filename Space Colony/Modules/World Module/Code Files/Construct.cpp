#include "World Module\Headers\Galactic\Planetary\Construct.h"

using namespace Space_Colony::World_Module::Galacitc::Planetary;

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct()
	: Construct(0, false) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(const Construct & orig)
	: Construct(orig.TypeID, orig.active) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(ConstructType_ID TpID, bool actv)
	: TypeID(TpID), active(actv) {}

const ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::getType() const {
	return ConstructType_get(TypeID);
}

Construct & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator=(const Construct & right) {
	TypeID = right.TypeID;
	active = right.active;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator==(const Construct & right) const {
	return (this == &right)
		|| (TypeID == right.TypeID
			&& active == right.active);
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}
