#include "stdio.h"
#include "euclid.h"
#include "mod_pow.h"
#include "time.h"
#include "math.h"
//#define ull unsigned long long


// p - prime.
int legendre_symbol(ull a, ull p)
{
    if ((a % p) == 0) return 0;
    int ans = mod_pow(a, (p-1)>>1, p);
    if (ans == 1) return ans;
    else return -1;
}

// p != 2;
int legendre_symbol2(ull q, ull p)
{
    if ((q % p) == 0) return 0;
    short ans = 1;
    ull temp;
    short res = 1;
    int rank = 0;
    
    while ((q != 1) && (p != 1))
    {
        q %= p;
        if (!(q & 1))
        {
            while (!(q&1)) {q >>= 1; rank++; }

            if ((p & 3) == 1)
            {
                if ((p>>2) & 1) res = -1;
            }
            else if (!((p>>2) & 1)) res = -1;
            if (!(rank & 1)) res *= res;
            if (res < 0) ans = -ans;
            res = 1; rank = 0;
        }
        if (((q & 3) == 3) && ((p & 3) == 3)) ans = -ans;
        temp = p;
        p = q; q = temp;
    }
    return ans;
}

void time_diff()
{
    ull a = 2429648;
    ull p = 99999539;
    //scanf("%d", &a);
    int ans1, ans2;
    clock_t time1, time2;
    

    time1 = clock();
    for (int i = 0; i < 10000000; i ++)
    {
        ans1 = legendre_symbol(a, p);
    }
    time2 = clock();
    printf("time1 = %li\nans1 = %d\n", (time2 - time1), ans1);

    time1 = clock();
    for (int i = 0; i < 10000000; i ++)
    {
        ans2 = legendre_symbol2(a, p);
    }
    time2 = clock();
    printf("time2 = %li\nans2 = %d\n", (time2 - time1), ans2);

    // printf("%d ", legendre_symbol(a, p));
    // printf("%d\n", legendre_symbol2(a, p));
}

ull pow2(ull a, ull b)
{
    int ans = 1;
    while (b)
    {
        ans *= a; b--;
    }
    return ans;
}

int sqr_mod(int a, int p)
{
    if (legendre_symbol2(a, p) != 1) return 0;
    if ((p & 3) == 3) return mod_pow(a, (p+1)/4, p);
    int notRes;
    for (int i = 2; i < p-1; i++)
    {
        if (legendre_symbol2(i, p) == (-1))
        {
            notRes = i;
            break;
        }    
    }
    int r = 0, rb = 0;
    int h = p - 1;
    while (!(h & 1)) { h >>= 1; r++; }
    for (int i = 0; i <= r; i++)
    {
        if (mod_pow(a, pow(2, i) * h, p) == 1)
        {
            r = i;
            break;
        }
        
    }
    int x, y;
    int k = 0;
    while (r)
    {
        x = mod_pow(a, pow2(2, r) * h, p);
        y = mod_pow(notRes, rb, p);
        if ((x*y) % p == 1);
        else { rb += (p-1) >> 1; }
        r--; rb >>= 1;
    }
    x = mod_pow(a, h, p);
    y = mod_pow(notRes, rb, p);
    if ((x*y)%p != 1) rb += (p-1)>>1; 
    return mod(mod_pow(a, (h+1)>>1, p) * mod_pow(notRes, rb>>1, p), p);
}

void test()
{
    int p = 13;
    for (int i = 0; i < (p+1)/2; i++)
    {
        printf("%d %d %d\n", i, legendre_symbol2(i, p), mod(i*i, p));
    }
    printf("%d\n", mod_pow(3, 7, p));
    printf("%d", sqr_mod(2, 129));
}

int main()
{
    int p = 1789, q = 103;
    int ans = sqr_mod(q, p);
    printf("ans = %d\n", ans);
    // printf("%d\n", p - ans);
    // printf("%d\n", mod_pow(ans, 2, p));
    printf("%d %d\n", sqr_mod(108, 24481), legendre_symbol2(108, 24481));
    printf("%d\n", mod_pow(16509, 2, 24481));
    // int a = 103, r = 1, h = 447;
    // int a1 = 103, r1 = 0, h1 = 447;
    // printf("1) %lli\n", pow2(a, pow2(2, r) * h) % p);
    // printf("2) %lli\n", mod_pow(a, pow2(2, r) * h, p));
    // printf("1) %d\n", pow2(a1, 2 * h1) % p);
    // printf("2) %d\n", mod_pow(a1, 2 * h1, p));
    // printf("%d\n", sqr_mod(3, 13));
    p = 157457; q = 135;
    //p = 25799;
    //for (int i=1; i < p; i++) printf("=%d\n", legendre_symbol2(i, p));
    ans = sqr_mod(q, p);
    printf("%d %d\n", ans, mod_pow(ans, 2, p));
    return 0;
}