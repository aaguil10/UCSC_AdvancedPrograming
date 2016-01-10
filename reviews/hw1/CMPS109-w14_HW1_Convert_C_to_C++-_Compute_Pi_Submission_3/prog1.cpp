//  Convert this program to C++

//   change to C++ io

//   change to one line comments

//   change defines of constants to const

//   change array to vector<>

//   inline any short function

 

// Convert to a C++ version of monte carlo integration for pi

// Copyright Ira Pohl


 
#include <math.h>

#include <iostream>

#include <stdlib.h>

//include vector
#include <vector>

//replaced define
const int MAXINT = 32767;

//added namespace
using namespace std;

//added inline function
inline double F(double x) {
	
	return (sqrt(1-x*x));

}
 

double mcint(double a, double b, double max, int n)

{

   int  below = 0, trials = 0;

   double  x, y;

 

      for(trials = 0; trials < n; ++trials ) {

       x =  ((rand() % MAXINT)/(double)MAXINT)* (b - a)  + a;

       y =  (rand() % MAXINT)/(double)MAXINT;

       if (F(x) > y)

          ++below;

      }

      return (    (double)below/trials  * (b - a) * max);

}

 

 

int main()

{
	// unnecessary
	// double   pi, x, y;

   int mtrial, i, n_experiment = 5;

   //vector initilization
   vector<double>* pi_approx = new vector<double>();
 
   //replaced printf with cout
   cout << "TRIALS = " << endl;

   //replaced scanf with cin
   cin >> mtrial;

 

   for( i = 0; i < n_experiment; ++i ) {

	   //push values on to the back of the vector
	   pi_approx->push_back(4.0 * mcint(0.0, 1.0, 1.0, mtrial)) ;

      mtrial = 10 * mtrial;

   }

 

   for( i = 0; i < n_experiment; ++i )

	   //replaced printf with cout
	   cout << "pi trial " << i << " = " << (pi_approx->at(i)) << endl;

   return 0;

}
