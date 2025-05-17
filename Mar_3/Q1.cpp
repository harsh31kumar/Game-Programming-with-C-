#include<iostream>
using namespace std;
class Base{
    private:
        int privateVar;
    public:
        Base(int val):privateVar(val){}
        int getPrivateVar() const {
            return  privateVar;
            }
        void setPrivateVar(int val){
             privateVar=val;
             }
  };
class Derived: public Base{
public:
Derived(int val): Base(val){}
     void displayPrivateVar()
     {
        cout << "Value of privateVar in Base class: "<< getPrivateVar()<<endl;
     }
     void modifyPrivateVar(int val)
     {
         setPrivateVar(val);
     }
};
int main(){
    Derived obj(10);
    obj.displayPrivateVar();
    obj.modifyPrivateVar(20);
    obj.displayPrivateVar();
    return 0;
  }
