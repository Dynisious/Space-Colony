#pragma once

#include "Galactic.h"
#include "Fleet.h"
#include "Planet.h"
#include "Planetary\ConstructType.h"
#include "TypeCounter.h"
#include <vector>
#include <list>
#include <string>

namespace Space_Colony {

	namespace World_Module {

		namespace Galacitc {

			/*
			A SolarSystem is a collection of stars, Planets and Fleets.*/
			class SolarSystem {
			public:
				typedef std::vector<Planet> PlanetVector;
				typedef std::list<FleetRef> FleetList;

				SolarSystem();
				SolarSystem(const SolarSystem &orig);
				SolarSystem(const SolarSystem &orig, const std::string &nm);
				SolarSystem(const std::string &nm, const size_t strs, const PlanetVector &plnts);
				SolarSystem(const std::string &nm, const size_t strs, const PlanetVector &plnts, const FleetList & flts);

				const PlanetVector & getPlanets() const;
				Planet & getPlanet(const size_t index);
				const Planet & getPlanet(const size_t index) const;
				const FleetList & getFleets() const;
				/*
				Returns the collective resources of all the Planets in the SolarSystems.*/
				TypeCounter getResources() const;
				/*
				Returns the collective resources of all the Planets in the
				SolarSystems for the resource type.*/
				size_t getResource(const __int32 rsrc) const;
				/*
				Returns all Fleets which contain ships whose types have and exclude the passed tags.*/
				FleetList getFleetsByTags(const ShipType::RollTagSet &tags, const ShipType::RollTagSet &exclude) const;
				/*
				Adds the passed Fleet to the SolarSystem.*/
				void addFleet(const FleetRef &flt);
				/*
				Removes the passed Fleet from the SolarSystem.*/
				bool removeFleet(const FleetRef &flt);
				/*
				Returns the faction of the SolarSystem.*/
				faction_type getFaction() const;
				/*
				Performs the change in this SolarSystem for a single game tick.*/
				void iterate();

				/*
				A String representing the name of this SolarSystem.*/
				std::string name;

				SolarSystem & operator=(const SolarSystem &right);
				bool operator==(const SolarSystem &right) const;
				bool operator!=(const SolarSystem &right) const;

			private:
				/*
				The number of stars in this SolarSystem.*/
				size_t stars;
				/*
				The collection of Planets in this SolarSystem.*/
				PlanetVector planets;
				/*
				The collection of Fleets in this SolarSystem.*/
				FleetList fleets;

			};

		}

	}

}
