#include "..\Headers\BoundedResource.h"

World_Module::BoundedResource::BoundedResource()
	: BoundedResource(0) {}

World_Module::BoundedResource::BoundedResource(const BoundedResource & orig)
	: BoundedResource(orig.typeID, orig.quantity_min, orig.quantity, orig.quantity_max) {}

World_Module::BoundedResource::BoundedResource(const ResourceTypeID type)
	: BoundedResource(type, INT32_MIN, 0, INT32_MAX) {}

World_Module::BoundedResource::BoundedResource(const ResourceTypeID type, const resource min,
											   const resource qnty, const resource max)
	: typeID(type), quantity_min(min), quantity_max(max) {
	set_quantity(qnty);
}

bool World_Module::BoundedResource::sameType(const BoundedResource & right) const {
	return typeID == right.typeID;
}

bool World_Module::BoundedResource::identical(const BoundedResource & right) const {
	return sameType(right)
		&& quantity_min == right.quantity_min
		&& quantity == right.quantity
		&& quantity_max == right.quantity_max;
}

World_Module::BoundedResource World_Module::BoundedResource::safeAddition(const resource shift, bool & error) const {
	BoundedResource res(*this);
	res.set_quantity(quantity + shift, &error);
	return res;
}

World_Module::BoundedResource World_Module::BoundedResource::safeSubtraction(const resource shift, bool & error) const {
	BoundedResource res(*this);
	res.set_quantity(quantity - shift, &error);
	return res;
}

World_Module::BoundedResource World_Module::BoundedResource::safeMultiplication(const resource shift, bool & error) const {
	BoundedResource res(*this);
	res.set_quantity(quantity * shift, &error);
	return res;
}

World_Module::BoundedResource World_Module::BoundedResource::safeDivision(const resource shift, bool & error) const {
	BoundedResource res(*this);
	res.set_quantity(quantity / shift, &error);
	return res;
}

void World_Module::BoundedResource::set_quantityMin(const resource min, bool * const error) {
	if (min > quantity_max) {
		if (error == nullptr) {
			*error = true;
			return;
		}
	} else
		quantity_min = min;
	set_quantity(quantity);
}

World_Module::resource World_Module::BoundedResource::get_quantityMin() const {
	return quantity_min;
}

void World_Module::BoundedResource::set_quantityMax(const resource max, bool * const error) {
	if (max < quantity_min) {
		if (error == nullptr) {
			*error = true;
			return;
		}
	} else
		quantity_max = max;
	set_quantity(quantity);
}

World_Module::resource World_Module::BoundedResource::get_quantityMax() const {
	return quantity_min;
}

void World_Module::BoundedResource::set_quantity(const resource shift, bool * const error) {
	if (shift > quantity_max) {
		quantity = quantity_max;
		if (error != nullptr)
			*error = true;
	} else if (shift < quantity_min) {
		quantity = quantity_min;
		if (error != nullptr)
			*error = true;
	} else
		quantity = shift;
}

World_Module::resource World_Module::BoundedResource::get_quantity() const {
	return quantity;
}

World_Module::BoundedResource::ResourceTypeID World_Module::BoundedResource::get_typeID() const {
	return typeID;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator=(const resource right) {
	set_quantity(right);
	return *this;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator=(const BoundedResource & right) {
	typeID = right.typeID;
	set_quantity(right.quantity);
	return *this;
}

bool World_Module::BoundedResource::operator==(const BoundedResource & right) const {
	if (this == &right)
		return true;
	return sameType(right)
		&& quantity == right.quantity;
}

bool World_Module::BoundedResource::operator!=(const BoundedResource & right) const {
	if (this != &right)
		return true;
	return !sameType(right)
		|| quantity != right.quantity;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator+=(const BoundedResource & right) {
	if (!sameType(right))
		throw BoundedResources_TypeException();
	set_quantity(quantity + right.quantity);
	return *this;
}

World_Module::BoundedResource World_Module::BoundedResource::operator+(const BoundedResource & right) const {
	return BoundedResource(*this) += right;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator-=(const BoundedResource & right) {
	if (!sameType(right))
		throw BoundedResources_TypeException();
	set_quantity(quantity - right.quantity);
	return *this;
}

World_Module::BoundedResource World_Module::BoundedResource::operator-(const BoundedResource & right) const {
	return BoundedResource(*this) -= right;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator*=(const resource right) {
	set_quantity(quantity * right);
	return *this;
}

World_Module::BoundedResource World_Module::BoundedResource::operator*(const resource right) const {
	return BoundedResource(*this) *= right;
}

World_Module::BoundedResource & World_Module::BoundedResource::operator/=(const resource right) {
	set_quantity(quantity / right);
	return *this;
}

World_Module::BoundedResource World_Module::BoundedResource::operator/(const resource right) const {
	return BoundedResource(*this) /= right;
}

World_Module::BoundedResource::operator __int32() const {
	return quantity;
}

BoundedResources_TypeException::BoundedResources_TypeException()
	: exception("There was an error in the ResourceTypeIDs for the BoundedResources") {}

BoundedResources_TypeException::BoundedResources_TypeException(const BoundedResources_TypeException & orig)
	: exception(orig) {}

BoundedResources_TypeException::BoundedResources_TypeException(char const * Message)
	: exception(Message) {}
