#pragma once

#include "SpaceCraft.h"
#include "FloatilaTemplate.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			namespace SpaceCraft {

				/*
				A Floatila is a collection of different ships.*/
				class Floatila final {
				public:
					/*
					The number of points of fuel each FuelCow is capable of carrying.*/
					static unsigned __int32 FuelCowCapacity;

					/*
					True if the Floatila is currently in hostile terretory.*/
					bool hostileTerrertory;

					Floatila();
					Floatila(unsigned __int32* const cft);
					Floatila(const FloatilaTemplate& orig);

					const unsigned __int32* getCraft();
					/*
					Increments the specified type of craft by the passed increment,
					performing any necessary changes to the Floatila along the way.*/
					void incrementCraft(CraftTypes type, __int32 incr);
					/*
					Returns true if the Floatila is able to move.*/
					bool canMove();

					__declspec(property(get = getCraft)) const unsigned __int32* craft_prop;

					Floatila& operator=(FloatilaTemplate& const orig);

				private:
					unsigned __int32 craft[CraftTypes_max], fuel, fuel_max;

					/*
					Increments the type with no other change of values.*/
					void stdIncrement(CraftTypes type, __int32 incr);
					/*
					Increments the count of fuelCows and alters the fuel values as
					necessary.*/
					void fuelCowIncrement(__int32 incr);

				};

			}

		}

	}

}
