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
 
#ifndef OEM_MEMORY_H
#define OEM_MEMORY_H

#define EC_RAMBase 		    0x0000

#define OEMRAM1 		    EC_RAMBase+0x0100   // EC_RAMBase+0x0100 
#define OEMRAM2 		    EC_RAMBase+0x0200   // EC_RAMBase+0x0200 
#define OEMRAM3 		    EC_RAMBase+0x0300   // EC_RAMBase+0x0300 
#define OEMRAM4 		    EC_RAMBase+0x0400   // EC_RAMBase+0x0400 
#define OEMRAM5 		    EC_RAMBase+0x0500   // EC_RAMBase+0x0500 

#define OEMRAM8 		    EC_RAMBase+0x0800   // EC_RAMBase+0x0800 
#define OEMRAM9 		    EC_RAMBase+0x0900   // EC_RAMBase+0x0900 
#define OEMRAMA 		    EC_RAMBase+0x0A00   // EC_RAMBase+0x0A00 
#define OEMRAMB 		    EC_RAMBase+0x0B00   // EC_RAMBase+0x0B00 
#define OEMRAMC 		    EC_RAMBase+0x0C00   // EC_RAMBase+0x0C00 
#define OEMRAMD 		    EC_RAMBase+0x0D00   // EC_RAMBase+0x0D00 
#define OEMRAME 		    EC_RAMBase+0x0E00   // EC_RAMBase+0x0E00 
#define OEMRAMF 		    EC_RAMBase+0x0F00   // EC_RAMBase+0x0F00 

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define ECRAM		         OEMRAM1
#define ECRAM_Lenovo        ECRAM+0x00
#define ECRAM_BAT1          ECRAM+0x20 
#define ECRAM_EXT_CMD  	 	ECRAM+0x50 
#define ECRAM_SMB_PRTCL     ECRAM+0x60
#define ECRAM_BAT2          ECRAM+0xC0       

extern XBYTE VCMD_Lenovo;			 //_at_(ECRAM+0x00); 
extern XBYTE VDAT_Lenovo;			 //_at_(ECRAM+0x01); 
extern XBYTE VSTA_Lenovo;			 //_at_(ECRAM+0x02);

extern XBYTE VPC_Lenovo;			 //_at_(ECRAM+0x06);
#define One_Key_Bit_vpc             BIT0
#define Genenal_Bit_vpc				BIT1
#define Inverter_Bit_vpc			BIT2
#define Novo_Bit_vpc                BIT3
#define Brightness_Bit_vpc          BIT4
#define TouchPad_Bit_vpc			BIT5
#define Display_Bit_vpc				BIT6
#define Camera_Bit_vpc				BIT7

extern XBYTE VPC2_Lenovo;			//_at_(ECRAM+0x07);
#define MIC_VPC2			        BIT0
#define All_RF_VPC2					BIT1
#define Switch_Display_VPC2			BIT4
#define App_Control_RF_VPC2         BIT5



 
 
extern XBYTE Device_Status_Lenovo; 	//_at_(ECRAM+0x08);
#define Wireless_S_B				BIT0
#define Bluetooth_S_B        		BIT1
#define Inverter_S_B          		BIT2
#define Novo_S_B					BIT3
#define TouchPad_S_B				BIT4
#define Camera_S_B					BIT5
#define RF3G_S_B					BIT6
#define RFALL_S_B					BIT7
 
extern XBYTE Device_Status_AllRF;	//_at_(ECRAM+0x09);
#define Wireless_S_B_AllRF			BIT0
#define Bluetooth_S_B_AllRF        	BIT1
#define Super_performance_F        	BIT2
#define LPCRST_F					BIT3
#define LVDS_BKLT_F					BIT4
#define MIC_S_B				        BIT5
#define RF3G_S_B_AllRF				BIT6
#define Lost_Alarm_ONOFF            BIT7  // 0---on    1----off

extern XBYTE   Fn_S_V_Flag;
#define  _FN_BIT   BIT0
#define  _S_BIT    BIT1
#define  _V_BIT    BIT2




extern XBYTE   Fn_S_V_Count;

extern XBYTE Lenovo_PM_Cmd_count;




extern XBYTE   Host_BAT1_RMcap_L;	//_at_(ECRAM+0x1E);   
extern XBYTE   Host_BAT1_RMcap_H;   // _at_(ECRAM+0x1F);


/*  BATTERYS INFORMATION	 */ 

//ECRAM_BAT1           ECRAM+0x20 

 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
extern XBYTE	 BAT1_STATUS; 			     //_at_(ECRAM+0x20);	 //(BYTE)Battery#1 Data Status
#define          Oem_BAT1_valid              BIT0

//extern XBYTE	 BAT1_RSOC;					 //_at_(ECRAM+0x21);	 //(BYTE)Battery1 Battery Percentage ........(0x0D) - BYTE.

extern XWORD	 BT1_ALARM_STATUS;		    //_at_(ECRAM+0x22);	 //(BYTE)Battery1 Battery Status  ...........(0x16)
//Represent the status BAT1_ALARM1 BAT1_ALARM2



//extern XBYTE	 BAT1_FCcap_L;				 //_at_(ECRAM+0x24);	 // (WORD)Battery1 Fully Charge Capacity  ....(0x10) - word.
//extern XBYTE	 BAT1_FCcap_H;				 //_at_(ECRAM+0x25);	 // 
//extern XBYTE	 BAT1_RMcap_L;				 //_at_(ECRAM+0x26);	 // (WORD)Battery1 Remaining Capacity  .......(0x0F) - word.
//extern XBYTE	 BAT1_RMcap_H;				 //_at_(ECRAM+0x27);	 // 
extern XBYTE	 BAT1_temp_L;				 //_at_(ECRAM+0x28);	 //(WORD)Battery1 Battery Temperature  ......(0x08) - word.
extern XBYTE	 BAT1_temp_H;				 //_at_(ECRAM+0x29);	 // 
 
extern XBYTE	 BAT1_volt_L;				 //_at_(ECRAM+0x2A);	 // (WORD)Battery1 Battery Voltage	..........(0x09) - word.
extern XBYTE	 BAT1_volt_H;				 //_at_(ECRAM+0x2B);	 // 
extern XBYTE	 BAT1_current_L; 			 //_at_(ECRAM+0x2C);	 // (WORD)Battery1 Battery Average Current	..(0x0B) - word.
extern XBYTE	 BAT1_current_H; 			 //_at_(ECRAM+0x2D);	 //  
 
extern XBYTE	 BAT1_CC_L;					 //_at_(ECRAM+0x2E);	 // Battery 1	 
extern XBYTE	 BAT1_CC_H;					 //_at_(ECRAM+0x2F);	 // Battery 1	 
extern XBYTE	 BAT1_CV_L;					 //_at_(ECRAM+0x30);	 // Battery 1
extern XBYTE	 BAT1_CV_H;					 //_at_(ECRAM+0x31);	 // Battery 1
 

extern XBYTE     BAT1_ALARM1;				 //_at_(ECRAM+0x32);	 // Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBerror0    	BIT0            // error code bit0
#define SMBerror1    	BIT1            // error code bit1
#define SMBerror2      	BIT2            // error code bit2
#define SMBerror3      	BIT3            // error code bit3
#define FullyDsg    	BIT4            // statusfully discharged
#define FullyChg     	BIT5            // statusfully charged
#define Dsg         	BIT6            // statusdischarging
#define Initialized  	BIT7            // statusgauge initialized
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	 BAT1_ALARM2;				 //_at_(ECRAM+0x33);	 // Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RemTime_alarm	BIT0            // alarmremaining time
#define RemCap_alarm  	BIT1            // alarmremaining capacity
#define TermDsg_alarm 	BIT3            // alarmterminate discharge
#define OverTemp_alarm 	BIT4            // alarmover temperature
#define TermChg_alarm 	BIT6            // alarmterminate charge
#define OverChg_alarm 	BIT7            // alarmover charge
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  

extern XBYTE	 BAT1_MFGF2L;				 //_at_(ECRAM+0x34);	//Battery 1
extern XBYTE	 BAT1_MFGF2H;				 //_at_(ECRAM+0x35);	//Battery 1
extern XBYTE   	 BIOS_Tjmax_Toffset;         //_at_(ECRAM+0x36);
#define Toffset_f       BIT7
extern XBYTE      CpuTemp;					//_at_(ECRAM+0x37);

//***************Reserved ECRam offset 0x37 *********************

extern XWORD	 EC_OptionalMfgFunction2;	 //_at_(ECRAM+0x38); 
extern XBYTE     HotKey_SW;                  //_at_(ECRAM+0x3A);                    

extern XBYTE 	 LCD_BRIGHTNESS;			 //_at_(ECRAM+0x3B);
extern XBYTE 	 B1SS; 						 //_at_(ECRAM+0x3C);
#define BAT_discharge_f	BIT0
#define BAT_charge_f	BIT1

