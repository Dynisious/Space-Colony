#include "..\Headers\Ship Types\ShipType Collection.h"

Combat_Module::Ship_Types::ShipTypeCollection::ShipTypeCollection() {}

Combat_Module::Ship_Types::ShipTypeCollection::ShipTypeCollection(const ShipTypeCollection & orig)
	: ShipTypes_ByID(orig.ShipTypes_ByID), ShipTypes_ByName(orig.ShipTypes_ByName), ShipTypes_BySize(orig.ShipTypes_BySize) {}

bool Combat_Module::Ship_Types::ShipTypeCollection::loadType(const ShipType& type) {
	if (ShipTypes_ByID.count(type._ID) != 0)
		return false;
	ShipTypes_ByID[type._ID] = type;
	ShipTypes_ByName[type._name].push_back(type);
	ShipTypes_BySize[type._stats.sizeValue].push_back(type);
	return true;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::unloadType(const ShipType& type) {
	if (ShipTypes_ByName.count(type._name) != 0) {
		ShipType_List::iterator iter(ShipTypes_ByName[type._name].begin()), end(ShipTypes_ByName[type._name].end());
		for (; iter != end; iter++)
			if (iter->valueEquals(type)) {
				ShipTypes_ByID.erase(iter->_ID);
				ShipTypes_ByName[type._name].remove(type);
				ShipTypes_BySize[type._stats.sizeValue].remove(type);
				return true;
			}
	}
	return false;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::unloadType(const Space_Colony::Ships::Type_ID ID) {
	if (ShipTypes_ByID.count(ID) != 0) {
		ShipType type(ShipTypes_ByID[ID]);
		ShipTypes_ByID.erase(ID);
		ShipTypes_ByName[type._name].remove(type);
		ShipTypes_BySize[type._stats.sizeValue].remove(type);
		return true;
	}
	return false;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::getFromID(const Space_Colony::Ships::Type_ID ID, ShipType& type) const {
	if (ShipTypes_ByID.count(ID) != 0) {
		type = ShipTypes_ByID.at(ID);
		return true;
	}
	return false;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::getFromName(const ShipType::name_str name, ShipTypes_NamedMap::mapped_type& types) const {
	if (ShipTypes_ByName.count(name) != 0) {
		types = ShipTypes_ByName.at(name);
		return true;
	}
	return false;
}

bool Combat_Module::Ship_Types::ShipTypeCollection::getFromSize(const ShipType_Stats::size_t size, ShipTypes_SizedMap::mapped_type& types) const {
	if (ShipTypes_BySize.count(size) != 0) {
		types = ShipTypes_BySize.at(size);
		return true;
	}
	return false;
}

void Combat_Module::Ship_Types::ShipTypeCollection::correctTypeID(ShipType & type) const {
	if (ShipTypes_ByName.count(type._name) != 0) {
		ShipTypes_NamedMap::mapped_type namedTypes(ShipTypes_ByName.at(type._name));
		for (ShipTypes_NamedMap::mapped_type::iterator iter(namedTypes.begin()),
			 end(namedTypes.end()); iter != end; iter++)
			if (iter->valueEquals(type))
				return;
	}
}

__int32 Combat_Module::Ship_Types::ShipTypeCollection::loadedTypes() const {
	return ShipTypes_ByID.size();
}

void Combat_Module::Ship_Types::ShipTypeCollection::iterateByID(ShipType_IdMap::const_iterator & start, ShipType_IdMap::const_iterator & end) {
	start = ShipTypes_ByID.begin();
	end = ShipTypes_ByID.end();
}

void Combat_Module::Ship_Types::ShipTypeCollection::iterateByName(ShipTypes_NamedMap::const_iterator & start, ShipTypes_NamedMap::const_iterator & end) {
	start = ShipTypes_ByName.begin();
	end = ShipTypes_ByName.end();
}

void Combat_Module::Ship_Types::ShipTypeCollection::iterateBySize(ShipTypes_SizedMap::const_iterator & start, ShipTypes_SizedMap::const_iterator & end) {
	start = ShipTypes_BySize.begin();
	end = ShipTypes_BySize.end();
}
