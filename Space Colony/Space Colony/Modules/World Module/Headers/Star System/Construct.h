#pragma once

#include "Star System.h"

namespace World_Module {

	namespace Star_System {

		/*
		A large scale construction which provides it
		functionality or defences.*/
		class Construct {
		public:
			Construct();
			Construct(const Construct& orig);
			Construct(const ResourceMap& rsrcChng, const FunctionTags& fnctnlty);

			const ResourceMap& get_resourceChange() const;
			FunctionTags get_functionality() const;

			__declspec(property(get = get_resourceChange)) ResourceMap _resourceChange;
			__declspec(property(get = get_functionality)) FunctionTags _functionality;

			Construct& operator=(const Construct& right);
			bool operator==(const Construct& right) const;
			bool operator!=(const Construct& right) const;

		private:
			/*
			The drain on resources this construct provides.*/
			ResourceMap resourceChange;
			/*
			The functionality this construct provides.*/
			FunctionTags functionality;

		};

		typedef std::vector<Construct> ConstructVector;

	}

}
