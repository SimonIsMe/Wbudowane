#include <stdio.h>
#include <inttypes.h>

int main(void)
{
	//	zakres [a, b]
	uint32_t a = 3;
	uint32_t b = 123;

	//uint32_t maska = 1431655765;	//	dla parzystych
	uint32_t maska = 2863311530;	//	dla nieparzystych
	uint32_t bufforMaski;

	a--;
	while (++a <= b) if ((maska | a) == maska) printf("%d\n", a);

    return 0;
}
