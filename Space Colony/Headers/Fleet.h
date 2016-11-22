#pragma once

#include "Space Colony.h"
#include "TypeCounter.h"
#include "ShipType.h"
#include "ResourceType.h"
#include <string>
#include <stdexcept>
#include <vector>

namespace Space_Colony {

	/*
	A Fleet is a collection of counters of different and cargo ShipTypes.*/
	class Fleet {
	public:
		typedef TypeCounter ShipTypeCounter;
		typedef TypeCounter ResourceTypeCounter;

		static const size_t Cargo_Capacity_Exceeded = 1,
			Fuel_Capacity_Exceeded = 2,
			Invalid_Counter_Exception = 3;

		Fleet();
		Fleet(const Fleet &orig);
		Fleet(const faction_type fctn, const std::string &nm, const size_t fl,
			  const ShipTypeCounter &shps, const ResourceTypeCounter &crg);

		const ShipTypeCounter & getShips() const;
		ShipTypeCounter setShips(
			const ShipTypeCounter &shps, const ShipTypeVector &typs,
			const ResourceTypeVector &rsrc);
		const ResourceTypeCounter & getCargo() const;
		ResourceTypeCounter setCargo(
			const ResourceTypeCounter &crg, const ShipTypeVector &shps,
			const ResourceTypeVector &rsrc);
		/*
		Sets the counter for the passed type of ship and returns the old counter.*/
		size_t setShips(const size_t ship_type, const size_t val,
						const ShipTypeVector &shps, const ResourceTypeVector &rsrc);
		/*
		Sets the counter for the passed type of cargo and returns the old counter.*/
		size_t setCargo(const size_t resource_type, const size_t val,
						const ShipTypeVector &shps, const ResourceTypeVector &rsrc);
		/*
		Returns the range which this Fleet can travel before running out of fuel.*/
		double getRange(const ShipTypeVector &shps, const ResourceTypeVector &rsrc) const;
		/*
		Returns the average fuel efficiency of all the ships in this Fleet.*/
		double getFuelEfficiency(const ShipTypeVector &shps) const;
		/*
		Returns the cumulative fuel capacity of this Fleet.*/
		size_t getFuelCapacity(const ShipTypeVector &shps) const;
		/*
		Returns the fuel in this Fleet.*/
		size_t getFuel() const;
		/*
		Returns the old fuel value and sets the internal value.*/
		size_t setFuel(const size_t fl, const ShipTypeVector &shps);
		/*
		Returns the old fuel value and increments the internal value.*/
		size_t incFuel(const __int32 inc, const ShipTypeVector &shps);
		/*
		Returns the cumulative cargo capacity(volume units) of this Fleet.*/
		size_t getCargoCapacity(const ShipTypeVector &shps) const;
		/*
		Returns the volume of all the cargo in this Fleet.*/
		size_t getCargoVolume(const ResourceTypeVector &rsrc) const;
		/*
		Returns the mass of all the cargo in this Fleet.*/
		size_t getCargoMass(const ResourceTypeVector &rsrc) const;
		/*
		Returns the cumulative mass of all the Ships in this Fleet.*/
		size_t getShipMass(const ShipTypeVector &shps) const;
		/*
		Returns the mass of all the cargo and Ships in this Fleet.*/
		size_t getFleetMass(const ShipTypeVector &shps, const ResourceTypeVector &rsrc) const;

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
		ShipTypeCounter ships;
		/*
		A count of the quantity of different types of cargo contained within
		this Fleet.*/
		ResourceTypeCounter cargo;

	};

	typedef std::vector<Fleet> FleetVector;

}
