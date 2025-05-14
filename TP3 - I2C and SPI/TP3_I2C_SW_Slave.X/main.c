#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 20000000

uint8_t Vitesse = 45;
uint8_t Lum = 78;

void I2C_Slave_Init(uint8_t address) {
    SSPSTAT = 0x00;
    SSPCON = 0x36;
    SSPADD = address;
    TRISC3 = 1;
    TRISC4 = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void __interrupt() ISR() {
    uint8_t rec;
    if (PIR1bits.SSPIF == 1) {
        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            rec = SSPBUF;
            while (!BF);
            rec = SSPBUF;
            PIR1bits.SSPIF = 0;

            switch (rec) {
                case 0xA0:
                    break;
                case 0xA1:
                    break;
                case 0xA2:
                    PORTCbits.RC0 = 1;
                    break;
                case 0xA3:
                    PORTCbits.RC0 = 0;
                    break;
                case 0xA4:
                    PORTCbits.RC1 = 1;
                    break;
                case 0xA5:
                    PORTCbits.RC1 = 0;
                    break;
            }
        }

        if (!SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
            rec = SSPBUF;
            while (!BF);
            SSPCONbits.CKP = 0;

            if (rec == 0xA0)
                SSPBUF = Lum;
            else if (rec == 0xA1)
                SSPBUF = Vitesse;

            SSPCONbits.CKP = 1;
            while (SSPSTATbits.BF);
        }
        PIR1bits.SSPIF = 0;
    }
}

void main() {
    TRISC0 = 0;
    TRISC1 = 0;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    I2C_Slave_Init(0x0F);
    while (1) {}
}
