/*----------------------------------------------------------------------------
 * Filename: OEM_PROJECT.H  For Chipset: ITE.IT85XX
 *
 * Function: Project function selection.
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 *---------------------------------------------------------------------------*/

#ifndef OEM_Project_H
#define OEM_Project_H

//OEM Version number
#define	OEM_Version_MSB	  0x03  //Label:BLD_RN1503_03_01
#define	OEM_Version_LSB	  0x16

//Label:BLD_TIPIA_20160905_007
// Flash EC ROM channel. PM1--62/66   PM2--68/6C
#define FLASH_EC_PMxDO    PM2DO
#define FLASH_EC_PMxDI    PM2DI
#define FLASH_EC_PMxSTS   PM2STS


//*****************************************************************************
// Kernel code feature
//*****************************************************************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function define
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SMBusServiceCenterFunc          // Define : for SMBus service center

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define EC_Signature_Flag	    0xB5    // For 8518 crystal free						            

//-----------------------------------------------------------------------------
// PS2 interface
//-----------------------------------------------------------------------------
#define TouchPad_only           TRUE    // True : Only touch pad device in this project
                                        /* Note : If TouchPad_only is set, remeber to call 
                                            PowerOffClearTPPendingData() function in power off sequnce
                                            include (S3, S4, and S5)¡C*/   

#if TouchPad_only                                     
#define MultiplexedModes        FALSE   // 0 : Doesn't support multiplexed modes.
#else
#define MultiplexedModes        TRUE    // 1 : Support multiplexed modes.
#endif

//-----------------------------------------------------------------------------
// Keyboard scan
//-----------------------------------------------------------------------------
#define KB_FnStickKey           FALSE   // True : for Fn stick key function
//#define SUPPORT_KB_MATRIX_ID1			//support Matrix 1


/*--------------;
 ;WATCH-DOG		;
 ;--------------*/ 
#define	WATCHDOG			TRUE	// WATCHDOG FUNCTION SUPPORT *DEFAULT*                          
//#define	WATCHDOG			FALSE	// WATCHDOG FUNCTION NON-SUPPORT                                

#define	WATCHDOG_COUNTER_1S		1
#define	WATCHDOG_COUNTER_2S		2

#define	WATCHDOG_COUNTER		5	// 4.2 : FOR NORMAL *DEFAULT=4.2 SEC*     

//add low temprature heat 
#define SSD_Hdd_Used         TRUE   // True: use ssd, can not get hdd temp;




//*****************************************************************************
// UART debug interface
// Timer 2 baudrate = Fosc / 32 / (0x10000-RCAP2)¡C
//*****************************************************************************
//#define UART_Debug        // Define : enable Tx debug (GPIO B1)

#ifdef UART_Debug 
// 9600 bps-------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xE2  
// 9600 bps-------------------------

// 19200 bps------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xF1  
// 19200 bps------------------------

// 57600 bps------------------------
#define R2HV                    0xFF
#define R2LV                    0xFB  
// 57600 bps------------------------
#endif


//*****************************************************************************
// OEM code feature
//*****************************************************************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// OEM Function define
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define ITE8500                   // Define : chip is 8500
//#define HSPI                      // Define : support HSPI function
//#define PECI_Support         // Define : support PECI function
//#define PMC3_Support              // Define : For Intel PECI stress tool and other OEM command via PMC3
//#define SysMemory2ECRam	        // Define : support system memory cycle mapping to ec ram
//#define SMBusChannel4Support      // Define : GPH1/GPH2 will select SMBus function

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// OEM EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
// Base address select 0x00:2E/2F 0x01:4E/4F 0x02:User define  
//-----------------------------------------------------------------------------
#define Init_BADR           Core_Init_BADR       // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define SWCBALR | SWCBAHR 
#define Init_SWCBAHR        Core_Init_SWCBAHR    // I/O Port High Byte 
#define Init_SWCBALR        Core_Init_SWCBALR    // I/O Port Low  Byte
#define Init_I2EC           Core_Init_I2EC       // Enable I2EC R/W and log 80 port 

