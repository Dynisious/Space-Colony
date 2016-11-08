#include "stdafx.h"
#include "CppUnitTest.h"
#include "TypeCounter.h"

using namespace Space_Colony;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SpaceColony_tests {
	TEST_CLASS(Space_Colony_tests) {
public:

	TEST_METHOD(TypeCounter_tests) {
		TypeCounter z0, cntr1, cntr2, neg, pos;
		for (__int32 i(0); i < 5; ++i) {
			z0.setCounter(i, 0);
			neg.setCounter(i, -1);
			pos.setCounter(i, 1);
			cntr1.setCounter(i, i);
			cntr2.setCounter(i, i * 2);
		}

		Assert::IsTrue(pos.isPos(), L"\"isPos\" failed.");

		Assert::IsTrue(neg.isNeg(), L"\"isNeg\" failed.");

		Assert::IsTrue(cntr1.size() == 4, L"\"size\" failed.");

		Assert::IsTrue(z0.empty(), L"\"empty\" failed.");

		Assert::IsTrue(z0 == z0, L"\"== op\" failed.");

		Assert::IsTrue(z0 != cntr1, L"\"!= op\" failed.");

		Assert::IsTrue(z0 == (cntr1 - cntr1), L"\"+ op\" failed.");

		Assert::IsTrue(cntr2 == (cntr1 + cntr1), L"\"+ op\" failed.");

		Assert::IsTrue(cntr1.getCounter(3) == 3, L"\"getCounter\" failed.");

		cntr1.incCounter(1, 1);
		Assert::IsTrue(cntr1.getCounter(1) == cntr2.getCounter(1), L"\"incCounter\" failed.");

	}

	};
}