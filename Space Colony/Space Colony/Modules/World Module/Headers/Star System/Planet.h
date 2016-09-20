#pragma once

#include "Star System.h"
#include "ConstructionSite.h"
#include <vector>

namespace World_Module {

	namespace Star_System {

		/*
		A Planet has resources and can have Citys and
		Constructs built on it; Constructs can also be built as
		satallites for a Planet.*/
		struct Planet {
		public:
			Planet();
			Planet(const Planet& orig);
			Planet(const __int32 sts, const __int32 stlts, const BoundedResourceMap& rsrceDpsts, Space_Colony::faction_t fctn);
			Planet(const SiteVector& sts, const ConstructVector& stlts, const BoundedResourceMap& rsrceDpsts, Space_Colony::faction_t fctn);

			void performTick();

			Planet& operator=(const Planet& right);
			bool operator==(const Planet& right) const;
			bool operator!=(const Planet& right) const;

			SiteVector sites;
			ConstructVector satallites;
			BoundedResourceMap resourceDeposits;
			Space_Colony::faction_t faction;

		};

		typedef std::vector<Planet> PlanetVector;

	}

}
