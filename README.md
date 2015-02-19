# simulant
Simple visualisation of a specific probability function.

The software first generates a population of points using an uniform random distribution. Then it calculates how often the points come within some given distance of other points and how many points there are in those neighbourhoods.


Output is a set of files for the different population sizes and neighbourhood sizes specified in settings.

The rows in the files contain the following information:
neighbourhood_radius  mean0  error0 mean1  error1 ... meanN errorN
