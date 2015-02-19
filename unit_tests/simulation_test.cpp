#include "stdafx.h"
#include "CppUnitTest.h"

#include "test_helpers.h"
#include "../simulant/simulation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(simulation_test)
	{
	public:

		TEST_METHOD(count_neighbours_0)
		{
			std::vector<simulant::simulation::complex> data{ { 0, 0.0, 0.0 }, { 1, 1.0, 0.0 }, { 2, 100.0, 100.0 } };
			double diameter{2.0};
			std::vector<size_t> result = simulant::simulation::count_neighbours(data,diameter);
			std::vector<size_t> expected{ 1 , 1 };

			Assert::AreEqual(expected, result, L"Should be equal.", LINE_INFO());
		}

		TEST_METHOD(count_neighbours_1)
		{
			std::vector<simulant::simulation::complex> data{ { 0, 0.0, 0.0 }, { 1, 1.0, 0.0 }, { 2, 100.0, 100.0 }, { 3, 100.0, 101.0 } };
			double diameter{ 2.0 };
			std::vector<size_t> result = simulant::simulation::count_neighbours(data, diameter);
			std::vector<size_t> expected{ 0, 2 };

			Assert::AreEqual(expected, result, L"Should be equal.", LINE_INFO());
		}
	};
}