#include "stdafx.h"
#include "settings.h"

simulant::simulation::settings::settings() : test_area_radius(3500.0), experiment_runs(1000)
{
	blob_size_radii =
		{
			0.625 / 2.0,
			1.25 / 2.0,
			2.5 / 2.0,
			5.0 / 2.0,
			10.0 / 2.0,
			20.0 / 2.0,
			40.0 / 2.0,
			80.0 / 2.0,
			160.0 / 2.0
		};
	number_of_complexes = { 125, 250, 500, 1000, 2000, 4000, 8000 };
}