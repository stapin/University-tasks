#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define BASE 256

typedef struct big_int
{
    unsigned int length;
    unsigned char *number;
    unsigned char sign;  // 0 (-), 1 (+);
} big_int;


/*   Functions working with chars.   */

char *clean_zeros(const char *num)
{
    long len = strlen(num);
    char *result = malloc(len + 1);
    long ind = 0;
    for (long i = 0; i < len; i++)
    {
        if (num[i] != '0')
        {
            ind = i;
            break;
        }
    }
    if (ind != 0)
    {
        for (long i = 0; i < len - ind; i++)
        {
            result[i] = num[i + ind];
        }
        result = realloc(result, len - ind + 1);
        result[len - ind] = '\0';
    }
    else
    {
        for (long i = 0; i < len; i++)
        {
            result[i] = num[i];
        }
        result[len] = '\0';
        
    }
    return result;
}

char *clean_zeros2(char *num)
{
    int len = strlen(num);
    int ind = 0;
    for (int i = 0; i < len; i++)
    {
        if (num[i] != '0')
        {
            ind = i;
            break;
        }
    }
    if (ind != 0)
    {
        for (int i = 0; i < len; i++)
        {
            num[i] = num[i + ind];
        }
        num = realloc(num, len - ind + 1);
        num[len - ind] = '\0';
    }
    return num;
}

char *from_2_to_10(const char *bin_number)
{
    int len = strlen(bin_number);
    char *result = malloc(len);
    char *power_2 = malloc(len);
    // digit result, digit power_2.
    int dr, dp;
    int rem = 0;
    int rem2 = 0;
    for (int i = 0; i < len; i++)
    {
        result[i] = '0';
        power_2[i]  = '0';
    }
    power_2[len - 1] = '1';
    for (int i = len - 1; i >= 0; i--)
    {
        if (bin_number[i] - '0')
        {
            for (int j = len - 1; j >= 0; j--)
            {
                dr = result[j] - '0' + rem;
                dp = power_2[j] - '0';
                if (dr + dp >= 10) rem = 1;
                else rem  = 0;
                result[j] = (dr + dp) % 10 + '0';
            }
        }
        // power_2 *= 2;
        for (int j = len - 1; j >= 0; j--)
        {
            dp = (power_2[j] - '0');
            power_2[j] = (((dp + dp) % 10) + rem2) + '0';
            if (dp + dp >= 10) rem2 = 1;
            else rem2 = 0;
        }
    }
    free(power_2);
    // clean zeros from beginngig of number.
    int ind = 0;
    for (int i = 0; i < len; i++)
    {
        if (result[i] - '0')
        {
            ind = i;
            break;
        }
    }
    for (int i = ind; i < len; i++)
    {
        result[i - ind] = result[i];
    }
    result = realloc(result, len - ind + 1);
    result[len - ind] = '\0';
    return result;
}

char *from_10_to_2(const char *number)
{
    int len = strlen(number);
    char *num = malloc(len);
    for (size_t i = 0; i < len; i++)
    {
        num[i] = number[i];
    }
    
    char *result = malloc(len*4 + 1);
    result[len * 4] = '\0';
    for (int i = 0; i < len * 4; i++) result[i] = '0';
    int it = 1;
    short digit;
    short rem = 0;
    unsigned char flag = 1;
    while (flag)
    {
        flag = 0;
        if ((num[len - 1] - '0') & 1) result[len*4 - it] = '1';
        else result[len*4 - it] = '0';
        ++it;
        // n //= 2;
        for (int i = 0; i < len; i++)
        {
            digit = num[i] - '0' + rem;
            if (digit) flag = 1;
            if (!flag) continue;
            if (digit & 1)
            {
                digit >>= 1;
                rem = 10;
            }
            else
            {
                digit >>= 1;
                rem = 0;
            }
            num[i] = digit + '0';
        }
        rem = 0;
    }
    // delete '0' form beggining of number.
    it = 0;
    for (int i = 0; i < len * 4; i++)
    {
        if (result[i] - '0') 
        {
            it = i;
            break;
        }
    }
    for (int i = it; i < len * 4 + 1; i++)
    {
        result[i - it] = result[i];
    }
    result = (char *)realloc(result, len * 4 - it + 1);
    result[len * 4 - it] = '\0';

    return result;
}


