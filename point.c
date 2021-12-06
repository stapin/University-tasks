#include "stdio.h"
#include "stdlib.h"

int main()
{
    int a[1] = {0};
    int *b = calloc(sizeof(int), 4);
    //b = a;
    printf("%d %d\n", sizeof(a), sizeof(b));
    printf("%p %p\n", a, b);
    //printf("%ld %ld", )
    char k = 100;
    char m = 100;
    char ans = -128;
    printf("%d\n", (char)128 == (char)-128);
    printf("%d\n", (char)255);
    return 0;
}