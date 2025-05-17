#include<iostream>
using namespace std;
class Base{
    public:
        int publicVar;
        void display(){
             cout << "Value of publicVar: "<< publicVar << endl;
        }
  };
class Derived: public Base{
public:
     void displayMember()
     {
         display();
     }
     void modifyMember(int pub)
     {
     publicVar=pub;
     }
  };
int main(){
    Derived obj;
    obj.modifyMember(10);
    obj.displayMember();
    return 0;
  }
