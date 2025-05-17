#include <iostream>
using namespace std;

int factorialIndirect1(int n, int acc) {
if (n==0 ||n==1) {
return acc;
}
else {
return factorialIndirect1(n-1, n*acc);
}
}
int factorialIndirect2(int n,int acc) {
return factorialIndirect1(n, acc);
}
int main() {
int num;
cout<< "Enter a +ve no: ";
cin >>num;
if (num<0) {
cout << "Factorial isn't defined for -ve no. . .";
} 
else {
cout << "Factorial of "<< num<< "="<<factorialIndirect1(num, 1);
}
return 0;
}
