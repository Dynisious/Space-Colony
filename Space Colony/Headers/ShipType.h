#pragma once

#include "Space Colony.h"
#include "TypeCounter.h"
#include "CombatStats.h"
#include <string>
#include <vector>

namespace Space_Colony {

	/*
	A Ship Type denotes the stats and identifying characteristics of a ship which
	defines how it behaves and the functionality it provides.*/
	class ShipType {
	public:
		struct WorldStats {
			WorldStats();
			WorldStats(const WorldStats &orig);
			WorldStats(const TypeCounter &rsrcCst, const size_t ms,
					   const size_t flCpcty, const double flEfcncy,
					   const size_t crgCpcty, const std::string &nm);

			/*
			The quantity of each resource which are required to construct a
			single ship of this type.*/
			TypeCounter resourceCost;
			/*
			The mass of this Ship type in mass units.*/
			size_t mass;
			/*
			The quantity of fuel this type of ship can carry.*/
			size_t fuelCapacity;
			/*
			Units of fuel this type of ship consumes per unit of mass.*/
			double fuelEfficiency;
			/*
			The number of cargo units(denoting volume of cargo) which can be
			stored in this Ship Type.*/
			size_t cargoCapacity;
			/*
			A String representing the name of this Ship Type.*/
			std::string name;

			WorldStats & operator=(const WorldStats &right);
			bool operator==(const WorldStats &right) const;
			bool operator!=(const WorldStats &right) const;

		} world;

		ShipType();
		ShipType(const ShipType &orig);
		ShipType(const CombatStats &cmbt, const WorldStats &wrld);

		CombatStats combat;

		ShipType & operator=(const ShipType &right);
		bool operator==(const ShipType &right) const;
		bool operator!=(const ShipType &right) const;

	};

	typedef std::vector<ShipType> ShipTypeVector;

}
