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

std::unordered_set<ConstructType_ID> ConstructType_All_IDs;

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::isLoaded(ConstructType_ID id) {
	return ConstructType_All_IDs.count(id) != 0;
}

ConstructType & Space_Colony::World_Module::Galacitc::Planetary::ConstructType::getType(ConstructType_ID id) {
	if (!isLoaded(id))
		throw std::runtime_error("The passed ID is not a loaded ID.");
	return *( ConstructType_Pointer ) id;
}

ConstructType_ID Space_Colony::World_Module::Galacitc::Planetary::ConstructType::loadType(const ConstructType & type) {
	for (auto iter(ConstructType_All_IDs.begin()), end(ConstructType_All_IDs.end()); iter != end; ++iter)
		if (type == *( ConstructType_Pointer ) *iter)
			//This type is already loaded.
			return ( ConstructType_ID ) *iter;
	return *ConstructType_All_IDs.insert((ConstructType_ID) new ConstructType(type)).first;
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::unloadType(ConstructType_ID id) {
	if (isLoaded(id)) {
		//The type is loaded, unload it.
		ConstructType_All_IDs.erase(id);
		//Delete the ConstructType.
		delete ( ConstructType_Pointer ) id;
		return true;
	} else {
		return false;
	}
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

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct()
	: Construct(0, false) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(const Construct & orig)
	: Construct(orig.typeID, orig.active) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(ConstructType_ID TpID, bool actv)
	: typeID(TpID), active(actv) {}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::check() const {
	return ConstructType::isLoaded(typeID);
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

ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator*() {
	if (!check())
		throw std::exception("The TypeID of this Construct is invalid.");
	return ConstructType::getType(typeID);
}

const ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator*() const {
	if (!check())
		throw std::exception("The TypeID of this Construct is invalid.");
	return ConstructType::getType(typeID);
}

ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::Construct::operator->() {
	if (!check())
		throw std::exception("The TypeID of this Construct is invalid.");
	return ( ConstructType_Pointer ) typeID;
}

const ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::Construct::operator->() const {
	if (!check())
		throw std::exception("The TypeID of this Construct is invalid.");
	return ( ConstructType_Pointer ) typeID;
}
