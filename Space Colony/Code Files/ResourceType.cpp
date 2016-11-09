#include "ResourceType.h"
#include <unordered_set>

using namespace Space_Colony;

Space_Colony::ResourceType::ResourceType() {}

Space_Colony::ResourceType::ResourceType(const ResourceType & orig)
	: ResourceType(orig.mass, orig.volume) {}

Space_Colony::ResourceType::ResourceType(const size_t ms, const size_t vlm)
	: mass(ms), volume(vlm) {}

std::unordered_set<ResourceType *> Pooled_All_ResourceTypes;

ResourceRef Space_Colony::ResourceType::create() {
	ResourceRef res(new ResourceType());
	Pooled_All_ResourceTypes.insert(res);
	return res;
}

ResourceRef Space_Colony::ResourceType::create(const ResourceType & orig) {
	ResourceRef res(new ResourceType(orig));
	Pooled_All_ResourceTypes.insert(res);
	return res;
}

ResourceRef Space_Colony::ResourceType::create(const size_t ms, const size_t vlm) {
	ResourceRef res(new ResourceType(ms, vlm));
	Pooled_All_ResourceTypes.insert(res);
	return res;
}

bool Space_Colony::ResourceType::isLoaded(ResourceType *const id) {
	return Pooled_All_ResourceTypes.count(id) != 0;
}

bool Space_Colony::ResourceType::unloadType(ResourceType *const id) {
	if (isLoaded(id)) {
		//The ID is already loaded, unload it.
		Pooled_All_ResourceTypes.erase(id);
		//Delete the ResourceType.
		delete id;
		return true;
	} else {
		return false;
	}
}

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

Space_Colony::ResourceRef::ResourceRef()
	: instance(nullptr) {}

Space_Colony::ResourceRef::ResourceRef(ResourceType * const orig)
	: instance(orig) {
	if (!check())
		throw std::exception("The pointer is invalid.");
}

bool Space_Colony::ResourceRef::check() const {
	return ResourceType::isLoaded(instance);
}

void Space_Colony::ResourceRef::unbind() {
	instance = nullptr;
}

ResourceRef & Space_Colony::ResourceRef::operator=(ResourceType * const right) {
	if (!ResourceType::isLoaded(right))
		throw std::exception("The pointer is invalid.");
	instance = right;
	return *this;
}

bool Space_Colony::ResourceRef::operator==(ResourceType * const right) const {
	if (!check() || !ResourceType::isLoaded(right))
		throw std::exception("The pointer is invalid.");
	return instance == right;
}

bool Space_Colony::ResourceRef::operator!=(ResourceType * const right) const {
	return !operator==(right);
}

ResourceType & Space_Colony::ResourceRef::operator*() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

const ResourceType & Space_Colony::ResourceRef::operator*() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

ResourceType * Space_Colony::ResourceRef::operator->() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

const ResourceType * Space_Colony::ResourceRef::operator->() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::ResourceRef::operator ResourceType*const() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::ResourceRef::operator const ResourceType*const() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}
