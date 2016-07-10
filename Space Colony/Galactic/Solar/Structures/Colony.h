#pragma once

#include "Structures.h"
#include "ColonyTemplate.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			namespace Structures {

				/*
				A Colony can be built on top of a planet to extract it's
				resources.*/
				class Colony {
				public:
					unsigned __int32 orbitalDefences,
						harvesters,
						civilisations;

					Colony();
					Colony(const Colony& orig);
					Colony(const ColonyTemplate& temp);

					Colony& operator=(const ColonyTemplate& temp);

				};

			}

		}

	}

}
