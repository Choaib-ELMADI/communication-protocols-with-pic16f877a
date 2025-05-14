/*
 * Project name:
     CAN_2nd (CAN Network demonstration with mikroE's CAN-1 module)
 * Copyright:
     (c) MikroElektronika, 2010.
 * Revision History:
     20100205:
       - initial release;
 * Description:
     This code demonstrates how to use CAN library functions and procedures.
     It is used together with the CAN_1st example (on second MCU), and it can
     be used to test the connection of MCU to the CAN network.
     With minor adjustments, it should work with any other MCU that has a CAN module.
 * Test configuration:
     MCU:             dsPIC30F4013
                      http://ww1.microchip.com/downloads/en/DeviceDoc/70138F.pdf
     Dev.Board:       EASYPIC v7 for dsPIC30  ac:CAN
                      http://www.mikroe.com/easypic-dspic30/
     Oscillator:      XT-PLL8, 80.000MHz
     Ext. Modules:    -
     SW:              mikroC PRO for dsPIC30/33 and PIC24
                      http://www.mikroe.com/mikroc/dspic/
 * NOTES:
     - Turn on PORTB LEDs at SW10 and turn on CAN RX (RF0) and TX (RF1) switches at SW8 and SW9.
 */

unsigned int Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags;  // can flags
unsigned int Rx_Data_Len;                                    // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const unsigned long ID_1st = 12111, ID_2nd = 3;              // node IDs
unsigned long Rx_ID;

// LCD module connections
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
// End LCD module connections

void main() {
  Lcd_Init();                        // Initialize LCD
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

  ADPCFG = 0xFFFF;
  PORTB = 0;
  TRISB = 0;

  Can_Init_Flags = 0;                               //
  Can_Send_Flags = 0;                               // clear flags
  Can_Rcv_Flags  = 0;                               //

  Can_Send_Flags = _CAN_TX_PRIORITY_0 &             // form value to be used
                   _CAN_TX_XTD_FRAME &              // with CAN1Write
                   _CAN_TX_NO_RTR_FRAME;

  Can_Init_Flags = _CAN_CONFIG_SAMPLE_THRICE &      // form value to be used
                   _CAN_CONFIG_PHSEG2_PRG_ON &      // with CAN1Initialize
                   _CAN_CONFIG_XTD_MSG &
                   _CAN_CONFIG_DBL_BUFFER_ON &
                   _CAN_CONFIG_MATCH_MSG_TYPE &
                   _CAN_CONFIG_LINE_FILTER_OFF;

  CAN1Initialize(1,3,3,3,1,Can_Init_Flags);         // initialize CAN

  CAN1SetOperationMode(_CAN_MODE_CONFIG,0xFF);      // set CONFIGURATION mode

  CAN1SetMask(_CAN_MASK_B1,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask1 bits to ones
  CAN1SetMask(_CAN_MASK_B2,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask2 bits to ones
  CAN1SetFilter(_CAN_FILTER_B1_F1,ID_1st,_CAN_CONFIG_XTD_MSG);                     // set id of filter B1_F1 to 1st node ID

  CAN1SetOperationMode(_CAN_MODE_NORMAL,0xFF);                                     // set NORMAL mode


  while(1) {
    Lcd_Cmd(_LCD_CLEAR);
    Msg_Rcvd = CAN1Read(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags);        // receive message
    if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                           // if message received check id
      Lcd_Out(1,1,RxTx_Data[0]);
      RxTx_Data[0]++;
      Delay_ms(250);
      CAN1Write(ID_2nd, RxTx_Data, 1, Can_Send_Flags);                             // send incremented data back
    }
  }
}