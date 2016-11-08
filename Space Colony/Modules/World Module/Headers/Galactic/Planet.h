#pragma once

#include "Galactic.h"
#include "TypeCounter.h"
#include "Planetary\Construct.h"
#include <vector>
#include <list>
#include <stdexcept>
#include <string>

namespace Space_Colony {

	namespace World_Module {

		namespace Galacitc {
			
			/*
			A Planet has a collection of resource and can support a set number
			of Constructs on it's surface or any number in it's orbit.*/
			class Planet {
			public:
				typedef std::vector<Planetary::Construct> ConstructVector;
				typedef std::list<Planetary::Construct> ConstructList;

				Planet();
				Planet(const Planet &orig);
				Planet(const Planet &orig, const faction_type fctn);
				Planet(const Planet &orig, const std::string &nm);
				Planet(const Planet &orig, const faction_type fctn, const std::string &nm);
				Planet(const faction_type fctn, const std::string &nm, const TypeCounter & rsrcs, const TypeCounter & ntrlCpcty,
					   const size_t bldngs);
				Planet(const faction_type fctn, const std::string &nm, const TypeCounter & rsrcs, const TypeCounter & ntrlCpcty,
					   const ConstructVector & bldngs, const ConstructList & stlts);

				/*
				Returns the shift in resources produced by the Constructs
				on this Planet.*/
				TypeCounter getResourceShift() const;
				/*
				Returns the shift in resources produced by the Constructs
				on this Planet for this type of resource.*/
				__int32 getResourceShift(const __int32 rsrc) const;
				/*
									Returns the combined tags of all the Constructs on this Planet.*/
				Planetary::ConstructType::ConstructTags getTags() const;
				/*
				Returns the combined capacity for resource for the Planet and all its Constructs.*/
				TypeCounter getResourceCapacity() const;
				/*
				Returns the capacity for this resource for the Planet and all its Constructs.*/
				size_t getResourceCapacity(const __int32 rsrc) const;
				const TypeCounter & getResources() const;
				TypeCounter setResources(const TypeCounter &rsrcs);
				size_t setResources(const __int32 rsrcs, const size_t val);
				const ConstructVector & getSites() const;
				/*
				True if the passed index is filled.*/
				bool isFilled(const size_t index) const;
				Planetary::Construct & getSite(const size_t index);
				const Planetary::Construct & getSite(const size_t index) const;
				const ConstructList & getSatellites() const;
				ConstructList & getSatellites();

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
				A TypeCounter of the natural capacities for resources on this Planet.*/
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
