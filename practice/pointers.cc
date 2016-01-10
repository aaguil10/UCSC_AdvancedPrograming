
#include<iostream>
#include<string>
using namespace std;


class Person{
 public:
  void pprint(){
    cout << "Person\n";
  }
 private:
  int a,b;


};


int main(){
  cout << "Hello\n";
  Person me;
  me.pprint();
  Person it;
  it.pprint();

}
