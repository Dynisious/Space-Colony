#pragma once

#include "Solar.h"
#include "Construct.h"
#include "..\..\..\..\..\..\Headers\TypeCounter.h"
#include <unordered_map>

namespace World_Module {

	namespace Galactic {

		namespace Sector {

			namespace Solar {

				/*
				A Planet has a store of resources and a collection of
				Constructs and can be aligned with a faction.*/
				class Planet {
				public:
					typedef std::unordered_map<__int32, Construct> ConstructMap;
					typedef ConstructMap::const_iterator const_iterator;

					Planet();
					Planet(const Planet& orig);
					Planet(Space_Colony::TypeCounter rsrcs, Space_Colony::TypeCounter ntrlStrg,
						   Space_Colony::faction_t fctn, __int32 stsCnt);
					Planet(Space_Colony::TypeCounter rsrcs, Space_Colony::TypeCounter ntrlStrg,
						   Space_Colony::faction_t fctn, __int32 stsCnt, ConstructMap sts);

					/*
					Get the start iterator of this Planets sites.*/
					const_iterator begin_ground() const;
					/*
					Get the end iterator of this Planets sites.*/
					const_iterator end_ground() const;
					/*
					Get the start iterator of this Planets orbitals.*/
					const_iterator begin_orbital() const;
					/*
					Get the end iterator of this Planets orbitals.*/
					const_iterator end_orbital() const;
					/*
					Places the passed construct into an empty site and returns
					it's index. If no sites are empty or the Construct does not
					have the Ground_Construct WorldTag it returns -1.*/
					__int32 fillSite(const Construct& cnstrct);
					/*
					Adds the passec Construct to the Constructs orbiting this
					Planet and returns it's index. If no sites are empty or the
					Construct does not have the Orbital_Construct WorldTag it
					returns -1.*/
					__int32 addOrbital(const Construct& cnstrct);
					/*
					Returns the number of unfilled sites for Constructs.*/
					__int32 emptySites() const;
					/*
					Removes the Construct at the passed index. If the index is
					unfilled returns false, else true. The old Construct can be
					retrieved with cnstrct.*/
					bool demolishConstruct(const __int32 index, Construct* const cnstrct = nullptr);
					/*
					True if the index is filled.*/
					bool exists(const __int32 index) const;

					const ConstructMap& get_sites() const;
					const ConstructMap& get_orbital() const;
					tagSet get_tags() const;
					Space_Colony::TypeCounter get_totalStorage() const;
					__int32 get_sitesCount() const;
					void set_sitesCount(const __int32 vl);

					/*
					The sites which contain Constructs.*/
					__declspec(property(get = get_sites)) ConstructMap _sites;
					/*
					The Constructs in orbit around this Planet.*/
					__declspec(property(get = get_orbital)) ConstructMap _orbital;
					/*
					The cumulative WorldTags of all this Planets Constructs.*/
					__declspec(property(get = get_tags)) tagSet _tags;
					/*
					The cumulative resource stores of this Planet and all it's Constructs.*/
					__declspec(property(get = get_totalStorage)) Space_Colony::TypeCounter _totalStorage;
					/*
					The maximum number of Constructs which can exist on this Planet.*/
					__declspec(property(get = get_sitesCount, put = set_sitesCount)) __int32 _sitesCount;

					/*
					The resources of this Planet.*/
					Space_Colony::TypeCounter resources;
					/*
					The resource capacity natural to this Planet.*/
					Space_Colony::TypeCounter naturalStorage;
					/*
					The faction which this Planet is aligned with.*/
					Space_Colony::faction_t faction;

					Planet& operator=(const Planet& right);
					bool operator==(const Planet& right) const;
					bool operator!=(const Planet& right) const;

				private:
					ConstructMap sites;
					ConstructMap orbital;
					__int32 sitesCount;

				};

			}

		}

	}

}
