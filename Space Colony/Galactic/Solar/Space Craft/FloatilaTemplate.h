#pragma once

#include "SpaceCraft.h"

namespace Space_Colony {

	namespace Galactic {

		namespace Solar {

			namespace SpaceCraft {
#pragma region Craft Types
				/*
				Typed in size order (small to large).

				- Small craft can:
				- Invade colonised Planets (to capture Colonies rather than destroy).
				- Need no source of fuel to survive.
				- Are cheap and quick to build.
				- Medium craft can:
				- Siege colonised Planets to destroy the Colony.
				- Need no source of fuel to survive.
				- Are reasonably to pay for and build.
				- Large craft can:
				- Siege colonised Planets to destroy the Colony.
				- Require a supply of gas fuel to survive (Running out of fuel
				means the Floatila is unable to move).
				- Are expensive and take a long time to build.
				- Are heavily armoured.
				*/
				enum CraftTypes {
					/*
					Inteceptors are:
					- Small
					- Cheap
					- Reasonable protection vs small craft
					- Reasonable damage vs small craft
					- Immune vs Gunships and > Frigates
					*/
					Inteceptor,
					/*
					Bombers are:
					- Small
					- Cheap
					- Poor protection vs small craft
					- Poor damage vs small craft
					- Better damage vs >Gunships
					- Immune vs >Frigates
					*/
					Bomber,
					/*
					Gunships are:
					- Small
					- Low Cost
					- Reasonable protection vs small craft
					- Reasonable damage vs small craft
					- Can attack multiple targets at once
					- Immune vs >Frigates
					*/
					Gunship,
					/*
					Frigates are:
					- Small
					- Reasonable Cost
					- Good protection vs small craft
					- Low damage vs medium craft
					- Immune vs >Frigates
					*/
					Frigate,
					/*
					FuelCows are:
					- Medium
					- Reasonable Cost
					- Good protection vs small craft
					- Unarmed
					- Immune vs >Cruiser
					*/
					FuelCow,
					/*
					Destroyers are:
					- Medium
					- Good Cost
					- Reasonable protection vs medium craft
					- High damage vs medium craft
					- Extend the fuel lifetime of large craft
					*/
					Destroyer,
					/*
					Destroyers are:
					- Medium
					- Medium Cost
					- Good protection vs medium craft
					- Good damage vs medium craft
					*/
					Cruiser,
					/*
					Destroyers are:
					- Large
					- Medium Cost
					- Good protection vs medium craft
					- Unarmed
					- Require a supply of gas as fuel
					- Stores a reasonable supply of gas fuel
					- Required to support a population of <Frigate craft
					*/
					Carrier,
					/*
					- Large
					- High Cost
					- High protection
					- High damage
					- Stores a small supply of gas fuel
					- Require a supply of gas as fuel
					*/
					Dreadnought,
					CraftTypes_max
				};
#pragma endregion

				/*
				A template for Floatilas*/
				class FloatilaTemplate final {
				public:
					FloatilaTemplate();
					FloatilaTemplate(unsigned __int32* const cft);

					const unsigned __int32* getCraft();

					__declspec(property(get = getCraft)) const unsigned __int32* craft_prop;

				private:
					unsigned __int32 craft[CraftTypes_max];

				};

			}

		}

	}

}
