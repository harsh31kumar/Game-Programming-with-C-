#include<iostream>
using namespace std;
class Derived;
class Base{
    private:
        int privateVar;
    public:
        Base(int val):privateVar(val){}
            friend class Derived;
  };

class Derived{
public:
     void displayPrivateVar(Base& obj)
     {
        cout << "Value of privateVar in Base class: "<< obj.privateVar << endl;
     }
     void modifyPrivateVar(Base& obj, int val)
     {
         obj.privateVar=val;
     }
};
int main(){
    Base baseobj(10);
    Derived derivedobj;
    derivedobj.displayPrivateVar(baseobj);
    derivedobj.modifyPrivateVar(baseobj,20);
    derivedobj.displayPrivateVar(baseobj);
    return 0;
  }
