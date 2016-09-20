#pragma once

#include "Star System.h"
#include "Construct.h"
#include "Planet.h"
#include <Ships\Fleet.h>
#include <vector>

namespace World_Module {

	namespace Star_System {

		/*
		A SolarSystem is a collection of Stars and Planets; Fleets are
		also able to move inside of SolarSystems.*/
		class SolarSystem {
		public:
			SolarSystem();
			SolarSystem(const SolarSystem& orig);
			SolarSystem(unsigned __int32 plnts, unsigned __int32 strctrs, const BoundedResourceMap& rsrcs);
			SolarSystem(const Space_Colony::Ships::FleetVector& flts, const PlanetVector& plnts, 
						const ConstructVector& strctrs, const BoundedResourceMap& rsrcs);

			void performTick();

			const Space_Colony::faction_t get_faction() const;
			const PlanetVector& get_planets() const;
			const ConstructVector& get_structures() const;
			const BoundedResourceMap& get_resources() const;

			__declspec(property(get = get_faction)) Space_Colony::faction_t faction;
			__declspec(property(get = get_planets)) PlanetVector _planets;
			__declspec(property(get = get_structures)) ConstructVector _structures;
			__declspec(property(get = get_resources)) BoundedResourceMap _resources;

			Space_Colony::Ships::FleetVector fleets;

		private:
			PlanetVector planets;
			ConstructVector structures;
			BoundedResourceMap resources;

		};

		typedef std::vector<SolarSystem> SolarVector;

	}

}
