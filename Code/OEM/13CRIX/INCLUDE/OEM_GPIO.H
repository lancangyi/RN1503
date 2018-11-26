/*-----------------------------------------------------------------------------
 * TITLE: OEM_GPIO.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/
 
#ifndef OEM_GPIO_H
#define OEM_GPIO_H

//-----------------------------------------------------------------
// 
//-----------------------------------------------------------------
#define HighActive  	1
#define LowActive     	0

//-----------------------------------------------------------------
// GPIO Registers define
//-----------------------------------------------------------------
/*  General Control Register (GCR)  */
// BIT 7     -  GPIOB5 HIGH Follow LPCRST# HIGH-to-LOW
// BIT 6     -  WUI7 Enabled
// BIT 5     -  WUI6 Enabled
// BIT [2:1] -  [01] LPCRST# in GPIOB7
//              [10] LPCRST# in GPIOD2
//              [11] LPCRST# is dsiabled 
#define GCR_Init		0x06             
#define GCR2_Init		0x00			 

//-----------------------------------------------------------------
// GPIO Port A Registers define
//-----------------------------------------------------------------
#define PortA_Init		0x02            // PORT Data  

#define PortA0_Ctrl		ALT			    //  CPU Fan control  PWM
#define PortA1_Ctrl		OUTPUT			//  Power_LED 低电平有效
#define PortA2_Ctrl		OUTPUT			//  GPU Heating EN
#define PortA3_Ctrl		OUTPUT 			//  MBAT LED0  
#define PortA4_Ctrl		ALT      		//  LCD BKLT_CTRL  PWM
#define PortA5_Ctrl		INPUT			//  SYS_SHUT_EC 
#define PortA6_Ctrl		OUTPUT			//  MBAT LED1
#define PortA7_Ctrl		ALT             //  GPU FAN control PWM




//-----------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------
#define PortB_Init		0x40            // PORT Data  
#define PortB0_Ctrl		OUTPUT		    // Key Board LED
#define PortB1_Ctrl		OUTPUT			// GPS Enable
#define PortB2_Ctrl		INPUT			// MXLID 
#define PortB3_Ctrl		ALT			    // CLK_SMB
#define PortB4_Ctrl		ALT			    // DAT_SMB
#define PortB5_Ctrl		INPUT			// BAT_IN
#define PortB6_Ctrl		INPUT			// KBRST_R
#define PortB7_Ctrl		INPUT			// SYS_RESET_EC 



//-----------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------
#define PortC_Init		0x10            // PORT Data

#define PortC0_Ctrl		OUTPUT			// LCD HEATING
#define PortC1_Ctrl		ALT				// I2C_CLK  Thermal Sensor 
#define PortC2_Ctrl		ALT				// I2C_DATA  Thermal Sensor 
#define PortC3_Ctrl		OUTPUT			// BT Enable
#define PortC4_Ctrl		OUTPUT	        // HT LED 低电平有效

#define PortC5_Ctrl		OUTPUT	        // RF ENABLE
#define PortC6_Ctrl		OUTPUT			// EDP VDD EN 
#define PortC7_Ctrl		OUTPUT			// EC_GPF7

//-----------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------
#define PortD_Init		0x00            // PORT Data

#define PortD0_Ctrl		INPUT			// BACKL_EN     backlight
#define PortD1_Ctrl		INPUT			// SUS_STAT# 
#define PortD2_Ctrl		INPUT			// LPCRST

#define PortD3_Ctrl		OUTPUT			//  
#define PortD4_Ctrl		ALT				// EXT_SMI#

#define PortD5_Ctrl		OUTPUT			// EC_VR_ON
#define PortD6_Ctrl		ALT 		    // CPU FAN TACH
#define PortD7_Ctrl		ALT      	    // GPU FAN TACH


//-----------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------
#define PortE_Init		0x80            // PORT Data

