#include "ResourceType.h"
#include <unordered_set>

using namespace Space_Colony;

Space_Colony::ResourceType::ResourceType() {}

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

std::unordered_set<ResourceType_ID> ResourceType_All_IDs;

bool Space_Colony::ResourceType_isLoaded(ResourceType_ID id) {
	return ResourceType_All_IDs.count(id) != 0;
}

const ResourceType & Space_Colony::ResourceType_get(ResourceType_ID id) {
	if (!ResourceType_isLoaded(id))
		throw std::runtime_error("The passed ID is not a loaded ID.");
	return *( ResourceType_Pointer ) id;
}

ResourceType_ID Space_Colony::ResourceType_load(const ResourceType & type) {
	for (auto iter(ResourceType_All_IDs.begin()), end(ResourceType_All_IDs.end()); iter != end; ++iter)
		if (type == *( ResourceType_Pointer ) *iter)
			//This type is already loaded, return it's ID.
			return ( ResourceType_ID ) *iter;
	return *ResourceType_All_IDs.insert((ResourceType_ID) new ResourceType(type)).first;
}

bool Space_Colony::ResourceType_unload(ResourceType_ID id) {
	if (ResourceType_isLoaded(id)) {
		//The ID is already loaded, unload it.
		ResourceType_All_IDs.erase(id);
		//Delete the ResourceType.
		delete ( ResourceType_Pointer ) id;
		return true;
	} else {
		return false;
	}
}
