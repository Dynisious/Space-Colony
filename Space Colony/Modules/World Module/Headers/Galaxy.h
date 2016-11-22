#pragma once

#include "World Module.h"
#include "Galactic\StarSector.h"
#include "Maths\matrix.h"
#include <string>
#include <unordered_map>

namespace Space_Colony {

	namespace World_Module {

		typedef Dyn_API::Maths::matrix<__int32, 2, 1> coordinate;

		/*
		A Galaxy is a map of StarSectors.*/
		class Galaxy {
		public:
			typedef std::unordered_map<coordinate, size_t> SectorMap;

			static const size_t Repreated_Sector_Id = 1;

			Galaxy();
			Galaxy(const Galaxy &orig);
			Galaxy(const std::string &nm, const SectorMap &sctrs);

			const SectorMap & getSectors() const;
			/*
			Adds the passed StarSector ID and returns the coordinates to it.*/
			coordinate addSector(const size_t sector, const double range,
								 const coordinate &location);
			/*
			Returns the StarSector mapped to the passed coordinate.*/
			size_t getSector(const coordinate &loc) const;
			/*
			Returns the coordinate for the centre of this Galaxy.*/
			coordinate getCentre() const;
			/*
			Iterates all the StarSector in the map.*/
			void iterate(Galactic::SectorVector &sctrs, const FleetVector &flts,
						 const ConstructTypeVector &cnstrcts);
			/*
			Returns a new randomised coordinate which is a randomly up to
			'range' away from 'location'.The new coordinate is guaranteed to
			not already exist in the game world.*/
			coordinate newCoordinate(const double range, const coordinate &location) const;

			/*
			A String representing the name of this Galaxy.*/
			std::string name;

			Galaxy & operator=(const Galaxy &right);
			bool operator==(const Galaxy &right) const;
			bool operator!=(const Galaxy &right) const;

		private:
			/*
			The map of StarSectors Ids for the Galaxy to coordinates.*/
			SectorMap sectors;

		};

	}

}
