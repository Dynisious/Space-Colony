#pragma once

#include "Combat Module.h"
#include "CombatFrame.h"
#include "ResourceType.h"

namespace Space_Colony {

	namespace Combat_Module {

		/*
		An active and updating instance of a conflict.*/
		class CombatInstance {
		public:
			CombatInstance();
			CombatInstance(const CombatFrame &frm);

			/*
			Iterate to the next frame in the conflict.*/
			void iterate(FleetVector & fleets, const ShipTypeVector &ships,
						 const ResourceTypeVector &rsrc);
			/*
			Returns the next frame in this conflict.*/
			CombatFrame getNextFrame(FleetVector &fleets, const ShipTypeVector &ships, 
									 const ResourceTypeVector &rsrc) const;
			/*
			Adds a new Fleet to this conflict.*/
			bool addFleet(const size_t fltId, const FleetVector &fleets);
			/*
			Removes the Fleet from this conflict.*/
			bool removeFleet(const size_t fltId, const FleetVector &fleets);

			CombatInstance & operator=(const CombatFrame &right);
			bool operator==(const CombatFrame &right) const;
			bool operator!=(const CombatFrame &right) const;

			operator CombatFrame &();
			operator const CombatFrame &() const;

		private:
			/*
			The current frame that represents this instant in the ongoing
			conflict.*/
			CombatFrame frame;

		};

	}

}
