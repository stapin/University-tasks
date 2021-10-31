#ifndef LONG_ARITHMETICS
#define LONG_ARITHMETICS


typedef struct big_int
{
    unsigned int length;
    unsigned char *number;

} big_int;


char *clean_zeros(const char *num);

big_int *get_big_int( char *bin_number);

void print_big_int2(const big_int *n);

big_int *big_int_add(const big_int *n1, const big_int *n2);

big_int *big_int_sub(const big_int *n1, const big_int *n2);

char *from_10_to_2(const char *number);

big_int *get_big_int_10(const char *decimal);

char *from_2_to_10(const char *bin_number);

char *big_int_get_bin(const big_int *n);

void print_big_int_10(const big_int *n);

char *big_int_get_decimal(const big_int *n);

char *add_bin(const char *n1, const char *n2, int len1, int len2);

big_int *big_int_multiply(const big_int *n1, const big_int *n2);

big_int *big_int_copy(big_int *n);

big_int *big_int_pow2(const big_int *n, int r);

void test_10();

void test_add_bin();

void test_multiply();

void test_pow()

#endif