#include "stdio.h"

#define N 3

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
    int flag = 0;
    if (a < b) flag = 1;
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

int abs(int a)
{
    if (a > 0) return a;
    else return -a;
}

int linear_diophantine(int *a, int n, int b, int *x)
{
    if (b <= 0) return 0;
    int nod = euclid(abs(a[0]), abs(a[1]));
    int d;
    euclid_extended(a[0], a[1], x, x+1);
    for (int i=1; i < (n-1); i++)
    {    
        euclid_extended(nod, a[i+1], &d, x + i + 1);
        nod = euclid(nod, abs(a[i+1]));
        for (int p=0; p < (i+1); p++) x[p] *= d;
    }
    if (b%nod == 0)
    {
        for (int i = 0; i < n; i++) x[i] *= (b/nod);
        return 1;
    } 
    return 0;
}

int mod(int x, int m)
{
    if (x > 0) return x % m;
    else return m + (x % m);
}

int main()
{
    // int a[N] = {21, -5};
    // int x[N];
    // if (linear_diophantine(a, N, 1, x))
    // {
    //     for (size_t i = 0; i < N; i++)
    //     {
    //         printf("%d ", x[i]);
    //     }
    // }
    // else printf("No solutions");
    // int k, y;
    // euclid_extended(110, -9, &k, &y);
    // printf("%d %d\n", k, y);
    // printf("%d", mod(-15, 7));

    int a[N] = {2166, 3534, 1302};
    int x[N];
    if (linear_diophantine(a, N, 126, x))
    {
        for (size_t i = 0; i < N; i++)
        {
            printf("%d ", x[i]);
        }
    }
    else printf("No solutions");
    int k, y;
    
    return 0;
}
