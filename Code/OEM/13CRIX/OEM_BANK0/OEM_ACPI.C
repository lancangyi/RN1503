/*-----------------------------------------------------------------------------
 * TITLE: OEM_ACPI.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Handle OEM ACPI command
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Handle OEM ACPI command 8x.
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_80(void)
{
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))  // ACPI mode
    {
        if(IS_MASK_CLEAR(PM1STS,BURST)) // Non-burst mode
        {
            ECCheckBurstMode = 1;
        }
    }
}

void OEM_ACPI_Cmd_81(void)
{
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))  // ACPI mode
    {
        if(IS_MASK_CLEAR(PM1STS,BURST)) // Non-burst mode
        {
            ECCheckBurstMode = 1;
        }
  	}
}

void OEM_ACPI_Cmd_82(void)
{
    ECCheckBurstMode = 1;
}

void OEM_ACPI_Cmd_83(void)
{
    ECCheckBurstMode = 0;
}

void OEM_ACPI_Cmd_84(void)
{
	ITempB05 = 0x00;
	if (SCI_Event_Out_Index != SCI_Event_In_Index)
	{  
		ITempB05 = SCI_Event_Buffer[SCI_Event_Out_Index];
    	SCI_Event_Out_Index++;
    	if (SCI_Event_Out_Index >= EVENT_BUFFER_SIZE) 
		{
           	SCI_Event_Out_Index = 0;
   		}
		
   		if (SCI_Event_Out_Index == SCI_Event_In_Index)
   		{
         	CLEAR_MASK(PM1STS,SCIEVT);
   		}
		
		SendFromAcpi(ITempB05);
	}
	else
	{
		CLEAR_MASK(PM1STS,SCIEVT);
	}
}

void OEM_ACPI_Cmd_86(void)
{
    SET_MASK(SYS_MISC1,ACPI_OS);
}

void OEM_ACPI_Cmd_87(void)
{
    CLEAR_MASK(SYS_MISC1,ACPI_OS);
}

void OEM_ACPI_Cmd_8E(void)
{
	SET_MASK(UtilityFlag, SMBusDebug);
}
void OEM_ACPI_Cmd_8F(void)
{
	CLEAR_MASK(UtilityFlag, SMBusDebug);
}

//----------------------------------------------------------------------------
// Handle OEM ACPI command Dx.
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_D8(void)
{

  RamProgram(0X66);
}

void OEM_ACPI_Cmd_DD(void)
{
	RamProgram(0X66);
}


//----------------------------------------------------------------------------
// The hook function of 62 port data
//  Note : 
//  PM1Step != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_62Port(BYTE PM1Data)
{
    switch(PM1Data)
    {

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// The hook function of 66 port command.
//----------------------------------------------------------------------------
void Hook_66Port(BYTE PM1Cmd)
{
    switch(PM1Cmd)
    {
        case 0x80:
        OEM_ACPI_Cmd_80();
        break;

        case 0x81:
        OEM_ACPI_Cmd_81();
        break;

        case 0x82:
        OEM_ACPI_Cmd_82();
        break;

        case 0x83:
        OEM_ACPI_Cmd_83();
        break;

        case 0x84:
        OEM_ACPI_Cmd_84();
        break;

        case 0x86:
        OEM_ACPI_Cmd_86();
        break;

        case 0x87:
        OEM_ACPI_Cmd_87();
        break;

        case 0x8E:
        OEM_ACPI_Cmd_8E();
        break;

        case 0x8F:
        OEM_ACPI_Cmd_8F();
        break;

        case 0xD8:
        OEM_ACPI_Cmd_D8();
        break;

        case 0xDD:
        OEM_ACPI_Cmd_DD();
        break;

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// Hook function of ACPI command
//----------------------------------------------------------------------------
void Hook_ACPICommand(void)
{
#if ACPI_Smbus
	OSSMbusComd();		// ACPI SMBus command
#endif	
}

//-------------------------------------------------------------------------------
// parameter "QeventSCI" only, For a pulsed SCI
//------------------------------------------------------------------------------
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void ResetSCIEvent(void)
{
    SCI_Event_In_Index = 0;
    SCI_Event_Out_Index = 0;

    #if ACPI_QEventPending
    PD_SCI_Event_In_Index = 0;
    PD_SCI_Event_Out_Index = 0;
    #endif
    
    CLEAR_MASK(PM1STS,SCIEVT);

    ECCheckBurstMode = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
void ECQEvent(BYTE sci_number, BYTE sci_mode)
{

	 if(IS_MASK_CLEAR(SYS_MISC1,ACPI_OS))
	 {
	 	return;
	 }
	 
    #if ACPI_QEventPending
    if((sci_mode == SCIMode_Normal)||(sci_mode == SCIMode_Pending))
    {
        if(sci_mode == SCIMode_Normal)
        {
            if(PD_SCI_Event_In_Index!=PD_SCI_Event_Out_Index)
            {
                PendingECQEvent(sci_number);
                return;
            }
        }
    
        if(IS_MASK_SET(PM1STS,P_IBF)||IS_MASK_SET(KBHISR, IBF))
        {
            if(sci_mode == SCIMode_Pending)
            {
                if(PD_SCI_Event_Out_Index==0x00)
                {
                    PD_SCI_Event_Out_Index = PENDING_BUFFER-1;
                }
                else
                {
                    PD_SCI_Event_Out_Index--;
                }
            }
            else
            {
                PendingECQEvent(sci_number);
            }
            return;
        } 
    }
    #endif
    
	ITempB05 = SCI_Event_In_Index; 				// Get the input index.
	SCI_Event_Buffer[ITempB05] = sci_number; 	// Put the SCI number in the buffer.
 	ITempB05++;    								// Increment the index. 
 	if (ITempB05 >= EVENT_BUFFER_SIZE) 
	{
     	ITempB05 = 0;
 	}
 											// If the buffer is not full, update the input index.
  	if (ITempB05 != SCI_Event_Out_Index) 
	{
   		SCI_Event_In_Index = ITempB05;
    }
    
	SET_MASK(PM1STS,SCIEVT);
    OEM_ACPI_Gen_Int();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PendingECQEvent(BYTE sci_number)
{
    BYTE index;
    
    #if ACPI_QEventPending
    
	index = PD_SCI_Event_In_Index; 			    // Get the input index.
	PD_SCI_Event_Buffer[index] = sci_number;    // Put the SCI number in the buffer.
 	index++;    							    // Increment the index. 
 	if(index >= PENDING_BUFFER) 
	{
     	index = 0;
 	}
 											    // If the buffer is not full, update the input index.
  	if(index != PD_SCI_Event_Out_Index) 
	{
   		PD_SCI_Event_In_Index = index;
    }
    #endif
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Get_PendingECQEvent(void)

{
    BYTE sci_number;
    
    #if ACPI_QEventPending
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
	    if (PD_SCI_Event_Out_Index != PD_SCI_Event_In_Index)
	    {  
		    sci_number = PD_SCI_Event_Buffer[PD_SCI_Event_Out_Index];
    	    PD_SCI_Event_Out_Index++;
    	    if(PD_SCI_Event_Out_Index >= PENDING_BUFFER) 
		    {
           	    PD_SCI_Event_Out_Index = 0;
   		    }

            ECQEvent(sci_number, SCIMode_Pending);
	    }
    }
    #endif
}

//----------------------------------------------------------------------------
// Read EC ram Space 
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
	Tmp_XPntr=(ECRAM|MapIndex);
	return(*Tmp_XPntr);	
}

void SpecialFunc_01(void)
{

}

//----------------------------------------------------------------------------
// Do hook function when write EC ram Space 
//----------------------------------------------------------------------------
const sECRamSS code asECRamSS[] = 
{	
    {&MISC_FLAG1,    SpecialFunc_01		},		
};

void WriteECRamSpecialFunc(XBYTE *xdptr)        //81 EC write command
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(asECRamSS)/sizeof(sECRamSS)))
	{
		if(xdptr == asECRamSS[index].addr)
		{
			(asECRamSS[index].hookfunc)();
			break;
		}
		index++;
	}
}

//----------------------------------------------------------------------------
// Write EC ram Space 
//----------------------------------------------------------------------------
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
	Tmp_XPntr=(ECRAM|MapIndex);
	*Tmp_XPntr = data1;

#if HookFucnofWriteECRam
    WriteECRamSpecialFunc(Tmp_XPntr);
#endif	
}

#if ACPI_Smbus
//----------------------------------------------------------------------------
// process OS SMBus command
//----------------------------------------------------------------------------
// ACPI response to writes to SMBus Protocol register. 
const FUNCT_PTR_B_V code vOSSMbusComd_table[16] =
{								//the low nibble of SMB_PRTC
	DummyFunction,		//0x00	
	DummyFunction,		//0x01
	DummyFunction,		//0x02-Write Quick Command 
	DummyFunction,		//0x03-Read Quick Command
	DummyFunction,		//0x04-Send Byte
	DummyFunction,		//0x05-Receive Byte
	vOSSMbusWBYTE,		//0x06-Write Byte
	vOSSMbusRByte,		//0x07-Read Byte
	vOSSMbusWWord,		//0x08-Write Word
	vOSSMbusRWord,		//0x09-Read Word
	vOSSMbusWBlcok,		//0x0A-Write Block
	vOSSMbusRBlcok,		//0x0B-Read Block
	DummyFunction,		//0x0C-Process Call
	DummyFunction,		//0x0D-Write Block-Read Block Process Call
	DummyFunction,		//0x0E
	DummyFunction		//0x0F
};

void OSSMbusComd(void)
{//	60 protocol,	61 status,		62 address,	63 command
	if(SMB_PRTC != 0x00)
	{
  		SMB_STS = 0x00;
     	SMB_PRTC &= 0x0F;
      	if((vOSSMbusComd_table[SMB_PRTC])())
      	{
     		SMB_STS = 0x80;
      	}
		else
		{
			SMB_STS = 0x5A;
		}
      	SMB_PRTC = 0x00;
  	}
}

BYTE vOSSMbusWBlcok(void)
{
  	return (bWSMBusBlock(SMbusCh1, SMbusWBK, SMB_ADDR, SMB_CMD, &SMB_DATA,SMB_BCNT,1));
}

BYTE vOSSMbusRBlcok(void)
{
  	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRByte(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusRWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusWBYTE(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

BYTE vOSSMbusWWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

void DummyFunction(void)
{

}
#endif


#if Lenovo_Support
void Lenovo_PM_Cmd(void)
{
	switch(VCMD_Lenovo)
	{	
	case 0x10 :  //-----------------------------------read VPC  
		VDAT_Lenovo = VPC_Lenovo;
		VPC_Lenovo = 0x00;
		break;
		
	case 0x11 :	 //-----------------------------------read Brightness max level 
		if(OS_Type==3)
		{
			VDAT_Lenovo = MAX_LEVEL_linux;
		}
		else
		{
			VDAT_Lenovo = MAX_LEVEL; 
		}
		break;
		
	case 0x12 :	 //-----------------------------------read  Current  brightness level
		if(IS_MASK_SET(Oem_Globe_Flag,Brightness_Up_Pressed))
		{
			CLEAR_MASK(Oem_Globe_Flag,Brightness_Up_Pressed);
			CLEAR_MASK(Oem_Globe_Flag,Brightness_Down_Pressed);
		}
		else if(IS_MASK_SET(Oem_Globe_Flag,Brightness_Down_Pressed))
		{
			CLEAR_MASK(Oem_Globe_Flag,Brightness_Down_Pressed);
			CLEAR_MASK(Oem_Globe_Flag,Brightness_Up_Pressed);
		}
		VDAT_Lenovo = LCD_BRIGHTNESS;
		break;
		
	case 0x13 :	//------------------------------------write Current  brightness level
		LCD_BRIGHTNESS = VDAT_Lenovo;
		Setup_Brightness(LCD_BRIGHTNESS);
		break;

	case 0x14 :	//------------------------------------read Wireless Status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,Wireless_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x15 :	//------------------------------------set Wireless Status
		if(0 == VDAT_Lenovo) //------------------------turn off wifi
		{
			CLEAR_MASK(Device_Status_Lenovo,Wireless_S_B);
		}
		else				 //------------------------turn on wifi
		{
			SET_MASK(Device_Status_Lenovo,Wireless_S_B);
		}
		TurnOnOffWlan();
		break;
		
	case 0x16 :	//------------------------------------read Bluetooth status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,Bluetooth_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;

	case 0x17 :	//------------------------------------set Bluetooth Status
		if(0 == VDAT_Lenovo)  //----------------------- turn off 
		{
			CLEAR_MASK(Device_Status_Lenovo,Bluetooth_S_B);
		}
		else                  // ----------------------- turn on
		{
			SET_MASK(Device_Status_Lenovo,Bluetooth_S_B);
		}
		TurnOnOffBT();
		break;
		
	case 0x18 :	//-------------------------------------read Inverter Status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,Inverter_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x19 :	//-------------------------------------read Novo Button Status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,Novo_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x1A :	//-------------------------------------Query VPC2
		VDAT_Lenovo = VPC2_Lenovo;
		VPC2_Lenovo = 0x00;
		break;
		
	case 0x1B :	//-------------------------------------Read Touch Pad Status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,TouchPad_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x1C :	//-------------------------------------Set Touch Pad
		if(0 == VDAT_Lenovo)
		{
			CLEAR_MASK(Device_Status_Lenovo,TouchPad_S_B);
		}
		else
		{
			SET_MASK(Device_Status_Lenovo,TouchPad_S_B);
		}
		break;
				
	case 0x1D :	//-------------------------------------read Camera
		if(IS_MASK_CLEAR(Device_Status_Lenovo,Camera_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x1E :	//-------------------------------------Set Camera
		if(0 == VDAT_Lenovo)
		{
			CLEAR_MASK(Device_Status_Lenovo,Camera_S_B);
		}
		else
		{
			SET_MASK(Device_Status_Lenovo,Camera_S_B);
		}
		break;
		
	case 0x1F :	//-------------------------------------Read 3G RF Status
		if(IS_MASK_CLEAR(Device_Status_Lenovo,RF3G_S_B))
		{
			VDAT_Lenovo = 0;
		}
		else
		{
			VDAT_Lenovo = 1;
		}
		break;
		
	case 0x20 :	//-------------------------------------Set RF 3G
		if(0 == VDAT_Lenovo) //------------------------turn off 3G
		{
			CLEAR_MASK(Device_Status_Lenovo,RF3G_S_B);
		}
		else				//------------------------turn on 3G
		{
			SET_MASK(Device_Status_Lenovo,RF3G_S_B);
		}
		//TurnOnOff3G();
		break;
		
	case 0x21 :
		break;
		
	case 0x22 :
		#if SmartFanSupport
		if(VDAT_Lenovo&BIT0)           			// start dust mode
		{
			GPUFanValue = MaxOutValue;
			DustTotleCont = 1200;                 // totle 2 min
			FanFullOnCont=80;
			SET_MASK(OEM_flag_1,Fan_Dust_OnOff_f); // dust mode on
			Lenvo_dust_mode=0x01;
		}
		else                                   // cancle dust mode
		{
			FanFullOnCont=0;
			DustTotleCont = 0; 
			CLEAR_MASK(OEM_flag_1,Fan_Dust_OnOff_f);
			Lenvo_dust_mode=0x02;
			
		}
		#endif
		break;
		
	case 0x23 :	//--------------------------------------read All RF Status
		VDAT_Lenovo = 1;
		break;	
		
	case 0x24 : //--------------------------------------set All AF Status
		break;
		
	case 0x25 :	
	case 0x26 :
	case 0x27 :
		break;
		
	case 0x28 :
		if(VDAT_Lenovo)
		{
			SET_MASK(Device_Status_AllRF,Super_performance_F);
		}
		else
		{
			CLEAR_MASK(Device_Status_AllRF,Super_performance_F);
		}
		break;
		
	case 0x29 :
		VDAT_Lenovo = 1;
		break;
		
	case 0x2A :
		break;
		
	case 0x2B : //------------------------------------read Fan dust mode status
		VDAT_Lenovo = 0;
		#if SmartFanSupport
		switch(Lenvo_dust_mode)
		{
			case 0:
				VDAT_Lenovo = 0x05;
				break;
			case 1:
				if(DustTotleCont)
				{
					VDAT_Lenovo = 0x03;
				}
				else
				{
					VDAT_Lenovo = 0x05;
					Lenvo_dust_mode = 0;
				}
				break;
			case 2:
				VDAT_Lenovo = 0x85;
				Lenvo_dust_mode = 0x00;
				break;
			default:
				break;
		}		
		#endif
		break;
		
	case 0x2C :
		break;
		
	case 0x2D :
		VDAT_Lenovo = 0x02;//SV+ATI
		if(Device_Status_AllRF&Super_performance_F)
		{
			SET_MASK(VDAT_Lenovo,BIT3);
		}
		
		if((Oem_Globe_Flag1&Oem_SYS_Temp_OV_f) || (Oem_Globe_Flag1&Oem_SYS_Temp_OV_f))
		{
			SET_MASK(VDAT_Lenovo,BIT4);
		}
		break;
		
	case 0x2E :
		break;
		
	case 0x2F :
		if(Bios_Battery_Health_0&EDCC)
		{
			VDAT_Lenovo=BIT2;
		}
		else
		{
			VDAT_Lenovo=0;	
		}
		
		if(Lenvo_general_f&auto_mode_f)
		{
			SET_MASK(VDAT_Lenovo,BIT1);
		}

		if(Lenvo_general_f&super_temp_f)
		{
			SET_MASK(VDAT_Lenovo,BIT3);
		}
		break;
		
	case 0x30 :
		break;
		
	case 0x31 :
		VDAT_Lenovo = 0x01;   //------- onekey recovery
		break;
		
	case 0x32 :
		break;
		
	case 0x33 : //--------------------------------------Set Inverter
		if(0 == VDAT_Lenovo)//-------------------------- turn off
		{
			CLEAR_MASK(Device_Status_Lenovo,Inverter_S_B);
			//HW_OFF_BKLT_PORT &= ~HW_OFF_BKLT;
		}
		else               //-------------------------- turn on
		{
			SET_MASK(Device_Status_Lenovo,Inverter_S_B);
			//HW_OFF_BKLT_PORT |= HW_OFF_BKLT;
		}
		break;
		
	default:
		break;	 

	}


	
	VCMD_Lenovo = 0x00;
}

#endif

void OEM_QUIT_TEST(void)
{


}


//--------------------------------------
//
//--------------------------------------
void OEM_Fan_LED_Verify(void)
{
	if(EC_EXT_CMD==0x80)
	{
		switch(EC_DAT1)
		{
			case 0x01:
				DebugFan1VoltageOut=0x01;
				break;
					
			case 0x02:
			//	DebugFanRPMT=EC_DAT3;  //V71   //lw 2017/12/04
				break;
				
			case 0x03:
			//	DebugFanRPMT=0x01;         //lw 2017/12/04
				break;
				
			case 0x04:
			//	DebugFanRPMT=FanHighValue;   //lw 2017/12/04
				break;
				
			case 0x05:
				OEM_LED_TEST();
				break;
				
			case 0x06:
			case 0x07:
			case 0x08:
			case 0x09:
			case 0x0A:
			case 0x0B:
			case 0x0C:
				break;
				
			case 0x0D:
 				OEM_QUIT_TEST();
				break;
		}		

		EC_EXT_CMD=0;		
	}
}




/*------------------------------------------;
 ;  Extra EC COMMAND TABLE 0x80-0xFF
 ; base 5ms 
 ;------------------------------------------*/
