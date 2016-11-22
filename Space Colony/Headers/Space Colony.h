#pragma once

/*
A namespace for all things in the Space Colony game.*/
namespace Space_Colony {
	typedef __int32 faction_type;
	struct Game_Factions {
		static const faction_type player = 0,
			no_faction = -1,
			conflicted = -2,
			mixed = -3,
			minimum = -4;
	};

}
