#pragma once

#include "Space Colony.h"
#include "TypeCounter.h"
#include <string>
#include <xhash>
#include <unordered_set>

namespace Space_Colony {

	enum class ShipType_RoleTag : __int32;
	class ShipType;
	typedef const ShipType *const ShipType_Pointer;
	typedef __int32 ShipType_ID;

	/*
	A Ship Type denotes the stats and identifying characteristics of a ship
	which defines how it behaves and the functionality it provides.*/
	class ShipType {
	public:
		typedef std::unordered_set<ShipType_RoleTag> RollTagSet;

		ShipType();
		ShipType(const ShipType &orig);

		static bool isLoaded(ShipType_ID id);
		static const ShipType & getType(ShipType_ID id);
		static ShipType_ID loadType(const ShipType &type);
		static bool unloadType(ShipType_ID id);

		struct CombatStats {
			CombatStats();
			CombatStats(const CombatStats &orig);

			/*
			Chance whether a successful hit glances off the armour of a ship
			causing 1 damage for the glance.*/
			double glance;
			/*
			Chance whether this ship type can evade an attack.*/
			double evade;
			/*
			The size of this ship type.*/
			size_t size;
			/*
			The smallest size of ship this ship type can target.*/
			size_t target_min;
			/*
			The largest size of ship this ship type can damage.*/
			size_t target_max;
			/*
			The number of attacks that this ship type can launch at once.*/
			size_t attacks;
			/*
			Chance whether each attack this ship type launches will hit it's target.*/
			double accuracy;

			CombatStats & operator=(const CombatStats &right);
			bool operator==(const CombatStats &right) const;
			bool operator!=(const CombatStats &right) const;

		} combat;
		struct WorldStats {
			WorldStats();
			WorldStats(const WorldStats &orig);

			/*
			A String representing the name of this Ship Type.*/
			std::string name;
			/*
			The quantity of each resource which are required to construct a single
			ship of this type.*/
			TypeCounter cost;
			/*
			The mass of this Ship type in mass units.*/
			size_t mass;
			/*
			The distance units which this ShipType travels per tick.*/
			size_t speed;
			/*
			The quantity of fuel this type of ship can carry.*/
			size_t fuel_capacity;
			/*
			Units of fuel this type of ship consumes per unit of mass.*/
			size_t fuel_efficiency;
			/*
			The number of cargo units(denoting volume of cargo) which can be stored
			in this Ship Type.*/
			size_t cargo_capacity;
			/*
			A collection of tags denoting the roll of this Ship Type in the fleet
			outside of combat.*/
			RollTagSet rollTags;

			WorldStats & operator=(const WorldStats &right);
			bool operator==(const WorldStats &right) const;
			bool operator!=(const WorldStats &right) const;

		} world;

		ShipType operator=(const ShipType &right);
		bool operator==(const ShipType &right) const;
		bool operator!=(const ShipType &right) const;

	};

	enum class ShipType_RoleTag : __int32 {
		Orbital_Bombardment = 0,
		Ground_Invasion = 1,
		Ship_Transport = 2,
		Scanning = 3,
		maximum = 4
	};

}
