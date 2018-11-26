/*-----------------------------------------------------------------------------
 * TITLE: CORE_IRQ.C - Interrupt Service Routines (ISR).
 *
 * The Interrupt Service Routines (ISR).  The actual interrupt functions are
 * implemented in the "CHIP_IRQ.C".
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

//----------------------------------------------------------------------------
// Input full irq lock scan
//----------------------------------------------------------------------------
void IrqLock_scan(void)
{
	Int_Var.Scan_Lock = 1;
    //Timer_B.fbit.SEND_ENABLE = 0;	// Lock scanner. 
}

//----------------------------------------------------------------------------
// Null function
//----------------------------------------------------------------------------
void IRQ_INT0_Null(void)
{

}

//----------------------------------------------------------------------------
// WKO[20]
//----------------------------------------------------------------------------
void IRQ_INT1_WKO20(void)
{
    Hook_IRQ_INT1_WKO20();
}

//----------------------------------------------------------------------------
// KBC Output Buffer Empty Interrupt
//----------------------------------------------------------------------------
void IRQ_INT2_KBCOBE(void)
{
    Hook_IRQ_INT2_KBCOBE();
}

//----------------------------------------------------------------------------
// PMC Output Buffer Empty Intr. PMC1 Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void IRQ_INT3_PMCPMC1OBE(void)
{
    Hook_IRQ_INT3_PMCPMC1OBE();
}

//----------------------------------------------------------------------------
// SMBus D Interrupt
//----------------------------------------------------------------------------
void IRQ_INT4_SMBusD(void)
{
    Hook_IRQ_INT4_SMBusD();
}

//----------------------------------------------------------------------------
// WKINTAD (WKINTA or WKINTD)
//----------------------------------------------------------------------------
void IRQ_INT5_WKINTAD(void)
{
    Hook_IRQ_INT5_WKINTAD();
}

//----------------------------------------------------------------------------
// WKO[23]
//----------------------------------------------------------------------------
void IRQ_INT6_WKO23(void)
{
    Hook_IRQ_INT6_WKO23();
}

//----------------------------------------------------------------------------
// PWM Interrupt
//----------------------------------------------------------------------------
void IRQ_INT7_PWM(void)
{
    Hook_IRQ_INT7_PWM();
}

//----------------------------------------------------------------------------
// ADC Interrupt
//----------------------------------------------------------------------------
void IRQ_INT8_ADC(void)
{
    Hook_IRQ_INT8_ADC();
}

//----------------------------------------------------------------------------
// SMBus A Interrupt
//----------------------------------------------------------------------------
void IRQ_INT9_SMBusA(void)
{
    Hook_IRQ_INT9_SMBusA();
}

//----------------------------------------------------------------------------
// SMBus B Interrupt
//----------------------------------------------------------------------------
void IRQ_INT10_SMBusB(void)
{
    Hook_IRQ_INT10_SMBusB();
}

//----------------------------------------------------------------------------
// KB Matrix Scan Interrupt
//----------------------------------------------------------------------------
void IRQ_INT11_KBMatrixScan(void)
{
	CLEAR_MASK(IER1,Int_KB);
    ISR1 = Int_KB;
	F_Service_KEY = 1;    	// Post service request to scan internal keyboard. 
    Hook_IRQ_INT11_KBMatrixScan();
}

//----------------------------------------------------------------------------
// WKO[26]
//----------------------------------------------------------------------------
void IRQ_INT12_WKO26(void)
{
    Hook_IRQ_INT12_WKO26();
}

//----------------------------------------------------------------------------
// WKINTC
//----------------------------------------------------------------------------
void IRQ_INT13_WKINTC(void)
{
    Hook_IRQ_INT13_WKINTC();
}

//----------------------------------------------------------------------------
// WKO[25]
//----------------------------------------------------------------------------
void IRQ_INT14_WKO25(void)
{
    Hook_IRQ_INT14_WKO25();
}

//----------------------------------------------------------------------------
// CIR Interrupt
//----------------------------------------------------------------------------
void IRQ_INT15_CIR(void)
{
    Hook_IRQ_INT15_CIR();
}

//----------------------------------------------------------------------------
// SMBus C Interrupt
//----------------------------------------------------------------------------
void IRQ_INT16_SMBusC(void)
{
    Hook_IRQ_INT16_SMBusC();
}

//----------------------------------------------------------------------------
// WKO[24]
//----------------------------------------------------------------------------
void IRQ_INT17_WKO24(void)
{
    Hook_IRQ_INT17_WKO24();
}

//----------------------------------------------------------------------------
// PS/2 Interrupt 2
//----------------------------------------------------------------------------
void IRQ_INT18_PS2Interrupt2(void)
{

    
    #if TouchPad_only
    CLEAR_MASK(IER2,Int_PS2_2); // Disable PS2 interrupt 0
    ISR2 = Int_PS2_2;           // Write to clear pending interrupt

    if(SendtoAUXFlag)
    {
        for(PS2DataPinStatusCounter=0x00;PS2DataPinStatusCounter<5;PS2DataPinStatusCounter++)
        {
            //if(IS_MASK_SET(PSSTS1, DLS))   // DATA Line Status is high
            if(IS_MASK_SET(GPDRF, BIT5))   // DATA Line Status is high
            {
                break;
            }
            else
            {
                WNCKR = 0x00;   // Delay 15.26 us
            }
        }
    }

	PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
	PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
	PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3

    PS2_IRQ_Channel = 2;        // Set PS2 0 service flag
	F_Service_PS2 = 1;          // Set main service flag
    PS2StartBit=0;			    // clear start bit flag
    PS2_SSIRQ_Channel = 0xFF;   //
	PS2PortxData[2]=PSDAT3;
    #else
	
	if(IS_MASK_SET(PSSTS3, TDS))    // Transaction done interrupt 
	{
		CLEAR_MASK(IER2,Int_PS2_2); // Disable PS2 interrupt 2  
	    ISR2 = Int_PS2_2;           // Write to clear pending interrupt
	    
	    if(SendtoAUXFlag)
	    {
            for(PS2DataPinStatusCounter=0x00;PS2DataPinStatusCounter<5;PS2DataPinStatusCounter++)
            {
                if(IS_MASK_SET(PSSTS3, DLS))   // DATA Line Status is high
                {
                    break;
                }
                else
                {
                    WNCKR = 0x00;   // Delay 15.26 us
                }
            }
        }
        else
        {
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
        }
        
		PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
		PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
		PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3

		PS2_IRQ_Channel = 2;        // Set PS2 2 service flag
		F_Service_PS2 = 1;          // Set main service flag
		PS2StartBit=0;		        // clear start bit flag
	    PS2_SSIRQ_Channel = 0xFF;   //
	    PS2PortxData[2]=PSDAT3;
	}
    else					        // Start bit interrupt 
    {
        PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
        PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
        IER2&= ~(Int_PS2_0+Int_PS2_1+Int_PS2_2);    // Disable all PS2 interrupt
        ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
        PS2StartBit = 1;	        // Set start bit flag
        PS2_SSIRQ_Channel = 2;      //
        SET_MASK(IER2,Int_PS2_2);   // Enable PS2 interrupt 2
    }	
    #endif

    Hook_IRQ_INT18_PS2Interrupt2();
}

//----------------------------------------------------------------------------
// PS/2 Interrupt 1
//----------------------------------------------------------------------------
void IRQ_INT19_PS2Interrupt1(void)
{
	if(IS_MASK_SET(PSSTS2, TDS))    // Transaction done interrupt 
	{
		CLEAR_MASK(IER2,Int_PS2_1); // Disable PS2 interrupt 1  
	    ISR2 = Int_PS2_1;           // Write to clear pending interrupt 
	    
	    if(SendtoAUXFlag)
	    {
            for(PS2DataPinStatusCounter=0x00;PS2DataPinStatusCounter<5;PS2DataPinStatusCounter++)
            {
                if(IS_MASK_SET(PSSTS2, DLS))   // DATA Line Status is high
                {
                    break;
                }
                else
                {
                    WNCKR = 0x00;   // Delay 15.26 us
                }
            }
        }
        else
        {
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
            WNCKR = 0x00;           // Delay 15.26 us
        }
        
		PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
		PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
		PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3
   
	    PS2_IRQ_Channel = 1;        // Set PS2 1 service flag
		F_Service_PS2 = 1;          // Set main service flag
        PS2StartBit=0;		        // clear start bit flag
        PS2_SSIRQ_Channel = 0xFF;   //
	    PS2PortxData[1]=PSDAT2;
	}
    else					        // Start bit interrupt 
    {
        PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
        PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3
        IER2&= ~(Int_PS2_0+Int_PS2_1+Int_PS2_2);    // Disable all PS2 interrupt
        ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
        PS2StartBit = 1;	        // Set start bit flag
        PS2_SSIRQ_Channel = 1;      //
        SET_MASK(IER2,Int_PS2_1);   // Enable PS2 interrupt 1
    }	

    Hook_IRQ_INT19_PS2Interrupt1();
}

//----------------------------------------------------------------------------
// PS/2 Interrupt 0
//----------------------------------------------------------------------------
void IRQ_INT20_PS2Interrupt0(void)
{
    #if TouchPad_only
    CLEAR_MASK(IER2,Int_PS2_0); // Disable PS2 interrupt 0
    ISR2 = Int_PS2_0;           // Write to clear pending interrupt

    if(SendtoAUXFlag)
    {
        for(PS2DataPinStatusCounter=0x00;PS2DataPinStatusCounter<5;PS2DataPinStatusCounter++)
        {
            //if(IS_MASK_SET(PSSTS1, DLS))   // DATA Line Status is high
            if(IS_MASK_SET(GPDRF, BIT1))   // DATA Line Status is high
            {
                break;
            }
            else
            {
                WNCKR = 0x00;   // Delay 15.26 us
            }
        }
    }

	PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
	PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
	PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3

    PS2_IRQ_Channel = 0;        // Set PS2 0 service flag
	F_Service_PS2 = 1;          // Set main service flag
    PS2StartBit=0;			    // clear start bit flag
    PS2_SSIRQ_Channel = 0xFF;   //
	PS2PortxData[0]=PSDAT1;
    #else
	if(IS_MASK_SET(PSSTS1, TDS))    // Transaction done interrupt 
	{
        CLEAR_MASK(IER2,Int_PS2_0); // Disable PS2 interrupt 0
	    ISR2 = Int_PS2_0;           // Write to clear pending interrupt

        if(SendtoAUXFlag)
	    {
            for(PS2DataPinStatusCounter=0x00;PS2DataPinStatusCounter<5;PS2DataPinStatusCounter++)
            {
                if(IS_MASK_SET(PSSTS1, DLS))   // DATA Line Status is high
                {
                    break;
                }
                else
                {
                    WNCKR = 0x00;   // Delay 15.26 us
                }
            }
        }
        else
        {
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
            //WNCKR = 0x00;           // Delay 15.26 us
        }
        
		PSCTL1 = PS2_InhibitMode;   // Inhibit clock pin1
		PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
		PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3

	    PS2_IRQ_Channel = 0;        // Set PS2 0 service flag
		F_Service_PS2 = 1;          // Set main service flag
	    PS2StartBit=0;			    // clear start bit flag
	    PS2_SSIRQ_Channel = 0xFF;   //
		PS2PortxData[0]=PSDAT1;
	}
    else						    // Start bit interrupt 
    {
        PSCTL2 = PS2_InhibitMode;   // Inhibit clock pin2
        PSCTL3 = PS2_InhibitMode;   // Inhibit clock pin3
        IER2&= ~(Int_PS2_0+Int_PS2_1+Int_PS2_2);    // Disable all PS2 interrupt
        ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
        PS2StartBit = 1;		    // Set start bit flag
        PS2_SSIRQ_Channel = 0;      //
        SET_MASK(IER2,Int_PS2_0);   // Enable PS2 interrupt 0
    }	
    #endif
    Hook_IRQ_INT20_PS2Interrupt0();
}

//----------------------------------------------------------------------------
// WKO[22]
//----------------------------------------------------------------------------
void IRQ_INT21_WKO22(void)
{
    Hook_IRQ_INT21_WKO22();
}

//----------------------------------------------------------------------------
// SMFI Semaphore Interrupt
//----------------------------------------------------------------------------
void IRQ_INT22_SMFISemaphore(void)
{
    Hook_IRQ_INT22_SMFISemaphore();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT23_Null(void)
{
    Hook_IRQ_INT23_Null();
}

//----------------------------------------------------------------------------
// KBC Input Buffer Full Interrupt
//----------------------------------------------------------------------------
void IRQ_INT24_KBCIBF(void)
{
	IrqLock_scan();
	CLEAR_MASK(IER3,Int_KBCIBF);
    ISR3 = Int_KBCIBF;
    F_Service_PCI = 1;

    Hook_IRQ_INT24_KBCIBF();
}

//----------------------------------------------------------------------------
// PMC Input Buffer Full Interrupt PMC1 Input Buffer Full Interrupt
//----------------------------------------------------------------------------
void IRQ_INT25_PMCPMC1IBF(void)
{
	if(IS_MASK_SET(PM2STS, P_IBF))	// 68/6C input buffer full
	{
		F_Service_PCI3 = 1;
	}
	
	CLEAR_MASK(IER3,Int_PMCIBF);
    ISR3 = Int_PMCIBF;

    Hook_IRQ_INT25_PMCPMC1IBF();
}

//----------------------------------------------------------------------------
// PMC2 Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void IRQ_INT26_PMC2OBE(void)
{
    Hook_IRQ_INT26_PMC2OBE();
}

//----------------------------------------------------------------------------
// PMC2 Input Buffer Full Intr.
//----------------------------------------------------------------------------
void IRQ_INT27_PMC2IBF(void)
{
    Hook_IRQ_INT27_PMC2IBF();
}

//----------------------------------------------------------------------------
// GINT from function 1 of GPD5
//----------------------------------------------------------------------------
void IRQ_INT28_GINTofGPD5(void)
{
    Hook_IRQ_INT28_GINTofGPD5();
}

//----------------------------------------------------------------------------
// EGPC Interrupt
//----------------------------------------------------------------------------
void IRQ_INT29_EGPC(void)
{
    Hook_IRQ_INT29_EGPC();
}

//----------------------------------------------------------------------------
// External Timer 1 Interrupt
//----------------------------------------------------------------------------
void IRQ_INT30_ET1(void)
{
    Hook_IRQ_INT30_ET1();
}

//----------------------------------------------------------------------------
// WKO[21]
//----------------------------------------------------------------------------
void IRQ_INT31_WKO21(void)
{
    Hook_IRQ_INT31_WKO21();
}

//----------------------------------------------------------------------------
// GPINT0
//----------------------------------------------------------------------------
void IRQ_INT32_GPINT0(void)
{
    Hook_IRQ_INT32_GPINT0();
}

//----------------------------------------------------------------------------
// GPINT1
//----------------------------------------------------------------------------
void IRQ_INT33_GPINT1(void)
{
    Hook_IRQ_INT33_GPINT1();
}

//----------------------------------------------------------------------------
// GPINT2
//----------------------------------------------------------------------------
void IRQ_INT34_GPINT2(void)
{
    Hook_IRQ_INT34_GPINT2();
}

//----------------------------------------------------------------------------
// GPINT3
//----------------------------------------------------------------------------
void IRQ_INT35_GPINT3(void)
{
    Hook_IRQ_INT35_GPINT3();
}

//----------------------------------------------------------------------------
// CIR GPINT
//----------------------------------------------------------------------------
void IRQ_INT36_CIRGPINT(void)
{
    Hook_IRQ_INT36_CIRGPINT();
}

//----------------------------------------------------------------------------
// SSPI Interrupt
//----------------------------------------------------------------------------
void IRQ_INT37_SSPI(void)
{
    Hook_IRQ_INT37_SSPI();
}

//----------------------------------------------------------------------------
// UART1 Interrupt
//----------------------------------------------------------------------------
void IRQ_INT38_UART1(void)
{
    Hook_IRQ_INT38_UART1();
}

//----------------------------------------------------------------------------
// UART2 Interrupt
//----------------------------------------------------------------------------
void IRQ_INT39_UART2(void)
{
    Hook_IRQ_INT39_UART2();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT40_Null(void)
{
    Hook_IRQ_INT40_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT41_Null(void)
{
    Hook_IRQ_INT41_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT42_Null(void)
{
    Hook_IRQ_INT42_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT43_Null(void)
{
    Hook_IRQ_INT43_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT44_Null(void)
{
    Hook_IRQ_INT44_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT45_Null(void)
{
    Hook_IRQ_INT45_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT46_Null(void)
{
    Hook_IRQ_INT46_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT47_Null(void)
{
    Hook_IRQ_INT47_Null();
}

//----------------------------------------------------------------------------
// WKO[60]
//----------------------------------------------------------------------------
void IRQ_INT48_WKO60(void)
{
    Hook_IRQ_INT48_WKO60();
}

//----------------------------------------------------------------------------
// WKO[61]
//----------------------------------------------------------------------------
void IRQ_INT49_WKO61(void)
{
    Hook_IRQ_INT49_WKO61();
}

//----------------------------------------------------------------------------
//WKO[62]
//----------------------------------------------------------------------------
void IRQ_INT50_WKO62(void)
{
    Hook_IRQ_INT50_WKO62();
}

//----------------------------------------------------------------------------
// WKO[63]
//----------------------------------------------------------------------------
void IRQ_INT51_WKO63(void)
{
    Hook_IRQ_INT51_WKO63();
}

//----------------------------------------------------------------------------
// WKO[64]
//----------------------------------------------------------------------------
void IRQ_INT52_WKO64(void)
{
    Hook_IRQ_INT52_WKO64();
}

//----------------------------------------------------------------------------
// WKO[65]
//----------------------------------------------------------------------------
void IRQ_INT53_WKO65(void)
{
    Hook_IRQ_INT53_WKO65();
}

//----------------------------------------------------------------------------
// WKO[66]
//----------------------------------------------------------------------------
void IRQ_INT54_WKO66(void)
{
    Hook_IRQ_INT54_WKO66();
}

//----------------------------------------------------------------------------
// WKO[67]
//----------------------------------------------------------------------------
void IRQ_INT55_WKO67(void)
{
    Hook_IRQ_INT55_WKO67();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT56_Null(void)
{
    Hook_IRQ_INT56_Null();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT57_Null(void)
{
    Hook_IRQ_INT57_Null();
}

//----------------------------------------------------------------------------
// External Timer 2 Interrupt
//----------------------------------------------------------------------------
void IRQ_INT58_ET2(void)
{
    Hook_IRQ_INT58_ET2();
}

//----------------------------------------------------------------------------
// Deferred SPI Instruction Interrupt
//----------------------------------------------------------------------------
void IRQ_INT59_DeferredSPIInstruction(void)
{
    Hook_IRQ_INT59_DeferredSPIInstruction();
}

//----------------------------------------------------------------------------
// TMRINTA0
//----------------------------------------------------------------------------
void IRQ_INT60_TMRINTA0(void)
{
    Hook_IRQ_INT60_TMRINTA0();
}

//----------------------------------------------------------------------------
// TMRINTA1
//----------------------------------------------------------------------------
void IRQ_INT61_TMRINTA1(void)
{
    Hook_IRQ_INT61_TMRINTA1();
}

//----------------------------------------------------------------------------
// TMRINTB0
//----------------------------------------------------------------------------
void IRQ_INT62_TMRINTB0(void)
{
    Hook_IRQ_INT62_TMRINTB0();
}

//----------------------------------------------------------------------------
// TMRINTB1
//----------------------------------------------------------------------------
void IRQ_INT63_TMRINTB1(void)
{
    Hook_IRQ_INT63_TMRINTB1();
}

//----------------------------------------------------------------------------
// PMC2EX Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void IRQ_INT64_PMC2EXOBE(void)
{
    Hook_IRQ_INT64_PMC2EXOBE();
}

//----------------------------------------------------------------------------
// PMC2EX Input Buffer Full Intr.
//----------------------------------------------------------------------------
void IRQ_INT65_PMC2EXIBF(void)
{
    Hook_IRQ_INT65_PMC2EXIBF();
}

//----------------------------------------------------------------------------
// PMC3 Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void IRQ_INT66_PMC3OBE(void)
{
    Hook_IRQ_INT66_PMC3OBE();
}

//----------------------------------------------------------------------------
// PMC3 Input Buffer Full Intr.
//----------------------------------------------------------------------------
void IRQ_INT67_PMC3IBF(void)
{
    Hook_IRQ_INT67_PMC3IBF();
}

//----------------------------------------------------------------------------
// PMC4 Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void IRQ_INT68_PMC4OBE(void)
{
    Hook_IRQ_INT68_PMC4OBE();
}

//----------------------------------------------------------------------------
// PMC4 Input Buffer Full Intr.
//----------------------------------------------------------------------------
void IRQ_INT69_PMC4IBF(void)
{
    CLEAR_MASK(IER8,Int_PMC4IBF);
    ISR8 = Int_PMC4IBF;
    F_Service_PCI5 = 1;
    Hook_IRQ_INT69_PMC4IBF();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void IRQ_INT70_Null(void)
{
    Hook_IRQ_INT70_Null();
}

//----------------------------------------------------------------------------
// I2BRAM Interrupt
//----------------------------------------------------------------------------
void IRQ_INT71_I2BRAM(void)
{
    Hook_IRQ_INT71_I2BRAM();
}

//----------------------------------------------------------------------------
// WKO[70]
//----------------------------------------------------------------------------
void IRQ_INT72_WKO70(void)
{
    Hook_IRQ_INT72_WKO70();
}

//----------------------------------------------------------------------------
// WKO[71]
//----------------------------------------------------------------------------
void IRQ_INT73_WKO71(void)
{
    Hook_IRQ_INT73_WKO71();
}

//----------------------------------------------------------------------------
// WKO[72]
//----------------------------------------------------------------------------
void IRQ_INT74_WKO72(void)
{
    Hook_IRQ_INT74_WKO72();
}

//----------------------------------------------------------------------------
// WKO[73]
//----------------------------------------------------------------------------
void IRQ_INT75_WKO73(void)
{
    Hook_IRQ_INT75_WKO73();
}

//----------------------------------------------------------------------------
// WKO[74]
//----------------------------------------------------------------------------
void IRQ_INT76_WKO74(void)
{
    Hook_IRQ_INT76_WKO74();
}

//----------------------------------------------------------------------------
// WKO[75]
//----------------------------------------------------------------------------
void IRQ_INT77_WKO75(void)
{
    Hook_IRQ_INT77_WKO75();
}

//----------------------------------------------------------------------------
// WKO[76]
//----------------------------------------------------------------------------
void IRQ_INT78_WKO76(void)
{
    Hook_IRQ_INT78_WKO76();
}

//----------------------------------------------------------------------------
// WKO[77]
//----------------------------------------------------------------------------
void IRQ_INT79_WKO77(void)
{
    Hook_IRQ_INT79_WKO77();
}

//----------------------------------------------------------------------------
// FUNCTION:   Isr_Int0
// ISR for INT0 (Key Scan Interrupt).
//----------------------------------------------------------------------------
void Isr_Int0(void) interrupt 0 using 2
{

}

//----------------------------------------------------------------------------
// Isr_Tmr0
// ISR for TF0 (Timer 0 Interrupt).  Timer 0 is the 1mS Timer (Timer A).
//----------------------------------------------------------------------------
/* ----------------------------------------------------------------------------
 * FUNCTION: Irq_Timer_A - Handle Timer A interrupts.
 *
 * Timer A has a time base of 1 mS.
 *
 * Input: On entry, "TIMER Timer_A" has the event(s) to handle. Valid Events:
 *     TMR_SCAN   -
 *     TMR_GENTMO - This timer is a timer that is used for timeout detection
 *                  of serial data transmissions to/from the auxiliary
 *                  keyboard/pointing devices.
 * ------------------------------------------------------------------------- */
