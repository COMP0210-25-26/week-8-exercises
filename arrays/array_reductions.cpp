#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock timingClock;

double t_seconds(std::chrono::time_point<timingClock> t1, std::chrono::time_point<timingClock> t2)
{
    return (t2 - t1).count() / 1e9;
}

int main()
{
    mt19937_64 rng(42);
    normal_distribution<double> dist(0, 1);

    // Generating mock data using a random (Gaussian) distribution
    const int N = 100000;
    vector<double> rand_list(N);
    for(int i = 0; i < N; i++)
    {
        rand_list[i] = dist(rng);
    }

    // Initialise a histogram as an array with 101 bins
    // since the number of bins is finite, we will only be able to 
    // capture values in a finite range. 
    const unsigned int bins = 101;
    double x_min = -3, x_max = 3;
    int histogram[bins];
    for(size_t i = 0; i < bins; i++)
    {
        histogram[i] = 0;
    }

    // Fill out the histogram 
    for (int i = 0; i < N; i++)
    {
        double x = rand_list[i];
        
        // discard elements which are beyond the boundaries of our histogram
        if (x < x_min || x >= x_max)
        {
            continue;
        }

        // Find the index of the bin
        int idx = static_cast<int>(((x - x_min) / (x_max - x_min)) * bins);
        histogram[idx]++;
    }

    for(int i = 0; i < bins; i++)
    {
        cout << (-3 + (i + 0.5)*(6.0/bins)) << " " <<  histogram[i] << endl;
    }

    return 0;
}