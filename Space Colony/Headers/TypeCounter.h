#pragma once

#include "Space Colony.h"
#include <unordered_map>

namespace Space_Colony {

	/*
	A collection of type_ids mapped to ints.*/
	class TypeCounter {
	public:
		typedef __int32 type_id;
		typedef std::unordered_map<type_id, __int32> CounterMap;
		typedef CounterMap::const_iterator const_iterator;

		TypeCounter();
		TypeCounter(const TypeCounter &orig);
		TypeCounter(const CounterMap &orig);

		const_iterator begin() const;
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
		Returns the mapped value of the passed type_id or 0 if not found.*/
		__int32 getCounter(const type_id id) const;
		/*
		Returns the old mapped value and sets the internal value.*/
		__int32 setCounter(const type_id id, const __int32 val);
		/*
		Returns the old mapped value and increments the internal value.*/
		__int32 incCounter(const type_id id, const __int32 val);
		/*
		Returns a Type Counter with all the negative counters of this type counter.*/
		TypeCounter getNeg() const;
		/*
		Returns a Type Counter with all the positive counters of this type counter.*/
		TypeCounter getPos() const;
		/*
		Returns true if all the counters are positive.*/
		bool isPos() const;
		/*
		Returns true if all the counters are negative.*/
		bool isNeg() const;
		/*
		Returns all the counters which are shared by both counters.*/
		TypeCounter shared(const CounterMap &right) const;
		/*
		Returns all the counters which are unique to this TypeCounter.*/
		TypeCounter difference(const CounterMap &right) const;

		TypeCounter & operator=(const TypeCounter &right);
		bool operator==(const TypeCounter &right) const;
		bool operator!=(const TypeCounter &right) const;
		bool operator<(const TypeCounter &right) const;
		bool operator>=(const TypeCounter &right) const;
		bool operator>(const TypeCounter &right) const;
		bool operator<=(const TypeCounter &right) const;
		TypeCounter & operator+=(const TypeCounter &right);
		TypeCounter operator+(const TypeCounter &right) const;
		TypeCounter operator-() const;
		TypeCounter & operator-=(const TypeCounter &right);
		TypeCounter operator-(const TypeCounter &right) const;
		TypeCounter & operator*=(const double right);
		TypeCounter operator*(const double right) const;
		TypeCounter & operator/=(const double right);
		TypeCounter operator/(const double right) const;

		operator const CounterMap &() const;
		explicit operator CounterMap () const;

	private:
		CounterMap counters;

	};

}
