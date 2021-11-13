#include "stdio.h"

typedef long long ull;

int euclid_recursive(int a, int b)
{
    if (b == 0) return a;
    else return euclid_recursive(b, a%b);
}

int euclid(int a, int b)
{
    while(a && b)
    {
        if (a > b) a %= b;
        else b %= a;
    }
    if (a) return a;
    else return b;
}

int euclid_binary(int a, int b)
{
    int k = 0;
    while (a&1 == 0 && b&1 == 0)
    {
        a >>= 1; b >>= 1;
        k++;           
    }
    while(a && b)
    {
        if (a == b) return b<<k;
        while (a&1 == 0) a >>= 1;
        while (b&1 == 0) b >>= 1; 
        if (a < b) b -= a;
        else a -= b;       
    }
}

int abs(int a)
{
    if (a > 0) return a;
    else return -a;
}

int euclid_extended(int a, int b, int *x, int *y)
{
    int a11=1, a12=0, a21=0, a22=1;
    int a11n, a12n, a21n, a22n;
    int b11;
    int i = 1;
    *x = 1; *y = 1;
    if (a < 0)
    {
        *x = -1; a = -a;
    }
    if (b < 0)
    {
        *y = -1; b = -b;
    }
    int flag = (a < b) ? 1 : 0;
    while (a && b)
    {
        if (a > b)
        {
            b11 = a / b;
            a %= b;
        } 
        else 
        {
            b11 = b / a;
            b %= a;
        }
        a11n = a11 * b11 + a12;
        a12n = a11;
        a21n = a21 * b11 + a22;
        a22n = a21;
        a11 = a11n; a12 = a12n; a21 = a21n; a22 = a22n;
        i = -i;
    }
    if (flag)
    {
        *x *= a12 * (-i);
        *y *= a22 * i;
    }
    else
    {
        *x *= a22 * i;
        *y *= a12 * (-i);
    }
    return 0;
}

// a1*x1 + ... + an*xn = b
// returns 0 (no sol), 1(sol exist)
int linear_diophantine(int *a, int *x, int n, int b)
{
    int nod = euclid(abs(a[0]), abs(a[1]));
    int d;
    euclid_extended(a[0], a[1], x, x + 1);
    for (int i=1; i < (n-1); i++)
    {    
        euclid_extended(nod, a[i+1], &d, x + i + 1);
        nod = euclid(nod, abs(a[i+1]));
        for (int p=0; p < (i+1); p++) x[p] *= d;
    }
    if (b < 0) 
    {
        for (int i = 0; i < n; i++) x[i] = -x[i];
        b = -b;
    }
    if (b%nod == 0)
    {
        for (int i = 0; i < n; i++) x[i] *= (b/nod);
        return 1;
    } 
    return 0;
}

int lcm(const int *a,  int n)
{
    int nok = a[0];
    for (int i=1; i < n; i++) 
        nok = nok * a[i] / euclid_binary(nok, a[i]);
    return nok;
}

int mul_inv(int a, int m)
{
    int x, y;
    if (euclid_binary(a, m) != 1) return 0;
    euclid_extended(a, m, &x, &y);
    return x;
}

ull mod(ull x, ull m)
{
    if (x >= 0) return x % m;
    else return m + (x % m);
}
