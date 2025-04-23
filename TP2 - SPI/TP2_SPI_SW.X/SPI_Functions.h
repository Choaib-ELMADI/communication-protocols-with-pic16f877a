#ifndef SPI_FUNCTIONS_H
#define	SPI_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

void SPI_Init(void);
void SPI_Write_Enable(void);
void SPI_Write_Data(unsigned char);
unsigned char SPI_Read_Data(void);

#ifdef	__cplusplus
}
#endif

#endif // SPI_FUNCTIONS_H
