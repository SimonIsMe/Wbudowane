#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

uint32_t pierwszySposob(uint32_t wartosc)
{
    //	Dzielę 32 bitową liczbę na dwie 16 bitowe części, które zamieniam
    //	ze sobą miejscami
    //	itd...
    wartosc = (wartosc & 0b11111111111111110000000000000000) >> 16 | (wartosc & 0b00000000000000001111111111111111) << 16;
    wartosc = (wartosc & 0b11111111000000001111111100000000) >> 8 | (wartosc & 0b00000000111111110000000011111111) << 8;
    wartosc = (wartosc & 0b11110000111100001111000011110000) >> 4 | (wartosc & 0b00001111000011110000111100001111) << 4;
    wartosc = (wartosc & 0b11001100110011001100110011001100) >> 2 | (wartosc & 0b00110011001100110011001100110011) << 2;
    wartosc = (wartosc & 0b10101010101010101010101010101010) >> 1 | (wartosc & 0b01010101010101010101010101010101) << 1;

	return wartosc;
}


uint32_t drugiSposob(uint32_t wartosc)
{
	uint32_t buffor;
	uint32_t potega;
	uint32_t odwroconaWartosc = 0;
	short przesuniecie = 7;
	short i;
	
	for (i = 32; i >= 0; i--) {
		potega = pow(2, i);
		buffor = wartosc;
		
		buffor = buffor & potega;
		
		if (i <= 15) {
			buffor = buffor << przesuniecie;
			przesuniecie += 2;
		} else {
			buffor = buffor >> przesuniecie;
			przesuniecie -= 2;
		}
		
		if (przesuniecie >= 0) {
			przesuniecie = 1;
		}
		
		odwroconaWartosc = odwroconaWartosc | buffor;
	}
	return odwroconaWartosc;
}

uint32_t trzeciSposob(uint32_t num)
{
    uint32_t count = sizeof(num) * 32 - 1;
    uint32_t reverse_num = num;

    num >>= 1;
    while(num)
    {
       reverse_num <<= 1;
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}

int main(void)
{
	uint32_t wartosc = 2;

    printf("Liczba: %d\n", wartosc);

    printf("%d\n", pierwszySposob(wartosc));
    printf("%d\n", drugiSposob(wartosc));
    printf("%d\n", trzeciSposob(wartosc));

    return 0;
}