/*  Auxiliary functions  */

big_int *big_int_assign(const big_int *n)
{
    big_int *result = malloc(sizeof(big_int));
    result->length = n->length;
    result->sign = n->sign;
    result->number = malloc(result->length);
    result->number = memcpy(result->number, n->number, result->length);
    return result;
}

void big_int_free(big_int *n)
{
    free(n->number);
    free(n);
}


/* Getters */

big_int *get_big_int(const char *bin_num, unsigned char sign)
{
    char *bin_number = clean_zeros(bin_num);
    int len = strlen(bin_number);

    big_int *ans = malloc(sizeof(big_int));
    ans->sign = sign;
    ans->length = (len & 7) ? (len >> 3) + 1 : len >> 3;

    ans->number = malloc(ans->length);
    for (int i = 0; i < ans->length; i++)
        ans->number[i] = 0;
    size_t ind = 0;
    unsigned char power2 = 1;
    for (int i = len - 1; i >= 0; i--)
    {

        if (bin_number[i] == '1')
            ans->number[ans->length - ind - 1] += power2;
        power2 <<= 1;
        if (((len - i - 1) & 7) == 7)
        {
            ind++;
            power2 = 1;
        }
    }
    return ans;
}

big_int *get_big_int_10(const char *decimal, unsigned char sign)
{
    return get_big_int(from_10_to_2(decimal), sign);
}

char *big_int_get_bin(const big_int *n)
{
    short flag = 0;
    char *result = malloc(n->length * 8 + 1);
    for (int i = 0; i < n->length * 8 + 1; i++)
    {
        result[i] = '0';
    }
    int ind = 0;
    for (int i = 0; i < n->length; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if ((n->number[i] & (1 << j)) && (!flag))
            {
                flag = 1;
                ind = j;
            }
            if (flag) 
            {
                result[i * 8 + ind - j] = n->number[i] & (1 << j) ? '1' : '0';
            }
        }
    }
    result = realloc(result, n->length * 8 - (7 - ind) + 1);
    result[n->length * 8 - (7 - ind)] = '\0';
    return result;
}

char *big_int_get_decimal(const big_int *n)
{
    char *result = big_int_get_bin(n);
    result = from_2_to_10(result);
    return result;
}


/* Comparison */

short big_int_is_greater_or_equal(const big_int *n1, const big_int *n2)
{
    if (n1->length > n2->length) return 1;
    if (n1->length < n2->length) return 0;
    for (int i = 0; i < n1->length; i++)
    {
        if (n1->number[i] < n2->number[i]) return 0;
        if (n1->number[i] > n2->number[i]) return 1;
    }
    return 1;
}

short big_int_is_greater(const big_int *n1, const big_int *n2)
{
    if (n1->length > n2->length) return 1;
    if (n1->length < n2->length) return 0;
    for (int i = 0; i < n1->length; i++)
    {
        if (n1->number[i] < n2->number[i]) return 0;
        if (n1->number[i] > n2->number[i]) return 1;
    }
    return 0;
}

short big_int_is_equal(const big_int *n1, const big_int *n2)
{
    if (n1->length != n2->length) return 0;
    for (int i = 0; i < n1->length; i++)
        if (n1->number[i] != n2->number[i]) return 0;
    return 1;
}

short big_int_is_zero(const big_int *n)
{
    if ((n->length == 1) && (!n->number[0]))
        return 1;
    return 0;
}


/*  Arithmetic operations  */

