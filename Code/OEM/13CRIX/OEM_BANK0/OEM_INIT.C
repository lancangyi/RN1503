/*-----------------------------------------------------------------------------
 * TITLE: OEM_INIT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
void Oem_StartUp(void)
{

}

//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{

	LWORD *pnt;
	
	pnt = sha1_auth(&HashRandom);    // only for compile
	

	Init_GPIO();
	
    #ifdef HSPI
	GPIO_HSPI_INIT();
    #endif

    #ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);
    #endif

    #ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
    #endif

    #ifdef PLLFrequency
    ChangePLLFrequency(PLLFrequency);
    #endif

    #ifdef PECI_Support
    Init_PECI();
    #endif

	Init_Regs();

    #ifdef SMBusChannel4Support
    InitSMBusChannel4();
    #endif
	Init_SMBus_Regs();
    
    #if ADCFuncSupport    
	Init_ADC();
    #endif

    #if CIRFuncSupport	
	Init_CIR();
    #endif

	Init_Cache();
	Init_PS2Port();
    
    #ifdef SysMemory2ECRam	
	InitSysMemory2ECRam();
    #endif
	
    InitSMBus();
	
    ResetSCIEvent();
	Init_OEMVariable();

	if(ExtendScanPin==0x02)		// KSO16 and KSO17 are used.
	{  
		if(ExternMatrixGPO)
		{
			ExtendScanPin++;
		}
	}
   
	ExtWDTInit();
	InitThermalChip();
	
}

//----------------------------------------------------------------------------
// The function of init. registers 
//----------------------------------------------------------------------------
//const struct REG_INIT_DEF code reg_init_table[] = 
const sREG_INIT_DEF code reg_init_table[] = 
{
        { &FMSSR 		,Init_FMSSR         }, 	// share rom size
// HOST interface
    	{ &SPCTRL1      ,Init_I2EC+0x80          },  // Enable I2EC R/W
    	{ &BADRSEL      ,Init_BADR          },  // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define
    	{ &SWCBALR      ,Init_SWCBALR       },
    	{ &SWCBAHR      ,Init_SWCBAHR       },
		{ &RSTS			,0x84				},

// KBC and PM interface
		{ &KBIRQR 		,0x00				},	// Disable KBC IRQ
        { &KBHICR 		,IBFCIE+PM1ICIE     }, 	// KBC port control IBFCIE+PMICIE
        // KBC and PM3 interface
        #ifdef PMC3_Support
        { &PM3CTL 		,IBFIE         	    }, 	// PMC3 input buffer full interrupt enable
        #endif	

// PS2
        { &PSCTL1 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL2 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL3 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
		{ &PSINT1		,0x04				}, 	// Transation Done,Start Clock Interrupt
        { &PSINT2		,0x04				},	// Transation Done,Start Clock Interrupt 
        { &PSINT3		,0x04				},	// Transation Done,Start Clock Interrupt 

// Key Scan
        { &KSOCTRL   	,KSOOD + KSOPU      },	//
  		{ &KSICTRL   	,KSIPU       		},	//

		// ADC	
  		{ &ADCSTS    	,AINITB             }, 	// Enable Analog accuracy initialization
        { &ADCSTS    	,0x80          		}, 	// Stop adc accuracy initialization
		{ &ADCCFG    	,0         			}, 	//
        { &KDCTL     	,AHCE              	}, 	// Enable Hardware Callibration
		{ &ADCCFG    	,DFILEN  		    },	// Enable Digital Filter enable,
		{ &ADCCTL		,0x15				},  // ADC clock divider 

// DAC
       { &DACPWRDN  	,0x00              	}, 	//
    
//PWM   
//channel 3: Beep   ----->  C6    1K
//channel 4: blacklight ---> C0    500Hz
//channel 7: Fan --------> C4    24K
//=========================
// Group 	Prescaler channel  PCFSR
//   0   	C0CPRS
//   1   	C4MCPRS   C4CPRS	
//   2   	C6MCPRS   C6CPRS
//   3   	C7MCPRS   C7CPRS

//Fan PWM = 9200000Hz
//=========================
// PCSSG
//  0 0    C0
//  0 1    C4
//  1 0    C6
//  1 1    C7

		{ &ZTIER        ,0x00       		},   // Disable
        { &CTR      	,0x3F      		    },   //	Set CTR = 200 Duty Cycle output = (DCRi)/(CTR+1)
        { &C0CPRS       ,0x00               },   // Cpu Fan  =  144KHZ  
		{ &C4CPRS    	,0x00				},	 // Panel    = 510Hz
		{ &C4MCPRS	    ,0x00				},   //
		{ &C6CPRS    	,0x8F				},	 // Beep =  1KHz
		{ &C6MCPRS		,0x00				},	 //
		{ &C7CPRS    	,0x00				},	 // Gpu Fan  = 144KHZ  
		{ &C7MCPRS		,0x00				},   //
		{ &PCFSR        ,0x07      		    },   // bit7=1: Disable CR256 channel 1 output. bit0-bit3: 0 => select 32.768 kHz, 1=> select EC clock frequency  
        { &PCSSGL       ,0x80      		    },   // Select channel 0-3 Group
		{ &PCSSGH       ,0x40				},	 // Select channel 4-7 Group
		{ &ZTIER        ,0x02       		},   // Enable
        { &DCR3         ,0x00      		    },   // Default 
        { &DCR4         ,0x00      		    },   // Default 
        { &DCR7         ,0x00      			},   // Default
};


void Init_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(reg_init_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = reg_init_table[index].address;
		*Tmp_XPntr = reg_init_table[index].initdata;
        index ++;
    }
}

//const struct REG_INIT_DEF code Init_SMBus_table[] = 
const sREG_INIT_DEF code Init_SMBus_table[] = 
{
// SMBus   100K 

	    { &SMB4P7USL	, 0x28				},	// 100K	
	    { &SMB4P0USH  	, 0x25      		},  
        { &SMB300NS     , 0x03      		},  
        { &SMB250NS     , 0x02      		},   
        { &SMB25MS      , 0x19      		},   
        { &SMB45P3USL   , 0xA5      		},  
        { &SMBS4P3USH   , 0x01      		},   
        { &SMB4P7A4P0H	, 0x00      		},  


/*
	    { &SMB4P7USL	, 0x71				},	// 20K	
	    { &SMB4P0USH  	, 0xdd      		},  
        { &SMB300NS     , 0x03      		},  
        { &SMB250NS     , 0x71      		},   
        { &SMB25MS      , 0x19      		},   
        { &SMB45P3USL   , 0x5c      		},  
        { &SMBS4P3USH   , 0x01      		},   
        { &SMB4P7A4P0H	, 0x00      		},  
*/

        { &HOCTL2_A 	, 0x01      		},  
        { &HOCTL_A   	, 0x03      		},  
        { &HOCTL_A  	, 0x01      		},  
        { &HOSTA_A    	, 0xFF      		},  
        
        { &HOCTL2_B   	, 0x01      		},  
        { &HOCTL_B    	, 0x03      		},	
        { &HOCTL_B    	, 0x01      		},	
        { &HOSTA_B    	, 0xFF      		},	
        
    	{ &HOCTL2_C		, 0x01				},	 
   	 	{ &HOCTL_C		, 0x03				},	 
   		{ &HOCTL_C		, 0x01				},	 
    	{ &HOSTA_C		, 0xFF				},
            
        #ifdef SMBusChannel4Support
    	{ &HOCTL2_D		, 0x01				},	 
   	 	{ &HOCTL_D		, 0x03				},	 
   		{ &HOCTL_D		, 0x01				},	 
    	{ &HOSTA_D		, 0xFF				},
        #endif
};

