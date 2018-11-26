/*----------------------------------------------------------------------------
 * Filename: OEM_Power.C  For Chipset: ITE.IT85XX
 *
 * Function: Power sequnce control function example
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

void ALLOW_PowerON(void)
{
	
	S5_PWR_ON();
}


void ALLOW_PowerOFF(void)
{
	S5_PWR_OFF();
}


void Heatingfilm_PowerON(void)
{
   S5_PWR_ON();
}


void Heatingfilm_PowerOFF(void)
{
   S5_PWR_OFF();
}

 


BYTE EC_Read_SB_PWROK(void)
{
	if(Read_SB_PWRGD())
	{
		return(1);
	}
	return(0);
}



BYTE EC_Read_1V8_PWROK(void)
{
	if(Read_1V8_PWRGD())
	{
		return(1);
	}
	return(0);
}

BYTE EC_Read_VCORE_PWROK(void)
{
    if(Read_VCORE_PWRGD())
	{
		return(1);
	}
	return(0);
}

BYTE EC_Read_VDDA_PWROK(void)
{
    if(Read_VDDA_PWRGD())
	{
		return(1);
	}
	return(0);
}


void EC_VOLMUTE_ON(void)
{
	VOLMUTE_ON();
}

void EC_VOLMUTE_OFF(void)
{
	VOLMUTE_OFF();
}

void Init_PS8625(void)
{
   BYTE PS8625_Tmp;
   //PS8625 common setting
   PS8625_Tmp = 0x01;
   if(!bRWSMBus(PS8625Channel,SMbusWB,0X94,0xa1,&PS8625_Tmp,SMBus_NoPEC))
   { 
     return;
   }
   PS8625_Tmp = 0x01;
   bRWSMBus(PS8625Channel,SMbusWB,0X98,0x14,&PS8625_Tmp,SMBus_NoPEC);
   PS8625_Tmp = 0x20;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0xe3,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x80;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0xe2,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x0c;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x8a,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x08;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x89,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x2d;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x71,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x04;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x7d,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x00;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x7b,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0xfd;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x7a,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x12;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0xc0,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x92;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0xc1,&PS8625_Tmp,SMBus_NoPEC);
    PS8625_Tmp = 0x1c;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0xc2,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x80;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x32,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0xb0;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x00,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x40;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x15,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x10;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x54,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x20;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0x52,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x03;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0xf1,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x41;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0x62,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x01;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0xf6,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x03;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0xf1,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x41;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0x62,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x01;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0xf6,&PS8625_Tmp,SMBus_NoPEC);
    PS8625_Tmp = 0x10;
	bRWSMBus(PS8625Channel,SMbusWB,0X94,0xa1,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x06;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0x77,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x04;
	bRWSMBus(PS8625Channel,SMbusWB,0X90,0x4c,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x00;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc0,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x1c;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc1,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0xf8;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc2,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x44;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc3,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x32;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc4,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x44;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc5,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x4c;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc6,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x56;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc7,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x35;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc8,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x01;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xca,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x07;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xcb,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x1c;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xc1,&PS8625_Tmp,SMBus_NoPEC);

    //PS8625 Customized Setting
    PS8625_Tmp = 0x07;
	bRWSMBus(PS8625Channel,SMbusWB,0X92,0xcc,&PS8625_Tmp,SMBus_NoPEC);
    PS8625_Tmp = 0x20;
	bRWSMBus(PS8625Channel,SMbusWB,0X94,0xb1,&PS8625_Tmp,SMBus_NoPEC);
	PS8625_Tmp = 0x16;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x10,&PS8625_Tmp,SMBus_NoPEC);

   // PS8625_Tmp = 0x10;
   // bRWSMBus(PS8625Channel,SMbusWB,0X98,0x00,&PS8625_Tmp,SMBus_NoPEC);
	
	PS8625_Tmp = 0x60;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x59,&PS8625_Tmp,SMBus_NoPEC);

	PS8625_Tmp = 0x14;
	bRWSMBus(PS8625Channel,SMbusWB,0X98,0x54,&PS8625_Tmp,SMBus_NoPEC);

	PS8625_Tmp = 0x91;
	bRWSMBus(PS8625Channel,SMbusWB,0X94,0xa1,&PS8625_Tmp,SMBus_NoPEC);
}





//-------------------------------------------------------------------------------------
//  Do S5 -> S0 power sequnce
//-------------------------------------------------------------------------------------

const sPowerSEQ code asPowerSEQS5S0[]=  
{ 
    { 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ ALLOW_PowerON,	    5,		0,	},  // start system Power on,delay 5ms ----step1
	{ Hook_PWR_ON,			0,		0,	},  // ---------step2
	{ EC_Read_SB_PWROK,		1,		1,	},  // wait SB Power ok,delay 1ms ---------step3
	{ Hook_MISCPWR_ON,      2,      0,  },  // -----------step4 delay 2ms
	{ InitSio,				0,		0,	},  // -----------
	{ EC_Read_1V8_PWROK,    20,		1,	},  //------------step7
	{ Hook_VCORE_EN_ON,		0,		0,	},  //------------step8 
	{ EC_Read_VCORE_PWROK,  10,		1,	},  // -----------step9  
	{ Hook_ECVDDA_ON,	    0,      0,  },  //  ------------step10
	{ EC_Read_VDDA_PWROK,	3,		1,	},  //  ------------step11   delay 40ms  
	{ Hook_SUS_ON,			37,		0,	},	// -----------step6
	{ Hook_FTPOR_ON,	    60,		0,	},  // -------------step12   delay 60ms 
	{ Hook_PCIRST1_ON,		10,		0,	},  // -------------step13   delay 10ms  
	{ Hook_PCIRST23_ON,     20,     0,  },  // -------------step14 system Power on ok  init usb host controller,wifi module
    { Init_PS8625,          0,      0,  },  // -------------init PS8625
	{ PWRLED_ON,            0,      0,  },  // -------------   //lw
	{ S5_S0Variable,		0,		0,	},  // always in the end of tabel
}; 







//-------------------------------------------------------------------------------------
//  Do S5 -> S0 power sequnce
//-------------------------------------------------------------------------------------

/*
const sPowerSEQ code asPowerSEQS5S0[]=  
{
	{ 0x0000,		        0,		0,	},	// Dummy step always in the top of tabel
	{ ALLOW_PowerON,	    5,		0,	},  // start system Power on,delay 5ms ----step1
	{ Hook_PWR_ON,			0,		0,	},  // ---------step2
	{ EC_Read_SB_PWROK,		1,		1,	},  // wait SB Power ok,delay 1ms ---------step3
	{ Hook_MISCPWR_ON,      2,      0,  },  // -----------step4 delay 2ms
	{ Hook_SMIOFF,			0,		0,	},
	{ Hook_SCIOFF,			0,		0,	},
	{ InitSio,				0,		0,	},
	{ Hook_SUS_ON,		    0,		0,	},  // -----------step5
	{ EC_Read_1V8_PWROK,    20,		1,	},  //------------step6
	{ Hook_VCORE_EN_ON,		0,		0,	},  //------------step7 
	{ EC_Read_VCORE_PWROK,  10,		1,	},  // -----------step8 CPU Power
	{ Hook_ECVDDA_ON,	    0,      0,  },  //  ------------step9
	{ EC_Read_VDDA_PWROK,	40,		1,	},  //  ------------step10   delay 40ms  
	{ Hook_FTPOR_ON,	    60,		0,	},  // -------------step12   delay 60ms  
	{ Hook_PCIRST1_ON,		10,		0,	},  // -------------step13   delay 10ms  
	{ Hook_PCIRST23_ON,     20,     0,  },  // -------------step14 system Power on ok  init USB Host Controller,Wifi Module
    { Init_PS8625,          0,      0,  },  // -------------init PS8625
	{ PWRLED_ON,            0,      0,  },  // -------------
	{ S5_S0Variable,		0,		0,	},  // always in the end of tabel
}; 
*/


