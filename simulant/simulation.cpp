#include "stdafx.h"
#include "simulation.h"
#include "simulation_impl.h"

#include "statistics.h"
#include "settings.h"
#include "complex.h"



std::vector<std::pair<double, double>> simulant::simulation::impl::experiment(double test_area_radius, double blob_radius, size_t complex_count, size_t experiment_runs)
{
	std::vector<std::vector<size_t>> counts_per_run;
	for (size_t run = 0; run < experiment_runs; ++run)
	{
		auto experiment_complexes = simulant::simulation::complex::generate_complexes(complex_count, test_area_radius);

		counts_per_run.push_back(count_neighbours(experiment_complexes, blob_radius * 2.0));
	}

	return simulant::statistics::get_means_and_errors(counts_per_run);
}

void simulant::simulation::impl::print_results(const settings & settings, size_t complex_count, const std::vector<std::vector<std::pair<double, double>>> & blob_radius_results)
{
	std::stringstream ss;
	ss << "data_for_complex_count_" << complex_count << ".dat";
	std::ofstream writer{ ss.str() };
	for (size_t jj = 0; jj < blob_radius_results.size(); ++jj)
	{
		writer << settings.blob_size_radii[jj];
		for (const std::pair<double, double> & ev_err : blob_radius_results[jj])
		{
			writer << "\t" << ev_err.first << "\t" << ev_err.second;
		}
		writer << "\n";
	}
	writer.flush();
	writer.close();
}

void simulant::simulation::simulate()
{
	settings settings{};

	for (size_t ii = 0; ii < 5; ++ii)
	{
		std::vector<std::vector<std::pair<double, double>>> blob_radius_results;
		for (size_t jj = 0; jj < 3; ++jj)
		{
			auto blob_size_jj_complex_count_ii =
				simulant::simulation::impl::experiment(settings.test_area_radius, settings.blob_size_radii[jj], settings.number_of_complexes[ii], settings.experiment_runs);
			blob_radius_results.push_back(blob_size_jj_complex_count_ii);
		}
		simulant::simulation::impl::print_results(settings, settings.number_of_complexes[ii], blob_radius_results);
	}
}
