#pragma once

#include "Ships.h"
#include "ShipTypeCount.h"

namespace Space_Colony {

	namespace Ships {

		/*
		A Fleet is a collection of Ships aligned with a particular faction.*/
		class Fleet {
		public:
			Fleet();
			Fleet(const Fleet& orig);
			Fleet(const Space_Colony::faction_t fac, const ShipTypeCount& shps);

			ShipTypeCount& get_Ships();
			const ShipTypeCount& get_Ships() const;

			__declspec(property(get = get_Ships)) ShipTypeCount _ships;

			/*
			A faction alignment for the Ships in this Fleet.*/
			Space_Colony::faction_t faction;

		private:
			/*
			The number of Ships of different ShipTypes currently in this Fleet.*/
			ShipTypeCount ships;

		};

		typedef std::list<Space_Colony::Ships::Fleet> FleetList;
		typedef std::vector<Space_Colony::Ships::Fleet> FleetVector;

	}
}
