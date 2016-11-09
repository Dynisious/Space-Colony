#include "Fleet.h"
#include <unordered_set>

using namespace Space_Colony;

Space_Colony::FleetRef::FleetRef() {}

Space_Colony::FleetRef::FleetRef(Fleet *const inst)
	: instance(inst) {
	if (!check())
		throw std::exception("The pointer is invalid.");
}

bool Space_Colony::FleetRef::check() const {
	return Fleet::isPooled(instance);
}

FleetRef & Space_Colony::FleetRef::operator=(Fleet * const right) {
	instance = right;
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *this;
}

bool Space_Colony::FleetRef::operator==(Fleet * const right) const {
	if (!check() || !Fleet::isPooled(right))
		throw std::exception("The pointer is invalid.");
	return instance == right;
}

bool Space_Colony::FleetRef::operator!=(Fleet * const right) const {
	return !operator==(right);
}

Fleet & Space_Colony::FleetRef::operator*() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

const Fleet & Space_Colony::FleetRef::operator*() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return *instance;
}

Fleet * Space_Colony::FleetRef::operator->() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

const Fleet * Space_Colony::FleetRef::operator->() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::FleetRef::operator Fleet*() {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::FleetRef::operator const Fleet*() const {
	if (!check())
		throw std::exception("The pointer is invalid.");
	return instance;
}

Space_Colony::Fleet::Fleet()
	: faction(( faction_type ) Game_Factions::no_faction) {}

Space_Colony::Fleet::Fleet(const Fleet & orig)
	: Fleet(orig, orig.faction) {}

Space_Colony::Fleet::Fleet(const Fleet & orig, const faction_type fctn)
	: Fleet(orig.faction, orig.ships, orig.cargo, orig.name) {}

Space_Colony::Fleet::Fleet(const faction_type fctn, const TypeCounter & shps, const TypeCounter & crg, const std::string & nm)
	: name(nm), faction(fctn), ships(shps), cargo(crg) {}

std::unordered_set<Fleet *> Pooled_Fleet_Pointers;

FleetRef Space_Colony::Fleet::createPooled() {
	FleetRef res(new Fleet());
	Pooled_Fleet_Pointers.insert(res);
	return res;
}

FleetRef Space_Colony::Fleet::createPooled(const Fleet & orig) {
	FleetRef res(new Fleet(orig));
	Pooled_Fleet_Pointers.insert(res);
	return res;
}

FleetRef Space_Colony::Fleet::createPooled(const Fleet & orig, const faction_type fctn) {
	FleetRef res(new Fleet(orig, fctn));
	Pooled_Fleet_Pointers.insert(res);
	return res;
}

FleetRef Space_Colony::Fleet::createPooled(const faction_type fctn, const TypeCounter & shps, const TypeCounter & crg, const std::string & nm) {
	FleetRef res(new Fleet(fctn, shps, crg, nm));
	Pooled_Fleet_Pointers.insert(res);
	return res;
}

bool Space_Colony::Fleet::isPooled(Fleet * const ptr) {
	return Pooled_Fleet_Pointers.count(ptr) != 0;
}

bool Space_Colony::Fleet::deleteFleet(Fleet * const ptr) {
	return Pooled_Fleet_Pointers.erase(ptr) != 0;
}

TypeCounter Space_Colony::Fleet::getShipsByTags(const ShipType::RollTagSet & tags, const ShipType::RollTagSet & exclude) const {
	TypeCounter res(ships);
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter) {
		for (auto tag_iter(tags.begin()), tag_end(tags.end()); tag_iter != tag_end; ++tag_iter)
			//Check all include tags.
			if (ShipType::getType(iter->first).world.rollTags.count(*tag_iter) == 0) {
				//This tag is not included.
				res.setCounter(iter->first, 0);
				break;
			}
		if (res.getCounter(iter->first) == 0)
			//This type has already been removed.
			for (auto exclude_iter(tags.begin()), exclude_end(tags.end()); exclude_iter != exclude_end; ++exclude_iter)
				//Check all include tags.
				if (ShipType::getType(iter->first).world.rollTags.count(*exclude_iter) != 0) {
					//This tag is not included.
					res.setCounter(iter->first, 0);
					break;
				}
	}
	return res;
}

const TypeCounter & Space_Colony::Fleet::getShips() const {
	return ships;
}

TypeCounter Space_Colony::Fleet::setShips(const TypeCounter & shps) {
	TypeCounter res(ships);
	ships = shps;
	if (getCargoCapacity() < getCargoVolume()) {
		//The new capacity is less than the sum of the cargo
		ships = res;
		throw std::exception("New ships cause cargo capacity to exceed.");
	}
	if (getFuelCapacity() < fuel) {
		//The new capacity is less than the sum of the cargo
		ships = res;
		throw std::exception("New ships cause fuel capacity to exceed.");
	}
	return res;
}

