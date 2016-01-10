//Alejandro Agilar
#include <iostream>
#include <string>
using namespace std;

inline void pr_message(string s = "hello world!"){
   cout << s << endl;
}

inline void big_string(string s = "please enter a string",int k = 1){
   for(int i = 0; i < k; i++){
      cout << i <<": " << s << endl;
   }
}

int main(){
   pr_message("Gia!");
   big_string();
}


