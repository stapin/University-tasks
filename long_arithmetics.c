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

void print_big_int(const big_int *n)
{
    for (int i = n->length - 1; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            printf("%d", n->number[i] & (1 << j) ? 1 : 0);
        }
        printf("\n");
    }
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

char *big_int_print_10()
{

}

int main()
{
    big_int *a = get_big_int("001100011000000110000001");
    print_big_int2(a);
    big_int *n1 = get_big_int("1000001");
    big_int *n2 = get_big_int("1100001");
    //big_int *n3 = big_int_add(n1, n2);
    //printf("\n");
    //print_big_int2(n3);
    printf("\n");
    big_int *n4 = big_int_sub(n1, n2);
    //printf("%d %d", n4->length, sizeof(n4->number));
    print_big_int2(n4);
    return 0;
}