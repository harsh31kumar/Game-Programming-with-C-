#include <iostream>
using namespace std;
void fun(int);
void fun(int&);
int main(){
int a = 10;
fun(a); 
return 0;
}
