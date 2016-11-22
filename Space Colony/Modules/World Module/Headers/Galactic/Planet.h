#pragma once

#include "Galactic.h"
#include "TypeCounter.h"
#include "Planetary\Construct.h"
#include <string>
#include <vector>
#include <list>

namespace Space_Colony {

	namespace World_Module {

		namespace Galactic {

			/*
			A Planet has a collection of resource and can support a set number
			of Constructs on it's surface or any number in it's orbit.*/
			class Planet {
			public:
				typedef std::vector<Planetary::Construct> ConstructVector;
				typedef std::list<Planetary::Construct> ConstructList;

				Planet();
				Planet(const Planet &orig);
				Planet(const faction_type fctn, const std::string &nm,
					   const TypeCounter &rsrcs, const TypeCounter &ntrlCpcty,
					   const size_t sts);
				Planet(const faction_type fctn, const std::string &nm,
					   const TypeCounter &rsrcs, const TypeCounter &ntrlCpcty,
					   const ConstructVector sts, const ConstructList stlts);

				static const size_t Resource_Capacity_Exceeded = 1,
					Site_Size_Exception = 2,
					Invalid_Counter_Exception = 3;

				const TypeCounter & getResources() const;
				TypeCounter setResources(const TypeCounter &rsrcs,
										 const ConstructTypeVector types);
				const TypeCounter & getNaturalCapacity() const;
				TypeCounter setNaturalCapacity(const TypeCounter &ntrlCpcty,
											   const ConstructTypeVector types);
				const ConstructVector & getSites() const;
				Planetary::Construct & getSite(const size_t site);
				const Planetary::Construct & getSite(const size_t site) const;
				ConstructVector setSites(const ConstructVector &sts,
										 const ConstructTypeVector types);
				ConstructList & getSatellites();
				const ConstructList & getSatellites() const;
				ConstructList setSatellites(const ConstructList &stlts,
											const ConstructTypeVector types);
				/*
				Returns the old counter for the passed resource and sets the
				new counter.*/
				size_t setResource(const size_t resource_type, const size_t val,
								   const ConstructTypeVector types);
				/*
				Adds the passed Construct to the list of Satellites on the Planet.*/
				void addSatellite(const Planetary::Construct &cnstrct);
				/*
				Removes the passed Construct from the list of Satellites on the Planet.*/
				void removeSatellite(const Planetary::Construct &cnstrct,
									 const ConstructTypeVector types);
				/*
				True if the Planet is populated by a Super Construct.*/
				bool isSuperConstruct() const;
				/*
				Returns the old natural capacity for the passed resources type
				and sets the new capacity.*/
				size_t setNaturalCapacity(const size_t resource_type, const size_t val,
										  const ConstructTypeVector types);
				/*
				Returns the combined capacity for resources for the Planet and
				all its Constructs.*/
				TypeCounter getResourceCapacity(const ConstructTypeVector types) const;
				/*
				Returns the capacity for this resource for the Planet and all
				its Constructs.*/
				size_t getResourceCapacity(const size_t resource_type,
										   const ConstructTypeVector types) const;
				/*
				True if the passed index is filled.*/
				bool isFilled(const size_t site) const;
				/*
				Clears the Construct in this Site.*/
				void emptySite(const size_t site);

				/*
				The faction alignment of this Planet.*/
				faction_type faction;
				/*
				A String representing the name of this Planet.*/
				std::string name;

				Planet & operator=(const Planet &right);
				bool operator==(const Planet &right) const;
				bool operator!=(const Planet &right) const;

			private:
				/*
				A TypeCounter of all the resources on this Planet.*/
				TypeCounter resources;
				/*
				A TypeCounter of the natural capacities for resources units on
				this Planet.*/
				TypeCounter naturalCapacity;
				/*
				A collection of all the Constructs built on this Planet.*/
				ConstructVector sites;
				/*
				A collection of all the Constructs in orbit around this Planet.*/
				ConstructList satellites;

			};

		}

	}

}
