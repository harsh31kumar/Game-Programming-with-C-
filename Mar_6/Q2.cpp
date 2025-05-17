#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() { 
        cout << "Animal makes a sound\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() override { 
        cout << "Dog barks\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() override { 
        cout << "Cat meows\n";
    }
};

int main() {
    Animal* a = nullptr; 
    Dog d;
    Cat c;

    a = &d;
    a->makeSound(); 

    a = &c;
    a->makeSound(); 
    
    return 0;
}

