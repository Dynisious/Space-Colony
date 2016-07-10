#pragma once

#include "Solar.h"
#include "Asteroid.h"
#include "Structures\Colony.h"
#include "Structures\ColonyTemplate.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			/*
			A Planet is a member of a StarSystem which can contains a
			collection of asteroids, smaller space vehicles and defencive
			structures.*/
			class Planet final {
			public:
				unsigned __int32 resources_v[ResourceType_max];

				Planet();
				Planet(unsigned __int32 resrc[], Asteroid* astrds, unsigned __int32 astrds_c);
				~Planet();

				Asteroid* setAsteroids(Asteroid* const astrds);
				Asteroid* setAsteroids(Asteroid* const astrds, unsigned __int32 astrds_c);
				Asteroid* getAsteroids();
				unsigned __int32 getAsteroidsCount();
				/*
				Returns true and subtracts the required resources from the
				Planet if there are enough resources to colonise the Planet;
				else it returns false.*/
				bool colonise(Structures::ColonyTemplate& const col);
				Structures::Colony& const getColony();

				__declspec(property(get = getAsteroids, put = setAsteroids)) Asteroid* asteroids_prop;
				__declspec(property(get = getColony)) Structures::Colony& const colony_prop;


			private:
				Asteroid* asteroids;
				unsigned __int32 asteroids_c;
				bool colonised;
				Structures::Colony colony;

			};

		}

	}

}
