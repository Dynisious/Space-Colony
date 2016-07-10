#pragma once

#include "Solar.h"
#include "Planet.h"
#include "Star.h"
#include "Asteroid.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			/*
			A StarSystem contains a few Stars and a collection of Planets and
			Asteroids. Some larger space structures or vehicals can only exist
			in the influence of a StarSystem also.*/
			class StarSystem final {
			public:
				StarSystem();
				StarSystem(Planet* const plnts, unsigned __int32 plnts_c,
						   Star* strs, unsigned __int32 strs_c,
						   Asteroid* astrds, unsigned __int32 astrds_c);
				~StarSystem();

				Planet* setPlanets(Planet* const plan);
				Planet* setPlanets(Planet* const plan, unsigned __int32 plan_c);
				Planet* getPlanets();
				unsigned __int32 getPlanetsCount();
				Star* setStars(Star* const str);
				Star* setStars(Star* const str, unsigned __int32 str_c);
				Star* getStars();
				unsigned __int32 getStarsCount();
				Asteroid* setAsteroids(Asteroid* const astr);
				Asteroid* setAsteroids(Asteroid* const astr, unsigned __int32 astr_c);
				Asteroid* getAsteroids();
				unsigned __int32 getAsteroidsCount();

				__declspec(property(get = getPlanets, put = setPlanets)) Planet* planets_prop;
				__declspec(property(get = getStars, put = setStars)) Star* stars_prop;
				__declspec(property(get = getAsteroids, put = setAsteroids)) Asteroid* asteroids_prop;
				
			private:
				Planet* planets;
				unsigned __int32 planets_c;
				Star* stars;
				unsigned __int32 stars_c;
				Asteroid* asteroids;
				unsigned __int32 asteroids_c;

			};

		}

	}

}
