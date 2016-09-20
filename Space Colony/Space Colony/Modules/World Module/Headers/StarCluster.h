#pragma once

#include "World Module.h"
#include "Star System\SolarSystem.h"

namespace World_Module {

	/*
	A StarCluster is a collection of SolarSystems and can retrieve information
	about them as a group.*/
	class StarCluster {
	public:
		StarCluster();
		StarCluster(const StarCluster& orig);
		StarCluster(const Star_System::SolarVector systms);

		Star_System::SolarVector& get_systems();
		const Star_System::SolarVector& get_systems() const;
		Space_Colony::faction_t get_faction() const;
		BoundedResourceMap get_resources() const;

		__declspec(property(get = get_systems)) Star_System::SolarVector _systems;
		__declspec(property(get = get_faction)) Space_Colony::faction_t faction;
		__declspec(property(get = get_resources)) BoundedResourceMap _resources;

	private:
		Star_System::SolarVector systems;

	};

}
