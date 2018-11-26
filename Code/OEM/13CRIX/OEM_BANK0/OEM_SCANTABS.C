/*-----------------------------------------------------------------
 * TITLE: OEM_SCANTABS.C - RC Table(s) for Scan Matix
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *----------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const unsigned char code Rc_ROM_Tables1[] =
{
//-------------------------------------------------------------------------------------------
//	0	   1	       2	   3	      4       5        6        7        8        9        10     11       12       13      14        15
//	Fn     Esc	   XX	 XX	   XX    F3	   EZ2	  F5	 F6	  F7	  F9 Num8   F10     F11   NumLK  End
	0x8C, 0xEC, 0x00, 0x00, 0x00,0xE2, 0x00, 0xE4, 0xE5, 0xE6, 0xE8, 0x9D, 0xE9, 0xEA, 0xE6,  0xF4,   //  0 
//	XX      F1	L-Shf  XX	XX	  F2	     EZ5	  F4	     6	  8*	     F8      Num-   9(	  F12     PS/SR  PU/BR
	0x00, 0xE0, 0x88, 0x00, 0x00,0xE1, 0x00, 0xE3, 0x36, 0x9D, 0xE7, 0x9E, 0x9E, 0xEB, 0xF1,  0xF9,   //   1
//	XX	   ~`	XX      L-CTL  XX	  2        EZ6    4        5		  7	     I	        Num7   O       0)	     +=       BackSpace
	0x00, 0x0E, 0x00, 0x8E, 0x00,0x1E, 0x00, 0x25, 0x2E, 0x9C, 0xA1, 0x9C, 0xA2, 0x9F, 0x55,  0x66,   //   2
//	XX	   Tab     XX	   XX	L-Win w       EZ4	  E	     R	 Y	     K	  Num*  L	  [{	     \|45     Enter
	0x00, 0x0D, 0x00, 0x00, 0x82,0x1D, 0x00, 0x24, 0xF2, 0x35, 0xA5, 0xA3, 0xA6, 0x54, 0x61,  0x5A,   //    3
//	XX      Caps   Shf-R   XX	XX     S	     EZ3	  D	     G	  H	     M       130(JP)»??    XX      UpArr    \|29
	0x00, 0x58, 0x89, 0x00, 0x00,0x1B, 0x00, 0x23, 0x34, 0x33, 0xA8, 0x13, 0x00, 0x00, 0xED,  0x5D,   //   4
//	XX	   A	   XX	 XX	  XX	 X	  L-Alt   C	     F	  N	    ,<	 132(JP)  .>	/?	   Home    ;:
	0x00, 0x1C, 0x00, 0x00, 0x00,0x22, 0x8A, 0x21, 0x2B, 0x31, 0x41, 0x64, 0xAA, 0xAB, 0xF3,  0xA7,   //   5
//	XX	   $(JP)   XX	   XX       XX	  Z        R-Alt  131(JP)  V      B        Space App     ' "       $(?)    L-Arr    D-Arr
	0x00, 0x6A, 0x00, 0x00, 0x00,0x1A, 0x8B, 0x67, 0x2A, 0x32, 0x29, 0x84, 0x52, 0x00, 0xEF,  0xEE,   //   6
//	XX	   1!	      XX       CTL-R XX	  Q	     EZ1	  3#	     T	  U	      J	  Insert  P        -_      }]      R-Arr
	0x00, 0x16, 0x00, 0x8D, 0x00,0x15, 0x00, 0x26, 0x2C, 0xA0, 0xA4, 0xF5, 0xA3, 0x4E, 0x5B, 0xF0,   //    7  
};   // win8 key board matrix

//-------------------------------------------------------------------------------------------------
const unsigned char code EtKey_ROM_Tables1[] =
{
    //16    17    18    Extended - 19X8 Scan Table
    
  //Num/ NumEnter					//+CY_CR016
    0x00,0x00,0x00,     // 00  0
  //Num+ Num1
    0x00,0x00,0x00,     // 03  1
  //Num4 Num2
    0x00,0x00,0x00,     // 01  2
  //Num0 \_(JP)
    0x00,0x00,0x00,     // 05  3
  //PageUp  Num¡¤
    0x96,0x00,0x00,     // 02  4
  //Num9 PageDown
    0x00,0x97,0x00,     // 04  5
  //Del    Num6
    0xF6,0x00,0x00,     // 06  6
  //Num3 Num5
    0x00,0x00,0x00,     // 07  7		//-CY_CR016

};

//-------------------------------------------------------------------------------------------------
//RN1503 keyboard matrix code to Scan Code Set 2 table
const unsigned char code Rc_ROM_Tables[] =
{
 
//--------------------------------------------------------------------------------------------------------
//0  	1	    2 	 3	   4      5	   6  	7	   8       9	 A   B	   C  	D	   E  	F

// ESC    F4   NUL             G     H      F6          '     NUL   F5           Lalt        UpAw 
  0xEC, 0x0C, 0x2D, 0x00, 0x34, 0x33, 0xE5, 0x00, 0x52, 0x00, 0xE4, 0x00, 0x8A, 0x00, 0xED, 0x00,

// TAB	 F3  Capslock        t/T    Y     ]     F7	    [  	 LShift             backspace     	   	              
  0x0D, 0xE2, 0x90, 0x00, 0x2c, 0x35, 0x5B, 0xE6, 0x54, 0x88, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,

//	Q    E     W              R     U     I     O     P                                        Left windows
  0x15, 0x24, 0x1D, 0x00, 0x2D, 0x3C, 0x43, 0x44, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82,

// '     F2     F1    Fn     5%    6^    =+     F8      -    F9      Ins   del         home    pgup     	   	                                                      
  0x0E, 0xE1, 0xE0, 0x8E, 0x2E, 0x36, 0x55, 0x0A, 0x4E, 0x00, 0x01, 0xF3, 0xF5, 0x00, 0x94, 0x96,

//	A    D     S               F     J     K     L     ;           \	     	  LCtrl	Application 	     	  	                            
  0x1C, 0x23, 0x1B, 0x00, 0x2B, 0x3B, 0x42, 0x4B, 0x4C, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x8C, 0x84,

//  1!   3#    2@           4$	   7&      8*    9(    0)          F10   F11   PrtSrc F12   End   pgdn	       		            	      	     	     	         
  0x16, 0x26, 0x1E, 0x00, 0x25, 0x3D, 0x3E, 0x46, 0x45, 0x00, 0x09, 0x78, 0xF1, 0x07, 0xF2, 0x97,

//	Z     C     X    RCtrl	 V     M      <   	 >          RShift  Enter	                 Break	     	     	         
  0x1A, 0x21, 0x22, 0x8D, 0x2A, 0x3A, 0x41, 0x49, 0x00, 0x89, 0x5A, 0x00, 0x00, 0x00, 0xF4, 0x00,

//		     	      	      B      N                ?/          space    DAw   RAlt  RAw    LAw     	            
  0x00, 0x00, 0x00, 0x00, 0x32, 0x31, 0x00, 0x00, 0x4A, 0x00, 0x29, 0xEE, 0x8B, 0xF0, 0xEF, 0x00,
};

const unsigned char code EtKey_ROM_Tables[] =
{
    //16    17    18    Extended - 19X8 Scan Table
    
  //Num/ NumEnter					//+CY_CR016
    0x00,0x00,0x00,     // 00  0
  //Num+ Num1
    0x00,0x00,0x00,     // 03  1
  //Num4 Num2
    0x00,0x00,0x00,     // 01  2
  //Num0 \_(JP)
    0x00,0x00,0x00,     // 05  3
  //PageUp  Num¡¤
    0x96,0x00,0x00,     // 02  4
  //Num9 PageDown
    0x00,0x97,0x00,     // 04  5
  //Del    Num6
    0xF6,0x00,0x00,     // 06  6
  //Num3 Num5
    0x00,0x00,0x00,     // 07  7		//-CY_CR016
};

//-------------------------------------------------------------------------------------------


const unsigned char code KB_S3WakeUP_Tables[] =
{
    // Scanner Table 1
	//00   01   02   03   04   05   06   07   08   09   10   11   12   13   14   15
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
   	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55  //
};

const unsigned char code EtKey_S3WakeUP_Tables[] =
{	//16   17   18		// 19X8 Scan Table 
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Setup_Brightness_Level(BYTE Up_Down_f)
{
	if(Up_Down_f ==BRIGHTNESS_UP)
	{
		if (LCD_BRIGHTNESS<MAX_LEVEL)
		{
			LCD_BRIGHTNESS++;
		}
	}
	else
	{
		if (LCD_BRIGHTNESS > 0)
		{
			LCD_BRIGHTNESS--;
		}
	}
}

void OEM_SetBrightness_NO_ACPI(BYTE Up_Down_f)
{
	Setup_Brightness_Level(Up_Down_f);
	Setup_Brightness(LCD_BRIGHTNESS);
}

void OEM_WinXP_SetBrightness(BYTE Up_Down_f)
{
	SET_MASK(VPC_Lenovo,Brightness_Bit_vpc);
	ECQEvent(FN_SETBK_EVT,SCIMode_Normal);
	Setup_Brightness_Level(Up_Down_f);
	Setup_Brightness(LCD_BRIGHTNESS);
}


//---------------------------------------------------------------------------------
// The function of hotkey Fn + F1  Quickly go to S3 RN1503 have only S0 and S5 
//---------------------------------------------------------------------------------
void HotKey_Fn_F1(BYTE event)
{
  
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F2  Turn on/off the LCD pannel
//----------------------------------------------------------------------------
void HotKey_Fn_F2(BYTE event)
{
	Buffer_Key(0xE0);

   	if(event == BREAK_EVENT)
	{
		Buffer_Key(0xF0);
	}
	
    Buffer_Key(0x03); 
	
    if(event == MAKE_EVENT)
    {
      if(IS_MASK_SET(Oem_GPU_EC_BLK,Oem_EC_BLK))
      {
         CLEAR_MASK(Oem_GPU_EC_BLK,Oem_EC_BLK);
         LID_ON();  
	  }
	  else
	  {
          SET_MASK(Oem_GPU_EC_BLK,Oem_EC_BLK);
          LID_OFF();
	  }
	  
    }

}

//------------------------------------------------------------------------------------
// The function of hotkey Fn + F3  Turn on the projection switch application  
//------------------------------------------------------------------------------------
void HotKey_Fn_F3(BYTE event)//WYY:Fn+F3
{
   	if(event == MAKE_EVENT)
	{
		if(0x01 == Fn_Win_State)
		{
			Buffer_Key(0xE0);	 // win  make code,  scan code set 2
			Buffer_Key(0x1f);
			Buffer_Key(0x4d);	 // P make code,  scan code set 2
			Fn_Win_State = 0x02;
		}
		else if(0x02 == Fn_Win_State)
		{
			Buffer_Key(0x4d);	 // P make code,  scan code set 2
		}	
	}
  	else if(event == BREAK_EVENT)
	{
		Buffer_Key(0x99);	 //p break,  scan code set 1
	}
	else if(event == REPEAT_EVENT)
	{
		Buffer_Key(0x4d);	 // P make code,  scan code set 2
	}
 
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F4
//----------------------------------------------------------------------------
void HotKey_Fn_F4(BYTE event)      
{


}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F5 Turn on the wireless application  
//----------------------------------------------------------------------------
void HotKey_Fn_F5(BYTE event)
{
    Buffer_Key(0xE0);
	
	if(event == BREAK_EVENT)
	{
	  Buffer_Key(0xF0);	
	}
	
    Buffer_Key(0x04); 
	

   if(event != MAKE_EVENT)
   {
     return;
   }

   if(IS_MASK_SET(Oem_Device_Status,Wireless_IN))
   {
       CLEAR_MASK(Oem_Device_Status,Wireless_IN);
	  // RF_OFF();  // 2018/04/10
   }
   else
   {
      SET_MASK(Oem_Device_Status,Wireless_IN);
     // RF_ON();  // 2018/04/10
   }
   
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F6  on/off Touch pad
//----------------------------------------------------------------------------
void HotKey_Fn_F6(BYTE event)
{
    Buffer_Key(0xE0);
	
    if(event == BREAK_EVENT)
	{
	  Buffer_Key(0xF0);	
	}
	
    Buffer_Key(0x06); 
 
    if(event != MAKE_EVENT)
    {
      return;
    }
    if(IS_MASK_CLEAR(Oem_TP_Status,TP_ON_OFF))
	{
	     SET_MASK(Oem_TP_Status,TP_ON_OFF); 
		 CLEAR_MASK(Device_Status_Lenovo,TouchPad_S_B);
		 CLEAR_MASK(Device_Status_Lenovo,TouchPad_IN);
		 Hook_DisablePS2Port_2();
	}
	else
	{	
	    CLEAR_MASK(Oem_TP_Status,TP_ON_OFF); 
		SET_MASK(Device_Status_Lenovo,TouchPad_S_B);
		SET_MASK(Device_Status_Lenovo,TouchPad_IN);
		Hook_EnablePS2Port_2();
	}
	
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F7
//----------------------------------------------------------------------------
void HotKey_Fn_F7(BYTE event)
{


}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F8
//----------------------------------------------------------------------------
void HotKey_Fn_F8(BYTE event)
{


	
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F9
//----------------------------------------------------------------------------
void HotKey_Fn_F9(BYTE event)
{


}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F10
//----------------------------------------------------------------------------
void HotKey_Fn_F10(BYTE event)
{



}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F11
//----------------------------------------------------------------------------
void HotKey_Fn_F11(BYTE event)   
{



}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F12
//----------------------------------------------------------------------------
void HotKey_Fn_F12(BYTE event)
{


}

//----------------------------------------------------------------------------
// The function of hotkey Fn + ESC on/off Keyboard Led
//----------------------------------------------------------------------------
void HotKey_Fn_ESC(BYTE event)
{
    if(event != MAKE_EVENT)
	{
		return;
    }
	
    if(IS_MASK_SET(Oem_KB_Status,KB_LED))
    {
	   KBLED_OFF();
	   CLEAR_MASK(Oem_KB_Status,KB_LED);
	}
    else
    {
       KBLED_ON();
	   SET_MASK(Oem_KB_Status,KB_LED);
	}
    
}

//----------------------------------------------------------------------------------------------------------------
// The function of hotkey Fn + up arrow: to increase the pannel lightness and  need to send scan code to the host
//----------------------------------------------------------------------------------------------------------------
void HotKey_Fn_UP(BYTE event)
{

   Buffer_Key(0xE0);
   
   if(event == BREAK_EVENT)
   {
	  Buffer_Key(0xF0);
   }

   Buffer_Key(0x02); 

   if(event != MAKE_EVENT)
   {
      return;
   }
 

//Set_Brightness_Level(Brg_Up);   //<<lw 2017/12/6

Setup_Brightness(LCD_BRIGHTNESS); 

}

//--------------------------------------------------------------------------------------------------------------
// The function of hotkey Fn + down arrow: to reduce the pannel lightness and need to send scan code to the host
//--------------------------------------------------------------------------------------------------------------
void HotKey_Fn_DOWN(BYTE event)
{ 


	Buffer_Key(0xE0);
	 
	if(event == BREAK_EVENT)
	{
	  Buffer_Key(0xF0);
	}
	
	Buffer_Key(0x01);

    if(event != MAKE_EVENT)
    {
      return;
    }
	

//Set_Brightness_Level(Brg_Dw);   //<<lw 2017/12/6
	
//Setup_Brightness(LCD_BRIGHTNESS);  

    
}

//--------------------------------------------------------------------------------------
// The function of hotkey Fn + left arrow
//--------------------------------------------------------------------------------------
void HotKey_Fn_LEFT(BYTE event)
{


}

//---------------------------------------------------------------------------------------
// The function of hotkey Fn + right arrow
//---------------------------------------------------------------------------------------
void HotKey_Fn_RIGHT(BYTE event)
{


}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Ins (Scr Lk)
//---------------------------------------------------------------------------
void HotKey_Fn_Ins(BYTE event)
{
   
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Del (ScrLk)
//---------------------------------------------------------------------------
void HotKey_Fn_Del(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Pause (break)
//---------------------------------------------------------------------------

void HotKey_Fn_Pause(BYTE event)
{
   
}


//----------------------------------------------------------------------------
// The function of hotkey Fn + PrtScr (SysRq)
//---------------------------------------------------------------------------

void HotKey_Fn_PrtScr(BYTE event)
{


}



const FUNCT_PTR_V_B code HotKey_Fn_Fx[] =
{
	HotKey_Fn_F1,    	// Fn + F1
	HotKey_Fn_F2, 		// Fn + F2
	HotKey_Fn_F3, 		// Fn + F3
	HotKey_Fn_F4,       // Fn + F4
	HotKey_Fn_F5,    	// Fn + F5
	HotKey_Fn_F6, 		// Fn + F6
	HotKey_Fn_F7, 		// Fn + F7
	HotKey_Fn_F8,       // Fn + F8
	HotKey_Fn_F9,    	// Fn + F9
	HotKey_Fn_F10, 		// Fn + F10
	HotKey_Fn_F11, 		// Fn + F11
	HotKey_Fn_F12,    	// Fn + F12	
	HotKey_Fn_ESC,    	// Fn + ESC	
	HotKey_Fn_UP,    	// Fn + up arrow	
	HotKey_Fn_DOWN,    	// Fn + down arrow	
	HotKey_Fn_LEFT,    	// Fn + left arrow	
	HotKey_Fn_RIGHT,  	// Fn + right arrow	 
	HotKey_Fn_Del,	    // Fn + Del (ScrLk)
	HotKey_Fn_Pause,    // Fn + Pause (break)
	HotKey_Fn_PrtScr,   // Fn + PrtScr (SysRq)
};

//---------------------------------------------------------------------------
//	Numpad 7 Home	[B0h]
//	Numpad 8 UP  	[B1h]
//	Numpad 9 PGUp	[B2h]
//	Numpad *   		[B3h]
//	Numpad 4 Left	[B4h]
//	Numpad 5 		[B5h]
//	Numpad 6 Right	[B6h]
//	Numpad -  		[B7h]
//	Numpad 1 End	[B8h]
// 	Numpad 2 Down	[B9h]
//	Numpad 3 PGDn	[BAh]
//	Numpad + 		[BBh]
//	Numpad 0 Ins	[BCh]
// 	Numpad . Del	[BDh]
//	Numpad /      	[BEh]
//---------------------------------------------------------------------------
#if !NUMPAD_USE_OEM
const BYTE code ss2_9C[] =	// Numpad 7 
{
    0x3D,   // Normal 		// 7
    0xB0,   // Numlock 
    0xB0,   // Fn 
    0xB0    // Fn+Numlock 
};

const BYTE code ss2_9D[] =	// Numpad 8   
{
    0x3E,   // Normal 		// 8
    0xB1,   // Numlock 
    0xB1,   // Fn 
    0xB1    // Fn+Numlock 
};

const BYTE code ss2_9E[] = 	// Numpad 9  
{
    0x46,   // Normal 		// 9
    0xB2,   // Numlock 
    0xB2,   // Fn 
    0xB2    // Fn+Numlock 
};



const BYTE code ss2_A0[] = 	// Numpad U  
{
    0x3C,   // Normal 		// U
    0xB4,   // Numlock 
    0xB4,   // Fn 
    0xB4    // Fn+Numlock 
};

const BYTE code ss2_A1[] = 	// Numpad I  
{
    0x43,   // Normal 		// I
    0xB5,   // Numlock 
    0xB5,   // Fn 
    0xB5    // Fn+Numlock 
};

const BYTE code ss2_A2[] =	// Numpad O 
{
    0x44,   // Normal 		// O
    0xB6,   // Numlock 
    0xB6,   // Fn 
    0xB6    // Fn+Numlock 
};



const BYTE code ss2_A4[] = 	// Numpad J 
{
    0x3B,   // Normal 		// J
    0xB8,   // Numlock 
    0xB8,   // Fn 
    0xB8    // Fn+Numlock 
};

const BYTE code ss2_A5[] = 	// Numpad K 
{
    0x42,   // Normal 		// K
    0xB9,   // Numlock 
    0xB9,   // Fn 
    0xB9    // Fn+Numlock 
};

const BYTE code ss2_A6[] =	// Numpad L 
{
    0x4B,   // Normal 		// L
    0xBA,   // Numlock 
    0xBA,   // Fn 
    0xBA    // Fn+Numlock 
};


const BYTE code ss2_A8[] =	// Numpad M  
{
    0x3A,   // Normal 		// M
    0xBC,   // Numlock 
    0xBC,   // Fn 
    0xBC    // Fn+Numlock 
};



const BYTE code ss2_AA[] = 	// Numpad .>   
{
    0x49,   // Normal 		// .> 
    0xBD,   // Numlock 
    0xBD,   // Fn 
    0xBD    // Fn+Numlock 
};

#endif

#if !NUMPAD_MATH_USE_OEM

const BYTE code ss2_9F[] = 	// Numpad 0  
{
    0x45,   // Normal 		// 0
    0xBE,   // Numlock 
    0xBE,   // Fn 
    0xBE    // Fn+Numlock 
};

const BYTE code ss2_A3[] =	// Numpad P 
{
    0x4D,   // Normal 		// P
    0xB3,   // Numlock 
    0xB3,   // Fn 
    0xB3    // Fn+Numlock 
};


const BYTE code ss2_A7[] = 	// Numpad ;:  
{
    0x4C,   // Normal 		// ;:
    0xB7,   // Numlock 
    0xB7,   // Fn 
    0xB7    // Fn+Numlock 
};

const BYTE code ss2_AB[] = 	// Numpad /?      
{
    0x4A,   // Normal 		// /? 
    0xBB,   // Numlock 
    0xBB,   // Fn 
    0xBB    // Fn+Numlock 
};

#endif


//                                              Normal  Nrmlock    Fn      Fn+Numlock
#if NUMPAD_MATH_USE_OEM
const BYTE code ss2_9F[] ={  0x45,  0xBE,  0x45,  0xBE  };  //[0 ]<->[/]
const BYTE code ss2_A3[] ={  0x4D,  0xB3,  0x4D,  0xB3  };  //[P ]<->[*]
const BYTE code ss2_A7[] ={  0x4C,  0xB7,  0x4C,  0xB7  };  //[:;]<->[-]
const BYTE code ss2_AB[] ={  0x4A,  0xBB,  0x4A,  0xBB  };  //[?/]<->[+]
#endif
//-----------------------------------------------------------------------------
#if NUMPAD_USE_OEM
//Copy from CORE_XLT.C if Oem special request.
const BYTE code ss2_9C[] ={  0x3D,  0x3D,  0x3D,  0x3D  };  //[7 ]<->[7 ]
const BYTE code ss2_9D[] ={  0x3E,  0x3E,  0x98,  0x3E  };  //[8 ]<->[8 ]
const BYTE code ss2_9E[] ={  0x46,  0x46,  0x46,  0x46  };  //[9 ]<->[9 ]

const BYTE code ss2_A0[] ={  0x3C,  0x25,  0x9A,  0x25  };  //[U ]<->[4 ]
const BYTE code ss2_A1[] ={  0x43,  0x2E,  0x43,  0x2E  };  //[I ]<->[5 ]
const BYTE code ss2_A2[] ={  0x44,  0x36,  0x9B,  0x36  };  //[O ]<->[6 ]

const BYTE code ss2_A4[] ={  0x3B,  0x16,  0x3B,  0x16  };  //[J ]<->[1 ]
const BYTE code ss2_A5[] ={  0x42,  0x1E,  0x99,  0x1E  };  //[K ]<->[2 ]
const BYTE code ss2_A6[] ={  0x4B,  0x26,  0x4B,  0x26  };  //[L ]<->[3 ]

const BYTE code ss2_A8[] ={  0x3A,  0x45,  0x3A,  0x45  };  //[M ]<->[0 ]
const BYTE code ss2_AA[] ={  0x49,  0xBD,  0x49,  0xBD  };  //[>/]<->[. ]
#endif


const BYTE code ss2_A9[] = 	// Numpad ,<  
{
    0x41,   // Normal 		// ,< 
    0x41,   // Numlock 
    0x41,   // Fn 
    0x41    // Fn+Numlock 
};


const BYTE code ss2_AC[] =   
{
    0x5A,   // Normal 
    0x81,   // Fn 
};
//----------------------------------------------------------------
// Function key F1 ~ F12
//----------------------------------------------------------------
const BYTE code ss2_AD[] = 	// F1
{
    0x05,   // Normal 
    0xD0,   // Fn 
};

const BYTE code ss2_AE[] = 	// F2 	 
{
    0x06,   // Normal 
    0xD1,   // Fn 
};

const BYTE code ss2_AF[] = 	// F3  
{
    0x04,   // Normal 
    0xD2,   // Fn 
};

const BYTE code ss2_B0[] =	// F4   
{
    0x0C,   // Normal 
    0xD3,   // Fn 
};

const BYTE code ss2_B1[] = 	// F5  
{
    0x03,   // Normal 
    0xD4,   // Fn 
};

const BYTE code ss2_B2[] = 	// F6  
{
    0x0B,   // Normal 
    0xD5,   // Fn 
};

const BYTE code ss2_B3[] = 	// F7  
{
    0x80,   // Normal 
    0xD6,   // Fn 
};

const BYTE code ss2_B4[] = 	// F8  
{
    0x0A,   // Normal 
    0xD7,   // Fn 
};

const BYTE code ss2_B5[] = 	// F9  
{
    0x01,   // Normal 
    0xD8,   // Fn 
    //0x01,   // Normal 
};

const BYTE code ss2_B6[] = 	// F10  
{
    0x09,   // Normal  
    0xD9,   // Fn  
};

const BYTE code ss2_B7[] = 	// F11  
{
    0x78,   // Normal 
    0xDA,   // Fn  
};

const BYTE code ss2_B8[] = 	// F12  
{
    0x07,   // Normal 
    0xDB,   // Fn  
};

/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_A2_table
 *
 * The A2_TABLE structure contains the following.
 *
 * BYTE comb;  Bit   Setting Combination Key
 *            ---   -----------------------
 *             7    Hook_calc_index_comb_BIT7
 *             6    Hook_calc_index_comb_BIT6
 *             5    Fn
 *             4    Numlock
 *             3    Ctrl
 *             2    Alt
 *             1    Shift
 *             0    reserved
 *
 * BYTE *pntr; Pointer to array for key.
 * ------------------------------------------------------------------------- */
