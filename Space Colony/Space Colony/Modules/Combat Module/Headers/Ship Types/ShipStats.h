#pragma once

#include "Ship Types.h"

#define APPLYFRAC(VALUE, NUMERATOR, DENOMINATOR) ((VALUE) * (NUMERATOR) / (DENOMINATOR))
#define P100 128

namespace Combat_Module {

	namespace Ship_Types {

		/*
		The stats which define a Ship type.*/
		class ShipStats {
		public:
			ShipStats();
			ShipStats(const ShipStats& orig);
			ShipStats(__int32 atcks, __int32 htPnts, __int32 evdChnc,
					  __int32 htChnc, __int32 dflctChnc, __int32 szCls,
					  __int32 szMx, __int32 szMn);

			/*
			Returns the number of deaths that the passed attacks would cause
			against this type.*/
			__int32 deaths(__int32 atcks) const;
			/*
			Returns the number of passed defenders that would survive the passed
			attacks.*/
			__int32 survivors(__int32 dfndrs, __int32 atacks) const;

			__int32 get_attacks() const;
			__int32& get_attacks();
			__int32 get_hitPoints() const;
			void set_hitPoints(__int32 vl);
			__int32 get_evadeChance() const;
			void set_evadeChance(__int32 vl);
			__int32 get_hitChance() const;
			__int32& get_hitChance();
			__int32 get_deflectChance() const;
			void set_deflectChance(__int32 vl);
			__int32 get_attacksToKill() const;

			/*
			The number of attacks this Ship type can launch at once.*/
			__declspec(property(get = get_attacks, put = set_attacks)) __int32 _attacks;
			/*
			The number of attacks this ShipType can suffer before becoming at
			risk of destruction.*/
			__declspec(property(get = get_hitPoints, put = set_hitPoints)) __int32 _hitPoints;
			/*
			The % chance that this ShipType will evade an attack.*/
			__declspec(property(get = get_evadeChance, put = set_evadeChance)) __int32 _evadeChance;
			/*
			The % chance that this Ship type will fire accurately.*/
			__declspec(property(get = get_hitChance, put = set_hitChance)) __int32 _hitChance;
			/*
			The % chance that this Ship type will deflect an attack.*/
			__declspec(property(get = get_deflectChance, put = set_deflectChance)) __int32 _deflectChance;
			/*
			The number of attacks which need to be made against an instance of
			this Ship type before statistically it will die.*/
			__declspec(property(get = get_attacksToKill)) __int32 _attacksToKill;

			/*
			The size of this type of Ship.*/
			__int32 sizeClass;
			/*
			The largest Ship size which this Ship type is able to attack.*/
			__int32 sizeMax;
			/*
			The smallest Ship size which this Ship type is able to attack.*/
			__int32 sizeMin;

			ShipStats& operator=(const ShipStats& right);
			bool operator==(const ShipStats& right) const;
			bool operator!=(const ShipStats& right) const;

		private:
			/*
			Calculate the number of attacks which need to be fired against an
			instance of this Ship type to statistically kill it.*/
			void calcAttacksToKill();

			__int32 attacks;
			__int32 hitPoints;
			__int32 evadeChance;
			__int32 hitChance;
			__int32 deflectChance;
			__int32 attacksToKill;

		};

	}

}
