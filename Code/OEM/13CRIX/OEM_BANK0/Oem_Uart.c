#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


#define MaxLenStr       64 
#define TABNum          5


void put_char_uart(unsigned char ch);
void get_char_uart(void);
void Put_Hex_Cha_Uart(unsigned char ch);
void insidePut_Hex_Cha_Uart(unsigned char Byte);
void Put_Hex_Byte(unsigned char Byte);
void Put_Int(unsigned int aInt);	
void Put_Str(unsigned char *str);


void uart_Initial_Host(void)
{
	BADRSEL = 0x01;
  //  RSTDMMC = 0x00;
	GCR1 = 0x05;
	GPCRB0 = ALT;
	GPCRB1 = ALT;
}

void uart_Initial(void)
{
#ifdef UART_Debug   
//	GCR1 = 0x00;
	SCON=0x40;         // Mode 1  
	//SCON |= BIT4;    // Receive data enable  //R017
    T2CON &= 0xF0;     // EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0;
    T2CON |= 0x30;     // RCLK = 1; TCLK=1;     receive and send use time2
    T2MOD=0x00;
    RCAP2H=R2HV;
    RCAP2L=R2LV;
    TR2=1;
	TI=1;
	Uart_flag |= Uart_buffer_Empty;  // buff empty flag
#endif	
}





//
//put char to buffer
//
void put_char_uart(unsigned char ch)
{
	
	if(Uart_flag & Uart_buffer_Full)
	{
		Uart_buffer_Inp_ptr=0x08;
		Uart_buffer_Oup_ptr=0x00;
		((*(char xdata *)((&Uart_Base_Add)+0))='\n');
		((*(char xdata *)((&Uart_Base_Add)+1))=0x0d);
		((*(char xdata *)((&Uart_Base_Add)+2))='l');
		((*(char xdata *)((&Uart_Base_Add)+3))='o');
		((*(char xdata *)((&Uart_Base_Add)+4))='s');
		((*(char xdata *)((&Uart_Base_Add)+5))='t');
		((*(char xdata *)((&Uart_Base_Add)+6))='\n');
		((*(char xdata *)((&Uart_Base_Add)+7))=0x0d);
		Uart_flag&=~Uart_buffer_Empty;
	}
	else
	{
		((*(char xdata *)((&Uart_Base_Add)+Uart_buffer_Inp_ptr))=ch);
		Uart_buffer_Inp_ptr++;
		
		if(Uart_buffer_Inp_ptr == DebugUartRange)
			Uart_buffer_Inp_ptr = 0;
		
		Uart_flag&=~Uart_buffer_Empty;
		if(Uart_buffer_Inp_ptr == Uart_buffer_Oup_ptr) 
		{
			Uart_flag|=Uart_buffer_Full;
		}
	}
	
	return ;
}

/***************************************************************/

  
/***************************************************************/
//
// send char from buffer
//
void get_char_uart()
{
	unsigned char i;
	
	if(Uart_flag&Uart_buffer_Empty)
		return ;	
	
	i = (*(char xdata *)((&Uart_Base_Add)+Uart_buffer_Oup_ptr));
	
	Uart_buffer_Oup_ptr++;

	if(Uart_buffer_Oup_ptr == DebugUartRange)
		Uart_buffer_Oup_ptr = 0;	

	Uart_flag&=~Uart_buffer_Full;
	if(Uart_buffer_Oup_ptr == Uart_buffer_Inp_ptr) 
	{
		Uart_flag|=Uart_buffer_Empty;
	}
	
	TI=0;
	SBUF=i;
	
	return ;
}



/***************************************************************/
//	PrintCh : 将十六进制数据以字符形式显示出来
//
//	--------参数----------
//	ch : 要显示的十六进制数据, 低4位有效
//
/***************************************************************/
void Put_Hex_Cha_Uart(unsigned char ch)
{
	if(ch <= 9) 
		ch = ch + '0';
    else 
		ch = ch + 'A' - 10;
    put_char_uart( ch );
}

/***************************************************************/
//	insidePrintByte : 内部使用，以十六进制格式显示1个字节数据
//
//	--------参数----------
//	Byte : 要输出的一个字节数据
//
/***************************************************************/
void insidePut_Hex_Cha_Uart(unsigned char Byte) 	
{
	unsigned char c;
	c = Byte;
	c = c >> 4;        
	Put_Hex_Cha_Uart( c );
	c = Byte;
	c = c & 0x0F;
	Put_Hex_Cha_Uart( c );
}

/***************************************************************/
//	PrintByte : 内部使用，以十六进制格式显示1个字节数据
//
//	--------参数----------
//	Byte : 要输出的一个字节数据
//
/***************************************************************/
void Put_Hex_Byte(unsigned char Byte) //以十六进制格式显示1个字节数据
{
        
	insidePut_Hex_Cha_Uart( Byte );                
}



/***************************************************************/
//	PrintInt : 以十进制显示整数
//
//	--------参数----------
//	aInt : 要输出的一个整型数据
//
/***************************************************************/
/*void Put_Int(unsigned int aInt)		
{
	unsigned char temp;


	temp = aInt / 10000;
	if (temp != 0)
		 put_char_uart(temp + '0');
	else
		 put_char_uart( '0' );
	temp = aInt % 10000 / 1000;
	if (temp != 0) 
		put_char_uart(temp + '0');
	else
	    put_char_uart( '0' );
	temp = aInt % 1000 / 100;
	if (temp != 0) 
		put_char_uart(temp + '0');
	else
   	   put_char_uart( '0' );
	temp = aInt % 100 / 10;
	if (temp != 0) 
		put_char_uart(temp + '0');
	else
	    put_char_uart( '0' );
   	temp = aInt % 10;
	put_char_uart(temp + '0');

}
*/

/***************************************************************/
//	PrintStr : 显示字符串
//
//	--------参数----------
//	str : 要输出的字符串首地址
//
/***************************************************************/
/*
void Put_Str(unsigned char *str)
{
	unsigned char i;
	unsigned char j;
	unsigned char ch;

	for (i = 0; i < MaxLenStr; i++)
	{
		ch = *(str + i);
		if (ch == '\0') 
			break;
		else if(ch=='\n')
		{
			put_char_uart(10);
			put_char_uart(13);
		}
		else if(ch=='\t')
		{
			for(j = 0; j < TABNum; j++)
				put_char_uart(' ');
		}
		else 
			put_char_uart(ch);
	}
 
}


*/



