#include<iostream>
using namespace std;
void indirectRecursionB(int n);
void indirectRecursionA(int n){
if (n>0){
cout<<n<<" ";
indirectRecursionB(n-1);
}
}
void indirectRecursionB(int n){
if (n>1){
cout<<n<<" ";
indirectRecursionA(n/2);
}
}
int main(){
indirectRecursionA(10);
return 0;
}

