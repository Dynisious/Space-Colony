#pragma once

#include "Galactic.h"
#include "Fleet.h"
#include "SolarSystem.h"
#include "TypeCounter.h"
#include <vector>

namespace Space_Colony {

	namespace World_Module {

		namespace Galactic {

			/*
			A StarSector is a group of indexed SolarSystems.*/
			class StarSector {
			public:
				typedef std::vector<SolarSystem> SystemVector;

				StarSector();
				StarSector(const StarSector &orig);
				StarSector(const std::string &nm, const SystemVector &systms);

				/*
				Returns the faction for the StarSector.*/
				faction_type getFaction(const FleetVector &flts) const;
				/*
				Returns the collective resource units of all the Planets of all
				the Planets in the SolarSystems of this StarSector.*/
				TypeCounter getResources() const;
				/*
				Returns the collective resource units of all the Planets of all
				the Planets in the SolarSystems of this StarSector of the
				resource type.*/
				size_t getResource(const size_t resource_type) const;
				/*
				Performs a single iteration on each SolarSystem in this StarSector.*/
				void iterate(const FleetVector &flts, const ConstructTypeVector &cnstrcts);

				/*
				A String representing the name of the StarSector.*/
				std::string name;

				StarSector & operator=(const StarSector &right);
				bool operator==(const StarSector &right) const;
				bool operator!=(const StarSector &right) const;

			private:
				/*
				The collection of SolarSystems in this StarSector.*/
				SystemVector systems;

			};

			typedef std::vector<StarSector> SectorVector;

		}

	}

}
