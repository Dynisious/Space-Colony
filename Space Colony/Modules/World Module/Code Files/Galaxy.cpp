#include "World Module\Headers\Galaxy.h"
#include <algorithm>

using namespace Space_Colony;
using namespace Space_Colony::World_Module;

Space_Colony::World_Module::Galaxy::Galaxy() {}

Space_Colony::World_Module::Galaxy::Galaxy(const Galaxy & orig)
	: Galaxy(orig.name, orig.sectors) {}

Space_Colony::World_Module::Galaxy::Galaxy(const std::string & nm, const StarMap & sctrs)
	: name(nm), sectors(sctrs) {}

coordinate Space_Colony::World_Module::Galaxy::addSector(const Galacitc::StarSector & sec, const double range, const coordinate &location) {
	coordinate coord(newCoordinate(range, location));
	sectors.emplace(coord, sec);
	return coord;
}

Galacitc::StarSector & Space_Colony::World_Module::Galaxy::getSector(const coordinate & coord) {
	return sectors.at(coord);
}

const Galacitc::StarSector & Space_Colony::World_Module::Galaxy::getSector(const coordinate & coord) const {
	return sectors.at(coord);
}

const Galaxy::StarMap & Space_Colony::World_Module::Galaxy::getSectors() const {
	return sectors;
}

coordinate Space_Colony::World_Module::Galaxy::getCentre() const {
	coordinate centre(0);
	for (auto iter(sectors.begin()), end(sectors.end()); iter != end; ++iter)
		centre += iter->first;
	return centre /= sectors.size();
}

void Space_Colony::World_Module::Galaxy::iterate() {
	for (auto iter(sectors.begin()), end(sectors.end()); iter != end; ++iter)
		iter->second.iterate();
}

Galaxy & Space_Colony::World_Module::Galaxy::operator=(const Galaxy & right) {
	name = right.name;
	sectors = right.sectors;
	return *this;
}

bool Space_Colony::World_Module::Galaxy::operator==(const Galaxy & right) const {
	return (this == &right)
		|| (name == right.name
			&& sectors == right.sectors);
}

bool Space_Colony::World_Module::Galaxy::operator!=(const Galaxy & right) const {
	return !operator==(right);
}

coordinate Space_Colony::World_Module::Galaxy::newCoordinate(double range, const coordinate &location) const {
	coordinate coord;
	//Randomise the range.
	range *= std::rand() / ( double ) INT32_MAX;
	do {
		//Produce a random coordinate.
		coord = {
			std::rand() + (INT32_MIN << 2),
			std::rand() + (INT32_MIN << 2)
		};
		coord = ((Dyn_API::Maths::Matrix_Math::unit<double>(coord -= location) * range) += location);
	} while (sectors.count(coord) != 0);
	return coord += (Dyn_API::Maths::Matrix_Math::unit<double>(getCentre() -= coord) * range);
}