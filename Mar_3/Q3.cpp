#include<iostream>
using namespace std;
class Vehicle{
public:
        Vehicle(){
        cout << "This is a Vehicle\n";
        }
};
class Car: public Vehicle{
public:
Car(){
cout << "This Vehicle is Car\n";
}
};

int main(){
Car obj;
return 0;
}

