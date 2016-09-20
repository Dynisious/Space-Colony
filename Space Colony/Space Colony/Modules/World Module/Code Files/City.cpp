#include "..\Headers\Star System\City.h"

using namespace World_Module::Star_System;

City::City()
	: City(ResourceMap(), FunctionTags(), -1, GroundForces(0)) {}

City::City(const City& orig)
	: City(orig.resourceChange, orig.funcionality, orig.size, orig.groundForces) {}

City::City(const World_Module::ResourceMap& resrcChng, const FunctionTags funcnlty,
		   const sizeValue sz, const GroundForces& grndFrcs)
	: resourceChange(resrcChng), funcionality(funcnlty), size(sz), groundForces(grndFrcs) {}

const World_Module::ResourceMap& City::get_resourceChange() const {
	return resourceChange;
}

World_Module::ResourceMap& City::get_resourceChange() {
	return resourceChange;
}

const City::GroundForces& City::get_groundForces() const {
	return groundForces;
}

City::GroundForces& City::get_groundForces() {
	return groundForces;
}

FunctionTags City::get_funcionality() const {
	return funcionality;
}

City::sizeValue City::get_size() const {
	return size;
}

City& City::operator=(const City& right) {
	resourceChange = right.resourceChange;
	funcionality = right.funcionality;
	size = right.size;
	return *this;
}

bool City::operator==(const City& right) const {
	if (this == &right)
		return true;
	return resourceChange == right.resourceChange
		&& funcionality == right.funcionality
		&& size == right.size;
}

bool City::operator!=(const City& right) const {
	if (this != &right)
		return true;
	return resourceChange != right.resourceChange
		|| funcionality != right.funcionality
		|| size != right.size;
}
