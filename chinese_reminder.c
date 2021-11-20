#include "stdio.h"
#include "euclid.h"
#include "stdlib.h"

#define N 5

// *m - array of modules.
// *a - array of ratios.
// *x - answer (remainder mod m1*m2*...*mn)
// n - number of equations.
// return 0 (no solutions), x(exist sol).
int chinese_reminder(const int *a, const int *m, int n)
{
    int M = 1;
    int ans = 0;
    int mi = 0;
    for (int i = 0; i < n; i++) M *= m[i];    
    for (int i = 0; i < n; i++)
    {
        mi = M / m[i];
        if (!mul_inv(mi, m[i])) return 0;
        ans += mi * mod(mul_inv(mi, m[i]), m[i]) * a[i];
    }
    return (ans % M);
}

int chinese_reminder2(const int *a, const int *m, int n)
{
    int ans = a[0];
    int ms = m[0];
    for (int i = 1; i < n; i++)
    {
        if (!mul_inv(m[i], ms)) return 0;
        ans *= m[i] * mod(mul_inv(m[i], ms), ms);
        ans += a[i] * ms * mod(mul_inv(ms, m[i]), m[i]);
        ms *= m[i];
    }
    return (ans % ms);
}

int chinese_reminder3(const int *a, const int *m, int n)
{
    
    int lcm2 = m[0];
    int ans = a[0];
    for (int i = 0; i < n-1; i++)
    {
        int b[2] = {-lcm2, m[i+1]};
        int x[2];
        if (!linear_diophantine(b, x, 2, ans - a[i+1])) return 0;
        ans += x[0] * lcm2;
        int nokArg[2] = {lcm2, m[i+1]};
        lcm2 = lcm(nokArg, 2);
    }
    return mod(ans, lcm2);
}

// cx == a (mod m);
int chinese_reminder_general(const int *c, const int *a, const int *m, int n)
{
    int C = lcm(c, n);
    int *cn = malloc(n);
    int *an = malloc(n);
    int *mn = malloc(n);
    for (int i = 0; i < n; i++)
    {
        mn[i] = m[i] * C / c[i];
        an[i] = a[i] * C / c[i];
    }
    int ans = chinese_reminder3(an, mn, n);
    free(cn);
    free(an);
    free(mn);
    if (ans % C != 0) return 0;
    return (ans / C);
}

void print_chinese_rem()
{
    int a[N] = {2, 3, 4, 5, 6};
    int m[N] = {3, 4, 5, 6, 7};
    int c[N] = {1, 1, 1, 1, 1};
    int x = 0;
    printf("1)%d\n", chinese_reminder(a, m, N));
    printf("2)%d\n", chinese_reminder2(a, m, N));
    printf("3)%d\n", chinese_reminder3(a, m, N));
    printf("4)%d", chinese_reminder_general(c ,a, m, N));
}

void print_chinese2()
{
    int a[3] = {0, -4, -9};
    int m[3] = {4, 9, 25};
    printf("%d", chinese_reminder3(a, m, 3));
}

// int main()
// {
//     print_chinese_rem();
//     return 0;
// }