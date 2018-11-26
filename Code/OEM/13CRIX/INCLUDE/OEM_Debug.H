#ifndef	OEM_Debug_H
#define OEM_Debug_H

#define BRAM_Debug  TRUE 

#define DebugRamAddr  0x900
#define DebugRamRange 0xFF

#define DebugBRamAddr  0x2210
#define DebugBRamRange 0x2F

#define Uart_Base_Add  (*(volatile BYTE xdata *)0x0C00)
#define DebugUartRange 0x3FF

#define HEAT_DEBUG 0   //   1  lw 
#define BATTERY_DEBUG 0

extern void RamDebug(unsigned char dbgcode);
extern void BRAMDebug(unsigned char dbgcode);
extern void ClearBRam(void);
extern void Copy_BRAM_SRAM(void);

#endif