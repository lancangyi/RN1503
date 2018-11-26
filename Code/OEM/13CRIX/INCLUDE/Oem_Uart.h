#ifndef OemUart_h
#define OemUart_h

extern void put_char_uart(unsigned char ch);
extern void get_char_uart(void);
extern void Put_Hex_Cha_Uart(unsigned char ch);
extern void Put_Hex_Byte(unsigned char Byte);
extern void Put_Int(unsigned int aInt);	
extern void Put_Str(unsigned char *str);
//extern void Init_UART(void);
extern void uart_Initial_Host(void);
extern void uart_Initial(void);

#endif
