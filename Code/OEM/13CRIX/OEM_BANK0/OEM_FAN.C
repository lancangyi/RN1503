/*-----------------------------------------------------------------------------
 * TITLE: OEM_FAN.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// Smart Fan control
//-----------------------------------------------------------------------------
// Fan table 1   2009/08/18 Rev.01
//
// T > on    level +1  ;   T < off ,Level -1
//
// Add function for linear calculation.
//----------------------------------------------------------------------------

//NOTE,thermal sensor 检测的问题范围为-64-191度 温度表需要做64度偏移:thermal sensor 64----> environment 0

const thermal code ascend_ThermalTabel[]=
{

//  Level   T_high   T_low   step    start_RPM
	{0,     94,     0,     0,        0,     },
	{1,     114,    94,    0,      2600,    },
	{2,     121,    114,   0,      3200,    },
	{3,     129,    121,   0,      3700,    }, 
	{4,     164,    129,   0,      4000,    }, 
};


const thermal code descend_ThermalTabel[]=
{

//  Level   T_high   T_low   step    start_RPM
	{0,     89,     0,       0,     0,        },
	{1,     109,    89,      0,     2600,     }, 
	{2,     116,    109,     0,     3200,     }, 
	{3,     124,    116,     0,     3700,     }, 
	{4,     164,    124,     0,     4000,     }, 
};






#define  _ThermTabSize   ((sizeof(ascend_ThermalTabel)/sizeof(thermal))-1)


// GPU 与 CPU FAN 保持同步,GPU 与 CPU 温度高的为参考

//-----------------------------------------------------------------------------
// The function of check fan1 rpm       1sec-A  time base     
//-----------------------------------------------------------------------------	
void CheckFanRPM(void)
{
    BYTE IsTemperature_Change; 
	WORD RPM_Increment;
	    if(IS_MASK_SET(DebugFanStatus,Debug_Fan_enable))
	    {
	         return;
	    }
		//修正温度的判断，以2度改变为参考
        if((Maxtemperature >=(Bktemperature-2))&&(Maxtemperature <=(Bktemperature+2)))
        {
           if(Fan_Adjust_Dir == 1)
           {
             FanLevel_t =  Bk1FAN_Level;
		   }
		   else if(Fan_Adjust_Dir == 2)
		   {
             FanLevel_t =  Bk2FAN_Level;
		   }
		   
            IsTemperature_Change = 0x00;//温度未发生改变
	     }
         else if(Maxtemperature > (Bktemperature+2))
         {
            IsTemperature_Change = 0x01;//温度上升
            //  FanLevel_t = Bk1FAN_Level;
	     }
	     else if(Maxtemperature < (Bktemperature-2))
	     {
            IsTemperature_Change = 0x02;//温度下降
            // FanLevel_t = Bk2FAN_Level;
	     }
	
	     Bktemperature = Maxtemperature;

	     if(IsTemperature_Change == 0x01)
         {
             Fan_Adjust_Dir = 1;
			 
	         if(FanLevel_t < _ThermTabSize)
	         {
		       if(Maxtemperature > ascend_ThermalTabel[FanLevel_t].T_high)
		       {
			      FanLevel_t += 1;
		       }
	         }
	
	        if (FanLevel_t>0)
	        {
		       if (Maxtemperature < ascend_ThermalTabel[FanLevel_t].T_low)
		       {
			     FanLevel_t -= 1;
		       }
	        }

	       
	       FAN1_Level  = FanLevel_t;  // backup fan speed level
           FAN2_Level  = FanLevel_t;  // backup fan speed level
           Bk1FAN_Level = FanLevel_t;
		
	     RPM_Increment = (Maxtemperature-ascend_ThermalTabel[FanLevel_t].T_low) * ascend_ThermalTabel[FanLevel_t].step;
	
	     FAN1_GoalRPM = ascend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
         FAN2_GoalRPM = ascend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
        }
	    else if(IsTemperature_Change == 0x02)
	    {
	        Fan_Adjust_Dir = 2;
      	    if(FanLevel_t < _ThermTabSize)
	        {
		      if(Maxtemperature > descend_ThermalTabel[FanLevel_t].T_high)
		      {
			    FanLevel_t += 1;
		      }
	        }
	        if(FanLevel_t>0)
	        {
		      if (Maxtemperature < descend_ThermalTabel[FanLevel_t].T_low)
		      {
			    FanLevel_t -= 1;
		      }
	        }
	
	       FAN1_Level   = FanLevel_t;  // backup fan speed level
	       FAN2_Level   = FanLevel_t;  // backup fan speed level
           Bk2FAN_Level = FanLevel_t;

		
	       RPM_Increment = (Maxtemperature-descend_ThermalTabel[FanLevel_t].T_low) * descend_ThermalTabel[FanLevel_t].step;
	
	       FAN1_GoalRPM = descend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
           FAN2_GoalRPM = descend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
	   }
	   else if(IsTemperature_Change == 0x00)
	   { 
	      if(Fan_Adjust_Dir==1)
	      {
	         if(FanLevel_t < _ThermTabSize)
	         {
		       if(Maxtemperature > ascend_ThermalTabel[FanLevel_t].T_high)
		       {
			      FanLevel_t += 1;
		       }
	         }
	
	        if (FanLevel_t>0)
	        {
		       if (Maxtemperature < ascend_ThermalTabel[FanLevel_t].T_low)
		       {
			     FanLevel_t -= 1;
		       }
	        }
			
			if(Bk1FAN_Level == FanLevel_t)
			{
			  return;
			}
			else
			{
	          Bk1FAN_Level = FanLevel_t;
	          FAN1_Level  =  FanLevel_t;  // backup fan speed level
              FAN2_Level  =  FanLevel_t;  // backup fan speed level
              
	          RPM_Increment = (Maxtemperature-ascend_ThermalTabel[FanLevel_t].T_low) * ascend_ThermalTabel[FanLevel_t].step;
	          FAN1_GoalRPM = ascend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
              FAN2_GoalRPM = ascend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
		   }
	     }
		 else if(Fan_Adjust_Dir==2)
		 {
            if(FanLevel_t < _ThermTabSize)
	        {
		      if(Maxtemperature > descend_ThermalTabel[FanLevel_t].T_high)
		      {
			    FanLevel_t += 1;
		      }
	        }
	        if(FanLevel_t>0)
	        {
		      if (Maxtemperature < descend_ThermalTabel[FanLevel_t].T_low)
		      {
			    FanLevel_t -= 1;
		      }
	        }

			if(Bk2FAN_Level == FanLevel_t)
			{
			   return;
			}
			else
			{
	
	          FAN1_Level   = FanLevel_t;  // backup fan speed level
	          FAN2_Level   = FanLevel_t;  // backup fan speed level
              Bk2FAN_Level = FanLevel_t;
	          RPM_Increment = (Maxtemperature-descend_ThermalTabel[FanLevel_t].T_low) * descend_ThermalTabel[FanLevel_t].step;
	
	          FAN1_GoalRPM = descend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
              FAN2_GoalRPM = descend_ThermalTabel[FanLevel_t].start_RPM + RPM_Increment;
		   }  
	   }
	   else
	   {
		  Fan_Adjust_Dir=0;
	   }
    } 

}



//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void FanControl(void)
{
 
    if(IS_MASK_SET(DebugFanStatus,Debug_Fan_enable))
    {
      return;
    }

	if((FAN1_GoalRPM-RPMACC)>FAN1_CurrentRPM)
	{
		if(GPUFanValue<MaxOutValue)
		{
			GPUFanValue++;
		}
		else
		{
            GPUFanValue = MaxOutValue;
		}
	}
	else if((FAN1_GoalRPM+RPMACC)<FAN1_CurrentRPM)
	{
		if(GPUFanValue>0x00)
		{
			GPUFanValue--;
		}
		else
		{
            GPUFanValue = 0x00;
		}
	}

    if((FAN2_GoalRPM-RPMACC)>FAN2_CurrentRPM)
	{
		if(CPUFanValue<MaxOutValue)
		{
			CPUFanValue++;
		}
		else
		{
           CPUFanValue = MaxOutValue;
		}
	}
	else if((FAN2_GoalRPM+RPMACC)<FAN2_CurrentRPM)
	{
		if(CPUFanValue>0x00)
		{
		   CPUFanValue--;
		}
		else
		{
		   CPUFanValue = 0x00;
		}
	}
	
}



//-----------------------------------------------------------------------------
// GPU Fan full on control
//-----------------------------------------------------------------------------
void GPUFanFullOn(void)
{
	GPUFanValue = MaxOutValue;
	FanFullOnCont = FullOnCounter;		    //2sec
}


//-----------------------------------------------------------------------------
// CPU Fan full on control
//-----------------------------------------------------------------------------
void CPUFanFullOn(void)
{
	CPUFanValue = MaxOutValue;
	FanFullOnCont = FullOnCounter;		    //2sec
}


//-----------------------------------------------------------------------------
// GPU Fan full off control
//-----------------------------------------------------------------------------
void GPUFanFullOff(void)
{
	GPUFanValue = 0x00;
}

//-----------------------------------------------------------------------------
// CPU Fan full off control
//-----------------------------------------------------------------------------

void CPUFanFullOff(void)
{
    CPUFanValue = 0x00;
}


//-----------------------------------------------------------------------------
// GPU Fan Init on control
//-----------------------------------------------------------------------------
void GPUFanInitOn(void)
{
	GPUFanValue = FanInitValue;
	FanFullOnCont = FullOnCounter;		    //2sec
}


//-----------------------------------------------------------------------------
// CPU Fan Init on control
//-----------------------------------------------------------------------------
void CPUFanInitOn(void)
{
	CPUFanValue = FanInitValue;
	FanFullOnCont = FullOnCounter;		    //2sec
}


//-----------------------------------------------------------------------------
// Fan Init on control
//-----------------------------------------------------------------------------
void S5S0FanInitOn(void)
{
	GPUFanValue = S5S0FanInitValue;
	CPUFanValue  = S5S0FanInitValue;
	FanFullOnCont = S5S0FullOnCounter;		    //10sec
}

//-----------------------------------------------------------------------------
// Fan Init on control
//-----------------------------------------------------------------------------
void S4S0FanInitOn(void)
{
	GPUFanValue = S4S0FanInitValue;
	FanFullOnCont = S4S0FullOnCounter;		    //10sec
}


//-----------------------------------------------------------------------------
// Fan Init on control
//-----------------------------------------------------------------------------
void S3S0FanInitOn(void)
{
	GPUFanValue = S3S0FanInitValue;
	FanFullOnCont = S3S0FullOnCounter;		    //2sec
}


//-----------------------------------------------------------------------------
// function: GetRPM1, The function of get fan current RPM form EC Tachometer
//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//
//	Fs = FreqEC(9.2MHz)/128     sampling rate
//	P denotes the numbers of square pulses per revolution,  1 or 2, most of it's 2
//   Tach is the Tachometer counter Reg, Tach = {FnTMRR, FnTLRR}
//
//	Fan Speed(R.P.M) = 2156250/(Tach)
//-----------------------------------------------------------------------------
void GetRPM1(void)
{
    BYTE tach_H;
    BYTE tach_L;

	//{F2TMRR,F2TLRR} is the current RPM of RegValue, read from Reg
    tach_H = F2TMRR;
    tach_L = F2TLRR;
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
    	  ITempW01=(tach_H*256) + tach_L;

		  FAN1_CurrentRPM=(2156250/ITempW01);   //calculate current RPM
	      Oem_FAN1_CurrentRPM = FAN1_CurrentRPM;
		  if(FAN1_CurrentRPM > FAN_MAX_RPM)   // RPM1Max, The maximum speed of the FAN
		  {
            FAN1_CurrentRPM=FAN_MAX_RPM;
		  Oem_FAN1_CurrentRPM = FAN1_CurrentRPM; ////lw   //2017/12/8
		  }
    }
    else
    {
        FAN1_CurrentRPM=0;
		 Oem_FAN1_CurrentRPM = FAN1_CurrentRPM;     ////lw   //2017/12/8
    }


}



//-----------------------------------------------------------------------------
// function: GetRPM2, The function of get fan current RPM form EC Tachometer
//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//
//	Fs = FreqEC(9.2MHz)/128     sampling rate
//	P denotes the numbers of square pulses per revolution,  1 or 2, most of it's 2
//   Tach is the Tachometer counter Reg, Tach = {FnTMRR, FnTLRR}
//
//	Fan Speed(R.P.M) = 2156250/(Tach)
//-----------------------------------------------------------------------------
void GetRPM2(void)
{
    BYTE tach_H;
    BYTE tach_L;

	//{F1TMRR,F1TLRR} is the current RPM of RegValue, read from Reg
    tach_H = F1TMRR;
    tach_L = F1TLRR;
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
    	 ITempW02=(tach_H*256) + tach_L;

		 FAN2_CurrentRPM=(2156250/ITempW02);   //calculate current RPM
		
		 Oem_FAN2_CurrentRPM = FAN2_CurrentRPM;
		 if(FAN2_CurrentRPM > FAN_MAX_RPM)   // RPM1Max, The maximum speed of the FAN
		 {
            FAN2_CurrentRPM=FAN_MAX_RPM;
			Oem_FAN2_CurrentRPM = FAN2_CurrentRPM;  ////lw   //2017/12/8
		 }
     }
     else
     {
        FAN2_CurrentRPM=0;
		Oem_FAN2_CurrentRPM = FAN2_CurrentRPM;    ////lw   //2017/12/8
     }

 
 }



//-----------------------------------------------------------------------------
// The function of smart fan
// base 100ms-C
//-----------------------------------------------------------------------------
void FanManager(void)
{
	if(IS_MASK_CLEAR(DebugFanStatus,Debug_Fan_enable))// In normal control mode
	{
	   //when In normal control mode and need to clear the debug ram 
	    DebugFanRPMT = 0;
		
		if(FAN1_GoalRPM !=0x00 || FAN2_GoalRPM !=0x00)
		{
            GetRPM1();       //get Gpu fan current RPM
            GetRPM2();       //get Cpu fan current RPM
			FanControl();   
		}
		else
		{
			if(GPUFanValue != 0x00)
			{
				FAN1_CurrentRPM=0x0000;
				GPUFanFullOff();
			}
			if(CPUFanValue != 0x00)
			{
				FAN2_CurrentRPM=0x0000;
				CPUFanFullOff();
			}
		}
	}
    else// Lable:In RPM debug mode(by speed),the GPU and CPU have the same PWM Cycle
	{
		GetRPM1();
		GetRPM2();
		if(DebugFanRPMT==0x00)
		{
            GPUFanValue = 0;
			CPUFanValue = 0;
	    }
		else
		{   
		   if(DebugFanRPMT>40)//限制最高转速为4000转
		   {
              DebugFanRPMT = 40;
		   }
           if(((DebugFanRPMT*100)-RPMACC)>FAN1_CurrentRPM)
		   {
				if(GPUFanValue<MaxOutValue)
				{
					 GPUFanValue++;
				}
			}
			else if(((DebugFanRPMT*100)+RPMACC)<FAN1_CurrentRPM)
			{
				 if(GPUFanValue>0x00)
				 {
					 GPUFanValue--;
				 }
		    }  
		   if(((DebugFanRPMT*100)-RPMACC)>FAN2_CurrentRPM)
		   {
				if(CPUFanValue<MaxOutValue)
				{
					 CPUFanValue++;
				}
			}
			else if(((DebugFanRPMT*100)+RPMACC)<FAN2_CurrentRPM)
			{
				 if(CPUFanValue>0x00)
				 {
					 CPUFanValue--;
				 }
			} 
		}
    }
	
}

//the temp getting from sensor must be changed for heating module
BYTE Change_Temp(BYTE temp)
{
	BYTE ret;
	
	if(temp >= 0x40)   // 0 degree
		ret = temp - 0x40;
	else
	{
		ret = 0x40 - temp;
		ret = (~ret)+1;
	}

	return ret;
}

//-----------------------------------------------------------------------------
//T=100   centigrade	Enable EC throttle	50%  
//T=80    centigrade   Disable EC throttle 50%
//T=103   centigrade   EC shutdown System
// base 1sec-C
//-----------------------------------------------------------------------------
void MoniterTemprature(void)
{ 
 
	if(Debugtemperature1!=0x00)
	{
		TCPU_temp = Debugtemperature1;
	}
	else
	{    
/*	    //温度已经在温度表里面做了64度的偏移

	 if(Sys_Temp_Check_Flag ==1)
		{
		   if((Cpu_Tmp_Temp > Cpu_Temp_H)||(Cpu_Tmp_Temp < Cpu_Temp_H))//CPU温度发生改变
		   {
             if((Cpu_Tmp_Temp > Cpu_Temp_H)&&((Cpu_Tmp_Temp - Cpu_Temp_H)>=20))
             {
                 Read_CPU_Temp_OK = 0;
				//  RamDebug(0x32);
			 }
			 else if((Cpu_Tmp_Temp < Cpu_Temp_H) && ((Cpu_Temp_H - Cpu_Tmp_Temp)>=20))
			 {
			    Read_CPU_Temp_OK = 0;
				// RamDebug(0x12);
			 }
			 else
			 {
			  //   RamDebug(0x42);
                 Cpu_Tmp_Temp = Cpu_Temp_H;
				 Read_CPU_Temp_OK = 1;
			 } 
		   }
		   else//CPU 温度未发生改变
		   {
		      Read_CPU_Temp_OK = 1;
		   }

		   if((Gpu_Tmp_Temp > Gpu_Temp_H)||(Gpu_Tmp_Temp < Gpu_Temp_H))//GPU温度发生改变
		   {
             if((Gpu_Tmp_Temp > Gpu_Temp_H)&&((Gpu_Tmp_Temp - Gpu_Temp_H)>=20))
             {
                 Read_GPU_Temp_OK = 0;
				// RamDebug(0x21);
			 }
			 else if((Gpu_Tmp_Temp < Gpu_Temp_H) && ((Gpu_Temp_H - Gpu_Tmp_Temp)>=20))
			 {
			    Read_GPU_Temp_OK = 0;
				// RamDebug(0x11);
			 }
			 else
			 {
			    //  RamDebug(0x41);
                 Gpu_Tmp_Temp = Gpu_Temp_H;
				 Read_GPU_Temp_OK = 1;
			 } 
		   }
		   else//GPU温度未发生改变
		   {
		      Read_CPU_Temp_OK = 1;
		   }

		   if((Read_CPU_Temp_OK == 1) && (Read_GPU_Temp_OK ==1) )
		   {
              CpuTemp = Cpu_Temp_H;
		      Oem_CPU_Temp = Cpu_Temp_H;
              Change_CpuTemp = Change_Temp(Oem_CPU_Temp); 
			  TCPU_temp = CpuTemp;

              GpuTemp = Gpu_Temp_H;
		      Oem_GPU_Temp = Gpu_Temp_H;
              Change_GpuTemp = Change_Temp(Oem_GPU_Temp);  
			 // RamDebug(0x10);
		   }
		    
		}
		else
		{

	*/	
           CpuTemp = Cpu_Temp_H;
		   Oem_CPU_Temp = Cpu_Temp_H;
           Change_CpuTemp = Change_Temp(Oem_CPU_Temp); 
		   TCPU_temp = CpuTemp;
		   
           GpuTemp = Gpu_Temp_H;
		   Oem_GPU_Temp = Gpu_Temp_H;
           Change_GpuTemp = Change_Temp(Oem_GPU_Temp);  
		  // RamDebug(0x99);

		  
	//	}

		LcdTemp = Lcd_Temp_H;
		Oem_LCD_Temp = Lcd_Temp_H;
		Change_LcdTemp = Change_Temp(Oem_LCD_Temp);


		
        temperature1 = GpuTemp;  // Get GPU temperature
        temperature2 = CpuTemp;  // Get CPU temperature
        
	    if(temperature1 > temperature2)
        {
           Maxtemperature = temperature1;
	    }
	    else
	    {
	       Maxtemperature = temperature2;
	    }

        if(Maxtemperature >= ProchotOnTM)  // Max(CPU,GPU) drop half frequency
	    {
		    if(0==(Oem_Globe_Flag1&Oem_SYS_Temp_OV_f))
		    {
			  Check_notify_em();
		    }
		
		   Oem_Globe_Flag1 |= Oem_SYS_Temp_OV_f;
	    }
	    else if(Maxtemperature <= ProchotOffTM) // Max(CPU,GPU) restore all frequency
	    {
		  if(Oem_Globe_Flag1&Oem_SYS_Temp_OV_f)
		  {
			Check_notify_em();
		  }
		
		  Oem_Globe_Flag1 &= ~Oem_SYS_Temp_OV_f;
		 
	    }

	  if(Maxtemperature >= ShutdownTM)   //EC shutdown
	  {
		 SYS_TooHot_Cnt += 1;
		 if(SYS_TooHot_Cnt>3)
		 {
			OEM_Debug_flag |= OEM_Temp_Stop_f;

			BRAM_TEMP_OV = 0x55;
			ETWCTRL = 0x10; 	   				//EWDCMS  External WDT stop count mode select   1: External WDT can be stopped by setting EWDSCEN bit,	0: External WDT cannot be stopped
			EWDCNTLR = WATCHDOG_COUNTER_1S;		//reset ec domain		
			while(1);							// Wait for watch dog time-out	
		 }
	 }
	 else
	 {
		SYS_TooHot_Cnt = 0x00;
	 }
	 
	}

}

