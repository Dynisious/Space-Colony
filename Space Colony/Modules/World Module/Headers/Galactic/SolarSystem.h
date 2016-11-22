#pragma once

#include "Galactic.h"
#include "Planet.h"
#include "TypeCounter.h"
#include "Fleet.h"
#include <unordered_set>
#include <vector>
#include <string>

namespace Space_Colony {

	namespace World_Module {

		namespace Galactic {

			/*
			A SolarSystem is a collection of stars, Planets and Fleets.*/
			class SolarSystem {
			public:
				typedef std::unordered_set<size_t> FleetIdSet;
				typedef std::vector<Planet> PlanetVector;

				static const size_t Planets_Size_Exception = 1,
					Fleet_Not_Found_Exception = 2,
					Update_State_Unhandled = 3;

				SolarSystem();
				SolarSystem(const SolarSystem &orig);
				SolarSystem(const std::string nm, const size_t strs,
							const PlanetVector &plnts, const FleetIdSet &flts);

				size_t getStars() const;
				const PlanetVector & getPlanets() const;
				PlanetVector setPlanets(const PlanetVector &plnts);
				Planet & getPlanet(const size_t index);
				const Planet & getPlanet(const size_t index) const;
				const FleetIdSet & getFleets() const;
				FleetIdSet setFleets(const FleetIdSet &flts);
				/*
				Returns the collective resource units of all the Planets in the
				SolarSystems.*/
				TypeCounter getResources() const;
				/*
				Returns the collective resource units of all the Planets in the
				SolarSystems for the resource type.*/
				size_t getResource(const size_t resource_type) const;
				/*
				Adds the passed Fleet ID to the SolarSystem.*/
				void addFleet(const size_t fltId);
				/*
				Moves the passed Fleet ID from one SolarSystem, to the other.*/
				static void moveFleet(const size_t fltId, SolarSystem &from,
									  SolarSystem &to);
				/*
				Removes the passed Fleet ID from the SolarSystem.*/
				void removeFleet(const size_t fltId);
				/*
				Returns the faction of the SolarSystem.*/
				faction_type getFaction(const Space_Colony::FleetVector &flts) const;
				/*
				Performs the change in this SolarSystem for a single game tick.*/
				void iterate(const FleetVector &flts, const ConstructTypeVector &cnstrct);

				/*
				A String representing the name of this SolarSystem.*/
				std::string name;

				SolarSystem operator=(const SolarSystem &right);
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
				The collection of Fleets IDs in this SolarSystem.*/
				FleetIdSet fleets;

			};

		}

	}

}
