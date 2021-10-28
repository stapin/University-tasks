#include "stdio.h"


typedef long long ull;

int mod_pow_recursive(int x, long y, int m)
{
    if (y == 0) return 1;
    if (y&1)
    {
        int t = mod_pow_recursive(x, y>>1, m);
        return (t*t*x)%m;
    }  
    else
    {
        int t = mod_pow_recursive(x, y>>1, m);
        return (t*t)%m;
    }
}
    
int mod_pow(ull x, ull y, ull m)
{
    ull ans = 1;
    while (y)
    {
        if (y&1)
        {
            ans *= x;
            ans %= m;
        }
        y >>= 1;
        x *= x; x %= m;
    }
    return ans;
}

int mod_fibonachi(unsigned long n, int m)
{
    int c11 = 1, c12 = 0, c21 = 0, c22= 1;
    int a11 = 0, a12 = 1, a21 = 1, a22 = 1;
    while (n)
    {
        if (n&1)
        {
            int b11 = c11, b12 = c12, b21 = c21, b22 = c22;
            c11 = b11 * a11 + b12 * a21;
            c12 = b11 * a12 + b12 * a22;
            c21 = b21 * a11 + b22 * a21;
            c22 = b21 * a12 + b22 * a22;
            c11 %= m; c12 %= m; c21 %= m; c22 %= m;
        }
        int b11 = a11, b12 = a12, b21 = a21, b22 = a22;
        a11 = b11 * b11 + b12 * b21;
        a12 = b11 * b12 + b12 * b22;
        a21 = b21 * b11 + b22 * b21;
        a22 = b21 * b12 + b22 * b22;
        a11 %= m; a12 %= m; a21 %= m; a22 %= m;
        n >>= 1;
    }
    return c21;
}
