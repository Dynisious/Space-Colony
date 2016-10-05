#pragma once

#include "..\Headers\Galactic\Sector\Solar\Construct.h"

World_Module::Galactic::Sector::Solar::Construct::Construct()
	: Construct(tagSet(), resourceMap(), resourceMap(), false) {}

World_Module::Galactic::Sector::Solar::Construct::Construct(const Construct & orig)
	: Construct(orig.tags, orig.resourceShifts, orig.storage, orig.enabled) {}

World_Module::Galactic::Sector::Solar::Construct::Construct(tagSet tgs, resourceMap rsrcShfts, Space_Colony::TypeCounter strg, bool enbld)
	: tags(tgs), resourceShifts(rsrcShfts), storage(strg), enabled(enbld) {}

World_Module::Galactic::Sector::Solar::Construct & World_Module::Galactic::Sector::Solar::Construct::operator=(const Construct & right) {
	tags = right.tags;
	resourceShifts = right.resourceShifts;
	enabled = right.enabled;
	return *this;
}

bool World_Module::Galactic::Sector::Solar::Construct::operator==(const Construct & right) const {
	return (this == &right)
		|| (tags == right.tags
			&& resourceShifts == right.resourceShifts
			&& enabled == right.enabled);
}

bool World_Module::Galactic::Sector::Solar::Construct::operator!=(const Construct & right) const {
	return !operator==(right);
}