void Init_SMBus_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(Init_SMBus_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[index].address;
		*Tmp_XPntr = Init_SMBus_table[index].initdata;
        index ++;
    }
}

//----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//----------------------------------------------------------------------------
void Init_ClearRam(void)
{
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }

}

//----------------------------------------------------------------------------
// The function of DMA for scratch sram
//----------------------------------------------------------------------------
const sDMAScratchSRAM code asDMAScratchSRAM[]=    // For 8500 Dino
{
	{	&SCRA1H,	&SCRA1M,	&SCRA1L	},		// 1024 bytes (externl ram 0x800 ~ 0xBFF)
	{	&SCRA2H,	&SCRA2M,	&SCRA2L	},		// 512 bytes  (externl ram 0xC00 ~ 0xDFF)
	{	&SCRA3H,	&SCRA3M,	&SCRA3L	},		// 256 bytes  (externl ram 0xE00 ~ 0xEFF)
	{	&SCRA4H,	&SCRA4M,	&SCRA4L	}		// 256 bytes  (externl ram 0xF00 ~ 0xFFF)

};
void  CacheDma(BYTE sramnum,WORD addr)
{
	*asDMAScratchSRAM[sramnum].scarh = 0x80;
	*asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;   	// high byte of function address
	*asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;	// low byte of function address
	*asDMAScratchSRAM[sramnum].scarh = 0x00;	// start cache dma     			
}

