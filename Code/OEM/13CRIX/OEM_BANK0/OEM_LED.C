/*-----------------------------------------------------------------------------
 * TITLE: OEM_LED.C
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/* ----------------------------------------------------------------------------
 * FUNCTION:   OEM_Write_Leds
 *
 * Write to SCROLL LOCK, NUM LOCK, CAPS LOCK, and any custom LEDs (including
 * an "Fn" key LED).
 *
 * Input: data (LED_ON bit) = Data to write to the LEDs
 *         bit 0 - SCROLL, Scroll Lock
 *         bit 1 - NUM,    Num Lock
 *         bit 2 - CAPS,   Caps Lock
 *         bit 3 - OVL,    Fn LED
 *         bit 4 - LED4,   Undefined
 *         bit 5 - LED5,   Undefined
 *         bit 6 - LED6,   Undefined
 *         bit 7 - LED7,   Undefined
 *
 * Updates Led_Data variable and calls send_leds if appropriate.
 * ------------------------------------------------------------------------- */
void OEM_Write_Leds(BYTE data_byte)
{
    Led_Data = data_byte;
    if ( data_byte & BIT1 )
    {
	   	Hook_NUMLED_ON();
    }
 	else
 	{
		Hook_NUMLED_OFF();
 	}
	
    if ( data_byte & BIT2 )
    {
		Hook_CAPLED_ON();
    }
	else
	{
		Hook_CAPLED_OFF();
	}
}

//-----------------------------------------------------------------
// LED pattern
//-----------------------------------------------------------------
#define  BATLED_LEN      6
#define  PWRLED_LEN      6

const WORD code BattLEDPattern[]= 
{
	//-------------------------------------------------------------
 	//	BAT_FUL BAT_CHG BAT_DSG BAT_OUT BAT_LOW BAT_FAIL     
  	//-------------------------------------------------------------
  	0x0000,0x5555,
 	//	0x0000, 0x5555, 0x0000, 0x0000, 0x0000, 0x0000,  		// Battery LED1 
 	//	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   	// Battery LED2 
};

const WORD code PowerLEDPattern[]= 
{
  	//--------------------------------------------------------------------------
  	// 	S0      	S3   		S4      	S5      	index4  	index5    					 
	//--------------------------------------------------------------------------
  		0xFFFF, 0x5555, 0x0000, 0x0000, 0x0000, 0x0000,		//	Power LED1
      	0xFFFF, 0x5555, 0x0000, 0x0000, 0x0000,	0x0000,		// 	Power LED2
};

//----------------------------------------------------------------------------
// Turn on/off LEDs according to machine status.
// Executed once per 1 sec
// for example:
//		 ->BIT14	
// 		1010101010101010
// 		0101010101010101
//				  <-BIT3 				
//----------------------------------------------------------------------------
void ProcessLED(void)  // base 1s-A
{
	BYTE bat_index, pwr_index;   

	if(ledTestFlag)//test led mode
		return;
	
   	LED_FLASH_CNT <<= 1;
	if(LED_FLASH_CNT == 0)	LED_FLASH_CNT=0x0001;

    /* Power LED control method */
    pwr_index=0;                // pre-set S0                  
    
	if(SystemIsS5)              // pre-set S5    
	{
		pwr_index=3;
	}
	if(SystemIsS4)              // pre-set S4   
	{
		pwr_index=2;
	}
	if(SystemIsS3)              // pre-set S3    
	{
		pwr_index=1;
	}

	if(((Sys_Power_Status & 0x7f) == 0x03))    
	{
		pwr_index=1;
	}

	if(PowerLEDPattern[pwr_index] & LED_FLASH_CNT)	// setup power LED
	{	
      PWR_LED_ON();
	} 
	else 
	{	
      PWR_LED_OFF();
	}

    
    /* Battery LED control method */
	
	if(IS_MASK_SET(Oem_BatCtrl_F,Oem_BatCapTooLow_NotS0_f))
	{
		Oem_BatLedBlink_Cnt--;
		
		if(Oem_BatLedBlink_Cnt>0)
		{
			Delay1MS(10);
			
			bat_index = 0x01;

			if(BattLEDPattern[bat_index] & LED_FLASH_CNT) 
			{	
			  BATLED1_ON();
			} 
			else 
			{		
              BATLED1_OFF();
			}			
		}
		else
		{
			CLEAR_MASK(Oem_BatCtrl_F,Oem_BatCapTooLow_NotS0_f);

			if(IS_MASK_CLEAR(OS_PM_STATE,OS_AC_IN))
			{
			   ALLOW_PowerOFF();
			}
		}	
	}
	
}



