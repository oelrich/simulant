#include "stdafx.h"
#include "complex.h"
#include "complex_impl.h"

simulant::simulation::complex::complex simulant::simulation::complex::impl::complex_generator::operator()()
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

bool simulant::simulation::complex::impl::complex_distance_comparator::operator()(const complex & compl)
{
	for (const auto & itm : items)
	{
		if (impl::distance(compl, itm) <= diameter && compl.id != itm.id)
		{
			return true;
		}
	}
	return false;
}

bool simulant::simulation::complex::impl::complex_neighbour::operator()(const simulant::simulation::complex::complex & test)
{
	if (impl::distance(test, complex) <= diameter && test.id != complex.id)
	{
		return true;
	}
	return false;
}

double simulant::simulation::complex::impl::distance(const simulant::simulation::complex::complex & lhs, const simulant::simulation::complex::complex & rhs)
{
	return std::sqrt(std::pow(lhs.x - rhs.x, 2.0) + std::pow(lhs.y - rhs.y, 2.0));
}
