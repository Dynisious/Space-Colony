#pragma once

#include "Galactic.h"
#include "Solar\StarSystem.h"

namespace Space_Colony {

	namespace Galactic {

		/*
		A Galaxy contains a network of StarSystems.*/
		class Galaxy final {
		public:
			Galaxy();
			Galaxy(Solar::StarSystem* const sys, unsigned __int32 sys_c);
			~Galaxy();

			/*
			Fills the array of StarSystems with the contents of the passed array.*/
			Solar::StarSystem* setSystems(Solar::StarSystem* const sys);
			/*
			Redimensionalises the array of StarSystems to the passed size and
			then fills it with the contents of the passed array.*/
			Solar::StarSystem* setSystems(Solar::StarSystem* const sys, unsigned __int32 sys_c);
			/*
			Returns a pointer to the array of StarSystems.*/
			Solar::StarSystem* getSystems();
			/*
			Returns the size of the array of StarSystems.*/
			unsigned __int32 getSystemsCount();

			__declspec(property(get = getSystems, put = setSystems)) Solar::StarSystem* systems_prop;

		private:
			Solar::StarSystem* systems;
			unsigned __int32 systems_c;

		};

	}

}