//-------------------------------------------------------------------------------------
//  Do S0 -> S5 power sequnce
//-------------------------------------------------------------------------------------

const sPowerSEQ code asPowerSEQS0S5[]=  
{ 
    { 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ Hook_PCIRST23_OFF,	10,     0,  },
	{ Hook_PCIRST1_OFF,		10,		0,	},
    { Hook_FTPOR_OFF, 	    10,		0,  },
    { Hook_SUS_OFF, 	    2,		0,  },
	{ Hook_ECVDDA_OFF, 	    0,		0,  },	
	{ Hook_VCORE_EN_OFF,	10,		0,  },
	{ Hook_MISCPWR_OFF,     1,      0,  },
	{ Hook_PWR_OFF, 		100,	0,  },
    { ALLOW_PowerOFF,		2,		0,	},
	{ S0_S5Variable, 	    0,		0,  },  // always in the end of tabel	
}; 







//-----------------------------------------------------------------------------
//  The OEM variable of Sx -> S0
//-----------------------------------------------------------------------------
void OEM_SX_S0CommVar(void)
{
    CheckPowerStateIndex = 0x00;
	DebugFanStatus = 0x00;//Lable:进入S0需要清除风扇调试状态寄存器，避免发生误入debug模式
	SET_MASK(Oem_Device_Status,Wireless_IN);
}

