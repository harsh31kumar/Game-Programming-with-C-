#include<iostream>
using namespace std;
class Vehicle{
public:
        Vehicle(){
        cout << "This is a Vehicle\n";
        }
};
class Fare{
public:
        Fare(){
        cout << "Fare Vehicle\n";
        }
};
class Car: public Vehicle{
public:
Car(){
cout << "This  Vehicle is Car\n";
}
};

class Bus: public Vehicle, public Fare{
public:
Bus(){
cout << "This  Vehicle is Bus\n";
}
};

int main(){
Bus obj1;
return 0;
}


