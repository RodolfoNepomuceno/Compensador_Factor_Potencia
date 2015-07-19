/*
 * Compensador.c
 *
 * Created: 13/6/15 3:50:40 p. m.
 *  Author: Rodolfo
 */ 

#include <avr/io.h>
#include "Librerias/Comunicacion_Serial_ATMega8.h"
#include "Librerias/lcd8.h"
#include "Librerias/ADC_Converte.h"
#include "C:\Users\Rodolfo\Google Drive\Ingenieria Electronica\Potencia 2\Compensador_Proyecto\Compensador_Factor_Potencia\AVR\Compensador\Librerias\delay.h"

char voltaje();
char corriente();

int main(void)
{
	char voltaje_lectura=0,adc_voltaje;
	
	/*Inicializacion de dispositivos*/
	lcd_init();

    while(1)
    {
		lcd_clear();
		
		lcd_gotorc(1,1);
		lcd_puts("Potencia 2");
		lcd_gotorc(2,1);
		
		/**Voltaje**/
		voltaje_lectura=voltaje();
		itoa(voltaje_lectura,adc_voltaje,10);
		lcd_puts(adc_voltaje);
		
		ldelay_ms(500);
    }
}

/**Funcion obtener valor voltaje
Canal_sensor 0x4X donde 4 son los parametros y X el numero del canal**/
char voltaje()
{
	char canal_sensor1=0x40,voltaje_valor=0; 	
	voltaje_valor=ADC_Converter(canal_sensor1);	
	return voltaje_valor;
}

/**Funcion obtener valor corriente**/
char corriente()
{
	char canal_sensor2=0x41,corriente_valor=0;	
	corriente_valor=ADC_Converter(canal_sensor2);	
	return corriente_valor;
}