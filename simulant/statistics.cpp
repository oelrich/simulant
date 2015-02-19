#include "stdafx.h"
#include "statistics.h"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>


size_t longest_sub_vector(const std::vector<std::vector<size_t>> & data)
{
	size_t max_length{ 0 };
	for (const auto & elem : data)
	{
		if (elem.size() > max_length)
		{
			max_length = elem.size();
		}
	}

	return max_length;
}

using mean_error_accumulator = boost::accumulators::accumulator_set < double, boost::accumulators::features<boost::accumulators::tag::mean, boost::accumulators::tag::error_of<boost::accumulators::tag::mean>> > ;

std::vector<mean_error_accumulator> get_statistic_accumulators(const std::vector<std::vector<size_t>> & data)
{
	size_t max_length = longest_sub_vector(data);

	std::vector<mean_error_accumulator> statistic_accumulators(max_length);

	for (const auto & experiment : data)
	{
		for (size_t ii = 0; ii < max_length; ++ii)
		{
			if (ii < experiment.size())
			{
				statistic_accumulators[ii](static_cast<double>(experiment[ii]));
			}
			else
			{
				statistic_accumulators[ii](0.0);
			}
		}
	}
	return statistic_accumulators;
}

std::vector<std::pair<double, double>> simulant::statistics::get_means_and_errors(const std::vector<std::vector<size_t>> & data)
{
	auto accumulators = get_statistic_accumulators(data);

	std::vector<std::pair<double, double>> stats;

	for (const auto & acc : accumulators)
	{
		stats.emplace_back(boost::accumulators::mean(acc), boost::accumulators::error_of<boost::accumulators::tag::mean>(acc));
	}

	return stats;
}
