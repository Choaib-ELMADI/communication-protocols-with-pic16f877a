#include "SPI_Functions.h"

void SPI_Init() {
    SSPCON = 0x20;
    SSPSTAT = 0x00;
}

void SPI_Write_Enable() {
    SSPBUF = 0x06;
    while (!PIR1bits.SSPIF);                // Set automatically
    PIR1bits.SSPIF = 0;
}

void SPI_Write_Data(unsigned char data) {
    SSPBUF = data;
    while (!PIR1bits.SSPIF);                // Set automatically
    PIR1bits.SSPIF = 0;
}

unsigned char SPI_Read_Data() {
    SSPBUF = 0x00;
    while (!SSPSTATbits.BF);                // Set automatically
    SSPSTATbits.BF = 0;
    return SSPBUF;
}
