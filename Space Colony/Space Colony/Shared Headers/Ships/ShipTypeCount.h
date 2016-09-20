#pragma once

#include "Ships.h"
#include <unordered_map>

namespace Space_Colony {

	namespace Ships {

		/*
		A count for different ShipTypes recalled by ID.*/
		class ShipTypeCount {
		public:
			/*
			A map of ints with ShipType_IDs as keys.*/
			typedef std::unordered_map<Type_ID, __int32> ShipTypeCounterMap;

			ShipTypeCount();
			ShipTypeCount(const ShipTypeCount& orig);

			/*
			Shift the counter of the passed ID. The counter will not go negative.*/
			void offsetCounter(const Type_ID ID, const __int32 change);
			/*
			Sets the counter of the passed ID to the specified value. The counter
			will not go negative.*/
			void setCounter(const Type_ID ID, const unsigned __int32 val);
			/*
			Returns the counter of the passed ID.*/
			__int32 getCounter(const Type_ID ID) const;
			/*
			Returns iterators over each ID in this ShipTypeCount.*/
			void iterateByID(ShipTypeCounterMap::const_iterator& start, ShipTypeCounterMap::const_iterator& end) const;
			/*
			Returns True if the value for the passed key was erased.*/
			bool erase(Type_ID ID);
			
			ShipTypeCount& operator=(const ShipTypeCount& orig);
			bool operator==(const ShipTypeCount& orig) const;
			bool operator!=(const ShipTypeCount& orig) const;
			ShipTypeCount& operator+=(const ShipTypeCount& right);
			ShipTypeCount operator+(const ShipTypeCount& right) const;

		private:
			/*
			The counters of each type.*/
			ShipTypeCounterMap ships;

		};

	}

}
