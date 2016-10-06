#pragma once

#include "World Module.h"
#include "Galactic\StarCluster.h"
#include <unordered_map>

namespace World_Module {

	/*
	A Galaxy is a collection of connected StarClusters.*/
	class Galaxy {
	public:
		typedef std::unordered_map<coordinate, Galactic::StarCluster> StarMap;

		Galaxy();
		Galaxy(const Galaxy& orig);
		Galaxy(const StarMap& clstrs);

		void newCluster(const Galactic::StarCluster& cluster);

		StarMap clusters;

		Galaxy& operator=(const Galaxy& right);
		bool operator==(const Galaxy& right) const;
		bool operator!=(const Galaxy& right) const;

	};

}
