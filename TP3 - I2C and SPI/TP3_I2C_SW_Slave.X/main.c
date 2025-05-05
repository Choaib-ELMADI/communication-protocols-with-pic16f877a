/* ---- SLAVE ---- */

#include <xc.h>
#include "main.h"

void main(void) {
    I2C_Slave_Init(0x0F);

    while (1) {
        /*if (PIR1bits.SSPIF) {
            if (!SSPSTATbits.D_nA) { // Address received
                Send_ACK_Bit();
            } else {
                Send_NACK_Bit();
            }
            PIR1bits.SSPIF = 0;
        }*/
    }
}
