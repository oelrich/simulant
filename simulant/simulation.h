#pragma once
#include <vector>


namespace simulant {
	namespace simulation{

		struct complex {
			size_t id;
			double x, y;
		};

		void simulate();
		std::vector<size_t> count_neighbours(std::vector<complex> & experiment_complexes, double blob_diameter);
	}
}