// n1 - n2; n1, n2 >= 0;
// if n2 > n1 returns 0;
big_int *big_int_sub_positive(const big_int *n1, const big_int *n2)
{
    if (n1->length < n2->length) return 0;
    if (big_int_is_equal(n1, n2))
        return get_big_int("0", 1);

    big_int *result = malloc(sizeof(big_int));
    result->length = n1->length;
    result->sign = 1;
    result->number = calloc(n1->length, sizeof(char));
    int diff = n1->length - n2->length;
    int ind = 0; // index of last non 0 byte.
    short temp;

    for (int i = 0; i < n1->length; i++)
    {
        if (i < diff)
        {
            result->number[i] = n1->number[i];
            if (n1->number[i]) 
                ind = i;
            continue;
        }
        if (n1->number[i] >= n2->number[i-diff])
        {
            result->number[i] = n1->number[i] - n2->number[i-diff];
            if (result->number[i]) ind = i; 
        }
        else
        {
            if (result->number[ind] == 0) return 0;
            for (int j = ind + 1; j < i; j++)            
                result->number[j] = BASE - 1;
            temp = n1->number[i] + BASE;
            result->number[ind]--;
            result->number[i] = temp - n2->number[i-diff];
            ind = i;
        }
    }

    for (int i = 0; i < result->length; i++)
    {
        if ((result->number[i] != 0) && (i != 0))
        {
            for (int j = i; j < result->length; j++)
                result->number[j - i] = result->number[j];
            result->length -= i;
            result->number = realloc(result->number, result->length);
            break;
        }
        if ((result->number[i] != 0) && (i == 0)) break;
    }
    return result;
}

