# simulant
Simple visualisation of a specific probability function.

The software first generates a population of points using an uniform random distribution. Then it calculates how often the points come within some given distance of other points and how many points there are in those neighbourhoods.


Output is a set of files for the different population sizes and neighbourhood sizes specified in settings.

The rows in the files contain the following information:
neighbourhood_radius  mean0  error0 mean1  error1 ... meanN errorN

## Details
We randomly place a given number of complexes on a test surface.

The complexes are then counted depending on how they can be covered by a blob. If a blob can be placed so that it covers three complexes those three will be removed and the count for "three neighbours" will be incremented by one. This continues until the test surface is empty.

The counts are converted to means with error.

The test surface has a radius of 3500 um for all runs.
Blob radii tested are 0.3125, 0.125, 0.25, 2.5, 5.0, 10.0, 20.0, 40.0 and 80.0.
Number of complexes on surface are 125, 250, 500, 1000, 2000, 4000 and 8000.

For each combination of blob radius and complex count 1000 tests are made.

The code is not fast and the time required for the 1000+ complex counts is substantial.
