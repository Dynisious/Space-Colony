#include "TypeCounter.h"

using namespace Space_Colony;

Space_Colony::TypeCounter::TypeCounter()
	: counters(0) {}

Space_Colony::TypeCounter::TypeCounter(const size_t cnt)
	: counters(cnt) {}

Space_Colony::TypeCounter::TypeCounter(const TypeCounter & orig)
	: counters(orig) {}

Space_Colony::TypeCounter::TypeCounter(const CounterMap & orig)
	: counters(orig.size()) {
	//Iterate all the counters in the passed map.
	for (auto iter(orig.begin()), end(orig.end()); iter != end; ++iter)
		//Only non 0 counters should be added.
		if (iter->second != 0)
			counters.emplace(*iter);
}

TypeCounter::const_iterator Space_Colony::TypeCounter::begin() const {
	return counters.begin();
}

TypeCounter::const_iterator Space_Colony::TypeCounter::end() const {
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
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Accumulate the counter to the sum of all counters.
		res += iter->second;
	return res;
}

bool Space_Colony::TypeCounter::contains(const __int32 key) const {
	return counters.count(key) != 0;
}

__int32 Space_Colony::TypeCounter::getCounter(const __int32 key) const {
	if (contains(key))
		//Return the counter is the key is found.
		return counters.at(key);
	else
		//Return 0 if the key is not found.
		return 0;
}

__int32 Space_Colony::TypeCounter::setCounter(const __int32 key, const __int32 val) {
	//Store the current counter.
	__int32 res(getCounter(key));
	if (val == 0)
		//If the counter is being set to 0, remove it.
		counters.erase(key);
	else
		//If the value is non 0 assign it.
		counters.insert_or_assign(key, val);
	//Return the old counter.
	return res;
}

__int32 Space_Colony::TypeCounter::incCounter(const __int32 key, const __int32 inc) {
	//Set the counter to it's current value plus the increment.
	return setCounter(key, getCounter(key) + inc);
}

TypeCounter Space_Colony::TypeCounter::getNeg() const {
	//Create a result counter with enough spaces for all the counters.
	TypeCounter res(size());
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second < 0)
			//If the counter is negative add it to the result.
			res.counters.emplace(*iter);
	//Return the result counter.
	return res;
}

TypeCounter Space_Colony::TypeCounter::getPos() const {
	//Create a result counter with enough spaces for all the counters.
	TypeCounter res(size());
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second > 0)
			//If the counter is positive add it to the result.
			res.counters.emplace(*iter);
	//Return the result counter.
	return res;
}

bool Space_Colony::TypeCounter::isPos() const {
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second < 0)
			//Return false if the counter is negative.
			return false;
	return true;
}

bool Space_Colony::TypeCounter::isNeg() const {
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (iter->second > 0)
			//Return false if the counter is positive.
			return false;
	return true;
}

TypeCounter Space_Colony::TypeCounter::shared(const TypeCounter & cnts) const {
	//Create a result counter with enough spaces for all the counters.
	TypeCounter res(size());
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (cnts.contains(iter->first))
			//If the key is shared in both counters, include it.
			res.counters.emplace(*iter);
	//Return the result counter.
	return res;
}

TypeCounter Space_Colony::TypeCounter::different(const TypeCounter & cnts) const {
	//Create a result counter with enough spaces for all the counters.
	TypeCounter res(size());
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		if (!cnts.contains(iter->first))
			//If the key is unique to this counter, include it.
			res.counters.emplace(*iter);
	//Return the result counter.
	return res;
}

TypeCounter & Space_Colony::TypeCounter::operator=(const TypeCounter & right) {
	counters = right.counters;
	return *this;
}

bool Space_Colony::TypeCounter::operator==(const CounterMap & right) const {
	return counters == right;
}

bool Space_Colony::TypeCounter::operator!=(const CounterMap & right) const {
	return !operator==(right);
}

bool Space_Colony::TypeCounter::operator<(const CounterMap & right) const {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) >= iter->second)
			//If not '<' return false.
			return false;
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Check whether the counter is in 'right'.
		if (right.count(iter->first) != 0) {
			if (iter->second >= right.at(iter->first))
				//If not '<' return false.
				return false;
		} else {
			if (iter->second >= 0)
				//If not '<' return false.
				return false;
		}
	return true;
}

bool Space_Colony::TypeCounter::operator>=(const CounterMap & right) const {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) < iter->second)
			//If not '>=' return false.
			return false;
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Check whether the counter is in 'right'.
		if (right.count(iter->first) != 0) {
			if (iter->second < right.at(iter->first))
				//If not '>=' return false.
				return false;
		} else {
			if (iter->second < 0)
				//If not '>=' return false.
				return false;
		}
	return true;
}

bool Space_Colony::TypeCounter::operator>(const CounterMap & right) const {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) <= iter->second)
			//If not '>' return false.
			return false;
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Check whether the counter is in 'right'.
		if (right.count(iter->first) != 0) {
			if (iter->second <= right.at(iter->first))
				//If not '>' return false.
				return false;
		} else {
			if (iter->second <= 0)
				//If not '>' return false.
				return false;
		}
	return true;
}

bool Space_Colony::TypeCounter::operator<=(const CounterMap & right) const {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		if (getCounter(iter->first) > iter->second)
			//If not '<=' return false.
			return false;
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Check whether the counter is in 'right'.
		if (right.count(iter->first) != 0) {
			if (iter->second > right.at(iter->first))
				//If not '<=' return false.
				return false;
		} else {
			if (iter->second > 0)
				//If not '<=' return false.
				return false;
		}
	return true;
}

TypeCounter & Space_Colony::TypeCounter::operator+=(const CounterMap & right) {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Increment the counter by 'right'.
		incCounter(iter->first, iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator+(const CounterMap & right) const {
	return TypeCounter(*this) += right;
}

TypeCounter & Space_Colony::TypeCounter::operator-=(const CounterMap & right) {
	//Iterate all 'right's counters.
	for (auto iter(right.begin()), end(right.end()); iter != end; ++iter)
		//Decrement the counter by 'right'.
		incCounter(iter->first, -iter->second);
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator-(const CounterMap & right) const {
	return TypeCounter(*this) -= right;
}

TypeCounter Space_Colony::TypeCounter::operator-() const {
	//Create the result counter with enough spaces for all the counters.
	TypeCounter res(size());
	//Iterate all counters.
	for (auto iter(begin()), end(end()); iter != end; ++iter)
		//Assign the negative of the counter.
		res.counters.insert_or_assign(iter->first, -iter->second);
	//Return the result counter.
	return res;
}

TypeCounter & Space_Colony::TypeCounter::operator*=(const double right) {
	//Iterate all counters.
	for (auto iter(counters.begin()), end(counters.end()); iter != end; ++iter)
		//Multiply the counter by 'right'.
		iter->second *= right;
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator*(const double right) const {
	return TypeCounter(*this) *= right;
}

TypeCounter & Space_Colony::TypeCounter::operator/=(const double right) {
	//Iterate all counters.
	for (auto iter(counters.begin()), end(counters.end()); iter != end; ++iter)
		//Divide the counter by 'right'.
		iter->second /= right;
	return *this;
}

TypeCounter Space_Colony::TypeCounter::operator/(const double right) const {
	return TypeCounter(*this) /= right;
}

Space_Colony::TypeCounter::operator const CounterMap&() const {
	return counters;
}
