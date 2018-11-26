 /*-----------------------------------------------------------------------------
 * Filename:OEM_MEMORY.C     For Chipset: ITE.IT85XX
 *
 * Function: Memory Definition for extern all code base reference
 *
 * [Memory Map Description]
 *
 * Chip Internal Ram : 0x00-0xFF For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x000-0x7FF
 * Chip Other 85XX : External ram 0x000-0xFFF
 ***************************************************
 *
 * [OEM Memory Rang]
 * [External Ram]
 * 0x100-0x1FF   OEM RAM 
 * 0x200-0x2FF   OEM RAM SPI buffer array
 * 0x300-0x3FF   OEM RAM EC Space   
 * 0x400-0x4FF   OEM RAM
 * 0x500-0x5FF   OEM RAM      

 * 0x800-0x8FF   OEM RAM Ramdebug function.
 * 0x800-0x9FF   OEM RAM 
 * 0xA00-0xAFF   OEM RAM 
 * 0xB00-0xBFF   OEM RAM  
 * 0xC00-0xCFF   OEM RAM 
 * 0xD00-0xDFF   OEM RAM 
 * 0xE00-0xEFF   OEM RAM 
 * 0xF00-0xFFF   OEM RAM For HSPI ram code function 
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
XBYTE VCMD_Lenovo					_at_(ECRAM+0x00); 
XBYTE VDAT_Lenovo					_at_(ECRAM+0x01); 
XBYTE VSTA_Lenovo					_at_(ECRAM+0x02);

XBYTE VPC_Lenovo					_at_(ECRAM+0x06);
XBYTE VPC2_Lenovo					_at_(ECRAM+0x07);
XBYTE Device_Status_Lenovo          _at_(ECRAM+0x08);
XBYTE Device_Status_AllRF			_at_(ECRAM+0x09);

XBYTE   Fn_S_V_Flag        	        _at_(ECRAM+0x10);
XBYTE   Fn_S_V_Count      	        _at_(ECRAM+0x11);
XBYTE   Lenovo_PM_Cmd_count         _at_(ECRAM+0x12);
       


XBYTE   Host_BAT1_RMcap_L        	_at_(ECRAM+0x1E);   
XBYTE   Host_BAT1_RMcap_H           _at_(ECRAM+0x1F);



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ECRAM + 0x20

XBYTE   BAT1_STATUS					_at_(ECRAM+0x20);	//(BYTE)Battery#1 Data Status
//XBYTE   BAT1_RSOC					_at_(ECRAM+0x21);	//(BYTE)Battery1 Battery Percentage
XWORD	BT1_ALARM_STATUS		    _at_(ECRAM+0x22); //(WORD) Battery1 Alarm Status
//XBYTE   BAT1_FCcap_L        		_at_(ECRAM+0x24);   // (WORD)Battery1 last Fully Charge Capacity  // <<lw 2017/11/20
//XBYTE   BAT1_FCcap_H        		_at_(ECRAM+0x25);   // 
//XBYTE   BAT1_RMcap_L        		_at_(ECRAM+0x26);   // (WORD)Battery1 Remaining Capacity  // <<lw 2017/11/20
//XBYTE   BAT1_RMcap_H        		_at_(ECRAM+0x27);   // 
XBYTE  BAT1_temp_L         		    _at_(ECRAM+0x28);  //(WORD)Battery1 Battery Temperature 
XBYTE  BAT1_temp_H         		    _at_(ECRAM+0x29);  // 

XBYTE   BAT1_volt_L         		_at_(ECRAM+0x2A);   // (WORD)Battery1 Battery Voltage  
XBYTE   BAT1_volt_H         		_at_(ECRAM+0x2B);   // 
XBYTE   BAT1_current_L      		_at_(ECRAM+0x2C);   // (WORD)Battery1 Battery Average Current 
XBYTE   BAT1_current_H      		_at_(ECRAM+0x2D);   //  

XBYTE   BAT1_CC_L    	    		_at_(ECRAM+0x2E);   // Battery 1	
XBYTE   BAT1_CC_H    	   	 		_at_(ECRAM+0x2F);   // Battery 1	
XBYTE   BAT1_CV_L    	    		_at_(ECRAM+0x30);   // Battery 1
XBYTE   BAT1_CV_H    	    		_at_(ECRAM+0x31);   // Battery 1

XBYTE   BAT1_ALARM1        			_at_(ECRAM+0x32);   // Battery 1
XBYTE   BAT1_ALARM2         		_at_(ECRAM+0x33);   // Battery 1
XBYTE   BAT1_MFGF2L        			_at_(ECRAM+0x34);   //Battery 1
XBYTE   BAT1_MFGF2H         		_at_(ECRAM+0x35);   //Battery 1

XBYTE   BIOS_Tjmax_Toffset         	_at_(ECRAM+0x36);
XBYTE   CpuTemp         			_at_(ECRAM+0x37);

XWORD   EC_OptionalMfgFunction2    	_at_(ECRAM+0x38);
XBYTE   HotKey_SW                	_at_(ECRAM+0x3A);  

XBYTE LCD_BRIGHTNESS		    	_at_(ECRAM+0x3B);	
XBYTE B1SS    						_at_(ECRAM+0x3C);
XBYTE Manufacture_mode		   		_at_(ECRAM+0x3D);
XBYTE SystemWatts_Status		    _at_(ECRAM+0x3E);
XBYTE KeyboardMatrixID      		_at_(ECRAM+0x3F);
XBYTE OS_mode						_at_(ECRAM+0x40); 	//(BYTE)OS System Type DOS(00H),98(01H),2000(02H),ME(03H),XP(04H) ...
XBYTE OemAllDevices_state			_at_(ECRAM+0x41);
XBYTE OS_Type                   	_at_(ECRAM+0x42);
XBYTE OemNoVokeyFlag				_at_(ECRAM+0x43);
XBYTE Oem_For_Bios_Flag				_at_(ECRAM+0x44);
XBYTE Oem_Bios_Interface_1          _at_(ECRAM+0x45);
XBYTE ECMainVersionInfo				_at_(ECRAM+0x46);
XBYTE ECVersionInfo					_at_(ECRAM+0x47);	//(BYTE)EC DATA 5 FOR EXT COMMAND = 0x46B
//XBYTE OS_PM_STATE					_at_(ECRAM+0x48);	//(BYTE)POWER SOURCE STATUS    // <<lw 2017/11/20
XBYTE Bios_Battery_Health_0			_at_(ECRAM+0x49);
XBYTE Bios_Battery_Health_1			_at_(ECRAM+0x4A);
XBYTE Bios_Battery_Health_2			_at_(ECRAM+0x4B);
XBYTE BIOS_OEM_battery_health		_at_(ECRAM+0x4C);
XBYTE ME_GPIO33_Disable     		_at_(ECRAM+0x4D);
XBYTE EC_EXT_SOURCE_STATE			_at_(ECRAM+0x4E);	//(BYTE)EXTERN SOURCE STATUS	
XBYTE Sys_Power_Status				_at_(ECRAM+0x4F);

// #define ECRAM_EXT_CMD  ECRAM+0x050
XBYTE EC_EXT_CMD              		_at_(ECRAM_EXT_CMD+0x00);	//(BYTE)EC EXT COMMAND DEFAULE  
XBYTE EC_DAT1                 		_at_(ECRAM_EXT_CMD+0x01);	//(BYTE)EC DATA 1 FOR EXT COMMAND  
XBYTE EC_DAT2                 		_at_(ECRAM_EXT_CMD+0x02);	//(BYTE)EC DATA 2 FOR EXT COMMAND  
XBYTE EC_DAT3                 		_at_(ECRAM_EXT_CMD+0x03);	//(BYTE)EC DATA 3 FOR EXT COMMAND  
XBYTE Bat1_FW[8]					_at_(ECRAM+0x54);		// 0x54-0x5B
XBYTE Adpater_Status                _at_(ECRAM+0x5c);		//00-Normal adapter; 
															//01-incorrectly adapter; 
															//10-adpter power is not suitable.
XBYTE SYS_MISC1           			_at_(ECRAM+0x5D); 	// System Misc flag 1
XBYTE SYS_MISC2           			_at_(ECRAM+0x5E); 	// System Misc flag 2
XBYTE Oem_RTP_ID_CMD                _at_(ECRAM+0x5F);  


//#define ECRAM_SMB_PRTCL   ECRAM+0x060
XBYTE	SMB_PRTC            		_at_(ECRAM_SMB_PRTCL+0x00);   // EC SMB1 Protocol register
XBYTE	SMB_STS						_at_(ECRAM_SMB_PRTCL+0x01); 	// EC SMB1 Status register
XBYTE	SMB_ADDR      				_at_(ECRAM_SMB_PRTCL+0x02); 	// EC SMB1 Address register
XBYTE	SMB_CMD   					_at_(ECRAM_SMB_PRTCL+0x03); 	// EC SMB1 Command register
XBYTE	SMB_DATA     				_at_(ECRAM_SMB_PRTCL+0x04); 	// EC SMB1 Data register array (32 bytes)
XBYTE	SMB_DATA1[31]      	 		_at_(ECRAM_SMB_PRTCL+0x05);
XBYTE	SMB_BCNT  					_at_(ECRAM_SMB_PRTCL+0x24); 	// EC SMB1 Block Count register
XBYTE	SMB_ALRA    				_at_(ECRAM_SMB_PRTCL+0x25); 	// EC SMB1 Alarm Address register
XBYTE	SMB_ALRD0   				_at_(ECRAM_SMB_PRTCL+0x26); 	// EC SMB1 Alarm Data register 0
XBYTE	SMB_ALRD1   				_at_(ECRAM_SMB_PRTCL+0x27); 	// EC SMB1 Alarm Data register 1

XBYTE   BAT1_RSOC				    _at_(ECRAM+0x8C);

XBYTE   BAT1_FCcap_L        		_at_(ECRAM+0x8D); // (WORD)Battery1 last Fully Charge Capacity  // <<lw 2017/11/20

XBYTE   BAT1_FCcap_H        		_at_(ECRAM+0x8E); // // <<lw 2017/11/20


XBYTE   Lcd_Temp_H                   _at_(ECRAM+0x90);   //_at_(ECRAM+0x90)
XBYTE   Lcd_Temp_L                   _at_(ECRAM+0x91);   //_at_(ECRAM+0x91)
XBYTE   Cpu_Temp_H                   _at_(ECRAM+0x92);   //_at_(ECRAM+0x92)
XBYTE   Cpu_Temp_L                   _at_(ECRAM+0x93);   //_at_(ECRAM+0x93)
XBYTE   Gpu_Temp_H                   _at_(ECRAM+0x94);   //_at_(ECRAM+0x94)  
XBYTE   Gpu_Temp_L                   _at_(ECRAM+0x95);   //_at_(ECRAM+0x95)


XBYTE  Change_CpuTemp                _at_(ECRAM+0x96);

XBYTE	GpuTemp					     _at_(ECRAM+0x97);   //_at_(ECRAM+0x97)

XBYTE	LcdTemp					     _at_(ECRAM+0x98);   //_at_(ECRAM+0x98)

XBYTE  Change_GpuTemp                _at_(ECRAM+0x99);  

XBYTE  Change_LcdTemp                 _at_(ECRAM+0x9A);

XBYTE  Cpu_Tmp_Temp                   _at_(ECRAM+0x9B); 

XBYTE  Gpu_Tmp_Temp                   _at_(ECRAM+0x9C);

XBYTE   BAT1_RMcap_L        		  _at_(ECRAM+0x9D);   // (WORD)Battery1 Remaining Capacity   // <<lw 2017/11/20

XBYTE   BAT1_RMcap_H        		  _at_(ECRAM+0x9E);   // // <<lw 2017/11/20

XBYTE  Oem_CPU_Temp                   _at_(ECRAM+0x9F); 

XBYTE  Oem_GPU_Temp                   _at_(ECRAM+0xA0); 

XBYTE  Oem_LCD_Temp                   _at_(ECRAM+0xA1);

XBYTE  Read_CPU_Temp_OK               _at_(ECRAM+0xA2);
XBYTE  Read_GPU_Temp_OK               _at_(ECRAM+0xA3);
	
XBYTE  Sys_Temp_Check_Flag            _at_(ECRAM+0xA4);

XBYTE  Sys_Temp_Check_Cnt             _at_(ECRAM+0xA5);

XBYTE  Bat1_MaftName[8]               _at_(ECRAM+0xA6);   //0xA6-0xAD


XBYTE OS_PM_STATE					_at_(ECRAM+0xB0);    // <<lw 2017/11/20
XBYTE Bat_ShipMode_Cmd				_at_(ECRAM+0xB1);
XBYTE ACPI_OS_Delay_Count			_at_(ECRAM+0xB2);
XBYTE BAT1_CycleCount_L				_at_(ECRAM+0xB3);
XBYTE BAT1_CycleCount_H				_at_(ECRAM+0xB4);
XBYTE KeyboardID					_at_(ECRAM+0xB5);
XBYTE Oem_BAT1_ALARM         		_at_(ECRAM+0xB6);   // Battery 1

//XBYTE DebugFanRPMT		  			_at_(ECRAM+0xB7);



XBYTE BAT1_AVTEmpty_L		_at_(ECRAM+0xC0);
XBYTE BAT1_AVTEmpty_H		_at_(ECRAM+0xC1);
XBYTE BAT1_AVTFull_L		_at_(ECRAM+0xC2);
XBYTE BAT1_AVTFull_H		_at_(ECRAM+0xC3);
XBYTE BAT1_DCap_L			_at_(ECRAM+0xC4);
XBYTE BAT1_DCap_H			_at_(ECRAM+0xC5);
XBYTE BAT1_DVolt_L			_at_(ECRAM+0xC6);
XBYTE BAT1_DVolt_H			_at_(ECRAM+0xC7);




XBYTE Debug_Heating_switch	_at_(ECRAM+0xE1);  //lw 2017/12/18



XWORD BAT_SerialNumber				_at_(ECRAM+0xE2);

XBYTE  Oem_TP_Status                _at_(ECRAM+0xE4);

XBYTE  Fn_Win_State                 _at_(ECRAM+0xE5);  

XBYTE Temperature_Low_Flag          _at_(ECRAM+0xE6);

XBYTE HEAT_FLAG                     _at_(ECRAM+0xE7);

XBYTE Debug_Heating_Status         _at_(ECRAM+0xE8);  //<<2017/11/22 lw
XBYTE Debug_TIME					_at_(ECRAM+0xE9);//<<2017/11/22 lw



XBYTE ComCheckCnt					_at_(ECRAM+0xF0);

WORD  Oem_FAN1_CurrentRPM           _at_(ECRAM+0xF2);
WORD  Oem_FAN2_CurrentRPM           _at_(ECRAM+0xF4);
XBYTE ComCheckflag					_at_(ECRAM+0xF8);
XBYTE Debugflag						_at_(ECRAM+0xF9);
XBYTE ComMoniterflag				_at_(ECRAM+0xFA);
XBYTE DebugTCPU						_at_(ECRAM+0xFB);
WORD  DebugReadRPM   				_at_(ECRAM+0xFC);    
XBYTE DebugFanRPMT		  			_at_(ECRAM+0xFE);   //  ->0xB7
XBYTE DebugFanStatus	  			_at_(ECRAM+0xFF);


// gap
//***************Reserved 0xa3~ 0xff  *********************

//-------------------------------------------------------------------------------
//	0x200-0x2FF   OEM RAM 2  
//-------------------------------------------------------------------------------
XBYTE   SPIBuffer[256]      _at_(SPIBufferRAM+0x00);    // 256 bytes SPI read/write buffer

//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------

//+++++++++++++battery++++++++++++++++++++++++++++

XBYTE Oem_BatCtrl_F         	_at_(OEMRAM3+0x00);
WORD  BAT1_RMcap_Pre        	_at_(OEMRAM3+0x01);
XBYTE Bat_Test_Mode_f      	 	_at_(OEMRAM3+0x03); 
XBYTE BAT_Calibrate_Step    	_at_(OEMRAM3+0x04);
XBYTE BAT_Storagemode_Step		_at_(OEMRAM3+0x05);
XBYTE Oem_Globe_Flag 		    _at_(OEMRAM3+0x06);
XBYTE Oem_Globe_Flag1 		    _at_(OEMRAM3+0x07);

XBYTE DebugFan1VoltageOut    	_at_(OEMRAM3+0x08);


XBYTE  Oem_Device_Status 	    _at_(OEMRAM3+0x0c);
XBYTE  Oem_Globe_Flag2           _at_(OEMRAM3+0x0d);
XBYTE  Oem_GPU_EC_BLK          	_at_(OEMRAM3+0x0e);
XBYTE  Oem_PC_Beep_EN          	_at_(OEMRAM3+0x0f);
XBYTE  TDIM0_temp          		_at_(OEMRAM3+0x10);   // DRAM 0 temperature
XBYTE  TDIM1_temp          		_at_(OEMRAM3+0x11);   // DRAM 1 temperature
XBYTE  TPkg_temp           		_at_(OEMRAM3+0x12);   // 
XBYTE  TVGA_temp           		_at_(OEMRAM3+0x13);   // VGA Temperature
XBYTE  TSys_temp           		_at_(OEMRAM3+0x15);   // system Temperature
XSBYTE TCPU_temp           		_at_(OEMRAM3+0x16);   // CPU Temperature
XBYTE  PECI_CPU_temp       		_at_(OEMRAM3+0x17);   // Use PECI interface to read CPU temperature
XBYTE  TPKG_Pch_temp            _at_(OEMRAM3+0x18);   // PCH temperature  package 20bytes
XBYTE  Pch_temp_Smbus           _at_(OEMRAM3+0x19); 

XBYTE  Oem_KB_Status            _at_(OEMRAM3+0x2E);


//reserved 0x30,0x31

XBYTE SYS_TooHot_Cnt          _at_(OEMRAM3+0x32);

XBYTE GPU_INFO_FLG			    _at_(OEMRAM3+0x33); 
XBYTE GPU_INIT_CNT              _at_(OEMRAM3+0x34);
XBYTE OEM_2S_COUNT         	 	_at_(OEMRAM3+0x35);
XBYTE Adapter_Null_Counter 	 	_at_(OEMRAM3+0x36);
XBYTE Adapter_In_Counter 	 	_at_(OEMRAM3+0x37);
XBYTE Oem_Storage_mode_f 	 	_at_(OEMRAM3+0x38);
XBYTE Oem_Mute_Delay_Cnt      	_at_(OEMRAM3+0x39); 
XBYTE ledTestFlag      			_at_(OEMRAM3+0x3A); 
XBYTE Lenvo_dust_mode  			_at_(OEMRAM3+0x3C); 
XBYTE Lenvo_general_f   		_at_(OEMRAM3+0x3D);// 


XBYTE SCI_timer_RLOAD			    _at_(OEMRAM3+0x40);// (*(volatile unsigned char xdata *)0x0340)
XBYTE SCI_timer_cnt				     _at_(OEMRAM3+0x41);// (*(volatile unsigned char xdata *)0x0341)
XBYTE EC_STATE_BUF            	     _at_(OEMRAM3+0x42);// (*(volatile unsigned char xdata *)0x0342)  
XBYTE Oem_BatLedBlink_Cnt		     _at_(OEMRAM3+0x43);// (*(volatile unsigned char xdata*) 0x0343)
XBYTE Uart_flag 				     _at_(OEMRAM3+0x44);// (*(volatile BYTE xdata *)0x0344)
XWORD Uart_buffer_Inp_ptr     	     _at_(OEMRAM3+0x45);// (*(volatile WORD xdata *)0x0345)
XWORD Uart_buffer_Oup_ptr     	     _at_(OEMRAM3+0x47);// (*(volatile WORD xdata *)0x0347)
XBYTE OEM_flag_1         		     _at_(OEMRAM3+0x49);// (*(volatile BYTE xdata *)0x0349)
XBYTE ITS_GPU_BYTE1         	     _at_(OEMRAM3+0x4A);// (*(volatile BYTE xdata *)0x034A) //Read GPU internal TS to read GPU temperature through SMBUS
XBYTE ITS_GPU_BYTE2         	     _at_(OEMRAM3+0x4B);// (*(volatile BYTE xdata *)0x034B)
XBYTE ITS_GPU_BYTE3         	     _at_(OEMRAM3+0x4C);// (*(volatile BYTE xdata *)0x034C)
XBYTE ITS_GPU_BYTE4         	     _at_(OEMRAM3+0x4D);// (*(volatile BYTE xdata *)0x034D)
XBYTE Bat_ShipMode_Data_L		     _at_(OEMRAM3+0x4E);
XBYTE Bat_ShipMode_Data_H		     _at_(OEMRAM3+0x4F);
XWORD OEM_Debug_flag         	     _at_(OEMRAM3+0x50);// (*(volatile WORD xdata *)0x0350)
XWORD BAT1_RMcap_L_temp              _at_(OEMRAM3+0x52);// (*(volatile WORD xdata *)0x0352)
XWORD BAT1_FCcap_Pre        	     _at_(OEMRAM3+0x54);// (*(volatile WORD xdata *)0x0354)
XWORD SYSTEM_POWER_BATOnly_Current	 _at_(OEMRAM3+0x5A);// (*(volatile WORD xdata *)0x035A)
XWORD SYSTEM_POWER_BATProtect_C	  	 _at_(OEMRAM3+0x5C);// (*(volatile WORD xdata *)0x035C)
XWORD SystemWatts_BatChar_C       	 _at_(OEMRAM3+0x62);// (*(volatile WORD xdata*)   0x0362)  // current now  battery request
XWORD Pre_SystemWatts_BatChar_C   	 _at_(OEMRAM3+0x64);// (*(volatile WORD xdata*)   0x0364)
XBYTE SystemWatts_CHRStatus			 _at_(OEMRAM3+0x66);// (*(volatile unsigned char xdata*)0x0366)
XWORD SysCurrent				    _at_(OEMRAM3+0x67);// (*(volatile WORD xdata*) 0x0367)
XBYTE SystemWatts                   _at_(OEMRAM3+0x69);// (*(volatile BYTE xdata *)0x0369)
XBYTE SystemPowerCtrlStep           _at_(OEMRAM3+0x6A);// (*(volatile BYTE xdata *)0x036A)
XBYTE SystemWatts_Over_Cnt    	    _at_(OEMRAM3+0x6B);// (*(volatile BYTE xdata *)0x036B)
XBYTE SystemWatts_Resume_Cnt        _at_(OEMRAM3+0x6C);// (*(volatile BYTE xdata *)0x036C)
XWORD SystemWatts_BatChar_BK   	    _at_(OEMRAM3+0x6D);// (*(volatile WORD xdata *)0x036D)
XBYTE Power_Protect_Cnt  		    _at_(OEMRAM3+0x6F);// (*(volatile BYTE xdata *)0x036F)
XBYTE DebugECFlash          	    _at_(OEMRAM3+0x70);
XBYTE Oem_RTP_ID_Flag  			    _at_(OEMRAM3+0x80); 
XBYTE Oem_RTP_ID_Step  			    _at_(OEMRAM3+0x81);  
XBYTE Oem_RTP_ID_Index  		    _at_(OEMRAM3+0x82);  
XBYTE Oem_RTP_ID_LOOP_Index  	    _at_(OEMRAM3+0x83);  
XWORD Oem_RTP_ID_1s_T  			    _at_(OEMRAM3+0x84); 	 
XBYTE Oem_RTP_ID_1s_EN  		    _at_(OEMRAM3+0x86);	 
XWORD Oem_RTP_ID_PWR_Delay  	    _at_(OEMRAM3+0x87);  




XBYTE HomeBtn_Ass_F			     _at_(OEMRAM3+0xC0);
XBYTE EnterDeepSleep_ACDC_Cnt    _at_(OEMRAM3+0xC1);
XBYTE EnterDeepSleep_ACDC_f      _at_(OEMRAM3+0xC2);
XBYTE Check_Shutdown_cnt         _at_(OEMRAM3+0xC3);

XBYTE Check_Reset_cnt            _at_(OEMRAM3+0xC4);
XBYTE Check_DelayShutdown_cnt    _at_(OEMRAM3+0xC5);
XBYTE  R14Heating_Temp		     _at_(OEMRAM3+0xC6); 
XBYTE  HEAT_TEST_FLAG            _at_(OEMRAM3+0xC7);
XWORD	MAX_Heat_Time	         _at_(OEMRAM3+0xC8);
XWORD	Min_Heat_Time            _at_(OEMRAM3+0xCA);

XWORD	BATT_TEMP_PowerOn        _at_(OEMRAM3+0xCC); 





XBYTE POWER_FLAG1         _at_(OEMRAM3+0xD0); 	// EC power flag 1
XBYTE POWER_FLAG2         _at_(OEMRAM3+0xD1); 	// EC power flag 2
XBYTE POWER_FLAG3         _at_(OEMRAM3+0xD2); 	// EC power flag 3
 

XBYTE EVT_STATUS1         _at_(OEMRAM3+0xD6); 	// Event status flag 1
XBYTE EVT_STATUS2         _at_(OEMRAM3+0xD7); 	// Event status flag 2
XBYTE EVT_STATUS3         _at_(OEMRAM3+0xD8); 	// Event status flag 3
XBYTE MISC_FLAG1          _at_(OEMRAM3+0xD9); 	// Misc flag 1
XBYTE MISC_FLAG2          _at_(OEMRAM3+0xDA); 	// Misc flag 2
XBYTE MISC_FLAG3          _at_(OEMRAM3+0xDB); 	// Misc flag 3
XBYTE MISC_FLAG4          _at_(OEMRAM3+0xDC); 	// Misc flag 4
XBYTE BT1_STATUS1         _at_(OEMRAM3+0xDD);   // Battery 1 status1 flag
XBYTE BT1_STATUS2         _at_(OEMRAM3+0xDE);   // Battery 1 status2 flag
XBYTE BT1_STATUS3         _at_(OEMRAM3+0xDF);   // Battery 1

XBYTE EC_CPU_TEMP		  _at_(OEMRAM3+0xE0); //(BYTE)CPU Temperature
XBYTE B1SS_Bak            _at_(OEMRAM3+0xE1);
XBYTE FanSpeedLow		  _at_(OEMRAM3+0xE2);           
XBYTE FanSpeedHigh	 	  _at_(OEMRAM3+0xE3);
XBYTE BrgLevel            _at_(OEMRAM3+0xE4);   // Brightness level
XBYTE CrisisKeyStatus     _at_(OEMRAM3+0xE5);   // Crisis key flag
XBYTE PanelId             _at_(OEMRAM3+0xE6);   // Panel ID
XBYTE BAT1_ACCESSL    	  _at_(OEMRAM3+0xE7);   //Battery 1
XBYTE BAT1_ACCESSH    	  _at_(OEMRAM3+0xE8);   //Battery 1 
XBYTE BAT1_MODEL          _at_(OEMRAM3+0xE9);
XBYTE BAT1_MODEH          _at_(OEMRAM3+0xEA);
XBYTE PanelInitFlag       _at_(OEMRAM3+0xEF);






XBYTE ACPI_Count				_at_(OEMRAM3+0xF6);
XBYTE ACPI_Flag					_at_(OEMRAM3+0xF7);
XBYTE SysPostTime				_at_(OEMRAM3+0xF8);
XBYTE CoolBootTime		        _at_(OEMRAM3+0xF9);
XBYTE CoolBootFlag              _at_(OEMRAM3+0xFA);
XBYTE AdjustBLDelay             _at_(OEMRAM3+0xFB);



//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
//===============================================================================
// OEMRAM4 Offset 0x00 ~ 0x11   Power sequnce control 
XBYTE	SysPowState			_at_(PowerSequnceRAM+0x00); //(byte)
XBYTE	PWSeqStep			_at_(PowerSequnceRAM+0x01); //(byte)
XBYTE	DeepSleepCunt		_at_(PowerSequnceRAM+0x02); //(byte)
XWORD   DelayDoPowerSeq		_at_(PowerSequnceRAM+0x03); //(word)
XWORD   PowSeqDelay			_at_(PowerSequnceRAM+0x05); //(word)
XBYTE	ECAutoPowerOn		_at_(PowerSequnceRAM+0x07); //(byte)
XBYTE	ECWDTRSTNow			_at_(PowerSequnceRAM+0x08); //(byte)
XBYTE	CheckPowerStateIndex _at_(PowerSequnceRAM+0x09);//(byte)
XBYTE	SBSWReleaseCunt		_at_(PowerSequnceRAM+0x0A); //(byte)
XWORD	PSW_COUNTER         _at_(PowerSequnceRAM+0x0B); //(word)
XWORD	HWPG_TIMER          _at_(PowerSequnceRAM+0x0D); //(word)
XBYTE	ShutDnCause     	_at_(PowerSequnceRAM+0x0F); //(byte)
XWORD   PSWPressed_COUNTER  _at_(PowerSequnceRAM+0x10);//(word)
XWORD   PanelInit_COUNTER  _at_(PowerSequnceRAM+0x12);//(word)

//===============================================================================

//===============================================================================


//Reserved offset 0x05 ~ 0x0F
//===============================================================================



//===============================================================================
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
XWORD   LED_FLASH_CNT  		_at_(LEDRAM+0x00);  //(word) LED index
XWORD   BAT_LED_Cnt_ON	    _at_(LEDRAM+0x02);
XBYTE   BAT_LED_Cnt_OFF		_at_(LEDRAM+0x04);


//Reserved offset 0x02 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x28 ~ 0x2F   LCD variables
XBYTE   bBrightness         _at_(LCDRAM+0x00);  //(byte)
//Reserved offset 0x01 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x30 ~ 0x4F   ADC variables
XWORD	ADCAvg0				_at_(ADCRAM+0x00);
XWORD	ADCAvg1				_at_(ADCRAM+0x02);
XWORD	ADCAvg2				_at_(ADCRAM+0x04);
XWORD	ADCAvg3				_at_(ADCRAM+0x06);
XWORD	ADCAvg4				_at_(ADCRAM+0x08);
XWORD	ADCAvg5				_at_(ADCRAM+0x0A);
XWORD	Fix_ADCAvg0			_at_(ADCRAM+0x0C);
XWORD	Fix_ADCAvg1			_at_(ADCRAM+0x0E);

XBYTE	ADCDyTable1Index    _at_(ADCRAM+0x10);
XBYTE	ADCDyTable2Index    _at_(ADCRAM+0x11);
//Reserved offset 0x12 ~ 0x1F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x50 ~ 0x6F   SMBus center variables
XBYTE	SMBus1Flag1			_at_(SMBusCenterRAM+0x00);
XBYTE	SMBus1Flag2			_at_(SMBusCenterRAM+0x01);
XBYTE	SMBus1Flag3			_at_(SMBusCenterRAM+0x02);
XBYTE	SMBus1Flag4			_at_(SMBusCenterRAM+0x03);
XBYTE	SMBus1Flag5			_at_(SMBusCenterRAM+0x04);
XBYTE	SMBus2Flag1			_at_(SMBusCenterRAM+0x05);
XBYTE	SMBus2Flag2			_at_(SMBusCenterRAM+0x06);
XBYTE	SMBus2Flag3			_at_(SMBusCenterRAM+0x07);
XBYTE	SMBus2Flag4			_at_(SMBusCenterRAM+0x08);

XBYTE	ThermalSensorStatus	 _at_(SMBusCenterRAM+0x09);

XBYTE	SMBus3Flag1			_at_(SMBusCenterRAM+0x0A);
XBYTE	SMBusSelection	    _at_(SMBusCenterRAM+0x0B);
XBYTE	F_Service_SMBus1    _at_(SMBusCenterRAM+0x0C);
XBYTE	F_Service_SMBus2    _at_(SMBusCenterRAM+0x0D);
XBYTE	F_Service_SMBus3    _at_(SMBusCenterRAM+0x0E);
XBYTE	F_Service_SMBus4     _at_(SMBusCenterRAM+0x0F);
XBYTE	SMBus1ByteCunt	    _at_(SMBusCenterRAM+0x10);
XBYTE	SMBus2ByteCunt		_at_(SMBusCenterRAM+0x11);
XBYTE	SMBus3ByteCunt		_at_(SMBusCenterRAM+0x12);
XBYTE	SMBus1counter		_at_(SMBusCenterRAM+0x13);
XBYTE	SMBus2counter		_at_(SMBusCenterRAM+0x14);
XBYTE	SMBus3counter		_at_(SMBusCenterRAM+0x15);
XBYTE	SMBus1index			_at_(SMBusCenterRAM+0x16);
XBYTE	SMBus2index			_at_(SMBusCenterRAM+0x17);
XBYTE	SMBus3index			_at_(SMBusCenterRAM+0x18);
XBYTE   SMBus1InUsing       _at_(SMBusCenterRAM+0x19);
XBYTE   SMBus2InUsing       _at_(SMBusCenterRAM+0x1A);
XBYTE   SMBus3InUsing       _at_(SMBusCenterRAM+0x1B);
XBYTE   SMBus1TableSize     _at_(SMBusCenterRAM+0x1C);
XBYTE   SMBus2TableSize     _at_(SMBusCenterRAM+0x1D);
XBYTE   SMBus3TableSize     _at_(SMBusCenterRAM+0x1E);
XBYTE   SMBusXStatus        _at_(SMBusCenterRAM+0x1F);
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x70 ~ 0x9F   Battery 1 control variables
XBYTE   BAT1_CtrlStep       _at_(BAT1CtrlRAM+0x00);
XBYTE   BAT1_ID_Step        _at_(BAT1CtrlRAM+0x01);
XBYTE   BAT1_1SecTimer      _at_(BAT1CtrlRAM+0x02);
XBYTE   BAT1_S_Number       _at_(BAT1CtrlRAM+0x03);
XBYTE   ByteTemp01          _at_(BAT1CtrlRAM+0x04);
XBYTE   ByteTemp02          _at_(BAT1CtrlRAM+0x05);
XBYTE   BAT1_ID_TimeOut_CNT _at_(BAT1CtrlRAM+0x06);
XBYTE   BAT1_Number         _at_(BAT1CtrlRAM+0x07);
XBYTE   BAT1_FailCause      _at_(BAT1CtrlRAM+0x08);
XBYTE   BAT1_FirstDataIndex _at_(BAT1CtrlRAM+0x09);
XBYTE	INPUT_CURRENT_LO    _at_(BAT1CtrlRAM+0x0A);
XBYTE	INPUT_CURRENT_HI    _at_(BAT1CtrlRAM+0x0B);
XBYTE	CHARGE_CURRENT_LO   _at_(BAT1CtrlRAM+0x0C);
XBYTE	CHARGE_CURRENT_HI   _at_(BAT1CtrlRAM+0x0D);
XBYTE	CHARGE_VOLTAGE_LO   _at_(BAT1CtrlRAM+0x0E);    
XBYTE	CHARGE_VOLTAGE_HI   _at_(BAT1CtrlRAM+0x0F);
XBYTE	Charger_TimeOut     _at_(BAT1CtrlRAM+0x10);
XBYTE   WakeUpChrCunt_Min   _at_(BAT1CtrlRAM+0x11); 
XWORD   PreChrCunt_Min      _at_(BAT1CtrlRAM+0x12); 
XWORD   NormalChrCunt_Min   _at_(BAT1CtrlRAM+0x14); 
XWORD   WakeUpChrCunt       _at_(BAT1CtrlRAM+0x16);  
XWORD   PreChrCunt          _at_(BAT1CtrlRAM+0x18);  
XWORD   NormalChrCunt       _at_(BAT1CtrlRAM+0x1A);  
XBYTE   BAT1_OTCunt         _at_(BAT1CtrlRAM+0x1C);
XBYTE   BAT1_OVCunt         _at_(BAT1CtrlRAM+0x1D);
XBYTE   BAT1_BADCunt        _at_(BAT1CtrlRAM+0x1E);
XWORD   CHARGE_CURRENT_BK   _at_(BAT1CtrlRAM+0x1F);	
XWORD   CHARGE_VOLTAGE_BK   _at_(BAT1CtrlRAM+0x21);	
XBYTE   CHARGER_OPTION_L   	_at_(BAT1CtrlRAM+0x23);
XBYTE   CHARGER_OPTION_H   	_at_(BAT1CtrlRAM+0x24);
XWORD   BAT1_DeVol          _at_(BAT1CtrlRAM+0x25);
XWORD   BAT1_DeCap          _at_(BAT1CtrlRAM+0x27);
XBYTE   BK_BAT1_CtrlStep    _at_(BAT1CtrlRAM+0x29);
XBYTE   BAT1_Type_Flag      _at_(BAT1CtrlRAM+0x2A);



//===============================================================================
// OEMRAM4 Offset 0xA0 ~ 0xAF   Power sequnce control 
XBYTE   PowerStatusBK       _at_(PowerSequnce2RAM+0x00);	
XWORD   PowerOnWDT          _at_(PowerSequnce2RAM+0x01);
//===============================================================================
// OEMRAM4 Offset 0xB0 ~ 0xBF  Lightsensor control 
XBYTE   LIGHTDATE            _at_(LightsensorRAM+0x00);

XBYTE    NEED_MinHeatTime    _at_(OEMRAM4+0xB8);
 
XBYTE   CPU_HEAT_HIGH        _at_(OEMRAM4+0xB9); 

XBYTE   LCD_OS_Heating_Flag  _at_(OEMRAM4+0xBA); 
XWORD    AC_Current          _at_(OEMRAM4+0xBB);//(OEMRAM4+0xBB)  adapter current



//===============================================================================
// OEMRAM4 Offset 0xF0 ~ 0xFF   Event debounce counter 
XBYTE	DEBOUNCE_CONT1		_at_(DebounceRAM+0x00); //(byte)
XBYTE	DEBOUNCE_CONT2		_at_(DebounceRAM+0x01); //(byte)
XBYTE	DEBOUNCE_CONT3		_at_(DebounceRAM+0x02); //(byte)
XBYTE	DEBOUNCE_CONT4		_at_(DebounceRAM+0x03); //(byte) 
XBYTE	DEBOUNCE_CONT5		_at_(DebounceRAM+0x04); //(byte)
XBYTE	DEBOUNCE_CONT6		_at_(DebounceRAM+0x05); //(byte)
XBYTE	DEBOUNCE_CONT7		_at_(DebounceRAM+0x06); //(byte)
XBYTE	DEBOUNCE_CONT8		_at_(DebounceRAM+0x07); //(byte)
XBYTE	DEBOUNCE_CONT9		_at_(DebounceRAM+0x08); //(byte) 
XBYTE	DEBOUNCE_CONT10		_at_(DebounceRAM+0x09); //(byte)
XBYTE	DEBOUNCE_CONT11		_at_(DebounceRAM+0x0A); //(byte) 
XBYTE	DEBOUNCE_CONT12		_at_(DebounceRAM+0x0B); //(byte)
XBYTE	DEBOUNCE_CONT13		_at_(DebounceRAM+0x0C); //(byte)
XBYTE	DEBOUNCE_CONT14		_at_(DebounceRAM+0x0D); //(byte)
XBYTE	DEBOUNCE_CONT15		_at_(DebounceRAM+0x0E); //(byte)
XBYTE	DEBOUNCE_CONT16		_at_(DebounceRAM+0x0F); //(byte) 
//===============================================================================

//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
//===============================================================================
// OEMRAM5 Offset 0x00 ~ 0x3F   For fan control

XWORD	FAN1_CurrentRPM		_at_(FanCtrlRAM+0x00);
XWORD	FAN1_GoalRPM 		_at_(FanCtrlRAM+0x02);
XBYTE	FAN1_Level			_at_(FanCtrlRAM+0x04);
XBYTE	temperature1		_at_(FanCtrlRAM+0x05);	
XBYTE	Debugtemperature1	_at_(FanCtrlRAM+0x06);			
XBYTE	FanFullOnCont		_at_(FanCtrlRAM+0x07);
XWORD	DustTotleCont		_at_(FanCtrlRAM+0x08);

XWORD	FAN2_CurrentRPM		_at_(FanCtrlRAM+0x0A);
XWORD	FAN2_GoalRPM 		_at_(FanCtrlRAM+0x0C);
XBYTE	FAN2_Level			_at_(FanCtrlRAM+0x0E);
XBYTE	temperature2		_at_(FanCtrlRAM+0x0F);
XBYTE	Debugtemperature2	_at_(FanCtrlRAM+0x10);
XBYTE   Bktemperature       _at_(FanCtrlRAM+0x11);
XBYTE   Maxtemperature      _at_(FanCtrlRAM+0x12); 
XBYTE   Bk1FAN_Level        _at_(FanCtrlRAM+0x13);
XBYTE   Bk2FAN_Level        _at_(FanCtrlRAM+0x14);
XBYTE   FanLevel_t          _at_(FanCtrlRAM+0x15);  
XBYTE   Fan_Adjust_Dir      _at_(FanCtrlRAM+0x16);


//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function 
XBYTE   PECIReadBuffer[16]  _at_( PECICtrlRAM + 0x000);
XBYTE   PECIWriteBuffer[16] _at_( PECICtrlRAM + 0x010);
XBYTE   PECI_CRC8           _at_( PECICtrlRAM + 0x020);
XBYTE   PECI_CompletionCode _at_( PECICtrlRAM + 0x021);
XBYTE   PECI_PCIConfigAddr[4] _at_( PECICtrlRAM + 0x022);

XBYTE   PECI_PowerCtrlStep  _at_( PECICtrlRAM + 0x030);
XBYTE   PECI_PowerUnit      _at_( PECICtrlRAM + 0x031);
XBYTE   PECI_EnergyUnit     _at_( PECICtrlRAM + 0x032);
XBYTE   PECI_TimeUnit       _at_( PECICtrlRAM + 0x033);
XBYTE   PECI_PL2Watts       _at_( PECICtrlRAM + 0x034);
XBYTE   PECI_MAXPL2         _at_( PECICtrlRAM + 0x035);
XBYTE   PECI_PL1TDP         _at_( PECICtrlRAM + 0x036);
XBYTE   PECI_PL1Time        _at_( PECICtrlRAM + 0x037);
XBYTE   PECI_Ctrl           _at_( PECICtrlRAM + 0x038);
XBYTE   PECI_AdaptorWatts   _at_( PECICtrlRAM + 0x039);
XBYTE   PECI_SystemWatts    _at_( PECICtrlRAM + 0x03A);
XBYTE   PECI_Algorithm_Delay     _at_( PECICtrlRAM + 0x03B);
LWORD   PECI_ErrorCount         _at_( PECICtrlRAM + 0x03C);
XBYTE   PECI_StressToolBuf[32]  _at_( PECICtrlRAM + 0x040);
XBYTE   PSTB_Timer              _at_( PECICtrlRAM + 0x060);
XBYTE   PSTB_CmdStatus          _at_( PECICtrlRAM + 0x061);
XBYTE   PSTB_RepeatIntervalCount    _at_( PECICtrlRAM + 0x062);  
LWORD   PSTB_RepeatCycle        _at_( PECICtrlRAM + 0x063);
XBYTE	CPUTjmax			    _at_( PECICtrlRAM + 0x067);
XBYTE	ReadCPUTjmaxCUNT        _at_( PECICtrlRAM + 0x068);
XBYTE   StressToolReadBufIndex  _at_( PECICtrlRAM + 0x069);
LWORD   PECI_PkgPower_Pre 		_at_( PECICtrlRAM + 0x06A);  
LWORD   PECI_PkgPower_Cur 		_at_( PECICtrlRAM + 0x06E);

LWORD    PECI_PkgPower           _at_( PECICtrlRAM + 0x072);
LWORD    PECI_PkgPower_average   _at_( PECICtrlRAM + 0x076);
XBYTE    PECI_PkgPower_average_count   _at_( PECICtrlRAM + 0x07a);


//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 

XBYTE   SPI_Mouse_Buf[3]        _at_( SPI_Mouse + 0x00);
XBYTE   SPI_Mouse_DeltaX        _at_( SPI_Mouse + 0x03);
XBYTE   SPI_Mouse_DeltaY        _at_( SPI_Mouse + 0x04);
XBYTE   SPI_Mouse_BYTE1         _at_( SPI_Mouse + 0x05);
XBYTE   SPI_Mouse_XMovement     _at_( SPI_Mouse + 0x06);
XBYTE   SPI_Mouse_YMovement     _at_( SPI_Mouse + 0x07);
XBYTE   SPI_Mouse_Buf_Index     _at_( SPI_Mouse + 0x08);
XBYTE   SPI_Mouse_Misc          _at_( SPI_Mouse + 0x09);
XBYTE   SPI_Mouse_ID            _at_( SPI_Mouse + 0x0A);

//Reserved offset 0x0B ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
XBYTE 	SCI_Event_In_Index 					_at_( SCI_Qevent_Ctrl + 0x00);
XBYTE 	SCI_Event_Out_Index 				_at_( SCI_Qevent_Ctrl + 0x01);
XBYTE 	SCI_Event_Buffer[EVENT_BUFFER_SIZE] _at_( SCI_Qevent_Ctrl + 0x02); // EVENT_BUFFER_SIZE bytes

XBYTE 	PD_SCI_Event_In_Index 			    _at_( SCI_Qevent_Ctrl + 0x10);
XBYTE 	PD_SCI_Event_Out_Index 				_at_( SCI_Qevent_Ctrl + 0x11);
XBYTE 	PD_SCI_Event_Buffer[PENDING_BUFFER] _at_( SCI_Qevent_Ctrl + 0x12); // PENDING_BUFFER bytes

//===============================================================================
// OEMRAM5 Offset 0xF0 ~ 0xFF   For OEM HSPI function
XBYTE   HSPI_SelfRamCode_Index              _at_( HSPI_Ctrl + 0x00);
XBYTE   HSPI_tempcmd                        _at_( HSPI_Ctrl + 0x01);
XBYTE   HSPI_FPT_timeout                    _at_( HSPI_Ctrl + 0x02);
XBYTE   HSPI_Misc1                          _at_( HSPI_Ctrl + 0x03);




//===============================================================================

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x800-0x8FF   OEM RAM 8  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x900-0x9FF   OEM RAM 9  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xA00-0xAFF   OEM RAM A  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xB00-0xBFF   OEM RAM B  
//-------------------------------------------------------------------------------
//*******************************************************************************


//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xC00-0xCFF   OEM RAM C  
//-------------------------------------------------------------------------------
//*******************************************************************************
LWORD HashRandom[5]						_at_ (OEMRAMC+0x00);   
LWORD SHA1ECProcV[5]					_at_ (OEMRAMC+0x20); 
LWORD Respond[5]						_at_ (OEMRAMC+0x40); 

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xD00-0xDFF   OEM RAM D  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xE00-0xEFF   OEM RAM E  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xF00-0xFFF   OEM RAM F  
//-------------------------------------------------------------------------------
//*******************************************************************************



