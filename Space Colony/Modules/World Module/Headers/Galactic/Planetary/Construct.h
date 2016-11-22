#pragma once

#include "Planetary.h"
#include "ConstructType.h"

namespace Space_Colony {

	namespace World_Module {

		namespace Galactic {

			namespace Planetary {

				/*
				A Construct represents a actualised instance of a ConstructType.*/
				class Construct {
				public:
					Construct();
					Construct(const Construct &orig);
					Construct(const size_t typId, const bool actv);

					/*
					An int ID for a ConstructType which represents this Construct.*/
					__int32 typeId;
					/*
					True if the Construct is currently active and is producing
					a change in resources.*/
					bool active;

					Construct & operator=(const Construct &right);
					bool operator==(const Construct &right) const;
					bool operator!=(const Construct &right) const;

				};

			}

		}

	}

}
