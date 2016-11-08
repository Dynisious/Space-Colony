#pragma once

#include "Space Colony.h"
#include "ShipType.h"
#include "TypeCounter.h"
#include "ResourceType.h"
#include <string>
#include <stdexcept>

namespace Space_Colony {

	/*
	A Fleet is a collection of counters of different Ship Types.*/
	class Fleet {
	public:
		Fleet();
		Fleet(const Fleet &orig);
		Fleet(const Fleet &orig, const faction_type fctn);
		Fleet(const faction_type fctn, const TypeCounter & shps, const TypeCounter & crg, const std::string & nm);

		/*
		Returns the ship counters whose types have and exclude the passed tags.*/
		TypeCounter getShipsByTags(const ShipType::RollTagSet &tags, const ShipType::RollTagSet &exclude) const;
		/*
		Returns all the ship counters for this Fleet.*/
		const TypeCounter & getShips() const;
		/*
		Returns the old counters and sets the internal counters.*/
		TypeCounter setShips(const TypeCounter & shps);
		/*
		Returns the old counter and sets the internal counter.*/
		size_t setShip(const __int32 type, const size_t val, size_t *const returned_fuel = nullptr);
		/*
		Returns the range which this Fleet can travel before running out of fuel.*/
		double getRange() const;
		/*
		Returns the cumulative role tags of all the Ship Types of this Fleet.*/
		ShipType::RollTagSet getRollTags() const;
		/*
		Returns the cumulative fuel effeciency of all the Ships.*/
		double getFuelEffeciency() const;
		/*
		Returns the cumulative fuel capacity of this Fleet.*/
		size_t getFuelCapacity() const;
		/*
		Returns the fuel in this Fleet.*/
		size_t getFuel() const;
		/*
		Returns the old fuel value and sets the internal value.*/
		size_t setFuel(size_t fl);
		/*
		Returns the old fuel value and increments the internal value.*/
		size_t incFuel(__int32 fl);
		/*
		Returns the cumulative cargo capacity of this Fleet.*/
		size_t getCargoCapacity() const;
		/*
		Returns the volume of all the cargo in this Fleet.*/
		size_t getCargoVolume() const;
		/*
		Returns the mass of all the cargo in this Fleet.*/
		size_t getCargoMass() const;
		/*
		Returns the mass of all the cargo and Ships in this Fleet.*/
		size_t getFleetMass() const;
		/*
		Returns all the cargo in this Fleet.*/
		const TypeCounter & getCargo() const;
		/*
		Returns the old cargo and sets the internal cargo.*/
		TypeCounter setCargo(const TypeCounter & crg);
		/*
		Returns the old value and sets the internal value.*/
		size_t setCargo(const __int32 crg, const __int32 vl);
		/*
		Returns the old cargo value and increments the internal cargo.*/
		size_t incCargo(const __int32 crg, const __int32 vl);

		/*
		The alignment of this Fleet within the game.*/
		faction_type faction;
		/*
		A String representing the name of this Fleet.*/
		std::string name;

		Fleet & operator=(const Fleet &right);
		bool operator==(const Fleet &right) const;
		bool operator!=(const Fleet &right) const;

	private:
		/*
		The amount of fuel the Fleet has.*/
		size_t fuel;
		/*
		A count of the number of Ships of a particular type within this Fleet.*/
		TypeCounter ships;
		/*
		A count of the quantity of different types of cargo contained within
		this Fleet.*/
		TypeCounter cargo;

	};

}
