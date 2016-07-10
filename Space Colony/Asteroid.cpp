#include "Galactic\Solar\Asteroid.h"

Space_Colony::Galactic::Solar::Asteroid::Asteroid() {}

Space_Colony::Galactic::Solar::Asteroid::Asteroid(unsigned __int32 resrcs[]) {
	for (unsigned __int32 i(0); i < ResourceType_max; i++)
		resources[i] = resrcs[i];
}
