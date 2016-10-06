#include "..\Headers\World Module.h"
#include "..\Headers\Galactic\StarCluster.h"

namespace World_Module {

	class WorldModule {
	public:
		Galactic::StarMap worldMap;

	};

}

World_Module::WorldModule instance;

__int32 World_Module::WorldModule_load() {
	return 0;
}