extern XBYTE Manufacture_mode;              //_at_(ECRAM+0x3D);
extern XBYTE SystemWatts_Status;          	//_at_(ECRAM+0x3E)  
extern XBYTE KeyboardMatrixID;        	   // _at_(ECRAM+0x3F) 




extern XBYTE OS_mode;					//_at_(ECRAM+0x40); Lable:	OS System Type DOS(00H),Linux:0x01 for RN1503
#define OS_mode_flag				0x07		// bit 2,1,0
										 		// 	 000: DOS mode
										 		// 	 001: Windows 98
										 		// 	 010: Windows 2000
										 		// 	 011: Windows ME
										 		// 	 100: Windows XP
 
extern XBYTE OemAllDevices_state;		  //_at_(ECRAM+0x41)
#define Bluetooth_exist         BIT0
#define G3_exist         		BIT1
#define Wireless_exist         	BIT2
#define Camera_exist        	BIT3
#define SysStart                BIT4
#define Pm_Em_exist             BIT5       // 0: not exist ; 1: exist
#define Beep_Disable            BIT6       // 0: enable beep ; 1: disable beep
#define Post_Over_f             BIT7       // when post over, host set this bit

extern XBYTE OS_Type;                  	//_at_(ECRAM+0x42);
 //  
 // 										0 - Win 2000
 // 									   	1 - Win 98/Se
 // 										2 - Win Me
 // 										3 - Linux
 // 										4 - WinXP
 // 										5 - Windows Server 2003										
 // 										6 - FreeBSD				  
 // 										7 - HP-UX
 // 										8 - OpenVMS			   
 //;-------------------New Values Added -----------------------------
 
 // 									 	9 - WinXP SP1
 // 									 	10 - WinXP SP2
 // 									 	11 - WinXP SP3    
 // 									 	12 - Vista
 // 									 	13 - Vista SP1
 // 										14 - Win7
 
extern XBYTE OemNoVokeyFlag;			 	// _at_(ECRAM+0x43) 
extern XBYTE Oem_For_Bios_Flag;			 	//_at_(ECRAM+0x44)
#define Forreset			BIT0    //when set,do not shutdown southbridge
#define EC_flashed			BIT1	//ec has been flashed should reset ec domain 

extern XBYTE Oem_Bios_Interface_1;        	// _at_(ECRAM+0x45);
#define Biosflash_AC_IN    		BIT0
#define Biosflash_BatCap_30     BIT1
#define Biosflash_DC_IN         BIT2

extern XBYTE ECMainVersionInfo;			  	//_at_(ECRAM+0x46);
extern XBYTE ECVersionInfo;				 	//_at_(ECRAM+0x47)

extern XBYTE OS_PM_STATE;					//_at_(ECRAM+0xB0);	//(BYTE)POWER SOURCE STATUS
#define OS_AC_IN					BIT0 	// =1 AC IN
#define OS_BAT1_IN					BIT1	// =1 BAT1 IN
#define OS_BAT2_IN					BIT2	// =1 BAT2 IN


extern XBYTE Bios_Battery_Health_0; 		//_at_(ECRAM+0x49)
#define EDCC 	BIT0		// End Calibration cycle     0:start   1:end
#define ALSC 	BIT1		// ALS(Ambient Light Sensor), N/A
#define CDMB 	BIT2		// Initiate a Calibrate cycle for the Main battery
#define CCSB 	BIT3		// Initiate a Calibrate cycle for the second battery
#define BTSM 	BIT4		// Let kbc to apply battery storage mode.
#define BTCM 	BIT5		// Let kbc to apply battery cycle mode   1:enable  0:disable change to fast charge flag
#define LBTM 	BIT6		// Let kbc to apply longest battery mode.
#define CSBM 	BIT7		// Clear bit of advise user to select battery mode
#define Bios_Battery_Health_0_mode		(EDCC+BTCM)

extern XBYTE Bios_Battery_Health_1;			//_at_(ECRAM+0x4A)
#define HYMS 	BIT0
#define HDME 	BIT1
#define HGMF 	BIT2
#define SWCS 	BIT3
#define CREC 	BIT4		// For Method(SALS, 1, Serialized), 
#define DCRC 	BIT5
#define ALSS 	BIT6
extern XBYTE Bios_Battery_Health_2;			//_at_(ECRAM+0x4B)
#define IPEN 	BIT0
#define MBBD 	BIT1		// indicates the main battery is bad
#define SBBD 	BIT2		// indicates the second battery is bad
#define MBQC    BIT3        // indicates the main battery support quick charge or not     1: support   0: don't support
#define ENQC	BIT4        // Host enable or disable quick charge

extern XBYTE BIOS_OEM_battery_health;	//_at_(ECRAM+0x4C)
#define HOST_end_calibrate			BIT0 //host end calibrate exit battery calibrate
#define HOST_BTCM					BIT1 //host end storage mode
#define HOST_SMBUS_GET              BIT2
#define HOST_STM_NOTIFY             BIT3
#define HOST_BAT_Authentication		BIT4
#define HOST_BAT_LIFE_TEST_MODE		BIT5
#define HOST_Auto_mode_f			BIT6

extern XBYTE ME_GPIO33_Disable;  			// _at_(ECRAM+0x4D)  

extern XBYTE EC_EXT_SOURCE_STATE;			// _at_(ECRAM+0x4E);	//(BYTE)EXTERN SOURCE STATUS
#define LID_CLOSE_Act			BIT0		// =1 when LID_CLOSE# = Low

extern XBYTE Sys_Power_Status;				//_at_(ECRAM+0x4F);		 						            //BIT1 .. BIT7 RESERVED

// #define ECRAM_EXT_CMD  ECRAM+0x050
extern XBYTE EC_EXT_CMD;            		//_at_(ECRAM_EXT_CMD+0x00))	//(BYTE)EC EXT COMMAND DEFAULE = 0x0460
extern XBYTE EC_DAT1;               		//_at_(ECRAM_EXT_CMD+0x01))	//(BYTE)EC DATA 1 FOR EXT COMMAND = 0x0461
extern XBYTE EC_DAT2;               		//_at_(ECRAM_EXT_CMD+0x02))	//(BYTE)EC DATA 2 FOR EXT COMMAND = 0x0462
extern XBYTE EC_DAT3;               		//_at_(ECRAM_EXT_CMD+0x03))	//(BYTE)EC DATA 3 FOR EXT COMMAND = 0x0463

extern XBYTE Bat1_FW[8];	//_at_(ECRAM+0x54);		// 0x54-0x5B

extern XBYTE Adpater_Status;	//_at_(ECRAM+0x5c);
#define NORMAL_ADAPTER               0X00
#define INCORRECTLY_ADAPTER          0x01
#define NOTSUITABLE_ADAPTER          0x10


extern XBYTE    SYS_MISC1;              //(ECRAM+0x5d)  System Misc flag 1  
#define ACPI_OS         	BIT0        // 1: system in ACPI environment
#define Bat1_Firm_En		BIT1		// 1: Battery Enable      host side
#define BAT_FW_UP			BIT2		// 1: Battery Firmware updata Enable   0:  charger  disable fail
//#define BAT_Balance			BIT4		// 1: Balance mode on         //lw
#define OFF_ALW				BIT5		// 0:close alw_on		1:reserve alw_on
#define Oem_Backlight		BIT7		// 0:off		1:on



extern XBYTE    SYS_MISC2;              //(ECRAM+0x5e)  System Misc flag 2
#define  Sys_WorkMode     BIT0 // 1:system in recovery mode 0:system in normal mode



extern XBYTE Oem_RTP_ID_CMD;         ////_at_(ECRAM+0x5f);  
#define Synaptics_TP_ID                BIT0
#define Elan_TP_ID                     BIT1
#define ALPS_TP_ID                     BIT2
#define Read_TP_ID_ERROR			   BIT6
#define Read_TP_ID_SUCCESS             BIT7


//#define ECRAM_SMB_PRTCL   ECRAM+0x060
extern XBYTE	SMB_PRTC;            		//_at_(ECRAM_SMB_PRTCL+0x00);   // EC SMB1 Protocol register
extern XBYTE	SMB_STS;					//_at_(ECRAM_SMB_PRTCL+0x01); 	// EC SMB1 Status register
extern XBYTE	SMB_ADDR;      				//_at_(ECRAM_SMB_PRTCL+0x02); 	// EC SMB1 Address register
extern XBYTE	SMB_CMD;   					//_at_(ECRAM_SMB_PRTCL+0x03); 	// EC SMB1 Command register
extern XBYTE	SMB_DATA;     				//_at_(ECRAM_SMB_PRTCL+0x04); 	// EC SMB1 Data register array (32 bytes)
extern XBYTE	SMB_DATA1[31];      	 	//_at_(ECRAM_SMB_PRTCL+0x05);
extern XBYTE	SMB_BCNT;  					//_at_(ECRAM_SMB_PRTCL+0x24); 	// EC SMB1 Block Count register
extern XBYTE	SMB_ALRA;    				//_at_(ECRAM_SMB_PRTCL+0x25); 	// EC SMB1 Alarm Address register
extern XBYTE	SMB_ALRD0;   				//_at_(ECRAM_SMB_PRTCL+0x26); 	// EC SMB1 Alarm Data register 0
extern XBYTE	SMB_ALRD1;   				//_at_(ECRAM_SMB_PRTCL+0x27); 	// EC SMB1 Alarm Data register 1



