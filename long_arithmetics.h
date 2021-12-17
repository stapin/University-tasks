#ifndef LONG_ARITHMETICS
#define LONG_ARITHMETICS

#define BASE 256

typedef struct big_int
{
    unsigned int length;
    unsigned char *number;
    unsigned char sign;  // 0 (-), 1 (+);
} big_int;


/*   Functions working with chars.   */

char *clean_zeros(const char *num);

char *clean_zeros2(char *num);

char *from_2_to_10(const char *bin_number);

char *from_10_to_2(const char *number);


/*  Auxiliary functions  */

big_int *big_int_assign(const big_int *n);

void big_int_free(big_int *n);

void big_int_replace(big_int *old, big_int *newValue);


/* Getters */

big_int *get_big_int(const char *bin_num, unsigned char sign);

big_int *get_big_int_10(const char *decimal, unsigned char sign);

char *big_int_get_bin(const big_int *n);

char *big_int_get_decimal(const big_int *n);


/* Comparison */

short big_int_is_greater_or_equal(const big_int *n1, const big_int *n2);

short big_int_is_greater(const big_int *n1, const big_int *n2);

short big_int_is_equal(const big_int *n1, const big_int *n2);

short big_int_is_zero(const big_int *n);


/*  Arithmetic operations  */

// n1 - n2; n1, n2 >= 0;
// if n2 > n1 returns 0;
big_int *big_int_sub_positive(const big_int *n1, const big_int *n2);

big_int *big_int_add(const big_int *n1, const big_int *n2);

big_int *big_int_add_f(big_int *n1, big_int *n2);

big_int *big_int_sub(const big_int *n1, const big_int *n2);

void left_shift(big_int *x, int value);

void right_shift_2(big_int *x);

void left_shift_2(big_int *x);

big_int *big_int_multiply(const big_int *n1, const big_int *n2);

big_int *big_int_multiply_f(big_int *n1, big_int *n2);

big_int *big_int_pow(const big_int *n, int r);

big_int *big_int_mod(const big_int *divident, const big_int *modul);

big_int *big_int_div(const big_int *divident, const big_int *divisor);

big_int *big_int_mod_pow(const big_int *n, const big_int *y, const big_int *m);

void big_int_reminder_division(const big_int *divident, const big_int *divisor, big_int *(*result));


/*  MATRIX AND OPERATIONS  */

big_int **big_int_create_matrix_2x2(int *k);

big_int **big_int_multiply_matrix(big_int * const *matrix1, big_int * const *matrix2);

void **big_int_matrix_free(big_int **m);

void big_int_euclid_extended(const big_int* a_in, const big_int* b_in, big_int* *x, big_int* *y);

big_int *big_int_mul_inv(const big_int *a, const big_int *p);

/*  Output block functions  */

void print_big_int_2(const big_int *n);

void print_big_int_10(const big_int *n);

void print_matrix_2x2(big_int **matrix);


#endif