//-----------------------------------------------------------------------------
//  The variable of Sx -> S0 
//-----------------------------------------------------------------------------
void SX_S0CommVar(void)
{
  
	SysPowState=SYSTEM_S0;
	ResetSCIEvent();
#if CIRFuncSupport
	Reset_CIR();
#endif 
	Hook_KBRSTOFF();
    OEM_SX_S0CommVar();
	
    InitSMBus();
	
	Init_Brightness();

	LID_ON();	//lw++
    
    PWRLED_ON(); 

	BT_EN_ON();

	RF_ON();

	BD_EN_ON();

    Sys_Temp_Check_Flag = 0;
	Sys_Temp_Check_Cnt = 0;
	//clear the keyboard led flag
    CLEAR_MASK(Oem_KB_Status,KB_LED);
	
	Sys_Power_Status = (Sys_Power_Status & 0x0f0);

	Oem_Globe_Flag1 |= Oem_Mute_Delay_f;// timebase 500ms 
	Oem_Mute_Delay_Cnt = 6;

	Oem_Globe_Flag1 &= ~Oem_SYSTEM_DeepS3_f;

	if(Oem_RTP_ID_CMD == 0)
	{
      Oem_RTP_ID_LOOP_Index = 0;

	  Oem_RTP_ID_Step = 0;

	  Oem_RTP_ID_1s_EN = 0x01;
	  Oem_RTP_ID_1s_T = 0;
	}

	
	EnterDeepSleep_ACDC_Cnt = 0;
	CLEAR_MASK(EnterDeepSleep_ACDC_f,EnterDeepSleep_ACDC_EN);

	if (IS_MASK_SET(POWER_FLAG1, bat_in)) SET_MASK(SMBus1Flag2, B1_BatFW);
	
    GPCRF7 = OUTPUT;// S0->Sx set as INPUT  

	//DeepSleepCunt = 0x00;
 
}

//-----------------------------------------------------------------------------
// The variable of S5 -> S0
//-----------------------------------------------------------------------------
void S5_S0Variable(void)
{
	SX_S0CommVar();
    S5S0FanInitOn();

}

//-----------------------------------------------------------------------------
//  The OEM variable of S0 -> Sx
//-----------------------------------------------------------------------------
void OEM_S0_SXCommVar(void)
{
	Oem_Globe_Flag1 &= ~Oem_Fn_R;
	OS_mode = 0;
    CheckPowerStateIndex = 0x00;
    CLEAR_MASK(SYS_MISC1,ACPI_OS);
	CLEAR_MASK(Oem_Device_Status,Wireless_IN);
	DebugFanStatus = 0x00;//Lable:进入S0需要清除风扇调试状态寄存器，避免发生误入debug模式
}

//-----------------------------------------------------------------------------
//  The variable of S0 -> Sx
//-----------------------------------------------------------------------------
void S0_SXCommVar(void)
{
#ifdef PECI_Support
    PECI_ClearPSTVariables();
#endif
    
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif

	CLEAR_MASK(KBHISR,SYSF); 
    Ccb42_SYS_FLAG=0;
	Hook_KBRSTON();
	Hook_A20OFF();
	
#if CIRFuncSupport	
	Init_CIR();
#endif
   
    OEM_S0_SXCommVar();	
	
    EVT_STATUS2 &= ~Sys_Shutdown_f; 

	LID_OFF();	// lw++
	 
	PWRLED_OFF();
    
	BT_EN_OFF();

	RF_OFF();

	BD_EN_OFF();

	EC_LAN_OFF(); //lw++
	
	EC_BLT_EN_OFF();//lw++
  	EDP_VDD_OFF();//lw++
  	CAPS_LED_OFF();//lw++
	
	SPCTRL1 = Init_I2EC+0x80;
	
	if(PLLFREQR != PLLFreqSetting03)
	{
		ChangePLLFrequency(PLLFreqSetting03);
	}	

	GPCRF7 = INPUT;	//fixed PROCHOT_EC_N leakage current when s4/s5    
	

}

