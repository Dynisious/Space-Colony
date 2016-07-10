#include "Galactic\Solar\Structures\Colony.h"

Space_Colony::Galactic::Solar::Structures::Colony::Colony()
	: orbitalDefences(0), harvesters(0), civilisations(0) {}

Space_Colony::Galactic::Solar::Structures::Colony::Colony(const Colony & orig)
	: orbitalDefences(orig.orbitalDefences), harvesters(orig.harvesters), civilisations(orig.civilisations) {}

Space_Colony::Galactic::Solar::Structures::Colony::Colony(const ColonyTemplate & temp) {
	operator=(temp);
}

Space_Colony::Galactic::Solar::Structures::Colony & Space_Colony::Galactic::Solar::Structures::Colony::operator=(const ColonyTemplate & temp) {
	orbitalDefences = temp.orbitalDefences;
	harvesters = temp.harvesters;
	civilisations = temp.civilisations;
	return (Colony&) *this;
}
