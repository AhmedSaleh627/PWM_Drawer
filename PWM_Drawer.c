#include "LIB/STD_Type.h"
#include "MCAL/Watch_Dog/WatchDog_interface.h"
#include "LIB/BITMATH.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/GIE_interrupt/GIE_interface.h"
#include "MCAL/GIE_interrupt/EXIT_interface.h"
#include "MCAL/TIMER0/TIMER0_private.h"
#include "MCAL/TIMER0/TIMER0_interface.h"
#include "MCAL/TIMER1/TIMER1_private.h"
#include "MCAL/TIMER1/TIMER1_interface.h"
#include "HAL/DC_Motor_Driver/DC_Motor_interface.h"
#include "HAL/LCD_Driver/LCD_config.h"
#include "HAL/LCD_Driver/LCD_interface.h"
#include <string.h>
#include "LIB/Vect_table.h"

#define F_CPU 16000000UL
#include "util/delay.h"


volatile static u32 overflow_ticks=0 ;

volatile static u32 on_ticks=0 ;

volatile static u8 dutycycle=10 ;

void  HW_ICU(void) ;



char *_0_dutycyle ="_______________________________ ";
char *_10_dutycyle ="_________|-|_________|-|_________|-| ";
char *_20_dutycyle ="________|--|________|--|________|--| ";
char *_30_dutycyle ="_______|---|_______|---|_______|---| ";
char *_40_dutycyle ="______|----|______|----|______|----| ";
char *_50_dutycyle ="_____|-----|_____|-----|_____|-----| ";
char *_60_dutycyle ="____|------|____|------|____|------| ";
char *_70_dutycyle ="___|-------|___|-------|___|-------| ";
char *_80_dutycyle ="__|--------|__|--------|__|--------| ";
char *_90_dutycyle ="_|---------|_|---------|_|---------| ";
char *_100_dutycyle ="----------------------------- ";

char *smallText="Hi how are you ";

u8 iCursor=0;
u8 iLineNumber=1;
 
void UpdateDisplay(char *Text);

int main(void)
{
	  
	 LCD_Vid_Init() ;
	 DIO_Vid_Set_Pin_Dir(PORTB,PIN3,OUTPUT) ;
	 TIMER1_Vid_NormalMode_Init() ;
	 GIE_Vid_Enable();
	 Timer1_U8CaptureEventEnableInterrupt();
	 EXT_Vid_Interrupt_Init(RISING_EDGE) ;
	EXT_Vid_Interrupt0();
	EXT_Vid_Interrupt1();
	  while (1)
	  {
		
		TIM0_Vid_Fast_PWM(dutycycle) ;
		
		Timer1_U8CaptureEventSetCallBack(HW_ICU);
		Timer1_Edge_Select(RISING_EDGE);
		LCD_Vid_GOTOXY(0,0);
		LCD_Send_String("Duty=");
		LCD_Vid_GOTOXY(7,0);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GOTOXY(5,0);
		LCD_Send_Number(dutycycle);
		LCD_Vid_Send_Data('%');
		LCD_Vid_GOTOXY(9,0);
		LCD_Send_String("Freq=");
		LCD_Send_Number( 976);
		LCD_Send_String("Hz");
		LCD_Vid_GOTOXY(22,0);
		LCD_Send_String("Ton=");
		LCD_Vid_GOTOXY(26,0);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GOTOXY(27,0);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GOTOXY(26,0);
		if(dutycycle<10)
		{
			LCD_Send_Number(0) ;
		}
		else
		{
			LCD_Send_Number(on_ticks) ;
		}
		
		LCD_Vid_GOTOXY(33,0);
		LCD_Send_String("Toff=");
		LCD_Vid_GOTOXY(38,0);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GOTOXY(39,0);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GOTOXY(38,0);
		LCD_Send_Number(16-on_ticks) ;
		LCD_Vid_GOTOXY(8,0);
		LCD_Vid_Send_Data(' ');
		
		if(dutycycle==10)
		{
			UpdateDisplay(_10_dutycyle);
			
		}
		else if(dutycycle==20)
		{
			UpdateDisplay(_20_dutycyle);
	
		}
		else if(dutycycle==30)
		{
			UpdateDisplay(_30_dutycyle);
		
		}
		else if(dutycycle==40)
		{
			UpdateDisplay(_40_dutycyle);

		}
		else if(dutycycle==50)
		{
			UpdateDisplay(_50_dutycyle);
	
		}
		else if(dutycycle==60)
		{
			UpdateDisplay(_60_dutycyle);
	
		}
		else if(dutycycle==70)
		{
			UpdateDisplay(_70_dutycyle);
	
		}
		else if(dutycycle==80)
		{
			UpdateDisplay(_80_dutycyle);
			
		}
		else if(dutycycle==90)
		{
			UpdateDisplay(_90_dutycyle);

		}
		else if(dutycycle==100)
		{
			UpdateDisplay(_100_dutycyle);
			

		}
		else
		{
			UpdateDisplay(_0_dutycyle);
	
		}
	
		_delay_ms(60);
				
	  }

	
}
void UpdateDisplay(char *Text)
{
	u8 iLenofLargeText=strlen(Text);
	if(iCursor==(iLenofLargeText-1))
	{
		iCursor=0;
	}
	LCD_Vid_GOTOXY(0,iLineNumber);
	
	if(iCursor<iLenofLargeText-40)
	{
		 for(u8 iChar=iCursor; iChar<iCursor+40; iChar++)
		 {
			 LCD_Vid_Send_Data(Text[iChar]);
		 }
	}
	else
	{
		for(u8 iChar=iCursor;iChar< (iLenofLargeText-1);iChar++)
		{
			  LCD_Vid_Send_Data(Text[iChar]);
		}
		for(u8 iChar=0;iChar<=40-(iLenofLargeText-iCursor);iChar++)
		{
			 LCD_Vid_Send_Data(Text[iChar]);
		}
	}
	iCursor++;
	
}



void  HW_ICU(void){

	static u8 count=0 ;
	count ++ ;
	
	if(count==1){
		TIMER1_Vid_RestTimer() ;
		Timer1_Edge_Select(FALLING_EDGE);
		
	}
	if(count==2){
		on_ticks=TIMER1_u16_Read_TimerVal() ;
		
		Timer1_Edge_Select(RISING_EDGE);
		
	}
	if(count==3){
		
		overflow_ticks=TIMER1_u16_Read_TimerVal();

	}
	
	
	
}

ISR(INT_0)
{
	
	dutycycle+=10;
	
}
ISR(INT_1)
{

	dutycycle-=10;
	
}