extern XBYTE  BAT1_RSOC;				   //_at_(ECRAM+0x8C);
extern XBYTE  BAT1_FCcap_L;        		   //_at_(ECRAM+0x8D); // (WORD)Battery1 last Fully Charge Capacity  
extern XBYTE  BAT1_FCcap_H;        		   //_at_(ECRAM+0x8E);  // 



extern XBYTE   Lcd_Temp_H;                 //_at_(ECRAM+0x90);
extern XBYTE   Lcd_Temp_L;                 //_at_(ECRAM+0x91);
extern XBYTE   Cpu_Temp_H;                 //_at_(ECRAM+0x92);
extern XBYTE   Cpu_Temp_L;                 //_at_(ECRAM+0x93);
extern XBYTE   Gpu_Temp_H;                 //_at_(ECRAM+0x94);   
extern XBYTE   Gpu_Temp_L;                 //_at_(ECRAM+0x95);

extern XBYTE  Change_CpuTemp;              //_at_(ECRAM+0x96);

 
extern XBYTE  GpuTemp;				       //_at_(ECRAM+0x97);
extern XBYTE  LcdTemp;				       //_at_(ECRAM+0x98);


extern XBYTE  Change_GpuTemp;              //_at_(ECRAM+0x99);  
extern XBYTE  Change_LcdTemp;              //_at_(ECRAM+0x9A);

extern XBYTE  Cpu_Tmp_Temp;               // _at_(ECRAM+0x9B); 

extern XBYTE  Gpu_Tmp_Temp;               // _at_(ECRAM+0x9C); 

extern XBYTE  BAT1_RMcap_L;        		  //_at_(ECRAM+0x9D);   // (WORD)Battery1 Remaining Capacity  

extern XBYTE  BAT1_RMcap_H;        		 // _at_(ECRAM+0x9E);   // 


extern XBYTE  Oem_CPU_Temp;               //_at_(ECRAM+0x9F); 

extern XBYTE  Oem_GPU_Temp;               //_at_(ECRAM+0xA0); 

extern XBYTE  Oem_LCD_Temp;               //_at_(ECRAM+0xA1);

extern XBYTE  Read_CPU_Temp_OK;          //_at_(ECRAM+0xA2);
extern XBYTE  Read_GPU_Temp_OK;          //_at_(ECRAM+0xA3);

extern XBYTE  Sys_Temp_Check_Flag;       //_at_(ECRAM+0xA4);

extern XBYTE  Sys_Temp_Check_Cnt;        //_at_(ECRAM+0xA5);

extern XBYTE Bat1_MaftName[8];	         //_at_(ECRAM+0xA6)-_at_(ECRAM+0xAD)


extern XBYTE Bat_ShipMode_Cmd;	//_at_(ECRAM+0xB1);
extern XBYTE ACPI_OS_Delay_Count;	//_at_(ECRAM+0xB2);
extern XBYTE BAT1_CycleCount_L;	//_at_(ECRAM+0xB3);
extern XBYTE BAT1_CycleCount_H;	//_at_(ECRAM+0xB4);
extern XBYTE KeyboardID;	//_at_(ECRAM+0xB5);
extern XBYTE Oem_BAT1_ALARM; // _at_(ECRAM+0xB6);   
#define      Oem_BAT1_OverTemp_alarm 	BIT0     // alarmover temperature
#define      Oem_BAT1_OverVolt_alarm    BIT1     // alarmover voltage
#define      Oem_BAT1_OverTemp_Flag     BIT2     // when the event of the battery over temperature have occured ,this bit will be set when the battery resume normal this bit will be cleared
#define      Oem_BAT1_OverVolt_Flag     BIT3     // when the event of the battery over voltage have occured ,this bit will be set when the battery resume normal this bit will be cleared


//         ECRAM+0xC0 
extern XBYTE BAT1_AVTEmpty_L;		//_at_(ECRAM+0xc0);
extern XBYTE BAT1_AVTEmpty_H;		//_at_(ECRAM+0xc1);
extern XBYTE BAT1_AVTFull_L;		//_at_(ECRAM+0xc2);
extern XBYTE BAT1_AVTFull_H;		//_at_(ECRAM+0xc3);
extern XBYTE BAT1_DCap_L;			//_at_(ECRAM+0xc4);
extern XBYTE BAT1_DCap_H;			//_at_(ECRAM+0xc5);
extern XBYTE BAT1_DVolt_L;			//_at_(ECRAM+0xc6);
extern XBYTE BAT1_DVolt_H;			//_at_(ECRAM+0xc7);

 

extern XWORD BAT_SerialNumber;      //_at_(ECRAM+0xE2);

extern XBYTE Oem_TP_Status;  //_at_(OEMRAM+0xE4); 
#define TP_ON_OFF   BIT0 // 0:TP turn on 1:TP turn off

extern XBYTE Fn_Win_State;// _at_(OEMRAM+0xE5); 

extern XBYTE	Temperature_Low_Flag;		//_at_(OEMRAM+0xE6);
#define TempLow		    0x01    //heating stat
#define TestHeating		0x02
#define PreTempLow      0x03    //ec wake up,must wait same time
#define HeatingWaiting  0x04    //wait 30s to switch next step
#define HeatingInOS     0x05    //lcd heating in os mode

extern XBYTE    HEAT_FLAG;          //_at_(OEMRAM+0xE7);
#define   HEATING_HDD   BIT0
#define   HEATING_LCD   BIT1
#define   HEATING_GPU   BIT2

#define   HEATING_NONE2 BIT5
#define   HEATING_NONE1 BIT6
#define   HEATING_END   BIT7

#define   HEATING_ALL_MODEL (HEATING_HDD | HEATING_LCD | HEATING_GPU)

//lw 2017/12/18
//<<2017/11/22 lw
extern XBYTE Debug_Heating_switch ;
extern XBYTE Debug_Heating_Status ; //_at_(ECRAM+0xE8)               
#define  Debug_Heating_enable BIT0  //// 1:  enable     0:disenable
extern XBYTE Debug_TIME;		//_at_(ECRAM+0xE9) 
//#define  Debug_TIME_up BIT0  //// 1:  enable     0:disenable
//<<2017/11/22 lw
//lw 2017/12/18


extern XBYTE ComCheckCnt;	 //_at_(ECRAM+0xf0);
extern WORD  Oem_FAN1_CurrentRPM;//_at_(ECRAM+0xf2);
extern WORD  Oem_FAN2_CurrentRPM;//_at_(ECRAM+0xf4);
extern XBYTE ComCheckflag;	 //_at_(ECRAM+0xf8);

extern XBYTE Debugflag;		 //_at_(ECRAM+0xf9);

extern XBYTE ComMoniterflag;//_at_(ECRAM+0xfa);

extern XBYTE DebugTCPU;		 //_at_(ECRAM+0xfb);
extern WORD  DebugReadRPM;   //_at_(ECRAM+0xfc);    
extern XBYTE DebugFanRPMT;	 //_at_(ECRAM+0xfe);
extern XBYTE DebugFanStatus; //_at_(ECRAM+0xff);
#define Debug_Fan_enable   BIT0   // 1:  enable     0:disenable

// gap
//***************Reserved 0xa2~ 0xff  *********************


//++++++++++++++++++++++++++++++++++++++++++


//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x200-0x2FF   OEM RAM 2  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define SPIBufferRAM        OEMRAM2+0x00
extern XBYTE    SPIBuffer[];            // (SPIBufferRAM+0x00)  56 bytes SPI read/write buffer

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define OemTempBase         OEMRAM3+0x10

extern XBYTE Oem_BatCtrl_F;              //_at_(OEMRAM3+0x00);
#define Oem_BatAuth_WBK_f               BIT0             // Oem_BatAuth_WBK_f = 1: write block success   
#define Oem_BatCapTooLow_NotS0_f        BIT1
                                   
extern WORD BAT1_RMcap_Pre;               //_at_(OEMRAM3+0x01);
extern XBYTE Bat_Test_Mode_f;             // _at_(OEMRAM3+0x03);

extern XBYTE BAT_Calibrate_Step;		  // _at_(OEMRAM3+0x04);
#define BAT_Calibrate_Step_PreDC        0x01
#define BAT_Calibrate_Step_NC           0x02
#define BAT_Calibrate_Step_DC           0x04
#define BAT_Calibrate_Step_Exit         0x08


