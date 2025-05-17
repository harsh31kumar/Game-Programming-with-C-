#include <iostream>
using namespace std;

int factorialDirect(int n) {
if (n==0 || n==1) {
return 1;
}
else {
return n*factorialDirect(n-1);
}
}
int main() {
int num;
cout << "Enter a +ve no: ";
cin >> num;
if (num < 0) {
cout << "Factorial isn't defined for -ve no.";
} 
else {
cout <<"Factorial of "<< num <<"= "<< factorialDirect(num);
}
return 0;
}
