/*-----------------------------------------------------------------------------
 * TITLE: OEM_EVENT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


void Auto_NOTIFY_EM(BYTE adata)
{
	VPC_Lenovo|=Genenal_Bit_vpc;
	
	if(adata)
	{
		Lenvo_general_f|=auto_mode_f;
	}
	else
	{
		Lenvo_general_f&=~auto_mode_f;
	}
	 
}
void Check_notify_em(void)
{
	if(Device_Status_AllRF&Super_performance_F)
	{
		VPC_Lenovo|=Genenal_Bit_vpc;
		Lenvo_general_f|=super_temp_f; 
	}
}

//-----------------------------------------------------------------------------
// no change function

//-----------------------------------------------------------------------------
void NullEvent(void)
{

}

//-----------------------------------------------------------------------------
// Adapter in function
//-----------------------------------------------------------------------------
void AdapterIn(void) //Lable:remove adapter plug in smart charger smbus reset  2017-5-10
{

	SET_MASK(OS_PM_STATE,OS_AC_IN);
	
	Adpater_Status = NORMAL_ADAPTER;
   //////////lw--
   /*
	DisableAllInterrupt();
	ResetSMBus(SmartChargerChannel);
	EnableAllInterrupt();
	*/
	if(IS_MASK_SET(OS_PM_STATE,OS_BAT1_IN))
	{
	  SetBAT1CtrlStep(BAT_Step_ID);
	  B1SS = BAT_charge_f;
	}

	//ECQEvent(AC_HOT_PLUG_EVT,SCIMode_Normal);  //lw
	 
	if((OemAllDevices_state&Beep_Disable)==0)     // if beep disable ,return.
	{
		if(OS_PM_STATE & OS_BAT1_IN)
		{
			Oem_PC_Beep_EN=1;
		}
	}
}

//-----------------------------------------------------------------------------
// Adapter out function
//-----------------------------------------------------------------------------
void AdapterOut(void)
{
	CLEAR_MASK(OS_PM_STATE,OS_AC_IN);

	B1SS = BAT_discharge_f;
	if((OemAllDevices_state&Beep_Disable)==0)     // if beep disable ,return.
	{
		Oem_PC_Beep_EN=1;
	}
	// ECQEvent(AC_HOT_PLUG_EVT,SCIMode_Normal);  //lw
}

void RecoveryStartUpMode(void)
{
    SET_MASK(SYS_MISC2,Sys_WorkMode);//recovery work mode
    if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))
    {
	    if(IS_MASK_SET(BT1_STATUS1, bat_valid))
	    {
		   if(BAT1_RSOC<=1)
		   {
			  if((Sys_Power_Status & 0x7f) == 0x03)
			  {
				Sys_Power_Status = (Sys_Power_Status & 0x0f0);  // enter really s5
			  }
			  Oem_BatCtrl_F |= Oem_BatCapTooLow_NotS0_f;
			  Oem_BatLedBlink_Cnt = 7;
			  return;
		   }
		   else
		   {
			  Oem_TriggerS5S0();
			  Oem_Globe_Flag1 |= Oem_PCHBTN_En;
		   }	
	   }
	   else
	   {
		   return;
	   }
   }
   else
   {
	  Oem_TriggerS5S0();
	  Oem_Globe_Flag1 |= Oem_PCHBTN_En;
   }
   if(CrisisKeyStatus != 0 )
   {
	  Oem_Globe_Flag1 |= Oem_Fn_R;
   }
   else
   {
      Oem_Globe_Flag1 &= ~Oem_Fn_R;
   }
}





//-----------------------------------------------------------------------------
//power button was pressed
//-----------------------------------------------------------------------------
void PSWPressed(void)
{  
   BYTE temp =0;
   PSW_COUNTER = T_PSWPAUSE;  // initialize counter

   switch(SysPowState)
   {
     case SYSTEM_S4: 
	 case SYSTEM_S5:

	 	ComCheckflag = 1;
	 	temp = Check_Low_Temperature(); 
		if(temp==0)
			 Oem_TriggerS5S0(); 
		else if(temp==1)
			 Heatingfilm_PowerON();
		   break;
	 case SYSTEM_S0:
	 	  ComMoniterflag = 0;
	 	  Oem_TriggerS0S5(SC_S0SLPOff); 
	      break; 
	  default:
	  	break;
   } 
	
}


