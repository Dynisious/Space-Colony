#pragma once

/*
A namespace for all things shared within the game.*/
namespace Space_Colony {
	typedef __int32 faction_t;
	enum DefaultFactions {
		Faction_Neutral,
		Faction_Max
	};

	__int32 SpaceColony_load();

}
