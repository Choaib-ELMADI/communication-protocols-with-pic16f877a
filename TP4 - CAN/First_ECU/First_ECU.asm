
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;First_ECU.c,54 :: 		void main() {
;First_ECU.c,55 :: 		Lcd_Init();                        // Initialize LCD
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	CALL	_Lcd_Init
;First_ECU.c,56 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
	MOV.B	#12, W10
	CALL	_Lcd_Cmd
;First_ECU.c,58 :: 		ADPCFG = 0xFFFF;
	MOV	#65535, W0
	MOV	WREG, ADPCFG
;First_ECU.c,59 :: 		PORTB = 0;
	CLR	PORTB
;First_ECU.c,60 :: 		TRISB = 0;
	CLR	TRISB
;First_ECU.c,62 :: 		Can_Init_Flags = 0;                             //
	CLR	W0
	MOV	W0, _Can_Init_Flags
;First_ECU.c,63 :: 		Can_Send_Flags = 0;                             // clear flags
	CLR	W0
	MOV	W0, _Can_Send_Flags
;First_ECU.c,64 :: 		Can_Rcv_Flags  = 0;                             //
	CLR	W0
	MOV	W0, _Can_Rcv_Flags
;First_ECU.c,68 :: 		_CAN_TX_NO_RTR_FRAME;
	MOV	#244, W0
	MOV	W0, _Can_Send_Flags
;First_ECU.c,75 :: 		_CAN_CONFIG_LINE_FILTER_OFF;
	MOV	#241, W0
	MOV	W0, _Can_Init_Flags
;First_ECU.c,77 :: 		RxTx_Data[0] = 9;                               // set initial data to be sent
	MOV	#lo_addr(_RxTx_Data), W1
	MOV.B	#9, W0
	MOV.B	W0, [W1]
;First_ECU.c,78 :: 		CAN1Initialize(1,3,3,3,1,Can_Init_Flags);       // initialize CAN1
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
;First_ECU.c,80 :: 		CAN1SetOperationMode(_CAN_MODE_CONFIG,0xFF);    // set CONFIGURATION mode
	MOV	#255, W11
	MOV	#4, W10
	CALL	_CAN1SetOperationMode
;First_ECU.c,82 :: 		CAN1SetMask(_CAN_MASK_B1,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask1 bits to ones
	MOV	#247, W13
	MOV	#65535, W11
	MOV	#65535, W12
	CLR	W10
	CALL	_CAN1SetMask
;First_ECU.c,83 :: 		CAN1SetMask(_CAN_MASK_B2,-1,_CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_XTD_MSG);   // set all mask2 bits to ones
	MOV	#247, W13
	MOV	#65535, W11
	MOV	#65535, W12
	MOV	#1, W10
	CALL	_CAN1SetMask
;First_ECU.c,84 :: 		CAN1SetFilter(_CAN_FILTER_B2_F3,ID_2nd,_CAN_CONFIG_XTD_MSG);                     // set id of filter B1_F1 to 2nd node ID
	MOV	#247, W13
	MOV	#3, W11
	MOV	#0, W12
	MOV	#4, W10
	CALL	_CAN1SetFilter
;First_ECU.c,86 :: 		CAN1SetOperationMode(_CAN_MODE_NORMAL,0xFF);                                     // set NORMAL mode
	MOV	#255, W11
	CLR	W10
	CALL	_CAN1SetOperationMode
;First_ECU.c,88 :: 		CAN1Write(ID_1st, RxTx_Data, 1, Can_Send_Flags);                                 // send initial message
	MOV	#1, W13
	MOV	#lo_addr(_RxTx_Data), W12
	MOV	#12111, W10
	MOV	#0, W11
	PUSH	_Can_Send_Flags
	CALL	_CAN1Write
	SUB	#2, W15
;First_ECU.c,90 :: 		while(1) {
L_main0:
;First_ECU.c,91 :: 		Lcd_Cmd(_LCD_CLEAR);                                                           // endless loop
	MOV.B	#1, W10
	CALL	_Lcd_Cmd
;First_ECU.c,92 :: 		Msg_Rcvd = CAN1Read(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags);        // receive message
	MOV	#lo_addr(_Can_Rcv_Flags), W13
	MOV	#lo_addr(_Rx_Data_Len), W12
	MOV	#lo_addr(_RxTx_Data), W11
	MOV	#lo_addr(_Rx_ID), W10
	CALL	_CAN1Read
	MOV	#lo_addr(_Msg_Rcvd), W1
	MOV.B	W0, [W1]
;First_ECU.c,93 :: 		if ((Rx_ID == ID_2nd) && Msg_Rcvd) {
	MOV	_Rx_ID, W0
	MOV	_Rx_ID+2, W1
	CP	W0, #3
	CPB	W1, #0
	BRA Z	L__main11
	GOTO	L__main9
L__main11:
	MOV	#lo_addr(_Msg_Rcvd), W0
	CP0.B	[W0]
	BRA NZ	L__main12
	GOTO	L__main8
L__main12:
L__main7:
;First_ECU.c,94 :: 		Lcd_Out(1,1,RxTx_Data[0]);                                                   // if message received check id
	MOV	#lo_addr(_RxTx_Data), W0
	ZE	[W0], W12
	MOV	#1, W11
	MOV	#1, W10
	CALL	_Lcd_Out
;First_ECU.c,95 :: 		RxTx_Data[0]++;
	MOV.B	#1, W1
	MOV	#lo_addr(_RxTx_Data), W0
	ADD.B	W1, [W0], [W0]
;First_ECU.c,96 :: 		Delay_ms(250);
	MOV	#4, W8
	MOV	#11725, W7
L_main5:
	DEC	W7
	BRA NZ	L_main5
	DEC	W8
	BRA NZ	L_main5
	NOP
;First_ECU.c,97 :: 		CAN1Write(ID_1st, RxTx_Data, 1, Can_Send_Flags);                             // send incremented data back
	MOV	#1, W13
	MOV	#lo_addr(_RxTx_Data), W12
	MOV	#12111, W10
	MOV	#0, W11
	PUSH	_Can_Send_Flags
	CALL	_CAN1Write
	SUB	#2, W15
;First_ECU.c,93 :: 		if ((Rx_ID == ID_2nd) && Msg_Rcvd) {
L__main9:
L__main8:
;First_ECU.c,99 :: 		}
	GOTO	L_main0
;First_ECU.c,100 :: 		}
L_end_main:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