const A2_TABLE sskey2_A2_table[] =
{											// Keyboard matrix index
	// Keypad -->
	{0x30, ss2_9C },    /* index = 00h */    // 0x9C --- 7
    {0x30, ss2_9D },    /* index = 01h */	// 0x9D --- 8
    {0x30, ss2_9E },    /* index = 02h */	// 0x9E --- 9	
    {0x30, ss2_9F },    /* index = 03h */	// 0x9F --- 0	 
    {0x30, ss2_A0 },    /* index = 04h */	// 0xA0 --- U
    {0x30, ss2_A1 },    /* index = 05h */	// 0xA1 --- I
    {0x30, ss2_A2 },    /* index = 06h */	// 0xA2 --- O
    {0x30, ss2_A3 },    /* index = 07h */	// 0xA3 --- P
    {0x30, ss2_A4 },    /* index = 08h */	// 0xA4 --- J
    {0x30, ss2_A5 },    /* index = 09h */	// 0xA5 --- K
    {0x30, ss2_A6 },    /* index = 0Ah */	// 0xA6 --- L
    {0x30, ss2_A7 },    /* index = 0Bh */	// 0xA7 --- ;:
    {0x30, ss2_A8 },    /* index = 0Ch */	// 0xA8 --- M
    {0x30, ss2_A9 },  	/* index = 0Dh */	// 0xA9 --- ,<
    {0x30, ss2_AA },  	/* index = 0Eh */	// 0xAA --- .>
    {0x30, ss2_AB },    /* index = 0Fh */	// 0xAB --- /?
    {0x20, ss2_AC },  	/* index = 10h */	// 0xAC
	// Keypad <--
	
	// F1~F12 hotkeys -->
    {0x20, ss2_AD },    /* index = 11h */	// 0xAD
    {0x20, ss2_AE },    /* index = 12h */	// 0xAE
    {0x20, ss2_AF },    /* index = 13h */	// 0xAF
    {0x20, ss2_B0 },    /* index = 14h */	// 0xB0
    {0x20, ss2_B1 },    /* index = 15h */	// 0xB1
    {0x20, ss2_B2 },    /* index = 16h */	// 0xB2
    {0x20, ss2_B3 },    /* index = 17h */	// 0xB3
    {0x20, ss2_B4 },    /* index = 18h */	// 0xB4
    {0x20, ss2_B5 },    /* index = 19h */	// 0xB5
    {0x20, ss2_B6 },  	/* index = 1Ah */   // 0xB6
    {0x20, ss2_B7 },    /* index = 1Bh */	// 0xB7
    {0x20, ss2_B8 }     /* index = 1Ch */	// 0xB8	
    // F1~F12 hotkeys <--
};
											// Reserved 0xB9 ~ 0xDF
 
