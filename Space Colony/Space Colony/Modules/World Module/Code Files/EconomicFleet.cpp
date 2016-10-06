#include "..\Headers\Galactic\Solar\EconomicFleet.h"

World_Module::Galactic::Solar::EconomicFleet::EconomicFleet()
	: EconomicFleet(TypeCounter(), TypeCounter()) {}

World_Module::Galactic::Solar::EconomicFleet::EconomicFleet(const EconomicFleet & orig)
	: EconomicFleet(orig.resources, orig.resourcesCapacity) {}

World_Module::Galactic::Solar::EconomicFleet::EconomicFleet(const Space_Colony::TypeCounter & rsrcs, const Space_Colony::TypeCounter & rsrcsCpcty)
	: resources(rsrcs), resourcesCapacity(rsrcsCpcty) {}

World_Module::Galactic::Solar::EconomicFleet & World_Module::Galactic::Solar::EconomicFleet::operator=(const EconomicFleet & right) {
	resources = right.resources;
	resourcesCapacity = right.resourcesCapacity;
	return *this;
}

bool World_Module::Galactic::Solar::EconomicFleet::operator==(const EconomicFleet & right) const {
	return (this == &right)
		|| (resources == right.resources
			&& resourcesCapacity == right.resourcesCapacity);
}

bool World_Module::Galactic::Solar::EconomicFleet::operator!=(const EconomicFleet & right) const {
	return !operator==(right);
}