void Isr_Tmr0(void) interrupt 1 using 2
{
    Load_Timer_A();
    F_Service_MS_1 = 1;   // Request 1 mS timer service.
}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Int1
 * ISR for INT1 (Interrupt Source A and B Interrupts).
 *
 * Interrupt Source A:  
 * ------------------------------------------------------------------------- */
const FUNCT_PTR_V_V code IRQ_Service[] = 
{
    IRQ_INT0_Null,                      //   INT0	Reserved
    IRQ_INT1_WKO20,                     //   INT1	WUC interrupt WUI0	
    IRQ_INT2_KBCOBE,                    //   INT2	KBC output buffer empty interrupt 
    IRQ_INT3_PMCPMC1OBE,                //   INT3	PMC output buffer empty interrupt 
    IRQ_INT4_SMBusD,                    //   INT4	SMBus D Interrupt
    IRQ_INT5_WKINTAD,                   //   INT5	WUC interrupt (WU10 ~ WU15)(WU40 ~ WU47)	
    IRQ_INT6_WKO23,                     //   INT6	WUC interrupt WUI3
    IRQ_INT7_PWM,                       //   INT7	PWM interrupt 
    
    IRQ_INT8_ADC,    		            //   INT8  	ADC Interrupt 	
    IRQ_INT9_SMBusA,      		        //   INT9  	SMB0 Interrupt 
    IRQ_INT10_SMBusB,       	        //   INT10 	SMB1 Interrupt
    IRQ_INT11_KBMatrixScan,     	    //   INT11 	Key matrix scan Int
    IRQ_INT12_WKO26,                    //   INT12	WUC interrupt SWUC wake up
    IRQ_INT13_WKINTC,                   //   INT13	WUC interrupt KSI wake-up (WU30 ~ WU37)
    IRQ_INT14_WKO25,                    //   INT14	WUC interrupt Power switch
    IRQ_INT15_CIR,         	            //   INT15 	CIR interrupt 
    
    IRQ_INT16_SMBusC,       	        //   INT16	SMB2 Interrupt
    IRQ_INT17_WKO24,                    //   INT17	WUC Interrupt WUI4
    IRQ_INT18_PS2Interrupt2,    	    //   INT18 	PS2 P2 Interrupt
    IRQ_INT19_PS2Interrupt1,     	    //   INT19 	PS2 P1 Interrupt
    IRQ_INT20_PS2Interrupt0,   	        //   INT20 	PS2 P0 Interrupt
    IRQ_INT21_WKO22,                    //   INT21	WUC Interrupt WUI2
    IRQ_INT22_SMFISemaphore,            //   INT22  SMFI Semaphore Interrupt
    IRQ_INT23_Null,                     //   INT23  --
    
    IRQ_INT24_KBCIBF,       	        //   INT24 	KBC input buffer full interrupt 
    IRQ_INT25_PMCPMC1IBF,       	    //   INT25 	PMC input buffer full interrupt 
    IRQ_INT26_PMC2OBE,                  //   INT26   PMC2 Output Buffer Empty Intr.
    IRQ_INT27_PMC2IBF,                  //   INT27   PMC2 Input Buffer Full Intr.
    IRQ_INT28_GINTofGPD5,               //   INT28   GINT from function 1 of GPD5
    IRQ_INT29_EGPC,                     //   INT29   EGPC Interrupt
    IRQ_INT30_ET1,                      //   INT30   External timer interrupt 
    IRQ_INT31_WKO21,                    //   INT31   WUC	interrupt WUI1
    
    IRQ_INT32_GPINT0,       		    //   INT32  GPINT0	
    IRQ_INT33_GPINT1,       		    //   INT33  GPINT1	    
    IRQ_INT34_GPINT2,                   //   INT34  GPINT2
    IRQ_INT35_GPINT3,                   //   INT35  GPINT3
    IRQ_INT36_CIRGPINT,                 //   INT36  CIR GPINT
    IRQ_INT37_SSPI,                     //   INT37  SSPI Interrupt
    IRQ_INT38_UART1,                    //   INT38  UART1 Interrupt
    IRQ_INT39_UART2,                    //   INT39  UART2 Interrupt
    
    IRQ_INT40_Null,       		        //   INT40 	--
    IRQ_INT41_Null,       		        //   INT41 	--
    IRQ_INT42_Null,                     //   INT42  --
    IRQ_INT43_Null,                     //   INT43  --
    IRQ_INT44_Null,                     //   INT44  --
    IRQ_INT45_Null,                     //   INT45  --
    IRQ_INT46_Null,                     //   INT46	--
    IRQ_INT47_Null,                     //   INT47	--
    
    IRQ_INT48_WKO60,       	            //   INT48  WKO[60]	
    IRQ_INT49_WKO61,       		        //   INT49  WKO[61] 	
    IRQ_INT50_WKO62,                    //   INT50  WKO[62]
    IRQ_INT51_WKO63,                    //   INT51  WKO[63]
    IRQ_INT52_WKO64,                    //   INT52  WKO[64]
    IRQ_INT53_WKO65,                    //   INT53  WKO[65]
    IRQ_INT54_WKO66,                    //   INT54  WKO[66]	
    IRQ_INT55_WKO67,                    //   INT55  WKO[67]    

    IRQ_INT56_Null,       		        //   INT56  -- 	
    IRQ_INT57_Null,                     //   INT57  --
    IRQ_INT58_ET2,                      //   INT58  External Timer 2 Interrupt
    IRQ_INT59_DeferredSPIInstruction,   //   INT59  Deferred SPI Instruction Interrupt      
    IRQ_INT60_TMRINTA0,                 //   INT60  TMRINTA0
    IRQ_INT61_TMRINTA1,                 //   INT61  TMRINTA1
    IRQ_INT62_TMRINTB0,                 //   INT62  TMRINTB0  
	IRQ_INT63_TMRINTB1,                 //   INT63  TMRINTB1

    IRQ_INT64_PMC2EXOBE,       		    //   INT64  PMC2EX Output Buffer Empty Intr.
    IRQ_INT65_PMC2EXIBF,       		    //   INT65  PMC2EX Input Buffer Full Intr.
    IRQ_INT66_PMC3OBE,                  //   INT66  PMC3 Output Buffer Empty Intr.
    IRQ_INT67_PMC3IBF,                  //   INT67  PMC3 Input Buffer Full Intr.
    IRQ_INT68_PMC4OBE,                  //   INT68  PMC4 Output Buffer Empty Intr.
    IRQ_INT69_PMC4IBF,                  //   INT69  PMC4 Input Buffer Full Intr.
    IRQ_INT70_Null,                     //   INT70  --
    IRQ_INT71_I2BRAM,                   //   INT71  I2BRAM Interrupt

    IRQ_INT72_WKO70,       	            //   INT72  WKO[70]	
    IRQ_INT73_WKO71,       		        //   INT73  WKO[71] 	
    IRQ_INT74_WKO72,                    //   INT74  WKO[72]
    IRQ_INT75_WKO73,                    //   INT75  WKO[73]
    IRQ_INT76_WKO74,                    //   INT76  WKO[74]
    IRQ_INT77_WKO75,                    //   INT77  WKO[75]
    IRQ_INT78_WKO76,                    //   INT78  WKO[76]	
    IRQ_INT79_WKO77,                    //   INT79  WKO[77]   
};
							
