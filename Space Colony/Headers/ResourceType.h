#pragma once

#include "Space Colony.h"

namespace Space_Colony {

	class ResourceRef;

	/*
	A mass and volume value.*/
	struct ResourceType {
	public:
		ResourceType();
		ResourceType(const ResourceType &orig);
		ResourceType(const size_t ms, const size_t vlm);

		static ResourceRef create();
		static ResourceRef create(const ResourceType &orig);
		static ResourceRef create(const size_t ms, const size_t vlm);
		static bool isLoaded(ResourceType *const id);
		static bool unloadType(ResourceType *const id);

		/*
		The mass of a unit of this ResourceType.*/
		size_t mass;
		/*
		The volume of a unit of this ResourceType.*/
		size_t volume;

		ResourceType & operator=(const ResourceType &right);
		bool operator==(const ResourceType &right) const;
		bool operator!=(const ResourceType &right) const;

	};

	/*
	A safe pointer it a pooled ResourceType.*/
	class ResourceRef {
	public:
		ResourceRef();
		ResourceRef(ResourceType *const orig);

		/*
		True if this reference correlates to a pooled ResourceType.*/
		bool check() const;
		/*
		Unbinds the pointer to the ResourceType.*/
		void unbind();

		ResourceRef & operator=(ResourceType *const right);
		bool operator==(ResourceType *const right) const;
		bool operator!=(ResourceType *const right) const;
		ResourceType & operator*();
		const ResourceType & operator*() const;
		ResourceType * operator->();
		const ResourceType * operator->() const;

		operator ResourceType *const ();
		operator const ResourceType * const() const;

	private:
		/*
		A pointer to a pooled ResourceType.*/
		ResourceType *instance;
		
	};

}
