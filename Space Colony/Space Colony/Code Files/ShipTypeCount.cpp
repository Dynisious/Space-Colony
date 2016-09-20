#include "..\Shared Headers\Ships\ShipTypeCount.h"

Space_Colony::Ships::ShipTypeCount::ShipTypeCount() {}

Space_Colony::Ships::ShipTypeCount::ShipTypeCount(const ShipTypeCount & orig) {
	operator=(orig);
}

void Space_Colony::Ships::ShipTypeCount::offsetCounter(const Space_Colony::Ships::Type_ID ID, const __int32 change) {
	setCounter(ID, ships.at(ID) + change);
}

void Space_Colony::Ships::ShipTypeCount::setCounter(const Space_Colony::Ships::Type_ID ID, const unsigned __int32 val) {
	if (val < 0)
		ships.at(ID) = 0;
	else
		ships.at(ID) = val;
}

__int32 Space_Colony::Ships::ShipTypeCount::getCounter(const Space_Colony::Ships::Type_ID ID) const {
	return ships.at(ID);
}

void Space_Colony::Ships::ShipTypeCount::iterateByID(ShipTypeCounterMap::const_iterator & start, ShipTypeCounterMap::const_iterator & end) const {
	start = ships.begin();
	end = ships.end();
}

bool Space_Colony::Ships::ShipTypeCount::erase(Space_Colony::Ships::Type_ID ID) {
	return ships.erase(ID);
}

Space_Colony::Ships::ShipTypeCount & Space_Colony::Ships::ShipTypeCount::operator=(const ShipTypeCount & orig) {
	ships = orig.ships;
	return *this;
}

bool Space_Colony::Ships::ShipTypeCount::operator==(const ShipTypeCount & orig) const {
	if (this == &orig)
		return true;
	return ships == orig.ships;
}

bool Space_Colony::Ships::ShipTypeCount::operator!=(const ShipTypeCount & orig) const {
	if (this != &orig)
		return true;
	return ships != orig.ships;
}

Space_Colony::Ships::ShipTypeCount & Space_Colony::Ships::ShipTypeCount::operator+=(const ShipTypeCount & right) {
	for (ShipTypeCounterMap::const_iterator iter(ships.begin()), end(ships.end()); iter != end; iter++)
		if (right.ships.count(iter->first) != 0)
			//If there is a value to increment this counter in "right".
			offsetCounter(iter->first, right.ships.at(iter->first));
	return *this;
}

Space_Colony::Ships::ShipTypeCount Space_Colony::Ships::ShipTypeCount::operator+(const ShipTypeCount & right) const {
	return ShipTypeCount(*this) += right;
}
