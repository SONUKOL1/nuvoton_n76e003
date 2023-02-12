#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "string.h"
#include "lcd.h"

void show_value(int value);
void center_display(const char *text, int line);
void scroll_display(const char *text, int line);

int values[] = {0, 409, 818, 1227, 1636, 2045, 2454, 2863, 3272, 4091};

void main(void)
{   unsigned long count;
    unsigned char s = 0;
    const char txt2[] = {"HELLO WORLD!"};
    const char txt3[] = {"WELLCOME!"};
    const char txt4[] = {"THANKYOU..!"};
		
    LCD_init();
    LCD_clear_home();

    center_display(txt2, 0);
    center_display(txt3, 1);
    Timer3_Delay100ms(30);
    LCD_clear_home();


    while(1)
    {      			
			  LCD_clear_home();
	      center_display("SENSOR DATA:", 0);
			  show_value(values[s % 10]);         
        Timer3_Delay100ms(20);
			
        LCD_clear_home();
	      center_display("COUNTER:", 0);
        show_value(count);			
	      Timer3_Delay100ms(20);
	
			 scroll_display(txt4, 1);
			
       s++; count++;
    };
}

void show_value(int value)
{  
   unsigned char ch = 0x00;  
	
   ch = ((value / 1000) + 0x30);
   LCD_goto(6, 1);
   LCD_putchar(ch);
   ch = (((value / 100) % 10) + 0x30);
   LCD_goto(7, 1);
   LCD_putchar(ch);
   ch = (((value / 10) % 10) + 0x30);
   LCD_goto(8, 1);
   LCD_putchar(ch);
   ch = ((value % 10) + 0x30);
   LCD_goto(9, 1);
   LCD_putchar(ch);
}

void center_display(const char *text, int line)
{    
    int start_pos = (16 - strlen(text)) / 2;
    if ((16 - strlen(text)) % 2 != 0)
        start_pos++;

      LCD_goto(start_pos, line);
      LCD_putstr(text);
}

void scroll_display(const char *text, int line)
{
    int i; LCD_clear_home();
    for (i = 0; i <= strlen(text); i++) {
			  LCD_clear_home();
        LCD_goto(0, line);
        LCD_putstr(&text[i]);
        Timer3_Delay100ms(0.3);
    }
  LCD_clear_home();
}
