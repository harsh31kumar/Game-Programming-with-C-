#include<iostream>
using namespace std;

int main(){
int* ptr1 = new int;
*ptr1 = 8; 
float *ptr2 = new float(28.489);
int *ptr3 = new int[26];

cout << "Value of pointer variable 1: " << *ptr1<<endl;
cout << "Value of pointer variable 2: " << *ptr2<<endl;

if (!ptr3)
cout << "Allocation of memory failed\n";
else {
for (int i = 1; i < 16; i++)
ptr3[i] = i+1;
cout << "Value of store in block of memory: ";
for (int i = 1; i < 16; i++)
cout << ptr3[i] << " ";
}

cout << *ptr1;
delete ptr1;
delete ptr2;
delete ptr3;
return 0;

}
