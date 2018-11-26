/*-----------------------------------------------------------------------------
 * TITLE: OEM_FAN.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_FAN_H
#define OEM_FAN_H

//-----------------------------------------------------------------------------
// Define Smbus device address
//-----------------------------------------------------------------------------
#define ThermalAddr	        0x98	// thermal sensor address
#define PCH_Address         0x96    // PCH address
#define GPU_Address         0x82    // GPU address

//-----------------------------------------------------------------------------
// Define thermal sensor commands
//-----------------------------------------------------------------------------
#define LocalCmd		    0x00	// Read Local temprature
#define RemoteCmd	        0x01	// Read remote temprature
#define ReadStatsuCmd       0x02	// Read thermal status

#define CPURemoteOVTCmd	    0x19	// HW shutdown command 
#define CPULocalOVTCmd	    0x20	// HW shutdown command
#define CPURACmd            0x0D    // Stores the integer portion of the high limit for the External Diode
#define CPULACmd            0x0B    // Stores the 8-bit high limit for the Internal Diode
#define CPURALCmd           0x0E    // Stores the integer portion of the low limit for the External Diode
#define CPULALCmd           0x0C    // Stores the 8-bit low limit for the Internal Diode
#define ManifactorID        0xFE

#define PchTPackageCmd      0x40    // pch temprature package
#define GPUTPackageCmd      0x03

#define GPU_ITS_Chanel		SMbusCh2
#define GPU_TS_Addr			0x98	// for GPU Thermal sensor
#define GPU_ITS_Addr		0x82	// for GPU internal sensor


#define Configuration       0x09
#define ThermHysteresis     0x21
#define ConsecutiveAlert    0x22
#define DiodeFactor         0x27
#define DiodeFactor2        0x28
#define FilterControl       0x40
#define AlertConfig         0xBF

//-----------------------------------------------------------------------------
// For SMSC thermal sensor setting
//-----------------------------------------------------------------------------
#define SMSC_ID             0x5D
#define SMSC_CPU_Local_OVT  0x78            
#define SMSC_CPU_Remote_OVT 0x78   
#define SMSC_CPURAValue     0x78    
#define SMSC_CPULAValue     0x5A   

#define GMT_ID              0x47
#define GMT_CPU_Local_OVT   0x78          
#define GMT_CPU_Remote_OVT  0x78  
#define GMT_CPURAValue      0x78
#define GMT_CPULAValue      0x5A
#define GMT_CPURALValue     0xC9
#define GMT_CPULALValue     0xC9

#define NS_ID               0x01
#define NS_CPU_Local_OVT    0x78            
#define NS_CPU_Remote_OVT   0x78   
#define NS_CPURAValue       0x78
#define NS_CPULAValue       0x5A
#define NS_CPURALValue      0xC9
#define NS_CPULALValue      0xC9

//-----------------------------------------------------------------------------
// PCH Thermal Command
//-----------------------------------------------------------------------------
#define WriteSTSPreferences     0x41
#define WriteCPUTempLimits      0x42
#define WriteMCHTempLimits      0x43
#define WritePCHTempLimits      0x44
#define WriteDIMMTempLimits     0x45
#define WriteMPCCPUPowerClamp   0x50
#define PCHBlockRead            0x40

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define GPUFanValue		    GPUFan_volt        // The register of voltage output. (DAC or PWM)
#define CPUFanValue         CPUFan_volt
#define FanInitValue	    0x1F              // PWM output duty cycle 50%
#define S5S0FanInitValue	FanInitValue
#define S4S0FanInitValue	FanInitValue
#define S3S0FanInitValue	FanInitValue
#define	MaxOutValue		    0x3F             // PWM output duty cycle 100%
#define FanHighValue	    MaxOutValue
#define FanMiddleValue	    FanInitValue
#define FanLowValue	        0x10            // PWM duty cycle 25%

#define FullOnCounter	    20		       // time base 100ms
#define S5S0FullOnCounter	100		       // time base 100ms   10s
#define S4S0FullOnCounter	100		       // time base 100ms   10s
#define S3S0FullOnCounter	20		       // time base 100ms   2s

#define RPMACC			    100		       // +- 100 rpm ACC
#define FAN_MAX_RPM			5000	       // rpm max value for softwave filter, This value depends on the fan
#define FanDOS_RPM          3200		   //dos fan speed 

//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------



#define PCH_FanHigh_ON		90
#define PCH_FanHigh_OFF     80



#define SysTooHot		    80
#define SysTooHotTimes	    5

#define ProchotOnTM	        154 // 降频点的温度 ----90度
#define ProchotOffTM		149 // 自动恢复的温度---85度
#define ShutdownTM			164 // 系统关机的温度---100度

#define ThermalSenser_Addr		    0x98     //  temperature sensor can measure GPU CPU LCD temprature
#define LcdTemprature_H	            0x01     //  Lcd temperature High byte
#define LcdTemprature_L             0x10    //   Lcd temperature Low  byte
#define CpuTemprature_H             0x23    //   Cpu temperature High byte
#define CpuTemprature_L             0x24    //   Cpu temperature Low  byte
#define GpuTemprature_H             0x2A    //   Gpu temperature High byte
#define GpuTemprature_L             0x2B    //   Gpu temperature Low  byte


//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void GetThermalData(void);
extern void FanControl (void);
extern void MoniterTemprature(void);
extern void InitThermalChip(void);
extern void ReadThermalID(void);
extern void GPUFanFullOn(void);
extern void CPUFanFullOn(void);

extern void GPUFanFullOff(void);
extern void CPUFanFullOff(void);

extern void GPUFanInitOn(void);

extern void CPUFanInitOn(void);

extern void S5S0FanInitOn(void);
extern void S4S0FanInitOn(void);
extern void S3S0FanInitOn(void);
extern void GetRPM1(void);
extern void GetRPM2(void);
extern void CheckFanRPM(void);

extern void FanManager(void);
extern void ReadCPUTemp(void);
extern void ReadSysTemp(void);

//-----------------------------------------------------------------------------
// Structure define
//-----------------------------------------------------------------------------
typedef struct thermalstruct
{
	BYTE 	Level;
	BYTE 	T_high;
	BYTE 	T_low;
	WORD	step;
	WORD	start_RPM;
}thermal;

typedef	struct	TooHotStruct
{
	XBYTE	*Temprature;
	BYTE	Limit;
	XBYTE	*Counter;
	BYTE	Times;
}sTooHot;

typedef struct ThermalInitTablt
{
	BYTE	cmd	;	        // thermal init. command
	BYTE	value	;       // value of command	
	BYTE	RorW	;       // 0: read byte, 1: write byte
} sThermalInitTablt;

extern sThermalInitTablt code asThermalInitTablt[];
#endif