/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_overlay_table
 * ------------------------------------------------------------------------- */
 /*
const BYTE code sskey2_overlay_table[] =
{               //index     Normal   	Fn   			

	0x05,0xD0,	// E0H     F1     	Sleep
	0x06,0xD1,	// E1H	F2	  	Inverter
	0x04,0xD2,	// E2H	F3	  	Display mode
	0x0C,0x00,  // E3H     F4
	0x03,0xD4,	// E4H     F5 	  	RF 	
	0x0B,0x00,  // E5H     F6
	0x80,0xD6,  // E6H     F7
	0x0A,0xD7,  // E7H     F8           TP
	0x01,0x9F,  // E8H     F9           Multimedia Play/Pause Key 
	0x09,0x9E,  // E9H     F10          Multimedia Stop 
	0x78,0x9D,	// EAH     F11 	       Multimedia Previous Track	  
	0x07,0x9C,	// EBH     F12	  	 Multimedia Next Track 
	0x76,0xDC,  // ECH     ESC     	Camera on/off	
	0x98,0xDD,	// EDH	UpArrow  	Brightness Up
	0x99,0xDE,	// EEH	DnArrow	Brightness Down
	0x9A,0xA2,	// EFH	LeftArr	Vol Down 
	0x9B,0xA1,	// F0H	RightArr  	Vol Up
	0xC3,0xC1,  // F1H	PrtSc     	SysRq
	0x2D,0x4F,  // F2H      R       	Fn+R
	0x94,0x00, 	// F3h 	Home	<-> Null		  	 		 
	0x95,0x00, 	// F4h 	End 		<-> Null						 
	0xC2,0x77, 	// F5h 	Insert	<-> NumLK 		  	 
	0xC0,0x7E, 	// F6h 	Delete 	<-> Scr LK				  
	0x96,0x00, 	// F7h 	PageUp	<-> Null		 			 
	0x97,0x00, 	// F8h	PageDown	<-> Null				  
	0x91,0x92, 	// F9h 	Pause	<-> Break 			  


};
*/
const BYTE code  sskey2_overlay_table[] =
{

//index 	            Normal                           Fn                       	      																
  0x05,0x00,	// E0H    F1	                             Reserved RN1503 have not S3 status
  0x06,0xD1,	// E1H	 F2	                             turn on/off LCD
  0x04,0xD2,	// E2H    F3	                             turn on rejection application
  0x0C,0x00,	// E3H	 F4                              Reserved
  0x03,0xD4,	// E4H	 F5                              turn on wireless function
  0x0B,0xD5,	// E5H    F6                              turn on/off touchpad
  0x80,0x00,	// E6H    F7                              Reserved
  0x0A,0x00,	// E7H	 F8                              Reserved   
  0x01,0x00,	// E8H    F9	                            Reserved
  0x09,0x00,	// E9H    F10                            Reserved
  0x78,0x00,	// EAH    F11                            Reserved 
  0x07,0x00,	// EBH    F12	                            Reserved
  0x76,0xDC,	// ECH    ESC_function                   on/off Keyboard led                      
  0x98,0xDD,	// EDH    UpArr                          Brightness Up           
  0x99,0xDE,	// EEH    DnArr                          Brightness Down                                 
  0x9A,0xA2,	// EFH    LeftArr                        vol down               
  0x9B,0xA1,	// F0H    RightArr                       vol up
  0xC3,0x93,	// F1H	  PrtSc                         SysRq                                
  0x95,0x00,	// F2h	  End                           Reserved  	
  0xc2,0x00,	// F3h	 Insert                         Reserved
  0x91,0x92,	// F4h	  Pause                          Break  
  0xC0,0x7E,	// F5h	 Del                            ScrLK
  
  //0xC2,0x97,	// F6h	 insert                         PageDown 
 // 0x00,0x00	    // F7h	 Reserved                        Reserved        
 // 0x4F,0x00,	// F8H	  R                              Reserved
 // 0xDD,0x00,	// F9h	 UP_function                    Reserved   
};

