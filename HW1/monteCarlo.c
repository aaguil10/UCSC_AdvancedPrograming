#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXINT   32767
#define F(X) (sqrt(1-x*x))

double mcint(double a, double b, double max, int n){
   int  below = 0, trials = 0;
   double  x, y;
      for(trials = 0; trials < n; ++trials ) {
         x =  ((rand() % MAXINT)/(double)MAXINT)* (b - a)  + a;
         y =  (rand() % MAXINT)/(double)MAXINT;
         if (F(x) > y){
            ++below;
         }
      }
   return ((double)below/trials  * (b - a) * max);
}





int main(){
   double   pi, x, y;
   int      below, trials, mtrial, i, n_experiment = 5;
   double   pi_approx[n_experiment];

   printf("TRIALS = \n");
   scanf("%d", &mtrial);

   for( i = 0; i < n_experiment; ++i ) {
      pi_approx[i] = 4 * mcint(0.0, 1.0, 1.0, mtrial) ;
      mtrial = 10 * mtrial;
   }

   for( i = 0; i < n_experiment; ++i ){
      printf("pi trial %d = %f, \n", i,  pi_approx[i]);
   }
   return 0;
}