extern XBYTE BAT_Storagemode_Step;	  // _at_(OEMRAM3+0x05);
#define BAT_Storagemode_Check			0x00
#define BAT_Storagemode_Step_DC       	0x01
#define BAT_Storagemode_Step_NC      	0x02
#define BAT_Storagemode_Step_Exit      	0x04


extern XBYTE Oem_Globe_Flag; 		       // _at_(OEMRAM3+0x06);		
#define Charge_Inhibit_Inital_f		BIT0                   // 1: Inhibit    0:allow
#define Brightness_Down_Pressed     BIT1                   // 1: pressed    0:break
#define Brightness_Up_Pressed       BIT2                   // 1: pressed    0:break
#define All_Rf_Initial_OnlyOnce_f   BIT3				   // 1: have initialled   0:not initial
#define Send_44event_Disable        BIT4
#define LED_BAT_BP_READY            BIT5                   // 1: first strat shining 
#define Fn_Win_f                    BIT6                   // 1: Fn + F3(display mode switch) pressed  
#define Oem_AlwaysOn_f              BIT7                   // 1: Always well is powered  on 

extern XBYTE Oem_Globe_Flag1;              // _at_(OEMRAM3+0x07);
#define Oem_SYSTEM_DeepS3_f         BIT0
#define Oem_Mute_Delay_f            BIT1
#define Oem_GPU_Temp_OV_f           BIT2
#define Oem_Fn_R                    BIT3
#define Oem_SYS_Temp_OV_f           BIT4
#define Oem_Novo_Bit_f              BIT5
#define Oem_PCHBTN_En               BIT6
#define Oem_PCH_Temp_OV_f           BIT7


extern XBYTE    DebugFan1VoltageOut;       // _at_(OEMRAM3+0x08);	

  

extern XBYTE Oem_Device_Status; 	       // _at_(OEMRAM3+0x0c);
#define Wireless_IN				    BIT0
#define Bluetooth_IN        		BIT1
#define Inverter_IN          		BIT2
#define Novo_S_B					BIT3
#define TouchPad_IN				    BIT4
#define Camera_IN					BIT5
#define RF3G_IN					    BIT6
#define RFALL_IN					BIT7


extern XBYTE Oem_Globe_Flag2;              // _at_(OEMRAM3+0x0d);
#define Oem_F8_Make_f               BIT0   // 1: make     0: break
#define Oem_F10_Make_f              BIT1   // 1: make     0: break
#define Oem_AC_OFF_f                BIT2
#define Oem_AC_ON_f                 BIT3  
#define Oem_F8C_Make_f              BIT4   // 1: make     0: break
#define Oem_F10_Make_count          BIT5
#define Oem_Brightness_Make         BIT6   // 1: make     0: break


extern XBYTE Oem_GPU_EC_BLK;          	//_at_(OEMRAM3+0x0e);
#define Oem_GPU_BLK         BIT0
#define Oem_EC_BLK          BIT1
extern XBYTE Oem_PC_Beep_EN;          	//_at_(OEMRAM3+0x0f);

extern XBYTE   TDIM0_temp;          	//_at_(OEMRAM3+0x10);   // DRAM 0 temperature
extern XBYTE   TDIM1_temp;          	//_at_(OEMRAM3+0x11);   // DRAM 1 temperature
extern XBYTE   TPkg_temp;           	//_at_(OEMRAM3+0x12);   // 
extern XBYTE   TVGA_temp;           	//_at_(OEMRAM3+0x13);   // VGA Temperature

extern XBYTE   TSys_temp;           	//_at_(OEMRAM3+0x15);   // system Temperature
extern XSBYTE  TCPU_temp;           	//_at_(OEMRAM3+0x16);   // CPU Temperature
extern XBYTE   PECI_CPU_temp;       	//_at_(OEMRAM3+0x17);   // Use PECI interface to read CPU temperature
extern XBYTE   TPKG_Pch_temp;           //_at_(OEMRAM3+0x18);   // PCH Temperature   package 20bytes    // bios change the mode , so  2byte is enough
extern XBYTE   Pch_temp_Smbus;          //_at_(OEMRAM3+0x19);   


extern XBYTE Oem_KB_Status;            //_at_(OEMRAM3+0x2E);
#define KB_LED    BIT0 // 0:KB_LED turn off 1:KB_LED turn on




//reserved 0x30,0x31


extern XBYTE   SYS_TooHot_Cnt;          //_at_(OEMRAM3+0x32);

extern XBYTE   GPU_INFO_FLG;			//_at_(OEMRAM3+0x33);  for GPU infomation some flag
#define 	   GPU_INIT_OK				BIT0
#define        GPU_INIT_FAIL			BIT1

extern XBYTE   GPU_INIT_CNT;			//_at_(OEMRAM3+0x34);

extern XBYTE   OEM_2S_COUNT;            //_at_(OEMRAM3+0x35);
extern XBYTE   Adapter_Null_Counter; 	//_at_(OEMRAM3+0x36);
extern XBYTE   Adapter_In_Counter; 	 	//_at_(OEMRAM3+0x37);

extern XBYTE   Oem_Storage_mode_f ;	 		//_at_(OEMRAM3+0x38);
#define        Storage_Forbid_charge	BIT0

extern XBYTE Oem_Mute_Delay_Cnt;      	//_at_(OEMRAM3+0x39);
extern XBYTE ledTestFlag;      			//_at_(OEMRAM3+0x3A);
extern XBYTE Lenvo_dust_mode;  			//_at_(OEMRAM3+0x3C);
extern XBYTE Lenvo_general_f;   		//_at_(OEMRAM3+0x3D);
#define auto_mode_f				BIT0
#define super_temp_f			BIT1


extern XBYTE SCI_timer_RLOAD;			//_at_(OEMRAM3+0x40);
extern XBYTE SCI_timer_cnt;				//_at_(OEMRAM3+0x41);
extern XBYTE EC_STATE_BUF;            	//_at_(OEMRAM3+0x42);
#define Q_BUF_FULL_F            0x01   	// BIT 1 Q_BUF FULL FLAG = 1 (FULL)
#define Q_BUF_EMPTY_F           0x02   	// BIT 2 Q_BUF EMPTY FLAG = 1 (EMPTY)

extern XBYTE Oem_BatLedBlink_Cnt;		//_at_(OEMRAM3+0x43);

extern XBYTE Uart_flag; 				//_at_(OEMRAM3+0x44);
#define Uart_buffer_Empty       BIT0
#define Uart_buffer_Full        BIT1 

extern XWORD Uart_buffer_Inp_ptr;    	//_at_(OEMRAM3+0x45);

extern XWORD Uart_buffer_Oup_ptr;    	//_at_(OEMRAM3+0x47);

extern XBYTE OEM_flag_1;         		//_at_(OEMRAM3+0x49);
#define	fan_onoff_f   			BIT0
#define Oem_PECI_ReadUnit       BIT1
#define Fan_Dust_OnOff_f        BIT2    // 1:  8 sec max speed         0: 2 sec  off

extern XBYTE ITS_GPU_BYTE1;         	//_at_(OEMRAM3+0x4A); //Read GPU internal TS to read GPU temperature through SMBUS
extern XBYTE ITS_GPU_BYTE2;         	//_at_(OEMRAM3+0x4B);
extern XBYTE ITS_GPU_BYTE3;         	//_at_(OEMRAM3+0x4C);
extern XBYTE ITS_GPU_BYTE4;         	//_at_(OEMRAM3+0x4D);

extern XBYTE Bat_ShipMode_Data_L;	   //_at_(OEMRAM3+0x4E);
extern XBYTE Bat_ShipMode_Data_H;	   //_at_(OEMRAM3+0x4F);



extern XWORD OEM_Debug_flag;         	//(*(volatile WORD xdata *)0x0350)
#define OEM_Temp_Stop_f			BIT0
#define OEM_DEEPSLEEP_F         BIT3

extern XWORD BAT1_RMcap_L_temp;         //(*(volatile WORD xdata *)0x0352)

extern XWORD BAT1_FCcap_Pre;        	//(*(volatile WORD xdata *)0x0354)

extern XWORD SYSTEM_POWER_BATOnly_Current;	  //(*(volatile WORD xdata *)0x035A)

extern XWORD SYSTEM_POWER_BATProtect_C;	  //(*(volatile WORD xdata *)0x035C)


extern XWORD SystemWatts_BatChar_C;       //(*(volatile WORD xdata*)   0x0362)  // current now  battery request
extern XWORD Pre_SystemWatts_BatChar_C;   //(*(volatile WORD xdata*)   0x0364)


extern XBYTE SystemWatts_CHRStatus;		  //(*(volatile unsigned char xdata*)0x0366)
#define Increase_BatChr_C_f     		  BIT0
#define Reduce_BatChr_C_f                 BIT1
#define Change_BatChr_f                   BIT2


