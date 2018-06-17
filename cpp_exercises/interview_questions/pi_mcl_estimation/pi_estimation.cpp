/*
* Estimate pi to three decimal places using Monte Carlo Sampling
* See README file for more details
*/

//Include standard library 
#include <cstdlib>
#include <iostream>
#include <random>

//Code options
#define REQUESTED_PRECISION 0.001

//Parameters
#define CRF_RADIUS 1.0

//Import everything from std namespace
using namespace std;

//Main method
int main(int argc, char* argv[])
{
  //Instantiate random number generator (used to sample
  //from the uniform distribution)
  //Note: we work only in one quadrant (not the full crf) since the result is the same
  mt19937_64 rng{};
  uniform_real_distribution<double> unifrnd{0.0, 1.0};

  //Number of samples to be drawn
  size_t sampleCount = 2 / (REQUESTED_PRECISION * REQUESTED_PRECISION);

  //Lambda used to check if the given point is inside a crf having the specified radius
  auto insideCrf = [](double x, double y) -> bool { return (sqrt((x * x) + (y * y)) <= CRF_RADIUS); };
  
  //Initialize probability estimate
  double crfProb = 0.0;
  for (size_t i = 0; i < sampleCount; i++)
  {
    //Draw a point from the square area
    double x = unifrnd(rng);
    double y = unifrnd(rng);

    //Compute prob update
    double probUpdate = (insideCrf(x, y) == true) ? 1.0 : 0.0;
    crfProb += static_cast<double>(static_cast<long double>(probUpdate - crfProb) / static_cast<long double>(i + 1));
  }

  //Display estimated pi value
  cout << "Pi value estimated using MC = " << (4.0 * crfProb) << endl;
  cout << "Number of samples used with MC method = " << sampleCount << endl;
  cout << endl;

  //For comparison we show what happens if we use a numerical
  //integration method to compute the probability estimate

  //Define lamba used to evaluate crf function
  auto crfEval = [](double x) -> double { return sqrt((CRF_RADIUS * CRF_RADIUS) - (x * x)); };

  //Define integration step
  double intStep = 0.002;

  //Initialize variables used during intergration
  //and initialize 
  double prevCrfVal = CRF_RADIUS;
  double intgralVal = 0.0;

  //Compute crf area in the first quadrant only 
  int intStepCount = 0;

  for (double x = intStep; x <= CRF_RADIUS; x += intStep)
  {
    //Evaluate crf value for the current x coordinate
    double currCrf = crfEval(x);

    //Update integral using trapezoidal method
    intgralVal += ((prevCrfVal + currCrf) * intStep) / 2.0;
    prevCrfVal = currCrf;

    //Update number of steps
    intStepCount++;
  }

  //Display estimated pi value
  cout << "Pi value estimated using integrals = " << (4.0 * (intgralVal / (CRF_RADIUS * CRF_RADIUS))) << endl;
  cout << "Number of samples used with integrals method = " << intStepCount << endl;
  cout << endl;

  //Code rexited normally
  return 0;
}