big_int *big_int_add(const big_int *n1, const big_int *n2)
{
    if (n1->sign && !n2->sign)
    {
        if (big_int_is_greater_or_equal(n1, n2))
            return big_int_sub_positive(n1, n2);
        else
            return big_int_sub_positive(n2, n1);
    }
    if (!n1->sign && n2->sign)
    {
        if (big_int_is_greater_or_equal(n2, n1))
            return big_int_sub_positive(n2, n1);
        else
            return big_int_sub_positive(n1, n2);
    }

    big_int *result = malloc(sizeof(big_int));
    int temp = 0;
    int carry = 0;
    result->length = n1->length > n2->length ? n1->length : n2->length;
    result->number = malloc(result->length);
    result->sign = 1;
    for (int i = 1; i <= result->length; i++)
    {
        if ( ((int)n1->length - i + 1 > 0) && ((int)n2->length - i + 1 > 0) )
        {
            temp = n1->number[n1->length - i] + n2->number[n2->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        else if ((int)n1->length - i + 1 > 0)
        {
            temp = n1->number[n1->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        else if ((int)n2->length - i + 1 > 0)
        {
            temp = n2->number[n2->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
    }
    if (carry)
    {
        result->length++;
        result->number = (unsigned char*) realloc(result->number, result->length);
        for (int it = result->length - 1; it > 0; it--)
        {
            result->number[it] = result->number[it - 1];
        }
        result->number[0] = 1;
    }

    if (!(n1->sign || n2->sign)) result->sign = 0;
    return result;
}

big_int *big_int_add_f(big_int *n1, big_int *n2)
{
    if (n1->sign && !n2->sign)
    {
        if (big_int_is_greater_or_equal(n1, n2))
        {
            big_int* temp = big_int_sub_positive(n1, n2);
            free(n1);
            free(n2);
            return temp;
        }
        else
        {
            big_int* temp = big_int_sub_positive(n2, n1);
            free(n1);
            free(n2);
            return temp;
        }
    }
    if (!n1->sign && n2->sign)
    {
        if (big_int_is_greater_or_equal(n2, n1))
        {
            big_int* temp = big_int_sub_positive(n2, n1);
            big_int_free(n1);
            big_int_free(n2);
            return temp;
        } 
        else
        {
            big_int* temp = big_int_sub_positive(n1, n2);
            big_int_free(n1);
            big_int_free(n2);
            return temp;
        } 
    }

    big_int *result = malloc(sizeof(big_int));
    int temp = 0;
    int carry = 0;
    result->length = n1->length > n2->length ? n1->length : n2->length;
    result->number = malloc(result->length);
    result->sign = 1;
    for (int i = 1; i <= result->length; i++)
    {
        if ( ((int)n1->length - i + 1 > 0) && ((int)n2->length - i + 1 > 0) )
        {
            temp = n1->number[n1->length - i] + n2->number[n2->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        else if ((int)n1->length - i + 1 > 0)
        {
            temp = n1->number[n1->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        else if ((int)n2->length - i + 1 > 0)
        {
            temp = n2->number[n2->length - i] + carry;
            result->number[result->length - i] = temp & (BASE - 1);
            carry = temp >> 8;
        }
    }
    if (carry)
    {
        result->length++;
        result->number = (unsigned char*) realloc(result->number, result->length);
        for (int it = result->length - 1; it > 0; it--)
        {
            result->number[it] = result->number[it - 1];
        }
        result->number[0] = 1;
    }

    if (!(n1->sign || n2->sign)) result->sign = 0;
    big_int_free(n1);
    big_int_free(n2);
    return result;
}

big_int *big_int_sub(const big_int *n1, const big_int *n2)
{
    big_int *temp = big_int_assign(n2); 
    temp->sign = 1 - temp->sign;
    big_int *res = big_int_add(n1, temp);
    big_int_free(temp);
    return res;
}

void left_shift(big_int *x, int value)
{
    if (value <= 0) return;
    x->length += value;
    x->number = realloc(x->number, x->length);
    for (int i = x->length - value; i < x->length; i++)
        x->number[i] = 0;
}

void right_shift_2(big_int *x)
{
    short d = 0;
    if (!(x->number[0] >> 1)) d = 1;
    short rem = 0;
    for (int i = 0; i < x->length - d; i++)
    {
        if (rem)
        {
            rem = x->number[i + d] & 1;
            x->number[i] = (x->number[i + d] >> 1) + (BASE >> 1);
        }
        else
        {
            rem = x->number[i + d] & 1;
            x->number[i] = x->number[i + d] >> 1;
        }
    }
    if (d)
    {
        x->length--;
        x->number = realloc(x->number, x->length);
    }
    return;
}

void left_shift_2(big_int *x)
{
    int carry = 0;
    int temp = 0;
    for (int i = x->length - 1; i >= 0; i--)
    {
        x->number[i] = (x->number[i] + carry) << 1;
        carry = x->number[i] >> 8;
    }
    if (carry)
    {
        x->length++;
        x->number = realloc(x->number, x->length);
        for (int i = x->length - 1; i >= 1; i--)
        {
            x->number[i] = x->number[i - 1];
        }
        x->number[0] = 1;
    }
    return;
}

big_int *big_int_multiply(const big_int *n1, const big_int *n2)
{
    if ( big_int_is_zero(n1) || big_int_is_zero(n2) )
        return get_big_int("0", 1); 

    big_int *result = malloc(sizeof(big_int));
    result->length = (n1->length + n2->length - 1);
    result->number = calloc(result->length, sizeof(char));

    int carry = 0;
    int temp = 0;

    for (int i = n2->length - 1; i >= 0; i--)
    {
        int j = n1->length - 1;
        for ( ; j >= 0; j--)
        {
            temp = n1->number[j] * n2->number[i] + carry + result->number[i + j];
            result->number[i + j] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        if (carry)
        {   
            if (i + j >= 0)
            {
                result->number[i + j] += carry;
                carry = 0;
            }
        }
    }

    if (carry)
    {
        result->length ++;
        result->number = realloc(result->number, result->length);
        for (long i = result->length - 2; i >= 0; i--)
            result->number[i + 1] = result->number[i];
        result->number[0] = carry;
    }

    if ((n1->sign + n2->sign) == 1) result->sign = 0;
    else result->sign = 1;

    return result;
}

big_int *big_int_multiply_f(big_int *n1, big_int *n2)
{
    if ( big_int_is_zero(n1) || big_int_is_zero(n2) )
    {
        big_int_free(n1);
        big_int_free(n2);
        return get_big_int("0", 1); 
    }

    big_int *result = malloc(sizeof(big_int));
    result->length = (n1->length + n2->length - 1);
    result->number = calloc(result->length, sizeof(char));

    int carry = 0;
    int temp = 0;

    for (int i = n2->length - 1; i >= 0; i--)
    {
        int j = n1->length - 1;
        for ( ; j >= 0; j--)
        {
            temp = n1->number[j] * n2->number[i] + carry + result->number[i + j];
            result->number[i + j] = temp & (BASE - 1);
            carry = temp >> 8;
        }
        if (carry)
        {   
            if (i + j >= 0)
            {
                result->number[i + j] += carry;
                carry = 0;
            }
        }
    }

    if (carry)
    {
        result->length ++;
        result->number = realloc(result->number, result->length);
        for (long i = result->length - 2; i >= 0; i--)
            result->number[i + 1] = result->number[i];
        result->number[0] = carry;
    }

    if ((n1->sign + n2->sign) == 1) result->sign = 0;
    else result->sign = 1;

    big_int_free(n1);
    big_int_free(n2);

    return result;
}

big_int *big_int_pow(const big_int *n, int r)
{
    if (r < 0) return get_big_int("0", 1);
    big_int *result = get_big_int("1", 1);
    big_int *p2 = big_int_assign(n);
    clock_t time1, time2;
    while (r)
    {
        if (r & 1) result = big_int_multiply(result, p2);
        time1 = clock();
        p2 = big_int_multiply(p2, big_int_assign(p2));
        time2 = clock();
        printf("%d -> %ld\n", r, time2 - time1);
        r >>= 1;
    }
    return result;
}

big_int *big_int_mod(const big_int *divident, const big_int *modul)
{
    if (big_int_is_equal(divident, modul))
        return get_big_int("0", 1);

    big_int *n = big_int_assign(divident);
    if (big_int_is_greater(modul, n))
        return n;

    big_int *temp;
    big_int *subt;
    big_int *subt2;
    int diff;
    while (big_int_is_greater_or_equal(n, modul))
    {
        subt = big_int_assign(modul);
        diff = n->length - modul->length;
        if (n->number[0] > modul->number[0])
            left_shift(subt, diff);
        else
            left_shift(subt, diff - 1);
        subt2 = big_int_assign(subt);
        while (big_int_is_greater_or_equal(n, subt))
        {
            temp = subt;
            subt = big_int_add(subt, subt2);
            big_int_free(temp);
        }
        temp = subt;
        subt = big_int_sub_positive(subt, subt2);
        big_int_free(temp);
        big_int_free(subt2);
        temp = n;
        n = big_int_sub_positive(n, subt);
        big_int_free(temp);
        big_int_free(subt);
    }
    return n;
}

big_int *big_int_mod_pow(const big_int *n, const big_int *y, const big_int *m)
{
    big_int *ans = get_big_int("1", 1);
    big_int *temp;
    big_int *x = big_int_assign(n);
    unsigned char mask = 1;
    for (int i = y->length - 1; i >= 0; i--)
    {
        for (mask = 1; mask; mask <<= 1)
        {
            if (y->number[i] & mask)
            {
                temp = ans;
                ans = big_int_multiply(ans, x);
                big_int_free(temp);
                temp = ans;
                ans = big_int_mod(ans, m);
                big_int_free(temp);
            }
            //mask <<= 1;
            temp = x;
            x = big_int_multiply(x, x);
            big_int_free(temp);
            temp = x;
            x = big_int_mod(x, m);
            big_int_free(temp);
        }
    }
    return ans;
}

void big_int_reminder_division(const big_int *divident, const big_int *divisor, big_int *(*result))
{
    if (big_int_is_equal(divident, divisor))
    {
        result[0] = get_big_int_10("1", 1);
        result[1] = get_big_int_10("0", 1);
    }
        
    big_int *n = big_int_assign(divident);
    if (big_int_is_greater(divisor, n))
    {
        result[0] = get_big_int_10("0", 1);
        result[1] = n;
    }

    big_int *quotient = get_big_int_10("0", 1);
    int qDigit = 0;
    big_int *temp;
    big_int *temp2;
    big_int *subt;
    big_int *subt2;
    int diff;
    while (big_int_is_greater_or_equal(n, divisor))
    {
        subt = big_int_assign(divisor);
        diff = n->length - divisor->length;
        temp2 = get_big_int_10("1", 1);
        if (n->number[0] > divisor->number[0])
        {
            left_shift(subt, diff);
            left_shift(temp2, diff);
            qDigit = n->number[0] / divisor->number[0];
        }
        else
        {
            left_shift(subt, diff - 1);
            left_shift(temp2, diff - 1);
            qDigit = (n->number[0] * BASE + n->number[1]) / divisor->number[0];
        }
        subt2 = big_int_assign(subt);
        big_int *qDigitBig = get_big_int_10("1", 1);
        qDigitBig->number[0] = qDigit;
        temp = subt;
        subt = big_int_multiply(subt, qDigitBig);
        big_int_free(temp);
        while (big_int_is_greater(subt, n))
        {
            temp = subt;
            subt = big_int_sub_positive(subt, subt2);
            big_int_free(temp);
            --qDigit;
        }
        big_int_free(subt2);

        temp = quotient;
        temp2->number[0] = qDigit;
        quotient = big_int_add(quotient, temp2);
        big_int_free(temp);
        big_int_free(temp2);
        qDigit = 0;

        temp = n;
        n = big_int_sub_positive(n, subt);
        big_int_free(temp);
        big_int_free(subt);
    }
    result[0] = quotient;
    result[1] = n;
}


/*  MATRIX AND OPERATIONS  */

void print_matrix_2x2(big_int **matrix);

void print_big_int_10(const big_int *n);

big_int **big_int_create_matrix_2x2(int *k)
{
    big_int **matrix = (big_int **)malloc(4 * sizeof(big_int *));
    for (int i = 0; i < 4; i++)
    {
        matrix[i] = get_big_int_10("1", 1);
        matrix[i]->number[0] = (unsigned char)k[i];
    }
    return matrix;
}

big_int **big_int_multiply_matrix(big_int * const *matrix1, big_int * const *matrix2)
{
    big_int **matrixTemp = malloc(4 * sizeof(big_int *));
    big_int *temp;
    matrixTemp[0] = big_int_add_f(big_int_multiply(matrix1[0], matrix2[0]), big_int_multiply(matrix1[1], matrix2[2]));
    matrixTemp[1] = big_int_add_f(big_int_multiply(matrix1[0], matrix2[1]), big_int_multiply(matrix1[1], matrix2[3]));
    matrixTemp[2] = big_int_add_f(big_int_multiply(matrix1[2], matrix2[0]), big_int_multiply(matrix1[3], matrix2[2]));
    matrixTemp[3] = big_int_add_f(big_int_multiply(matrix1[2], matrix2[1]), big_int_multiply(matrix1[3], matrix2[3]));
    return matrixTemp;
}

void **big_int_matrix_free(big_int **m)
{
    for (int i = 0; i < 4; i++)
        big_int_free(m[i]);
    free(m);
}

void big_int_euclid_extended(const big_int* a_in, const big_int* b_in, big_int* *x, big_int* *y)
{
    big_int *a = big_int_assign(a_in);
    big_int *b = big_int_assign(b_in);

    int k1[] = {1, 0, 0, 1};
    int k2[] = {0, 1, 1, 0};
    big_int **matrix_a = big_int_create_matrix_2x2(k1);
    big_int **matrix_b = big_int_create_matrix_2x2(k2);
    big_int *rem_div[2];
    big_int **bin;
    int i = 1;

    while (!big_int_is_zero(a) && !big_int_is_zero(b))
    {
        if (big_int_is_greater(a, b))
        {
            big_int_reminder_division(a, b, rem_div);
            big_int_free(matrix_b[0]);
            matrix_b[0] = big_int_assign(rem_div[0]);
            big_int_free(a);
            a = big_int_assign(rem_div[1]);
        }
        else
        {
            big_int_reminder_division(b, a, rem_div);
            big_int_free(matrix_b[0]);
            matrix_b[0] = big_int_assign(rem_div[0]);
            big_int_free(b);
            b = big_int_assign(rem_div[1]);
        }

        print_big_int_10(a);
        print_big_int_10(b);
        printf("%s", "___\n");

        bin = matrix_a;
        matrix_a = big_int_multiply_matrix(matrix_a, matrix_b);
        big_int_matrix_free(bin);

        print_matrix_2x2(matrix_a);
        print_matrix_2x2(matrix_b);
        printf("%s", "____===\n");

        i = 1 - i;
    }
    if (big_int_is_greater_or_equal(a_in, b_in))
    {
        *x = big_int_assign(matrix_a[3]);
        *y = big_int_assign(matrix_a[1]);
        (*y)->sign ^= i;
        (*x)->sign ^= 1 - i;
    }
    else
    {
        *x = big_int_assign(matrix_a[1]);
        *y = big_int_assign(matrix_a[3]);
        (*y)->sign ^= 1 - i;
        (*x)->sign ^= i;
    }

    big_int_matrix_free(matrix_a);
    big_int_matrix_free(matrix_b);
    
    return;
}

/*  Output block functions  */

void print_big_int_2(const big_int *n)
{
    short flag = 0;
    for (int i = 0; i < n->length; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (n->number[i] & (1 << j)) flag = 1;
            if (flag) printf("%d", n->number[i] & (1 << j) ? 1 : 0);
        }
    }
    printf("\n");
}

void print_big_int_10(const big_int *n)
{
    char *result = big_int_get_decimal(n);
    if (!n->sign) printf("%c", '-');
    for (int i = 0; i < strlen(result); i++) 
        printf("%c", result[i]);
    free(result);
    printf("\n");
}

void print_matrix_2x2(big_int **matrix)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%d)", i);
        print_big_int_10(matrix[i]);
    }
}

/*  Testing block functions  */

void test_10()
{
    big_int *n1 = get_big_int("101010101010101010101010", 1);
    big_int *n2 = get_big_int("10101010101010101010111", 1);

    big_int *res = big_int_add(n1, n2);
    // print_big_int_10(n1);
    // print_big_int_10(n2);
    // print_big_int_10(res);
    print_big_int_2(res);

    n1 = get_big_int_10("10345", 1);
    n2 = get_big_int_10("10345", 1);

    res = big_int_sub_positive(n1, n2);
    print_big_int_2(res);
    if (res) printf("%d %d", res->number[0], res->length);

    big_int_free(n1);
    big_int_free(n2);
}

void test_multiply()
{
    big_int *n1 = get_big_int_10("10000000000000000001", 1);
    big_int *n2 = get_big_int_10("10000000000000", 1);
    big_int *res = big_int_multiply(n1, n2);
    print_big_int_10(res);
}

void test_pow()
{
    big_int *n = get_big_int_10("3", 1);
    int r = 5000;
    clock_t time1, time2;
    time1 = clock();
    n = big_int_pow(n, r);
    time2 = clock();
    printf("total -> %ld\n", time2 - time1);
    print_big_int_10(n);
    print_big_int_10(big_int_mod(n, get_big_int_10("1000000000", 1)));
}

void test()
{
    int a = 10000;
    printf("%d\n%d\n", a & 255, 39 * 256 + 16);
    unsigned char *m = malloc(2);
    m[0] = 0; 
    m[1] = 0;
    m[1] = a & 255;
    printf("%d\n", m[1]);

}

void test_assign()
{
    big_int *n1 = get_big_int("1", 1);
    big_int *n2 = big_int_assign(n1);
    print_big_int_10(n1);
    printf("\n");
    print_big_int_10(n2);
}

void test_mod()
{
    big_int *n1 = get_big_int_10("715379531346476456454434646546465423145411111111111111111111111111111111111333333333333333333377777777777777777777773333333333333333333333333777777777777777777777773333", 1);
    big_int *mod = get_big_int_10("1000000000000000000000000", 1);
    mod = get_big_int_10("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 1);
    //n1 = get_big_int_10("71117", 1);
    //mod = get_big_int_10("1000", 1);
    printf("%d %d\n", n1->number[0], mod->number[0]);
    printf("%d %d\n" ,n1->length, mod->length);
    big_int *res = big_int_mod(n1, mod);
    //mod = get_big_int_10("999999999999999999999999999999999999999999999999999999999999999999999999999", 1);
    //res = big_int_sub(n1, mod);
    print_big_int_10(res);
}

void test_rshift()
{
    big_int *n1 = get_big_int_10("0", 1);
    right_shift_2(n1);
    print_big_int_10(n1);
}

void test_mod_pow()
{
    // big_int *x = get_big_int_10("3", 1);
    // big_int *y = get_big_int_10("5000", 1);
    // big_int *m = get_big_int_10("1000000000", 1);
    // x = get_big_int_10("65614564543443", 1);
    // y = get_big_int_10("8767687235467867621377", 1);
    // m = get_big_int_10("319797212497321917", 1);
    big_int *x = get_big_int_10("5", 1);
    big_int *y = get_big_int_10("32416188697", 1);
    big_int *m = get_big_int_10("32416188697", 1);
    
    big_int *res = big_int_mod_pow(x, y, m);
    print_big_int_10(res);
}

void test_reminder_division()
{
    //big_int *divident = get_big_int_10("1456561514575545365217216154162387163214287671216235163821677193278192371324132618391", 1);
    big_int *ans[2];
    // big_int *x = get_big_int_10("97654321462381623183", 1);
    // big_int *sq_x = big_int_multiply(x,x);
    // big_int_reminder_division(sq_x, x, ans);
    // big_int_free(x);
    // print_big_int_10(ans[0]);
    // print_big_int_10(ans[1]);

    //big_int *divisor = get_big_int_10("97654321462381623183", 1);
    
    big_int *x = get_big_int("111111111111111111111", 1);
    big_int *y = get_big_int("1111111", 1);
    big_int_reminder_division(x, y, ans);
    print_big_int_2(ans[0]);
    print_big_int_10(ans[1]);

}

void test_lshift_2()
{
    big_int *x = get_big_int("1000100100", 1);
    left_shift_2(x);
    print_big_int_2(x);
}

void matrix_test()
{
    // const big_int **matrix1 = malloc(4);
    // for (int i = 0; i < 4; i++)
    //     matrix1[i] = get_big_int_10("1", 1);
    int k1[4] = {12, 3, 5, 9};
    int k2[4] = {1, 0, 0, 1};
    big_int **matrix1 = big_int_create_matrix_2x2(k1);
    big_int **matrix2 = big_int_create_matrix_2x2(k2);
    big_int **matrixRes = big_int_multiply_matrix(matrix1, matrix2);
    print_matrix_2x2(matrixRes);
}

void euclid_test()
{
    big_int *x;
    big_int *y;
    big_int *a = get_big_int_10("1215447", 1);
    big_int *b = get_big_int_10("17267674", 1);
    big_int_euclid_extended(a, b, &x, &y);
    printf("ans:");
    print_big_int_10(x);
    print_big_int_10(y);
}

// int main()
// {
//     //test();
//     //test_10();
//     //test_add_bin();
//     //test_multiply();
//     //test_pow();
//     //test_assign();
//     //test_mod();
//     //test_rshift();
//     //test_mod_pow();
//     //test_reminder_division();
//     //test_lshift_2();
//     //matrix_test();
//     euclid_test();

//     return 0;
// }