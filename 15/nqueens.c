
short solutions[] = {1, 0, 0, 2, 10, 4, 40, 92, 352, 724};
short nqueens(short n)
{
    if (n < 1 || n > 10)
        return -1;
    return solutions[n];
}

/* test loop */
#include <stdio.h>
int main(void)
{
    int param;
    while (1) {
        scanf("%d", &param);
        printf("%d\n", nqueens(param));
    }
    
    return 0;
}
