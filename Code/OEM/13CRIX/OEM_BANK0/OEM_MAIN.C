/*-----------------------------------------------------------------------------
 * TITLE: OEM_MAIN.C - OEM specific code
 *
 * Some "HOOKS" from CHIPHOOK.C are copied into this file in order to replace
 * (or augment) core functions.
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

void Oem_Hook_Timer1ms(void)
{
	if(IS_MASK_SET(OS_mode,OS_mode_flag))
	{
		SET_MASK(SYS_MISC1,ACPI_OS);
		CLEAR_MASK(Oem_Globe_Flag1,Oem_Fn_R); 
	}
	else
	{
		CLEAR_MASK(SYS_MISC1,ACPI_OS); 
	}
	#ifdef UART_Debug
	if(TI)	
		get_char_uart();
	#endif
}

//------------------------------------------------------------
// Hook 1ms events
// EventId is 0 ~ 9 cycle
//------------------------------------------------------------
void Hook_Timer1msEvent(IBYTE EventId)
{
    #if MailBoxRWECRam
    HandleMailBox();
    #endif
	
    EventManager(EventId); // Polling system event
    Oem_SysPowerContrl();  // System Power Control

	if (IS_MASK_CLEAR(SYS_MISC1, BAT_FW_UP))
	{	
    	SMBusCenter();
	}
	 
	Oem_Hook_Timer1ms();
 
    Check_PanelInit();     // check if the panel need init
    
}


void Oem_Hook_Timer5ms(void)
{

	if (EC_EXT_CMD) EXT_EC_CMD();


	if((OemAllDevices_state & Post_Over_f) != 0)    //post over
	{
		OemAllDevices_state &= ~Post_Over_f;	
		
		Device_Status_Lenovo |= TouchPad_S_B;
		Device_Status_Lenovo |= Inverter_S_B;

		Oem_Device_Status    |= TouchPad_IN;
		Oem_Device_Status    |= Inverter_IN;
	}
}

//------------------------------------------------------------
// Hook 5ms events
//------------------------------------------------------------
void Hook_Timer5msEvent(void)
{

	Read_TP_ID();

    #if ADCFuncSupport  
	ScanADCFixChannel();
	LCD_OS_Heating_Service();
    #endif

	#ifdef PECI_Support
    PECI_PowerCtrlCenter();
    #endif

    #ifdef PMC3_Support
    if(SystemIsS0)
    {
        PECI_SendBufferData();
    }
    #endif

    #if ACPI_QEventPending
    Get_PendingECQEvent();
    #endif
	
	Oem_Hook_Timer5ms();


}

//------------------------------------------------------------
// Hook 10ms events
//------------------------------------------------------------
void Hook_Timer10msEventA(void)
{
    #if ADCFuncSupport 
    ScanADCDyChannel1();
    #endif

    #if BAT1FuncSupport
	
 	if (IS_MASK_CLEAR(SYS_MISC1, BAT_FW_UP))
 	{	
    	Battey1ControlCenter();
 	}

	#endif

	#if FWUSupport
	if (SystemIsS0) 
	{
		Battey1FrimUp();
	}
	#endif 

	Setup_Brightness(LCD_BRIGHTNESS);    // //<<lw 2017/12/6  ++
}

//------------------------------------------------------------
// Hook 10ms events
//------------------------------------------------------------
void Hook_Timer10msEventB(void)
{  
    	Check_SysShutDown();     	
		Check_SysReset();  
    	CheckSBPowerButton();
	
    #if ADCFuncSupport 
    ScanADCDyChannel2();
    #endif
	
	if(IS_MASK_SET(Oem_Globe_Flag2,Oem_Brightness_Make))
	{
		if(AdjustBLDelay>0)
		{
		  AdjustBLDelay--;
		}
	}
	else
	{
		AdjustBLDelay=0;
	}
}

//------------------------------------------------------------
// Hook 50ms events A
//------------------------------------------------------------
void Hook_Timer50msEventA(void)
{
	if (Read_LPCRST())
	{
		if (IS_MASK_CLEAR(Device_Status_AllRF, LPCRST_F))
		{
			SET_MASK (Device_Status_AllRF, LPCRST_F);
		}
	}
	else
	{
		CLEAR_MASK(Device_Status_AllRF, LPCRST_F);
	}
}

//------------------------------------------------------------
// Hook 50ms events B
//------------------------------------------------------------
void Hook_Timer50msEventB(void)
{

    //Check Enter Ship mode for battery (battery_off)
	if (Bat_ShipMode_Cmd == 0x01)
	{	
		Bat_ShipMode_Data_L = 0x00;
		Bat_ShipMode_Data_H = 0x00;
		SET_MASK(SYS_MISC1, Bat1_Firm_En);
		SET_MASK(SYS_MISC1, BAT_FW_UP);		// disable smbus communication
		
		if (bRWSMBus(SMbusCh1, SMbusWW, 0x16, 0x34, &Bat_ShipMode_Data_L, SMBus_NeedPEC))		// write 0x0000 to 0x34
		{
			Bat_ShipMode_Data_H = 0x10;
			if (bRWSMBus(SMbusCh1, SMbusWW, 0x16, 0x34, &Bat_ShipMode_Data_L, SMBus_NeedPEC))		//write 0x1000 to 0x34
			{
				if (bRWSMBus(SMbusCh1, SMbusRW, 0x16, 0x34, &Bat_ShipMode_Data_L, SMBus_NoPEC))			//read data from 0x34
				{
					if (Bat_ShipMode_Data_L==0x00 && Bat_ShipMode_Data_H==0x01)					// return 0x0100, ship mode done!
						Bat_ShipMode_Cmd = 0x02;
				}
			}
		}
	}
}

//------------------------------------------------------------
// Hook 50ms events C
//------------------------------------------------------------
void Hook_Timer50msEventC(void)
{
    
}

//------------------------------------------------------------
// Hook 100ms events A
//------------------------------------------------------------
void Hook_Timer100msEventA(void)
{

}


//------------------------------------------------------------
// Hook 100ms events B
//------------------------------------------------------------
void Hook_Timer100msEventB(void)
{


	 SetBatLed();    

	BT1_ALARM_STATUS = (BAT1_ALARM1 << 8) | BAT1_ALARM2;	


	if(OS_PM_STATE&OS_AC_IN) // AC plug in
	{
		if(((BAT1_current_H== 0)&& (BAT1_current_L < 0x10)) || ((BAT1_current_H== 0xFF)&&(0xF0==(BAT1_current_L&0xF0))))  //Charge current is very small
		{
			B1SS = 0;
		}
		else if(IS_MASK_SET(BIOS_OEM_battery_health,HOST_BAT_Authentication))   //Charge current is not small , and  Battery is Authentication
		{
			B1SS = BAT_charge_f;
		}	
	}
	else
	{
		B1SS = BAT_discharge_f;    // AC  plug out
	}



	if(B1SS_Bak != B1SS)
	{
		B1SS_Bak = B1SS;

		if(OS_mode !=0)
			ECQEvent(BAT1_STATUS_EVT,SCIMode_Normal);		
	}
	
}

//------------------------------------------------------------
// Hook 100ms events C
//------------------------------------------------------------
void Hook_Timer100msEventC(void)
{
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))			//System in ACPI Mode
	{
		if (ACPI_OS_Delay_Count < 20)
		{
			if (ACPI_OS_Delay_Count == 10)
			{
				Device_Status_Lenovo |= TouchPad_S_B;
				Device_Status_Lenovo |= Inverter_S_B;

				Oem_Device_Status |= TouchPad_IN;
				Oem_Device_Status |= Inverter_IN;
				
				TurnOnOffWlan();
				TurnOnOffBT();
			}
			ACPI_OS_Delay_Count ++;
		}
	}
	else
	{
		ACPI_OS_Delay_Count = 0;
	}
	
	#ifdef SUPPORT_KB_MATRIX_ID1
	if (KeyboardID != KeyboardMatrixID)
	{
		KeyboardID = KeyboardMatrixID;
		Hook_Setup_Scanner_Pntr();
	}
	#endif

#if SmartFanSupport
	if(SystemIsS0)
	{
	   FanManager();
	}
	else
	{
	  GPUFanFullOff();
	  CPUFanFullOff();
	}
#endif


}

//------------------------------------------------------------
// Hook 500ms events A
//------------------------------------------------------------
void Hook_Timer500msEventA(void)
{
    #if ECSleepModeSupport
       if(CheckEnterDeepSleep())
   	   {
	       EnterDeepSleep();

		   EnterDeepSleep_ACDC_Cnt = 0;
		   CLEAR_MASK(EnterDeepSleep_ACDC_f,EnterDeepSleep_ACDC_EN);
    	}
	#endif

	#if OEM_GPU_ITS_SUPPORT
	CheckGPUInitok();
	#endif

    #if SmartFanSupport
    if(SystemIsS0)
    {
        CheckFanRPM();
	}
    #endif
	



}

//------------------------------------------------------------
// Hook 500ms events B
//------------------------------------------------------------
void Hook_Timer500msEventB(void)
{
    if(IS_MASK_SET(Oem_TP_Status,TP_ON_OFF))
    {
      CLEAR_MASK(Device_Status_Lenovo,TouchPad_S_B);
      CLEAR_MASK(Device_Status_Lenovo,TouchPad_IN);
      Hook_DisablePS2Port_2();
    }
}

//------------------------------------------------------------
// Hook 500ms events C
//------------------------------------------------------------
void Hook_Timer500msEventC(void)
{
   	if(Oem_PC_Beep_EN)     // if beep disable ,return.
   	{
		PC_BEEP_PWM=0x20;
		Oem_PC_Beep_EN=0;
	}
	else
	{
		PC_BEEP_PWM=0x00;
	}

	if(Oem_Globe_Flag1 & Oem_Mute_Delay_f)
	{
		Oem_Mute_Delay_Cnt--;
		if(Oem_Mute_Delay_Cnt == 0)
		{
			Oem_Globe_Flag1 &= ~Oem_Mute_Delay_f;
			EC_VOLMUTE_OFF(); 	
		}
	}
	
	if(OS_Type==3)
	{
		if((IS_MASK_SET(Oem_Globe_Flag2,Oem_F8_Make_f))&&(IS_MASK_SET(Oem_Globe_Flag2,Oem_F8C_Make_f)))
		{
			Buffer_Key(0x0D);   // Tab
			Buffer_Key(0xF0);   // Tab         break code
			Buffer_Key(0x0D);
		}		
	}
	else
	{
		if(IS_MASK_SET(Oem_Globe_Flag2,Oem_F8_Make_f))
		{
			Buffer_Key(0x0D);   // Tab
			Buffer_Key(0xF0);   // Tab         break code
			Buffer_Key(0x0D);
		}
	
	}
	if(IS_MASK_SET(Oem_Globe_Flag2,Oem_F10_Make_f))
	{
		if(IS_MASK_SET(Oem_Globe_Flag2,Oem_F10_Make_count))
		{
			Buffer_Key(0x4d);	 // P make code,  scan code set 2
			Buffer_Key(0x99);    //p break,  scan code set 1
		}
		if(IS_MASK_CLEAR(Oem_Globe_Flag2,Oem_F10_Make_count))
		{
			SET_MASK(Oem_Globe_Flag2,Oem_F10_Make_count);
		}
	}		

	EC_Wakeup_Check_Temperature();  //lw 2018/03/02

   // Sys_Temp_Check();   //lw--
    
     ////////////lw++   from 1sec B
 if(IS_MASK_SET(ThermalSensorStatus,ThermalSensorIn))//check if the thermal senser exist
  {
    PollingTempSensor(); 
  }
///////////lw++
	
}

//------------------------------------------------------------
// Hook 1sec events A
//------------------------------------------------------------
void Hook_Timer1SecEventA(void)
{ 


   
	#if Lenovo_Support

	if(BIOS_OEM_battery_health&HOST_BAT_LIFE_TEST_MODE)
	{
		BIOS_OEM_battery_health&=~HOST_BAT_LIFE_TEST_MODE;

		Bat_Test_Mode_f = 1;//close led except power led and change thermal table
	}	
	
	Lenovo_Battery_Health();
	#endif 

	
    MoniterTemprature();    

	

    #if LEDFuncSupport
    ProcessLED();
    #endif
	
    #ifdef PECI_Support
    if(SystemIsS0)
    {
        #if ReadDRAMTemperature
        PECI_ReadDRAMTemperature();
        #endif
    }

	if(SystemIsS0)
    {
		PECI_CalculatePkgPower();
		
		if(BIOS_OEM_battery_health&HOST_Auto_mode_f)
			{
				if(PECI_PkgPower<100)
				{
					PECI_PkgPower_average_count++;
					PECI_PkgPower_average+=PECI_PkgPower;
				}
		
				
				if(20==PECI_PkgPower_average_count)
				{
					PECI_PkgPower_average=PECI_PkgPower_average/20;
					
					if(0==(Lenvo_general_f&auto_mode_f))
					{
						if(PECI_PkgPower_average<13)//6.5w 
							Auto_NOTIFY_EM(1);
						else
							Auto_NOTIFY_EM(0);	
					}else
					{
						if(PECI_PkgPower_average>6)//3w 
							Auto_NOTIFY_EM(0);
						else
							Auto_NOTIFY_EM(1);	
					}
					PECI_PkgPower_average_count=0;
					PECI_PkgPower_average=0;
				}
			 }
			else
			{
					PECI_PkgPower_average_count=0;
					PECI_PkgPower_average=0;
					Lenvo_general_f&=~auto_mode_f;
			}
	}
    #endif
	
	if ((SystemIsS4 || SystemIsS5) && 
		(BAT1_CtrlStep == BAT_Step_FullyChg) &&
		IS_MASK_SET(BT1_STATUS1, adapter_in) &&
		IS_MASK_SET(POWER_FLAG1, bat_in))
	{
		EnterDeepSleep_ACDC_Cnt++;

		if(EnterDeepSleep_ACDC_Cnt >= 120)
		{
			SET_MASK(EnterDeepSleep_ACDC_f,EnterDeepSleep_ACDC_EN);
			EnterDeepSleep_ACDC_Cnt = 0;
		}
	}
	else
	{
		EnterDeepSleep_ACDC_Cnt = 0;
		CLEAR_MASK(EnterDeepSleep_ACDC_f,EnterDeepSleep_ACDC_EN);
	}

    Heating_Service();//add low tempreture heat //mark for battery debug    

	Check_ComPort();
}

//------------------------------------------------------------
// Hook 1sec events B
//-------------------------- ----------------------------------
void Hook_Timer1SecEventB(void)
{
   if(SystemIsS0)
   {
	   Check_Shutdown_cnt ++;
       if(Check_Shutdown_cnt>5)
       {
         Check_Shutdown_cnt =0;
		 EVT_STATUS2 |= Sys_Shutdown_f;
		 EVT_STATUS2 |= Sys_ResetPowerOn_f;  //÷√Œª
       }   
   }
	
   if(EVT_STATUS2 & Sys_ResetPowerOff_f)
   {
     Check_Reset_cnt++;
	 if(Check_Reset_cnt>5)
	 {
       Oem_TriggerS5S0();
       EVT_STATUS2 &= ~Sys_ResetPowerOff_f;
	   Check_Reset_cnt = 0;
	 }
   }

   if(EVT_STATUS2 & Sys_DelayShutdown_f)
   {
     Check_DelayShutdown_cnt++;
     if(Check_DelayShutdown_cnt>5)
     {     
       Oem_TriggerS0S5(SC_S0SLPOff);
	   EVT_STATUS2 &= ~Sys_DelayShutdown_f;
       Check_DelayShutdown_cnt = 0;
	 }
   }


   
/////////////lw--
 // if(IS_MASK_SET(ThermalSensorStatus,ThermalSensorIn))//check if the thermal senser exist
 // {
//     PollingTempSensor();
//  }
  /////////////lw--
}

//------------------------------------------------------------
// Hook 1sec events C
//------------------------------------------------------------
void Hook_Timer1SecEventC(void)
{
	WORD tmp1, tmp2;
    #ifdef PECI_Support
    if(SystemIsS0)
    {
        #if ReadPKGTemperature
        PECI_ReadPkgTemperature();
        #endif
    }
    #endif
    
    #if GetSysTempSupport
    ReadSysTemp();
    #endif

    if(SystemIsS0)
    {
    	
		if(DebugECFlash == 0x88)
			Oem_Bios_Interface_1 = 0x07;
		else
		{
			if((OS_PM_STATE & OS_AC_IN)!=0)
			{
				Oem_Bios_Interface_1 |= Biosflash_AC_IN;
			}
			else
			{
				Oem_Bios_Interface_1 &= ~Biosflash_AC_IN;
			}
					
			if((OS_PM_STATE & OS_BAT1_IN) != 0)
			{
				Oem_Bios_Interface_1 |=Biosflash_DC_IN;
			}
			else
			{
				Oem_Bios_Interface_1 &= ~Biosflash_DC_IN;
			}						
			
			if(BAT1_RSOC>30)
			{
				Oem_Bios_Interface_1 |= Biosflash_BatCap_30;
			}
			else
			{
				Oem_Bios_Interface_1 &= ~Biosflash_BatCap_30;
			}

		}
		// In S0, when the battery RMcapacity is not 100% or 0%,
		// every 1% increase or decrease in capacity, then send a event(capactiy info)
		if(IS_MASK_SET(BT1_STATUS1, bat_valid))
		{
			tmp1 = (Host_BAT1_RMcap_H<<8) + Host_BAT1_RMcap_L;
			if(0 != tmp1)
			{
				tmp2 = (BAT1_RMcap_H<<8) + BAT1_RMcap_L;
				if(IS_MASK_SET(BAT1_current_H, BIT7))//--------Discharge current is negative
				{
					if(tmp1 > tmp2)
					{
						ECQEvent(BAT1_STATUS_EVT, SCIMode_Normal);
					}
				}
				else//---------------------------------------------Charging current is positive
				{
					if(tmp1 < tmp2)
					{
						ECQEvent(BAT1_STATUS_EVT, SCIMode_Normal);
					}
				}
			}
		}

    }



}

//------------------------------------------------------------
// Hook1min events
//------------------------------------------------------------
void Hook_Timer1MinEvent(void)
{	
}

//------------------------------------------------------------
// service_OEM_1
//------------------------------------------------------------
void service_OEM_1(void)
{

}

//------------------------------------------------------------
// service_OEM_2
//------------------------------------------------------------
void service_OEM_2(void)
{

}

//------------------------------------------------------------
// service_OEM_3
//------------------------------------------------------------
void service_OEM_3(void)
{

}

//------------------------------------------------------------
// service_OEM_4
//------------------------------------------------------------
void service_OEM_4(void)
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_H(void) 
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_L(void) 
{

}

//------------------------------------------------------------
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//------------------------------------------------------------
BYTE Hook_Only_Timer1msEvent(void)
{
    if((SysPowState==SYSTEM_S5_S0)||(SysPowState==SYSTEM_S4_S0)||(SysPowState==SYSTEM_S3_S0))
    {
        if(++PowerOnWDT >4400)  // > 4.4 sec
        {
            PowerOnWDT = 0x00;
            Oem_TriggerS0S5(SC_PowerOnWatchDog);
			
        }
        return(Only_Timer1msEvent);
    }
    else
    {
        PowerOnWDT = 0x00;
    }
    
    #if PowerSequnceOnly    
    return(Only_Timer1msEvent);
    #endif

// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
    return(All_TimerEvent);
}

//----------------------------------------------------------------------------
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc function, don't change anything.
//----------------------------------------------------------------------------
BYTE OEM_SkipMainServiceFunc(void)
{
// Return :
    return(Normal_MainService);
}


void Sys_Temp_Check(void)
{

  if(SystemIsS0)
  {
      if(Sys_Temp_Check_Flag == 0)
      {
         Sys_Temp_Check_Cnt++;
	     if(Sys_Temp_Check_Cnt == 10)
	     {
	       Sys_Temp_Check_Cnt = 0; 
           Sys_Temp_Check_Flag = 1;
           Cpu_Tmp_Temp = Cpu_Temp_H;//≥ı º÷µ
           Gpu_Tmp_Temp = Gpu_Temp_H;
	     }
     }
}

}









