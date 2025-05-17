#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string brand;
    string model;
    float price;

public:
    Car(string b, string m, float p) {
        brand = b;
        model = m;
        price = p;
    }
    
    void display() {
        cout << "Car Details:" << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Price: $" << price << endl;
    }

    ~Car() {
        cout << "Car object for " << brand << " " << model << " is being deleted." << endl;
    }
};

int main() {
    Car* myCar = new Car("Tesla", "Model S", 79999.99); 
    myCar->display(); 

    delete myCar; 
    return 0;
}

