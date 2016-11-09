#pragma once

#include "Planetary.h"
#include "TypeCounter.h"
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <xhash>

namespace Space_Colony {

	namespace World_Module {

		namespace Galacitc {

			namespace Planetary {

				enum class ConstructType_FunctionTags : __int32;

				/*
				Defines a template for a type of construct which can be
				built on Planets.*/
				class ConstructType {
				public:
					typedef std::unordered_set<ConstructType_FunctionTags> ConstructTags;

					ConstructType();
					ConstructType(const ConstructType &orig);
					ConstructType(const TypeCounter &rsrcShft, const TypeCounter &dcnstrctRtrn,
								  ConstructTags tgs, const std::string &nm, const TypeCounter &rsrcCpcty,
								  const TypeCounter &cnstrctCst);

					static ConstructType *const create();
					static ConstructType *const create(const ConstructType &orig);
					static ConstructType *const create(const TypeCounter &rsrcShft, const TypeCounter &dcnstrctRtrn,
													   ConstructTags tgs, const std::string &nm, const TypeCounter &rsrcCpcty,
													   const TypeCounter &cnstrctCst);
					static bool isLoaded(const ConstructType *const id);
					static bool unloadType(const ConstructType *const id);

					const TypeCounter & getResourceCapacity() const;
					TypeCounter setResourceCapacity(const TypeCounter &rsrcCpcty);
					size_t setResourceCapacity(const __int32 rsrc, const size_t val);
					const TypeCounter & getConstructCost() const;
					TypeCounter setConstructCost(const TypeCounter &cnstrctCst);
					size_t setConstructCost(const __int32 rsrc, const size_t val);

					/*
					A counter of the change in resources produced by this
					type of construct.*/
					TypeCounter resourceShift;
					/*
					A counter of the resources returned when de-constructing
					this construct type.*/
					TypeCounter deconstructReturn;
					/*
					A collection of tags for this type of construct.*/
					ConstructTags tags;
					/*
					A String representing the name of this type of Construct.*/
					std::string name;

					ConstructType & operator=(const ConstructType &right);
					bool operator==(const ConstructType &right) const;
					bool operator!=(const ConstructType &right) const;

				private:
					/*
					A counter of the quantity of resources this type of
					construct can store.*/
					TypeCounter resourceCapacity;
					/*
					A counter of the resources required to build a new
					instance of this construct type.*/
					TypeCounter constructCost;

				};

				/*
				A Construct represents a actualised instance of a ConstructType.*/
				class Construct {
				public:
					Construct();
					Construct(const Construct &orig);
					Construct(ConstructType *const orig, const bool actv);

					/*
					True if the TypeID for this Construct is valid in the game.*/
					bool check() const;
					/*
					Unbinds the pointer to the ConstructType.*/
					void unbind();

					/*
					True if the Construct is currently active and is producing a change in resources.*/
					bool active;

					Construct & operator=(const Construct &right);
					bool operator==(const Construct &right) const;
					bool operator!=(const Construct &right) const;
					ConstructType & operator*();
					const ConstructType & operator*() const;
					ConstructType *const operator->();
					const ConstructType *const operator->() const;

					operator ConstructType const*();
					operator const ConstructType const*() const;

				private:
					/*
					A pointer to a ConstructType which represents this Construct.*/
					ConstructType *instance;

				};

				enum class ConstructType_FunctionTags : __int32 {
					Terestrial = 0,
					Orbital = 1,
					City = 2,
					Ship_Construction = 3,
					Orbital_Defence = 4,
					Terestrial_Defence = 5,
					Agricultural = 6,
					Constant_Drain = 7,
					maximum = 8
				};

			}

		}

	}

}

namespace std {

	template<>
	class hash<Space_Colony::World_Module::Galacitc::Planetary::ConstructType> {
	public:
		size_t operator()(const Space_Colony::World_Module::Galacitc::Planetary::ConstructType &cnstrct) const {
			size_t res(1);
			for (auto iter(cnstrct.tags.begin()), end(cnstrct.tags.end()); iter != end; ++iter)
				res *= ( __int32 ) *iter;
			for (auto iter(cnstrct.resourceShift.begin()), end(cnstrct.resourceShift.end()); iter != end; ++iter)
				res *= iter->first ^ iter->second;
			for (auto iter(cnstrct.deconstructReturn.begin()), end(cnstrct.deconstructReturn.end()); iter != end; ++iter)
				res *= iter->first ^ iter->second;
			for (auto iter(cnstrct.getResourceCapacity().begin()), end(cnstrct.getResourceCapacity().end()); iter != end; ++iter)
				res *= iter->first ^ iter->second;
			for (auto iter(cnstrct.getConstructCost().begin()), end(cnstrct.getConstructCost().end()); iter != end; ++iter)
				res *= iter->first ^ iter->second;
			return res * hash<std::string>()(cnstrct.name);
		}

	};

	template<>
	class hash<Space_Colony::World_Module::Galacitc::Planetary::Construct> {
	public:
		size_t operator()(const Space_Colony::World_Module::Galacitc::Planetary::Construct &cnstrct) const {
			return ( size_t ) (const Space_Colony::World_Module::Galacitc::Planetary::ConstructType *) cnstrct;
		}

	};

}
