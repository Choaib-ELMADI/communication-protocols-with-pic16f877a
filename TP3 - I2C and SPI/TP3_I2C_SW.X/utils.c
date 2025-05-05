#include <xc.h>
#include "main.h"

void I2C_Master_Init(int clock_speed) {
    SSPSTATbits.SMP = 0;
    SSPCON = 0b00101000;
    SSPADD = (_XTAL_FREQ / (4 * clock_speed)) - 1;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void Start_Bit() {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);                    // Cleared automatically
    PIR1bits.SSPIF = 0;
}

void Repeated_Start() {
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);                   // Cleared automatically
    PIR1bits.SSPIF = 0;
}

void Send_Byte_Data(uint8_t data) {
    SSPBUF = data;
    while (!PIR1bits.SSPIF);                    // Set automatically
    PIR1bits.SSPIF = 0;

    if (SSPCON2bits.ACKSTAT) {                  // No ACK
        Stop_Bit();
    }
}

uint8_t Receive_Byte_Data() {
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);                    // Set automatically
    return SSPBUF;
}

void Send_ACK_Bit() {
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);                  // Cleared automatically
}

void Send_NACK_Bit() {
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);                  // Cleared automatically
}

void Stop_Bit() {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);                    // Cleared automatically
    PIR1bits.SSPIF = 0;
}