#define PortE0_Ctrl		INPUT			//VR HOT N
#define PortE1_Ctrl		OUTPUT			// RUN_ON
#define PortE2_Ctrl		OUTPUT			// SUS_ON
#define PortE3_Ctrl		OUTPUT			// PWR_ON 
#define PortE4_Ctrl		INPUT			// PWRSW_R

#define PortE5_Ctrl		OUTPUT			// PCIRST3
#define PortE6_Ctrl		INPUT			// 1.8V_PWRGD
#define PortE7_Ctrl		OUTPUT			// LIDIN

//-----------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------
#define PortF_Init		0x00            // PORT Data

#define PortF0_Ctrl		OUTPUT		    // PCIRST1
#define PortF1_Ctrl		OUTPUT		    // PCIRST2
#define PortF2_Ctrl		OUTPUT		    // BLT_OFF_EC
#define PortF3_Ctrl		OUTPUT          // WLAN_RF_ENABLE
#define PortF4_Ctrl		ALT             // CLK_TP
#define PortF5_Ctrl		ALT 		    // DAT_TP
#define PortF6_Ctrl		ALT	       	    // CLK_GPU
#define PortF7_Ctrl		ALT	            // DAT_GPU

//-----------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------
#define PortG_Init		0x00            // PORT Data

#define PortG0_Ctrl		INPUT			// RECOVER_BT
#define PortG1_Ctrl		INPUT       	// HDD DESTROY_KEY
#define PortG2_Ctrl		OUTPUT          // LAN GPIO1

#define PortG3_Ctrl		INPUT           // NC    (null)
#define PortG4_Ctrl		INPUT           // NC    (null)
#define PortG5_Ctrl		INPUT           // NC    (null)
#define PortG6_Ctrl		INPUT			// NC 
#define PortG7_Ctrl		INPUT           // NC    (null)

//-----------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------
#define PortH_Init		0x00            // PORT Data

#define PortH0_Ctrl		INPUT+PULL_DW   // ACIN 
#define PortH1_Ctrl		OUTPUT			// VDDA Enable
#define PortH2_Ctrl		INPUT			// VCORE_PGOOD
#define PortH3_Ctrl		OUTPUT		    // FT_POR_N
#define PortH4_Ctrl		INPUT		    // VDDA_PWRGD

#define PortH5_Ctrl		INPUT		    // SB_PWRGD
#define PortH6_Ctrl		OUTPUT		    // S5_PWR_ON


//-----------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------
#define PortI_Init		0x20            // PORT Data

#define PortI0_Ctrl		INPUT           // KILL_HDD
#define PortI1_Ctrl		OUTPUT			// BAT Charger
#define PortI2_Ctrl		INPUT			// EDP HPD侦测PIN，做EDP PWM输出的标志位

#define PortI3_Ctrl		ALT	       	   // IADP  ADC adapter current 侦测
#define PortI4_Ctrl		ALT		       // IBATDIS dischager current 侦测

#define PortI5_Ctrl		OUTPUT		    // have the same behavior with the GPE5 
#define PortI6_Ctrl		INPUT		    // Right_IO_PWROK 
#define PortI7_Ctrl		INPUT       	// R226 to GND

//-----------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------
#define PortJ_Init		0x02            // PORT Data 

#define PortJ0_Ctrl		OUTPUT			// GBE0_DISABLE 
#define PortJ1_Ctrl		OUTPUT			// HW_POP_MUTE_EC
#define PortJ2_Ctrl		OUTPUT			// GBE1_DISABLE
#define PortJ3_Ctrl		OUTPUT			// BATSEL
#define PortJ4_Ctrl		OUTPUT			//CAPS_LED#
#define PortJ5_Ctrl		OUTPUT			// MAIN_ON




//-----------------------------------------------------------------------------
//   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//-----------------------------------------------------------------------------
#define PWR_LED_ON()		CLEAR_MASK(GPDRA,BIT(1))
#define PWR_LED_OFF()		SET_MASK(GPDRA,BIT(1))

