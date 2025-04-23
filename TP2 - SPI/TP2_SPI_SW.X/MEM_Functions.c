#include "MEM_Functions.h"

void Write_Byte_25AA256(unsigned char ADS_H, unsigned char ADS_L, unsigned char data) {
    SPI_Write_Data(0x02);
    SPI_Write_Data(ADS_H);
    SPI_Write_Data(ADS_L);
    SPI_Write_Data(data);
}

unsigned char Read_Byte_25AA256(unsigned char ADS_H, unsigned char ADS_L) {
    SPI_Write_Data(0x03);
    SPI_Write_Data(ADS_H);
    SPI_Write_Data(ADS_L);
    data = SPI_Read_Data();

    return data;
}
