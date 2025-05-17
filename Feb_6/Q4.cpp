#include <iostream>
using namespace std;
void fun(int);
void fun(int, int);
void fun(int i) { 
cout << "Value of i is: " << i << endl; 
}
void fun(int a, int b = 9){
cout << "Value of a is: " << a <<endl;
cout << "Value of bis: " <<b<< endl;
}
int main(){
fun(12);
return 0;
}
