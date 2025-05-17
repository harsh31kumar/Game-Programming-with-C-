#include<iostream>
using namespace std;
class Base{
    private:
        int privateVar;
    public:
        Base(int val):privateVar(val){}
        int getPrivateVar() const { return privateVar; }
        void getPrivateVar(int val) { privateVar = val; }
        }
  };
class Derived: public Base{
public:
Derived(int val): Base(val){}
     void displayMember()
     {
         cout << "Value of privatevar in base class"<< getPrivateVar()<<endl;
     }
     void modifyMember(int val)
     {
     publicVar=val;
     }
  };
int main(){
    Derived obj(10);
    obj.modifyMember();
    obj.displayMember(20);
    return 0;
  }
