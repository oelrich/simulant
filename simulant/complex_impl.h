#pragma once
#include <vector>
#include "complex.h"

namespace simulant {
	namespace simulation{
		namespace complex {
			namespace impl {
				double distance(const simulant::simulation::complex::complex & lhs, const simulant::simulation::complex::complex & rhs);

				size_t purge_neighbourless(std::vector<complex> & experiment_complexes, double blob_diameter);

				std::vector<size_t> count_map_to_count_vector(const std::map<size_t, size_t> & data);

				class complex_generator
				{
				public:
					complex_generator(double test_area_radius) :
						compl_id(0), test_area_radius(test_area_radius), test_area_radius_square(test_area_radius * test_area_radius), distribution(-test_area_radius, test_area_radius), generator(std::random_device()())
					{}

					complex operator()();
				private:
					size_t compl_id;
					double test_area_radius;
					double test_area_radius_square;
					std::mt19937_64 generator;
					std::uniform_real_distribution<double> distribution;
				};

				class complex_distance_comparator
				{
				public:
					complex_distance_comparator(const std::vector<complex> & items, double blob_diameter) : items(items), diameter(blob_diameter) {}
					bool operator()(const complex & compl);
				private:
					const std::vector<complex> & items;
					double diameter;
				};

				class complex_neighbour
				{
				public:
					complex_neighbour(const simulant::simulation::complex::complex & complex, double blob_diameter) : complex(complex), diameter(blob_diameter) {}
					bool operator()(const simulant::simulation::complex::complex & test);
				private:
					const complex & complex;
					double diameter;
				};
			}
		}
	}
}