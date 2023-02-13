#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "string.h"
#include "lcd.h"
#include "math.h"

void Number_display(int value,int column, int row);
void String_display(const char *text, int column, int row);
void scroll_String_display(const char *text, int column, int row);

int values[] = {0, 409, 818, 1227, 1636, 2045, 2454, 2863, 3272, 4091};

void main(void)
{  
    unsigned long count = 0;
    unsigned char s = 0;
    const char str2[] = "HELLO WORLD!";
    const char str3[] = "WELLCOME!";
    const char str4[] = "THANKYOU..!";

    LCD_init();
    LCD_clear_home();

    String_display(str2, 2, 0);
    String_display(str3, 3, 1);
    Timer3_Delay100ms(30);
    LCD_clear_home();

    while(1)
    {      
        LCD_clear_home();
        String_display("SENSOR: ", 0, 0);
        Number_display(values[s++ % 10], 8, 0);
        Timer3_Delay100ms(5);

        String_display("COUNTER: ", 0, 1);
        Number_display(count++,9,1);
        Timer3_Delay100ms(10);

        scroll_String_display(str4, 1, 0);
    };
}


void Number_display(int value, int column, int row)
{  int i;
    for (i = 3; i >= 0; i--)
    {   LCD_goto(column++, row);
        LCD_putchar((value / (int)pow(10, i) % 10) + 0x30);
    }
}


void String_display(const char *text, int column, int row)
{
    LCD_goto(column, row);
    LCD_putstr(text);
}

void scroll_String_display(const char *text, int column, int row)
{ int i; LCD_clear_home(); LCD_goto(column, row);
         LCD_putstr(text); Timer3_Delay100ms(2);
	
    for (i =0; i < strlen(text); i++)
    {   LCD_clear_home();
        LCD_goto(column, row);
        LCD_putstr(&text[i]);
        Timer3_Delay100ms(.1);
    }
}
