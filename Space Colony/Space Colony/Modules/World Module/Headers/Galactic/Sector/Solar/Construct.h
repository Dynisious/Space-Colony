#pragma once

#include "Solar.h"
#include "..\..\..\..\..\..\Headers\TypeCounter.h"

namespace World_Module {

	namespace Galactic {

		namespace Sector {

			namespace Solar {

				/*
				A construct represents a change in resource quantities and a
				capacity for storing resources.*/
				class Construct {
				public:
					Construct();
					Construct(const Construct& orig);
					Construct(tagSet tgs, resourceMap rsrcShfts, Space_Colony::TypeCounter strg, bool enbld);

					/*
					The WorldTags which apply to this Construct.*/
					tagSet tags;
					/*
					The change in resources produced by this Construct.*/
					resourceMap resourceShifts;
					/*
					The resource capacity provided by this Construct.*/
					Space_Colony::TypeCounter storage;
					bool enabled;

					Construct& operator=(const Construct& right);
					bool operator==(const Construct& right) const;
					bool operator!=(const Construct& right) const;

				};

			}

		}

	}

}
