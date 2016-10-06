#pragma once

#include "Galactic.h"
#include "StarSystem.h"
#include <vector>
#include <unordered_map>

namespace World_Module {

	namespace Galactic {

		/*
		A StarCluster is a group of StarSystems.*/
		class StarCluster : public std::vector<StarSystem> {
		public:
			StarCluster();
			StarCluster(const StarCluster& orig);
			StarCluster(const __int32 systms);

			tagSet get_tags() const;
			Space_Colony::faction_t get_faction() const;

			/*
			The cumulative WorldTags of all this StarClusters StarSystems.*/
			__declspec(property(get = get_tags)) tagSet _tags;
			/*
			The cumulative faction of all this StarClusters StarSystems.*/
			__declspec(property(get = get_faction)) Space_Colony::faction_t _faction;

		};

		typedef std::unordered_map<__int32, StarCluster> StarMap;

	}

}