//-----------------------------------------------------------------------------
//power button was released 
//-----------------------------------------------------------------------------
void PSWReleased(void)
{ 
}

//-----------------------------------------------------------------------------
//power button was overrided (press or release)   10ms time base
//-----------------------------------------------------------------------------
void PSWOverrided(void)
{


}

//-----------------------------------------------------------------------------
//Novo button was pressed
//-----------------------------------------------------------------------------
void NovoPressed(void)
{

    switch (SysPowState)
    {
        case SYSTEM_S5 :
			PulseSBPowerButton();
			OemNoVokeyFlag  |= Novo_Bit_vpc;
			Oem_Globe_Flag1 |= Oem_Novo_Bit_f;
            RecoveryStartUpMode();
			break;
		case SYSTEM_S4 :
			if(OS_Type == 16)
			{
				PulseSBPowerButton();
				OemNoVokeyFlag |= Novo_Bit_vpc; 
				Oem_Globe_Flag1 |= Oem_Novo_Bit_f;
			}
			break;
				
		case SYSTEM_S0 :
			VPC_Lenovo |= Novo_Bit_vpc; 		
			ECQEvent(0x44,SCIMode_Normal);
			break;

		default :
			break;
	}
}


//-----------------------------------------------------------------------------
//Novo button was released
//-----------------------------------------------------------------------------
void NovoReleased(void)
{
	if(SystemIsS0)
	{
		//Label:BLD_TIPIA_20161017_016
		// For LCFC Novo button test tool
		Buffer_Key(0xE0);	 // Break code,  scan code set 1
		Buffer_Key(0xB4);
	}
}

//-----------------------------------------------------------------------------
// battery 1 in function
//-----------------------------------------------------------------------------
void Battery1In(void)  // Lable:remove battery plug in smart battery smbus reset  2017-5-10
{
	Bat_ShipMode_Cmd = 0;   // battery ship mode check
	
	SET_MASK(OS_PM_STATE,OS_BAT1_IN);
    BAT1_FailCause = 0x00;
	
    DisableAllInterrupt();
	ResetSMBus(SmartChargerChannel);
	EnableAllInterrupt();
	
	SetBAT1CtrlStep(BAT_Step_ID);

	SET_MASK(BT1_STATUS1,Bat1_In_Event);
	
	SET_MASK(SMBus1Flag2, B1_BatFW);
	
	SET_MASK(SMBus1Flag2, B1_MaftName);
}

//-----------------------------------------------------------------------------
// battery 1 out function
//-----------------------------------------------------------------------------
void Battery1Out(void)
{
	BYTE i;
	CLEAR_MASK(OS_PM_STATE,OS_BAT1_IN);
	
    BAT1_PlugOutClrVariables();
	
    SetBAT1CtrlStep(BAT_Step_Out);
	
	//ECQEvent(BAT1_HOT_PLUG_EVT,SCIMode_Normal);

	//clear battery firmware version info
	for (i=0; i<8; i++)
		Bat1_FW[i]=0;
    for (i=0; i<8; i++)
		Bat1_MaftName[i]=0;

	DisableAllInterrupt();
	ResetSMBus(SmartChargerChannel);
	EnableAllInterrupt();
	
}

//-----------------------------------------------------------------------------
// LID  close
//-----------------------------------------------------------------------------

void LID_CLOSE(void)
{
	SET_MASK(EC_EXT_SOURCE_STATE,LID_CLOSE_Act);
	LID_OFF();
	if(SysPowState == SYSTEM_S0)
	{   
	  Device_Status_Lenovo &= ~Inverter_S_B;
	  BackLight_OFF(Oem_EC_BLK); 
	}
}

