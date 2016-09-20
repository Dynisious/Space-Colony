#pragma once

#include "Ship Types.h"
#include <stdexcept>

namespace Combat_Module {

	namespace Ship_Types {

		/*
		A collections of statuses which describe a ShipType.*/
		struct ShipType_Stats {
		public:
			/*
			The value used for the size of a ShipType.*/
			typedef __int32 size_t;
			/*
			The type used for a chance value.*/
			typedef __int32 chance_t;

			ShipType_Stats();
			ShipType_Stats(const ShipType_Stats& orig);
			ShipType_Stats(__int32 htPnts, chance_t vdChnc, chance_t dflctChnc,
						   chance_t htChnc, __int32 ttcksCnt, size_t szVl,
						   size_t mnSz, size_t mxSz);

			/*
			The number of attacks this ShipType can suffer before becoming at risk
			of destruction.*/
			__int32 hitPoints;
			/*
			The percentage chance that this ShipType can evade an oncomming attack.*/
			chance_t evadeChance;
			/*
			The percentage chance that a ShipType will deflect a landed attack.*/
			chance_t deflectChance;
			/*
			The percentage chance that each of this ShipTypes attacks will
			successfully land on a target.*/
			chance_t hitChance;
			/*
			The number of attacks that this ShipType can launch at once.*/
			__int32 attacksCount;
			/*
			The size value of this ShipType.*/
			size_t sizeValue;
			/*
			The smallest type of ship this ShipType can attack.*/
			size_t minSize;
			/*
			The largest type of ShipType this ShipType can attack.*/
			size_t maxSize;

			bool operator==(const ShipType_Stats& stats);
			bool operator!=(const ShipType_Stats& stats);

		};

	}

}
