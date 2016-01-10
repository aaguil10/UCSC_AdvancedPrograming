//Convert this program to C++
//change to C++ io
//change to one line comments
//change defines of constants to const
//change array to vector<>
//inline any short function
//Convert to a C++ version of monte carlo integration for pi
//Copyright Ira Pohl

//Changed by Hai Vo for C to C++
//username: hqvo@ucsc.edu

//changed up the include to a C++ format
#include <iostream>
#include <iomanip> 
#include <vector>
#include <cmath>
#include <cstdlib>

//so that there is no need to type std:: all the time
using namespace std;
//replace the #define
const int MAXINT = 32767;
//used inline for the small function
inline double F(double x){ 
	return((sqrt(1-x*x))); 
}

double mcint(double a, double b, double max, int n){
	int  below = 0;
	int trials = 0;
	for(trials; trials < n; ++trials ){
		//used static_cast instead
       	double x = ((rand() % MAXINT)/static_cast<double>(MAXINT))*(b - a) + a;
       	double y = (rand() % MAXINT)/static_cast<double>(MAXINT);
       	if (F(x) > y)
          ++below;

    }
    return(static_cast<double>(below)/trials  * (b - a) * max);
}

int main(){
	double pi, x, y;
	int    below, trials,mtrial;
	//made this part into a const because it is never changed
	const int n_experiment = 5;
	//made the array into a vector
	vector<double> pi_approx(n_experiment);
	//C++ version of printf
	cout << "TRIALS = " << endl;
	//cin takes in input from stdin
	cin >> mtrial;
	srand(clock());
	//C++ i can be declared in the for loop
	for( int i = 0; i < n_experiment; ++i ){
		pi_approx.at(i) = 4 * mcint(0.0, 1.0, 1.0, mtrial) ;
		mtrial = 10 * mtrial;
   	}
   	for( int i = 0; i < n_experiment; ++i ){
   		cout << "pi trial " << i << " = " << left;
   		cout << setw(8) << setfill('0') << pi_approx.at(i) << "," << endl;
   	}
	return 0;
}