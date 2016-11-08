#pragma once

#include "Galactic.h"
#include "SolarSystem.h"
#include <vector>
#include <string>

namespace Space_Colony {

	namespace World_Module {

		namespace Galacitc {

			/*
			A StarSector is a group of indexed SolarSystems.*/
			class StarSector {
			public:
				typedef std::vector<SolarSystem> SystemVector;

				StarSector();
				StarSector(const StarSector &orig);
				StarSector(const std::string &nm, const SystemVector &systms);

				SystemVector & getSystems(const size_t index);
				const SystemVector & getSystems(const size_t index) const;
				SolarSystem & getSolarSystem(const size_t index);
				const SolarSystem & getSolarSystem(const size_t index) const;
				/*
				Returns the faction for the StarSector.*/
				faction_type getFaction() const;
				/*
				Returns the collective resources of all the Planets of all the
				Planets in the SolarSystems of this StarSector.*/
				TypeCounter getResources() const;
				/*
				Returns the collective resources of all the Planets of all the
				Planets in the SolarSystems of this StarSector of the resource type.*/
				size_t getResource(const __int32 rsrc) const;
				/*
				Performs a single iteration on each SolarSystem in this StarSector.*/
				void iterate();

				std::string name;

				StarSector & operator=(const StarSector &right);
				bool operator==(const StarSector &right) const;
				bool operator!=(const StarSector &right) const;

				operator SystemVector & ();
				operator const SystemVector & () const;

			private:
				/*
				The collection of SolarSystems in this StarSector.*/
				SystemVector systems;

			};

		}

	}

}
