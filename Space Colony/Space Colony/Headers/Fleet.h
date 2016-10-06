#pragma once

#include "Space Colony.h"
#include "TypeCounter.h"

namespace Space_Colony {

	/*
	A Fleet is a TypeCounter with a faction value.*/
	class Fleet : public TypeCounter {
	public:
		Fleet();
		Fleet(const Fleet& orig);
		Fleet(faction_t fctn, const TypeCounter& shpCntr);

		/*
		The faction_t value which this Fleet is aligned with.*/
		faction_t faction;

		Fleet& operator=(const Fleet& right);
		bool operator==(const Fleet& right) const;
		bool operator!=(const Fleet& right) const;

	};

}
