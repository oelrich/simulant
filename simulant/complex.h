#pragma once
#include <vector>

namespace simulant {
	namespace simulation{
		namespace complex {

			struct complex {
				size_t id;
				double x, y;
			};

			std::vector<complex> generate_complexes(size_t complex_count, double experiment_area_radius);

			std::vector<size_t> count_neighbours(std::vector<complex> & experiment_complexes, double blob_diameter);
		}
	}
}
