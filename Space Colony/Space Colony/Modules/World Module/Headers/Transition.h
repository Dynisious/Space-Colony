#pragma once

#include "World Module.h"
#include "Galactic\Solar\EconomicFleet.h"

namespace World_Module {

	class Transition {
		typedef std::list<std::pair<coordinate, __int32>> Path;

		Transition();
		Transition(const Transition& orig);
		Transition(const Path& trnstPth, const Galactic::Solar::EconomicFleet& flt);

		bool transit();

		Path transitPath;
		Path::iterator position;
		Galactic::Solar::EconomicFleet fleet;

		Transition& operator=(const Transition& right);
		bool operator==(const Transition& right) const;
		bool operator!=(const Transition& right) const;

	};

}