//-----------------------------------------------------------------------------
// Function Name : ReadCPUTemp   1sec time base
//-----------------------------------------------------------------------------
#if GetCPUTempSupport
void ReadCPUTemp(void) 
{
    if(SystemIsS0)
    {
        // Use PECI interface to read cpu temperature
        #ifdef PECI_Support
            #if ReadCPUTemperature
            if(CPUTjmax==0x00)         // Need to read CPU Tjmax
            {
                PECI_ReadCPUTJMAX();
            }
            else
            {
                PECI_ReadCPUTemp();     // Use PECI interface to read cpu temperature
            }
            #endif
        #endif 
        
    }
}
#endif

//-----------------------------------------------------------------------------
// Function Name : ReadSysTemp
//-----------------------------------------------------------------------------
#if GetSysTempSupport
void ReadSysTemp(void) 
{
    if(SystemIsS0)
    {
		#if OEM_GPU_ITS_SUPPORT
		if(IS_MASK_SET(GPU_INFO_FLG, GPU_INIT_OK))
		{
			SET_MASK(SMBus2Flag1, GPUPackage);
			CLEAR_MASK(GPU_INFO_FLG, GPU_INIT_OK);
		}	
		#endif
    }
}
#endif

//-----------------------------------------------------------------------------
// Function Name : InitThermalChip
//-----------------------------------------------------------------------------
void InitThermalChip(void)
{

    BYTE ThermalSenserID;
    BYTE ThermalSenserConfig;
	
	EnableAllInterrupt();
	
   if(bRWSMBus(SMbusCh2,SMbusRB,ThermalSenser_Addr,0xFE,&ThermalSenserID,0))
   {
      
      if(ThermalSenserID == 0x5D)
      {
         SET_MASK(ThermalSensorStatus,ThermalSensorIn);
      }
	  else
	  {
	     CLEAR_MASK(ThermalSensorStatus,ThermalSensorIn);
	  }
   }
   else
   {
        CLEAR_MASK(ThermalSensorStatus,ThermalSensorIn);
   }
   
   if(IS_MASK_SET(ThermalSensorStatus,ThermalSensorIn))
   {
      //config the temp data format -64~191C
       ThermalSenserConfig = 0x04; 
       bRWSMBus(SMbusCh2,SMbusWB,ThermalSenser_Addr,0x03,&ThermalSenserConfig,0);
	   bRWSMBus(SMbusCh2,SMbusWB,ThermalSenser_Addr,0x09,&ThermalSenserConfig,0);
   }

    DisableAllInterrupt();
}    




