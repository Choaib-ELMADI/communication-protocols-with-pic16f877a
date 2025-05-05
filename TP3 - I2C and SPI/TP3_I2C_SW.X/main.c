/* ---- MASTER ---- */

#include <xc.h>
#include "main.h"

void main(void) {
    INTCONbits.PEIE = 1;
    PIE1bits.SSPIE = 1;
    SSPCONbits.SSPEN = 1;

    I2C_Master_Init(CLOCK_SPEED);

    while (1) {
        Start_Bit();
        Send_Byte_Data((0x0F << 1) | 0);  // 0x0F = slave address, write mode (last bit 0)
        Stop_Bit();
        __delay_ms(1000);
    }
}
