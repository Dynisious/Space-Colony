#include "World Module\Headers\Galactic\Planetary\ConstructType.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galacitc::Planetary;

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType() {}

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType(const ConstructType & orig)
	: resourceShift(orig.resourceShift), deconstructReturn(orig.deconstructReturn), tags(orig.tags), name(orig.name), resourceCapacity(orig.resourceCapacity), constructCost(orig.constructCost) {}

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType(
	const TypeCounter & rsrcShft, const TypeCounter & dcnstrctRtrn, ConstructTags tgs,
	const std::string & nm, const TypeCounter & rsrcCpcty, const TypeCounter & cnstrctCst)
	: resourceShift(rsrcShft), deconstructReturn(dcnstrctRtrn), tags(tgs), name(nm) {
	setResourceCapacity(rsrcCpcty);
	setConstructCost(cnstrctCst);
}

const TypeCounter & Space_Colony::World_Module::Galacitc::Planetary::ConstructType::getResourceCapacity() const {
	return resourceCapacity;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planetary::ConstructType::setResourceCapacity(const TypeCounter & rsrcCpcty) {
	if (!rsrcCpcty.isPos())
		throw std::exception("The new resource capacity has negative values.");
	TypeCounter res(resourceCapacity);
	resourceCapacity = rsrcCpcty;
	return res;
}

size_t Space_Colony::World_Module::Galacitc::Planetary::ConstructType::setResourceCapacity(const __int32 rsrc, const size_t val) {
	return resourceCapacity.setCounter(rsrc, val);
}

const TypeCounter & Space_Colony::World_Module::Galacitc::Planetary::ConstructType::getConstructCost() const {
	return constructCost;
}

TypeCounter Space_Colony::World_Module::Galacitc::Planetary::ConstructType::setConstructCost(const TypeCounter & cnstrctCst) {
	if (!cnstrctCst.isPos())
		throw std::exception("The new construction cost has negative values.");
	TypeCounter res(constructCost);
	constructCost = cnstrctCst;
	return res;
}

size_t Space_Colony::World_Module::Galacitc::Planetary::ConstructType::setConstructCost(const __int32 rsrc, const size_t val) {
	return constructCost.setCounter(rsrc, val);
}

ConstructType & Space_Colony::World_Module::Galacitc::Planetary::ConstructType::operator=(const ConstructType & right) {
	resourceShift = right.resourceShift;
	deconstructReturn = right.deconstructReturn;
	tags = right.tags;
	name = right.name;
	resourceCapacity = right.resourceCapacity;
	constructCost = right.constructCost;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::operator==(const ConstructType & right) const {
	return (this == &right)
		|| (resourceShift == right.resourceShift
			&& deconstructReturn == right.deconstructReturn
			&& tags == right.tags
			&& name == right.name
			&& resourceCapacity == right.resourceCapacity
			&& constructCost == right.constructCost);
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::operator!=(const ConstructType & right) const {
	return !operator==(right);
}

std::unordered_set<ConstructType_ID> ConstructType_All_IDs;

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType_isLoaded(ConstructType_ID id) {
	return ConstructType_All_IDs.count(id) != 0;
}

const ConstructType & Space_Colony::World_Module::Galacitc::Planetary::ConstructType_get(ConstructType_ID id) {
	if (!ConstructType_isLoaded(id))
		throw std::runtime_error("The passed ID is not a loaded ID.");
	return *( ConstructType_Pointer ) id;
}

ConstructType_ID Space_Colony::World_Module::Galacitc::Planetary::ConstructType_load(const ConstructType & type) {
	for (auto iter(ConstructType_All_IDs.begin()), end(ConstructType_All_IDs.end()); iter != end; ++iter)
		if (type == *( ConstructType_Pointer ) *iter)
			//This type is already loaded.
			return ( ConstructType_ID ) *iter;
	return *ConstructType_All_IDs.insert((ConstructType_ID) new ConstructType(type)).first;
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType_unload(ConstructType_ID id) {
	if (ConstructType_isLoaded(id)) {
		//The type is loaded, unload it.
		ConstructType_All_IDs.erase(id);
		//Delete the ConstructType.
		delete ( ConstructType_Pointer ) id;
		return true;
	} else {
		return false;
	}
}
