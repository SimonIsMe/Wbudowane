#include <stdio.h>
#include <string.h>

/* Note: assumes that str is proper
   C, null-terminated string. */
void movespaces(char* str, size_t len)
{
    int spaces = 0;
    char* p = str + len;

    while (p >= str) {
        if (*p == 0x20) ++spaces;
        else if (spaces > 0) p[spaces] = *p;
        --p;
    }

    p = str;
    while (p != str + spaces) *p++ = 0x20;
}

int main(void)
{
    char str[] = "  Ala ma  kota. ";
    movespaces(str, strlen(str));
    printf("%s\n", str);
    return 0;
}
