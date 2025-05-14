#include <xc.h>
#include <stdint.h>
#include "utils.c"

#define _XTAL_FREQ 20000000
#define CLOCK_SPEED 400000
#define SLAVE_ADDRESS 0x0F

void I2C_Master_Init(int);
void Start_Bit(void);
void Repeated_Start(void);
void Send_Byte_Data(uint8_t);
uint8_t Receive_Byte_Data(void);
void Send_ACK_Bit(void);
void Send_NACK_Bit(void);
void Stop_Bit(void);

void EEPROM_Write(uint8_t addr, uint8_t data);
void LCD_Send_String(const char* str);

void main(void) {
    uint8_t lum, vitesse;

    I2C_Master_Init(CLOCK_SPEED);

    while (1) {
        Start_Bit();
        Send_Byte_Data((SLAVE_ADDRESS << 1) | 0);
        Send_Byte_Data(0xA0);
        Stop_Bit();

        __delay_ms(10);

        Start_Bit();
        Send_Byte_Data((SLAVE_ADDRESS << 1) | 1);
        lum = Receive_Byte_Data();
        Send_NACK_Bit();
        Stop_Bit();

        Start_Bit();
        Send_Byte_Data((SLAVE_ADDRESS << 1) | 0);
        Send_Byte_Data(0xA1);
        Stop_Bit();

        __delay_ms(10);

        Start_Bit();
        Send_Byte_Data((SLAVE_ADDRESS << 1) | 1);
        vitesse = Receive_Byte_Data();
        Send_NACK_Bit();
        Stop_Bit();

        EEPROM_Write(0x10, lum);
        EEPROM_Write(0x11, vitesse);

        LCD_Send_String("L=");
        LCD_Send_String((char[]){lum / 10 + '0', lum % 10 + '0', ' ', '\0'});
        LCD_Send_String("V=");
        LCD_Send_String((char[]){vitesse / 10 + '0', vitesse % 10 + '0', '\0'});

        __delay_ms(1000);
    }
}