//-----------------------------------------------------------------------------
// HSPI share
//-----------------------------------------------------------------------------
#ifdef HSPI
    //*************************************************************************
    // Define : HSPI deffering mode, Non define : HSPI non deffering mode
    //*************************************************************************
    //#define HSPI_DefferingMode    // Define : HSPI is deffering mode

    //*************************************************************************
    // HSPI setting selection
    //*************************************************************************
    //#define HSPI_Setting01    // Host[All/20MHz],                                         EC[READ(03h)/33MHz]
    //#define HSPI_Setting02    // Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],  EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
    //#define HSPI_Setting03    // Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],  EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
    //#define HSPI_Setting04    // Host[DOFR/50MHz Otherwise/20MHz FREAD isn't supported],  EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]
    #define HSPI_Setting05      // Host[All/20MHz],                                         EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
    //#define HSPI_Setting06    // Host[All/20MHz],                                         EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
    //#define HSPI_Setting07    // Host[DOFR/33MHz,Otherwise/20MHz,FREAD isn't supported],  EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]

    #ifdef HSPI_Setting01
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_0           // Read cycle
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting02
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_1           // Fast read cycle
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting03
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting04
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting05
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_1           // Fast read cycle
    #define HSRSMode            HSPI_RequestSelection_2 // HSPI request Setting 5
    #endif

    #ifdef HSPI_Setting06
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
    #endif

    #ifdef HSPI_Setting07
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
    #endif
    
	#define Init_FMSSR	    0x0E	// 0x1F 16M Bytes Share Rom for HSPI
	
#else       
//-----------------------------------------------------------------------------
// LPC share
//-----------------------------------------------------------------------------
    //*************************************************************************
    // EC SPI [fast read, 64.5MHZ]
    //*************************************************************************
    //#define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    //#define SPIReadMode         SPIReadMode_1           // Fast read cycle

    //*************************************************************************
    // EC SPI [read, 46MHZ]
    //*************************************************************************
    //#define PLLFrequency        PLLFreqSetting05        // 46 MHZ PLL frequency
    //#define SPIReadMode         SPIReadMode_0           // read cycle

    //*************************************************************************
    // EC SPI [read, 32.3MHZ]
    //*************************************************************************
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_0           // read cycle
    
	#define Init_FMSSR	    0x1F	// 0x1F 2M Bytes Share Rom 
#endif						        // 0x0F 1M Bytes Share Rom 
							        // 0x07 512K Bytes Share Rom 
//-----------------------------------------------------------------------------
// GPIO pin scan keybaord
//-----------------------------------------------------------------------------
#define ExternMatrixGPO		    FALSE // True : using GPO Pin scan keyboard
									    // Note : just support one GPIO pin now !!!									    
#define GPOKeyPin1H		        SET_MASK(GPDRF,BIT(0))	// For extend GPIO scan keys
#define GPOKeyPin1L		        CLEAR_MASK(GPDRF,BIT(0))	
#define GPOKeyPin1Ctl	        GPCRF0  // GPCRF0
//-----------------------------------------------------------------------------
// Control ACPI
//-----------------------------------------------------------------------------
#define ACPI_Smbus			    TRUE    // True : for ACPI Smbus function
#define ACPI_QEventPending      TRUE    // FALSE   // True : EC will pending q-event, if 62/66 IBF

//*****************************************************************************
//-----------------------------------------------------------------------------
// OEM support function selection
//-----------------------------------------------------------------------------
//*****************************************************************************
#define ADCFuncSupport			TRUE    // True : support ADC function
#define CIRFuncSupport			FALSE   // True : support cir function
#define LEDFuncSupport          TRUE    // True : support LEC control function
#define HookFucnofWriteECRam    TRUE    // True : Hook function For ACPI command 0x81 write EC space 
#define S3KeyboardWakeUp        TRUE    // True : support S3 wake up from internal keyboard
#define MailBoxRWECRam          FALSE
#define Insyde_Bios             TRUE    //FALSE
#define Sha1Support 			FALSE   //  sha1 function support 
#define _8S_Reset_Support       TRUE


//-----------------------------------------------------------------------------
// Power sequence
//-----------------------------------------------------------------------------
#define ECSleepModeSupport      TRUE    // TRUE   support EC sleep mode  //lw
#define PowerSequnceOnly        FALSE   // TRUE   only support 1ms function

//-----------------------------------------------------------------------------
// Fan & Thermal
//-----------------------------------------------------------------------------
#define SmartFanSupport         TRUE    // True : Support smart fan control function
#define GetCPUTempSupport       FALSE   // True : get cpu temperature via PECI or thermal sensor per second
#define GetSysTempSupport       FALSE   // True : get thermal sensor local temperature per second

#define OEM_GPU_TS_SUPPORT		FALSE   // for Read GPU Thermal sensor 
#define OEM_GPU_ITS_SUPPORT		FALSE   // for Read GPU internal Thermal sensor 


