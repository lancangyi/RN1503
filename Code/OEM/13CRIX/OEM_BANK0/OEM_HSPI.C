/*-----------------------------------------------------------------------------
 * TITLE: CORE_HSPI.C
 *
 * Copyright (c) 2009- , ITE Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Disable HSPI interface pins 
//----------------------------------------------------------------------------
void GPIO_HSPI_INIT(void)
{
	GPCRH3 = INPUT;                 // Set input mode
	GPCRH4 = INPUT;                 // Set input mode
	GPCRH5 = INPUT;                 // Set input mode
	GPCRH6 = INPUT;                 // Set input mode
    SET_MASK(RSTC4,RSPI);           // Reset SPI
}

//----------------------------------------------------------------------------
// Enable HSPI interface
//----------------------------------------------------------------------------
void Enable_HSPI(void)
{
    #ifdef HSPI_DefferingMode
    CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    #endif
    
	GPCRH3 = ALT;                   // Set HSPI mode
	GPCRH4 = ALT;                   // Set HSPI mode
	GPCRH5 = ALT;                   // Set HSPI mode
	GPCRH6 = ALT;                   // Set HSPI mode

    #ifdef HSPI_DefferingMode
    HINSTC1 = (ENDPI+ENDEI);        // Host Instruction Control 1 
    #else
    HINSTC1 = 0x00;
    #endif
    
    HSPICTRL3R = 0x10;			    // set bit4 for not SST SPI ROM
								    // clear bit4 for SST SPI ROM or set bit4 for not SST SPI ROM
                           		    // For phoenix bios 
	//FLHCTRL1R = 0x00;			    // Flash Control Register 1
	HCTRL2R = 0x10;				    // Host Control 2 Register

    #ifdef HSPI_DefferingMode
    //ISR7 = Int_DeferredSPI;       // W/C interrupt status
    SET_MASK(IER7,Int_DeferredSPI); // Enable interrupt 
    #endif
}

//----------------------------------------------------------------------------
// Disable HSPI interface
//----------------------------------------------------------------------------
void Disable_HSPI(void)
{
    #ifdef HSPI_DefferingMode
    CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    //HCTRL2R = 0x80;
    #endif

    HCTRL2R=0x00;

	GPCRH3 = INPUT;                 // Set input mode
	GPCRH4 = INPUT;                 // Set input mode
	GPCRH5 = INPUT;                 // Set input mode
	GPCRH6 = INPUT;                 // Set input mode
    SET_MASK(RSTC4,RSPI);           // Reset SPI
}

#pragma ot(8, SPEED)
//----------------------------------------------------------------------------
// Instructino is valid
//----------------------------------------------------------------------------
void HSPI_RamCode(void)
{
    HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
    //HINSTC1 = (DISSV+DISS);         // Allow instruction
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    
    HSPI_FPT_timeout = 0x00;
    TR0 = 0;                        // Disable timer 0
    ET0 = 0;			            // Disable timer0 interrupt
    TH0 = T_HSPI_ISRTime>>8;	    // set timer0 counter xx ms 
    TL0 = T_HSPI_ISRTime;		    // set timer0 counter xx ms
    TF0 = 0;			            // clear overflow flag
    TR0 = 1;			            // enable timer0

    while(!TF0)                     // if isn't time out
    {
        if(IS_MASK_SET(ISR7, Int_DeferredSPI))  // Check HSPI isr
        {
            if(DSADR2==HSPI_ECCodeSpaceAddr)    // EC code space
            {
                HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
                //HINSTC1 = (DISSV+DISS);         // Allow instruction
                ISR7 = Int_DeferredSPI;         // W/C interrupt status
                    
                TH0 = T_HSPI_ISRTime>>8;	    // set timer1 counter xx ms 
                TL0 = T_HSPI_ISRTime;	        // set timer1 counter xx ms
                TF0 = 0;			            // clear overflow flag

                while(1)
                {
                    if(IS_MASK_SET(ISR7, Int_DeferredSPI))
                    {
                        HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
                        //HINSTC1 = (DISSV+DISS);     // Allow instruction
                        ISR7 = Int_DeferredSPI;     // W/C interrupt status
                            
                        TH0 = T_HSPI_ISRTime>>8;    // set timer1 counter xx ms 
                        TL0 = T_HSPI_ISRTime;	    // set timer1 counter xx ms
                        TF0 = 0; 
                        HSPI_FPT_timeout = 0x00;
                        continue;
                    }

                    if(TF0)
                    {
                        if(++HSPI_FPT_timeout>=35)     // 3 sec EC auto wake up from ram code.
                        {
                            HSPI_FPT_timeout=0xFF;
                            break;
                        }
                        TH0 = T_HSPI_ISRTime>>8;	    // set timer1 counter xx ms 
                        TL0 = T_HSPI_ISRTime;		    // set timer1 counter xx ms
                        TF0 = 0;			            // clear overflow flag
                    }
                }
                
                WinFlashMark = 0x33;
                TR0 = 0;			    // disable timer1
 	            TF0 = 0;			    // clear overflow flag
	            ET0 = 1;			    // Enable timer1 interrupt
	            
	            MainFucnLow = 0x00;     // Set main function low return vector
                MainFucnHigh= 0x02;     // Set main function high return vector
	            #pragma asm
                CLR     PSW.3
                CLR     PSW.4           // IRam bank 0
                PUSH    05EH            // Push main function low return vector
                PUSH    05FH            // Push main function high return vector       
                RETI                    // Return to main function 0x200 
                #pragma endasm
            }
            
            HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
            //HINSTC1 = (DISSV+DISS);         // Allow instruction
            ISR7 = Int_DeferredSPI;     // W/C interrupt status
                
            TH0 = T_HSPI_ISRTime>>8;    // set timer1 counter xx ms 
            TL0 = T_HSPI_ISRTime;	    // set timer1 counter xx ms
            TF0 = 0;
        }
    }
    
    TR0 = 0;			    // disable timer1
    TF0 = 0;			    // clear overflow flag
    ET0 = 1;			    // Enable timer1 interrupt 

    TL0 = Timer_1ms;      	// Reload timer
	TH0 = Timer_1ms>>8;	    // 1ms
    TR0 = 1;                // Start timer0 running
    ET0 = 1;				// Enable timer0 interrupt
    F_Service_MS_1 = 1;     // Request 1 mS timer service.
}

#pragma ot(8, SPEED)
//----------------------------------------------------------------------------
// Host send idle command to EC
//----------------------------------------------------------------------------
void HSPI_CmdRamCode(void)
{
	RamcodeCmd = 0x00;

	if(RamCodePort==0x64)
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
    
 	while(1)
  	{
        #ifdef HSPI_DefferingMode
        if(IS_MASK_SET(ISR7, Int_DeferredSPI))
        {
            HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
            //HINSTC1 = (DISSV+DISS);           // Allow instruction
            ISR7 = Int_DeferredSPI;             // W/C interrupt status
        }
        #endif
        
  		if(RamCodePort==0x64)
		{
			if( IS_MASK_CLEAR(KBHISR,IBF)) continue;
        	if( IS_MASK_CLEAR(KBHISR,C_D)) 
        	{
                RamcodeCmd = KBHIDIR;
                continue;
        	}
            else
            {
       		    RamcodeCmd = KBHIDIR;
            }
  		}
		else if(RamCodePort==0x66)
		{
        	if ( IS_MASK_CLEAR(PM1STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM1STS,P_C_D)) 
            {
                RamcodeCmd = PM1DI;
                continue;
            }
            else
            {
        	    RamcodeCmd = PM1DI;
            }
		}		
		else if(RamCodePort==0x6C)
		{
        	if ( IS_MASK_CLEAR(PM2STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM2STS,P_C_D)) 
        	{
                RamcodeCmd = PM2DI;
                continue;
        	}
            else
            {
        	    RamcodeCmd = PM2DI;
            }
		}	
		
        if ( RamcodeCmd == 0x55)
     	{
     		WinFlashMark = 0x33;
        	break;
  		}
		else if ( RamcodeCmd == 0xAF)
     	{
            //#ifdef HSPI_DefferingMode
            //HCTRL2R = 0x80;	
            HCTRL2R=0x00;
            CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
            ISR7 =Int_DeferredSPI;  // W/C interrupt status
	        GPCRH3 = INPUT;         // Set input mode
	        GPCRH4 = INPUT;         // Set input mode
	        GPCRH5 = INPUT;         // Set input mode
	        GPCRH6 = INPUT;         // Set input mode
            SET_MASK(RSTC4,RSPI);   // Reset SPI
            //#endif
            
			WDTRST = 1;			// Reset watch dog timer
			WDTEB = 1;			// Enable watch dog
       		while(1);			// Wait for watch dog time-out
        }
	}

	_nop_();

	GPCRH0 = ALT;

    #pragma asm
    EXTRN CODE (main)
    LJMP    main
    #pragma endasm

}

//-----------------------------------------------------------------------------
// Changing PLL frequency function
//-----------------------------------------------------------------------------
void ChangePLLFrequency(BYTE newseting)
{
    if(newseting!=PLLFREQR)
    {
        PLLFREQR = newseting;
        PLLCTRL = 1;
        DisableAllInterrupt();  
	    PCON =2 ;             	// enter sleep mode
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();	
    }
}

//-----------------------------------------------------------------------------
// Changing SPI flash read mode
//-----------------------------------------------------------------------------
void ChangeSPIFlashReadMode(BYTE Mode)
{
    XBYTE restore;
    restore = FLHCTRL1R;
    CLEAR_MASK(restore, SPIFR0+SPIFR1);
    
    switch(Mode)
    {
        case SPIReadMode_0:
            break;
            
        case SPIReadMode_1:
            SET_MASK(restore, SPIFR0);
            break;  
            
        case SPIReadMode_2:
            SET_MASK(restore, SPIFR1);
            break;
            
        case SPIReadMode_3:
            SET_MASK(restore, SPIFR0+SPIFR1);
            break;
            
        default:
            break;
    }
    FLHCTRL1R = restore;
}

//-----------------------------------------------------------------------------
// Changing HSPI requestmode
//-----------------------------------------------------------------------------
void ChangeHSRSMode(BYTE Mode)
{
    XBYTE restore;

    restore=0x00;
    
    switch(Mode)
    {
        case HSPI_RequestSelection_0:
            break;
            
        case HSPI_RequestSelection_1:
            SET_MASK(restore, BIT3);
            break;  
            
        case HSPI_RequestSelection_2:
            SET_MASK(restore, BIT4);
            break;
            
        case HSPI_RequestSelection_3:
            SET_MASK(restore, BIT3+BIT4);
            break;
            
        default:
            break;
    }
    
    HSPICTRL2R = restore+BIT2;
}