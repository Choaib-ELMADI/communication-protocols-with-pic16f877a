void I2C_Master_Init(int clock_speed) {
    SSPSTAT = 0x00;
    SSPCON = 0x28;
    SSPADD = (_XTAL_FREQ / (4 * clock_speed)) - 1;
    TRISC3 = 1;
    TRISC4 = 1;
}

void Start_Bit() {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);
    PIR1bits.SSPIF = 0;
}

void Repeated_Start() {
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);
    PIR1bits.SSPIF = 0;
}

void Send_Byte_Data(uint8_t data) {
    SSPBUF = data;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) Stop_Bit();
}

uint8_t Receive_Byte_Data() {
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    return SSPBUF;
}

void Send_ACK_Bit() {
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
}

void Send_NACK_Bit() {
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
}

void Stop_Bit() {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
    PIR1bits.SSPIF = 0;
}

void EEPROM_Write(uint8_t addr, uint8_t data) {
    Start_Bit();
    Send_Byte_Data(0xA0);
    Send_Byte_Data(addr);
    Send_Byte_Data(data);
    Stop_Bit();
    __delay_ms(5);
}

void LCD_Send_String(const char* str) {
    while (*str) {
        Start_Bit();
        Send_Byte_Data(0x4E);
        Send_Byte_Data(*str);
        Stop_Bit();
        str++;
    }
}
