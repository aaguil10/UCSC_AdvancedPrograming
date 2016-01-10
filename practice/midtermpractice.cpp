
#include<vector>
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


class Demon {
 public:
  Demon();
  inline int GetHealth(){
    return this->health;
  } 

 private:
  string name;
  string type;
  int health;
  friend class Angle;

};

Demon::Demon(){
  int it = 0;
  cout << "Enter Demon name: " << endl;
  cin >> name;
  cout << "Enter Demon health: " << endl;
  cin >> health;
  cout << "Enter Demon type: " << endl;
  cin >> type;
  health = 40;
}



class Angle {
 public:
  Angle();
  int GetHealth(){
    return this->health;
  }
  void TakeHealth(Demon &D){
    cout << "Demon had " << D.GetHealth() << endl;
    D.health = D.health - this->health;
    cout << "But now it has " << D.GetHealth() << endl;
  }
 
 private:
  string name;
  int health = 100;
  friend class Demon;

};

Angle::Angle(){
  int it = 0;
  cout << "Enter Angle name: " << endl;
  cin >> name; 
  cout << "Enter Angle health: " << endl;
  cin >> health;
  health = 10;
}

template<class Vec>
void PrintVec(vector<Vec> &V, string s){
  cout << s;
  for (auto p = V.begin(); p != V.end(); p++) {
    cout << *p << " ";
  }
  cout << endl;
}

int main(){
   int g = 0;
   vector<double> r;
   for (double i = 0; i < 10; i++) {
     r.push_back(static_cast<double>(i/10));
   }
  PrintVec(r,"R: ");

}

