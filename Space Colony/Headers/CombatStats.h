#pragma once

#include "Space Colony.h"

namespace Space_Colony {

	/*
	The values pertaining to a single frame of a fleet engagement.*/
	struct CombatStats {
		CombatStats();
		CombatStats(const CombatStats &orig);
		CombatStats(const double glnc, const size_t hl, const double evd, const size_t sz,
					const size_t mnSz, const size_t mxSz, const size_t atcks,
					const size_t dmg);

		/*
		Chance whether a successful hit glances off the armour of this type
		causing half damage for the glance.*/
		double glance;
		/*
		The number of damage points which this type can suffer before being at
		risk of destruction.*/
		size_t hull;
		/*
		Chance whether this type fails to evade an attack.*/
		double evade;
		/*
		The size of this type.*/
		size_t size;
		/*
		The smallest size of type this type can target.*/
		size_t minSize;
		/*
		The largest size of type this type type can damage.*/
		size_t maxSize;
		/*
		The number of attacks that this type can launch at once.*/
		size_t attacks;
		/*
		The number of damage points dealt by a successful direct attack from
		this type.*/
		size_t damage;

		CombatStats & operator=(const CombatStats &right);
		bool operator==(const CombatStats &right) const;
		bool operator!=(const CombatStats &right) const;

	};

}
