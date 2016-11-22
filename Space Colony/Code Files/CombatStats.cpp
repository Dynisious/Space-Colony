#include "CombatStats.h"

using namespace Space_Colony;

Space_Colony::CombatStats::CombatStats()
	: CombatStats(0, 0, 0, 0, 0, 0, 0, 0) {}

Space_Colony::CombatStats::CombatStats(const CombatStats & orig)
	: CombatStats(orig.glance, orig.hull, orig.evade, orig.size, orig.minSize,
				  orig.maxSize, orig.attacks, orig.damage) {}

Space_Colony::CombatStats::CombatStats(
	const double glnc, const size_t hl, const double evd, const size_t sz, const size_t mnSz,
	const size_t mxSz, const size_t atcks, const size_t dmg)
	: glance(glnc), hull(hl), evade(evd), size(sz), minSize(mnSz),
	maxSize(mxSz), attacks(atcks), damage(dmg) {}

CombatStats & Space_Colony::CombatStats::operator=(const CombatStats & right) {
	glance = right.glance;
	hull = right.hull;
	evade = right.evade;
	size = right.size;
	minSize = right.minSize;
	maxSize = right.maxSize;
	attacks = right.attacks;
	damage = right.damage;
	return *this;
}

bool Space_Colony::CombatStats::operator==(const CombatStats & right) const {
	return glance == right.glance
		&& hull == right.hull
		&& evade == right.evade
		&& size == right.size
		&& minSize == right.minSize
		&& maxSize == right.maxSize
		&& attacks == right.attacks
		&& damage == right.damage;
}

bool Space_Colony::CombatStats::operator!=(const CombatStats & right) const {
	return !operator==(right);
}
