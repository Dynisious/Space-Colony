#pragma once

#include "Star System.h"
#include "City.h"
#include "Construct.h"
#include <stdexcept>

namespace World_Module {

	namespace Star_System {

		/*
		A construction site on a Planet where either a
		construct or a City can be located.*/
		class ConstructionSite {
		public:
			union Site {
				Site();
				~Site();

				City city;
				Construct construct;

			};
			/*
			States indicating whether this site is occupied by something.*/
			enum ConstructionSite_state {
				state_empty,
				state_city,
				state_construct,
				state_max
			};

			ConstructionSite();
			ConstructionSite(const ConstructionSite& orig);
			ConstructionSite(const ConstructionSite_state st);
			ConstructionSite(const City& filledSite);
			ConstructionSite(const Construct& filledSite);
			~ConstructionSite();

			void deconstruct();

			ConstructionSite_state get_state() const;
			Site& get_site();
			const Site& get_site() const;

			ConstructionSite& operator=(const ConstructionSite& right);
			ConstructionSite& operator=(const City& right);
			ConstructionSite& operator=(const Construct& right);
			bool operator==(const ConstructionSite& right) const;
			bool operator==(const City& right) const;
			bool operator==(const Construct& right) const;
			bool operator!=(const ConstructionSite& right) const;
			bool operator!=(const City& right) const;
			bool operator!=(const Construct& right) const;

			operator const City&() const;
			operator const Construct&() const;
			operator City&();
			operator Construct&();

			__declspec(property(get = get_state)) ConstructionSite_state _state;
			__declspec(property(get = get_site)) Site _site;

		private:
			Site site;
			/*
			The current state of this site.*/
			ConstructionSite_state state;

		};

		typedef std::vector<ConstructionSite> SiteVector;

	}

}

class ConstructionSite_StateException : std::exception {
public:
	ConstructionSite_StateException();
	ConstructionSite_StateException(const ConstructionSite_StateException& orig);
	ConstructionSite_StateException(const char* Message);

};
