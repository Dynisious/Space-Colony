#include "World Module\Headers\Galaxy.h"

using namespace Space_Colony::World_Module;

Space_Colony::World_Module::Galaxy::Galaxy()
	: name("Unnamed Galaxy"), sectors(0) {}

Space_Colony::World_Module::Galaxy::Galaxy(const Galaxy & orig)
	: Galaxy(orig.name, orig.sectors) {}

Space_Colony::World_Module::Galaxy::Galaxy(const std::string & nm, const SectorMap & sctrs)
	: name(nm), sectors(sctrs) {}

const Galaxy::SectorMap & Space_Colony::World_Module::Galaxy::getSectors() const {
	return sectors;
}

coordinate Space_Colony::World_Module::Galaxy::addSector(const size_t sector, const double range,
														 const coordinate & location) {
	//Iterate all sectors.
	for (auto iter(sectors.begin()), end(sectors.end()); iter != end; ++iter)
		//Check if the sector already exists in the galaxy.
		if (sector == iter->second)
			//If the sector already exists in the galaxy, throw an error.
			throw Repreated_Sector_Id;
	//Create a new coordinate for the sector.
	coordinate coord(newCoordinate(range, location));
	//Add the new sector to the sectors.
	sectors.insert_or_assign(coord, sector);
	//Return the coordinate for the sector.
	return coord;
}

size_t Space_Colony::World_Module::Galaxy::getSector(const coordinate & loc) const {
	return sectors.at(loc);
}

coordinate Space_Colony::World_Module::Galaxy::getCentre() const {
	//Create a 0 coordinate for the result.
	coordinate res(0);
	//Iterate all sectors.
	for (auto iter(sectors.begin()), end(sectors.end()); iter != end; ++iter)
		//Accumulate the sector coordainte.
		res += iter->first;
	//Return the centre of the sector coordinates.
	return res /= sectors.size();
}

void Space_Colony::World_Module::Galaxy::iterate(Galactic::SectorVector & sctrs, const FleetVector & flts,
												 const ConstructTypeVector & cnstrcts) {
	//Iterate all sectors.
	for (auto iter(sectors.begin()), end(sectors.end()); iter != end; ++iter)
		//Perform an iteration on the sector.
		sctrs.at(iter->second).iterate(flts, cnstrcts);
}

coordinate Space_Colony::World_Module::Galaxy::newCoordinate(const double range, const coordinate & location) const {
	//Create a default coordinate for the result.
	coordinate coord;
	do {
		//Create a random value for the coordinates X.
		coord[0] = rand();
		//Create a random value for the coordinates Y.
		coord[1] = rand();
		//Assign the new coordinate by rescaling the coordinate for the range
		//in the random direction.
		coord = (Dyn_API::Maths::Matrix_Math::unit<double>(coord -= location) *= range);
		//Add the direction in range to the location.
		coord += location;
		//Loop until a new coordinate is found.
	} while (sectors.count(coord) != 0);
	//Return the new coordinate.
	return coord;
}

Galaxy & Space_Colony::World_Module::Galaxy::operator=(const Galaxy & right) {
	name = right.name;
	sectors = right.sectors;
	return *this;
}

bool Space_Colony::World_Module::Galaxy::operator==(const Galaxy & right) const {
	return name == right.name
		&& sectors == right.sectors;
}

bool Space_Colony::World_Module::Galaxy::operator!=(const Galaxy & right) const {
	return !operator==(right);
}
