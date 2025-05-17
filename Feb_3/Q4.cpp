#include<iostream>
#include<string>
void printString(const std::string*str){
std::cout<< *str<<std::endl;
}
int main(){
std::string myString = "this is Pss by pointer";
printString(&myString);
return 0;
}
