#include "World Module\Headers\Galactic\StarSector.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module::Galacitc;

Space_Colony::World_Module::Galacitc::StarSector::StarSector() {}

Space_Colony::World_Module::Galacitc::StarSector::StarSector(const StarSector & orig)
	: StarSector(orig.name, orig.systems) {}

Space_Colony::World_Module::Galacitc::StarSector::StarSector(const std::string & nm, const SystemVector & systms)
	: name(nm), systems(systms) {}

SolarSystem & Space_Colony::World_Module::Galacitc::StarSector::getSolarSystem(const size_t index) {
	return systems[index];
}

const SolarSystem & Space_Colony::World_Module::Galacitc::StarSector::getSolarSystem(const size_t index) const {
	return systems[index];
}

faction_type Space_Colony::World_Module::Galacitc::StarSector::getFaction() const {
	faction_type res(systems.front().getFaction());
	auto iter(++systems.begin()), end(systems.end());
	for (; (res == ( faction_type ) Game_Factions::no_faction) && iter != end; ++iter)
		res = iter->getFaction();
	if (res == ( faction_type ) Game_Factions::contested)
		return ( faction_type ) Game_Factions::contested;
	for (; iter != end; ++iter)
		if (iter->getFaction() == ( faction_type ) Game_Factions::contested)
			return ( faction_type ) Game_Factions::contested;
		else if (res != iter->getFaction() && (iter->getFaction() != ( faction_type ) Game_Factions::no_faction))
			return ( faction_type ) Game_Factions::mixed;
	return res;
}

TypeCounter Space_Colony::World_Module::Galacitc::StarSector::getResources() const {
	TypeCounter res(systems.front().getResources());
	for (auto iter(++systems.begin()), end(systems.end()); iter != end; ++iter)
		res += iter->getResources();
	return res;
}

size_t Space_Colony::World_Module::Galacitc::StarSector::getResource(const __int32 rsrc) const {
	size_t res(systems.front().getResource(rsrc));
	for (auto iter(++systems.begin()), end(systems.end()); iter != end; ++iter)
		res += iter->getResource(rsrc);
	return res;
}

void Space_Colony::World_Module::Galacitc::StarSector::iterate() {
	for (auto iter(systems.begin()), end(systems.end()); iter != end; ++iter)
		iter->iterate();
}

StarSector & Space_Colony::World_Module::Galacitc::StarSector::operator=(const StarSector & right) {
	name = right.name;
	systems = right.systems;
	return *this;
}

bool Space_Colony::World_Module::Galacitc::StarSector::operator==(const StarSector & right) const {
	return (this == &right)
		|| (name == right.name
			&& systems == right.systems);
}

bool Space_Colony::World_Module::Galacitc::StarSector::operator!=(const StarSector & right) const {
	return !operator==(right);
}

Space_Colony::World_Module::Galacitc::StarSector::operator SystemVector & () {
	return systems;
}

Space_Colony::World_Module::Galacitc::StarSector::operator const SystemVector & () const {
	return systems;
}
