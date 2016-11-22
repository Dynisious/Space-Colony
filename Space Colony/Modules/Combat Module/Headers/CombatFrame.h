#pragma once

#include "Combat Module.h"
#include "TypeCounter.h"
#include "Fleet.h"
#include <unordered_set>
#include <unordered_map>

namespace Space_Colony {

	namespace Combat_Module {

		/*
		The values pertaining to a single frame of a fleet engagement.*/
		struct CombatFrame {
		public:
			typedef std::unordered_map<faction_type, std::unordered_set<size_t>> FactionFleetIdSet;
			typedef std::unordered_map<faction_type, TypeCounter> FactionCounters;

			CombatFrame();
			CombatFrame(const CombatFrame &orig);
			CombatFrame(const FactionCounters &shpDmg, const FactionFleetIdSet &flts);

			/*
			The counts of damage against the different types of Ship combatants in this combat frame.*/
			FactionCounters shipDamage;
			/*
			A set of Ids for all Fleets engaged in this CombatFrame.*/
			FactionFleetIdSet fleets;

			CombatFrame & operator=(const CombatFrame &right);
			bool operator==(const CombatFrame &right) const;
			bool operator!=(const CombatFrame &right) const;

		};

	}

}
