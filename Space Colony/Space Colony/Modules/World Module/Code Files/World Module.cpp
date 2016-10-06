#include "..\Headers\World Module.h"
#include "..\Headers\Galaxy.h"
#include "..\Headers\Transition.h"
#include <list>

namespace World_Module {

	class WorldModule {
	public:
		typedef std::list<Transition> TransitList;

		Galaxy worldMap;
		TransitList transitions;

	};

}

World_Module::WorldModule instance;

__int32 World_Module::WorldModule_load() {
	return 0;
}
