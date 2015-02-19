#include "stdafx.h"
#include "CppUnitTest.h"

#include "test_helpers.h"
#include "../simulant/statistics.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(statistics_test)
	{
	public:
		
		TEST_METHOD(mean_and_error_0)
		{
			std::vector<std::vector<size_t>> data{ { 4, 1 }, { 6, 1, 1 } };
			auto result = simulant::statistics::get_means_and_errors(data);
			std::vector<std::pair<double, double>> expected{ { 5.0, 1.0 }, { 1.0, 0.0 }, { 0.5, 0.5 } };

			Assert::AreEqual(expected, result, L"Should be equal.", LINE_INFO());
		}
	};
}