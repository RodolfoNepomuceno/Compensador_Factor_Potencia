#include <avr/io.h>
#include <stdlib.h>
/**
    Rodolfo Vargas 2-07-0856

    Libreria para el manejo del ADC
**/

int ADC_Converter(char canal)
{
    int adc_temp,valor_final;

    DDRC=0x3; // Entrada
    ADCSRA= 0x87; //habilita el ADC y selecciona ck/128
    ADMUX= canal; //AVCC ref.,data justificada a la derecha
    while (1)
    {
        ADCSRA|=(1<<ADSC); //Inicio de conversion
        while((ADCSRA&(1<<ADIF))==0);//espera fin de conversion
        adc_temp=ADCL;
        adc_temp|=(ADCH<<8);
        valor_final=(adc_temp/10);
       // itoa(valor_final,convertido,10);
        return valor_final;
    }
}