// Reserved0xFA~ 0xFF
				


/* ----------------------------------------------------------------------------
 * Insyde Software Key Number 2
 *
 * 00h         Null
 * 01h - 7Fh   Same as IBM Scan Code, Set2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * C0h - DFh   Pre-Index for PPK function
 * C0h - DFh   Pre-Index for SMI function
 * ------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 * FUNCTION: sskey3_80_table - Insyde Software Key Number 2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * ------------------------------------------------------------------------- */
const BYTE code sskey3_80_table[] =
{

//-----------------------------------------------------------------
// Index from keyboard matrix
//-----------------------------------------------------------------	
									// Keyboard matrix index
	0x83, 	DO_SIMPLE_CODE,       	// 0		[80h] F7 (118) 
	0x5A, 	DO_E0_PREFIX_CODE,    	// 1		[81h] Numpad Enter (108) 
    0x1F, 	DO_E0_PREFIX_CODE,    	// 2		[82h] Windows Left 
    0x27, 	DO_E0_PREFIX_CODE,    	// 3		[83h] Windows Right 
    0x2F, 	DO_E0_PREFIX_CODE,    	// 4		[84h] Application 
    0x37, 	DO_E0_PREFIX_CODE,    	// 5		[85h] Power event 
    0x3F, 	DO_E0_PREFIX_CODE,    	// 6		[86h] Sleep event 
    0x5E, 	DO_E0_PREFIX_CODE,		// 7		[87h] Wake event 
    LShift, DO_CONTROL_EFFECT,		// 8		[88h] 12 Shift(L) 
    RShift, DO_CONTROL_EFFECT,		// 9		[89h] 59 Shift(R) 
    LAlt, 	DO_CONTROL_EFFECT,    	// A		[8Ah] 11 Alt(L) 
    RAlt, 	DO_CONTROL_EFFECT_E0,	// B		[8Bh] E0 11 Alt(R) 
    LCtrl, 	DO_CONTROL_EFFECT, 		// C		[8Ch] 14 Crtl(L) 
    RCtrl, 	DO_CONTROL_EFFECT_E0,	// D		[8Dh] E0 14 Ctrl(R) 
    FN, 	DO_CONTROL_EFFECT,    	// E		[8Eh] Fn 
    OVLAY,	DO_CONTROL_EFFECT,		// F		[8Fh] Overlay 
    CAP_LOCK,DO_CONTROL_EFFECT,     // 10	[90h] CapsLock
    0x00, 	DO_SPECIAL_CODE,      	// 11	[91h] Pause (126) 
    0x01, 	DO_SPECIAL_CODE,      	// 12	[92h] Break 
    0x84, 	DO_SIMPLE_CODE,       	// 13	[93h] (124) Alt-Case (SysRq) 
	0x6C, 	DO_E0_PREFIX_CODE,    	// 14	[94h] Home 
    0x69, 	DO_E0_PREFIX_CODE,    	// 15	[95h] End 
    0x7D, 	DO_E0_PREFIX_CODE,  	// 16	[96h] Page up 
    0x7A, 	DO_E0_PREFIX_CODE,    	// 17	[97h] Page down 
	0x75, 	DO_E0_PREFIX_CODE,    	// 18	[98h] UP arrow 
    0x72, 	DO_E0_PREFIX_CODE,    	// 19	[99h] Down arrow 
    0x6B, 	DO_E0_PREFIX_CODE,  	// 1A	[9Ah] Left arrow 
    0x74, 	DO_E0_PREFIX_CODE,   	// 1B	[9Bh] Right arrow 
    
//-----------------------------------------------------------------
// For MicroSoft enhance keyboard feature.
//-----------------------------------------------------------------
 	0x4D, DO_E0_PREFIX_CODE,    	// 1C	[9Ch] Next Track event 
    0x15, DO_E0_PREFIX_CODE,    	// 1D	[9Dh] Prev Track event 
    0x3B, DO_E0_PREFIX_CODE,    	// 1E	[9Eh] Stop event 
    0x34, DO_E0_PREFIX_CODE,    	// 1F	[9Fh] Play/Pause event 
    0x23, DO_E0_PREFIX_CODE,    	// 20	[A0h] Mute event 
    0x32, DO_E0_PREFIX_CODE,    	// 21	[A1h] Volume Up event 
    0x21, DO_E0_PREFIX_CODE,    	// 22	[A2h] Volume Down event 
    0x48, DO_E0_PREFIX_CODE,    	// 23	[A3h] Mail event 
    0x10, DO_E0_PREFIX_CODE,    	// 24	[A4h] Search event 
    0x3A, DO_E0_PREFIX_CODE,    	// 25	[A5h] Web/Home event 
    0x38, DO_E0_PREFIX_CODE,    	// 26	[A6h] Back event 
    0x30, DO_E0_PREFIX_CODE,    	// 27	[A7h] Forward event 
    0x28, DO_E0_PREFIX_CODE,    	// 28	[A8h] Stop event 
    0x20, DO_E0_PREFIX_CODE,    	// 29	[A9h] Refresh event 
    0x18, DO_E0_PREFIX_CODE,    	// 2A	[AAh] Favorites event 
    0x2B, DO_E0_PREFIX_CODE,    	// 2B	[ABh] Caluator event 
    0x40, DO_E0_PREFIX_CODE,    	// 2C	[ACh] My Computer event 
    0x50, DO_E0_PREFIX_CODE,    	// 2D	[ADh] Media event 
    0x00, DO_SIMPLE_CODE,       	// 2E	[AEh] Reserved
    0x00, DO_SIMPLE_CODE,      		// 2F	[AFh] Reserved 

    
//-----------------------------------------------------------------
// Index from sskey2_A2_table
//-----------------------------------------------------------------
	0x6C, DO_SIMPLE_CODE,     		// 30	Numpad 7 Home	   [B0h]
  	0x75, DO_SIMPLE_CODE,      		// 31	Numpad 8 UP  	   [B1h]     
 	0x7D, DO_SIMPLE_CODE,       	// 32	Numpad 9 PGUp	   [B2h] 
  	0x7C, DO_SIMPLE_CODE,       	// 33	Numpad *   	   [B3h]
	0x6B, DO_SIMPLE_CODE,       	// 34	Numpad 4 Left	   [B4h]     
 	0x73, DO_SIMPLE_CODE,       	// 35	Numpad 5 	   [B5h]
	0x74, DO_SIMPLE_CODE,       	// 36	Numpad 6 Right  [B6h]
	0x7B, DO_SIMPLE_CODE,       	// 37	Numpad -  	   [B7h]
	0x69, DO_SIMPLE_CODE,       	// 38	Numpad 1 End	    [B8h]
 	0x72, DO_SIMPLE_CODE,       	// 39	Numpad 2 Down	   [B9h]
	0x7A, DO_SIMPLE_CODE,       	// 3A	Numpad 3 PGDn	   [BAh]
	0x79, DO_SIMPLE_CODE,       	// 3B	Numpad + 	   [BBh]
	0x70, DO_SIMPLE_CODE,       	// 3C	Numpad 0 Ins	   [BCh]     
	0x71, DO_SIMPLE_CODE,      	 	// 3D	Numpad . Del	   [BDh]     
	0x4A, DO_E0_PREFIX_CODE, 		// 3E	Numpad /        [BEh]       
	                                                      
	0x00, DO_SIMPLE_CODE,      		// 3F	Reserved 	  [BFh]
	
    0x71, DO_E0_PREFIX_CODE,  		// 40 Delete 		[C0h]  
    0x84, DO_SIMPLE_CODE,    		// 41 SysRq		[C1h]  
    0x70, DO_E0_PREFIX_CODE,    	// 42 Insert		[C2h]  
    0x7C, DO_E0_PREFIX_CODE,  		// 43 Print Screen	[C3h] 
	0x41, DO_E0_PREFIX_CODE,     	// Euro Sign 		[C4h]
	0x49, DO_E0_PREFIX_CODE,    	// Dollar Sign 	[C5h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C6h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C7h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C8h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C9h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CAh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CBh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CCh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CDh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CEh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CFh]
	
// Function key F1 ~ F12     
    0x00	, DO_COSTOMER_FUNCTION,		// Function key F1	      [D0h]  
    0x01	, DO_COSTOMER_FUNCTION,		// Function key F2	      [D1h]  
    0x02	, DO_COSTOMER_FUNCTION,		// Function key F3	      [D2h] 
    0x03	, DO_COSTOMER_FUNCTION,		// Function key F4	      [D3h] 
    0x04	, DO_COSTOMER_FUNCTION,		// Function key F5	      [D4h] 
    0x05	, DO_COSTOMER_FUNCTION,		// Function key F6	      [D5h] 
    0x06	, DO_COSTOMER_FUNCTION,		// Function key F7	      [D6h] 
    0x07	, DO_COSTOMER_FUNCTION,		// Function key F8	      [D7h] 
    0x08	, DO_COSTOMER_FUNCTION,		// Function key F9	      [D8h] 
    0x09	, DO_COSTOMER_FUNCTION,		// Function key F10	      [D9h] 
    0x0A	, DO_COSTOMER_FUNCTION,		// Function key F11	      [DAh]  
    0x0B	, DO_COSTOMER_FUNCTION,		// Function key F12	      [DBh] 
	0x0C	, DO_COSTOMER_FUNCTION,   	// Function key Esc	      [DCh]
	0x0D	, DO_COSTOMER_FUNCTION,   	// Function key Up arrow	  [DDh]
	0x0E	, DO_COSTOMER_FUNCTION,   	// Function key Down arrow	  [DEh]
	0x0F	, DO_COSTOMER_FUNCTION,  	// Function key Left arrow	  [DFh]
	0x10	, DO_COSTOMER_FUNCTION,  	// Function key Right arrow  [E0h]	
	0x11    , DO_COSTOMER_FUNCTION,     // Function key Del          [E1h]
	0x12    , DO_COSTOMER_FUNCTION,     // Function key Pause        [E2h]
	0x13    , DO_COSTOMER_FUNCTION,     // Function key PrtScr       [E3h]     
};