void Battery_LED_PWM(WORD PWM_H,BYTE PWM_L)
{
	if(BAT_LED_Cnt_ON)
	{
		BAT_LED_Cnt_ON=BAT_LED_Cnt_ON-1;
		if((BAT_Step_ChargerFail != BAT1_CtrlStep)&&(BAT_Step_SetFail != BAT1_CtrlStep))
		{
           	if((BAT1_RSOC>=0) && (BAT1_RSOC<10) && (!Read_ACIN()))
            {
              BATLED1_ON(); //µÍµçÁ¿»ÆµÆÁÁ
		      BATLED0_OFF();
           	}   
            else
            {
              BATLED1_OFF();
		      BATLED0_ON();
           }
		}
		else
		{
           BATLED1_ON(); 
		   BATLED0_OFF();
		}
		
	}
	else if(BAT_LED_Cnt_OFF)
	{
		BAT_LED_Cnt_OFF = BAT_LED_Cnt_OFF - 1;
		BATLED1_OFF();
		BATLED0_OFF();
	}
	
	if(!(BAT_LED_Cnt_OFF|BAT_LED_Cnt_ON))
	{
		BAT_LED_Cnt_ON  = PWM_H;
		BAT_LED_Cnt_OFF = PWM_L;
	}
	
}

void Battery_LED_PWM_Fn_R(WORD PWM_H,BYTE PWM_L)   
{

	
	BATLED0_OFF();
	if(BAT_LED_Cnt_ON)
	{
		BAT_LED_Cnt_ON = BAT_LED_Cnt_ON - 1;
		BATLED1_ON();
	}
	else if(BAT_LED_Cnt_OFF)
	{
		BAT_LED_Cnt_OFF = BAT_LED_Cnt_OFF - 1;
		BATLED1_OFF();    
	}
	
	if(!(BAT_LED_Cnt_OFF|BAT_LED_Cnt_ON))
	{
		BAT_LED_Cnt_ON  = PWM_H;
		BAT_LED_Cnt_OFF = PWM_L;
	}
	
}

void Battery_LED_Reset(void)
{
	
	BAT_LED_Cnt_ON  = 0;
	BAT_LED_Cnt_OFF = 0;

    BATLED0_OFF();
    BATLED1_OFF();
}


void BatLedBlink()             //100ms  time base
{

}


void SetBatLed(void) // base 100ms-B 
{
		if(ledTestFlag)//test led mode
		return;
		

		if((SystemIsS0) && (IS_MASK_SET(Oem_Globe_Flag1,Oem_Fn_R)))
		{
			Battery_LED_PWM_Fn_R(10,5); 
			return;
		}
		
		if(!Read_BatIN())   // no battery
		{
			Battery_LED_Reset();
			CLEAR_MASK(Oem_Globe_Flag,LED_BAT_BP_READY);
			return;
		}

		
		if(IS_MASK_SET(Oem_BatCtrl_F,Oem_BatCapTooLow_NotS0_f))
		   return;

		if((SystemNotS0) && (!Read_ACIN()))		//no  ac  and in s3/s4/s5
		{
			Battery_LED_Reset();
			return;					//on only s0 in battery-only mode
		}


		if(BAT1_CtrlStep == BAT_Step_FullyChg)
		{
			Battery_LED_PWM(2,0); 	//solid on
		}
		else if((BAT1_CtrlStep == BAT_Step_NC) 
			|| (BAT1_CtrlStep == BAT_Step_PC)
			|| (BAT1_CtrlStep == BAT_Step_ForceC)) //---------------------- charge mode
		{
		    if(BAT1_RSOC>=0) //------------------ blue led blink
			{
				Battery_LED_PWM(20,1); 	//2s on ,100ms off 
			}
		}
		else if((BAT1_CtrlStep == BAT_Step_DC)
			|| (BAT1_CtrlStep == BAT_Step_FullyDisChg)
			|| (BAT1_CtrlStep == BAT_Step_ForceDC))  //lw //------------------- discharge mode
		{
             Battery_LED_PWM(2,0); 	//solid on			
		}
}




//----------------------------------------------------------------------------
// The function of turning on all LED		
//----------------------------------------------------------------------------
void TurnOnAllLED(void)
{
   
}

//----------------------------------------------------------------------------
// The function of turning off all LED		
//----------------------------------------------------------------------------
void TurnOffAllLED(void)
{

}
//----------------------------------------------------------------------------
// The function of debuging LED			
//----------------------------------------------------------------------------
void DebugLED(void) 
{

}

void PWRLED_ON(void)
{
	PWR_LED_ON();	
}

void PWRLED_OFF(void)
{
	PWR_LED_OFF();	
}


void OEM_LED_TEST(void)
{



}