//----------------------------------------------------------------------------
// Init GPU internal thermal sensor read register.
//----------------------------------------------------------------------------
#if OEM_GPU_ITS_SUPPORT
BYTE InitPollingGPUTemp(void)
{
	BYTE INIT_GPU_REG[4] = {0x0F, 0x00, 0x01, 0xCC};	// according to AMD GPU spec
	BYTE Rval = 0;

	if(bWSMBusBlock(GPU_ITS_Chanel, 0x14, GPU_ITS_Addr, 1, &INIT_GPU_REG, 4, SMBus_NoPEC))
		{
			SET_MASK(GPU_INFO_FLG, GPU_INIT_OK);
			Rval = 1;
		}
	return Rval;
}

#endif


//----------------------------------------------------------------------------
// Check Init GPU internal thermal sensor read register ok or not?
// for Polling 10 times at lest
//----------------------------------------------------------------------------
#if OEM_GPU_ITS_SUPPORT
void CheckGPUInitok(void)
{

	    if(SystemIsS0)
		{
			if(IS_MASK_SET(GPU_INFO_FLG, GPU_INIT_FAIL))		// set init fail flag and do not check again
				return;
			
			    if(IS_MASK_CLEAR(GPU_INFO_FLG, GPU_INIT_OK))
				{
					    if(!InitPollingGPUTemp())
						{
							GPU_INIT_CNT++;
							if(GPU_INIT_CNT >= 10)
							{
                              SET_MASK(GPU_INFO_FLG, GPU_INIT_FAIL);
							  CLEAR_MASK(GPU_INFO_FLG, GPU_INIT_OK);
							  GPU_INIT_CNT = 0;
							}
						}
					    else
						{
							SET_MASK(GPU_INFO_FLG, GPU_INIT_OK);
							CLEAR_MASK(GPU_INFO_FLG, GPU_INIT_FAIL);
							GPU_INIT_CNT = 0;
						}
				}
		}
	
}

#endif
 
 