#define GPU_HEAT_ON()    SET_MASK(GPDRA,BIT(2))
#define GPU_HEAT_OFF()	CLEAR_MASK(GPDRA,BIT(2))


#define BATLED0_ON()        SET_MASK(GPDRA,BIT(3))
#define BATLED0_OFF()       CLEAR_MASK(GPDRA,BIT(3))



#define Read_SysShutdown()  IS_MASK_SET(GPDRA,BIT(5))



#define BATLED1_ON()        SET_MASK(GPDRA,BIT(6))
#define BATLED1_OFF()       CLEAR_MASK(GPDRA,BIT(6))
#define Read_BATLED1_ON()   IS_MASK_SET(GPDRA,BIT(6))    

//-----------------------------------------------------------------------------
//   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
//-----------------------------------------------------------------------------

#define KBLED_ON()           SET_MASK(GPDRB,BIT(0))
#define KBLED_OFF()          CLEAR_MASK(GPDRB,BIT(0))

#define BD_EN_ON()         SET_MASK(GPDRB,BIT(1))
#define BD_EN_OFF()        CLEAR_MASK(GPDRB,BIT(1))


#define Read_MXLID()       IS_MASK_CLEAR(GPDRB,BIT(2)) 

#define Read_BatIN()       IS_MASK_CLEAR(GPDRB,BIT(5))

#define Read_ComStatus()   IS_MASK_SET(GPDRB,BIT(6))

#define Read_SysReset()    IS_MASK_SET(GPDRB,BIT(7))

//-----------------------------------------------------------------------------
//   CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//-----------------------------------------------------------------------------

#define LCD_HEAT1_ON()	SET_MASK(GPDRC,BIT(0))
#define LCD_HEAT1_OFF()	CLEAR_MASK(GPDRC,BIT(0))


#define BT_EN_ON()			SET_MASK(GPDRC,BIT(3))
#define BT_EN_OFF()			CLEAR_MASK(GPDRC,BIT(3))


#define HT_LED_ON()		    CLEAR_MASK(GPDRC,BIT(4))
#define IS_HT_LED_ON()		IS_MASK_CLEAR(GPDRC,BIT(4))   //lw 2017/12/29
#define HT_LED_OFF()		SET_MASK(GPDRC,BIT(4))


#define RF_ON()		        SET_MASK(GPDRC,BIT(5))
#define RF_OFF()            CLEAR_MASK(GPDRC,BIT(5))


#define EDP_VDD_ON()		SET_MASK(GPDRC,BIT(6))
#define EDP_VDD_OFF()		CLEAR_MASK(GPDRC,BIT(6))


#define LCD_HEAT2_ON()	   SET_MASK(GPDRC,BIT(7))
#define LCD_HEAT2_OFF()	   CLEAR_MASK(GPDRC,BIT(7))


//-----------------------------------------------------------------------------
//   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
//-----------------------------------------------------------------------------

#define Read_BACKL_EN()			IS_MASK_CLEAR(GPDRD,BIT(0))     
#define Read_SUS_STAT()         IS_MASK_SET(GPDRD,BIT(1))
#define Read_LPCRST()			IS_MASK_SET(GPDRD,BIT(2))  
#define GPD3_ON()			    SET_MASK(GPDRD,BIT3)
#define GPD3_OFF()			    CLEAR_MASK(GPDRD,BIT3)

#define SMI_ON()			    CLEAR_MASK(GPDRD,BIT4)
#define SMI_OFF()			    SET_MASK(GPDRD,BIT4)

#define VCORE_EN_ON()           SET_MASK(GPDRD,BIT(5))
#define VCORE_EN_OFF()          CLEAR_MASK(GPDRD,BIT(5))




//-----------------------------------------------------------------------------
//   EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
//-----------------------------------------------------------------------------

