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
		res += iter->second;
	return res;
}

__int32 Space_Colony::TypeCounter::getCounter(const type_id id) const {
	if (counters.count(id) == 0)
		return 0;
	else
		return counters.at(id);
}

__int32 Space_Colony::TypeCounter::setCounter(const type_id id, const __int32 val) {
	__int32 res(getCounter(id));
	if (val == 0)
		counters.erase(id);
	else
		counters.insert_or_assign(id, val);
	return res;
}

__int32 Space_Colony::TypeCounter::incCounter(const type_id id, const __int32 val) {
	return setCounter(id, getCounter(id) + val);
}

TypeCounter Space_Colony::TypeCounter::getNeg() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second < 0)
			res.emplace(*iter);
	return res;
}

TypeCounter Space_Colony::TypeCounter::getPos() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second > 0)
			res.emplace(*iter);
	return res;
}

bool Space_Colony::TypeCounter::isPos() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second < 0)
			return false;
	return true;
}

bool Space_Colony::TypeCounter::isNeg() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second > 0)
			return false;
	return true;
}

TypeCounter Space_Colony::TypeCounter::shared(const CounterMap & right) const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (right.count(iter->first) != 0)
			res.emplace(*iter);
	return res;
}

TypeCounter Space_Colony::TypeCounter::difference(const CounterMap & right) const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (right.count(iter->first) == 0)
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
		if (iter->second > right.getCounter(iter->first))
			return false;
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) > iter->second)
			return false;
	return true;
}

bool Space_Colony::TypeCounter::operator>=(const TypeCounter & right) const {
	return !operator<(right);
}

bool Space_Colony::TypeCounter::operator>(const TypeCounter & right) const {
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second < right.getCounter(iter->first))
			return false;
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) < iter->second)
			return false;
	return true;
}

bool Space_Colony::TypeCounter::operator<=(const TypeCounter & right) const {
	return !operator>(right);
}

TypeCounter & Space_Colony::TypeCounter::operator+=(const TypeCounter & right) {
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		incCounter(iter->first, iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator+(const TypeCounter & right) const {
	return TypeCounter(*this) += right;
}

TypeCounter Space_Colony::TypeCounter::operator-() const {
	CounterMap res(size());
	for (const_iterator iter(begin()), end(end()); iter != end; ++iter)
		res.insert_or_assign(iter->first, -iter->second);
	return res;
}

TypeCounter & Space_Colony::TypeCounter::operator-=(const TypeCounter & right) {
	for (const_iterator iter(right.begin()), end(right.end()); iter != end; ++iter)
		incCounter(iter->first, -iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator-(const TypeCounter & right) const {
	return TypeCounter(*this) -= right;
}

Space_Colony::TypeCounter::operator const CounterMap &() const {
	return counters;
}

Space_Colony::TypeCounter::operator CounterMap () const {
	return counters;
}
