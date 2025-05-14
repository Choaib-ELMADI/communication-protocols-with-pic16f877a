
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;Second_ECU.c,50 :: 		void main() {
;Second_ECU.c,51 :: 		Lcd_Init();                        // Initialize LCD
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	CALL	_Lcd_Init
;Second_ECU.c,52 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
	MOV.B	#12, W10
	CALL	_Lcd_Cmd
;Second_ECU.c,54 :: 		ADPCFG = 0xFFFF;
	MOV	#65535, W0
	MOV	WREG, ADPCFG
;Second_ECU.c,55 :: 		PORTB = 0;
	CLR	PORTB
;Second_ECU.c,56 :: 		TRISB = 0;
	CLR	TRISB
;Second_ECU.c,58 :: 		Can_Init_Flags = 0;                               //
	CLR	W0
	MOV	W0, _Can_Init_Flags
;Second_ECU.c,59 :: 		Can_Send_Flags = 0;                               // clear flags
	CLR	W0
	MOV	W0, _Can_Send_Flags
;Second_ECU.c,60 :: 		Can_Rcv_Flags  = 0;                               //
	CLR	W0
	MOV	W0, _Can_Rcv_Flags
;Second_ECU.c,64 :: 		_CAN_TX_NO_RTR_FRAME;
	MOV	#244, W0
	MOV	W0, _Can_Send_Flags
;Second_ECU.c,71 :: 		_CAN_CONFIG_LINE_FILTER_OFF;
	MOV	#241, W0
	MOV	W0, _Can_Init_Flags
;Second_ECU.c,73 :: 		CAN1Initialize(1,3,3,3,1,Can_Init_Flags);         // initialize CAN
	MOV	#3, W13
	MOV	#3, W12
	MOV	#3, W11
	MOV	#1, W10
	MOV	#241, W0
	PUSH	W0
	MOV	#1, W0
	PUSH	W0
	CALL	_CAN1Initialize
	SUB	#4, W15
;Second_ECU.c,75 :: 		CAN1SetOperationMode(_CAN_MODE_CONFIG,0xFF);      // set CONFIGURATION mode
	MOV	#255, W11
	MOV	#4, W10
	CALL	_CAN1SetOperationMode
;Second_ECU.c,77 :: 		CAN1SetMask(_CAN_MASK_B1,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask1 bits to ones
	MOV	#247, W13
	MOV	#65535, W11
	MOV	#65535, W12
	CLR	W10
	CALL	_CAN1SetMask
;Second_ECU.c,78 :: 		CAN1SetMask(_CAN_MASK_B2,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask2 bits to ones
	MOV	#247, W13
	MOV	#65535, W11
	MOV	#65535, W12
	MOV	#1, W10
	CALL	_CAN1SetMask
;Second_ECU.c,79 :: 		CAN1SetFilter(_CAN_FILTER_B1_F1,ID_1st,_CAN_CONFIG_XTD_MSG);                     // set id of filter B1_F1 to 1st node ID
	MOV	#247, W13
	MOV	#12111, W11
	MOV	#0, W12
	CLR	W10
	CALL	_CAN1SetFilter
;Second_ECU.c,81 :: 		CAN1SetOperationMode(_CAN_MODE_NORMAL,0xFF);                                     // set NORMAL mode
	MOV	#255, W11
	CLR	W10
	CALL	_CAN1SetOperationMode
;Second_ECU.c,84 :: 		while(1) {
L_main0:
;Second_ECU.c,85 :: 		Lcd_Cmd(_LCD_CLEAR);                                                                       // endless loop
	MOV.B	#1, W10
	CALL	_Lcd_Cmd
;Second_ECU.c,86 :: 		Msg_Rcvd = CAN1Read(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags);        // receive message
	MOV	#lo_addr(_Can_Rcv_Flags), W13
	MOV	#lo_addr(_Rx_Data_Len), W12
	MOV	#lo_addr(_RxTx_Data), W11
	MOV	#lo_addr(_Rx_ID), W10
	CALL	_CAN1Read
	MOV	#lo_addr(_Msg_Rcvd), W1
	MOV.B	W0, [W1]
;Second_ECU.c,87 :: 		if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                           // if message received check id
	MOV	_Rx_ID, W2
	MOV	_Rx_ID+2, W3
	MOV	#12111, W0
	MOV	#0, W1
	CP	W2, W0
	CPB	W3, W1
	BRA Z	L__main9
	GOTO	L__main7
L__main9:
	MOV	#lo_addr(_Msg_Rcvd), W0
	CP0.B	[W0]
	BRA NZ	L__main10
	GOTO	L__main6
L__main10:
L__main5:
;Second_ECU.c,88 :: 		Lcd_Out(1,1,RxTx_Data[0]);
	MOV	#lo_addr(_RxTx_Data), W0
	ZE	[W0], W12
	MOV	#1, W11
	MOV	#1, W10
	CALL	_Lcd_Out
;Second_ECU.c,89 :: 		RxTx_Data[0]++;
	MOV.B	#1, W1
	MOV	#lo_addr(_RxTx_Data), W0
	ADD.B	W1, [W0], [W0]
;Second_ECU.c,90 :: 		Delay_ms(250);
	NOP
;Second_ECU.c,91 :: 		CAN1Write(ID_2nd, RxTx_Data, 1, Can_Send_Flags);                             // send incremented data back
	MOV	#1, W13
	MOV	#lo_addr(_RxTx_Data), W12
	MOV	#3, W10
	MOV	#0, W11
	PUSH	_Can_Send_Flags
	CALL	_CAN1Write
	SUB	#2, W15
;Second_ECU.c,87 :: 		if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                           // if message received check id
L__main7:
L__main6:
;Second_ECU.c,93 :: 		}
	GOTO	L_main0
;Second_ECU.c,94 :: 		}
L_end_main:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
