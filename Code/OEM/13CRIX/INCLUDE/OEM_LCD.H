#ifndef OEM_LCD_H
#define OEM_LCD_H

#define	MAX_LEVEL	      10 
#define MAX_LEVEL_linux   10
#define Brg_Up            1
#define Brg_Dw            2

#define PANEL_COUNT       1 
#define Max_PWM           CTR

extern void Setup_Brightness(BYTE brg_level);
extern void Set_Brightness_Level(BYTE brg_dir);
extern void Init_Brightness(void);
extern void Off_Brightness(void);
extern void Check_Brightness(void);
extern void OEM_LED_TEST(void);
extern void Check_ALS_LUX(void);
#endif
