#include "..\Headers\Star System\Construct.h"

using namespace World_Module::Star_System;

Construct::Construct()
	: Construct(ResourceMap(0), FunctionTags(0)) {}

Construct::Construct(const Construct& orig)
	: Construct(orig.resourceChange, orig.functionality) {}

Construct::Construct(const World_Module::ResourceMap& rsrcChng, const FunctionTags& fnctnlty)
	: resourceChange(rsrcChng), functionality(fnctnlty) {}

const World_Module::ResourceMap& Construct::get_resourceChange() const {
	return resourceChange;
}

FunctionTags Construct::get_functionality() const {
	return functionality;
}

Construct& Construct::operator=(const Construct& right) {
	resourceChange = right.resourceChange;
	functionality = right.functionality;
	return *this;
}

bool Construct::operator==(const Construct& right) const {
	return resourceChange == right.resourceChange
		&& functionality == right.functionality;
}

bool Construct::operator!=(const Construct& right) const {
	return resourceChange != right.resourceChange
		|| functionality != right.functionality;
}
