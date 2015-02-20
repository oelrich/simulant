#pragma once
#include "stdafx.h"
#include "complex.h"
#include "complex_impl.h"

std::vector<simulant::simulation::complex::complex> simulant::simulation::complex::generate_complexes(size_t complex_count, double experiment_area_radius)
{
	std::vector<complex> experiment_complexes(complex_count, complex());
	std::generate(begin(experiment_complexes), end(experiment_complexes), impl::complex_generator(experiment_area_radius));

	return experiment_complexes;
}


std::vector<size_t> simulant::simulation::complex::count_neighbours(std::vector<complex> & experiment_complexes, double blob_diameter)
{
	auto total_number_of_complexes = experiment_complexes.size();
	std::map<size_t, size_t> neighbour_counts;

	neighbour_counts[0] = simulant::simulation::complex::impl::purge_neighbourless(experiment_complexes, blob_diameter);

	while (experiment_complexes.size() > 0)
	{
		auto complex = experiment_complexes.back();
		experiment_complexes.pop_back();

		auto element_neighbours_end = std::partition(begin(experiment_complexes), end(experiment_complexes), impl::complex_neighbour(complex, blob_diameter));

		std::vector<simulant::simulation::complex::complex> neighbours;
		neighbours.push_back(complex);

		auto element_neighbours_it = begin(experiment_complexes);
		while (element_neighbours_it != element_neighbours_end)
		{
			if (std::all_of(begin(neighbours), end(neighbours), impl::complex_neighbour(*element_neighbours_it, blob_diameter)))
			{
				neighbours.push_back(*element_neighbours_it);
			}
			++element_neighbours_it;
		}

		auto remove_it = std::remove_if(begin(experiment_complexes), end(experiment_complexes),
			[&neighbours](const simulant::simulation::complex::complex & elem){
			return std::any_of(begin(neighbours), end(neighbours),
				[&elem](const simulant::simulation::complex::complex & cmp){ return elem.id == cmp.id; }); });

		experiment_complexes.erase(remove_it, end(experiment_complexes));

		++neighbour_counts[neighbours.size() - 1];
	}

	return simulant::simulation::complex::impl::count_map_to_count_vector(neighbour_counts);
}

size_t simulant::simulation::complex::impl::purge_neighbourless(std::vector<complex> & experiment_complexes, double blob_diameter)
{
	auto has_neighbour = std::partition(begin(experiment_complexes), end(experiment_complexes), complex_distance_comparator(experiment_complexes, blob_diameter));

	if (has_neighbour == begin(experiment_complexes))
	{
		// no one has a neighbour
		auto purged_all = experiment_complexes.size();
		experiment_complexes.clear();

		return purged_all;
	}

	if (has_neighbour == end(experiment_complexes))
	{
		// everyone has a neighbour
		return 0;
	}

	auto purged_count = end(experiment_complexes) - has_neighbour;

	experiment_complexes.erase(has_neighbour, end(experiment_complexes));

	return purged_count;
}


std::vector<size_t> simulant::simulation::complex::impl::count_map_to_count_vector(const std::map<size_t, size_t> & data)
{
	std::vector<size_t> cv;
	for (const auto & kv : data)
	{
		while ((kv.first + 1) > cv.size())
		{
			cv.push_back(0);
		}
		cv[kv.first] = kv.second;
	}

	return cv;
}