#pragma once

#include "Solar.h"
#include "..\..\..\..\..\Headers\Fleet.h"
#include "..\..\..\..\..\Headers\TypeCounter.h"

namespace World_Module {

	namespace Galactic {

		namespace Solar {

			class EconomicFleet : public Space_Colony::Fleet {
			public:
				EconomicFleet();
				EconomicFleet(const EconomicFleet& orig);
				EconomicFleet(const Space_Colony::TypeCounter& rsrcs, const Space_Colony::TypeCounter& rsrcsCpcty);

				Space_Colony::TypeCounter resources;
				Space_Colony::TypeCounter resourcesCapacity;

				EconomicFleet& operator=(const EconomicFleet& right);
				bool operator==(const EconomicFleet& right) const;
				bool operator!=(const EconomicFleet& right) const;

			};

		}

	}

}
