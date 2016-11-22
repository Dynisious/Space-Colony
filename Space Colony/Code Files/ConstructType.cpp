#include "ConstructType.h"

using namespace Space_Colony;

Space_Colony::ConstructType::ConstructType()
	: ConstructType(0, 0, 0, 0, "Unnamed ConstructType", {}) {}

Space_Colony::ConstructType::ConstructType(const ConstructType & orig)
	: ConstructType(orig.resourceShift, orig.resourceCapacity,
					orig.constructCost, orig.returnedResources, orig.name,
					orig.combat) {}

Space_Colony::ConstructType::ConstructType(
	const TypeCounter & rsrcShft, const TypeCounter & rsrcCpcty,
	const TypeCounter & cntrctCst, const TypeCounter & rtrndRsrcs,
	const std::string & nm, const CombatStats &cmbt)
	: resourceShift(rsrcShft), resourceCapacity(rsrcCpcty),
	constructCost(cntrctCst), returnedResources(rtrndRsrcs), name(nm),
	combat(cmbt) {}

ConstructType & Space_Colony::ConstructType::operator=(const ConstructType & right) {
	resourceShift = right.resourceShift;
	resourceCapacity = right.resourceCapacity;
	constructCost = right.constructCost;
	returnedResources = right.returnedResources;
	name = right.name;
	combat = right.combat;
	return *this;
}

bool Space_Colony::ConstructType::operator==(const ConstructType & right) const {
	return resourceShift == right.resourceShift
		&& resourceCapacity == right.resourceCapacity
		&& constructCost == right.constructCost
		&& returnedResources == right.returnedResources
		&& name == right.name
		&& combat == right.combat;
}

bool Space_Colony::ConstructType::operator!=(const ConstructType & right) const {
	return !operator==(right);
}
