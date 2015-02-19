#pragma once

#include <vector>
#include <utility>

namespace simulant
{
	namespace statistics
	{
		std::vector<std::pair<double, double>> get_means_and_errors(const std::vector<std::vector<size_t>> & data);
	}
}
