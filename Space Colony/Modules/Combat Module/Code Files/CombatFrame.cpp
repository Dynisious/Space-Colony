#include "Combat Module\Headers\CombatFrame.h"

using namespace Space_Colony;
using namespace Space_Colony::Combat_Module;

Space_Colony::Combat_Module::CombatFrame::CombatFrame()
	: shipDamage(0), fleets(0) {}

Space_Colony::Combat_Module::CombatFrame::CombatFrame(const CombatFrame & orig)
	: CombatFrame(orig.shipDamage, orig.fleets) {}

Space_Colony::Combat_Module::CombatFrame::CombatFrame(const FactionCounters & shpDmg, const FactionFleetIdSet &flts)
	: shipDamage(shpDmg), fleets(flts) {}

CombatFrame & Space_Colony::Combat_Module::CombatFrame::operator=(const CombatFrame & right) {
	shipDamage = right.shipDamage;
	fleets = right.fleets;
	return *this;
}

bool Space_Colony::Combat_Module::CombatFrame::operator==(const CombatFrame & right) const {
	return shipDamage == right.shipDamage
		&& fleets == right.fleets;
}

bool Space_Colony::Combat_Module::CombatFrame::operator!=(const CombatFrame & right) const {
	return !operator==(right);
}