extern XWORD SysCurrent;				  //(*(volatile WORD xdata*) 0x0367)
extern XBYTE SystemWatts;                 //(*(volatile BYTE xdata *)0x0369)

extern XBYTE SystemPowerCtrlStep;         //(*(volatile BYTE xdata *)0x036A)
#define PowerCtrlStep_Start          0x01
#define PowerCtrlStep_Check          0x02
#define PowerCtrlStep_BatUp          0x03
#define PowerCtrlStep_BatDown        0x04
#define PowerCtrlStep_CPUUP          0x05
#define PowerCtrlStep_CPUDown        0x06
#define PowerCtrlStep_BATOnly        0x07

extern XBYTE SystemWatts_Over_Cnt;    	 //(*(volatile BYTE xdata *)0x036B)
extern XBYTE SystemWatts_Resume_Cnt;     //(*(volatile BYTE xdata *)0x036C)
extern XWORD SystemWatts_BatChar_BK;   	 //(*(volatile WORD xdata *)0x036D)

extern XBYTE Power_Protect_Cnt;  		 //(*(volatile BYTE xdata *)0x036F) 

extern XBYTE DebugECFlash;				 //(*(volatile BYTE xdata *)0x0370) 


extern XBYTE Oem_RTP_ID_Flag;  		 	//(*(volatile BYTE xdata *)0x0380)
#define Oem_RTP_ID_Respond_f       BIT0

extern XBYTE Oem_RTP_ID_Step;  		 	//(*(volatile BYTE xdata *)0x0381)
#define Oem_RTP_ID_Elan_step    0x01
#define Oem_RTP_ID_SY_step    	0x02
#define Oem_RTP_ID_ALPS_step    0x04

#define Oem_RTP_ID_SUCCESS   	0x80



extern XBYTE Oem_RTP_ID_Index; 		 	//(*(volatile BYTE xdata *)0x0382)

extern XBYTE Oem_RTP_ID_LOOP_Index; 	//(*(volatile BYTE xdata *)0x0383)

extern XWORD Oem_RTP_ID_1s_T; 	 	 	//(*( WORD xdata *)0x0384)

extern XBYTE Oem_RTP_ID_1s_EN;	 	 	//(*(volatile BYTE xdata *)0x0386)

extern XWORD Oem_RTP_ID_PWR_Delay; 	 	//(*( WORD xdata *)0x03d87)








extern XBYTE    POWER_FLAG1;            //(OEMRAM3+0xD0)  EC power flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define adapter_in      	     BIT0  	    // 1: AC adapter exist
#define wait_PSW_off    	     BIT1  	    // 1: waiting for PSW released
#define wait_NovoBtn_off         BIT2  	    // 1: waiting for NovoBtn released 
#define dc_heating_lcd_f         BIT3       // 1: lcd heating flag
#define ac_heating_lcd_f         BIT4       // 1: lcd heating fla
#define dc_heating_gpu_f         BIT5       // 1: gpu heating flag    
#define ac_heating_gpu_f         BIT6       // 1: gpu heating flag  


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  

extern XBYTE    POWER_FLAG2;            //(OEMRAM3+0xD1)  EC power flag 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	SLP_S3_ON         	BIT0        // 1:S3 power status
#define	SLP_S4_ON         	BIT1        // 1:S4 power status
#define	SLP_S5_ON         	BIT2        // 1:S5 power status
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    POWER_FLAG3;            //(OEMRAM3+0xD2)  EC power flag 3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE HomeBtn_Ass_F;			//_at_(OEMRAM3+0xC0);		[Home]+[Pwr] / [Home]+[Vol+] / [Home]+[Vol-]
extern XBYTE EnterDeepSleep_ACDC_Cnt;   // _at_(OEMRAM3+0xC1);
extern XBYTE EnterDeepSleep_ACDC_f;     // _at_(OEMRAM3+0xC2);
#define EnterDeepSleep_ACDC_EN         BIT0

extern XBYTE    Check_Shutdown_cnt;		//_at_(OEMRAM3+0xC3)

extern XBYTE    Check_Reset_cnt;          //_at_(OEMRAM3+0xC4)

extern XBYTE    Check_DelayShutdown_cnt; //_at_(OEMRAM3+0xC5)

extern XBYTE    R14Heating_Temp;		//_at_(OEMRAM3+0xC6)

extern XBYTE    HEAT_TEST_FLAG;   //_at_(OEMRAM3+0xC7);//V012_A: add flag for heating test

extern XWORD	MAX_Heat_Time;		//_at_(OEMRAM3+0xC8,C9);//V012_A: add flag for heating test

extern XWORD	Min_Heat_Time;		//_at_(OEMRAM3+0xCA,CB);//V012_A: add flag for heating test

extern XWORD	BATT_TEMP_PowerOn;	//_at_(OEMRAM3+0xCC,CD);//V012_A: add flag for heating test

extern XBYTE    EVT_STATUS1;            //(OEMRAM3+0xD6)  Event status flag 1
#define Lid_close_f         BIT0 
#define DelKey_f            BIT3
#define Read_VOLUME_DOWN_f  BIT4
#define Read_VOLUME_UP_f    BIT5
#define Home_Key_f			BIT6
#define Read_KillHdd_f      BIT7


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define HDMI_IN		    BIT6        // 1:HDMI 
//#define LAN_IN		    BIT7        // 1:LAN Plug-in
#define DummyFlag           BIT7        // 1:CRT Sense
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    EVT_STATUS2;            //(OEMRAM3+0xD7)  Event status flag 2
#define   Sys_Shutdown_f      BIT0
#define   Sys_DelayShutdown_f BIT1
#define   Sys_ResetPowerOn_f  BIT2
#define   Sys_ResetPowerOff_f BIT3 

extern XBYTE    EVT_STATUS3;            //(OEMRAM3+0xD8)  Event status flag 3

extern XBYTE    MISC_FLAG1;             //(OEMRAM3+0xD9)  Misc flag 1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	WL_En        		BIT6  	    // 1:Wireless Enable On 
#define BT_En			    BIT7  	    // 1:BlueTooth Enable On
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    MISC_FLAG2;             //(OEMRAM3+0xDA)  Misc flag 2 
extern XBYTE    MISC_FLAG3;             //(OEMRAM3+0xDB)  Misc flag 3 
extern XBYTE    MISC_FLAG4;             //(OEMRAM3+0xDC)  Misc flag 4 

extern XBYTE	 BT1_STATUS1;			//_at_(OEMRAM3+0xDD);	 // Battery 1 status1 flag
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_in         		BIT0	    // 1: Battery 1 exist
#define bat_valid           BIT1   	    // 1: Battery 1 battery idetify OK
#define bat_InCharge   		BIT2   	    // 1: battery 1 in any charge phase
#define bat_Full            BIT3   	    // 1: Battery 1 fully charged
#define bat_Dischg     		BIT4   	    // 1: Battery 1 in discharging
#define bat_Dead       		BIT5   	    // 1: Battery 1 fully discharged
#define bat_abnormal        BIT6   	    // 1: battery 1 abnormal
#define Bat1_In_Event		BIT7		// 1: battery in event, if 1 sent bat1_in Qevent after data is ready!

extern XBYTE	 BT1_STATUS2;			//_at_(OEMRAM3+0xDE);	 // Battery 1 status2 flag
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_DC         		BIT0	    // 1: Set Battery 1 discharge
#define bat_WC              BIT1   	    // 1: Set Battery 1 wake up charge
#define bat_PC         		BIT2	    // 1: Set Battery 1 pre-charge
#define bat_NC              BIT3   	    // 1: Set Battery 1 normal charge
#define bat_DC_OK           BIT4	    // 1: Battery 1 in discharge
#define bat_WC_OK           BIT5   	    // 1: Battery 1 in wake up charge
#define bat_PC_OK           BIT6	    // 1: Battery 1 in pre-charge
#define bat_NC_OK           BIT7   	    // 1: Battery 1 in normal charge

extern XBYTE	  BT1_STATUS3;			//_at_(OEMRAM3+0xDF);	  // Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_ForceChg       BIT0            // Battery 1 in force charge mode   
#define bat_ForceDischg    BIT1            // Battery 1 in force discharge mode 
#define bat_AL             BIT2            // Battery 1 in auto learning
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


