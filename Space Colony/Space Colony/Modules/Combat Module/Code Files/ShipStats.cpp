#include "..\Headers\Ship Types\ShipStats.h"

Combat_Module::Ship_Types::ShipStats::ShipStats()
	: ShipStats(-1, -1, -1, -1, -1, -1, -1, -1) {}

Combat_Module::Ship_Types::ShipStats::ShipStats(const ShipStats & orig)
	: ShipStats(orig.attacks, orig.hitPoints, orig.evadeChance, orig.hitChance,
				orig.deflectChance, orig.sizeClass, orig.sizeMax, orig.sizeMin) {}

Combat_Module::Ship_Types::ShipStats::ShipStats(__int32 atcks, __int32 htPnts, __int32 evdChnc,
												__int32 htChnc, __int32 dflctChnc, __int32 szCls,
												__int32 szMx, __int32 szMn)
	: attacks(atcks), hitPoints(htPnts), evadeChance(evdChnc), hitChance(htChnc),
	deflectChance(dflctChnc), sizeClass(szCls), sizeMax(szMx), sizeMin(szMn) {
	calcAttacksToKill();
}

__int32 Combat_Module::Ship_Types::ShipStats::deaths(__int32 atcks) const {
	return atcks / attacksToKill;
}

__int32 Combat_Module::Ship_Types::ShipStats::survivors(__int32 dfndrs, __int32 atacks) const {
	dfndrs -= deaths(atacks);
	return (dfndrs > 0) ? dfndrs : 0;
}

__int32 Combat_Module::Ship_Types::ShipStats::get_attacks() const {
	return attacks;
}

__int32 & Combat_Module::Ship_Types::ShipStats::get_attacks() {
	return attacks;
}

__int32 Combat_Module::Ship_Types::ShipStats::get_hitPoints() const {
	return hitPoints;
}

void Combat_Module::Ship_Types::ShipStats::set_hitPoints(__int32 vl) {
	hitPoints = vl;
	calcAttacksToKill();
}

__int32 Combat_Module::Ship_Types::ShipStats::get_evadeChance() const {
	return evadeChance;
}

void Combat_Module::Ship_Types::ShipStats::set_evadeChance(__int32 vl) {
	evadeChance = vl;
	calcAttacksToKill();
}

__int32 Combat_Module::Ship_Types::ShipStats::get_hitChance() const {
	return hitChance;
}

__int32 & Combat_Module::Ship_Types::ShipStats::get_hitChance() {
	return hitChance;
}

__int32 Combat_Module::Ship_Types::ShipStats::get_deflectChance() const {
	return deflectChance;
}

void Combat_Module::Ship_Types::ShipStats::set_deflectChance(__int32 vl) {
	deflectChance = vl;
	calcAttacksToKill();
}

__int32 Combat_Module::Ship_Types::ShipStats::get_attacksToKill() const {
	return attacksToKill;
}

Combat_Module::Ship_Types::ShipStats & Combat_Module::Ship_Types::ShipStats::operator=(const ShipStats & right) {
	attacks = right.attacks;
	hitPoints = right.hitPoints;
	evadeChance = right.evadeChance;
	hitChance = right.hitChance;
	deflectChance = right.deflectChance;
	attacksToKill = right.attacksToKill;
	sizeClass = right.sizeClass;
	sizeMax = right.sizeMax;
	sizeMin = right.sizeMin;
	return *this;
}

bool Combat_Module::Ship_Types::ShipStats::operator==(const ShipStats & right) const {
	return attacks == right.attacks
		&& hitPoints == right.hitPoints
		&& evadeChance == right.evadeChance
		&& hitChance == right.hitChance
		&& deflectChance == right.deflectChance
		&& attacksToKill == right.attacksToKill
		&& sizeClass == right.sizeClass
		&& sizeMax == right.sizeMax
		&& sizeMin == right.sizeMin;
}

bool Combat_Module::Ship_Types::ShipStats::operator!=(const ShipStats & right) const {
	return !operator==(right);
}

void Combat_Module::Ship_Types::ShipStats::calcAttacksToKill() {
	attacksToKill = APPLYFRAC(hitPoints, P100, evadeChance)
		+ APPLYFRAC(hitPoints, P100, deflectChance);
}
