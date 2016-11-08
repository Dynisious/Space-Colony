#pragma once

#include "World Module.h"
#include "Galactic\StarSector.h"
#include <unordered_map>
#include <string>

namespace Space_Colony {

	namespace World_Module {

		/*
		A Galaxy is a map of StarSectors.*/
		class Galaxy {
		public:
			typedef std::unordered_map<coordinate, Galacitc::StarSector> StarMap;

			Galaxy();
			Galaxy(const Galaxy &orig);
			Galaxy(const std::string & nm, const StarMap &sctrs);

			/*
			Adds the passed StarSector and returns the coordinates to it.*/
			coordinate addSector(const Galacitc::StarSector &sec, const double range, const coordinate &location);
			/*
			Returns the StarSector mapped to the passed coordinate.*/
			Galacitc::StarSector & getSector(const coordinate &coord);
			/*
			Returns the StarSector mapped to the passed coordinate.*/
			const Galacitc::StarSector & getSector(const coordinate &coord) const;
			const StarMap & getSectors() const;
			/*
			Returns the coordinate for the centre of this Galaxy.*/
			coordinate getCentre() const;
			/*
			Iterates all the StarSector in the map.*/
			void iterate();

			/*
			A String representing the name of this Galaxy.*/
			std::string name;

			Galaxy & operator=(const Galaxy &right);
			bool operator==(const Galaxy &right) const;
			bool operator!=(const Galaxy &right) const;

		private:
			/*
			Returns a new randomised coordinate which is a randomly up to 'range'
			away from 'location'. The new coordinate is guaranteed to not already
			exist in the game world.*/
			coordinate newCoordinate(double range, const coordinate &location) const;

			/*
			The map of StarSectors for the Galaxy to coordinates.*/
			StarMap sectors;

		};

	}

}
