#pragma once

#include "Combat Module.h"
#include "Ship Types\ShipType.h"
#include <Ships\ShipTypeCount.h>
#include <Ships\Fleet.h>
#include <unordered_map>

namespace Combat_Module {

	/*
	An instance for an engagment between fleets.*/
	class CombatInstance {
	public:
		/*
		A map of Factions and lists of Fleets.*/
		typedef std::unordered_map<Space_Colony::faction_t, Space_Colony::Ships::FleetList> FactionFleetListMap;
		/*
		A map of Factions and ShipTypeCounters.*/
		typedef std::unordered_map<Space_Colony::faction_t, Space_Colony::Ships::ShipTypeCount> FactionShipTypeMap;
		/*
		A map of factions and integers.*/
		typedef std::unordered_map<Space_Colony::faction_t, __int32> FactionCounter;

		CombatInstance();
		CombatInstance(const CombatInstance& orig);
		CombatInstance(const FactionFleetListMap& flts);

		/*
		Performs a single cycle of combat on this CombatInstance.*/
		__int32 iterate();
		/*
		Runs this CombatInstance to its conclusion.*/
		void resolve();
		/*
		Terminates the CombatInstance, returning all suriviving fleets with
		loses removed.*/
		void terminate();

	private:
		/*
		Calculates how many accurate hits are produced for each Faction and
		ShipType within this CombatInstance; totalling up all the hits from all
		Ships into their types.*/
		FactionShipTypeMap calc_LandedHitsFromShipTypes();
		/*
		Calculates the distribution of accurate hits across a given faction given:
		 * The number of hits which are directed at this faction.
		 * The number of each ship type which are being targeted.
		 * The total number of target ships for this faction.
		 * A return object to increment the counters off by the distributed
		   attacks.*/
		void calc_HitDistributionOnFaction(const __int32 landedHits, const Space_Colony::Ships::ShipTypeCount & targets,
										   const unsigned __int32 factionTargets, Space_Colony::Ships::ShipTypeCount & result);
		/*
		Calculates the distribution of accurate hits from a passed ship type
		and faction given:
		* The number of hits which are being distributed.
		* The faction which is attacking.
		* The ship type which is attacking.
		* A return object to increment the counters off by the distributed
		attacks.*/
		void calc_HitDistributionForType(const __int32 landedHits, const Space_Colony::faction_t currentFaction,
								  const Ship_Types::ShipType& attackingType, FactionShipTypeMap& result);
		/*
		Distributes hits across all factions and ship types given the number of
		accurate attacks from each faction and ship type.*/
		FactionShipTypeMap calc_HitDistributionForShipTypes(const FactionShipTypeMap& landedHits);
		/*
		Removes evaded attacks from the passed hits.*/
		FactionShipTypeMap calc_EvadedHitsForShipTypes(const FactionShipTypeMap& landedHits);
		/*
		Adds the passed hits to the pending damage in the conflict.*/
		void applyHits(const FactionShipTypeMap& hits);
		/*
		Performs calculations to determine how many Ships of each type and
		faction die given the number of hits pending against them; decrements
		the ships and pending hits based on the results.*/
		void calculateDeaths();
		/*
		Removes empty or zeroed positions in the fields of this CombatInstance
		to allow for faster iterations.*/
		void cleanFields();

		/*
		A map of factions and lists of fleets aligned with those factions
		currently engaged in this CombatInstance.*/
		FactionFleetListMap fleets;
		/*
		A map of factions and counters of ship types aligned with those
		factions currently engaged in this CombatInstance.*/
		FactionShipTypeMap ships;
		/*
		A map of factions and counters of successful hits against each ship
		type in those factions currently engaged in this CombatInstance.*/
		FactionShipTypeMap pendingHits;

	};

}
