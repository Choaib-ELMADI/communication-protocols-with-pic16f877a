#ifndef MEM_FUNCTIONS_H
#define	MEM_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#include "SPI_Functions.h"

unsigned char data;

void Write_Byte_25AA256(unsigned char, unsigned char, unsigned char);
unsigned char Read_Byte_25AA256(unsigned char, unsigned char);

#ifdef	__cplusplus
}
#endif

#endif // MEM_FUNCTIONS_H
