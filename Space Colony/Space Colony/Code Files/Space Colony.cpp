#include "..\Headers\Space Colony.h"

int main() {
	return 0;
}

namespace Space_Colony {

	/*
	The central module for the Space Colony game.*/
	struct SpaceColonyModule {
	public:
		/*
		A Set of all factions in the game.*/
		FactionSet allFactions;

	};

}

Space_Colony::SpaceColonyModule instance;

__int32 Space_Colony::countAllFactions() {
	return instance.allFactions.size();
}

void Space_Colony::iterateAllFactions(FactionSet::const_iterator start, FactionSet::const_iterator end) {
	start = instance.allFactions.begin();
	end = instance.allFactions.end();
}
