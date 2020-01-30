
/*
 * Lab1.c
 *
 * Created: 2020-01-22 10:12:27
 * Author : josvil-8
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define SCC_0 0x1551
#define SCC_1 0x0110
#define SCC_2 0x1E11
#define SCC_3 0x1b11
#define SCC_4 0x0b50
#define SCC_5 0x1b41
#define SCC_6 0x1F41
#define SCC_7 0x0111
#define SCC_8 0x1f51
#define SCC_9 0x1b51



int writeChar(char ch, int pos);
void LCD_Init(void);
void writeLong(long i);
void primes();
bool is_prime(long i);
int writeReg(int num, int reg, bool shift);
int main(void);

void blink() {
	int wait = 0x7FFF;
	bool swi = true;
	while(1) {
		if (TCNT1 == wait && swi) {
			LCDDR0 = 0x6;
			LCDDR3 = 0x1;
			LCDDR8 = 0x1;
		}
		else if(TCNT1 == 2*wait && !swi) {
			LCDDR0 = 0x0;
			LCDDR3 = 0x0;
			LCDDR8 = 0x0;
		}
		swi = !swi;
	//LCDDR13 = 0x1;
	//LCDDR18 = 0x1;
	}
}

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
    LCD_Init();
	blink();
	//writeChar('3',0);
	//long a = 32;
	//writeLong(a);
    //writeChar('4',4);
	//writeChar('6',3);
	//writeChar('9',5);
	//primes();
}

void LCD_Init(void){

	LCDCRB = (1<<LCDMUX1)|(1<<LCDMUX0)|(1<<LCDPM2)|(1<<LCDPM1)|(1<<LCDPM2);
	LCDFRR = (0<<LCDPS2)|(0<<LCDPS1)|(0<<LCDPS0)|(1<<LCDCD2)|(1<<LCDCD1)|(1<<LCDCD0);
	LCDCCR = (0<<LCDDC2)|(0<<LCDDC1)|(0<<LCDDC0)|(1<<LCDCC3)|(1<<LCDCC2)|(1<<LCDCC1)|(1<<LCDCC0);
	LCDCRA = (1<<LCDEN)|(1<<LCDAB)|(0<<LCDIE)|(0<<LCDBL);
	
	TCCR1B = (0<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);
	
}
void writeLong(long i) {
	int n = 0;
	while (n < 6) {
		int temp = i % 10;
		writeChar((char)temp + '0', 5-n);
		i = floor(i / 10);
		n += 1;
		
	}	
}

void primes() {
	for(long count=0; count < 50000; count+= 1) {
		if (is_prime(count))
			writeLong(count);
	}
	
}


bool is_prime(long i) {
	int n = 2;
	while (i % n != 0 && i > 1){
		if (i - 1 == n) return true;
		n += 1;
	}
	return false;
	
}


int writeChar(char ch, int pos){
	int SCC_X_0 = 0, SCC_X_1 = 0, SCC_X_2 = 0, SCC_X_3 = 0;
		
	switch (ch)
	{
	case '0' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0x5;
		SCC_X_3 = 0x1;
		
		break;
	case '1' :
		SCC_X_0 = 0x0;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0x1;
		SCC_X_3 = 0x0;
		break;
	case '2' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0xE;
		SCC_X_3 = 0x1;
		break;
	case '3' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	case '4' :
		SCC_X_0 = 0x0;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x0;
		break;
	case '5' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x4;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	case '6' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x4;
		SCC_X_2 = 0xf;
		SCC_X_3 = 0x1;
		break;
	case '7' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0x1;
		SCC_X_3 = 0x0;
		break;
	case '8' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xf;
		SCC_X_3 = 0x1;
		break;
	case '9' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	default:
		return 2;
	}
	
	switch(pos){
	case 0:
		LCDDR0=writeReg(SCC_X_0, LCDDR0, false);
		LCDDR5=writeReg(SCC_X_1, LCDDR5, false);
		LCDDR10=writeReg(SCC_X_2, LCDDR10, false);
		LCDDR15=writeReg(SCC_X_3, LCDDR15, false);		
		break;
	case 1:
		LCDDR0=writeReg(SCC_X_0, LCDDR0, true);
		LCDDR5=writeReg(SCC_X_1, LCDDR5, true);
		LCDDR10=writeReg(SCC_X_2, LCDDR10, true);
		LCDDR15=writeReg(SCC_X_3, LCDDR15, true);
		break;
	case 2:
		LCDDR1 = writeReg(SCC_X_0, LCDDR1, false);
		LCDDR6 = writeReg(SCC_X_1, LCDDR6, false);
		LCDDR11 = writeReg(SCC_X_2, LCDDR11, false);
		LCDDR16 = writeReg(SCC_X_3, LCDDR16, false);
		break;
	case 3:
		LCDDR1 = writeReg(SCC_X_0, LCDDR1, true);
		LCDDR6 = writeReg(SCC_X_1, LCDDR6, true);
		LCDDR11 = writeReg(SCC_X_2, LCDDR11, true);
		LCDDR16 = writeReg(SCC_X_3, LCDDR16, true);
		break;
	case 4:
		LCDDR2 = writeReg(SCC_X_0, LCDDR2, false);
		LCDDR7 = writeReg(SCC_X_1, LCDDR7, false);
		LCDDR12 = writeReg(SCC_X_2, LCDDR12, false);
		LCDDR17 = writeReg(SCC_X_3, LCDDR17, false);
		break;
	case 5:
		LCDDR2 = writeReg(SCC_X_0, LCDDR2, true);
		LCDDR7 = writeReg(SCC_X_1, LCDDR7, true);
		LCDDR12 = writeReg(SCC_X_2, LCDDR12, true);
		LCDDR17 = writeReg(SCC_X_3, LCDDR17, true);
		break;
	default:
		return 1;
	}
	return 0;
}

int writeReg(int num, int reg, bool shift){
	if(!shift){
		reg = reg & 0xF0;
		reg = reg | num;
	}
	else{
		reg = reg & 0x0F;
		reg = reg | (num<<4);
	}
	return reg;
}