// Reserved 0xE4 ~ 0xFF		


#define Crisiskey01        0x8E   	// Fn
#define Crisiskey02        0xF2  	// r/R
void CrisisHotkey01(BYTE event)	
{
   #define R_LOCATION  8
	
	BYTE  temp;
	temp=bscan_matrix[R_LOCATION];
	if((event == MAKE_EVENT)||(event==REPEAT_EVENT))
    {
		if (temp&0x08)
		{
			CrisisKeyStatus=100; 
		}
    }
}

void CrisisHotkey02(BYTE event)
{

	 if((event == MAKE_EVENT)||(event==REPEAT_EVENT))
	 {
		if (temp_scanner_state.field.tFN)
		{
			CrisisKeyStatus=100; 
		}
	 }
}

///modify by zhanglu



const sBootHotKeyStruct code asBootHotKeyStruct[]=
{
	{ Crisiskey01, CrisisHotkey01	},
	{ Crisiskey02, CrisisHotkey02	},
};

void CheckBootHotKey(matrix, event)
{
	BYTE index;
    for(index=0x00; index<(sizeof(asBootHotKeyStruct)/sizeof(sBootHotKeyStruct)); index++)
    {
		if(matrix==asBootHotKeyStruct[index].matrix)
	    {
	        (asBootHotKeyStruct[index].pfunction)(event);
            return;
        }
    }
    
}

