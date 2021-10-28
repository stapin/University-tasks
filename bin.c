


// int chinese_reminder3(const int *a, const int *m, int n)
// {
//     int ans = 0;
//     int M = 0;
//     for (int i = 0; i < n; i++)
//     {
//         int nok = a[i-1] * a[i] / euclid_binary(a[i-1], a[i]);
//         int a[2] = {-m[i-1], m[i]};
//         int x[2];
//         linear_diophantine(a, x, 2, a[i-1] - a[i]);
//     }
// }

// int chinese_reminder3(const int *a, const int *m, int n)
// {
//     int ans = 0;
//     int *x;
//     int nok = lcm(a);
// }

// int chinese_reminder3(const int *a, const int *m, int n)
// {
//     int ans = a[0];
//     int ms = m[0];
//     int nod = a[0];
//     int lcm = a[0];
//     int p = m[0];
//     for (int i = 1; i < n; i++)
//     {
//         lcm = lcm * m[i] / euclid(lcm, m[i]);
//         ans *= euclid(m[i], lcm) * mod(mul_inv(m[i], ms), ms);
//         ans += a[i] * ms * mod(mul_inv(ms, m[i]), m[i]);
//         ms *= m[i];
//     }
//     return (ans % ms);

// }

// for (int i = 0; i < n; i++)
//     {
//         for (int j = i; j < n; j++)
//             if (!((a[i] - a[j]) % euclid_binary(m[i], m[j]) == 0)) return 0;
//     }


// int chinese_rem(const int *a, const int *m, int n)
// {
//     int M = 1;
//     int ans = 0;
//     int mi = 0;
//     for (int i = 0; i < n; i++) M *= m[i];    
//     for (int i = 0; i < n; i++)
//     {
//         mi = M / m[i];
//         int b[2] = {mi, -m[i]};
//         int x[2];
//         if (!linear_diophantine(b, x, 2, 1)) return 0;
//         ans += mi * mod(x[0], m[i]) * a[i];
//     }
//     return (ans % M);
// }

// if (q == 2)
// {
//     if ((p & 3) == 1)
//     {
//         if ((p>>2) & 1) ans = -ans;
//         return ans;
//     }
//     if (!((p>>2) | 0)) ans = -ans;
//     return ans;
// }


// int sqr_mod(int a, int p)
// {
//     if (legendre_symbol2(a, p) != 1) return 0;
//     if ((p & 3) == 3) return mod_pow(a, (p+1)/4, p);
//     int notRes;
//     for (int i = 2; i < p-1; i++)
//     {
//         if (legendre_symbol2(i, p) == (-1))
//         {
//             notRes = i;
//             break;
//         }    
//     }
//     printf("nr = %d\n", notRes);
//     int r = 0, rb = 0;
//     int h = p - 1;
//     while (!(h & 1)) { h >>= 1; r++; }
//     // for (int i = 0; i <= r; i++)
//     // {
//     //     if (mod_pow(a, pow(2, i) * h, p) == 1)
//     //     {
//     //         r = i;
//     //         break;
//     //     }
        
//     // }
//     printf("r = %d\n", r);
//     int x, y;
//     int k = 0;
//     while (r)
//     {
//         // printf("a= %d r= %d h= %d\n", a, r, h);
//         // printf("1) %d\n2) %d\n", mod(pow2(a, pow2(2, r) * h), p), mod_pow(a, pow2(2, r) * h, p));
//         x = mod_pow(a, pow2(2, r) * h, p);
//         y = mod_pow(notRes, ((p-1) * rb)>>(k+1), p);
//         //if ((mod_pow(a, pow2(2, r) * h, p) * mod_pow(notRes, ((p-1)>>1) * rb, p))%p == 1) r--;
//         //printf("x=%d y=%d\n", x, y);
//         if ((x*y) % p == 1) 
//         {
//             r--;
//             if (rb != 0) k++;
//         }
//         else { rb++; r--; k++; }
//     }
//     x = mod_pow(a, h, p);
//     y = mod_pow(notRes, (((p-1)>>1) * rb)>>k, p);
//     if ((x*y)%p != 1) rb++; 
//     return mod(mod_pow(a, (h+1)>>1, p) * mod_pow(notRes, ((p - 1) * rb)>>(k+2), p), p);
// }


#include "stdio.h"

int main()
{
    int a = 100000000;
    long long b = 10000 * (long long)a;
    printf("%lli", b);
    return 0;
}