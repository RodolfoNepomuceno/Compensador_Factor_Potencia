/**
    Rodolfo Vargas 2-07-0856
**/

#include <avr/io.h>
#include <util/delay.h>

/** Se define en que puerto se conecta el teclado4x4 **/
#define KEY_PRT PORTB //Registro PORT del Puerto
#define KEY_DDR DDRB //Registro DDR del Puerto
#define KEY_PIN PINB //Registro PIN del Puerto

/** Se define el puerto de salida del teclado **/
#define KEY_OUT DDRD //Registro DDR del Puerto

///** Se define la resistencia Pull UP del Puerto de salida**/
//#define KEY_PULLUP PORTB

void tdelay_ms (unsigned int d)
{
    _delay_ms(d);
}

int teclado4x4()
{
    const unsigned char keypad [4][4]= {0x33,0x32,0x31,0x30,0x37,0x36,0x35,0x34,0x42,0x41,0x39,0x38,0x46,0x45,0x44,0x43};

    unsigned char colloc,rowloc,ascii; //keyboard routine. this sends the ASCII

    KEY_OUT = 0xF0; //Establece como salida el puerto poniendo en alto sus pines de Salida
    KEY_DDR = 0xF0;
    KEY_PRT = 0xFF;

    while(1)
    {
        do
        {
            KEY_PRT &= 0x0F; //ground all row at once
            colloc = (KEY_PIN & 0x0F);//read columns
        }

        while(colloc != 0x0F); //check until all keys released
        do
        {
            do
            {
                tdelay_ms(20); //call delay
                colloc = (KEY_PIN&0x0F); //read the columns
            }
            while(colloc == 0x0F); //see if any key is pressed
            tdelay_ms(20); //call delay for debounce
            colloc = (KEY_PIN & 0x0F);
        }

        while(colloc == 0x0F); //wait for key press

        while(1)
        {
            KEY_PRT = 0xEF;
            colloc = (KEY_PIN & 0x0F);
            if(colloc != 0X0F)
            {
                //column detected
                rowloc = 0; //save row location
                break; //exit while loop
            }

            KEY_PRT = 0xDF; //ground  row1
            colloc = (KEY_PIN & 0x0F); //read the columns
            if(colloc != 0x0F)
            {
                //column detected
                rowloc =1; //save row location
                break; //exit whilw loop
            }
            KEY_PRT = 0xBF; //ground row 2
            colloc = (KEY_PIN & 0x0F); //read the columns
            if(colloc != 0x0F)
            {
                //column detected
                rowloc = 2; //save row location
                break; //exit whilw loop
            }
            KEY_PRT = 0x7F; //ground row3
            colloc=(KEY_PIN & 0x0F); //read the columns
            rowloc =3;//save row location
            break; //exit while loop
        }

        //check column and send result to port D

//        if(colloc == 0x0E)
//            KEY_PULLUP = (keypad[rowloc][0]);
//        else if(colloc ==0x0D)
//            KEY_PULLUP = (keypad[rowloc][1]);
//        else if(colloc == 0x0B)
//            KEY_PULLUP = (keypad[rowloc][2]);
//        else
//            KEY_PULLUP = (keypad[rowloc][3]);

        if(colloc == 0x0E)
        {
            ascii = (keypad[rowloc][0]);
            break;
        }
        else if(colloc ==0x0D)
        {
            ascii = (keypad[rowloc][1]);
            break;
        }
        else if(colloc == 0x0B)
        {
            ascii = (keypad[rowloc][2]);
            break;
        }
        else
        {
            ascii = (keypad[rowloc][3]);
            break;
        }
    }

    return ascii;

}
