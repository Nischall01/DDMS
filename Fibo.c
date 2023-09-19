#include <stdio.h>

int main()
{
    int n, i, first = 0, second = 1, next, sum = 0;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    printf("Fibonacci Series: ");
    for (i = 0; i < n; i++)
    {
        if (i <= 1)
        {
            next = i;
            sum = i;
        }
        else
        {
            next = first + second;
            first = second;
            second = next;
            sum += next;
        }
        printf("%d ", next);
    }
    printf("\nSum = %d", sum);
    return 0;
}