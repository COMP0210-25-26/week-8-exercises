#include <math.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <complex>

typedef std::chrono::high_resolution_clock timingClock;

double t_seconds(std::chrono::time_point<timingClock> t1, std::chrono::time_point<timingClock> t2)
{
    return (t2 - t1).count() / 1e9;
}

int main() {

  const int NPOINTS = 1024;
  const int MAXITER = 1024;

  double x_min = -2.0;
  double x_max = 0.5;
  double y_min = 0.0;
  double y_max = 1.125;

  double dx = (x_max - x_min)/NPOINTS;
  double dy = (y_max - y_min)/NPOINTS;

  std::complex<double> z, c;
  int n_outside = 0;

  auto start = timingClock::now();

  // Iterate over entire domain
  for(int i=0; i<NPOINTS; ++i) 
  {
    for(int j=0; j<NPOINTS; ++j) 
    {
      // Set c to point inside domain
      c.real(x_min + i*dx);
      c.imag(y_min + j*dy);

      // Initial condition for z is c
      z = c;
      for (int iter=0; iter<MAXITER; iter++)
      {
        // Iterate z = z^2 + c
        z = z*z + c;

        // If |z| > 2, point is outside Mandelbrot set
        if (std::abs(z) > 2.0e0) 
        {
          n_outside++; 
          break;
        }
      }
    }
  }

  auto stop = timingClock::now();
  double duration = t_seconds(start, stop);

  double prop_inside = (double)(NPOINTS*NPOINTS-n_outside)/(double)(NPOINTS*NPOINTS);
  double area = 2.0*2.5*1.125*prop_inside;
  double error = std::abs(area - 1.506484);

  std::cout << "Area of Mandlebrot set = " << area << std::endl;
  std::cout << "Error = " << error << std::endl;
  std::cout << "Time = " << duration << " s" << std::endl;
}
