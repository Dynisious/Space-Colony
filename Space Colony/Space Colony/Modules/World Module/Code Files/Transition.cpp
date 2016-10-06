#include "..\Headers\Transition.h"

World_Module::Transition::Transition()
	: Transition(Path(0), Galactic::Solar::EconomicFleet()) {}

World_Module::Transition::Transition(const Transition & orig)
	: Transition(orig.transitPath, orig.fleet) {}

World_Module::Transition::Transition(const Path & trnstPth, const Galactic::Solar::EconomicFleet & flt)
	: transitPath(trnstPth), fleet(flt), position(transitPath.begin()) {}

bool World_Module::Transition::transit() {
	if (++position == transitPath.end())
		//The end of the path has been reached.
		return true;
	else
		//There is more of the path to travel.
		return false;
}

World_Module::Transition & World_Module::Transition::operator=(const Transition & right) {
	transitPath = right.transitPath;
	fleet = right.fleet;
	return *this;
}

bool World_Module::Transition::operator==(const Transition & right) const {
	return (this == &right)
		|| (transitPath == right.transitPath
			&& fleet == right.fleet);
}

bool World_Module::Transition::operator!=(const Transition & right) const {
	return !operator==(right);
}
