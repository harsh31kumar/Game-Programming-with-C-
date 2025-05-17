#include<iostream>
using namespace std;
class Vehicle{
public:
        Vehicle(){
        cout << "This is a Vehicle\n";
        }
};
class FourWheeler{
public:
        FourWheeler(){
        cout << "This is a FourWheeler\n";
        }
};
class Car: public Vehicle, public FourWheeler{
public:
Car(){
cout << "This 4 Wheeler Vehicle is Car\n";
}
};

int main(){
Car obj;
return 0;
}


