#pragma once

#include "Space Colony.h"
#include <vector>

namespace Space_Colony {

	/*
	A mass and volume value.*/
	struct ResourceType {
		ResourceType();
		ResourceType(const ResourceType &orig);
		ResourceType(const size_t ms, const size_t vlm);

		/*
		The mass of a unit of this type.*/
		size_t mass;
		/*
		The volume of a unit of this type.*/
		size_t volume;

		ResourceType & operator=(const ResourceType &right);
		bool operator==(const ResourceType &right) const;
		bool operator!=(const ResourceType &right) const;

	};

	typedef std::vector<ResourceType> ResourceTypeVector;

}