void Isr_Int1 (void) interrupt 2 using 2
{
    if(OEM_Isr_Int1_Request)
    {
        Hook_OEM_Isr_Int1();
    }
    else
    {
        if(IVECT==PS2Interrupt2)            // PS/2 Interrupt 2
        {
            IRQ_INT18_PS2Interrupt2();
        }
        else if(IVECT==PS2Interrupt1)       // PS/2 Interrupt 1
        {
            IRQ_INT19_PS2Interrupt1();
        }
        else if(IVECT==PS2Interrupt0)       // PS/2 Interrupt 0
        {
            IRQ_INT20_PS2Interrupt0();
        }
        else
        {
            (IRQ_Service[(IVECT-0x10)&0x7F])();   // Dispatch to service handler.
        }
    }
} 
    
/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Tmr1
 * ISR for TF1 (Timer 1 Interrupt).  Timer 1 is the 2ms Timer (Timer B).
 * ------------------------------------------------------------------------- */
void Isr_Tmr1(void) interrupt 3 using 2
{
	Stop_Timer_B();
	if ( Timer_B.fbit.SEND_ENABLE )  
 	{   
   		F_Service_SEND = 1;     		// Post service request.
     	Timer_B.fbit.SEND_ENABLE = 0;
		Load_Timer_B();
	}
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_UART
 * ISR for TI or RI (UART Interrupt).
 * ------------------------------------------------------------------------- */
void Isr_UART(void) interrupt 4 using 2
{

}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Isr_Tmr2
 * ISR for TF2 or EXF2 (Timer 2 Interrupt).
 * ------------------------------------------------------------------------- */
void Isr_Tmr2(void) interrupt 5 using 2
{

}

//------------------------------------------------------------------------------
// The function of disable all interrupts
//------------------------------------------------------------------------------
void DisableAllInterrupt(void)
{
  	EA = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

//------------------------------------------------------------------------------
// The function of enable all interrupts
//------------------------------------------------------------------------------
void EnableAllInterrupt(void)
{
  	EA = 1;
}

//------------------------------------------------------------------------------
// The function of enabling KBC Input Buffer Full (60 64 port)Interrupt 
//------------------------------------------------------------------------------
void EnableKBCIBFInt(void)
{
    SET_MASK(IER3,Int_KBCIBF);
}

//------------------------------------------------------------------------------
// The function of enabling PMC Input Buffer Full (62 66 68 6C port)Interrupt 
//------------------------------------------------------------------------------
void EnablePMCIBFInt(void)
{
	SET_MASK(IER3,Int_PMCIBF);	
}

//------------------------------------------------------------------------------
// The function of enabling PMC Input Buffer Full (74/78 port)Interrupt 
//------------------------------------------------------------------------------
void EnablePMC4IBFInt(void)
{
	SET_MASK(IER8,Int_PMC4IBF);	
}


//----------------------------------------------------------------------------
// The function of enabling interrupts
//----------------------------------------------------------------------------
void InitEnableInterrupt(void)
{
	ISR0 = 0xFF;
	ISR1 = 0xFF;
	ISR2 = 0xFF;
	ISR3 = 0xFF;
	ISR4 = 0xFF;
    ISR5 = 0xFF;
	ISR6 = 0xFF;
    ISR7 = 0xFF;
    ISR8 = 0xFF;
    ISR9 = 0xFF;
	ISR13 = 0xFF;

	EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();
}

//----------------------------------------------------------------------------
// The function of enabling module interrupt
//----------------------------------------------------------------------------
void EnableModuleInterrupt(void)
{
  	EnableAllInterrupt();   // enable all interrupts
    EnableKBCIBFInt();      // Enable 60/64 port input buffer full interrupt
  	EnablePMCIBFInt();      // Enable PMC Input Buffer Full (62 66 68 6C port)Interrupt
  	Hook_EnableInterrupt();
}