#define RUN_ON()				SET_MASK(GPDRE,BIT(1))
#define RUN_OFF()				CLEAR_MASK(GPDRE,BIT(1))

#define SUSON_ON()				SET_MASK(GPDRE,BIT(2))
#define SUSON_OFF()				CLEAR_MASK(GPDRE,BIT(2))

#define PWRON_ON()				SET_MASK(GPDRE,BIT(3))
#define PWRON_OFF()				CLEAR_MASK(GPDRE,BIT(3))

#define Read_PWRSW()		    IS_MASK_CLEAR(GPDRE,BIT(4))

#define PCIRST3_ON()            SET_MASK(GPDRE,BIT(5))    
#define PCIRST3_OFF()           CLEAR_MASK(GPDRE,BIT(5))

#define Read_1V8_PWRGD()        IS_MASK_SET(GPDRE,BIT(6))

#define LID_ON()				SET_MASK(GPDRE,BIT(7))  
#define LID_OFF()				CLEAR_MASK(GPDRE,BIT(7))


//-----------------------------------------------------------------------------
//   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//-----------------------------------------------------------------------------

#define PCIRST1_ON()			SET_MASK(GPDRF,BIT(0))
#define PCIRST1_OFF()			CLEAR_MASK(GPDRF,BIT(0))

#define PCIRST2_ON()		    SET_MASK(GPDRF,BIT(1))
#define PCIRST2_OFF()		    CLEAR_MASK(GPDRF,BIT(1))


#define EC_BLT_EN_ON()			SET_MASK(GPDRF,BIT(2))  
#define EC_BLT_EN_OFF()			CLEAR_MASK(GPDRF,BIT(2))
#define Read_BLT_EN()           IS_MASK_SET(GPDRF,BIT(2))

#define WLAN_PWR_EN_ON()        SET_MASK(GPDRF,BIT(3))
#define WLAN_PWR_EN_OFF()       CLEAR_MASK(GPDRF,BIT(3))

      
//-----------------------------------------------------------------------------
//   GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
//-----------------------------------------------------------------------------



#define Read_RECOVER_BT()      IS_MASK_CLEAR(GPDRG,BIT(0)) 

#define Read_DESTROY_KEY()     IS_MASK_CLEAR(GPDRG,BIT(1)) 

#define EC_LAN_ON()            SET_MASK(GPDRG,BIT(2))
#define EC_LAN_OFF()           CLEAR_MASK(GPDRG,BIT(2))

//-----------------------------------------------------------------------------
//   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
//-----------------------------------------------------------------------------

#define Read_ACIN()	           IS_MASK_SET(GPDRH,BIT(0))   

#define EC_VDDAEN_ON()         SET_MASK(GPDRH,BIT(1)) 
#define EC_VDDAEN_OFF()        CLEAR_MASK(GPDRH,BIT(1)) 

#define Read_VCORE_PWRGD()     IS_MASK_SET(GPDRH,BIT(2))

#define FT_POR_N_ON()          SET_MASK(GPDRH,BIT(3))
#define FT_POR_N_OFF()         CLEAR_MASK(GPDRH,BIT(3))

#define Read_VDDA_PWRGD()      IS_MASK_SET(GPDRH,BIT(4))

#define Read_SB_PWRGD()         IS_MASK_SET(GPDRH,BIT(5))

#define S5_PWR_ON()             SET_MASK(GPDRH,BIT(6))
#define S5_PWR_OFF()            CLEAR_MASK(GPDRH,BIT(6))
 

//-----------------------------------------------------------------------------
//   IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
//-----------------------------------------------------------------------------
#define Read_KILL_HDD()			IS_MASK_SET(GPDRI,BIT(0))
#define BAT_Charger_ON()        SET_MASK(GPDRI,BIT(1))
#define BAT_Charger_OFF()       CLEAR_MASK(GPDRI,BIT(1))

