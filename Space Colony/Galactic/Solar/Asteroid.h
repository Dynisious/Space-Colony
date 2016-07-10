#pragma once

#include "Solar.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			/*
			An asteroid is a small quick source of resources.*/
			class Asteroid {
			public:
				unsigned __int32 resources[ResourceType_max];

				Asteroid();
				Asteroid(unsigned __int32 resrcs[]);

			};

		}

	}

}
