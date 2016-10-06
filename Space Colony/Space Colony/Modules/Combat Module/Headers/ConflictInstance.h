#pragma once

#include "Combat Module.h"
#include "Ship Types\ShipTemplate.h"
#include "..\..\..\Headers\Fleet.h"
#include "..\..\..\Headers\TypeCounter.h"
#include <list>
#include <unordered_map>

namespace Combat_Module {

	/*
	A ConflictInstance acts out a battle between CombatFleets.*/
	class ConflictInstance {
	public:
		typedef __int32 ConflictID;
		typedef std::list<Space_Colony::Fleet> FleetList;
		typedef std::unordered_map<Space_Colony::faction_t, Space_Colony::TypeCounter> CounterMap;
		typedef std::unordered_map<Space_Colony::faction_t, FleetList> FleetMap;

		ConflictInstance();
		ConflictInstance(const ConflictInstance& orig);
		ConflictInstance(const FleetList& flts);
		ConflictInstance(const FleetMap& flts);

		/*
		Adds a CombatFleet and it's ships to the fight.*/
		void addFleet(const Space_Colony::Fleet& flt);
		/*
		Performs a single iteration of the ConflictInstance.*/
		__int32 iterate();
		/*
		Iterates until the ConflictInstance is resolved and can be dispanded.*/
		FleetList resolve();
		/*
		Cleans the environment so that empty mappings are cleared.*/
		__int32 clean();
		/*
		Returns a list of all the Fleets currently in combat.*/
		FleetList dispand();

		ConflictID get_ID() const;

		__declspec(property(get = get_ID)) ConflictID _ID;

		ConflictInstance& operator=(const ConflictInstance& right);
		bool operator==(const ConflictInstance& right) const;
		bool operator!=(const ConflictInstance& right) const;

	private:
		typedef std::unordered_map<Space_Colony::faction_t, std::list<Ship_Types::ShipTemplate::ShipTemplateID>> TypeMap;

		/*
		Returns the cumulative attacks launched from all engaged ships.*/
		CounterMap getAllAttacks();
		/*
		Returns the cumulative attacks launched from all engaged ships of this
		faction.*/
		CounterMap::mapped_type getFactionAttacks(Space_Colony::faction_t faction);
		/*
		Distributes the passed attacks across all the opposing factions.*/
		CounterMap distributeAllAttacks(const CounterMap& attacks);
		/*
		Distributes the passed attacks for a particular faction.*/
		void distributeFactionAttacks(Space_Colony::faction_t faction, const CounterMap::mapped_type& attacks, CounterMap& distributedHits);
		/*
		Filters only the types which can be targeted by the passed type out of
		the passed targets.*/
		void filterAttackableTypes(const Ship_Types::ShipTemplate& type, const CounterMap::mapped_type& targets, CounterMap::mapped_type& attackable);
		/*
		Distributes the passed attacks across the passed targets.*/
		void distributeAttacks(const __int32 attacks, const CounterMap::mapped_type& targets, CounterMap::mapped_type& distributedHits);
		/*
		Distributes the passed attacks across all opposing factions for the
		passed type.*/
		void distributeTypeAttacksForFaction(const __int32 typeID, __int32 attacks, Space_Colony::faction_t faction, CounterMap& distributedHits);
		/*
		Returns an iterations worth of deaths in the conflict.*/
		CounterMap getAllDeaths();
		/*
		Returns the deaths for a particular faction given the passed attacks
		against them.*/
		CounterMap::mapped_type getFactionDeaths(const CounterMap::mapped_type& attacks);
		/*
		Returns the deaths for a given type given the passed attacks.*/
		__int32 getTypeDeaths(__int32 typeID, const __int32 attacks);

		FleetMap fleets;
		CounterMap engagedShips;
		CounterMap pendingHits;
		ConflictID id;

	};

	/*
	Initiates conflict between the passed Fleets and returns the ID to access
	the conflict instance.*/
	ConflictInstance::ConflictID initiateConflict(const ConflictInstance::FleetList& fleets);
	/*
	Retrieves the ConflictInstance with the passed ID and returns true if it
	exists.*/
	bool ConflictInstance_getInstance(const ConflictInstance::ConflictID id, ConflictInstance& conflict);

}
