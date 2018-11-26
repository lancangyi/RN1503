/*-----------------------------------------------------------------------------
 * TITLE: OEM_HEATING.C - OEM specific code
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


//denglha:Add heating function start

#define BATTERY_TEMP_HEAT_LCD  0x957   //-34 degree
#define NORMAL_BATTERY_POWER_ON 0x97E   // -30 degree
#define SPECIAL_BATTERY_POWER_ON  0x975 // -31 degree  //0x97F  // -30 degree   //0x96B   // -32 degree  //system power on

#define BATTERY_RUNNING_VCC_LEVEL  8200  //8.2v  //8100   //8.1v

#define LCD_STOP_HEATING_TEMP   10   //stop lcd heating when lcd temp up to 10 degree
//#define LCD_STOP_HEATING_TEMP   50   //for test
#define LCD_OS_START_HEATING_TEMP   0xF6   //in os mode when lcd temp below -10 degree, enable lcd heating

#define LCD_AC_HEATING_TEMP  0xF1  // -15 degree in AC mode

#define MCH_AC_HEATING_TEMP  0xE9  //system power on when upto -23 degree in AC mode

#define AC_MAX_HEATING_TIME  8*60  
#define DC_SPECIAL_MAX_HEATING_TIME  15*60   // 10*60;   modify max time to 9 min zlh 20150911
#define DC_NORMAL_MAX_HEATING_TIME  270  //normal battery is working only in -20 degree.


#define MORMAL_BATTERY_TEMP_LEVEL  0xE7   //-25 degree  

//#define debug_heat  30  //debug  // lw 2017/12/28
//#define debug_heat2   50 	// lw 2017/12/28

#define HDD_HEAT_LOW  0x0     // 0 degree

#define HEATING_NEXT_STEP_WAITING_TIME  3  //20   //30s
#define HEATING_WAITING_VCC_READY   5  //10  //10s
#define STOP_HEATING_TIME   2  //10  //5s  //stop heating 2s

#if SSD_Hdd_Used
#define DC_HEATING_FIRST_STEP  (HEATING_GPU)
#else
#define DC_HEATING_FIRST_STEP  (HEATING_HDD)

#endif
#define DC_HEATING_TWO_STEP    (HEATING_NONE1)        //must delay 10s

#if SSD_Hdd_Used
#define DC_HEATING_THREE_STEP    (HEATING_GPU|HEATING_LCD)
#else
#define DC_HEATING_THREE_STEP    (HEATING_HDD|HEATING_LCD)
#endif
#define DC_HEATING_FOUR_STEP   (HEATING_NONE2)        //must delay 10s

//------------------------------------------------------------
// CompareT1T2
// Check if byte date T1>=T2
//return 1: T1>=T2
//return 0: T1<T2
//------------------------------------------------------------

//compare T1T2 if t1>=t2 return 1 else return 0
FLAG CompareT1T2(BYTE T1, BYTE T2)
{
      short temp1,temp2;
	  
      temp1=T1;
	  if(T1&0x80) temp1|=0xFF00;

      temp2=T2;
	  if(T2&0x80) temp2|=0xFF00;

	  if(temp1>=temp2) return 1;
	  else return 0;

}

//------------------------------------------------------------
// Stop heating
//-------------------
void StopHeat()
{
	HT_LED_OFF();
	GPU_HEAT_OFF();
	LCD_HEAT1_OFF();
	LCD_HEAT2_OFF();
	Temperature_Low_Flag=0;
	MAX_Heat_Time=0;
	HEAT_FLAG = 0;
}

//For code size issue, OEM code 32K, core code 32K,  OEM code is full and  core code not
//so move some OEM code to core_main.c
//return 0: not in low temperature
//reture 1: low temperature power on, heating first; or EC wake up,  wait sensor ready
//return 2:  can not heat and power on, because temperature is below -20, normal battery and adapter off,
BYTE Check_Low_Temperature(void)
{
	BYTE temp_count = 0;
	//if(Temperature_Low_Flag==TempLow) return 1;//press power button when heating, just return 1

	#ifdef HEAT_DEBUG
//	RamDebug(Change_GpuTemp);
//	RamDebug(Change_LcdTemp);		
//	RamDebug(BAT1_Type_Flag);
//	RamDebug(Temperature_Low_Flag);
	#endif

//lw 2018/03/02	
	//lw 2018/01/23
//	PollingTempSensor();    //lw 2018/01/23
//	SMBusCenterSelection(SMbusCh2);  //10
//	MoniterTemprature();  
	//lw 2018/01/23
//lw 2018/03/02	

	if((Change_LcdTemp==TEMP_SPECIAL_VALUE)||(Change_GpuTemp==TEMP_SPECIAL_VALUE))
	{
		Temperature_Low_Flag=PreTempLow;
		NEED_MinHeatTime=0x01;//ec sleep, R14HDD_Temp is always 0xFF, should check again
		return 1;
	}

	if((Temperature_Low_Flag == TempLow)||(Temperature_Low_Flag == HeatingWaiting)) //heating service is running, so exit
		return 1;
	
	//#if (!HEAT_DEBUG) //for zlh debug
	if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))   //DC mode
	{
		if(CompareT1T2(MORMAL_BATTERY_TEMP_LEVEL,Change_GpuTemp))    //make sure the temperature is below -20
			temp_count++;
		if(CompareT1T2(MORMAL_BATTERY_TEMP_LEVEL,Change_LcdTemp))
			temp_count++;
		if(temp_count > 1)  //temperature is below -20
		{
			if(BAT1_Type_Flag)   //normal battery
			{
				#ifdef HEAT_DEBUG
//			    RamDebug(0x19);
//				RamDebug(POWER_FLAG1);
				#endif				
				Temperature_Low_Flag = 0;
				return 2;   //can not power on and heat
			}	
		}
	}
	//#endif

	temp_count = 0;	
	if(!CompareT1T2(Change_GpuTemp,HDD_HEAT_LOW))
//	if(!CompareT1T2(Change_GpuTemp,0x30)) 		//fordebug
		temp_count++;
	if(!CompareT1T2(Change_LcdTemp,HDD_HEAT_LOW))
//	if(!CompareT1T2(Change_LcdTemp,0x30))       //fordebug
		temp_count++;

//	if(!CompareT1T2(R14HDD_Temp,HDD_HEAT_LOW))
//		temp_count++;

	#ifdef HEAT_DEBUG
//    RamDebug(0x12);
//	RamDebug(temp_count); 
//	RamDebug(Temperature_Low_Flag);
	#endif

	if(temp_count < 2 ) 
	{
	    return 0;								
	}	
	else  	
        Temperature_Low_Flag=TempLow;
	
	//get min heating time
	temp_count = Change_LcdTemp;
	if(!CompareT1T2(Change_GpuTemp,temp_count))
	{
		if(Change_GpuTemp!=TEMP_SPECIAL_VALUE)
			temp_count = Change_GpuTemp;
	}	
	if(temp_count & 0x80)
		temp_count = 0xFF - temp_count +1;

	R14Heating_Temp = temp_count;   //current temp value
	
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))//AC mode	
	{
		#if SSD_Hdd_Used
			Min_Heat_Time=((WORD)temp_count)*4;
		#else
			Min_Heat_Time=((WORD)temp_count)*5;
		#endif
	}	
	else                                    //DC mode
		Min_Heat_Time=((WORD)temp_count)*6;

	//get max heating time
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))
		 MAX_Heat_Time=AC_MAX_HEATING_TIME;
	else
	{
		if(BAT1_Type_Flag)   //normal battery
			//MAX_Heat_Time=DC_NORMAL_MAX_HEATING_TIME;  
			MAX_Heat_Time = ((WORD)temp_count)*15;
		else
		{
			//MAX_Heat_Time=DC_SPECIAL_MAX_HEATING_TIME;    
			if(temp_count>19)
				MAX_Heat_Time = ((WORD)temp_count)*20;
			else
				MAX_Heat_Time = ((WORD)temp_count)*13;
		}				
	}

	if(IS_MASK_SET(OS_PM_STATE,OS_BAT1_IN))  ///lw++  Determine whether the battery exists
	{
	    if(!BAT1_Type_Flag)
		BATT_TEMP_PowerOn = SPECIAL_BATTERY_POWER_ON;   // -31 degree
	else
		BATT_TEMP_PowerOn = NORMAL_BATTERY_POWER_ON;   // -30 degree
		
	}
	else
	{
		BATT_TEMP_PowerOn = TEMP_WITHOUT_BATTERY;   //  0xBD8
	}

	// set heating model
	HEAT_FLAG = 0;
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))//AC mode, heat CPU&LCD
	{
		//SET_MASK(HEAT_FLAG, HEATING_ALL_MODEL);		
		HEAT_FLAG = HEATING_ALL_MODEL;
	}
	else
	{
		HEAT_FLAG = DC_HEATING_FIRST_STEP;
	}


	
	#ifdef HEAT_DEBUG
//		RamDebug(0x10);
//		RamDebug(HEAT_FLAG);
//		RamDebug(*((BYTE *)(&MAX_Heat_Time)));
//		RamDebug(*(((BYTE *)(&MAX_Heat_Time))+1));
//		RamDebug(*((BYTE *)(&Min_Heat_Time)));
//		RamDebug(*(((BYTE *)(&Min_Heat_Time))+1));
		#ifdef SIMULATE_HEAT
		MAX_Heat_Time=10*60;  //for zlh debug
		Min_Heat_Time = 0;  //for zlh debug	
		#endif
	#endif
	
	return 1;
}

// return ==0, mean temp not ready
//           ==1, mean temp is ready
BYTE Check_Temp_Ready(void)
{
	BYTE sub1;

	sub1 = Change_LcdTemp - Change_GpuTemp;
	if(sub1 & 0x80)
		sub1 = 0xFF - sub1 +1;


	if(sub1>5)
		return 0;
	else
		return 1;

}

//EC wake up, wait sensor ready
void EC_Wakeup_Check_Temperature(void)
{
	BYTE result,temp;
	
     if((Temperature_Low_Flag==PreTempLow)&&(NEED_MinHeatTime))
   	 {  	
   	 	
		if(Change_LcdTemp!=TEMP_SPECIAL_VALUE)	//if temp == 0x9c, then sensor is not ready
				 {
					 NEED_MinHeatTime++; //the init value is 1, should it twice for no heating to power on in battery sometimes
					 temp = Check_Temp_Ready();
			 #if HEAT_DEBUG
						RamDebug(0x14);
						RamDebug(R14MCH_Temp); 
						RamDebug(R14HDD_Temp); 
						RamDebug(R14LCD_Temp);
						RamDebug(temp);
			 #endif
					 if((temp)||(NEED_MinHeatTime==4))
					 {
						 NEED_MinHeatTime = 0;
						 //sensor is ready, check temp again
						 result = Check_Low_Temperature();
						 if(!result)  //normal temp
						 {
							 Temperature_Low_Flag = TempLow;
							 HEAT_FLAG = HEATING_END;
							 MAX_Heat_Time = 0;   //set time = 0, then stop heat and power on
							 Min_Heat_Time = 0;
						 }
					 }
				 }
   	 }
}

//Check if heating power on
//return 1: heating over, should power on
//reture 0:  temperature is still low, should heating 
BYTE Check_Heating_PowerOn(void)
{
	#ifdef HEAT_DEBUG
		if(!(MAX_Heat_Time % 20))
		{
//			RamDebug(0x13);
//			RamDebug(Change_GpuTemp);			
//			RamDebug(HEAT_FLAG);
//			RamDebug(Temperature_Low_Flag);
			if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))
			{
//				RamDebug(0x15);
				//RamDebug(BT1_STATUS1);
//				RamDebug(BAT1_temp_H);
//				RamDebug(BAT1_temp_L);
//				RamDebug(BAT1_volt_H);				
//				RamDebug(BAT1_volt_L);		
				//RamDebug(*((BYTE *)(&MAX_Heat_Time)));
				//RamDebug(*(((BYTE *)(&MAX_Heat_Time))+1));				
			}			
			else
			{
//				RamDebug(0x15);
//				RamDebug(Change_LcdTemp);
			}
		}
	#endif
	if(Min_Heat_Time!=0) return 0;
	if(MAX_Heat_Time==0) return 1;	
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))  //AC mode
	{
		if(!CompareT1T2(LCD_STOP_HEATING_TEMP,Change_LcdTemp))
			CLEAR_MASK(HEAT_FLAG,HEATING_LCD);
		
		if(!CompareT1T2(CPU_HEAT_HIGH,Change_GpuTemp))
			CLEAR_MASK(HEAT_FLAG,HEATING_GPU);	
		
		#if SSD_Hdd_Used
		//if(MAX_Heat_Time == 0)
		//{
		//	#if HEAT_DEBUG
		//	RamDebug(0x1A);
		//	RamDebug(Change_GpuTemp);
		//	RamDebug(Change_LcdTemp);
		//	#endif
		//	HEAT_FLAG = HEATING_END;
		//	return 1;
		//}
		if(CompareT1T2(Change_GpuTemp,MCH_AC_HEATING_TEMP)&&CompareT1T2(Change_LcdTemp,LCD_AC_HEATING_TEMP))
		//if(CompareT1T2(Change_GpuTemp,0x30)&&CompareT1T2(Change_LcdTemp,0x30))	//fordebug
		{
			#ifdef HEAT_DEBUG
		//	RamDebug(0x1B);
		//	RamDebug(Change_GpuTemp);
		//	RamDebug(Change_LcdTemp);
			#endif		
			HEAT_FLAG = HEATING_END;
			return 1;
		}
		#else
		
		//check MCP temp		
		if(!CompareT1T2(CPU_HEAT_HIGH,Change_GpuTemp))
			CLEAR_MASK(HEAT_FLAG,HEATING_GPU);		
		#endif
		
		return 0;	
	}
	else //battery mode
	{
		#ifdef HEAT_DEBUG
//		if(!(MAX_Heat_Time % 9))
//		{
//			RamDebug(0x15);
//			//RamDebug(BT1_STATUS1);
//			RamDebug(BAT1_TEM_H);
//			RamDebug(BAT1_TEM_L);
//			RamDebug(BAT1_V_H);				
//			RamDebug(BAT1_V_L);		
//			//RamDebug(*((BYTE *)(&MAX_Heat_Time)));
//			//RamDebug(*(((BYTE *)(&MAX_Heat_Time))+1));				
//		}
		#endif	

		if(IS_MASK_CLEAR(HEAT_FLAG, HEATING_END)) return 0;
		
		//#if SSD_Hdd_Used    //ssd can work in low temp
		//HEAT_FLAG = HEATING_END;  //clear other bit
		//#endif
		return 1;
	}
	
}

//check the battery stat which is running now.
//return:  ==0  battery must keep current stat
//            >0    battery is ready for next step
//return battery vcc to top function
//if battery2 is online, then battery2 is working first. 
BYTE Check_Battery_Stat(WORD *p_battery_vcc_tmp)
{
	WORD battery_tmp = 0,battery_temp_level;
	BYTE temp_flag = 0;

	//set battery tempture level
	switch(HEAT_FLAG)  
	{
		case DC_HEATING_FIRST_STEP:  //first heating hdd
		case DC_HEATING_TWO_STEP:
			battery_temp_level = BATTERY_TEMP_HEAT_LCD;
			break;
			
		case DC_HEATING_THREE_STEP:
		case DC_HEATING_FOUR_STEP:	
		default:
			if(BAT1_Type_Flag)
				battery_temp_level = NORMAL_BATTERY_POWER_ON;
			else
				battery_temp_level = SPECIAL_BATTERY_POWER_ON;
		break;
	}	
	 
	//if(IS_MASK_SET(BT1_STATUS1, bat_in)  && IS_MASK_SET(BT1_STATUS2, bat_DC_OK))//battery1 dischargr
	if(IS_MASK_SET(BT1_STATUS1, bat_in))
	{
	    
		battery_tmp = (((WORD)BAT1_volt_H<<8)+BAT1_volt_L);
		if(battery_temp_level < (((WORD)BAT1_temp_H<<8)+BAT1_temp_L)) 
			temp_flag = 1;		
	}

	(*p_battery_vcc_tmp) = battery_tmp;
	
	if((temp_flag) && (battery_tmp >= BATTERY_RUNNING_VCC_LEVEL))
	{
		
		return 1;
	}
	else
	{
		return 0;
	}

	return 0;
}



//check the lcd temp.
//return:  ==0  lcd temp do not touch the level.
//            >0    lcd temp is ok.
BYTE Check_LCD_Stat(void)
{
	return (CompareT1T2(LCD_STOP_HEATING_TEMP,Change_LcdTemp))? 0:1;
}

void Set_Heating_Model(void)
{
	
	if(IS_MASK_SET(HEAT_FLAG,HEATING_ALL_MODEL))
		HT_LED_ON();
	else
		HT_LED_OFF();

	#ifdef SIMULATE_HEAT
	   HT_LED_OFF();
	   GPU_HEAT_OFF();
	   LCD_HEAT1_OFF();
	   LCD_HEAT2_OFF();
	#else		
		//start heating
		
		if(IS_MASK_SET(HEAT_FLAG, HEATING_LCD))
		{
			LCD_HEAT1_ON();
			if(IS_MASK_SET(POWER_FLAG1, adapter_in))  //in AC mode
			{
				LCD_HEAT2_ON();
			}
		}	
		else
		{
			LCD_HEAT1_OFF();
			if(IS_MASK_SET(POWER_FLAG1, adapter_in))  //in AC mode
			{
				LCD_HEAT2_OFF();
			}
		}
		if(IS_MASK_SET(HEAT_FLAG, HEATING_GPU))
			GPU_HEAT_ON();		
		else
			GPU_HEAT_OFF();
	#endif	


}

void Init_Heating(void)
{

//	CPU_HEAT_LOW=0xE7;    //-25 degree
	CPU_HEAT_HIGH=10;     //10->50  for debug
//	LCD_HEAT_HIGH=10;

	if(IS_MASK_SET(OS_PM_STATE,OS_BAT1_IN))
    {
	   BATT_TEMP_PowerOn=0x97E;	//-30
    }
	else
	{
       BATT_TEMP_PowerOn=TEMP_WITHOUT_BATTERY;
	}
	
    Change_GpuTemp =TEMP_SPECIAL_VALUE;
	Change_LcdTemp =TEMP_SPECIAL_VALUE;

	return ;
}

void Stop_LCD_Heating(void)
{
	#ifdef  HEAT_DEBUG
	//RamDebug(0x1C);
	#endif
	Temperature_Low_Flag=0; 
	LCD_OS_Heating_Flag=0;
	LCD_HEAT2_OFF();  //disable lcd small heating
	LCD_HEAT1_OFF();
	HT_LED_OFF();
}

void Heating_Service(void)
{
	static XBYTE heat_wait_time = 0;
	static XWORD battery_vcc = 0;
	BYTE tmp;
	WORD batt_tmp;

//lw 2017/12/18
	//<<  2017/11/22 lw
	//<<2017/12/18  modify the heat test code 
	//test the heat
   if(IS_MASK_SET(Debug_TIME,BIT0)||IS_MASK_SET(Debug_Heating_Status,BIT0))
   {
		SET_MASK(Debug_Heating_switch,BIT0);
   }
   else
   	CLEAR_MASK(Debug_Heating_switch,BIT0);
   	
   if(IS_MASK_SET(Debug_Heating_switch,BIT0))
   	{	
   		if(Temperature_Low_Flag != TestHeating)  MAX_Heat_Time = 180;  //<<lw 17/12/19
		Temperature_Low_Flag = TestHeating;
		if(IS_MASK_CLEAR(Debug_TIME,BIT0)&&IS_MASK_SET(Debug_Heating_Status,BIT0))
			HEAT_TEST_FLAG = 0x02;//gpu
		if(IS_MASK_SET(Debug_TIME,BIT0)&&IS_MASK_SET(Debug_Heating_Status,BIT0))
			HEAT_TEST_FLAG = 0x04;//lcd1
		if(IS_MASK_SET(Debug_TIME,BIT0)&&IS_MASK_CLEAR(Debug_Heating_Status,BIT0))
			HEAT_TEST_FLAG = 0x08;//lcd2
   	}
   else
   	{
		if(Temperature_Low_Flag == TestHeating) 
		{ 
			MAX_Heat_Time = 0; 
			CLEAR_MASK(Debug_Heating_switch,BIT0);
			CLEAR_MASK(Debug_Heating_Status,BIT0);
			CLEAR_MASK(Debug_TIME,BIT0);
		}
    }
   
//lw 2017/12/18
	//<<  2017/11/22 lw

	
   if((Temperature_Low_Flag==TempLow)||(Temperature_Low_Flag == HeatingWaiting))
   	{   

		if(Min_Heat_Time!=0) Min_Heat_Time--;
		if(MAX_Heat_Time!=0) MAX_Heat_Time--;
		if(heat_wait_time!=0) heat_wait_time--;
		
		if(Check_Heating_PowerOn())    
		{
			StopHeat();
			heat_wait_time = 0;
			switch (SysPowState) 
			{
				case SYSTEM_S5 :
				case SYSTEM_S4 :
					Oem_TriggerS5S0();
					break;
				default:
					break; 
			}
			
		    return;
        }
		else//not allow heating power on, do heating
		{
			Set_Heating_Model();  // AC & DC mode must heat now.
			if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))  //DC mode
			{
				if((Temperature_Low_Flag==TempLow)&&(IS_MASK_CLEAR(HEAT_FLAG, HEATING_END)))
				{
					tmp = Check_Battery_Stat(&batt_tmp);
					if(tmp)  //stat is ok, prepare to next step
					{
						battery_vcc = batt_tmp;
						heat_wait_time = HEATING_NEXT_STEP_WAITING_TIME;
						Temperature_Low_Flag = HeatingWaiting; 
						#ifdef  HEAT_DEBUG
					//	RamDebug(0x16);
					//	RamDebug(*((BYTE *)(&battery_vcc)));
					//	RamDebug(*(((BYTE *)(&battery_vcc))+1));
						#endif
					}
				}
				if((Temperature_Low_Flag==HeatingWaiting)&&(!heat_wait_time))
				{
					tmp = Check_Battery_Stat(&batt_tmp);
					//if((battery_vcc <= batt_tmp) && (tmp)) //ready to go to next step
					if(tmp)
					{
						switch(HEAT_FLAG)
						{
							case DC_HEATING_FIRST_STEP:  //first heating hdd
								HEAT_FLAG = DC_HEATING_TWO_STEP;
								heat_wait_time = STOP_HEATING_TIME; //this step must wait 10s
								break;
								
							case DC_HEATING_TWO_STEP:
								if((BAT1_Type_Flag)||(R14Heating_Temp < 22)) //normal battery or temp > -19 
								{
									HEAT_FLAG = HEATING_END;   //heating over
									if(Min_Heat_Time)
										Min_Heat_Time=0;     //set min time to zero
								}	
								else	    // low_temp battery must heat lcd.
									HEAT_FLAG = DC_HEATING_THREE_STEP;
								Temperature_Low_Flag = TempLow;   //return to heating
								break;

							case DC_HEATING_THREE_STEP:
									HEAT_FLAG = DC_HEATING_FOUR_STEP;
									heat_wait_time = STOP_HEATING_TIME; //this step must wait 10s
									break;	
							case DC_HEATING_FOUR_STEP:
							default:
								HEAT_FLAG = HEATING_END;
								Temperature_Low_Flag = TempLow;
								break;
						}
						#ifdef HEAT_DEBUG
					//	RamDebug(0x17);
					//	RamDebug(*((BYTE *)(&battery_vcc)));
					//	RamDebug(*(((BYTE *)(&battery_vcc))+1));
					//	RamDebug(heat_wait_time);
					//	RamDebug(HEAT_FLAG);
						#endif						
					}
					else
					{
						battery_vcc = batt_tmp;  //update batt vcc
						heat_wait_time = HEATING_WAITING_VCC_READY;
						#ifdef HEAT_DEBUG
					//	RamDebug(0x18);		
						#endif
					}
					
				}

			}
			
		}
   	}
    else if(Temperature_Low_Flag==TestHeating)//testheat tool to set this flag
    	{
	   	  if(MAX_Heat_Time > 180) MAX_Heat_Time=180;//Max 1 minute for heating test  //lw 2017/12/19
    	  if(MAX_Heat_Time!=0)MAX_Heat_Time --;
		  if(MAX_Heat_Time==0) //test time out
		  	{
		  		HT_LED_OFF();
				GPU_HEAT_OFF();
				LCD_HEAT1_OFF();
				LCD_HEAT2_OFF();
				Temperature_Low_Flag=0;
				HEAT_TEST_FLAG=0;//V012_A: add flag for heating test 
		  	}
		  else
		  	{
		  	  //V012_A: add flag for heating test start
		  	  
			  if(HEAT_TEST_FLAG & 0x01) //V012_A: HDD heat test 
			  	{HT_LED_ON();}
			  if(HEAT_TEST_FLAG & 0x02) //V012_A: CPU heat test 
			  	{GPU_HEAT_ON();HT_LED_ON();}
			  if(HEAT_TEST_FLAG & 0x04) //V012_A: LCD1 heat test 
			  	{LCD_HEAT1_ON();LCD_HEAT2_OFF();HT_LED_ON();}		
  			  if(HEAT_TEST_FLAG & 0x08) //V012_A: LCD2 heat test 
			  	{LCD_HEAT2_ON();LCD_HEAT1_ON();HT_LED_ON();}	
			 //V012_A: add flag for heating test end
			  
		  	}
    	}
	else if(Temperature_Low_Flag==HeatingInOS)  //heating lcd in os
	{
		if(IS_MASK_SET(POWER_FLAG1, adapter_in))   //in AC mode
		{
			if((Check_LCD_Stat())||(SystemNotS0))   //lcd temp is too high to stop lcd heating   //stop lcd heating when in S3\S4\S5 mode
			{
				Stop_LCD_Heating();
			}
		}	
		else
		{
			Stop_LCD_Heating();			
		}

	}	
	else 
	{
		if(IS_MASK_SET(POWER_FLAG1, adapter_in))   //in AC mode
		{
			if((SystemIsS0)&&(!Temperature_Low_Flag))
			{
				if(CompareT1T2(LCD_OS_START_HEATING_TEMP,Change_LcdTemp))  //lcd temp is too low, then enable lcd heating
					Temperature_Low_Flag = HeatingInOS;
			}
		}	
	}
		
}

void Update_LCD_Heating(void)
{

	if(IS_MASK_SET(LCD_OS_Heating_Flag, HEATING_lCD_35W))
	{
		LCD_HEAT1_ON();
	}
	else
	{
		LCD_HEAT1_OFF();
	}

	if(IS_MASK_SET(LCD_OS_Heating_Flag, HEATING_lCD_15W))
	{
		LCD_HEAT2_ON();
	}
	else
	{
		LCD_HEAT2_OFF();
	}

	if(LCD_OS_Heating_Flag)
		HT_LED_ON();
	else
		HT_LED_OFF();
	
}

#define ENABLE_35W_HEATING_CURRENT  0x7A    //1.8A    1.5A ------->102    
#define ENABLE_15W_HEATING_CURRENT  0xBE    //2.8A    
//#define DISABLE_HEATING_CURRENT   0x197   //3.75    
#define DISABLE_HEATING_CURRENT     0x110   // 4   

void LCD_OS_Heating_Service(void)
{
	BYTE state_temp;
	
	if((SystemNotS0)||(Temperature_Low_Flag!=HeatingInOS))
		return ;
	
	//lcd heating must in s0 mode and Temperature_Low_Flag = HeatingInOS

	state_temp = 0;
	
	if(AC_Current > DISABLE_HEATING_CURRENT)
	{
		state_temp = 0;   //stop heating
	}
	else 
	{
		if(AC_Current <= ENABLE_35W_HEATING_CURRENT)  
		{
			state_temp |= HEATING_lCD_35W;  //enable 35W
		}
		else 
		{
			if(AC_Current <= ENABLE_15W_HEATING_CURRENT)
			{
				if(IS_MASK_SET(LCD_OS_Heating_Flag,HEATING_lCD_35W))
				{
					state_temp = HEATING_lCD_15W| HEATING_lCD_35W;
				}
				else
				{
					if(IS_MASK_SET(LCD_OS_Heating_Flag,HEATING_lCD_15W))
						state_temp = HEATING_lCD_35W;  //enable 35W
					else
						state_temp = HEATING_lCD_15W;
				}	
			}
			else
			{
				state_temp = 0;		
				state_temp |= HEATING_lCD_15W;  //only enable 15W
			}
		}
	}
	if(state_temp != LCD_OS_Heating_Flag)
	{
	#ifdef ADC_DEBUG
		if(state_temp==0)
		{
		//	RamDebug(0xA1);
		//	RamDebug(*((BYTE *)(&AC_Current)));
		//	RamDebug(*(((BYTE *)(&AC_Current))+1));		
			//RamDebug(state_temp);
			//RamDebug(LCD_OS_Heating_Flag);
		}	
		#endif
		LCD_OS_Heating_Flag = state_temp;
		Update_LCD_Heating();		
	}

}
	
//****************************************************************************
// The function is use for debug heating service
//****************************************************************************
const WORD code BatteryAutoVcc[]=
{
	8600, 8400, 8380, 8350, 8320, 8310, 	
	8300, 8280, 8270, 8260, 8260, 8270, 	
	8290, 8260, 8250, 8240, 8230, 8210, 		
	8210, 8220, 8230, 8240, 8250, 0,
};

const WORD code BatteryAutoTemp[]=
{
//    -35,                         -34
	2381, 2382, 2383, 2391, 2392, 2393, 	
	2394, 2395, 2396, 2396, 2397, 2398,
//                         -30	
	2398, 2399, 2431, 2432, 2433, 2434, 		
	2435, 2436, 2437, 2438, 2439, 0, 			
};

void BatteryStatAutoChange(void)
{
	static XBYTE index = 0;
	static XBYTE delay = 10;
	WORD tmp;

	if(IS_MASK_SET(BT1_STATUS1, bat_valid)&&IS_MASK_SET(BT1_STATUS2, bat_DC_OK))
	{
		if(delay) delay--;
		tmp = BatteryAutoVcc[index];
		if(tmp)
		{
			BAT1_volt_L = (BYTE)(tmp & 0x00ff);
			BAT1_volt_H = (BYTE)((tmp & 0xFF00)>>8);
		}
		
		tmp = BatteryAutoTemp[index];
		if(tmp)
		{
			BAT1_temp_L = (BYTE)(tmp & 0x00ff);
			BAT1_temp_H = (BYTE)((tmp & 0xFF00)>>8);
			if(!delay)
				index++;
			else
				delay = 10;
		}
		else
		{
			//index = 0;
			
		}
	}
	else
		index = 0;
	return ;

}