extern XBYTE 	EC_CPU_TEMP;			//_at_(OEMRAM3+0xE0); //(BYTE)CPU Temperature
extern XBYTE 	B1SS_Bak;               //_at_(OEMRAM3+0xE1);
extern XBYTE 	FanSpeedLow;			//_at_(OEMRAM3+0xE2)           
extern XBYTE 	FanSpeedHigh;			//_at_(OEMRAM3+0xE3)
extern XBYTE    BrgLevel;               //_at_(OEMRAM3+0xE4)  Brightness level 
extern XBYTE    CrisisKeyStatus;        //_at_(OEMRAM3+0xE5)  Crisis key flag
extern XBYTE    PanelId;                //_at_(OEMRAM3+0xE6)  Panel ID
extern XBYTE	BAT1_ACCESSL;			//_at_(OEMRAM3+0xE7);	 //Battery 1
#define bat_GoodOrBad_f     BIT1
extern XBYTE	BAT1_ACCESSH;			//_at_(OEMRAM3+0xE8);	 //Battery 1 
extern XBYTE    BAT1_MODEL;             //_at_(OEMRAM3+0xE9);
extern XBYTE    BAT1_MODEH;             //_at_(OEMRAM3+0xEA);

extern XBYTE    PanelInitFlag;			//_at_(OEMRAM3+0xEF); //1:EDP have been initialized ;0:EDP have not been initialized

extern XBYTE ACPI_Count;				 //_at_(OEMRAM3+0xF6)
extern XBYTE ACPI_Flag;				 	 //_at_(OEMRAM3+0xF7)
extern XBYTE SysPostTime;				 //_at_(OEMRAM3+0xF8)
extern XBYTE CoolBootTime;               //_at_(OEMRAM3+0xF9)
extern XBYTE CoolBootFlag;               //_at_(OEMRAM3+0xFA)
extern XBYTE AdjustBLDelay;              //_at_(OEMRAM3+0xFB)



//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM4 Offset 0x00 ~ 0x11  Power sequnce control 
#define PowerSequnceRAM     OEMRAM4+0x00

extern XBYTE	SysPowState;			//(PowerSequnceRAM+0x00)    //(byte)
extern XBYTE	PWSeqStep;			    //(PowerSequnceRAM+0x01)    //(byte)
extern XBYTE	DeepSleepCunt;		    //(PowerSequnceRAM+0x02)    //(byte)
extern XWORD    DelayDoPowerSeq;		//(PowerSequnceRAM+0x03)    //(word)
extern XWORD    PowSeqDelay;			//(PowerSequnceRAM+0x05)    //(word)
extern XBYTE    ECAutoPowerOn;		    //(PowerSequnceRAM+0x07)    //(byte)
extern XBYTE	ECWDTRSTNow;			//(PowerSequnceRAM+0x08)    //(byte)
extern XBYTE	CheckPowerStateIndex;   //(PowerSequnceRAM+0x09)    //(byte)
extern XBYTE	SBSWReleaseCunt;		//(PowerSequnceRAM+0x0A)    //(byte)
extern XWORD	PSW_COUNTER;            //(PowerSequnceRAM+0x0B)    //(word)
extern XWORD	HWPG_TIMER;             //(PowerSequnceRAM+0x0D)    //(word)
extern XBYTE	ShutDnCause;     	    //(PowerSequnceRAM+0x0F)    //(byte)
extern XWORD	PSWPressed_COUNTER;     //(PowerSequnceRAM+0x10)    //(word)
extern XWORD    PanelInit_COUNTER;      //(PowerSequnceRAM+0x12)    //(word)
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x14 ~ 0x1F   Thermal variables
#define ThermalRAM     OEMRAM4+0x14
	

//Reserved offset 0x03 ~ 0x0F
//===============================================================================




//===============================================================================
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
#define LEDRAM     OEMRAM4+0x20
extern XWORD    LED_FLASH_CNT;  		//(LEDRAM+0x00) //(word) LED index
extern XWORD    BAT_LED_Cnt_ON;  		//(LEDRAM+0x02) //(word) LED index
extern XBYTE    BAT_LED_Cnt_OFF;  		//(LEDRAM+0x04) //(word) LED index


//Reserved offset 0x02 ~ 0x0F
//===============================================================================



//===============================================================================
// OEMRAM4 Offset 0x28 ~ 0x2F   LCD variables
#define LCDRAM     OEMRAM4+0x28
extern XBYTE    bBrightness;            //(LCDRAM+0x00) //(byte)
//Reserved offset 0x01 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x30 ~ 0x4F   ADC variables
#define ADCRAM     OEMRAM4+0x30
extern XWORD    ADCAvg0;				//(ADCRAM+0x00) //(word)
extern XWORD	ADCAvg1;				//(ADCRAM+0x02) //(word)
extern XWORD	ADCAvg2;			    //(ADCRAM+0x04) //(word)
extern XWORD	ADCAvg3;				//(ADCRAM+0x06) //(word)
extern XWORD	ADCAvg4;				//(ADCRAM+0x08) //(word)
extern XWORD	ADCAvg5;			    //(ADCRAM+0x0A) //(word)
extern XWORD	Fix_ADCAvg0;			//(ADCRAM+0x0C) //(word)
extern XWORD	Fix_ADCAvg1;			//(ADCRAM+0x0E) //(word)

extern XBYTE    ADCDyTable1Index;       //(ADCRAM+0x10) //(byte)
extern XBYTE	ADCDyTable2Index;       //(ADCRAM+0x11) //(byte)
//Reserved offset 0x12 ~ 0x1F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x50 ~ 0x6F   SMBus center variables
#define SMBusCenterRAM      OEMRAM4+0x50

extern XBYTE	SMBus1Flag1;			//(SMBusCenterRAM+0x00)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_RSOC         BIT0
#define B1_C            BIT1
#define B1_V            BIT2
#define B1_RMcap        BIT3
#define B1_Status       BIT4
#define B1_FCC          BIT5
#define B1_Temp         BIT6
#define B1_Cycle		BIT7


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus1Flag2;			//(SMBusCenterRAM+0x01)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_CC			BIT0
#define B1_CV			BIT1
#define B1_Mode			BIT3
#define B1_ACCESS		BIT4
#define B1_MFGF2		BIT5
#define B1_MaftName     BIT6
#define B1_BatFW		BIT7


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus1Flag3;			//(SMBusCenterRAM+0x02)
#define bSensor2_STATE	BIT0
#define bSensor2_Event1	BIT1
#define bSensor2_Event2	BIT2
#define bSensor2_State1	BIT3
#define bSensor2_State2	BIT4
#define bWSensor2_Ctrl	BIT5
#define bSensor2_Ctrl	BIT6
#define bSensor2_INT		BIT7

extern XBYTE	SMBus1Flag4;		    //(SMBusCenterRAM+0x03)
#define bAxis_X_L2	BIT0
#define bAxis_X_H2	BIT1
#define bAxis_Y_L2	BIT2
#define bAxis_Y_H2	BIT3
#define bAxis_Z_L2	BIT4
#define bAxis_Z_H2	BIT5

extern XBYTE	SMBus1Flag5;		    //(SMBusCenterRAM+0x04)
#define B1_AVTEmpty	BIT1
#define B1_AVTFULL	BIT2
#define B1_DCap		BIT3
#define B1_DVolt	BIT4




extern XBYTE	SMBus2Flag1;		    //(SMBusCenterRAM+0x05)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PchPackage      BIT0
#define GPUPackage      BIT1

#define Lsensor01       BIT2
#define Lsensor02       BIT3
#define Lsensor03       BIT4
#define Lsensor04       BIT5
#define Lsensor05       BIT6
#define Lsensor06       BIT7






#define PollRemote      BIT0            // Read thermal sensor remote temperature
#define PollLocal       BIT1            // Read thermal sensor local temperature
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus2Flag2;		    //(SMBusCenterRAM+0x06)
//===========================HID========================
#define bSensor_STATE	BIT0
#define bSensor_Event1	BIT1
#define bSensor_Event2	BIT2
#define bSensor_State1	BIT3
#define bSensor_State2	BIT4
#define bWSensor_Ctrl	BIT5
#define bSensor_Ctrl	BIT6
#define bSensor_INT		BIT7

//=====================================================
extern XBYTE	SMBus2Flag3;		    //(SMBusCenterRAM+0x07)
//===========================HID========================
#define bAxis_X_L	BIT0
#define bAxis_X_H	BIT1
#define bAxis_Y_L	BIT2
#define bAxis_Y_H	BIT3
#define bAxis_Z_L	BIT4
#define bAxis_Z_H	BIT5

//=====================================================


extern XBYTE	SMBus2Flag4;		    //(SMBusCenterRAM+0x08)

extern XBYTE	ThermalSensorStatus;    //(SMBusCenterRAM+0x09)
#define         ThermalSensorIn         BIT0  // CPU/GPU/LCD ThermalSersor exist
#define         ThermalSensorValid      BIT1  // CPU/GPU/LCD ThermalSersor ok
#define         LcdTemp_H	            BIT2  // Read LCD temperature high byte
#define         LcdTemp_L               BIT3  // Read LCD temperature low  byte
#define         CpuTemp_H               BIT4  // Read CPU temperature high byte
#define         CpuTemp_L               BIT5  // Read CPU temperature low  byte
#define         GpuTemp_H               BIT6  // Read GPU temperature high byte
#define         GpuTemp_L               BIT7  // Read GPU temperature low  byte






