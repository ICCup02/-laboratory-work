#include <iostream>
#include <cmath>
#include <math.h> 
#define _USE_MATH_DEFINES
using std::cin;
using std::cout;
int main()
{
    double e = 2.71828, a, b, dx, x0, xn, fx, max=-1.7976931348623158e+308,min= 1.7976931348623158e+308;
    cin >> a >> b >> dx >> x0 >> xn;
    while (x0 <= a) { 
        fx = pow(e,x0)/(3+sin(x0));
        if (max < fx) { max = fx; }
        if (min > fx) { min = fx; }
        cout << fx << '\n';
        x0 =x0+dx;
    }
    while ((x0 <b )&&(x0>a)) {
        fx = log(x0) + x0 * x0;
        if (min > fx) { min = fx; }
        if (max < fx) { max = fx; }
        cout << fx << '\n';
        x0 = x0 + dx;
    }
    while ((x0 >= b)&&(x0<=xn+dx/2)) {
        fx = 1+sin(-x0);
        if (min > fx) { min = fx; }
        if (max < fx) { max = fx; }
        cout << fx << '\n';
        x0 = x0 + dx;
    }
    cout << "max= " << max << std::endl;
    cout << "min= " << min;
    return 0;
}
