#include "Fleet.h"

using namespace Space_Colony;

Space_Colony::Fleet::Fleet()
	: Fleet(Game_Factions::no_faction, "Unnamed Fleet", 0, 0, 0) {}

Space_Colony::Fleet::Fleet(const Fleet & orig)
	: Fleet(orig.faction, orig.name, orig.fuel, orig.ships, orig.cargo) {}

Space_Colony::Fleet::Fleet(const faction_type fctn, const std::string & nm,
						   const size_t fl, const ShipTypeCounter & shps,
						   const ResourceTypeCounter & crg)
	: faction(fctn), name(nm), fuel(fl), ships(shps), cargo(crg) {}

const Fleet::ShipTypeCounter & Space_Colony::Fleet::getShips() const {
	return ships;
}

Fleet::ShipTypeCounter Space_Colony::Fleet::setShips(
	const ShipTypeCounter & shps, const ShipTypeVector &typs,
	const ResourceTypeVector &rsrc) {
	//Save the ships as the result.
	ShipTypeCounter res(ships);
	if (!shps.isPos())
		//If the new counter is not positive throw an error.
		throw Invalid_Counter_Exception;
	else {
		//Assign the new ships.
		ships = shps;
		//Check if the new cargo capacity is bellow the cargo volume.
		if (getCargoCapacity(typs) < getCargoVolume(rsrc)) {
			//If the new capacity is less than the volume...
			//Reset the ships counter.
			ships = res;
			//Throw an error.
			throw Cargo_Capacity_Exceeded;
			//Check if the new fuel capacity is bellow the fuel quantity.
		} else if (getFuelCapacity(typs) < fuel) {
			//If the new capacity is less than the fuel quantity...
			//Reset the ships counter.
			ships = res;
			//Throw an error.
			throw Fuel_Capacity_Exceeded;
		}
	}
	//Return the old ships counter.
	return res;
}

const Fleet::ResourceTypeCounter & Space_Colony::Fleet::getCargo() const {
	return cargo;
}

Fleet::ResourceTypeCounter Space_Colony::Fleet::setCargo(
	const ResourceTypeCounter & crg, const ShipTypeVector & shps,
	const ResourceTypeVector & rsrc) {
	//Save the cargo as the result.
	ResourceTypeCounter res(cargo);
	if (!crg.isPos())
		//If the new counter is not positive throw an error.
		throw Invalid_Counter_Exception;
	else {
		//Assign the new cargo.
		cargo = crg;
		//Check if the cargo capacity is bellow the new cargo volume.
		if (getCargoCapacity(shps) < getCargoVolume(rsrc)) {
			//If the new capacity is less than the volume...
			//Reset the ships counter.
			cargo = res;
			//Throw an error.
			throw Cargo_Capacity_Exceeded;
		}
	}
	//Return the old cargo counter.
	return res;
}

size_t Space_Colony::Fleet::setShips(const size_t key, const size_t val,
									 const ShipTypeVector & shps, const ResourceTypeVector & rsrc) {
	//Save the ship counter as the result.
	size_t res(ships.getCounter(key));
	//Set the new ship counter.
	ships.setCounter(key, val);
	//Check if the cargo capacity is bellow the new cargo volume.
	if (getCargoCapacity(shps) < getCargoVolume(rsrc)) {
		//If the new capacity is less than the volume...
		//Reset the ship counter.
		ships.setCounter(key, res);
		//Throw an error.
		throw Cargo_Capacity_Exceeded;
		//Check if the fuel capacity is bellow the new fuel quantity.
	} else if (getFuelCapacity(shps) < fuel) {
		//If the capacity is less than the new fuel quantity...
		//Reset the ships counter.
		ships.setCounter(key, res);
		//Throw an error.
		throw Fuel_Capacity_Exceeded;
	}
	//Return the old ship counter.
	return res;
}

size_t Space_Colony::Fleet::setCargo(const size_t key, const size_t val,
									 const ShipTypeVector & shps, const ResourceTypeVector & rsrc) {
	//Save the cargo counter as the result.
	size_t res(cargo.getCounter(key));
	//Set the new cargo counter.
	cargo.setCounter(key, val);
	//Check if the new cargo capacity is bellow the cargo volume.
	if (getCargoCapacity(shps) < getCargoVolume(rsrc)) {
		//If the new capacity is less than the volume...
		//Reset the cargo counter.
		cargo.setCounter(key, res);
		//Throw an error.
		throw Cargo_Capacity_Exceeded;
	}
	//Return the old cargo counter.
	return res;
}

