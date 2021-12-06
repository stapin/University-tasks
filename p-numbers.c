#include "stdio.h"
#include "euclid.h"
#include "legendre.h"
#include "long_arithmetics.h"

// int sqrt_p(int a, int p, int n)
// {

//     if (legendre_symbol2(a, p) == -1) return 0;
//     int rank = 1;
//     int x0 = 3;
//     int x0_inv;
//     int k;
//     int pn;
//     printf("%d\n", x0);
//     while (rank < n)
//     {
//         ++rank;
//         pn = pow2(p, rank);
//         x0_inv = mul_inv(x0, pn);
//         k = mod(((a - x0 * x0) / pow2(p, rank - 1)) * x0_inv * mul_inv(2, pn), pn);
//         x0 = (x0 + k * pow2(p, rank - 1)) % pn;
//         printf("%d\n", x0);
//     }
//     return 1;
// }

int sqrt_p(int a, int p, int n)
{

    if (legendre_symbol2(a, p) == -1) return 0;
    int rank = 1;
    int x0 = 3;
    int x0_inv;
    int k;
    int pn;
    printf("%d\n", x0);
    while (rank < n)
    {
        pn = pow2(p, rank);
        x0_inv = mul_inv(2 * x0, p);
        k = mod(((a - x0 * x0) / pow2(p, rank)) * x0_inv, p);
        x0 = mod((x0 + k * pn), pn * p);
        ++rank;
        printf("%d\n", k);
    }
    return 1;
}

int sqrt_p(int a, int p, int n)
{

    if (legendre_symbol2(a, p) == -1) return 0;
    int rank = 1;
    int x0 = 3;
    int x0_inv;
    int k;
    int pn;
    printf("%d\n", x0);
    while (rank < n)
    {
        pn = pow2(p, rank);
        x0_inv = mul_inv(2 * x0, p);
        k = mod(((a - x0 * x0) / pow2(p, rank)) * x0_inv, p);
        x0 = mod((x0 + k * pn), pn * p);
        ++rank;
        printf("%d\n", k);
    }
    return 1;
}



int main()
{
    sqrt_p(2, 7, 5);
    return 0;
}