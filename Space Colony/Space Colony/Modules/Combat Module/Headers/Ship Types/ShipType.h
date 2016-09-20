#pragma once

#include "Ship Types.h"
#include "ShipType Stats.h"
#include <string>
#include <Ships\Ships.h>

namespace Combat_Module {

	namespace Ship_Types {

		/*
		Holds the stats for a type of Ship in the combat module.*/
		class ShipType {
		public:
			/*
			The name for a ShipType, this name can also be used to group together ShipTypes.*/
			typedef std::string name_str;

			ShipType();
			ShipType(const ShipType& orig);
			ShipType(const ShipType& orig, const Space_Colony::Ships::Type_ID id);
			ShipType(const name_str& nm, const ShipType_Stats& sts,
					 const Space_Colony::Ships::Type_ID id);

			ShipType_Stats const& get_stats();
			const ShipType_Stats& get_stats() const;
			const name_str& get_name() const;
			Space_Colony::Ships::Type_ID get_ID() const;

			/*
			Returns true if there is a descrepency between the IDs and by value
			equivilance of these two ShipTypes.*/
			bool discrepency(const ShipType& type);
			/*
			Returns True if these types are equal by value alone, ID's are not
			compared.*/
			bool valueEquals(const ShipType& type);

			ShipType& operator=(const ShipType& orig);
			bool operator==(const ShipType& type);
			bool operator!=(const ShipType& type);

			__declspec(property(get = get_stats)) ShipType_Stats _stats;
			__declspec(property(get = get_name)) name_str _name;
			__declspec(property(get = get_ID)) Space_Colony::Ships::Type_ID _ID;

		private:
			/*
			The string name of this ShipType.*/
			name_str name;
			/*
			The stats of a ShipType.*/
			ShipType_Stats stats;
			/*
			The ID of this ShipType.*/
			Space_Colony::Ships::Type_ID ID;

		};

		/*
		Returns true if getting the ShipType corresponding to the passed ID
		was successful.*/
		bool getShipType_ByID(const Space_Colony::Ships::Type_ID ID, ShipType& type);

	}

}