#include "TypeCounter.h"

using namespace Space_Colony;

Space_Colony::TypeCounter::TypeCounter()
	: counters() {}

Space_Colony::TypeCounter::TypeCounter(const TypeCounter & orig)
	: counters(orig.counters) {}

Space_Colony::TypeCounter::TypeCounter(const CounterMap & orig)
	: counters(orig.size()) {
	for (const_iterator iter(orig.begin()), end(orig.end()); iter != end; ++iter)
		if (iter->second != 0)
			counters.emplace(*iter);
}

Space_Colony::TypeCounter::const_iterator Space_Colony::TypeCounter::begin() const {
	return counters.begin();
}

Space_Colony::TypeCounter::const_iterator Space_Colony::TypeCounter::end() const {
	return counters.end();
}

size_t Space_Colony::TypeCounter::size() const {
	return counters.size();
}

bool Space_Colony::TypeCounter::empty() const {
	return counters.empty();
}

__int32 Space_Colony::TypeCounter::sum() const {
	__int32 res(0);
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Accumulate all counters.
		res += iter->second;
	return res;
}

__int32 Space_Colony::TypeCounter::getCounter(const type_id id) const {
	if (counters.count(id) == 0)
		//The counter does not exists.
		return 0;
	else
		//The counter exists.
		return counters.at(id);
}

__int32 Space_Colony::TypeCounter::setCounter(const type_id id, const __int32 val) {
	__int32 res(getCounter(id));
	if (val == 0)
		//The counter is zeroed, remove it.
		counters.erase(id);
	else
		//Assign the counter.
		counters.insert_or_assign(id, val);
	return res;
}

__int32 Space_Colony::TypeCounter::incCounter(const type_id id, const __int32 val) {
	return setCounter(id, getCounter(id) + val);
}

TypeCounter Space_Colony::TypeCounter::getNeg() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second < 0)
			//The counter is negative and should be returned.
			res.emplace(*iter);
	return res;
}

TypeCounter Space_Colony::TypeCounter::getPos() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second > 0)
			//The counter is positive and should be removed.
			res.emplace(*iter);
	return res;
}

bool Space_Colony::TypeCounter::isPos() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second < 0)
			//The counter is negative, return false.
			return false;
	return true;
}

bool Space_Colony::TypeCounter::isNeg() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second > 0)
			//The counter is positive, return false.
			return false;
	return true;
}

TypeCounter Space_Colony::TypeCounter::shared(const CounterMap & right) const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (right.count(iter->first) != 0)
			//The counter is shared and the counter should be returned.
			res.emplace(*iter);
	return res;
}

TypeCounter Space_Colony::TypeCounter::difference(const CounterMap & right) const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (right.count(iter->first) == 0)
			//The counter is unique and the counter should be returned.
			res.emplace(*iter);
	return res;
}

TypeCounter & Space_Colony::TypeCounter::operator=(const TypeCounter & right) {
	counters = right;
	return *this;
}

bool Space_Colony::TypeCounter::operator==(const TypeCounter & right) const {
	return (this == &right)
		|| (counters == right.counters);
}

bool Space_Colony::TypeCounter::operator!=(const TypeCounter & right) const {
	return !operator==(right);
}

bool Space_Colony::TypeCounter::operator<(const TypeCounter & right) const {
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second > right.getCounter(iter->first))
			//This counter is greater, return false.
			return false;
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Iterate right's counters.
		if (getCounter(iter->first) > iter->second)
			//This counter is greater, return false.
			return false;
	return true;
}

bool Space_Colony::TypeCounter::operator>=(const TypeCounter & right) const {
	return !operator<(right);
}

bool Space_Colony::TypeCounter::operator>(const TypeCounter & right) const {
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate all counters.
		if (iter->second < right.getCounter(iter->first))
			//This counter is less, return false.
			return false;
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Iterate right's counters.
		if (getCounter(iter->first) < iter->second)
			//This counter is less, return false.
			return false;
	return true;
}

bool Space_Colony::TypeCounter::operator<=(const TypeCounter & right) const {
	return !operator>(right);
}

TypeCounter & Space_Colony::TypeCounter::operator+=(const TypeCounter & right) {
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Iterate and increment all counters by right.
		incCounter(iter->first, iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator+(const TypeCounter & right) const {
	return TypeCounter(*this) += right;
}

TypeCounter Space_Colony::TypeCounter::operator-() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		//Iterate and negate all counters.
		res.emplace(iter->first, -iter->second);
	return res;
}

TypeCounter & Space_Colony::TypeCounter::operator-=(const TypeCounter & right) {
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Iterate and increment all counters by -right.
		incCounter(iter->first, -iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator-(const TypeCounter & right) const {
	return TypeCounter(*this) -= right;
}

TypeCounter & Space_Colony::TypeCounter::operator*=(const double right) {
	for (const_iterator iter(counters.begin()), end(counters.end()); iter != end; ++iter)
		//Iterate and multiply all counters by right.
		setCounter(iter->first, iter->second * right);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator*(const double right) const {
	return TypeCounter(*this) *= right;
}

TypeCounter & Space_Colony::TypeCounter::operator/=(const double right) {
	for (const_iterator iter(counters.begin()), end(counters.end()); iter != end; ++iter)
		//Iterate and divide all counters by right.
		setCounter(iter->first, iter->second / right);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator/(const double right) const {
	return TypeCounter(*this) /= right;
}

Space_Colony::TypeCounter::operator const CounterMap &() const {
	return counters;
}

Space_Colony::TypeCounter::operator CounterMap () const {
	return counters;
}
