#include "Galactic\Solar\Planet.h"

Space_Colony::Galactic::Solar::Planet::Planet()
	: asteroids_c(0), asteroids(nullptr), colonised(false) {}

Space_Colony::Galactic::Solar::Planet::Planet(unsigned __int32 resrc[], Asteroid * astrds, unsigned __int32 astrds_c)
	: asteroids_c(astrds_c), asteroids(new Asteroid[astrds_c]), colonised(false) {
	asteroids_prop = astrds;
}

Space_Colony::Galactic::Solar::Planet::~Planet() {
	delete[] asteroids;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::Planet::setAsteroids(Asteroid * const astrds) {
	FILL_ARRAY(asteroids, astrds, asteroids_c, i, unsigned __int32 i(0))
		return asteroids;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::Planet::setAsteroids(Asteroid * const astrds, unsigned __int32 astrds_c) {
	COPY_ARRAY(Asteroid, asteroids, astrds, astrds_c, i, unsigned __int32 i(0));
	return asteroids;
}

Space_Colony::Galactic::Solar::Asteroid * Space_Colony::Galactic::Solar::Planet::getAsteroids() {
	return asteroids;
}

unsigned __int32 Space_Colony::Galactic::Solar::Planet::getAsteroidsCount() {
	return asteroids_c;
}

bool Space_Colony::Galactic::Solar::Planet::colonise(Structures::ColonyTemplate & const col) {
	if (colonised)
		return false;
	unsigned __int32 i(0);
	for (; i < ResourceType_max; i++)
		if (resources_v[i] < col.costs_prop[i])
			return false;

	for (i = 0; i < ResourceType_max; i++)
		resources_v[i] -= col.costs_prop[i];
	colony = col;
	return colonised = true;
}

Space_Colony::Galactic::Solar::Structures::Colony & const Space_Colony::Galactic::Solar::Planet::getColony() {
	return colony;
}
