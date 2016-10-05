#pragma once

#include "Space Colony.h"
#include <unordered_map>

namespace Space_Colony {

	/*
	A TypeCounter stores counters for different type values. These counters
	will always be greater than or equal to 0.*/
	class TypeCounter {
	public:
		typedef __int32 TypeID;
		typedef __int32 counter;
		typedef std::unordered_map<TypeID, counter> Map_t;
		typedef Map_t::const_iterator const_iterator;

		TypeCounter();
		TypeCounter(const TypeCounter& orig);
		TypeCounter(const Map_t& shps);

		const_iterator begin() const;
		const_iterator end() const;
		/*
		Returns the counter for the given type.*/
		counter getCounter(TypeID id) const;
		/*
		Sets the counter to vl or 0 if vl is less than 0. Returns the old
		counter. error is set to true if vl is less than 0.*/
		counter setCounter(TypeID id, counter vl, bool* const error = nullptr);
		/*
		Increments the counter by inc; if inc pushes the value to be less than
		0 the counter is set to 0. Returns the old counter. error is set to
		true if inc pushes to less than 0.*/
		counter incrementCounter(TypeID id, counter inc, bool* const error = nullptr);
		/*
		Returns the old counter and erases the value.*/
		counter erase(TypeID id);
		/*
		TRUE if there is a counter for this type.*/
		bool contains(TypeID id) const;
		/*
		Removes all 0 counters.*/
		void clean();
		/*
		The number of counters in this TypeCounter.*/
		__int32 size() const;
		/*
		The sum of all the counters.*/
		__int32 sum() const;

		TypeCounter& operator=(const TypeCounter& right);
		bool operator==(const TypeCounter& right) const;
		bool operator!=(const TypeCounter& right) const;
		TypeCounter& operator+=(const TypeCounter& right);
		TypeCounter operator+(const TypeCounter& right) const;
		TypeCounter& operator+=(const Map_t& right);
		TypeCounter operator+(const Map_t& right) const;
		TypeCounter& operator-=(const TypeCounter& right);
		TypeCounter operator-(const TypeCounter& right) const;
		TypeCounter& operator-=(const Map_t& right);
		TypeCounter operator-(const Map_t& right) const;
		counter operator[](TypeID id) const;

		explicit operator const Map_t() const;

	private:
		Map_t counters;

	};

}