//-----------------------------------------------------------------------------
// Keyboard wake up system from S3
//-----------------------------------------------------------------------------
void CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{
	BYTE wuv;

    wuv = ((BKSI << 4)|BKSO);
    Tmp_code_pointer = &KB_S3WakeUP_Tables;
    if(*(Tmp_code_pointer + wuv)==0x55)
    {
        PulseSBPowerButton();
    }
}

void Et_CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{
	BYTE wuv;

    wuv = ((BKSI*3)+BKSO);
    Tmp_code_pointer = &EtKey_S3WakeUP_Tables;
    if(*(Tmp_code_pointer + wuv)==0x55)
    {
        PulseSBPowerButton();
    }
}

//----------------------------------------------------------------------------
// table_entry : value of keyboard matrix table. for example Rc_ROM_Tables[]
// event : key MAKE_EVENT or BREAK_EVENT or REPEAT_EVENT
//----------------------------------------------------------------------------
void OEM_Hook_Send_Key(BYTE table_entry, BYTE event)
{
//    if(SystemIsS0)
//   {  	
        CheckBootHotKey(table_entry,event);
//    }
}

//----------------------------------------------------------------------------
// Return : 0xFF --> Send_Key function will be break; (no any scan code to host)
//----------------------------------------------------------------------------
BYTE OEM_Hook_Skip_Send_Key(void)
{
    return(0x00);
}
								
