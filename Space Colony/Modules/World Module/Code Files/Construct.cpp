#include "World Module\Headers\Galactic\Planetary\Construct.h"

using namespace Space_Colony::World_Module::Galactic::Planetary;

Space_Colony::World_Module::Galactic::Planetary::Construct::Construct()
	: Construct(-1, false) {}

Space_Colony::World_Module::Galactic::Planetary::Construct::Construct(const Construct & orig)
	: Construct(orig.typeId, orig.active) {}

Space_Colony::World_Module::Galactic::Planetary::Construct::Construct(const size_t typId, const bool actv)
	: typeId(typId), active(actv) {}

Construct & Space_Colony::World_Module::Galactic::Planetary::Construct::operator=(const Construct & right) {
	typeId = right.typeId;
	active = right.active;
	return *this;
}

bool Space_Colony::World_Module::Galactic::Planetary::Construct::operator==(const Construct & right) const {
	return typeId == right.typeId
		&& active == right.active;
}

bool Space_Colony::World_Module::Galactic::Planetary::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}
