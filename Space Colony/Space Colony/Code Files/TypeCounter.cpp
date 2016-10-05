#include "..\Headers\TypeCounter.h"

Space_Colony::TypeCounter::TypeCounter()
	: counters(0) {}

Space_Colony::TypeCounter::TypeCounter(const TypeCounter & orig)
	: counters(orig.counters) {}

Space_Colony::TypeCounter::TypeCounter(const Map_t & shps)
	: counters(shps.size()) {
	for (const_iterator iter(shps.begin()), end(shps.end()); iter != end; iter++)
		setCounter(iter->first, iter->second);
	clean();
}

Space_Colony::TypeCounter::const_iterator Space_Colony::TypeCounter::begin() const {
	return counters.begin();
}

Space_Colony::TypeCounter::const_iterator Space_Colony::TypeCounter::end() const {
	return counters.end();
}

Space_Colony::TypeCounter::counter Space_Colony::TypeCounter::getCounter(TypeID id) const {
	if (counters.count(id) == 0)
		return 0;
	return counters.at(id);
}

Space_Colony::TypeCounter::counter Space_Colony::TypeCounter::setCounter(TypeID id, counter vl, bool * const error) {
	counter res(getCounter(id));
	if (vl > 0) {
		counters[id] = vl;
		if (error != nullptr)
			*error = true;
	} else {
		counters[id] = 0;
		if (error != nullptr)
			*error = false;
	}
	return res;
}

Space_Colony::TypeCounter::counter Space_Colony::TypeCounter::incrementCounter(TypeID id, counter inc, bool * const error) {
	return setCounter(id, getCounter(id) + inc, error);
}

Space_Colony::TypeCounter::counter Space_Colony::TypeCounter::erase(TypeID id) {
	counter res(0);
	counters.erase(id);
	return res;
}

bool Space_Colony::TypeCounter::contains(TypeID id) const {
	return counters.count(id) != 0;
}

void Space_Colony::TypeCounter::clean() {
	Map_t saved(counters.size());
	for (const_iterator iter(begin()), end(end()); iter != end; iter++)
		if (iter->second != 0)
			saved[iter->first] = iter->second;
	counters = saved;
}

__int32 Space_Colony::TypeCounter::size() const {
	return counters.size();
}

__int32 Space_Colony::TypeCounter::sum() const {
	__int32 res(0);
	for (const_iterator iter(begin()), end(end()); iter != end; iter++)
		//Accumulate all the counters in this TypeCounter.
		res += iter->second;
	return res;
}

Space_Colony::TypeCounter & Space_Colony::TypeCounter::operator=(const TypeCounter & right) {
	counters = right.counters;
	return *this;
}

bool Space_Colony::TypeCounter::operator==(const TypeCounter & right) const {
	return (this == &right)
		|| (counters == right.counters);
}

bool Space_Colony::TypeCounter::operator!=(const TypeCounter & right) const {
	return !operator==(right);
}

Space_Colony::TypeCounter & Space_Colony::TypeCounter::operator+=(const TypeCounter & right) {
	return operator+=(right.counters);
}

Space_Colony::TypeCounter Space_Colony::TypeCounter::operator+(const TypeCounter & right) const {
	return TypeCounter(*this) += right;
}

Space_Colony::TypeCounter & Space_Colony::TypeCounter::operator+=(const Map_t & right) {
	const_iterator iter, end;
	for (iter = begin(), end = TypeCounter::end(); iter != end; iter++)
		//Iterate each counter in this TypeCounter.
		if (right.count(iter->first) != 0)
			//The counter is also in right.
			counters[iter->first] += right.at(iter->first);
	for (iter = right.begin(), end = right.end(); iter != end; iter++)
		//Iterate each counter in right.
		if (!contains(iter->first))
			//The counter is not in this TypeCounter.
			counters[iter->first] = iter->second;
	return *this;
}

Space_Colony::TypeCounter Space_Colony::TypeCounter::operator+(const Map_t & right) const {
	return TypeCounter(*this) += right;
}

Space_Colony::TypeCounter & Space_Colony::TypeCounter::operator-=(const TypeCounter & right) {
	return operator-=(right.counters);
}

Space_Colony::TypeCounter Space_Colony::TypeCounter::operator-(const TypeCounter & right) const {
	return TypeCounter(*this) -= right;
}

Space_Colony::TypeCounter & Space_Colony::TypeCounter::operator-=(const Map_t & right) {
	const_iterator iter, end;
	for (iter = begin(), end = TypeCounter::end(); iter != end; iter++)
		//Iterate each counter in this TypeCounter.
		if (right.count(iter->first) != 0)
			//The counter is also in right.
			setCounter(iter->first, iter->second - right.at(iter->first));
	for (iter = right.begin(), end = right.end(); iter != end; iter++)
		incrementCounter(iter->first, -iter->second);
	return *this;
}

Space_Colony::TypeCounter Space_Colony::TypeCounter::operator-(const Map_t & right) const {
	return TypeCounter(*this) -= right;
}

Space_Colony::TypeCounter::counter Space_Colony::TypeCounter::operator[](TypeID id) const {
	return getCounter(id);
}

Space_Colony::TypeCounter::operator const Map_t() const {
	return counters;
}
