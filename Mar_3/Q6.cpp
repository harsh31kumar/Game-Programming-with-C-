#include<iostream>
using namespace std;
class Vehicle{
public:
        Vehicle(){
        cout << "This is a Vehicle\n";
        }
};
class Car:public Vehicle{
public:
        Car(){
        cout << "This Vehicle is a Car\n";
        }
};
class Bus: public Vehicle{
public:
Bus(){
cout << "This  Vehicle is Bus\n";
}
};

int main(){
Car obj;
Bus obj1;
return 0;
}


