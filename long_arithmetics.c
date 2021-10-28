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

int main()
{
    big_int *a = get_big_int("001100011000000110000001");
    printf("%d\n", a->number[0]);
    print_big_int(a);
    return 0;
}