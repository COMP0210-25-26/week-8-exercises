#include <iostream>
#include <chrono>
#include <memory>
#include <cmath>

typedef std::chrono::high_resolution_clock timingClock;

double t_seconds(std::chrono::time_point<timingClock> t1, std::chrono::time_point<timingClock> t2)
{
    return (t2 - t1).count() / 1e9;
}

int main() {

  const int N = 800000000;
  double dx = 1.0f/N;

  auto start = timingClock::now();

  double sum = 0.0f;
  #pragma omp parallel for
  for(int i=0; i<N; ++i) {
    double x = i*dx;
    sum += 4.0f/(1.0f + x*x)*dx;
  }

  auto stop = timingClock::now();
  double duration = t_seconds(start, stop);

  std::cout << "Result: " << sum << std::endl;
  std::cout << "Time for " << N << " iterations: " << duration << " s" << std::endl;

  return 0;
}
