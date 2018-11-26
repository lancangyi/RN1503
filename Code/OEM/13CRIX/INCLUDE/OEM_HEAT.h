
#ifndef OEM_HEAT_H
#define OEM_HEAT_H

  
#define TEMP_SPECIAL_VALUE  0x9C   //if temp value = 0x9c, then EC wake up now

#define TEMP_WITHOUT_BATTERY     0xBD8


//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern FLAG CompareT1T2(BYTE T1, BYTE T2);
extern void StopHeat();
extern BYTE Check_Low_Temperature(void);
extern void EC_Wakeup_Check_Temperature(void);
extern BYTE Check_Heating_PowerOn(void);
extern BYTE Check_Battery_Stat(WORD *p_battery_vcc_tmp);
extern void Heating_Service(void);
extern void BatteryStatAutoChange(void);
extern void Init_Heating(void);
extern void LCD_OS_Heating_Service(void);

#endif
