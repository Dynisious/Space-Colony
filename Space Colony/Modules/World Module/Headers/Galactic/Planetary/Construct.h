#pragma once

#include "Planetary.h"
#include "ConstructType.h"

namespace Space_Colony {

	namespace World_Module {

		namespace Galacitc {

			namespace Planetary {

				/*
				A Construct represents a actualised instance of a ConstructType.*/
				class Construct {
				public:
					Construct();
					Construct(const Construct &orig);
					Construct(ConstructType_ID TpID, bool actv);

					const ConstructType & getType() const;

					/*
					An ID for the ConstructType which represents this Construct.*/
					__int32 typeID;
					/*
					True if the Construct is currently active and is producing a change in resources.*/
					bool active;

					Construct & operator=(const Construct &right);
					bool operator==(const Construct &right) const;
					bool operator!=(const Construct &right) const;

				};

			}

		}

	}

}
