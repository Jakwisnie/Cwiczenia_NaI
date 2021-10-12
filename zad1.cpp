
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int f2(int i)
{ int x = 0;
x=((2*(i%2)-1)*i/2);
return x;}
int f1(int y){ 
    int z= 0;
    z = (20-abs(y));
    return y;}

void obliczenia(int n)
{
   int max_x = f2(0);
   int max_y = f1(max_x);
    int x;
    int y;
    for (int i = 1  ;i<=n;i++){

        x = f2(i);
        y = f1(x);

        if(y > max_y)
            {
            max_x = x;
            max_y = y;
            }
    }
   cout<<"max_ x = "<<max_x<<endl;
   cout<<"max_y = "<< max_y<<endl;
}
int main() {



 obliczenia(5);
    return 0;
}