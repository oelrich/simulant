#include "stdafx.h"
#include "simulation.h"
#include "statistics.h"

namespace simulant {
	namespace simulation{

		struct settings
		{
			settings() : test_area_radius(3500.0), experiment_runs(1000)
			{
				blob_size_radii = { 0.25, 2.5, 25.0 };
				number_of_complexes = { 100, 200, 400, 800, 1600 };
			}
			size_t experiment_runs;
			double test_area_radius;
			std::vector<double> blob_size_radii;
			std::vector<size_t> number_of_complexes;
		};

		class complex_generator
		{
		public:
			complex_generator(double test_area_radius) :
				compl_id(0),
				test_area_radius(test_area_radius),
				test_area_radius_square(test_area_radius * test_area_radius),
				distribution(-test_area_radius, test_area_radius),
				generator(std::random_device()()) {}

			complex operator()()
			{
				complex c;
				c.x = distribution(generator);
				c.y = distribution(generator);
				while ((c.x * c.x + c.y * c.y) > test_area_radius_square)
				{
					c.x = distribution(generator);
					c.y = distribution(generator);
				}
				c.id = compl_id;
				++compl_id;
				return c;
			}
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
			complex_distance_comparator(const std::vector<complex> & items, double blob_diameter) : items(items), diameter(blob_diameter)
			{}
			bool operator()(const complex & compl)
			{
				for (const auto & itm : items)
				{
					if (distance(compl, itm) <= diameter && compl.id != itm.id)
					{
						return true;
					}
				}
				return false;
			}
		private:
			const std::vector<complex> & items;
			double diameter;
			double distance(const complex & lhs, const complex & rhs)
			{
				return std::sqrt(std::pow(lhs.x - rhs.x, 2.0) + std::pow(lhs.y - rhs.y, 2.0));
			}

		};

		class neighbour_of_complex
		{
		public:
			neighbour_of_complex(const complex & complex, double blob_diameter) : complex(complex), diameter(blob_diameter)
			{}
			bool operator()(const complex & test)
			{
				if (distance(test, complex) <= diameter && test.id != complex.id)
				{
					return true;
				}
				return false;
			}
		private:
			const complex & complex;
			double diameter;
			double distance(const simulant::simulation::complex & lhs, const simulant::simulation::complex & rhs)
			{
				return std::sqrt(std::pow(lhs.x - rhs.x, 2.0) + std::pow(lhs.y - rhs.y, 2.0));
			}
		};

		size_t purge_neighbourless(std::vector<complex> & experiment_complexes, double blob_diameter)
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

		std::vector<size_t> map_to_count_vector(const std::map<size_t, size_t> & data)
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

		std::vector<size_t> count_neighbours(std::vector<complex> & experiment_complexes, double blob_diameter)
		{
			auto total_number_of_complexes = experiment_complexes.size();
			std::map<size_t, size_t> neighbour_counts;

			neighbour_counts[0] = purge_neighbourless(experiment_complexes, blob_diameter);

			while (experiment_complexes.size() > 0)
			{
				auto complex = experiment_complexes.back();
				experiment_complexes.pop_back();

				auto element_neighbours_end = std::partition(begin(experiment_complexes), end(experiment_complexes), neighbour_of_complex(complex, blob_diameter));

				std::vector<simulant::simulation::complex> neighbours;
				neighbours.push_back(complex);

				auto element_neighbours_it = begin(experiment_complexes);
				while (element_neighbours_it != element_neighbours_end)
				{
					if (std::all_of(begin(neighbours), end(neighbours), neighbour_of_complex(*element_neighbours_it, blob_diameter)))
					{
						neighbours.push_back(*element_neighbours_it);
					}
					++element_neighbours_it;
				}

				auto remove_it = std::remove_if(begin(experiment_complexes), end(experiment_complexes),
					[&neighbours](const simulant::simulation::complex & elem){
					return std::any_of(begin(neighbours), end(neighbours),
						[&elem](const simulant::simulation::complex & cmp){ return elem.id == cmp.id; }); });

				experiment_complexes.erase(remove_it, end(experiment_complexes));

				++neighbour_counts[neighbours.size() - 1];
			}

			return map_to_count_vector(neighbour_counts);
		}

		std::vector<std::pair<double, double>> experiment(double test_area_radius, double blob_radius, size_t complex_count, size_t experiment_runs)
		{
			std::vector<std::vector<size_t>> counts_per_run;
			for (size_t run = 0; run < experiment_runs; ++run)
			{
				std::vector<complex> experiment_complexes(complex_count, complex());
				std::generate(begin(experiment_complexes), end(experiment_complexes), complex_generator(test_area_radius));

				counts_per_run.push_back(count_neighbours(experiment_complexes, blob_radius * 2.0));
			}

			return simulant::statistics::get_means_and_errors(counts_per_run);
		}

		void print_results(const settings & settings, size_t complex_count, const std::vector<std::vector<std::pair<double, double>>> & blob_radius_results)
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

		void simulate()
		{
			settings settings{};

			for (size_t ii = 0; ii < 5; ++ii)
			{
				std::vector<std::vector<std::pair<double, double>>> blob_radius_results;
				for (size_t jj = 0; jj < 3; ++jj)
				{
					auto blob_size_jj_complex_count_ii =
						experiment(settings.test_area_radius, settings.blob_size_radii[jj], settings.number_of_complexes[ii], settings.experiment_runs);
					blob_radius_results.push_back(blob_size_jj_complex_count_ii);
				}
				print_results(settings, settings.number_of_complexes[ii], blob_radius_results);
			}
		}
	}
}