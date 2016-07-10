#pragma once

#include "Structures.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			namespace Structures {

				/*
				A template class for Colonys so that they can be constructed
				and assigned from these.*/
				class ColonyTemplate {
				public:
					static unsigned __int32
						orbDefCosts[ResourceType_max], 
						harvestCosts[ResourceType_max], 
						civCosts[ResourceType_max];

					const unsigned __int32 orbitalDefences, harvesters, civilisations;

					ColonyTemplate();
					ColonyTemplate(const ColonyTemplate& orig);
					ColonyTemplate(const unsigned __int32 orbDef, const unsigned __int32 hrvsts, const unsigned __int32 civs);

					const unsigned __int32* getCosts();

					__declspec(property(get = getCosts)) const unsigned __int32* costs_prop;

				private:
					unsigned __int32 costs[ResourceType_max];

				};

			}

		}

	}

}
