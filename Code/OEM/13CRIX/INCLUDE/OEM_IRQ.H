/*-----------------------------------------------------------------------------
 * TITLE: OEM_IRQ.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef	OEM_IRQ_H
#define OEM_IRQ_H

extern void Hook_IRQ_INT1_WKO20(void);
extern void Hook_IRQ_INT2_KBCOBE(void);
extern void Hook_IRQ_INT3_PMCPMC1OBE(void);
extern void Hook_IRQ_INT4_SMBusD(void);
extern void Hook_IRQ_INT5_WKINTAD(void);
extern void Hook_IRQ_INT6_WKO23(void);
extern void Hook_IRQ_INT7_PWM(void);
extern void Hook_IRQ_INT8_ADC(void);
extern void Hook_IRQ_INT9_SMBusA(void);
extern void Hook_IRQ_INT10_SMBusB(void);
extern void Hook_IRQ_INT11_KBMatrixScan(void);
extern void Hook_IRQ_INT12_WKO26(void);
extern void Hook_IRQ_INT13_WKINTC(void);
extern void Hook_IRQ_INT14_WKO25(void);
extern void Hook_IRQ_INT15_CIR(void);
extern void Hook_IRQ_INT16_SMBusC(void);
extern void Hook_IRQ_INT17_WKO24(void);
extern void Hook_IRQ_INT18_PS2Interrupt2(void);
extern void Hook_IRQ_INT19_PS2Interrupt1(void);
extern void Hook_IRQ_INT20_PS2Interrupt0(void);
extern void Hook_IRQ_INT21_WKO22(void);
extern void Hook_IRQ_INT22_SMFISemaphore(void);
extern void Hook_IRQ_INT23_Null(void);
extern void Hook_IRQ_INT24_KBCIBF(void);
extern void Hook_IRQ_INT25_PMCPMC1IBF(void);
extern void Hook_IRQ_INT26_PMC2OBE(void);
extern void Hook_IRQ_INT27_PMC2IBF(void);
extern void Hook_IRQ_INT28_GINTofGPD5(void);
extern void Hook_IRQ_INT29_EGPC(void);
extern void Hook_IRQ_INT30_ET1(void);
extern void Hook_IRQ_INT31_WKO21(void);
extern void Hook_IRQ_INT32_GPINT0(void);
extern void Hook_IRQ_INT33_GPINT1(void);
extern void Hook_IRQ_INT34_GPINT2(void);
extern void Hook_IRQ_INT35_GPINT3(void);
extern void Hook_IRQ_INT36_CIRGPINT(void);
extern void Hook_IRQ_INT37_SSPI(void);
extern void Hook_IRQ_INT38_UART1(void);
extern void Hook_IRQ_INT39_UART2(void);
extern void Hook_IRQ_INT40_Null(void);
extern void Hook_IRQ_INT41_Null(void);
extern void Hook_IRQ_INT42_Null(void);
extern void Hook_IRQ_INT43_Null(void);
extern void Hook_IRQ_INT44_Null(void);
extern void Hook_IRQ_INT45_Null(void);
extern void Hook_IRQ_INT46_Null(void);
extern void Hook_IRQ_INT47_Null(void);
extern void Hook_IRQ_INT48_WKO60(void);
extern void Hook_IRQ_INT49_WKO61(void);
extern void Hook_IRQ_INT50_WKO62(void);
extern void Hook_IRQ_INT51_WKO63(void);
extern void Hook_IRQ_INT52_WKO64(void);
extern void Hook_IRQ_INT53_WKO65(void);
extern void Hook_IRQ_INT54_WKO66(void);
extern void Hook_IRQ_INT55_WKO67(void);
extern void Hook_IRQ_INT56_Null(void);
extern void Hook_IRQ_INT57_Null(void);
extern void Hook_IRQ_INT58_ET2(void);
extern void Hook_IRQ_INT59_DeferredSPIInstruction(void);
extern void Hook_IRQ_INT60_TMRINTA0(void);
extern void Hook_IRQ_INT61_TMRINTA1(void);
extern void Hook_IRQ_INT62_TMRINTB0(void);
extern void Hook_IRQ_INT63_TMRINTB1(void);
extern void Hook_IRQ_INT64_PMC2EXOBE(void);
extern void Hook_IRQ_INT65_PMC2EXIBF(void);
extern void Hook_IRQ_INT66_PMC3OBE(void);
extern void Hook_IRQ_INT67_PMC3IBF(void);
extern void Hook_IRQ_INT68_PMC4OBE(void);
extern void Hook_IRQ_INT69_PMC4IBF(void);
extern void Hook_IRQ_INT70_Null(void);
extern void Hook_IRQ_INT71_I2BRAM(void);
extern void Hook_IRQ_INT72_WKO70(void);
extern void Hook_IRQ_INT73_WKO71(void);
extern void Hook_IRQ_INT74_WKO72(void);
extern void Hook_IRQ_INT75_WKO73(void);
extern void Hook_IRQ_INT76_WKO74(void);
extern void Hook_IRQ_INT77_WKO75(void);
extern void Hook_IRQ_INT78_WKO76(void);
extern void Hook_IRQ_INT79_WKO77(void);

extern void EnablePMC3IBFInt(void);
extern void Hook_EnableInterrupt(void);
extern void Hook_OEM_Isr_Int1(void);

#endif