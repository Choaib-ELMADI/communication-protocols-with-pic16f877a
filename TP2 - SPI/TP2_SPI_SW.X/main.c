#include <xc.h>

#include "MEM_Functions.h"

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define ADDRESS_H 0x25
#define ADDRESS_L 0x50

unsigned char data_read;

void main(void) {
    TRISCbits.TRISC3 = 0;       // SCK
    TRISCbits.TRISC4 = 1;       // SDI
    TRISCbits.TRISC5 = 0;       // SDO
    TRISCbits.TRISC7 = 0;       // CS
    TRISD = 0xFF;

    SPI_Init();
    __delay_ms(1000);

    while (1) {
        PORTCbits.RC7 = 0;      // Activate slave
        Write_Byte_25AA256(ADDRESS_H, ADDRESS_L, PORTD);
        PORTCbits.RC7 = 1;      // Deactivate slave
        __delay_ms(1000);

        PORTCbits.RC7 = 0;
        data_read = Read_Byte_25AA256(ADDRESS_H, ADDRESS_L);
        PORTCbits.RC7 = 1;
        __delay_ms(3000);
    }
}