//-----------------------------------------------------------------------------
// LID  close
//-----------------------------------------------------------------------------
void LID_OPEN(void)
{
	EC_EXT_SOURCE_STATE &= ~LID_CLOSE_Act;
	LID_ON();	
	if(SysPowState == SYSTEM_S0)
	{
	  Device_Status_Lenovo |= Inverter_S_B;
	  BackLight_ON(Oem_EC_BLK);
	}
}

//-----------------------------------------------------------------------------
// HDD destroy   
//-----------------------------------------------------------------------------

void Check_Hdd_Destroy(void)
{

}

void Check_Kill_Hdd(void)
{
    
}
void DelPressed(void)
{


}

 
void Check_SysShutDown(void)
{
  if(EVT_STATUS2 & Sys_Shutdown_f)
  {
    if((Read_SysShutdown())&&(!Read_SysReset()))
    { 
    Oem_TriggerS0S5(SC_S0SLPOff);//lw++
   //  EVT_STATUS2 |= Sys_DelayShutdown_f;
	   ComMoniterflag = 0;
	}
	
	EVT_STATUS2 &= ~Sys_Shutdown_f;
     
  }
 
}

void Check_SysReset(void)
{
    if(EVT_STATUS2 & Sys_ResetPowerOn_f)
    {
      if((!Read_SysShutdown())&&(Read_SysReset()))
      {
        Oem_TriggerS0S5(SC_S0SLPOff);
        EVT_STATUS2 |= Sys_ResetPowerOff_f;
		ComCheckflag = 2;  //system reboot 
	  } 
	  
	  EVT_STATUS2 &= ~Sys_ResetPowerOn_f;//Çå³ýÖÃÎ»
 	  
	} 
}


void Check_PanelInit(void)
{
    if(SysPowState==SYSTEM_S0 || SysPowState==SYSTEM_S5_S0)
    {
       if(Read_EDP_HPD_L())
       {
           if(!PanelInitFlag)
           {
             PanelInit_COUNTER++;
	         if(PanelInit_COUNTER==25)//25ms
	         { 
	            LCD_BRIGHTNESS = 5;
	            Setup_Brightness(LCD_BRIGHTNESS);
	         }
             if(PanelInit_COUNTER==70)//70ms
             {
               EDP_VDD_ON();
             }
	         if(PanelInit_COUNTER==332)//332ms
	         {
	           PanelInitFlag = 1 ;
               PanelInit_COUNTER = 0;
		       EC_BLT_EN_ON();
	         }
          }
       }
	}
	else
	{
        PanelInitFlag = 0;
		PanelInit_COUNTER = 0;
	}
}

void Check_ComPort(void)
{
    if((ComCheckflag==1)||(ComCheckflag==2))//power on/system reboot/system shut down
    {
      ComMoniterflag = 0;
      ComCheckCnt++;
	  if(ComCheckCnt >=10)
	  {
	    ComMoniterflag = 1;
		ComCheckCnt = 0;
		ComCheckflag = 0;
	  }
	}
	if(ComMoniterflag==1)//process system reboot/power on
	{
	   if(Read_ComStatus())
       {
          GPD3_ON();
	   }
	   else
	   {
		  GPD3_OFF();
	   }
    }
}