extern XBYTE	SMBus3Flag1;			//(SMBusCenterRAM+0x0A)


extern XBYTE	SMBusSelection;			//(SMBusCenterRAM+0x0B)
extern XBYTE	F_Service_SMBus1;       //(SMBusCenterRAM+0x0C)
extern XBYTE	F_Service_SMBus2;       //(SMBusCenterRAM+0x0D)
extern XBYTE	F_Service_SMBus3;       //(SMBusCenterRAM+0x0E)
extern XBYTE	F_Service_SMBus4;       //(SMBusCenterRAM+0x0F)
extern XBYTE	SMBus1ByteCunt;	        //(SMBusCenterRAM+0x10)
extern XBYTE	SMBus2ByteCunt;		    //(SMBusCenterRAM+0x11)
extern XBYTE	SMBus3ByteCunt;		    //(SMBusCenterRAM+0x12)
extern XBYTE	SMBus1counter;		    //(SMBusCenterRAM+0x13)
extern XBYTE	SMBus2counter;		    //(SMBusCenterRAM+0x14)
extern XBYTE	SMBus3counter;		    //(SMBusCenterRAM+0x15)
extern XBYTE	SMBus1index;			//(SMBusCenterRAM+0x16)
extern XBYTE	SMBus2index;			//(SMBusCenterRAM+0x17)
extern XBYTE	SMBus3index;			//(SMBusCenterRAM+0x18)
extern XBYTE    SMBus1InUsing;          //(SMBusCenterRAM+0x19)
extern XBYTE    SMBus2InUsing;          //(SMBusCenterRAM+0x1A)
extern XBYTE    SMBus3InUsing;          //(SMBusCenterRAM+0x1B)
extern XBYTE    SMBus1TableSize;        //(SMBusCenterRAM+0x1C)
extern XBYTE    SMBus2TableSize;        //(SMBusCenterRAM+0x1D)
extern XBYTE    SMBus3TableSize;        //(SMBusCenterRAM+0x1E)
extern XBYTE    SMBusXStatus;           //(SMBusCenterRAM+0x1F)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBus1_OK       BIT0
#define SMBus1_Fail     BIT1
#define SMBus2_OK       BIT2
#define SMBus2_Fail     BIT3
#define SMBus3_OK       BIT4
#define SMBus3_Fail     BIT5
#define SMBus4_OK       BIT6
#define SMBus4_Fail     BIT7
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x70 ~ 0x9F   Battery 1 control variables
#define BAT1CtrlRAM     OEMRAM4+0x70
extern XBYTE    BAT1_CtrlStep;          //(BAT1CtrlRAM+0x00)
extern XBYTE    BAT1_ID_Step;           //(BAT1CtrlRAM+0x01)
extern XBYTE    BAT1_1SecTimer;         //(BAT1CtrlRAM+0x02)
extern XBYTE    BAT1_S_Number;          //(BAT1CtrlRAM+0x03)                               //serial number of battery cells 
extern XBYTE    ByteTemp01;             //(BAT1CtrlRAM+0x04)
extern XBYTE    ByteTemp02;             //(BAT1CtrlRAM+0x05)
extern XBYTE    BAT1_ID_TimeOut_CNT;    //(BAT1CtrlRAM+0x06)
extern XBYTE    BAT1_Number;            //(BAT1CtrlRAM+0x07)
extern XBYTE    BAT1_FailCause;         //(BAT1CtrlRAM+0x08)
extern XBYTE    BAT1_FirstDataIndex;    //(BAT1CtrlRAM+0x09)
extern XBYTE	INPUT_CURRENT_LO;       //(BAT1CtrlRAM+0x0A)
extern XBYTE	INPUT_CURRENT_HI;       //(BAT1CtrlRAM+0x0B)
extern XBYTE	CHARGE_CURRENT_LO;      //(BAT1CtrlRAM+0x0C)
extern XBYTE	CHARGE_CURRENT_HI;      //(BAT1CtrlRAM+0x0D)
extern XBYTE	CHARGE_VOLTAGE_LO;      //(BAT1CtrlRAM+0x0E)  
extern XBYTE	CHARGE_VOLTAGE_HI;      //(BAT1CtrlRAM+0x0F)
extern XBYTE	Charger_TimeOut;        //(BAT1CtrlRAM+0x10)
extern XBYTE    WakeUpChrCunt_Min;      //(BAT1CtrlRAM+0x11) 
extern XWORD    PreChrCunt_Min;         //(BAT1CtrlRAM+0x12)
extern XWORD    NormalChrCunt_Min;      //(BAT1CtrlRAM+0x14)
extern XWORD    WakeUpChrCunt;          //(BAT1CtrlRAM+0x16) 
extern XWORD    PreChrCunt;             //(BAT1CtrlRAM+0x18) 
extern XWORD    NormalChrCunt;          //(BAT1CtrlRAM+0x1A)
extern XBYTE    BAT1_OTCunt;            //(BAT1CtrlRAM+0x1C)
extern XBYTE    BAT1_OVCunt;            //(BAT1CtrlRAM+0x1D)
extern XBYTE    BAT1_BADCunt;           //(BAT1CtrlRAM+0x1E)
extern XWORD    CHARGE_CURRENT_BK;      //(BAT1CtrlRAM+0x1F)
extern XWORD    CHARGE_VOLTAGE_BK;      //(BAT1CtrlRAM+0x21)
extern XBYTE    CHARGER_OPTION_L;       //(BAT1CtrlRAM+0x23)
extern XBYTE    CHARGER_OPTION_H;       //(BAT1CtrlRAM+0x24)
extern XWORD    BAT1_DeVol;             //(BAT1CtrlRAM+0x25)  
extern XWORD    BAT1_DeCap;             //(BAT1CtrlRAM+0x27)
extern XBYTE    BK_BAT1_CtrlStep;       //(BAT1CtrlRAM+0x29)
extern XBYTE    BAT1_Type_Flag;         //(BAT1CtrlRAM+0x2A)

//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0xA0 ~ 0xAF   Power sequnce control 
#define PowerSequnce2RAM    OEMRAM4+0xA0

extern XBYTE    PowerStatusBK;          //(PowerSequnce2RAM+0x00)
extern XWORD    PowerOnWDT;             //(PowerSequnce2RAM+0x01)



//Reserved OEMRAM4 offset 0xB0 ~ 0xEF
#define LightsensorRAM    OEMRAM4+0xB0
extern XBYTE    LIGHTDATE;          //(LightsensorRAM+0x00)

extern XBYTE    NEED_MinHeatTime;   //(OEMRAM4+0xB8)

extern XBYTE	CPU_HEAT_HIGH;		//(OEMRAM4+0xB9)

extern XBYTE    LCD_OS_Heating_Flag; //(OEMRAM4+0xBA)
#define   HEATING_lCD_15W   BIT0
#define   HEATING_lCD_35W   BIT1


extern XWORD    AC_Current;         //(OEMRAM4+0xBB)  adapter current




//===============================================================================
// OEMRAM4 Offset 0xF0 ~ 0xFF   Event debounce counter 
#define DebounceRAM     OEMRAM4+0xF0

extern XBYTE	DEBOUNCE_CONT1;		    //(DebounceRAM+0x00) 	//(byte)
extern XBYTE	DEBOUNCE_CONT2;		    //(DebounceRAM+0x01) 	//(byte)
extern XBYTE	DEBOUNCE_CONT3;		    //(DebounceRAM+0x02) 	//(byte)
extern XBYTE	DEBOUNCE_CONT4;		    //(DebounceRAM+0x03) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT5;		    //(DebounceRAM+0x04) 	//(byte)
extern XBYTE	DEBOUNCE_CONT6;		    //(DebounceRAM+0x05) 	//(byte)
extern XBYTE	DEBOUNCE_CONT7;		    //(DebounceRAM+0x06) 	//(byte)
extern XBYTE	DEBOUNCE_CONT8;		    //(DebounceRAM+0x07) 	//(byte)
extern XBYTE	DEBOUNCE_CONT9;		    //(DebounceRAM+0x08) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT10;		//(DebounceRAM+0x09) 	//(byte)
extern XBYTE	DEBOUNCE_CONT11;		//(DebounceRAM+0x0A) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT12;		//(DebounceRAM+0x0B) 	//(byte)
extern XBYTE	DEBOUNCE_CONT13;		//(DebounceRAM+0x0C) 	//(byte)
extern XBYTE	DEBOUNCE_CONT14;		//(DebounceRAM+0x0D) 	//(byte)
extern XBYTE	DEBOUNCE_CONT15;		//(DebounceRAM+0x0E) 	//(byte)
extern XBYTE	DEBOUNCE_CONT16;		//(DebounceRAM+0x0F) 	//(byte) 
//===============================================================================

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM5 Offset 0x00 ~ 0x3F   For fan control 
#define FanCtrlRAM      OEMRAM5+0x00

