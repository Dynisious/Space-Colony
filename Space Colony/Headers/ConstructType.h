#pragma once

#include "TypeCounter.h"
#include "CombatStats.h"
#include <string>
#include <vector>

namespace Space_Colony {

	/*
	Defines a template for a type of construct which can be built on Planets.*/
	class ConstructType {
	public:
		ConstructType();
		ConstructType(const ConstructType &orig);
		ConstructType(const TypeCounter &rsrcShft, const TypeCounter &rsrcCpcty,
					  const TypeCounter &cntrctCst, const TypeCounter &rtrndRsrcs,
					  const std::string &nm, const CombatStats &cmbt);

		/*
		A counter of the change in resources produced by this type of construct.*/
		TypeCounter resourceShift;
		/*
		A counter of the quantity of resource units this type of construct can store.*/
		TypeCounter resourceCapacity;
		/*
		A counter of the resources required to build a new instance of this
		construct type.*/
		TypeCounter constructCost;
		/*
		A counter of the resources returned when de-constructing this construct type.*/
		TypeCounter returnedResources;
		/*
		A String representing the name of this type of Construct.*/
		std::string name;
		/*
		The stats required to represent this ConstructType in combat.*/
		CombatStats combat;

		ConstructType & operator=(const ConstructType &right);
		bool operator==(const ConstructType &right) const;
		bool operator!=(const ConstructType &right) const;

	};

	typedef std::vector<ConstructType> ConstructTypeVector;

}