// ----------------------------------------------------------------------------
// Device insert/remove debounce routine.
// input:   device_id
// ----------------------------------------------------------------------------
const struct sDebounce code Debounce_TBL[] = 
{
/*0*/   {&POWER_FLAG1	,wait_PSW_off		,&DEBOUNCE_CONT1	,T_PSW_DEBOUNCE	        ,PSWPressed,   PSWReleased	, PSWOverrided	},	
/*1*/	{&POWER_FLAG1	,adapter_in			,&DEBOUNCE_CONT2 	,T_AC_DEBOUNCE		    ,AdapterIn,    AdapterOut	, NullEvent	    },	
/*2*/	{&BT1_STATUS1	,bat_in				,&DEBOUNCE_CONT3 	,T_BAT_DEBOUNCE	        ,Battery1In,   Battery1Out	, NullEvent		},	
/*3*/	{&EVT_STATUS1	,Lid_close_f		,&DEBOUNCE_CONT4 	,T_LID_DEBOUNCE         ,LID_CLOSE,    LID_OPEN     , NullEvent     },	  
/*4*/	{&POWER_FLAG1	,wait_NovoBtn_off	,&DEBOUNCE_CONT5 	,T_PSW_DEBOUNCE		    ,NovoPressed,  NovoReleased , NullEvent		},     
/*5*/	{&EVT_STATUS1	,DelKey_f			,&DEBOUNCE_CONT6 	,T_10ms_DEBOUNCE	    ,DelPressed,   NullEvent	, NullEvent		},
/*6*/   {&EVT_STATUS1	,Read_VOLUME_DOWN_f	,&DEBOUNCE_CONT7 	,T_10ms_DEBOUNCE	    ,NullEvent,    NullEvent	, NullEvent		},
/*7*/   {&EVT_STATUS1	,Read_VOLUME_UP_f	,&DEBOUNCE_CONT8 	,T_10ms_DEBOUNCE	    ,NullEvent,    NullEvent	, NullEvent		},
/*8*/	{&EVT_STATUS1	,Home_Key_f	        ,&DEBOUNCE_CONT9	,T_10ms_DEBOUNCE		,NullEvent,    NullEvent    , NullEvent     },
/*9*/   {&EVT_STATUS1	,Read_KillHdd_f	    ,&DEBOUNCE_CONT10   ,T_10ms_DEBOUNCE		,Check_Hdd_Destroy, NullEvent , NullEvent   },
};  
// ----------------------------------------------------------------------------
// EventManager function
//
// Note : 
//	If want to call the function of status not change, please set nochange_func = 1    base time 1ms
// ----------------------------------------------------------------------------
#pragma OT(8, SPEED)
void EventManager(BYTE device_id) 
{
	BYTE new_state,old_state;
	BYTE device_flag;
    
	switch(device_id)	
	{
		case 0 :							
			new_state = Read_PWRSW();   // power button
			break;
		case 1:     							
			new_state = Read_ACIN();   // AC
			break;	
		case 2 :
			new_state = Read_BatIN();  // battery plug in
			break;
			
		case 3 :
			new_state = Read_MXLID();  // Lid
			break;
			
		case 4 :
			new_state = Read_RECOVER_BT();// recovery button
			break;
			
		case 5 :
			new_state = 0x00; 
			break;  
		case 6:
			new_state = 0x00;
			break;
		case 7:
			new_state = 0x00;
			break;
		case 8:
			new_state = 0x00;
			break;
		case 9:
			new_state = 0x00;
			break;
		default:
			new_state = 0x00;
			break;
	}

	Tmp_XPntr = Debounce_TBL[device_id].REG;
	Tmp_XPntr1 = Debounce_TBL[device_id].Cunter;
	device_flag = Debounce_TBL[device_id].Flag;

	old_state = ((*Tmp_XPntr & device_flag) != 0x00);
	if(new_state != old_state)
	{		 
		if((*Tmp_XPntr1) == 0x00)	
		{	
			(*Tmp_XPntr1) = Debounce_TBL[device_id].Time;	
		}	 
		else 
		{	
			(*Tmp_XPntr1) --;  //Keys away shaking
			if((*Tmp_XPntr1) == 0)	
			{	 
				if(new_state)
				{	
					(Debounce_TBL[device_id].press)();
					SET_MASK(*Tmp_XPntr,device_flag);
				}
				else 
				{	
					(Debounce_TBL[device_id].release)();
					CLEAR_MASK(*Tmp_XPntr,device_flag);
				}
			}  
		}  
	}
	else
	{ 	
		*Tmp_XPntr1 = 0x00;
	}
	
	(Debounce_TBL[device_id].nochange)();
}

