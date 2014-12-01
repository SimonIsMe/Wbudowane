/* C99 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

unsigned int pierwszySposob(unsigned int wartosc) 
{
	
	//	4294901760 = 1111 1111 1111 1111 0000 0000 0000 0000	<=	2 części po 16 bitów
	//	65535 = 0000 0000 0000 0000 1111 1111 1111 1111 	<=	2 części po 16 bitów
	
	//	4278255360 = 1111 1111 0000 0000 1111 1111 0000 0000	<=	4 części po 8 bity
	//	16711935 = 0000 0000 1111 1111 0000 0000 1111 1111	<=	4 części po 8 bity
	
	//	4042322160 = 1111 0000 1111 0000 1111 0000 1111 0000	<=	8 części po 4 bity
	//	252645135 = 0000 1111 0000 1111 0000 1111 0000	1111	<=	8 części po 4 bity
	
	//	3435973836 = 1100 1100 1100 1100 1100 1100 1100 1100	<=	16 części po 2 bity
	//	858993459 = 0011 0011 0011 0011 0011 0011 0011 0011	<=	16 części po 2 bity
	
	//	2863311530 = 1010 1010 1010 1010 1010 1010 1010 1010	<=	32 części po 1 bicie
	//	1431655765 = 0101 0101 0101 0101 0101 0101 0101 0101	<=	32 części po 1 bicie
	
    
    //	Dzielę 32 bitową liczbę na dwie 16 bitowe części, które zamieniam 
    //	ze sobą miejscami
    //	itd...
    wartosc = (wartosc & 4294901760) >> 16 | (wartosc & 65535) << 16;
    wartosc = (wartosc & 4278255360) >> 8 | (wartosc & 16711935) << 8;
    wartosc = (wartosc & 4042322160) >> 4 | (wartosc & 252645135) << 4; 
    wartosc = (wartosc & 3435973836) >> 2 | (wartosc & 858993459) << 2;
    wartosc = (wartosc & 2863311530) >> 1 | (wartosc & 1431655765) << 1;
    
	return wartosc;
}


int drugiSposob(int wartosc) 
{
	unsigned int buffor;
	unsigned int potega;
	unsigned int odwroconaWartosc = 0;
	short przesuniecie = 7;
	for (int  i = 32; i >= 16; i--) {
		potega = pow(2, i);
		buffor = wartosc;
		
		buffor = buffor & potega;
		
		buffor = buffor >> przesuniecie;
		przesuniecie -= 2;
		
		odwroconaWartosc = odwroconaWartosc | buffor;
	}
	przesuniecie = 1;
	for (int  i = 15; i >= 0; i--) {
		potega = pow(2, i);
		buffor = wartosc;
		
		buffor = buffor & potega;
		
		buffor = buffor << przesuniecie;
		
		przesuniecie += 2;
		
		odwroconaWartosc = odwroconaWartosc | buffor;
	}
	
	return odwroconaWartosc;
}

int main(void) 
{        
	unsigned int wartosc = 2;
	
	printf("%d => %d \n", wartosc, pierwszySposob(wartosc));
	printf("%d => %d \n", wartosc, drugiSposob(wartosc));
	
    
    return 0;
}

