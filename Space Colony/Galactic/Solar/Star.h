#pragma once

#include "Solar.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			/*
			A Star is an infinite slow source of energy and gas.*/
			class Star {
			public:
				unsigned __int32 outputs[ResourceType_max];
				bool harvester;

				Star();
				Star(unsigned __int32 outs[]);

			};

		}

	}

}
