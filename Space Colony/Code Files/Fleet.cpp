#include "Fleet.h"

using namespace Space_Colony;

Space_Colony::Fleet::Fleet()
	: faction(( faction_type ) Game_Factions::no_faction) {}

Space_Colony::Fleet::Fleet(const Fleet & orig)
	: Fleet(orig, orig.faction) {}

Space_Colony::Fleet::Fleet(const Fleet & orig, const faction_type fctn)
	: Fleet(orig.faction, orig.ships, orig.cargo, orig.name) {}

Space_Colony::Fleet::Fleet(const faction_type fctn, const TypeCounter & shps, const TypeCounter & crg, const std::string & nm)
	: name(nm), faction(fctn), ships(shps), cargo(crg) {}

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
		if ((getCargoCapacity() + (ShipType_get(type).world.cargo_capacity * ((( __int32 ) val) - res))) < cargo.sum())
			//The new capacity is less than the sum of the cargo
			throw std::exception("New ships would cause cargo capacity to exceed.");
		size_t retFuel(fuel * ShipType_get(type).world.fuel_capacity
					   * (res - val) / getFuelCapacity());
		if (returned_fuel != nullptr)
			*returned_fuel = retFuel;
		fuel -= retFuel;
	}
	ships.setCounter(type, val);
	return res;
}

double Space_Colony::Fleet::getRange() const {
	return fuel / (getFleetMass() * getFuelEffeciency());
}

ShipType::RollTagSet Space_Colony::Fleet::getRollTags() const {
	ShipType::RollTagSet res;
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		res.insert(ShipType_get(iter->first).world.rollTags.begin(), ShipType_get(iter->first).world.rollTags.end());
	return res;
}

double Space_Colony::Fleet::getFuelEffeciency() const {
	double res(0);
	size_t shipsSum(ships.sum());
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		res += ShipType_get(iter->first).world.fuel_efficiency * iter->second / shipsSum;
	return res;
}

size_t Space_Colony::Fleet::getFuelCapacity() const {
	size_t res(0);
	for (TypeCounter::const_iterator iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		res += ShipType_get(iter->first).world.fuel_capacity * iter->second;
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
		res += ShipType_get(iter->first).world.cargo_capacity * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getCargoVolume() const {
	size_t res(0);
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		res += ResourceType_get(iter->first).volume * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getCargoMass() const {
	size_t res(0);
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		res += ResourceType_get(iter->first).mass * iter->second;
	return res;
}

size_t Space_Colony::Fleet::getFleetMass() const {
	size_t res(0);
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		res += ShipType_get(iter->first).world.mass * iter->second;
	return res + getCargoMass();
}

const TypeCounter & Space_Colony::Fleet::getCargo() const {
	return cargo;
}

TypeCounter Space_Colony::Fleet::setCargo(const TypeCounter & crg) {
	TypeCounter res(cargo);
	cargo = crg;
	if (getCargoVolume() > getCargoCapacity()) {
		cargo = res;
		throw std::exception("The new cargo exceeds the capacity of the Fleet.");
	}
	return res;
}

size_t Space_Colony::Fleet::setCargo(const __int32 crg, const __int32 vl) {
	size_t res(cargo.getCounter(crg));
	cargo.setCounter(crg, vl);
	if (getCargoVolume() > getCargoCapacity()) {
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
