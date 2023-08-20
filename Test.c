#include <stdio.h>

int main()
{
    int a = 5;
    int b = 7;
    int *p;
    p = &a;
    printf("%d\n", *p);
    p = &b;
    printf("%d\n", *p);
}
