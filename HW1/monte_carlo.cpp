//This program calculates pie.
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const int kMaxInt = 32767;

inline double F(double X){
  return sqrt(1 - X * X);
} 

//returns pie, it's accuracy increases depending on size of n
double mcint(double a, double b, double max, int n){
  int below = 0, trials = 0;
  double x, y;
  for (trials = 0; trials < n; ++trials) {
    x = ((rand() % kMaxInt)/(double)kMaxInt)* (b - a) + a;
    y = (rand() % kMaxInt)/(double)kMaxInt;
    if (F(x) > y) {
      ++below;
    }
  }
  return ((double)below/trials * (b - a) * max);
}

int main(){
  double pi, x, y;
  int below, trials, mtrial, i, n_experiment = 5;
  vector<double> pi_approx(n_experiment);

  cout << "Trials = \n";
  cin >> mtrial;

  //computes pie 5 times. Increases number of trials each time
  for (i = 0; i < n_experiment; i++) {
    pi_approx[i] = (4 * mcint(0.0, 1.0, 1.0, mtrial));
    mtrial = 10 * mtrial;
  }
  
  //prints out results
  for (i = 0; i < n_experiment; i++){
    cout << "pi trial " << i << " = " << pi_approx[i] << "\n";
  }
}
