#include "Galactic\Solar\StarSystem.h"

Space_Colony::Galactic::Solar::StarSystem::StarSystem()
	: StarSystem(nullptr, 0, nullptr, 0, nullptr, 0) {}

Space_Colony::Galactic::Solar::StarSystem::StarSystem(Planet * const plnts, unsigned __int32 plnts_c,
													  Star * strs, unsigned __int32 strs_c,
													  Asteroid * astrds, unsigned __int32 astrds_c)
	: planets_c(plnts_c), planets(new Planet[plnts_c]),
	stars_c(strs_c), stars(new Star[strs_c]),
	asteroids_c(astrds_c), asteroids(new Asteroid[astrds_c]) {
	planets_prop = plnts;
	stars_prop = strs;
	asteroids_prop = astrds;
}

Space_Colony::Galactic::Solar::StarSystem::~StarSystem() {
	delete[] planets;
	delete[] stars;
	delete[] asteroids;
}

Space_Colony::Galactic::Solar::Planet * Space_Colony::Galactic::Solar::StarSystem::setPlanets(Planet * const plan) {
	FILL_ARRAY(planets, plan, planets_c, i, unsigned __int32 i(0))
		return planets;
}

Space_Colony::Galactic::Solar::Planet * Space_Colony::Galactic::Solar::StarSystem::setPlanets(Planet * const plan, unsigned __int32 plan_c) {
	COPY_ARRAY(Planet, planets, plan, plan_c, i, unsigned __int32 i(0))
		return planets;
}

Space_Colony::Galactic::Solar::Planet * Space_Colony::Galactic::Solar::StarSystem::getPlanets() {
	return planets;
}

unsigned __int32 Space_Colony::Galactic::Solar::StarSystem::getPlanetsCount() {
	return planets_c;
}

Space_Colony::Galactic::Solar::Star * Space_Colony::Galactic::Solar::StarSystem::setStars(Star * const str) {
	FILL_ARRAY(stars, str, planets_c, i, unsigned __int32 i(0))
		return stars;
}

Space_Colony::Galactic::Solar::Star * Space_Colony::Galactic::Solar::StarSystem::setStars(Star * const str, unsigned __int32 str_c) {
	COPY_ARRAY(Star, stars, str, str_c, i, unsigned __int32 i(0))
		return stars;
}

Space_Colony::Galactic::Solar::Star * Space_Colony::Galactic::Solar::StarSystem::getStars() {
	return stars;
}

unsigned __int32 Space_Colony::Galactic::Solar::StarSystem::getStarsCount() {
	return stars_c;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::StarSystem::setAsteroids(Asteroid * const astr) {
	FILL_ARRAY(asteroids, astr, planets_c, i, unsigned __int32 i(0))
		return asteroids;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::StarSystem::setAsteroids(Asteroid * const astr, unsigned __int32 astr_c) {
	COPY_ARRAY(Asteroid, asteroids, astr, astr_c, i, unsigned __int32 i(0))
		return asteroids;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::StarSystem::getAsteroids() {
	return asteroids;
}

unsigned __int32 Space_Colony::Galactic::Solar::StarSystem::getAsteroidsCount() {
	return asteroids_c;
}
