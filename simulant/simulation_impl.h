#pragma once
#include <vector>
#include "settings.h"
#include "complex.h"

namespace simulant {
	namespace simulation{
		namespace impl{
			void print_results(const settings & settings, size_t complex_count, const std::vector<std::vector<std::pair<double, double>>> & blob_radius_results);
			std::vector<std::pair<double, double>> experiment(double test_area_radius, double blob_radius, size_t complex_count, size_t experiment_runs);
		}
	}
}