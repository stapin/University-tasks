#include "stdio.h"
#include "euclid.h"
#include "legendre.h"
#include "long_arithmetics.h"
#include "stdlib.h"

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
//         pn = pow2(p, rank);
//         x0_inv = mul_inv(2 * x0, p);
//         k = mod(((a - x0 * x0) / pow2(p, rank)) * x0_inv, p);
//         x0 = mod((x0 + k * pn), pn * p);
//         ++rank;
//         printf("%d\n", k);
//     }
//     return 1;
// }

int sqrt_p(int num, int prime, int length)
{

    if (legendre_symbol(num, prime) == -1) return 0;
    int rank = 1;
    //int root = sqrt_mod(num, prime);
    int root = 3;
    printf("%d\n", root);
    char buffer[10];
    //_itoa_s(root, buffer, 10, 10);
    itoa(root, buffer, 10);
    big_int *x0 = get_big_int_10(buffer, 1);

    //_itoa_s(num, buffer, 10, 10);
    itoa(num, buffer, 10);
    big_int *a = get_big_int_10(buffer, 1);

    //_itoa_s(prime, buffer, 10, 10);
    itoa(prime, buffer, 10);
    big_int *p = get_big_int_10(buffer, 1);
    

    big_int *x0_inv;
    big_int *k;
    big_int *pn;
    big_int *two = get_big_int_10("2", 1);
    while (rank < length)
    {
        pn = big_int_pow(p, rank);
        x0_inv = big_int_mul_inv(x0, p);
        big_int *inv2 = big_int_mul_inv(two, p);

        big_int *x0_temp = big_int_assign(x0);
        big_int *temp1 = big_int_multiply(x0, x0_temp);
        temp1->sign = 0;
        big_int_free(x0_temp);
        big_int *temp2 = big_int_add(a, temp1);
        big_int_free(temp1);

        temp1 = big_int_div(temp2, pn);
        big_int_free(temp2);

        temp2 = big_int_multiply( big_int_multiply_f(temp1, x0_inv), inv2 );
        k = big_int_mod(temp2, p);
        big_int_free(temp2);
        big_int_free(temp1);
        
        print_big_int_10(k);

        temp1 = big_int_multiply(pn, p);
        temp2 = big_int_multiply_f(k, pn);
        x0 = big_int_mod(big_int_add_f(x0, temp2), temp1);
        big_int_free(temp1);
        
        ++rank;
    }
    return 1;
}



int main()
{
    sqrt_p(2, 7, 20);
    //printf("0");
    return 0;
}