//-----------------------------------------------------------------------------
// Battery
//-----------------------------------------------------------------------------
#define SmartCharger_Support	TRUE   // True : using charger IC for battery charge control
#define BAT1FuncSupport         TRUE   // True : support battery 1 management function
#define FWUSupport              TRUE   //  Support battery firmeare  update


//#define AdapterProtect_Support 

//#define SYSTEM_POWER_PROTECT_SUPPORT 

//-----------------------------------------------------------------------------
// PECI
//-----------------------------------------------------------------------------
#ifdef PECI_Support
#define ReadCPUTemperature      TRUE    // FALSE   // 1 : Getting CPU temperature via PECI interface
#define ReadPKGTemperature      TRUE    // 1 : Getting package temperature via PECI interface
#define ReadDRAMTemperature     FALSE    // 1 : Getting DRAM temperature via PECI interface
#define ACTurboControlAlgorithm FALSE   
#endif

//-----------------------------------------------------------------------------
// OEM_Event.C Debounce time setting
//-----------------------------------------------------------------------------
#define T_AC_DEBOUNCE    	    5       // 50 ms (timebase: 10 ms)
#define T_PSW_DEBOUNCE   	    5  	    // 50 ms (timebase: 10 ms)
#define T_BAT_DEBOUNCE   	    15      // 150 ms (timebase: 10 ms)
#define T_LID_DEBOUNCE          10 
#define T_DESTROY_KEY_DEBOUNCE  5 
#define T_50ms_DEBOUNCE   	    5    	// 50 ms (timebase: 10 ms)

#define T_10ms_DEBOUNCE   	    1    	// 50 ms (timebase: 10 ms)


#define T_PSWOFF         	    500 	// 5 secs (timebase: 10ms) EC 5sec override turn off system power
#define T_PSWPAUSE              20      // 200ms  mini  pause width

#define T_EXTEVT_DEBOUNCE 	    10      // 100 ms (timebase: 10 ms)
#define T_key_DEBOUNCE 	    	5       // 50 ms (timebase: 10 ms)
#define T_SYS_SHUT_DEBOUNCE     1
#define T_SYS_RESET_DEBOUNCE    1


//-----------------------------------------------------------------------------
// Power On Sequence Time-Out Condition
//-----------------------------------------------------------------------------
#define T_HWPG           	    500  	// 500ms (timebase: 1ms)

//-----------------------------------------------------------------------------
// SCI Q-event define
//-----------------------------------------------------------------------------
#define PowerManagement         0x20
#define CPU_ADJUST_F_EVT        0x9F


#define AC_HOT_PLUG_EVT			0xA0
#define CPU_TEMP_EVT			0XA1
// RESERVED EVENT NUMBER 0xA1 .. 0xAF
#define BAT_LOW_EVT				0xB0
#define BAT1_HOT_PLUG_EVT		0xB1                                      
#define BAT2_HOT_PLUG_EVT		0xB2

#define BAT1_STATUS_EVT         0xB3
// RESERVED EVENT NUMBER 0xB3 .. 0xBF                                      
#define THERMAL_EVT				0xC0
// RESERVED EVENT NUMBER 0xC1 .. 0xCF 
#define LID_EVT					0xD0
#define BackLight_DOWN_EVT      0xD1
#define BackLight_UP_EVT        0xD2

// RESERVED EVENT NUMBER 0xD3 .. 0xDF
#define FN_SLEEP_EVT			0xEB
#define FN_INVERTER_EVT			0x44
#define FN_DisplayMode_EVT		0xE1//0xE2
#define FN_TP_EVT			    0x44
#define FN_RF_EVT			    0x44//0xE4
#define FN_HOTKEY6_EVT			0x44//0xE5
#define FN_HOTKEY7_EVT			0x44//0xE6
#define FN_HOTKEY8_EVT			0x44//0xE7
#define FN_HOTKEY9_EVT			0x44//0xE8
#define FN_HOTKEY10_EVT			0x44//0xE9
#define FN_SETBK_EVT			0x44
#define FN_HOTKEY12_EVT			0x44
#define Fn_CAM_EVT              0x44
#define WL_SW_EVT               0x44
#define NOTIFY_EM_EVT           0x44
#define	ALS_EVENT				0xD3
#define	GS_EVENT				0xD4


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define Lenovo_Support          TRUE
#define NUMPAD_MATH_USE_OEM     FALSE //TRUE
#define NUMPAD_USE_OEM          FALSE //

#endif