size_t Space_Colony::Fleet::setShip(const __int32 type, const size_t val, size_t *const returned_fuel) {
	size_t res(ships.getCounter(type));
	if (val < res) {
		//ships are going down.
		if ((getCargoCapacity() + (ShipType::getType(type).world.cargo_capacity * ((( __int32 ) val) - res))) < cargo.sum())
			//The new capacity is less than the sum of the cargo
			throw std::exception("New ships would cause cargo capacity to exceed.");
		//Calculate the amount of fuel the removed Ships take with them.
		size_t retFuel(fuel * ShipType::getType(type).world.fuel_capacity
					   * (res - val) / getFuelCapacity());
		if (returned_fuel != nullptr)
			//Return the fuel.
			*returned_fuel = retFuel;
		//Remove the fuel.
		fuel -= retFuel;
	}
	//Set the counter for the ShipType.
	ships.setCounter(type, val);
	return res;
}

double Space_Colony::Fleet::getRange() const {
	return fuel / (getFleetMass() * getFuelEffeciency());
}

ShipType::RollTagSet Space_Colony::Fleet::getRollTags() const {
	ShipType::RollTagSet res;
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Iterate over all counters and add their tags to the return set.
		res.insert(ShipType::getType(iter->first).world.rollTags.begin(), ShipType::getType(iter->first).world.rollTags.end());
	return res;
}

double Space_Colony::Fleet::getFuelEffeciency() const {
	double res(0);
	//The total number of Ships in this Fleet.
	double shipsSum(ships.sum());
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Iterate each ShipType and add it's fuel efficiency proportional
		//to it's proportion of the Fleet.
		res += ShipType::getType(iter->first).world.fuel_efficiency * iter->second / shipsSum;
	return res;
}

size_t Space_Colony::Fleet::getFuelCapacity() const {
	size_t res(0);
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Iterate each ShipType and add the fuel capacity of all the ships of that type.
		res += ShipType::getType(iter->first).world.fuel_capacity * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getFuel() const {
	return fuel;
}

size_t Space_Colony::Fleet::setFuel(size_t fl) {
	size_t res(fuel);
	if (fl > getFuelCapacity())
		throw std::exception("The new fuel exceeds the fuel capacity.");
	fuel = fl;
	return res;
}

size_t Space_Colony::Fleet::incFuel(__int32 fl) {
	return setFuel(fuel + fl);
}

size_t Space_Colony::Fleet::getCargoCapacity() const {
	size_t res(0);
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Iterate each ShipType and add the cargo capacity of all the ships of that type.
		res += ShipType::getType(iter->first).world.cargo_capacity * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getCargoVolume() const {
	size_t res(0);
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		//Iterate each ResourceType and add the volume of all the cargo of that type.
		res += ResourceType_get(iter->first).volume * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getCargoMass() const {
	size_t res(0);
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		//Iterate each ResourceType and add the mass of all the cargo of that type.
		res += ResourceType_get(iter->first).mass * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getFleetMass() const {
	size_t res(0);
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Iterate each ShipType and add the mass of all the ships of that type.
		res += ShipType::getType(iter->first).world.mass * iter->second;
	//Return the mass of all the Ships and the cargo combined.
	return res + getCargoMass();
}

const TypeCounter & Space_Colony::Fleet::getCargo() const {
	return cargo;
}

TypeCounter Space_Colony::Fleet::setCargo(const TypeCounter & crg) {
	TypeCounter res(cargo);
	cargo = crg;
	if (getCargoVolume() > getCargoCapacity()) {
		//Reset the cargo.
		cargo = res;
		throw std::exception("The new cargo exceeds the capacity of the Fleet.");
	}
	return res;
}

size_t Space_Colony::Fleet::setCargo(const __int32 crg, const __int32 vl) {
	size_t res(cargo.getCounter(crg));
	//Set the new cargo.
	cargo.setCounter(crg, vl);
	if (getCargoVolume() > getCargoCapacity()) {
		//Reset the cargo.
		cargo.setCounter(crg, res);
		throw std::exception("The new cargo exceeds the capacity of the Fleet.");
	}
	return res;
}

size_t Space_Colony::Fleet::incCargo(const __int32 crg, const __int32 vl) {
	return setCargo(crg, cargo.getCounter(crg) + vl);
}

Fleet & Space_Colony::Fleet::operator=(const Fleet & right) {
	name = right.name;
	fuel = right.fuel;
	faction = right.faction;
	ships = right.ships;
	cargo = right.cargo;
	return *this;
}

bool Space_Colony::Fleet::operator==(const Fleet & right) const {
	return (this == &right)
		|| (name == right.name
			&& fuel == right.fuel
			&& faction == right.faction
			&& ships == right.ships
			&& cargo == right.cargo);
}

bool Space_Colony::Fleet::operator!=(const Fleet & right) const {
	return !operator==(right);
}
