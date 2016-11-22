#pragma once

#include "Space Colony.h"
#include <unordered_map>

namespace Space_Colony {

	/*
	A collection of ints mapped to ints.*/
	class TypeCounter {
	public:
		typedef std::unordered_map<__int32, __int32> CounterMap;
		typedef CounterMap::const_iterator const_iterator;

		TypeCounter();
		TypeCounter(const size_t cnt);
		TypeCounter(const TypeCounter &orig);
		TypeCounter(const CounterMap &orig);

		/*
		Returns a iterator to the start of the counters.*/
		const_iterator begin() const;
		/*
		Returns a iterator to the end of the counters.*/
		const_iterator end() const;
		/*
		Returns the number of mappings in this TypeCounter.*/
		size_t size() const;
		/*
		Returns true if this TypeCounter is empty.*/
		bool empty() const;
		/*
		Returns the sum of all the mappings in this TypeCounter.*/
		__int32 sum() const;
		/*
		True if the key has a mapping in the TypeCounter.*/
		bool contains(const __int32 key) const;
		/*
		Returns the mapped value of the passed int or 0 if not found.*/
		__int32 getCounter(const __int32 key) const;
		/*
		Returns the old mapped value and sets the internal value.*/
		__int32 setCounter(const __int32 key, const __int32 val);
		/*
		Returns the old mapped value and increments the internal value.*/
		__int32 incCounter(const __int32 key, const __int32 inc);
		/*
		Returns a TypeCounter with all the negative counters of this type counter.*/
		TypeCounter getNeg() const;
		/*
		Returns a TypeCounter with all the positive counters of this type counter.*/
		TypeCounter getPos() const;
		/*
		Returns true if all the counters are positive.*/
		bool isPos() const;
		/*
		Returns true if all the counters are negative.*/
		bool isNeg() const;
		/*
		Returns all the counters which are shared by both counters.*/
		TypeCounter shared(const TypeCounter &cnts) const;
		/*
		Returns all the counters which are unique to this TypeCounter.*/
		TypeCounter different(const TypeCounter &cnts) const;

		TypeCounter & operator=(const TypeCounter &right);
		bool operator==(const CounterMap &right) const;
		bool operator!=(const CounterMap &right) const;
		bool operator<(const CounterMap &right) const;
		bool operator>=(const CounterMap &right) const;
		bool operator>(const CounterMap &right) const;
		bool operator<=(const CounterMap &right) const;
		TypeCounter & operator+=(const CounterMap &right);
		TypeCounter operator+(const CounterMap &right) const;
		TypeCounter & operator-=(const CounterMap &right);
		TypeCounter operator-(const CounterMap &right) const;
		TypeCounter operator-() const;
		TypeCounter & operator*=(const double right);
		TypeCounter operator*(const double right) const;
		TypeCounter & operator/=(const double right);
		TypeCounter operator/(const double right) const;

		operator const CounterMap &() const;

	private:
		/*
		A map of ints to ints.*/
		CounterMap counters;

	};

}
