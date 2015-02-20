#pragma once

#include <vector>

namespace simulant {
	namespace simulation{
		struct settings
		{
			settings();
			size_t experiment_runs;
			double test_area_radius;
			std::vector<double> blob_size_radii;
			std::vector<size_t> number_of_complexes;
		};
	}
}