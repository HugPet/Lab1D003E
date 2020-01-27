/*
 * Lab1.c
 *
 * Created: 2020-01-22 10:12:27
 * Author : josvil-8
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

#define SCC_0 0x1551
#define SCC_1 0x0110
#define SCC_2 0x11d1
#define SCC_3 0x11c1
#define SCC_4 0x05b0
#define SCC_5 0x04b1
#define SCC_6 0x14b1
#define SCC_7 0x1110
#define SCC_8 0x15f1
#define SCC_9 0x15b1



int writeChar(char ch, int pos);
void LCD_Init(void);

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
    LCD_Init();
	writeChar('0',1);

    
}

void LCD_Init(void){

	/*LCDCRB = (1<<LCDMUX1)|(1<<LCDMUX0)|(1<<LCDPM2)|(1<<LCDPM1)|(1<<LCDPM2);
	LCDFRR = (0<<LCDPS2)|(0<<LCDPS1)|(0<<LCDPS0)|(1<<LCDCD2)|(1<<LCDCD1)|(1<<LCDCD0);
	LCDCCR = (0<<LCDDC2)|(0<<LCDDC1)|(0<<LCDDC0)|(1<<LCDCC3)|(1<<LCDCC2)|(1<<LCDCC1)|(1<<LCDCC0);
	LCDCRA = (1<<LCDEN)|(1<<LCDAB)|(0<<LCDIE)|(0<<LCDBL);
	*/
	LCDCRA= (1<<LCDEN) | (1<<LCDAB);
	LCDCRB= (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0) | (1<<LCDCS);
	LCDCCR= (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	LCDFRR= (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	
}

int writeChar(char ch, int pos){
	int SCC_X = 0;
		
	switch (ch)
	{
	case '0' :
		SCC_X = SCC_0;
		break;
	case '1' :
		SCC_X = SCC_1;
		break;
	case '2' :
		SCC_X = SCC_2;
		break;
	case '3' :
		SCC_X = SCC_3;
		break;
	case '4' :
		SCC_X = SCC_4;
		break;
	case '5' :
		SCC_X = SCC_5;
		break;
	case '6' :
		SCC_X = SCC_6;
		break;
	case '7' :
		SCC_X = SCC_7;
		break;
	case '8' :
		SCC_X = SCC_8;
		break;
	case '9' :
		SCC_X = SCC_9;
		break;
	default:
		return 2;
	}
	
	switch(pos){
	case 0:
		LCDDR0=(SCC_X & 0xF);
		LCDDR5=(SCC_X & 0xF0)<<4;
		LCDDR10=(SCC_X & 0xF00)<<8;
		LCDDR15=(SCC_X & 0xF000)<<12;
		break;
	case 1:
		LCDDR0=(SCC_X & 0xF)<<4;  //0000 1111     0001 0101 0101 0001
		LCDDR5=(SCC_X & 0xF0);
		LCDDR10=(SCC_X & 0xF00)>>4;
		LCDDR15=(SCC_X & 0xF000)>>12;
		break;
	case 2:
		LCDDR1=(SCC_X & 0xF);
		LCDDR6=(SCC_X & 0xF0);
		LCDDR11=(SCC_X & 0xF00);
		LCDDR16=(SCC_X & 0xF000);
		break;
	case 3:
		LCDDR1=(SCC_X & 0xF)<<4;
		LCDDR6=(SCC_X & 0xF0)<<4;
		LCDDR11=(SCC_X & 0xF00)<<4;
		LCDDR16=(SCC_X & 0xF000)<<4;
		break;
	case 4:
		LCDDR2=(SCC_X & 0xF);
		LCDDR7=(SCC_X & 0xF0);
		LCDDR12=(SCC_X & 0xF00);
		LCDDR17=(SCC_X & 0xF000);
		break;
	case 5:
		LCDDR2=(SCC_X & 0xF)<<4;
		LCDDR7=(SCC_X & 0xF0)<<4;
		LCDDR12=(SCC_X & 0xF00)<<4;
		LCDDR17=(SCC_X & 0xF000)<<4;
		break;
	default:
		return 1;
	}
	return 0;
}

