#include "World Module\Headers\Galactic\StarSector.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galactic;

Space_Colony::World_Module::Galactic::StarSector::StarSector()
	: name("Unnamed StarSector"), systems(0) {}

Space_Colony::World_Module::Galactic::StarSector::StarSector(const StarSector & orig)
	: StarSector(orig.name, orig.systems) {}

Space_Colony::World_Module::Galactic::StarSector::StarSector(
	const std::string & nm, const SystemVector & systms)
	: name(nm), systems(systms) {}

faction_type Space_Colony::World_Module::Galactic::StarSector::getFaction(const FleetVector &flts) const {
	//Get the faction of the first solar system.
	faction_type res(systems.front().getFaction(flts));
	//Create iterators for the remaining solar systems.
	auto iter(++systems.begin()), end(systems.end());
	//Check whether the current faction is assigned to a faction.
	if (res <= Game_Factions::player)
		//If the current faction is not assigned to a faction...
		//Iterate the remaining solar systems.
		for (; iter != end; ++iter) {
			//Retrieve the next faction.
			res = iter->getFaction(flts);
			//Check whether this faction is assigned to a faction.
			if (res >= Game_Factions::player)
				//If the current faction is assigned to a faction,
				//break out of the loop.
				break;
		}
	//Iterate the remaining solar systems.
	for (; iter != end; ++iter)
		//Check whether the factions differ...
		if (iter->getFaction(flts) != res
			//And whether the faction is not an unassigned faction.
			&& iter->getFaction(flts) != Game_Factions::no_faction) {
			//Check whether the faction is conflicted.
			if (iter->getFaction(flts) == Game_Factions::conflicted)
				//If the faction is conflicted, return conflicted.
				return Game_Factions::conflicted;
			else
				//Set the result to be mixed.
				res = Game_Factions::mixed;
		}
	//Return the resulting faction.
	return res;
}

TypeCounter Space_Colony::World_Module::Galactic::StarSector::getResources() const {
	//Get the resources for the first solar system as the result.
	TypeCounter res(systems.front().getResources());
	//Iterate the remaining solar systems.
	for (auto iter(++systems.begin()), end(systems.end()); iter != end; ++iter)
		//Accumulate the resources from the next solar system
		//to the result.
		res += iter->getResources();
	//Return the cummulative resources.
	return res;
}

size_t Space_Colony::World_Module::Galactic::StarSector::getResource(const size_t resource_type) const {
	//Get the resource value for the first solar system as the result.
	size_t res(systems.front().getResource(resource_type));
	//Iterate the remaining solar systems.
	for (auto iter(++systems.begin()), end(systems.end()); iter != end; ++iter)
		//Accumulate the resource from the next solar system to the result.
		res += iter->getResource(resource_type);
	//Return the cummulative resource.
	return res;
}

void Space_Colony::World_Module::Galactic::StarSector::iterate(const FleetVector &flts, const ConstructTypeVector &cnstrcts) {
	//Iterate all solar systems.
	for (auto iter(systems.begin()), end(systems.end()); iter != end; ++iter)
		//Perform an iteration on this solar system.
		iter->iterate(flts, cnstrcts);
}

StarSector & Space_Colony::World_Module::Galactic::StarSector::operator=(const StarSector & right) {
	name = right.name;
	systems = right.systems;
	return *this;
}

bool Space_Colony::World_Module::Galactic::StarSector::operator==(const StarSector & right) const {
	return name == right.name
		&& systems == right.systems;
}

bool Space_Colony::World_Module::Galactic::StarSector::operator!=(const StarSector & right) const {
	return !operator==(right);
}