extern XWORD	FAN1_CurrentRPM;		// FanCtrlRAM+0x00      current rpm  
extern XWORD	FAN1_GoalRPM;			// FanCtrlRAM+0x02      goal  rpm
extern XBYTE	FAN1_Level;				// FanCtrlRAM+0x04
extern XBYTE	temperature1;			// FanCtrlRAM+0x05	
extern XBYTE	Debugtemperature1;		// FanCtrlRAM+0x06				
extern XBYTE    FanFullOnCont;			// FanCtrlRAM+0x07
extern XWORD    DustTotleCont;			// FanCtrlRAM+0x08

extern XWORD	FAN2_CurrentRPM;		// FanCtrlRAM+0x0A      current rpm  
extern XWORD	FAN2_GoalRPM;			// FanCtrlRAM+0x0C      goal  rpm
extern XBYTE	FAN2_Level;				// FanCtrlRAM+0x0E
extern XBYTE	temperature2;			// FanCtrlRAM+0x0F	
extern XBYTE	Debugtemperature2;		// FanCtrlRAM+0x10	
extern XBYTE    Bktemperature;          // FanCtrlRAM+0x11
extern XBYTE    Maxtemperature;         // FanCtrlRAM+0x12
extern XBYTE    Bk1FAN_Level;           // FanCtrlRAM+0x13
extern XBYTE    Bk2FAN_Level;           // FanCtrlRAM+0x14
extern XBYTE    FanLevel_t;             // FanCtrlRAM+0x15
extern XBYTE    Fan_Adjust_Dir;         // FanCtrlRAM+0x16



//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function 
#define PECICtrlRAM      OEMRAM5+0x40

extern XBYTE   PECIReadBuffer[];        // PECICtrlRAM + 0x000 offset 0x40 ~ 0x4F
extern XBYTE   PECIWriteBuffer[];       // PECICtrlRAM + 0x010 offset 0x50 ~ 0x5F
extern XBYTE   PECI_CRC8;               // PECICtrlRAM + 0x020 offset 0x60
extern XBYTE   PECI_CompletionCode;     // PECICtrlRAM + 0x021 offset 0x61
extern XBYTE   PECI_PCIConfigAddr[];    // PECICtrlRAM + 0x022 offset 0x62 ~ 0x65
//Reserved offset 0x66 ~ 0x6F
extern XBYTE   PECI_PowerCtrlStep;      // PECICtrlRAM + 0x030 offset 0x70
extern XBYTE   PECI_PowerUnit;          // PECICtrlRAM + 0x031 offset 0x71
extern XBYTE   PECI_EnergyUnit;         // PECICtrlRAM + 0x032 offset 0x72
extern XBYTE   PECI_TimeUnit;           // PECICtrlRAM + 0x033 offset 0x73
extern XBYTE   PECI_PL2Watts;           // PECICtrlRAM + 0x034 offset 0x74
extern XBYTE   PECI_MAXPL2;             // PECICtrlRAM + 0x035 offset 0x75
extern XBYTE   PECI_PL1TDP;             // PECICtrlRAM + 0x036 offset 0x76
extern XBYTE   PECI_PL1Time;            // PECICtrlRAM + 0x037 offset 0x77
extern XBYTE   PECI_Ctrl;               // PECICtrlRAM + 0x038 offset 0x78
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SetPL2Request           BIT0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   PECI_AdaptorWatts;       // PECICtrlRAM + 0x039 offset 0x79
extern XBYTE   PECI_SystemWatts;        // PECICtrlRAM + 0x03A offset 0x7A
extern XBYTE   PECI_Algorithm_Delay;    // PECICtrlRAM + 0x03B offset 0x7B
extern LWORD   PECI_ErrorCount;         // PECICtrlRAM + 0x03C offset 0x7C ~ 0x0x7F
extern XBYTE   PECI_StressToolBuf[];    // PECICtrlRAM + 0x040 offset 0x80 ~ 0x9F
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PSTB_RepeatCycle0           0
#define PSTB_RepeatCycle1           1
#define PSTB_RepeatCycle2           2
#define PSTB_RepeatCycle3           3
#define PSTB_RepeatInterval         4           // 10ms timer base
#define PSTB_StopOnError            5
#define PSTB_ClientAddress          6
#define PSTB_WriteLength            7
#define PSTB_ReadLength             8
#define PSTB_CommandSpecificData    9
#define PSTB_CmdCode                PSTB_CommandSpecificData

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   PSTB_Timer;              // PECICtrlRAM + 0x060 offset 0xA0
extern XBYTE   PSTB_CmdStatus;          // PECICtrlRAM + 0x061 offset 0xA1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ServivePECIStressTool   BIT0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    PSTB_RepeatIntervalCount;   // PECICtrlRAM + 0x062  offset 0xA2
extern LWORD    PSTB_RepeatCycle;           // PECICtrlRAM + 0x063  offset 0xA3 ~ 0xA6
extern XBYTE    CPUTjmax;			        // PECICtrlRAM + 0x067
extern XBYTE    ReadCPUTjmaxCUNT;           // PECICtrlRAM + 0x068
extern XBYTE    StressToolReadBufIndex;     // PECICtrlRAM + 0x069
extern LWORD    PECI_PkgPower_Pre;          //( PECICtrlRAM + 0x06A);  AA --- AD
extern LWORD   	PECI_PkgPower_Cur; 		    //( PECICtrlRAM + 0x06E);  AE ----B1
extern LWORD    PECI_PkgPower;              //( PECICtrlRAM + 0x06E);  B2
extern LWORD    PECI_PkgPower_average;      //( PECICtrlRAM + 0x06E);  B2
extern XBYTE    PECI_PkgPower_average_count ;//  _at_( PECICtrlRAM + 0x07a);


//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 
#define SPI_Mouse           OEMRAM5+0xC0

extern XBYTE   SPI_Mouse_Buf[];         //( SPI_Mouse + 0x00)
extern XBYTE   SPI_Mouse_DeltaX;        //( SPI_Mouse + 0x03)
extern XBYTE   SPI_Mouse_DeltaY;        //( SPI_Mouse + 0x04)
extern XBYTE   SPI_Mouse_BYTE1;         //( SPI_Mouse + 0x05)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define Y_Overflow          BIT7
#define X_Overflow          BIT6
#define Y_Signbit           BIT5
#define X_Signbit           BIT4
#define Always1             BIT3
#define MiddleBtn           BIT2
#define RightBtn            BIT1
#define LeftBtn             BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   SPI_Mouse_XMovement;     //( SPI_Mouse + 0x06)
extern XBYTE   SPI_Mouse_YMovement;     //( SPI_Mouse + 0x07)
extern XBYTE   SPI_Mouse_Buf_Index;     //( SPI_Mouse + 0x08)
extern XBYTE   SPI_Mouse_Misc;          //( SPI_Mouse + 0x09)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SPI_Mouse_Need_Break    BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE   SPI_Mouse_ID;            //( SPI_Mouse + 0x0A)

//Reserved offset 0x0A ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
#define SCI_Qevent_Ctrl     OEMRAM5+0xD0

extern XBYTE 	SCI_Event_In_Index;     //( SCI_Qevent_Ctrl + 0x00);
extern XBYTE 	SCI_Event_Out_Index;    //( SCI_Qevent_Ctrl + 0x01);
extern XBYTE 	SCI_Event_Buffer[];     //( SCI_Qevent_Ctrl + 0x02); // EVENT_BUFFER_SIZE bytes

extern XBYTE 	PD_SCI_Event_In_Index;  //( SCI_Qevent_Ctrl + 0x10);
extern XBYTE 	PD_SCI_Event_Out_Index; //( SCI_Qevent_Ctrl + 0x11);
extern XBYTE 	PD_SCI_Event_Buffer[];  //( SCI_Qevent_Ctrl + 0x12); // PENDING_BUFFER bytes

//===============================================================================
// OEMRAM5 Offset 0xF0 ~ 0xFF   For OEM HSPI function
#define HSPI_Ctrl     OEMRAM5+0xF0

extern XBYTE    HSPI_SelfRamCode_Index; //( HSPI_Ctrl + 0x00);
extern XBYTE    HSPI_tempcmd;           //( HSPI_Ctrl + 0x01);
extern XBYTE    HSPI_FPT_timeout;       //( HSPI_Ctrl + 0x02);
extern XBYTE    HSPI_Misc1;             //( HSPI_Ctrl + 0x03);




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define HSPI_ReLoadHSPIRamCode  BIT0    // 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



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
//	0xA00-0xAFF   OEM RAM A   For bram copy
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
extern LWORD HashRandom[5];			// 0xC00~0xC1F
extern LWORD SHA1ECProcV[5];		// 0xC20~0xC3F
extern LWORD Respond[5];		  	// 0xC40~0xC5F

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

#endif 
