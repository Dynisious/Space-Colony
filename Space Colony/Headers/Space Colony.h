#pragma once

#include "Maths\matrix.h"

/*
A namespace for all the objects of the game.*/
namespace Space_Colony {
	typedef Dyn_API::Maths::matrix<__int32, 2, 1> coordinate;
	typedef __int32 faction_type;
	enum class Game_Factions : faction_type {
		no_faction = -1,
		player = 0,
		pirate = 1,
		mixed = 2,
		contested = 3,
		maximum = 4
	};

}
