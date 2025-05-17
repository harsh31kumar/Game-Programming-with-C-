#include <iostream>
using namespace std;
int main() {
int* pnt =new int;
*pnt=5;
cout<< *pnt;
delete pnt;
return 0;
}
