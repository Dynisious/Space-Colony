#pragma once

#include "..\..\..\Headers\Space Colony.h"
#include <Maths\matrix.h>
#include <unordered_set>
#include <unordered_map>

/*
A namespace for all things within the game world.*/
namespace World_Module {
	typedef __int32 resource_t;
	typedef __int32 resourceID;
	/*
	A Map of resoureIDs and counters.*/
	typedef std::unordered_map<resourceID, __int32> resourceMap;
	enum class WorldTags {
		Ground_Construct,
		Orbital_Construct
	};
	/*
	A set of __int32 tags.*/
	typedef std::unordered_set<WorldTags> tagSet;
	/*
	A coordinate for StarClusters in a Galaxy.*/
	typedef Dyn_API::Maths::matrix<__int32, 2, 1> coordinate;

	__int32 WorldModule_load();

};