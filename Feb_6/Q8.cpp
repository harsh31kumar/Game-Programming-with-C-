#include <iostream>
using namespace std;
class Operation {
    int a, b;
public:
    void get();
    void sum();
    void difference();
    void product();
    void division();
};
inline void Operation::get() {
    cout << "Enter first value: ";
    cin >> a;
    cout << "Enter second value: ";
    cin >> b;
}
inline void Operation::sum() {
    cout << "Addition of two numbers: " << (a + b) << "\n";
}
inline void Operation::difference() {
    cout << "Difference of two numbers: " << (a - b) << "\n";
}
inline void Operation::product() {
    cout << "Product of two numbers: " << (a * b) << "\n";
}
inline void Operation::division() {
    if (b != 0)
        cout << "Division of two numbers: " << (static_cast<float>(a) / b) << "\n";
    else
        cout << "Error: Division by zero is not allowed!\n";
}
int main() {
    cout << "Program using inline functions\n";
    
    Operation s;
    s.get();
    s.sum();
    s.difference();
    s.product();
    s.division();
    
    return 0;
}

