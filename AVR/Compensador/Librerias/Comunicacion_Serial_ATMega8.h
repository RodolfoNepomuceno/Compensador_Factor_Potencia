
/*
* Comunicacion Serial
*
* Created: 2/7/14 10:41:50 p. m.
*  Author: Rodolfo
*/

#include <avr/io.h>

/*Transmision/Recepcion [0 Inhabilita, 1 habilita]*/
#define TX 1
#define RX 0


/*Parametros de comunicacion*/
#define FOSC 16000000 // Clock Speed
#define BAUD 9600


/*Tamano de Datos*/
/*			Z2		Z1		Z0
5 Bit		0		0		0
6 Bit		0		0		1
7 Bit		0		1		0
8 Bit		0		1		1
9 Bit		1		1		1	*/

#define Z2 0
#define	Z1 1
#define Z0 1

/* Modo de Comunicacion [0  Asincrona, 1 Sincrona] */
#define AS 0


/*Funciones*/
void USART_Init()
{
	#define MYUBRR FOSC/16/BAUD-1
	
	UCSRB =(TX<<TXEN)|(RX<<RXEN)|(Z2<<UCSZ2);
	UCSRC = (Z1<<UCSZ1)|(Z0<<UCSZ0)|(1<<URSEL)|(AS<<UMSEL);
	UBRRL = MYUBRR;
}

void USART_Transmit (unsigned char ch)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = ch;
}

void USART_Texto(char* Texto)
{	
	while(*Texto != 0x00)
	{
		USART_Transmit(*Texto);
		Texto++;
	}	
}


