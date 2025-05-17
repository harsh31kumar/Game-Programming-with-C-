#include<iostream>
using namespace std;
void directRecursion(int n){
if (n>0){
cout<<n<<"";
directRecursion(n-1);
}
}
int main(){
directRecursion(10);
return 0;
}