//-----------------------------------------------------------------------------
//  The variable of S0 -> S5
//-----------------------------------------------------------------------------
void S0_S5Variable(void)
{
    SysPowState=SYSTEM_S5; 

	if(IS_MASK_SET(Oem_For_Bios_Flag,EC_flashed))
	{
		CLEAR_MASK(Oem_For_Bios_Flag,EC_flashed);
		
		BRAM_FLASH_ID0 = 0x55;
		BRAM_FLASH_ID1 = 0xaa;
		BRAM_FLASH_ID2 = 0x55;
		BRAM_FLASH_ID3 = 0xaa;
		
		_nop_();
		_nop_();
		_nop_();
		
		ETWCTRL = 0x10; 	   //EWDCMS  External WDT stop count mode select   1: External WDT can be stopped by setting EWDSCEN bit,	0: External WDT cannot be stopped
		EWDCNTLR = WATCHDOG_COUNTER_2S;//reset ec domain		
		while(1);				// Wait for watch dog time-out
	
	}

    S0_SXCommVar();


}







//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS5S0(void)
{
    if(SystemIsS0)
    {
        return;
    }
    SysPowState=SYSTEM_S5_S0;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;

}

//----------------------------------------------------------------------------
// S5 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S5S0Sequence(void)
{
    if( PowSeqDelay != 0x00 )//1m Sec count base
    {
        PowSeqDelay--; 				
        if ( PowSeqDelay != 0x00 )
        {
            return;
        } 
    }

	while(PWSeqStep<(sizeof(asPowerSEQS5S0)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS5S0[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS5S0[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS5S0[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
			    PWSeqStep++;
			}  
			break;
		}	
	}
}



void DoPowerStatus(void)
{
    BYTE presentstatus;

    presentstatus = (POWER_FLAG2&(SLP_S3_ON+SLP_S4_ON+SLP_S5_ON));
    if(PowerStatusBK != presentstatus)      // To make sure all SLP is checked.
    {
        PowerStatusBK = presentstatus;
        return;
    }
    
	switch(POWER_FLAG2 & (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON)) 
	{
		case 0: 	                        // goto S5
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
             //     Oem_TriggerS0S5(SC_S0SLPOff); 
                    break;
                    
                case SYSTEM_S4 :
                    break;
                    
                case SYSTEM_S3 :
              //    Oem_TriggerS0S5(SC_S3S4SLPOff);    
                    break;           
            }
           	break;

		case (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON): // goto S0
		
		
 			if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))   // no adapter
			{
				if(IS_MASK_SET(BT1_STATUS1, bat_valid))  // battery  in
				{
					if(BAT1_RSOC < 1)                     //  batterty is depleted
					{
                	//	Oem_TriggerS0S5(SC_BATTOOLOW);				
						break;
					}	
					else
					{

					}
				}
				else
					break;							
 			}
			
            switch (SysPowState) 
            {
                case SYSTEM_S3 :
                     
                    break;
                    
                case SYSTEM_S4 :
                     
                    break;
                    
                case SYSTEM_S5 :			             
                    Oem_TriggerS5S0();
                     break;
            }
            break;            

        case (SLP_S4_ON+SLP_S5_ON):             // goto S3 
            switch (SysPowState) 
            {
                case SYSTEM_S0 :						
                    
                    break;
            }
            break;

        case SLP_S5_ON:                         // goto S4
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
					
                    break;
            }
            break;
	}
}

//------------------------------------------------------------------------------
void CheckPowerState(void)
{
    switch(CheckPowerStateIndex)
    {
        case 0:
            CheckPowerStateIndex ++;
            break;

        case 1:
            CheckPowerStateIndex ++;
            break;
            
        case 2:
            CheckPowerStateIndex ++;
            break;

        case 3:
       //     DoPowerStatus(); 
            CheckPowerStateIndex = 0x00;
            break;

        default:
            CheckPowerStateIndex = 0x00;
            break;
    }
}





//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S5(BYTE causecode)
{
    if(SystemIsS5)
    {
        return;
    }
	ShutDnCause = causecode;		// setup shutdown case 
    SysPowState=SYSTEM_S0_S5;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;
}




