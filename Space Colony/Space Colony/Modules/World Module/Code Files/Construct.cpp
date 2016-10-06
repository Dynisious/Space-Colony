#pragma once

#include "..\Headers\Galactic\Solar\Construct.h"

World_Module::Galactic::Solar::Construct::Construct()
	: Construct(tagSet(), resourceMap(), resourceMap(), false) {}

World_Module::Galactic::Solar::Construct::Construct(const Construct & orig)
	: Construct(orig.tags, orig.resourceShifts, orig.storage, orig.enabled) {}

World_Module::Galactic::Solar::Construct::Construct(const tagSet & tgs, const resourceMap & rsrcShfts, const Space_Colony::TypeCounter & strg, bool enbld)
	: tags(tgs), resourceShifts(rsrcShfts), storage(strg), enabled(enbld) {}

World_Module::Galactic::Solar::Construct & World_Module::Galactic::Solar::Construct::operator=(const Construct & right) {
	tags = right.tags;
	resourceShifts = right.resourceShifts;
	enabled = right.enabled;
	return *this;
}

bool World_Module::Galactic::Solar::Construct::operator==(const Construct & right) const {
	return (this == &right)
		|| (tags == right.tags
			&& resourceShifts == right.resourceShifts
			&& enabled == right.enabled);
}

bool World_Module::Galactic::Solar::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}
