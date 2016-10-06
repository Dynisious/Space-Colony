#pragma once

#include "Galactic.h"
#include "Solar\Planet.h"
#include "Solar\EconomicFleet.h"
#include "..\..\..\..\Headers\TypeCounter.h"
#include <list>
#include <vector>

namespace World_Module {

	namespace Galactic {

		/*
		A StarSystem is a collection of Planets and loose resources
		orbiting a star. StarSystems can also host Fleets.*/
		class StarSystem {
		public:
			typedef std::vector<Solar::Planet> PlanetVector;
			typedef std::list<Solar::EconomicFleet> FleetList;

			StarSystem();
			StarSystem(const StarSystem& orig);
			StarSystem(const Space_Colony::TypeCounter& frRsrcs, const PlanetVector& plnts);
			StarSystem(const Space_Colony::TypeCounter& frRsrcs, const PlanetVector& plnts, const FleetList& flts);

			tagSet get_tags() const;
			Space_Colony::TypeCounter get_totalResources() const;
			Space_Colony::faction_t get_faction() const;

			/*
			The cumulative WorldTags of all this StarSystems Planets.*/
			__declspec(property(get = get_tags)) tagSet _tags;
			/*
			The cumulative resources of this StarSystem all its Planets.*/
			__declspec(property(get = get_totalResources)) Space_Colony::TypeCounter _totalResources;
			/*
			The cumulative faction of all this StarSystems Planets.*/
			__declspec(property(get = get_faction)) Space_Colony::faction_t _faction;

			/*
			Resources which are freely orbiting the star.*/
			Space_Colony::TypeCounter freeResources;
			/*
			The Planets which are orbiting the star.*/
			PlanetVector planets;
			/*
			The Fleets which are currently in the StarSystem.*/
			FleetList fleets;

			StarSystem& operator=(const StarSystem& right);
			bool operator==(const StarSystem& right) const;
			bool operator!=(const StarSystem& right) const;

		};

	}

}
