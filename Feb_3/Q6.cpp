#include<iostream>
#include<string>
int add(int a, int b){
return a+b;
}
int sub(int a, int b){
return a-b;
}
int mul(int a, int b){
return a*b;
}
int main(){
int(*funcArray[3])(int,int)={add,sub,mul};
int x=2,y=3;

std::cout<<"Add :" << funcArray[0](x,y)<<std::endl; 
std::cout<<"Sub :" << funcArray[1](x,y)<<std::endl; 
std::cout<<"Mul :" << funcArray[2](x,y)<<std::endl; 
return 0;
}
