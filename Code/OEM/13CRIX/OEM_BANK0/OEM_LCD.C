
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


//const BYTE code BrightnessTBL_PWM[MAX_LEVEL+1]= {0x01,0x04,0x08,0x0C,0x12,0x19,0x1F,0x25,0x2D,0x34,0x3F};
//const BYTE code BrightnessTBL_PWM[MAX_LEVEL+1]=   {0x01,0x02,0x06,0x0A,0x12,0x1C,0x25,0x28,0x2F,0x34,0x3F};  //lw 2018/02/02  for press twice to adjust the bl issue 
const BYTE code BrightnessTBL_PWM[MAX_LEVEL+1]=   {0x01,0x02,0x03,0x07,0x0C,0x12,0x13,0x1C,0x26,0x30,0x3F};   //lw 2018/03/13




//-----------------------------------------------------------------------------
// Setup Brightness value
//-----------------------------------------------------------------------------
void Setup_Brightness(BYTE brg_level)
{
    if(!PanelInitFlag||SystemIsS0) 
    {
       // check setup value is under range
       if(brg_level > MAX_LEVEL)
	   {
		  brg_level = MAX_LEVEL;
	   }
	   
       PWM_VADJ = BrightnessTBL_PWM[brg_level];
	}
}

void Set_Brightness_Level(BYTE brg_dir)
{

  if(brg_dir==Brg_Up)
  {
     if(LCD_BRIGHTNESS>MAX_LEVEL)
     {
        LCD_BRIGHTNESS = MAX_LEVEL;
     }
	 else
	 {
       LCD_BRIGHTNESS++;
	 }
  }
  else if(brg_dir==Brg_Dw)
  {
    if(LCD_BRIGHTNESS >0)
    {
	    LCD_BRIGHTNESS--;
    }
	else
	{
	  LCD_BRIGHTNESS = 0;
    }
  }

}



//-----------------------------------------------------------------------------
// Initialize Brightness variable
//-----------------------------------------------------------------------------
void Init_Brightness(void)
{
    BrgLevel = 0x04 ;	
	bBrightness = 0 ;
	LCD_BRIGHTNESS = 5;//pannel initial lightness
}

void Off_Brightness(void)
{
    BrgLevel = 0x00 ;
}

//-----------------------------------------------------------------------------
// Check Brightness level change
//-----------------------------------------------------------------------------
void Check_Brightness(void)
{
    if(bBrightness != BrgLevel)
    {    
        bBrightness = BrgLevel;
		LCD_BRIGHTNESS = BrgLevel;
        Setup_Brightness(bBrightness);
    }
}

