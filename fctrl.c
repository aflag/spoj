#include <stdio.h>

int factors(int fac, int n)
{
    int factors = 0;
    while (n >= fac) {
        n /= fac;
        factors += n;
    }
    return factors;
}

int Z(int n)
{
    return factors(5, n);
}

int main(void)
{
    int T, i;
    scanf("%d", &T);
    for (i = 0; i < T; ++i) {
        int n;
        scanf("%d", &n);
        printf("%d\n", Z(n));
    }
    return 0;
}
