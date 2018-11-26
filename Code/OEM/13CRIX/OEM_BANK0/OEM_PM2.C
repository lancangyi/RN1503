/*----------------------------------------------------------------------------
 * Filename: OEM_PM2.C  For Chipset: ITE.IT85XX
 *
 * Copyright (c) 2010 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>



void Pm2_Cmd_80Data(void)
{
	if (PM2Step == 1)
	{
		Tmp_XPntr=(ECRAM|PM2Data);
		PM2DO = *Tmp_XPntr;
	}
}


void Pm2_Cmd_81Data(void)
{
	if (PM2Step == 2)
	{
     	PM2Data1=PM2Data;
	}
	else if(PM2Step == 1)
	{
		Tmp_XPntr=(ECRAM|PM2Data1);
		*Tmp_XPntr = PM2Data;
 	}
}


void Pm2_Cmd_92Data(void)
{
	switch(PM2Step)
	{
		case 2:
			PM2Data1=PM2Data;	// address high
			break;
		case 1:
			Tmp_XPntr=((PM2Data1<<8)+PM2Data);
			PM2DO = *Tmp_XPntr;
			break;
		default:break;
	}
}


void Pm2_Cmd_93Data(void)
{
	switch(PM2Step)
	{
		case 3:
			PM2Data2=PM2Data;  // address high
			break;
		case 2:
			PM2Data1=PM2Data;  // address low
			break;
		case 1:
			Tmp_XPntr=((PM2Data2<<8)+PM2Data1);
			*Tmp_XPntr=PM2Data;
			break;
		default:break;
	}
}






void Pm2_Cmd_80(void)
{
	PM2Step=0x01;
}




void Pm2_Cmd_81(void)
{
	PM2Step=0x02;
}



void Pm2_Cmd_92(void)
{
	PM2Step=0x02;

}


void Pm2_Cmd_93(void)
{
	PM2Step=0x03;
}

void Pm2_Cmd_DC(void)
{
	ITE_Flash_Utility(); // for RN1503 
}

void Pm2_Cmd_DD(void)
{
	BIOS_Get_EC_LowVersion(); // bios get the EC Version Low Byte
}



void Pm2_Cmd_DE(void)
{
	BIOS_Get_EC_HighVersion(); // bios get the EC Version High Byte
}



//----------------------------------------------------------------------------
// The function of debuging 68 port
//----------------------------------------------------------------------------
void Hook_68Port(BYTE PM2Data)
{
	switch(PM2Data)
	{
		case 0x80:
			Pm2_Cmd_80Data();   // read ec ram
			break;
		case 0x81:
			Pm2_Cmd_81Data();   // write ec ram
			break;
		case 0x92:
			Pm2_Cmd_92Data();   // read extend ec ram
			break;
		case 0x93:
			Pm2_Cmd_93Data();   // write extend ec ram
			break;
		default:break;
	}
}


//----------------------------------------------------------------------------
// The function of debuging 6C port
//----------------------------------------------------------------------------
void Hook_6CPort(BYTE PM2Cmd)
{
	switch(PM2Cmd)
	{
		case 0x80:
			Pm2_Cmd_80();    // read ec ram
			break;
		case 0x81:
			Pm2_Cmd_81();    // write ec ram
			break;
		case 0x92:
			Pm2_Cmd_92();    // read extend ec ram
			break;
		case 0x93:
			Pm2_Cmd_93();  // write extend ec ram
			break;
	    case 0xDC:
			Pm2_Cmd_DC();  // RN1503 reflash firmware 
			break;
		case 0xDD:
			Pm2_Cmd_DD(); // bios get the EC version low byte
			break;
		case 0xDE:
			Pm2_Cmd_DE(); // bios get the EC version High byte
			break;

		
		default:break;
	}
}

//----------------------------------------------------------------------------
// Process Command/Data received from System via 68/6C interface
//----------------------------------------------------------------------------
void service_pci3(void)
{  
   if( IS_MASK_CLEAR(PM2STS,P_IBF) )  
   {
		return; 
   }
	
	if ( PM2STS & P_C_D)	// Command port
	{
        PM2Step =0;
   		PM2Cmd  = PM2DI;	// Load command
		EnablePMCIBFInt();
		Hook_6CPort(PM2Cmd);    // Handle command
	}
	else					// Data port
	{
        PM2Data = PM2DI;
        EnablePMCIBFInt();
        if (PM2Step!=0x00)
        {
		    Hook_68Port(PM2Cmd);   // Handle command data
		    PM2Step--;
	    }
	}
}

