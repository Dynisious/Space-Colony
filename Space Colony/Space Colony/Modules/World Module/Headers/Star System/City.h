#pragma once

#include "Star System.h"
#include <unordered_map>

namespace World_Module {

	namespace Star_System {

		/*
		A City exists on a Planet and causes it's resources
		to shift while also providing functionalities and/or
		bonuses to the Planet it sits on.*/
		class City {
		public:
			/*
			A map of experience levels and unit counts
			representing ground forces.*/
			typedef std::unordered_map<unsigned __int32, unsigned __int32> GroundForces;
			typedef __int32 sizeValue;

			City();
			City(const City& orig);
			City(const ResourceMap& resrcChng, const FunctionTags funcnlty,
				 const sizeValue sz, const GroundForces& grndFrcs);

			const ResourceMap& get_resourceChange() const;
			ResourceMap& get_resourceChange();
			const GroundForces& get_groundForces() const;
			GroundForces& get_groundForces();
			FunctionTags get_funcionality() const;
			sizeValue get_size() const;

			City& operator=(const City& right);
			bool operator==(const City& right) const;
			bool operator!=(const City& right) const;

			__declspec(property(get = get_resourceChange)) ResourceMap _resourceChange;
			__declspec(property(get = get_groundForces)) GroundForces _groundForces;
			__declspec(property(get = get_funcionality)) FunctionTags _funcionality;
			__declspec(property(get = get_size)) sizeValue _size;

		private:
			/*
			Values determining how resources of different
			types shift due to this City.*/
			ResourceMap resourceChange;
			/*
			The ground forces in this City.*/
			GroundForces groundForces;
			/*
			A tag indicating the functionality which this
			City provides the Planet.*/
			FunctionTags funcionality;
			/*
			A value indicating the size of this City.*/
			sizeValue size;

		};

	}

}
