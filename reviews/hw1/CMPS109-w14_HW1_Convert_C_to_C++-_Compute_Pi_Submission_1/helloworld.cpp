//Alexander Sadeghi 1280757
//CMPS 109 Asg 1
//C++ version of monte carlo integration for pi
//Converted from C (copyright Ira Pohl
//gia
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;
const int maxint =  32767;
inline double fx(double x){ return (sqrt(1-x*x));}

double mcint(double a, double b, double max, int n){
        int below = 0,trials = 0;
        double x, y;
        for(trials = 0; trials < n; ++trials){
                x =  ((rand() % maxint)/(double)maxint)* (b - a)  + a;
                y =  (rand() % maxint)/(double)maxint;
                if (fx(x) > y)
                        ++below;
        }
        return( (double)below/trials*(b-a)*max);
}

int main(){
        double pi,x,y;
        int below, trials, mtrial, n_experiment = 5;
        vector<double>pi_approx(n_experiment);
        cout << "Trials = \n";
        cin >> mtrial;
        for(int i = 0; i < n_experiment; ++i){
                pi_approx[i] = 4*mcint(0.0,1.0,1.0,mtrial);
                mtrial = 10*mtrial;
        }
        for(int i = 0; i < n_experiment; ++i)
                cout << "pi trial " <<i<< "= " <<pi_approx[i]<<endl;
        return 0;

}

