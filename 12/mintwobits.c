/* C99 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/* Use as boolean (non-zero if
   x is a power of 2 or x = 0). */
#define power2(x) (!(x & (x - 1)))

int main(void) 
{
    uint32_t num;
    while (scanf("%"SCNu32, &num) == 1)
        if (!power2(num)) printf("%"PRIu32"\n", num);
    return 0;
}