#define Read_EDP_HPD_L()        IS_MASK_SET(GPDRI,BIT(2))

#define GPI5_ON()              SET_MASK(GPDRI,BIT(5))
#define GPI5_OFF()             CLEAR_MASK(GPDRI,BIT(5))



#define Read_VCORE_TALERT()     IS_MASK_CLEAR(GPDRI,BIT(6))

//-----------------------------------------------------------------------------
//   JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ
//-----------------------------------------------------------------------------

#define LAN1_DISABLE_ON()       SET_MASK(GPDRJ,BIT(0)) 
#define LAN1_DISABLE_OFF()      CLEAR_MASK(GPDRJ,BIT(0))

#define VOLMUTE_ON()			SET_MASK(GPDRJ,BIT(1))      
#define VOLMUTE_OFF()			CLEAR_MASK(GPDRJ,BIT(1))   

#define LAN2_DISABLE_ON()       SET_MASK(GPDRJ,BIT(2)) 
#define LAN2_DISABLE_OFF()      CLEAR_MASK(GPDRJ,BIT(2))

#define BATSEL_B()              SET_MASK(GPDRJ,BIT(3)) 
#define BATSEL_A()              CLEAR_MASK(GPDRJ,BIT(3)) 

#define CAPS_LED_ON()           SET_MASK(GPDRJ,BIT(4)) 
#define CAPS_LED_OFF()          CLEAR_MASK(GPDRJ,BIT(4))


#define MAIN_ON()             SET_MASK(GPDRJ,BIT(5))
#define MAIN_OFF()            CLEAR_MASK(GPDRJ,BIT(5)) 




 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------




#define PWM_VADJ		DCR4    // backlight
#define GPUFan_volt		DCR7    // GPU Fan
#define CPUFan_volt     DCR0    // CPU Fan
#define PC_BEEP_PWM	    DCR3    // beep



#define Read_SYS_I()	    Fix_ADCAvg1             // System current
#define Read_VAdapter()     ADCAvg0                 // Adapter voltage
#define Read_CPU_VCC()      //ADCAvg0                    
#define Read_CPU_ICC()      //ADCAvg1
#define Read_GFX_VR_VCC()   //ADCAvg3
#define Read_GFX_VR_ICC()   //ADCAvg4



extern void Init_GPIO(void);
extern void TurnOnOffWlan(void);
extern void TurnOnOffBT(void);
extern void Hook_SCION(void);
extern void Hook_SCIOFF(void);
extern void Hook_SMION(void);
extern void Hook_SMIOFF(void);

extern void Hook_A20ON(void);

extern void Hook_PWR_ON(void);
extern void Hook_SUS_ON(void);
extern void Hook_VCORE_EN_ON(void);
extern void Hook_ECVDDA_ON(void);

extern void Hook_PCIRST1_ON(void);
extern void Hook_PCIRST23_ON(void);
extern void Hook_PCIRST23_OFF(void);
extern void Hook_PCIRST1_OFF(void);
extern void Hook_FTPOR_OFF(void);
extern void Hook_FTPOR_ON(void);

extern void Hook_ECVDDA_OFF(void);
extern void Hook_VCORE_EN_OFF(void);
extern void Hook_SUS_OFF(void);
extern void Hook_PWR_OFF(void);
extern void Hook_MISCPWR_ON(void);
extern void Hook_MISCPWR_OFF(void);


extern void Hook_A20OFF(void);
extern void Hook_KBRSTON(void);
extern void Hook_KBRSTOFF(void);
extern void Hook_NUMLED_ON(void);
extern void Hook_NUMLED_OFF(void);
extern void Hook_CAPLED_ON(void);
extern void Hook_CAPLED_OFF(void);
extern void BackLight_ON(BYTE blk);
extern void BackLight_OFF(BYTE blk);

typedef struct InitGPIOReg
{
    XBYTE 	*reg;	
	BYTE	value;
} sInitGPIOReg;

#endif
