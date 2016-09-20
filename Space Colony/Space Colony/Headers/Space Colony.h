#pragma once

#include <unordered_set>

#define CHANCE_1 128
#define APPLY_FRACTION(VALUE, NUMERATOR, DENOMINATOR) (VALUE * NUMERATOR / DENOMINATOR)

/*
The namespace for all things shared within the Space Colony game.*/
namespace Space_Colony {
	/*
	The type identifing a faction alignement in the Game.*/
	typedef __int32 faction_t;
	/*
	A Set of faction alignments.*/
	typedef std::unordered_set<faction_t> FactionSet;

	/*
	Returns the number of Factions in the game.*/
	__int32 countAllFactions();

	/*
	Returns iterates to iterate over every Faction value in the game.*/
	void iterateAllFactions(FactionSet::const_iterator start, FactionSet::const_iterator end);

}
