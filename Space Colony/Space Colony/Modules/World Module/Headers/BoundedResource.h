#pragma once

#include "World Module.h"
#include <unordered_map>
#include <stdexcept>

namespace World_Module {
	typedef __int32 resource;

	/*
	A collection of a particular type of resource. It has set limits on
	it's resource quantity which it will not exceed.*/
	class BoundedResource {
	public:
		/*
		Identifies a type of resource.*/
		typedef __int32 ResourceTypeID;

		BoundedResource();
		BoundedResource(const BoundedResource& orig);
		BoundedResource(const ResourceTypeID type);
		BoundedResource(const ResourceTypeID type, const resource min, const resource qnty, const resource max);

		/*
		True if these BoundedResources are of the same resource type.*/
		bool sameType(const BoundedResource& right) const;
		/*
		True if these BoundedResources are of the same type and have
		identical quantities and limits.*/
		bool identical(const BoundedResource& right) const;
		BoundedResource safeAddition(const resource shift, bool& error) const;
		BoundedResource safeSubtraction(const resource shift, bool& error) const;
		BoundedResource safeMultiplication(const resource shift, bool& error) const;
		BoundedResource safeDivision(const resource shift, bool& error) const;

		/*
		Sets the quantity_min of this BoundedResource. It will not set the
		minimum higher than the maximum, attempting to will return error as
		true. If the quantity is bellow the new minimum it will be adjusted.*/
		void set_quantityMin(const resource min, bool* const error = nullptr);
		resource get_quantityMin() const;
		/*
		Sets the quantity of this BoundedResource, throttles the quantity
		to remain within the limits and returns error as true.*/
		void set_quantity(const resource shift, bool* const error = nullptr);
		resource get_quantity() const;
		/*
		Sets the quantity_max of this BoundedResource. It will not set the
		minimum lower than the minimum, attempting to will return error as
		false. If the quantity is above the new maximum it will be adjusted.*/
		void set_quantityMax(const resource max, bool* const error = nullptr);
		resource get_quantityMax() const;
		ResourceTypeID get_typeID() const;

		BoundedResource& operator=(const resource right);
		BoundedResource& operator=(const BoundedResource& right);
		bool operator==(const BoundedResource& right) const;
		bool operator!=(const BoundedResource& right) const;
		BoundedResource& operator+=(const BoundedResource& right);
		BoundedResource operator+(const BoundedResource& right) const;
		BoundedResource& operator-=(const BoundedResource& right);
		BoundedResource operator-(const BoundedResource& right) const;
		BoundedResource& operator*=(const resource right);
		BoundedResource operator*(const resource right) const;
		BoundedResource& operator/=(const resource right);
		BoundedResource operator/(const resource right) const;

		operator __int32() const;

		__declspec(property(get = get_quantityMin, put = set_quantityMin)) resource _quantity_min;
		__declspec(property(get = get_quantityMin, put = set_quantityMin)) resource _quantity;
		__declspec(property(get = get_quantityMax, put = set_quantityMax)) resource _quantity_max;
		__declspec(property(get = get_typeID)) ResourceTypeID _typeID;


	private:
		/*
		The specific resource type of this BoundedResource.*/
		ResourceTypeID typeID;
		resource quantity_min;
		resource quantity;
		resource quantity_max;

	};

	typedef std::unordered_map<BoundedResource::ResourceTypeID, resource> ResourceMap;
	typedef std::unordered_map<BoundedResource::ResourceTypeID, BoundedResource> BoundedResourceMap;

}

class BoundedResources_TypeException : std::exception {
public:
	BoundedResources_TypeException();
	BoundedResources_TypeException(const BoundedResources_TypeException& orig);
	BoundedResources_TypeException(char const* Message);

};
