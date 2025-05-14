#line 1 "C:/Users/Choaib ELMADI/Documents/ENSA/GE-2/S4/Protocoles de Communication Embarqués/TP/TP4 - CAN/Second_ECU/Second_ECU.c"
#line 27 "C:/Users/Choaib ELMADI/Documents/ENSA/GE-2/S4/Protocoles de Communication Embarqués/TP/TP4 - CAN/Second_ECU/Second_ECU.c"
unsigned int Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags;
unsigned int Rx_Data_Len;
char RxTx_Data[8];
char Msg_Rcvd;
const unsigned long ID_1st = 12111, ID_2nd = 3;
unsigned long Rx_ID;


sbit LCD_RS at LATD0_bit;
sbit LCD_EN at LATD1_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;


void main() {
 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);

 ADPCFG = 0xFFFF;
 PORTB = 0;
 TRISB = 0;

 Can_Init_Flags = 0;
 Can_Send_Flags = 0;
 Can_Rcv_Flags = 0;

 Can_Send_Flags = _CAN_TX_PRIORITY_0 &
 _CAN_TX_XTD_FRAME &
 _CAN_TX_NO_RTR_FRAME;

 Can_Init_Flags = _CAN_CONFIG_SAMPLE_THRICE &
 _CAN_CONFIG_PHSEG2_PRG_ON &
 _CAN_CONFIG_XTD_MSG &
 _CAN_CONFIG_DBL_BUFFER_ON &
 _CAN_CONFIG_MATCH_MSG_TYPE &
 _CAN_CONFIG_LINE_FILTER_OFF;

 CAN1Initialize(1,3,3,3,1,Can_Init_Flags);

 CAN1SetOperationMode(_CAN_MODE_CONFIG,0xFF);

 CAN1SetMask(_CAN_MASK_B1,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);
 CAN1SetMask(_CAN_MASK_B2,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);
 CAN1SetFilter(_CAN_FILTER_B1_F1,ID_1st,_CAN_CONFIG_XTD_MSG);

 CAN1SetOperationMode(_CAN_MODE_NORMAL,0xFF);


 while(1) {
 Lcd_Cmd(_LCD_CLEAR);
 Msg_Rcvd = CAN1Read(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags);
 if ((Rx_ID == ID_1st) && Msg_Rcvd) {
 Lcd_Out(1,1,RxTx_Data[0]);
 RxTx_Data[0]++;
 Delay_ms(250);
 CAN1Write(ID_2nd, RxTx_Data, 1, Can_Send_Flags);
 }
 }
}