void EXT_EC_CMD(void)
{
	switch(EC_EXT_CMD)
	{
	case 0x80 : 
		if(0x70 == EC_DAT2)
		{
			//OEM_Fan_LED_Verify();//lw 2017/12/04
			EC_DAT2=0;
		}
		break;
		
	case 0x81 : 
		if(0x81 == EC_DAT1)
		{
			//EC_DAT2 = (FAN1_CurrentRPM/100);//lw 2017/12/04
		}
		break;
		
	case 0x82 : 
		if(3 == OS_Type)
		{
			EC_DAT1 = MAX_LEVEL_linux;
		}
		else
		{
			EC_DAT1 = MAX_LEVEL;
		}
		break;
		
	case 0x83 : 
		EC_DAT3 = CpuTemp;
		break;
		
	case 0x84 :  
//Oem_TriggerS0S5(SC_S0SLPOff);
		break;
		
	case 0x85 : //EXT_EC_CMD_66_85
	case 0x86 : //EXT_EC_CMD_66_86 
	case 0x87 : //EXT_EC_CMD_66_87 
	case 0x88 : //EXT_EC_CMD_66_88 
	case 0x89 : //EXT_EC_CMD_66_89 
	case 0x8A : //EXT_EC_CMD_66_8A 
	case 0x8B : //EXT_EC_CMD_66_8B 
	case 0x8C : //EXT_EC_CMD_66_8C 
	case 0x8D : //EXT_EC_CMD_66_8D 
	case 0x8E : //EXT_EC_CMD_66_8E 
	case 0x8F : //EXT_EC_CMD_66_8F 
	case 0x90 : //EXT_EC_CMD_66_90 
		SET_MASK(SYS_MISC1,OFF_ALW);
		break;
		
	case 0x91 : //EXT_EC_CMD_66_91 
		CLEAR_MASK(SYS_MISC1,OFF_ALW);
		break;
		
	case 0x92 : //EXT_EC_CMD_66_92 
	case 0x93 : //EXT_EC_CMD_66_93 
	case 0x94 : //EXT_EC_CMD_66_94 
	case 0x95 : //EXT_EC_CMD_66_95 
	case 0x96 : //EXT_EC_CMD_66_96 
	case 0x97 : //EXT_EC_CMD_66_97 
	case 0x98 : //EXT_EC_CMD_66_98 
	case 0x99 : //EXT_EC_CMD_66_99 
	case 0x9A : //EXT_EC_CMD_66_9A 
	case 0x9B : //EXT_EC_CMD_66_9B 
	case 0x9C : //EXT_EC_CMD_66_9C 
	case 0x9D : //EXT_EC_CMD_66_9D 
	case 0x9E : //EXT_EC_CMD_66_9E 
	case 0x9F : //EXT_EC_CMD_66_9F 
	case 0xA0 : //EXT_EC_CMD_66_A0 
	case 0xA1 : //EXT_EC_CMD_66_A1
	case 0xA2 : //EXT_EC_CMD_66_A2 
	case 0xA3 : //EXT_EC_CMD_66_A3							
	case 0xA4 : //EXT_EC_CMD_66_A4 
	case 0xA5 : //EXT_EC_CMD_66_A5 
	case 0xA6 : //EXT_EC_CMD_66_A6 
	case 0xA7 : //EXT_EC_CMD_66_A7 
	case 0xA8 : //EXT_EC_CMD_66_A8 
	case 0xA9 : //EXT_EC_CMD_66_A9 
	case 0xAA : //EXT_EC_CMD_66_AA 
	case 0xAB : //EXT_EC_CMD_66_AB 
	case 0xAC : //EXT_EC_CMD_66_AC 
	case 0xAD : //EXT_EC_CMD_66_AD 
	case 0xAE : //EXT_EC_CMD_66_AE 
	case 0xAF : //EXT_EC_CMD_66_AF 
	case 0xB0 : //EXT_EC_CMD_66_B0	
	case 0xB1 : //EXT_EC_CMD_66_B1	
	case 0xB2 : //EXT_EC_CMD_66_B2
		break;
		
	case 0xB3 : //EXT_EC_CMD_66_B3
		if(BIOS_OEM_battery_health&HOST_SMBUS_GET)
		{
			SMB_CMD=EC_DAT1;
			SMB_ADDR=EC_DAT2;
			SMB_PRTC=EC_DAT3;
		}
		break;
		
	case 0xB4 : //EXT_EC_CMD_66_B4	//:LM
		if(0x90 == EC_DAT1)
		{
	        AC_OFF();
			AdapterOut();
			
		}
		if(0x91 == EC_DAT1)
		{
 	        AC_ON();
			AdapterIn();

		}
		if(0x92 == EC_DAT1)
		{

		}
		break;
		
	case 0xB5 : //EXT_EC_CMD_66_B5
		if(0x82 == EC_DAT1) //wireless 
		{
			EC_DAT1=3;
		}
		
		if(0x83 == EC_DAT1) //novo
		{
		
		}
		
		if(0x84 == EC_DAT1) //lid 
		{
			if(EC_EXT_SOURCE_STATE&LID_CLOSE_Act)
			{
				EC_DAT1=1;
			}
			else
			{
				EC_DAT1=2;
			}
		}
		
		if(0x85 == EC_DAT1) //qs
		{
			EC_DAT1=3;
		}
		break;
		
	case 0xB6 : 
		if(0x86 == EC_DAT1)
		{
			LCD_BRIGHTNESS = EC_DAT3;
			Setup_Brightness(EC_DAT3);
			
		}
		if(0x87 == EC_DAT1)
		{
//			Oem_Open_Verify_Control();
			//OEM_Backlight_Verify();
		}
		break;
		
	case 0xB7 : 
	case 0xB8 :		// WRITE BYTE TO EXTERNAL MEMORY
		*((PORT_BYTE_PNTR)((EC_DAT1*0x100)+EC_DAT2)) = EC_DAT3;
		EC_DAT2=0;
		EC_DAT1=0;
        break;
		
	case 0xB9 : 	// READ BYTE FROM EXTERNAL MEMORY
		EC_DAT3 = *((PORT_BYTE_PNTR)((EC_DAT1*0x100)+EC_DAT2));
		break;
		
	case 0xBA : //EXT_EC_CMD_66_BA 
	case 0xBB : //EXT_EC_CMD_66_BB	
	case 0xBC : //EXT_EC_CMD_66_BC	
	case 0xBD : //EXT_EC_CMD_66_BD	
	case 0xBE : //EXT_EC_CMD_66_BE	
	case 0xBF : //EXT_EC_CMD_66_BF 
	case 0xC0 : //EXT_EC_CMD_66_C0	
	case 0xC1 : //EXT_EC_CMD_66_C1	
	case 0xC2 : //EXT_EC_CMD_66_C2 
		break;
		
	case 0xC3 : //EXT_EC_CMD_66_C3	;; GET GPIO STATUS
		EC_DAT3 = *((PORT_BYTE_PNTR)((&GPDRA)+(EC_DAT1&0x0f)));
		break;
		
	case 0xC4 : //EXT_EC_CMD_66_C4
	case 0xC5 : //EXT_EC_CMD_66_C5 		
	case 0xC6 : //EXT_EC_CMD_66_C6 
	case 0xC7 : //EXT_EC_CMD_66_C7 
	case 0xC8 : //EXT_EC_CMD_66_C8 
	case 0xC9 : //EXT_EC_CMD_66_C9	;; GET WAKE-UP EVENT

/*----------------------------------------------;
 ;C9 EC COMMAND : GET SWI						;
 ;----------------------------------------------*/
	//	EC_DAT3=SWI_BUF;
	//	SWI_BUF=0;
		break;

	case 0xCA : //EXT_EC_CMD_66_CA 
	case 0xCB : //EXT_EC_CMD_66_CB 
	case 0xCC : //EXT_EC_CMD_66_CC 
		break;
		
	case 0xCD : //EXT_EC_CMD_66_CD	;; GET SMI EVENT NOTIFICATION INFO
/*----------------------------------------------;
 ;CD EC COMMAND : GET SMI						;
 ;----------------------------------------------*/
	//	EC_DAT3=SMI_BUF;
	//	SMI_BUF=0;
	//	PMSTS &=~ SMIEVT_F;
		break;

	case 0xCE : //EXT_EC_CMD_66_CE 
	case 0xCF : //EXT_EC_CMD_66_CF 
	case 0xD0 : //EXT_EC_CMD_66_D0 
	case 0xD1 : //EXT_EC_CMD_66_D1 
	case 0xD2 : //EXT_EC_CMD_66_D2 
	case 0xD3 : //EXT_EC_CMD_66_D3 
	case 0xD4 : //EXT_EC_CMD_66_D4 
	case 0xD5 : //EXT_EC_CMD_66_D5	;; SET DELAY TASK 1 TIMER			
	case 0xD6 : //EXT_EC_CMD_66_D6	;; SET DELAY TASK 2 TIMER
	case 0xD7 : //EXT_EC_CMD_66_D7 
	case 0xD8 : //EXT_EC_CMD_66_D8 
	case 0xD9 : //EXT_EC_CMD_66_D9 
	case 0xDA : //EXT_EC_CMD_66_DA 
	case 0xDB : //EXT_EC_CMD_66_DB 
	case 0xDC : //EXT_EC_CMD_66_DC 
	case 0xDD : //EXT_EC_CMD_66_DD 
	case 0xDE : //EXT_EC_CMD_66_DE 
	case 0xDF : //EXT_EC_CMD_66_DF 
	case 0xE0 : //EXT_EC_CMD_66_E0 
	case 0xE1 : //EXT_EC_CMD_66_E1 
	case 0xE2 : //EXT_EC_CMD_66_E2 
	case 0xE3 : //EXT_EC_CMD_66_E3 
	case 0xE4 : //EXT_EC_CMD_66_E4 
	case 0xE5 : //EXT_EC_CMD_66_E5 
	case 0xE6 : //EXT_EC_CMD_66_E6 
	case 0xE7 : //EXT_EC_CMD_66_E7 
	case 0xE8 : //EXT_EC_CMD_66_E8 
	case 0xE9 : //EXT_EC_CMD_66_E9 
	case 0xEA : //EXT_EC_CMD_66_EA 
	case 0xEB : //EXT_EC_CMD_66_EB 
	case 0xEC : //EXT_EC_CMD_66_EC 
	case 0xED : //EXT_EC_CMD_66_ED 
	case 0xEE : //EXT_EC_CMD_66_EE 
	case 0xEF : //EXT_EC_CMD_66_EF 
	case 0xF0 : //EXT_EC_CMD_66_F0 
	case 0xF1 : //EXT_EC_CMD_66_F1 
	case 0xF2 : //EXT_EC_CMD_66_F2 
	case 0xF3 : //EXT_EC_CMD_66_F3 
	case 0xF4 : //EXT_EC_CMD_66_F4 
	case 0xF5 : //EXT_EC_CMD_66_F5 
	case 0xF6 : //EXT_EC_CMD_66_F6 
	case 0xF7 : //EXT_EC_CMD_66_F7 
	case 0xF8 : //EXT_EC_CMD_66_F8 
	case 0xF9 : //EXT_EC_CMD_66_F9 
	case 0xFA : //EXT_EC_CMD_66_FA 
	case 0xFB : //EXT_EC_CMD_66_FB 
	case 0xFC : //EXT_EC_CMD_66_FC 
	case 0xFD : //EXT_EC_CMD_66_FD 
	case 0xFE : //EXT_EC_CMD_66_FE 
	case 0xFF : //EXT_EC_CMD_66_FF
	default:
		break;	 
	}   
	
	EC_EXT_CMD=0;            
}                


