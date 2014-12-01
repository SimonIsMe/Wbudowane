#include <stdio.h>
#include <stdint.h>

int main(void)
{
	//	zakres [a, b]
	unsigned int a = 3;
	unsigned int b = 15;
	
	a--;

	//unsigned int maska = 0b01010101010101010101010101010101;	//	dla parzystych
	unsigned int maska = 0b10101010101010101010101010101010;	//	dla nieparzystych
	unsigned int bufforMaski;

	while (++a <= b) {
		bufforMaski = maska;
		bufforMaski |= a;
		if (bufforMaski == maska) printf("%d\n", a);
	}

    return 0;
}
