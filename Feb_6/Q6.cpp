
#include<iostream>
using namespace std;
class Largest  {
   int a,b,m;
   public:
      void setDemo();
      friend void findMax(Largest);
 };
void Largest::setDemo()  {
     cout << "Enter the first number: ";
     cin >> a;
     cout << "Enter the second number: ";
     cin >> b;
 }
void findMax(Largest l)   {
     if(l.a>l.b)  
         l.m=l.a;
     else
         l.m=l.b;
     cout << "\nLargest number is: "<< l.m << endl;
 }
int main(void)  {
    Largest l1;
    l1.setDemo();
    findMax(l1);
 }
