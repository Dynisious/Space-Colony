#pragma once

#include "World Module.h"
#include "Star System\SolarSystem.h"
#include <unordered_map>

namespace World_Module {

	/*
	A Galaxy is a network of clusters of SolarSystems linked together in a web.*/
	class Galaxy {
	public:
		typedef std::pair<__int32, __int32> coordinate;
		typedef std::unordered_map<coordinate, World_Module::Star_System::SolarVector> StarMap;

		Galaxy();
		Galaxy(const Galaxy& orig);
		Galaxy(const StarMap& orig);
		
	private:
		StarMap clusters;

	};

}
