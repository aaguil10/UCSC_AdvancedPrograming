//Michael Ungerer
//1272985
//cmps109 
//asg1
//
//
//




#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<cstdlib>

using namespace std;
//#define MAXINT 32767
//#define F(X)(sqrt(1-x*x))
const int MAXINT = 32767;
inline double F(double x){

    return (sqrt(1-x*x));
     }

//inline this function
inline double mcint(double a, double b, double max, int n){
       int below = 0, trials = 0;
       double x,y;
       for(trials = 0;trials < n; ++trials){
         x= ((rand()% MAXINT)/(double)MAXINT)*(b-a)+a;
         y= (rand()%MAXINT)/(double)MAXINT;
         if(F(x)>y)
           ++below;
       }
      return((double)below/trials*(b-a)*max);
      }

     
int main(){ 
      double pi, x, y;
      int below, trials, mtrial,i,n_experiment = 5;
    //  double pi_approx[n_experiment];
      vector<double> pi_approx(n_experiment);
      cout<<"TRIALS = \n";
      cin>>mtrial;


//        printf("%d mtrial\n",mtrial);
    //  for(i = pi_approx.begin();i!=pi_approx.end();++i){
    for(i=0;i<n_experiment;++i){ 
        pi_approx[i] = 4 * mcint(0.0,1.0,1.0,mtrial);
     //   printf("%f element", element); 
        mtrial = 10 * mtrial;
      }
    // i = 0;
     cout<<setprecision(5)<<fixed; 
     for(i=0;i<n_experiment;++i){
        std::cout<<"pi trial "<<i<<" = "<<pi_approx[i];
    //    cout<<element;//<<"\t";
        cout<<endl;

//        printf("pi trial %d = %f, \n",i,pi_approx[i]);
       }
      return 0;

} 
       

