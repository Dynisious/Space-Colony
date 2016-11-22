#include "ResourceType.h"

using namespace Space_Colony;

Space_Colony::ResourceType::ResourceType()
	: ResourceType(0, 0) {}

Space_Colony::ResourceType::ResourceType(const ResourceType & orig)
	: ResourceType(orig.mass, orig.volume) {}

Space_Colony::ResourceType::ResourceType(const size_t ms, const size_t vlm)
	: mass(ms), volume(vlm) {}

ResourceType & Space_Colony::ResourceType::operator=(const ResourceType & right) {
	mass = right.mass;
	volume = right.volume;
	return *this;
}

bool Space_Colony::ResourceType::operator==(const ResourceType & right) const {
	return mass == right.mass
		&& volume == right.volume;
}

bool Space_Colony::ResourceType::operator!=(const ResourceType & right) const {
	return !operator==(right);
}
