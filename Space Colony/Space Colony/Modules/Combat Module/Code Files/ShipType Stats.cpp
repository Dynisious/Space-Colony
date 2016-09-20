#include "..\Headers\Ship Types\ShipType Stats.h"

Combat_Module::Ship_Types::ShipType_Stats::ShipType_Stats()
	: ShipType_Stats(0, 0, 0, 0, 0, 0, 0, 0) {}

Combat_Module::Ship_Types::ShipType_Stats::ShipType_Stats(const ShipType_Stats & orig)
	: ShipType_Stats(orig.hitPoints, orig.evadeChance, orig.deflectChance,
					 orig.hitChance, orig.attacksCount, orig.sizeValue,
					 orig.minSize, orig.maxSize) {}

Combat_Module::Ship_Types::ShipType_Stats::ShipType_Stats(__int32 htPnts, chance_t vdChnc, chance_t dflctChnc,
														  chance_t htChnc, __int32 ttcksCnt, size_t szVl,
														  size_t mnSz, size_t mxSz)
	: hitPoints(htPnts), evadeChance(vdChnc), deflectChance(dflctChnc),
	hitChance(htChnc), attacksCount(ttcksCnt), sizeValue(szVl),
	minSize(mnSz), maxSize(mxSz) {}

bool Combat_Module::Ship_Types::ShipType_Stats::operator==(const ShipType_Stats & stats) {
	if (this == &stats)
		return true;
	return hitPoints == stats.hitPoints
		&& evadeChance == stats.evadeChance
		&& deflectChance == stats.deflectChance
		&& hitChance == stats.hitChance
		&& attacksCount == stats.attacksCount
		&& sizeValue == stats.sizeValue
		&& minSize == stats.minSize
		&& maxSize == stats.maxSize;
}

bool Combat_Module::Ship_Types::ShipType_Stats::operator!=(const ShipType_Stats & stats) {
	if (this != &stats)
		return true;
	return hitPoints == stats.hitPoints
		|| evadeChance == stats.evadeChance
		|| deflectChance == stats.deflectChance
		|| hitChance == stats.hitChance
		|| attacksCount == stats.attacksCount
		|| sizeValue == stats.sizeValue
		|| minSize == stats.minSize
		|| maxSize == stats.maxSize;
}
