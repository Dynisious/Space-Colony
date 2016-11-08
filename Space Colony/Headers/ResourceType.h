#pragma once

#include "Space Colony.h"

namespace Space_Colony {

	/*
	A mass and volume value.*/
	struct ResourceType {
	public:
		ResourceType();
		ResourceType(const ResourceType &orig);
		ResourceType(const size_t ms, const size_t vlm);

		/*
		The mass of a unit of this ResourceType.*/
		size_t mass;
		/*
		The volume of a unit of this ResourceType.*/
		size_t volume;

		ResourceType & operator=(const ResourceType &right);
		bool operator==(const ResourceType &right) const;
		bool operator!=(const ResourceType &right) const;

	};

	typedef const ResourceType *const ResourceType_Pointer;
	typedef __int32 ResourceType_ID;

	bool ResourceType_isLoaded(ResourceType_ID id);

	const ResourceType & ResourceType_get(ResourceType_ID id);

	ResourceType_ID ResourceType_load(const ResourceType &type);

	bool ResourceType_unload(ResourceType_ID id);

}
