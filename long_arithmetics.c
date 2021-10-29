#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct big_int
{
    unsigned int length;
    unsigned char *number;

} big_int;

big_int *get_big_int(const char *bin_number)
{
    size_t len = strlen(bin_number);
    big_int *ans = malloc(sizeof(big_int));
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


void print_big_int2(const big_int *n)
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
}


big_int *big_int_add(big_int *n1, big_int *n2)
{
    big_int *result = malloc(sizeof(big_int));
    int temp = 0;
    int rem = 0;
    // realloc
    result->length = n1->length > n2->length ? n1->length : n2->length;
    result->number = malloc(result->length);
    for (int i = 1; i <= result->length; i++)
    {
        if ((n1->length - i + 1) && (n2->length - i + 1))
        {
            temp = n1->number[n1->length - i] + n2->number[n2->length - i] + rem;
            result->number[result->length - i] = temp & 255;
            rem = temp << 8;
        }
        else if (n1->length - i - 1)
        {
            result->number[result->length - i] = n1->number[n1->length - i] + rem;
            rem = 0;
        }
        else if (n2->length - i - 1)
        {
            result->number[result->length - i] = n2->number[n2->length - i] + rem;
            rem = 0;
        }
        else if (rem)
        {
            result->length++;
            result->number = (unsigned char*) realloc(result->number, result->length);
            for (int it = 1; it < result->length; it++)
            {
                result->number[it] = result->number[it - 1];
            }
            result->number[0] = rem;
        }
    }
    return result;
}

// n1 - n2; n1, n2 >= 0;
// if n2 > n1 returns 0;
big_int *big_int_sub(big_int *n1, big_int *n2)
{
    if (n1->length < n2->length) return 0;
    int diff = n1->length - n2->length;
    big_int *result = malloc(sizeof(big_int));
    result->length = n1->length;
    result->number = malloc(n1->length);
    for (int i = 0; i < result->length; i++) result->number[i] = 0;
    int ind = 0;
    for (int i = 0; i < n1->length; i++)
    {
        if (i < diff)
        {
            result->number[i] = n1->number[i];
            if (n1->number[i])
            {
                ind = i;
            }
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
            short temp = n1->number[i] + 256;
            result->number[ind]--;
            result->number[i] = temp - n2->number[i-diff];
            ind = i;
        }
    }
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
    unsigned char flag = 0;
    while (1)
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
        if (!flag) break;
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

big_int *get_big_int_10(const char *decimal)
{
    return get_big_int(from_10_to_2(decimal));
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
        //printf("%c%c\n", power_2[len-2], power_2[len-1]);
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



int main()
{
    big_int *a = get_big_int("001100011000000110000001");
    big_int *n1 = get_big_int("1100001");
    big_int *n2 = get_big_int("1000001");

    big_int *n3 = get_big_int_10("1000000000000000000008");
    print_big_int2(n3);

    char n10[] = "000001";
    char *new2 = from_2_to_10(from_10_to_2(n10));
    //printf("->%d\n", sizeof(new2));
    for (int i = 0; i < strlen(new2); i++) printf("%c", new2[i]);
    return 0;
}