#include <iostream>
using namespace std;
int main() {
int age;
cout << "Enter your age: ";
cin >> age;
if (age >= 18) {
cout << "You can vote." << endl;
} 
else {
cout << "Not eligible for voting." << endl;
 }
return 0;
}