//----------------------------------------------------------------------------
// Init. DMA for scratch sram
//----------------------------------------------------------------------------
void Init_Cache(void)
{
#ifdef ITE8500					// Dino For 8500 no cache ram 0x800 ~ 0xFFF

#else
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        CacheDma(3, HSPI_RamCode);  // Cache to memory 0xF00 ~ 0xFFF
        #endif
    #endif
#endif

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//----------------------------------------------------------------------------
// Select touch pad, mouse, and keyboard port number
//----------------------------------------------------------------------------
void Init_PS2Port(void)
{

}

//----------------------------------------------------------------------------
// Function Name : Init_OEMVariable
// Purpose : setup default variable when EC reset
//----------------------------------------------------------------------------
void Init_OEMVariable(void)
{
 
#ifdef AdapterProtect_Support

	    SystemPowerCtrlStep = PowerCtrlStep_Start;

#endif


	Oem_GPU_EC_BLK = Oem_GPU_BLK + Oem_EC_BLK;

	LED_FLASH_CNT = 0x0001;	// for LED control

	ECMainVersionInfo = OEM_Version_MSB;
	ECVersionInfo = OEM_Version_LSB;

	PECI_PowerCtrlStep = 0x01;

	Bios_Battery_Health_0 |= EDCC; //default  end calibration cycle

	Device_Status_Lenovo |= Wireless_S_B;
	Device_Status_Lenovo |= Bluetooth_S_B;
	Device_Status_Lenovo |= Inverter_S_B;
	Device_Status_Lenovo |= Camera_S_B;	

	Oem_Device_Status |= Wireless_IN;
	Oem_Device_Status |= Bluetooth_IN;
	Oem_Device_Status |= Inverter_IN;
	Oem_Device_Status |= Camera_IN;
    
    
	Oem_Globe_Flag2 = 0;
	SysPostTime = 0;
	
    
	SysPowState=SYSTEM_S5;		
	if((BRAM[63]==0x55) && (ShutDnCause==SC_IntWatchDog))
	{
		BRAM[63]=0x00;
		CLEAR_MASK(KBHISR,SYSF);	
        Ccb42_SYS_FLAG=0;
		DelayDoPowerSeq=250;
		Oem_TriggerS5S0();
	}

	if((0x55==BRAM_FLASH_ID0)&&(0xaa==BRAM_FLASH_ID1)&&(0x55==BRAM_FLASH_ID2)&&(0xaa==BRAM_FLASH_ID3))
	{
		Delay1MS(10);
		//RSMRST_OFF();
	}


	if(Read_ACIN())
	{
        AC_ON();
		OS_PM_STATE |= OS_AC_IN;
		POWER_FLAG1	|= adapter_in;
	}

	if(Read_BatIN())
	{
		OS_PM_STATE |= OS_BAT1_IN;
		BT1_STATUS1	|= bat_in;
	}		


	if(Read_BatIN())
	{		
		SetBAT1CtrlStep(BAT_Step_ID);		
	}

	Init_Heating();
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      Before jump to main function [WinFlashMark = 0x33;] is necessary.
//----------------------------------------------------------------------------
void Hook_ECExitFollowMode(void)
{
    Init_Cache();
    
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        SET_MASK(IER7,Int_DeferredSPI); // Enable HSPI interrupt
        #endif
    #endif 
    
    InitSMBus();
    
    #if Insyde_Bios
    if(RamCodePort==0x64)   // for insyde bios
    {
        KBHIKDOR = 0xFA;
    }
    else if(RamCodePort==0x66)
    {
	    PM1DO = 0xFA;
    }	
    else if(RamCodePort==0x6C)
    {
	    PM2DO = 0xFA;
    }  
    #endif
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      1. Before jump to main function if want to keep EC setting [return(0x33);] is necessary.
//      2. If you don't understand the use of Hook_ECRetunrMainFuncKeepCondition function, 
//          don't change anything.
//      3. Always at bank0 (0x9000)
//----------------------------------------------------------------------------
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if(WinFlashMark==0x33)
    {
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}