//-----------------------------------------------------------------
// S0 to S5 sequnce
//-----------------------------------------------------------------
void Oem_S0S5Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

	while(PWSeqStep<(sizeof(asPowerSEQS0S5)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS0S5[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS0S5[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS0S5[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}	
	}  
}


/* ----------------------------------------------------------------------------
 * FUNCTION: check Enter Deep Sleep mode
 *      Timer base : 500 ms
 * ------------------------------------------------------------------------- */
BYTE CheckEnterDeepSleep(void)
{
	BYTE resault;
	resault = 0x00;
    
    if(SystemIsS0)		                        // if system in S0
    {
		BRAM_EnterDeep = 0x11;
		resault = 0x01;
    }	
    if(SystemIsS3)		                        // if system in S3
    {
		BRAM_EnterDeep = 0x33;
		resault = 0x01;
    }

	////lw 201801/23
	if(IS_HT_LED_ON())       // ???????????????
	{
		resault = 0x01;
	}
	// //lw 2018/01/23
	
    if(IS_MASK_SET(POWER_FLAG1,adapter_in))	
    //if(Read_ACIN())		// AC power exist
   // if(IS_MASK_SET(POWER_FLAG1,adapter_in)&&(IS_MASK_SET(BT1_STATUS1,bat_in)))
    {
		BRAM_EnterDeep = 0x22;
		resault = 0x01;	
    }
    if(IS_MASK_SET(POWER_FLAG1,wait_PSW_off))	// power switch pressed
    {
        resault = 0x01;
    }
	
	if(Oem_BatCtrl_F & Oem_BatCapTooLow_NotS0_f)
	{
		resault = 0x01;	
	}
	
	if(IS_MASK_SET(POWER_FLAG1,wait_NovoBtn_off)) //Novo switch pressed
	{
        resault = 0x01;	
    }
    
	if(CoolBootFlag==0x01)  // support LCFC cool boot
	{
		resault = 0x01;	
	}
	
	
	if(resault == 0x00)
	{
		if(DeepSleepCunt<40)        	//lw 2018/01/23  //FROM 20 -> 40		// Delay 500 ms for EC deep sleep mode
		{
			DeepSleepCunt++;
			resault = 0x02;
		}
		else
		{
			resault = 0x00;
			DeepSleepCunt = 0x00;
		}
	}
    else
    {
        DeepSleepCunt = 0x00;
    }

	switch(resault)
	{
		case 0:
			return(1);
			break;

		case 1:
			DeepSleepCunt=0x00;
			return(0);
			break;

		case 2:
			return(0);
			break;
	}
	return(0);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Enter Deep Sleep mode
 * ------------------------------------------------------------------------- */
void EnterDeepSleep(void)
{
	BRAM_EnterDeep1 = 0x88;   

	Oem_Globe_Flag &= ~Oem_AlwaysOn_f;
   

//++++++++++++++++++++++++++++

	IER0=0x00;
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;
	IER5=0x00;   //lw
	IER6=0X00;  //lw	

	IER9=0x00;
	IER13=0X00; //lw

	DisableAllInterrupt();

							// Disable module
	DisableADCChannel();	// Disable ADC
	DACPWRDN=0x3F;			// Disable DAC	

	Change_GpuTemp=TEMP_SPECIAL_VALUE;  //lw 2018/03/02
	Change_LcdTemp=TEMP_SPECIAL_VALUE;	//lw 2018/03/02

//	HOCTL2_A = 0;
//	HOCTL2_B = 0;
//	HOCTL2_C = 0;

	KSOL = 0xFF;
	KSOH1 = 0xFF;
	KSOH2 = 0xFF;
	

	CGCTRL1R = 0xFF;
	CGCTRL2R = 0xFF;
	CGCTRL3R = 0xFF;

 	
	
	//*************************************************************************
		// Set Wake up pin -> alt function
		//*************************************************************************
		//GPCRD0 = ALT; 		// SUSB to alternate pin	
		
		GPCRE4 = ALT;			// pwrsw to alternate pin
		WUEMR2 |= 0x20;
		WUESR2 |= 0x20;			// clear wakeup status
		WUENR2 |= 0x20;      
		ISR1 |= Int_WKO25;		// clear int14 for  pwrsw
		IER1 |= Int_WKO25;		// enable int14 for  pwrsw


	
	    GPCRE5 = ALT;			// NOVO Button to alternate pin  
      	WUEMR4 |= 0x01;         // Wake-up Edge WU40 for NOVO	 
   	    WUESR4 |= 0x01;
	    WUENR4 |= 0x01;         // Wake-up enable WU40 for NOVO Button
	    ISR0 |= Int_WKINTAD; 	//  (Int_WKO20+Int_WKINTAD);     // clear int 1 for  SUSB
   							    // clear int 5 for  NOVO button	
   	    IER0 |= Int_WKINTAD;    //(Int_WKO20+Int_WKINTAD);    // enable int 1 for  SUSB
   							    // enable int 5 for  NOVO button	
   							    
	//*************************************************************************
	// Set WUC interrupt function
	//*************************************************************************
	if(Read_BatIN())        // Battery  in system         
   	{
   		
   	   //GPCRC4 = ALT;		// ACIN to alternate pin 
   	   //GPCRH0 = ALT;       //lw
   	   //WUEMR2 |= 0x04;     //lw
	   //WUESR2 |= 0x04;
	   //WUENR2 |= 0x04;     // Wake-up enable WU22 for acin
       //                       	
       //ISR2 |= Int_WKO22;	// enable int 21 for   ACIN
       //IER2 |= Int_WKO22; // clear int 21 for  ACIN
       //RamDebug(0x54);
       
	   //////////////////
		GPCRH0 = ALT;       //lw
	  //WUEMR6 |= 0x01;
		WUESR6 |= 0x01;
		WUENR6 |= 0x01;

		ISR6 |= Int_WKO60;	// enable int 48 for   ACIN
        IER6 |= Int_WKO60; 
       /////////////////////
			
        
	}
	
     else                   //AC in  system 
	 {	
	 /*
		GPCRD0 = ALT;       //battery in   WU20   INT1 
		WUEMR2 |= 0x01;
		WUESR2 |= 0x01;
		WUENR2 |= 0x01;

		ISR0 |= Int_WKO20;
		IER0 |= Int_WKO20;
       */

		///////////////////lw
		GPCRB5 = ALT;
	
		WUEMR11 |= 0x01;
		WUESR11 |= 0x01;
		WUENR11 |= 0x01;

		ISR13 |= BIT5;
		IER13 |= BIT5;
		/////////////////lw

     }
     
	//Delay1MS(50); 
	
  	
	_nop_();
	_nop_();
   EnableAllInterrupt();

   ///+++
   EC_BLT_EN_OFF(); //lw++
   GPD3_OFF();
   WLAN_PWR_EN_OFF();
   EC_LAN_OFF();
   ///+++

	PLLCTRL = 1;
	
	PCON =2 ;             	// enter sleep mode
    
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();


	
	IER0=0x00;				
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;
	IER6=0X00;//lw
	IER9=0X00;//lw
	IER13=0X00;//lw
	
	
	IER1=0x00;
	ISR1=0xff;
	
	IER2=0x00;
	ISR2=0xff;
	
	IER0=0x00;
	ISR0=0xff;   //clear

//////////////lw
	IER6=0x00;
	ISR6=0xff;

	IER9=0X00;
	ISR9=0XFF;

	IER13=0X00;
	ISR13=0XFF;
///////////////lw	

	WUENR1 = 0x00;	
	WUENR2 = 0x00;	
	WUENR3 = 0x00;	
	WUENR4 = 0x00;   
	WUENR6 = 0x00;//lw
	WUENR7 = 0x00;
	WUENR11 = 0X00;//lw

	

	WUESR1 = 0xff;
	WUESR2 = 0xff;
	WUESR3 = 0xff;
	WUESR4 = 0xff;
	WUESR6 = 0xff;//lw
	WUESR7 = 0xFF;
    WUESR11 = 0xff;//lw
	
		//*************************************************************************
		//
		//************************************************************************* 
	    //GPCRD0 = INPUT; 		// SUSB to alternate pin	
	    //GPCRC4 = INPUT; 		// ACIN to alternate pin
	    GPCRH0 = INPUT;    // lw   ACIN to alternate pin
		GPCRE4 = INPUT; 		// pwrsw to alternate pin
		GPCRE5 = INPUT; 		// NOVO Button to alternate pin  
		//GPCRD0 = INPUT; 		//battery in
		GPCRB5 = INPUT;
		//*************************************************************************

	CGCTRL1R = 0x00;
	CGCTRL2R = 0x00;
	CGCTRL3R = 0x00;


//	HOCTL2_A = 0x01;
//	HOCTL2_B = 0x01;
//	HOCTL2_C = 0x01;

	///+++
   EC_BLT_EN_ON(); //lw 
   GPD3_ON();
   WLAN_PWR_EN_ON();
   EC_LAN_ON();
   ///+++

#if ADCFuncSupport  
	EnableADCChannel();		// enable ADC	
#endif	

	DACPWRDN=0x00;			// enable DAC	
	Enable_Any_Key_Irq();	// Enable Keyboard
	Init_Timers();

	//Delay1MS(10);       //increase delay to Initialize smbus   //lw 2017/12/8

	//lw 2018/03/02
	//lw 2018/01/23
//	PollingTempSensor();    //lw 2018/01/23
//	SMBusCenterSelection(SMbusCh2);  
//	MoniterTemprature();  
	//lw 2018/01/23
	//lw 2018/03/02
}

//-----------------------------------------------------------------------------
// The function of checking HWPG
//-----------------------------------------------------------------------------
void MoniterHWPG(void)
{
    if(SystemIsS0)
    {

    }
}

//----------------------------------------------------------------------------
// EC auto power on function
//----------------------------------------------------------------------------
void CheckAutoS5S0(void)
{

}


//-----------------------------------------------------------------------------
// Handle System Power Control
// Called by service_1mS -> Timer1msEvent -> Hook_Timer1msEvent
//-----------------------------------------------------------------------------
void Oem_SysPowerContrl(void)
{

   // Check if delay doing PowerSeq is needed.
    if ( DelayDoPowerSeq != 0x00 )
    {
        DelayDoPowerSeq--;
        if ( DelayDoPowerSeq != 0x00 )
        {
            return;
        }
    }

    if((SystemIsS0)||(SystemIsS3)||(SystemIsS4)||(SystemIsS5))
    {
      // CheckPowerState();  
        
    }

    // Check current System PowerState to see what should we do.
    switch (SysPowState)
    {
        case SYSTEM_S0: 
			MoniterHWPG();
			break;

        case SYSTEM_S3:			
         	break;

        case SYSTEM_S4:
            break;

        case SYSTEM_S5:
			
            break;

        case SYSTEM_S4_S0:
            
            break;

        case SYSTEM_S5_S0:
			Oem_S5S0Sequence();
			break;
				
        case SYSTEM_S3_S0:
			 
            break;

        case SYSTEM_S0_S3:
			
            break;

        case SYSTEM_S0_S4:
            
            break;

        case SYSTEM_S0_S5:
			Oem_S0S5Sequence();
         	break;

		case SYSTEM_EC_WDTRST:
			InternalWDTNow();
			break;

        default:
         	SysPowState=SYSTEM_S5;
         	break;
    }
}


void CheckResetSource(void)
{
    switch(RSTStatus&0x03)
    {
        case 0:
        case 1:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_ECColdBoot;
				ClearBRam();
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            break;
            
        case 2:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_IntWatchDog;
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            break;         

        case 3:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_ExtWatchDog;
				#if BRAM_Debug
				Copy_BRAM_SRAM();
				#endif				
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            
            break;
    }
}

//-----------------------------------------------------------------------------
// The function of pulsing S.B. power button 
//-----------------------------------------------------------------------------
void PulseSBPowerButton(void)
{
	if(0==SBSWReleaseCunt)      // Prevent continued pull low power signal to chipset
	{
		SBSWReleaseCunt = 20;   // decrease timer base is 10ms total time 200ms
	}
}

//-----------------------------------------------------------------------------
// The function of releasing S.B. power button  10ms
//-----------------------------------------------------------------------------
void CheckSBPowerButton(void)
{
	if(SBSWReleaseCunt!=0x00)
	{
		SBSWReleaseCunt--;
		if((SBSWReleaseCunt==0x00)&& (PSW_COUNTER == 0x00))
		{
			 
		}
	}
}

// For support LCFC cool boot tool
void CoolBootFun(void)
{
	if(CoolBootTime>0)
	{
		CoolBootTime--;
	}
	else
	{
		CoolBootFlag = 0;
		
		Delay1MS(10);
		PulseSBPowerButton();
	}
}



