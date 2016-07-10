#include "Galactic\Galaxy.h"

Space_Colony::Galactic::Galaxy::Galaxy()
	: Galaxy(nullptr, 0) {}

Space_Colony::Galactic::Galaxy::Galaxy(Solar::StarSystem * const sys, unsigned __int32 sys_c)
	: systems_c(sys_c), systems(new Solar::StarSystem[sys_c]) {
	systems_prop = sys;
}

Space_Colony::Galactic::Galaxy::~Galaxy() {
	delete[] systems;
}

Space_Colony::Galactic::Solar::StarSystem * Space_Colony::Galactic::Galaxy::setSystems(Solar::StarSystem * const sys) {
	FILL_ARRAY(systems, sys, systems_c, i, unsigned __int32 i(0))
		return systems;
}

Space_Colony::Galactic::Solar::StarSystem * Space_Colony::Galactic::Galaxy::setSystems(Solar::StarSystem * const sys, unsigned __int32 sys_c) {
	COPY_ARRAY(Solar::StarSystem, systems, sys, sys_c, i, unsigned __int32 i(0))
		return systems;
}

Space_Colony::Galactic::Solar::StarSystem * Space_Colony::Galactic::Galaxy::getSystems() {
	return systems;
}

unsigned __int32 Space_Colony::Galactic::Galaxy::getSystemsCount() {
	return systems_c;
}
