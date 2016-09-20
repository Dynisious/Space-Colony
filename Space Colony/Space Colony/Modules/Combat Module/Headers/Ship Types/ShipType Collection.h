#pragma once

#include "Ship Types.h"
#include "ShipType.h"
#include <unordered_map>
#include <list>

namespace Combat_Module {

	namespace Ship_Types {

		/*
		A double linked list of ShipTypes.*/
		typedef std::list<ShipType> ShipType_List;
		/*
		A vector of ShipTypes.*/
		typedef std::vector<ShipType> ShipType_Vector;
		/*
		An map of ShipTypes by their unique ID's.*/
		typedef std::unordered_map<Space_Colony::Ships::Type_ID, ShipType> ShipType_IdMap;
		/*
		A map of ShipType_Lists by the names of the ShipTypes.*/
		typedef std::unordered_map<ShipType::name_str, ShipType_List, std::hash<ShipType::name_str>> ShipTypes_NamedMap;
		/*
		A map of ShipType_Lists by the sizes of the ShipTypes.*/
		typedef std::unordered_map<ShipType_Stats::size_t, ShipType_List> ShipTypes_SizedMap;

		/*
		A maintained collection of unique ShipType objects.*/
		class ShipTypeCollection {
		public:
			ShipTypeCollection();
			ShipTypeCollection(const ShipTypeCollection& orig);

			/*
			Returns True if the type was loaded. Loading will fail if the type
			already exists.*/
			bool loadType(const ShipType& type);
			/*
			Returns true if the passed type was unloaded. Unloading will fail if
			the type does not exist.*/
			bool unloadType(const ShipType& type);
			/*
			Returns true if the type corresponding to the passed ID was unloaded.
			Unloading will fail if the type does not exist.*/
			bool unloadType(const Space_Colony::Ships::Type_ID ID);
			/*
			Returns True if a type was found and returned with the passed ID.*/
			bool getFromID(const Space_Colony::Ships::Type_ID ID, ShipType& type) const;
			/*
			Returns True if a types with the passed name were found and returned.*/
			bool getFromName(const ShipType::name_str name, ShipTypes_NamedMap::mapped_type& types) const;
			/*
			Returns True if a types with the passed size were found and returned.*/
			bool getFromSize(const ShipType_Stats::size_t size, ShipTypes_SizedMap::mapped_type& types) const;
			/*
			Changes the ID of the passed type if it was equal in value to a loaded
			type.*/
			void correctTypeID(ShipType& type) const;
			/*
			Returns the number of types loaded into this ShipTypeCollection.*/
			__int32 loadedTypes() const;
			/*
			Returns iterators to iterate over all ShipTypes by ID.*/
			void iterateByID(ShipType_IdMap::const_iterator& start, ShipType_IdMap::const_iterator& end);
			/*
			Returns iterators to iterate over all ShipTypes by Name.*/
			void iterateByName(ShipTypes_NamedMap::const_iterator& start, ShipTypes_NamedMap::const_iterator& end);
			/*
			Returns iterators to iterate over all ShipTypes by Size.*/
			void iterateBySize(ShipTypes_SizedMap::const_iterator& start, ShipTypes_SizedMap::const_iterator& end);

		private:
			/*
			All loaded ShipTypes mapped by their ID.*/
			ShipType_IdMap ShipTypes_ByID;
			/*
			All loaded ShipTypes grouped by their Names.*/
			ShipTypes_NamedMap ShipTypes_ByName;
			/*
			All loaded ShipTypes grouped by their Sizes.*/
			ShipTypes_SizedMap ShipTypes_BySize;

		};

		/*
		Returns iterators for every ShipType by ID.*/
		void iterateShipTypes_ByID(ShipType_IdMap::const_iterator& start, ShipType_IdMap::const_iterator& end);

	}

}