double Space_Colony::Fleet::getRange(const ShipTypeVector & shps, const ResourceTypeVector & rsrc) const {
	//Return the fuel quantity divided by the fuel consumption per range unit.
	return fuel / (
		//Fuel consumption per range unit = Mass-Of-Fleet x Units-Of-Fuel-Per-Mass-Unit
		getFleetMass(shps, rsrc) * getFuelEfficiency(shps));
}

double Space_Colony::Fleet::getFuelEfficiency(const ShipTypeVector & shps) const {
	//Create a 0 fuel efficiency as a result.
	double res(0);
	//Iterate all ship types.
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Add the sum of fuel efficiencies of all the ships of this type.
		res += shps.at(iter->first).world.fuelEfficiency * iter->second;
	//Return the average fuel efficiency of this Fleet.
	return res / ships.sum();
}

size_t Space_Colony::Fleet::getFuelCapacity(const ShipTypeVector & shps) const {
	//Create a 0 fuel capacity as a result.
	size_t res(0);
	//Iterate all ship types.
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Add the sum of fuel capacity of all the ships of this type.
		res += shps.at(iter->first).world.fuelCapacity * iter->second;
	//Return the total fuel capacity of this Fleet.
	return res;
}

size_t Space_Colony::Fleet::getFuel() const {
	return fuel;
}

size_t Space_Colony::Fleet::setFuel(const size_t fl, const ShipTypeVector & shps) {
	//Save the fuel value as a result.
	size_t res(fuel);
	//Check if the new fuel value is greater than the fuel capacity.
	if (getFuelCapacity(shps) < fl)
		//Throw an error.
		throw Fuel_Capacity_Exceeded;
	//Set the new fuel value.
	fuel = fl;
	//Return the old fuel value.
	return res;
}

size_t Space_Colony::Fleet::incFuel(const __int32 inc, const ShipTypeVector & shps) {
	//Set the fuel to the current fuel plus the increment.
	return setFuel(fuel + inc, shps);
}

size_t Space_Colony::Fleet::getCargoCapacity(const ShipTypeVector & shps) const {
	//Create a 0 capacity as a result.
	size_t res(0);
	//Iterate all ship types.
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Add the sum of all cargo capaicty for the ships of this ship type.
		res += shps.at(iter->first).world.cargoCapacity * iter->second;
	//Return the total cargo capacity for this Fleet.
	return res;
}

size_t Space_Colony::Fleet::getCargoVolume(const ResourceTypeVector & rsrc) const {
	//Create a 0 volume as a result.
	size_t res(0);
	//Iterate all cargo types.
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		//Add the sum volume of all the cargo units of this type.
		res += rsrc.at(iter->first).volume * iter->second;
	//Return the total cargo volume for this Fleet.
	return res;
}

size_t Space_Colony::Fleet::getCargoMass(const ResourceTypeVector & rsrc) const {
	//Create a 0 mass as a result.
	size_t res(0);
	//Iterate all cargo types.
	for (auto iter(cargo.begin()), end(cargo.end()); iter != end; ++iter)
		//Add the sum mass of all the cargo units of this type.
		res += rsrc.at(iter->first).mass * iter->second;
	//Return the total cargo mass for this Fleet.
	return res;
}

size_t Space_Colony::Fleet::getShipMass(const ShipTypeVector & shps) const {
	//Create a 0 mass as a result.
	size_t res(0);
	//Iterate all ship types.
	for (auto iter(ships.begin()), end(ships.end()); iter != end; ++iter)
		//Add the sum mass of all the ships of this type.
		res += shps.at(iter->first).world.mass * iter->second;
	//Return the total ship mass for this Fleet.
	return res;
}

size_t Space_Colony::Fleet::getFleetMass(const ShipTypeVector & shps, const ResourceTypeVector & rsrc) const {
	//Return the sum of the ship mass and cargo mass of this Fleet.
	return getShipMass(shps) + getCargoMass(rsrc);
}

Fleet & Space_Colony::Fleet::operator=(const Fleet & right) {
	faction = right.faction;
	name = right.name;
	fuel = right.fuel;
	ships = right.ships;
	cargo = right.cargo;
	return *this;
}

bool Space_Colony::Fleet::operator==(const Fleet & right) const {
	return faction == right.faction
		&& name == right.name
		&& fuel == right.fuel
		&& ships == right.ships
		&& cargo == right.cargo;
}

bool Space_Colony::Fleet::operator!=(const Fleet & right) const {
	return !operator==(right);
}
