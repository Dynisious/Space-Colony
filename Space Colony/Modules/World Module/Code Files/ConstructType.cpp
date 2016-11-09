#include "World Module\Headers\Galactic\Planetary\ConstructType.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galacitc::Planetary;

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType() {}

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType(const ConstructType & orig)
	: resourceShift(orig.resourceShift), deconstructReturn(orig.deconstructReturn), tags(orig.tags),
	name(orig.name), resourceCapacity(orig.resourceCapacity), constructCost(orig.constructCost) {}

Space_Colony::World_Module::Galacitc::Planetary::ConstructType::ConstructType(
	const TypeCounter & rsrcShft, const TypeCounter & dcnstrctRtrn, ConstructTags tgs,
	const std::string & nm, const TypeCounter & rsrcCpcty, const TypeCounter & cnstrctCst)
	: resourceShift(rsrcShft), deconstructReturn(dcnstrctRtrn), tags(tgs), name(nm) {
	setResourceCapacity(rsrcCpcty);
	setConstructCost(cnstrctCst);
}

std::unordered_set<ConstructType *> Pooled_All_ConstructTypes;

ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::ConstructType::create() {
	ConstructType *res(new ConstructType());
	Pooled_All_ConstructTypes.insert(res);
	return res;
}

ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::ConstructType::create(const ConstructType & orig) {
	ConstructType *res(new ConstructType(orig));
	Pooled_All_ConstructTypes.insert(res);
	return res;
}

ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::ConstructType::create(
	const TypeCounter & rsrcShft, const TypeCounter & dcnstrctRtrn, ConstructTags tgs, const std::string & nm,
	const TypeCounter & rsrcCpcty, const TypeCounter & cnstrctCst) {
	ConstructType *res(new ConstructType(rsrcShft, dcnstrctRtrn, tgs, nm, rsrcCpcty, cnstrctCst));
	Pooled_All_ConstructTypes.insert(res);
	return res;
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::isLoaded(const ConstructType *id) {
	return Pooled_All_ConstructTypes.count(( ConstructType * ) id) != 0;
}

bool Space_Colony::World_Module::Galacitc::Planetary::ConstructType::unloadType(const ConstructType *id) {
	if (isLoaded(id)) {
		//The type is loaded, unload it.
		Pooled_All_ConstructTypes.erase(( ConstructType * ) id);
		//Delete the ConstructType.
		delete id;
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
	: instance(0), active(false) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(const Construct & orig)
	: Construct(orig.instance, orig.active) {}

Space_Colony::World_Module::Galacitc::Planetary::Construct::Construct(ConstructType *const orig, bool actv)
	: instance(orig), active(actv) {
	if (!check())
		throw std::exception("The pointer is invalid.");
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::check() const {
	return ConstructType::isLoaded(instance);
}

void Space_Colony::World_Module::Galacitc::Planetary::Construct::unbind() {
	instance = nullptr;
}

Construct & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator=(const Construct & right) {
	if (!right.check())
		throw std::exception("The pointer is invalid.");
	instance = right.instance;
	active = right.active;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator==(const Construct & right) const {
	if (!check() || right.check())
		throw std::exception("The pointer is invalid.");
	return instance == right.instance
		&& active == right.active;
}

bool Space_Colony::World_Module::Galacitc::Planetary::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}

ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator*() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

const ConstructType & Space_Colony::World_Module::Galacitc::Planetary::Construct::operator*() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::Construct::operator->() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

const ConstructType * const Space_Colony::World_Module::Galacitc::Planetary::Construct::operator->() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::World_Module::Galacitc::Planetary::Construct::operator ConstructType const*() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::World_Module::Galacitc::Planetary::Construct::operator const ConstructType const*() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}
