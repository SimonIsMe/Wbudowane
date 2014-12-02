#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

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

//	odwracanie działa tylko dla 8 bitów
uint8_t reverseBits(uint8_t b)
{
	return ((b * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}

/**
 * https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
 * */
uint32_t drugiSposob(uint32_t toReverse)
{
	uint32_t inByte0 = (toReverse & 0xFF);
	uint32_t inByte1 = (toReverse & 0xFF00) >> 8;
	uint32_t inByte2 = (toReverse & 0xFF0000) >> 16;
	uint32_t inByte3 = (toReverse & 0xFF000000) >> 24;
	return (reverseBits(inByte0) << 24) | (reverseBits(inByte1) << 16) | (reverseBits(inByte2) << 8) | (reverseBits(inByte3));
}

uint32_t trzeciSposob(uint32_t wartosc)
{
    uint32_t count = sizeof(wartosc) * 32 - 1;
    uint32_t odwroconaWartosc = wartosc;

    wartosc >>= 1;
    while(wartosc)
    {
       odwroconaWartosc = odwroconaWartosc << 1;
       odwroconaWartosc = odwroconaWartosc | (wartosc & 1);
       wartosc = wartosc >> 1;
       count--;
    }
    odwroconaWartosc = odwroconaWartosc << count;
    return odwroconaWartosc;
}

int main(void)
{
	uint32_t wartosc = 1231231212;

    printf("Liczba: %d\n", wartosc);

	int iteracji = 50000000;
	double elapsed; // in milliseconds
	clock_t start, end;
	start = clock();
	for (int i = 0; i < iteracji; i++) {
		pierwszySposob(wartosc);
	}
	end = clock();
	elapsed = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("1. sposób potrzebowal %f ms dla %d iteracji.\n", elapsed, iteracji);
	
	//##############################################
	
	start = clock();
	for (int i = 0; i < iteracji; i++) {
		drugiSposob(wartosc);
	}
	end = clock();
	elapsed = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("2. sposób potrzebowal %f ms dla %d iteracji.\n", elapsed, iteracji);
	
	//##############################################
	
	start = clock();
	for (int i = 0; i < iteracji; i++) {
		trzeciSposob(wartosc);
	}
	end = clock();
	elapsed = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("3. sposób potrzebowal %f ms dla %d iteracji.\n", elapsed, iteracji);
	
	
    printf("%d\n", pierwszySposob(wartosc));
    printf("%d\n", drugiSposob(wartosc));
    printf("%d\n", trzeciSposob(wartosc));

    return 0;
}
