#include <stdio.h>
#include <delay.h>
#include <mega8.h>
#include <io.h>
#include <interrupt.h>

int i;
int lng;
char mystr[]="Atmega8 UART ready!";
char rc;

void lampOFF()
{
    PORTB.0=0;
}

void lampON()
{
    PORTB.0=1;
}

void initUART()
{
    UCSRB|=(1<<3)|(1<<4);   
    UBRRH=0x00;
    UBRRL=0x33;
}

void main(void)

{
    DDRB.0=1;
    initUART();

    //lng=strlen(mystr);

    for (i=0; i < 19; i++)    {
        while ( !( UCSRA & (1<<5)) ) {}
        UDR=mystr[i];
    }

    while (1)
    {
        if ((UCSRA & (1<<7)))
        {
            rc=UDR;
        }

        switch (rc)
        {
            case '1': lampON(); break;
            case '0': lampOFF(); break;
        }

    }

}
