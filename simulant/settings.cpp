#include "stdafx.h"
#include "settings.h"

simulant::simulation::settings::settings() : test_area_radius(3500.0), experiment_runs(1000)
{
	blob_size_radii = { 0.25, 2.5, 25.0 };
	number_of_complexes = { 100, 200, 400, 800, 1600 };
}