//-----------------------------------------------------------------------------
// Keyboard hook function (KSO0 - KSO15)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{
#if S3KeyboardWakeUp 
	if(SystemIsS3)
	{
		CheckKBS3Wake(KSIValus,KSOValus);
	}
#endif	
}		

//-----------------------------------------------------------------------------
// Keyboard hook function (KSO16 - KSO17 and GPIO KSO)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{
#if S3KeyboardWakeUp 
	if(SystemIsS3)
	{
		Et_CheckKBS3Wake(KSIValus,KSOValus);
	}
#endif	
}

/* ---------------------------------------------------------------------------
 * FUNCTION: Hook_Setup_Scanner_Pntr - to define the possible scanner tables
 *
 *     0   Rc_RAM_Table
 *     1   ROM Table 1
 *     ...
 * ------------------------------------------------------------------------ */
void Hook_Setup_Scanner_Pntr(void)
{  

    switch( KeyboardMatrixID )
    {
	#ifdef SUPPORT_KB_MATRIX_ID1
        case 0x01:
                Scanner_Table_Pntr = &Rc_ROM_Table1;
				if(ExtendMatrix)
	                Extendkey_Table_Pntr = &EtKey_ROM_Table1;
			
                break;
	#endif
	#ifdef SUPPORT_KB_MATRIX_ID2
        case 0x02:
                Scanner_Table_Pntr = &Rc_ROM_Table2;
				if(ExtendMatrix)
	                Extendkey_Table_Pntr = &EtKey_ROM_Table2;
			
                break;
	#endif
	#ifdef SUPPORT_KB_MATRIX_ID3
        case 0x03:
                Scanner_Table_Pntr = &Rc_ROM_Table3;
				if(ExtendMatrix)
	                Extendkey_Table_Pntr = &EtKey_ROM_Table3;
			
                break;
	#endif
        default:
                Scanner_Table_Pntr = &Rc_ROM_Tables;
				if(ExtendMatrix)
	                Extendkey_Table_Pntr = &EtKey_ROM_Tables;
			
                break;
    }

}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to high
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinH(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1H;
	}
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to low
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinL(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1L;
	}
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin output
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinCtrl(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1Ctl = 0x40;		// output
	}
}

//-----------------------------------------------------------------------------
// Fn key make
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Make(void)
{
   Fn_Win_State = 0x01;
}

//-----------------------------------------------------------------------------
// Fn key break
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Break(void)
{
	if(0x02==Fn_Win_State)
	{
		Buffer_Key(0xE0);	//WIN break code,  scan code set 1
		Buffer_Key(0xDB);
	}
	
	Fn_Win_State = 0;
}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit6
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT6(void)
{
    return(0x00);
}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit7
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT7(void)
{
    return(0x00);
}
