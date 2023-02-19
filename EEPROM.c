#include "N76E003.h"
#include "Common.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "lcd.h"
#include "delay.h"
#include "EEPROM.h"

void lcd_print_c(unsigned char x_pos, unsigned char y_pos, unsigned char value);
void lcd_print_i(unsigned char x_pos, unsigned char y_pos, unsigned int value);

void main(void) 
{
    unsigned char address = 0;
    unsigned char value = 0;
	
    Set_All_GPIO_Quasi_Mode;
    P14 = read_data_byte(5000);	 
	
    LCD_init();
    LCD_clear_home(); 
		
    LCD_goto(0, 0); 
    LCD_putstr("R ADDR:");
    LCD_goto(0, 1); 
    LCD_putstr("R DATA:");
	
    for (address = 0; address <= 9; address++)
    {
        value = read_data_byte(address + BASE_ADDRESS);		
        lcd_print_i(8, 0, address + BASE_ADDRESS);
        lcd_print_c(8, 1, value);
    }

    Timer0_Delay1ms(100);
		
    LCD_goto(0, 0); 
    LCD_putstr("W ADDR:");
    LCD_goto(0, 1); 
    LCD_putstr("W DATA:");
	
    for (address = 0; address <= 9; address++)
    {
        write_data_byte(address + BASE_ADDRESS, address);
        lcd_print_i(8, 0, address + BASE_ADDRESS);
        lcd_print_c(8, 1, address);
    } 
	
    LCD_clear_home(); 
    LCD_goto(0, 0);
    LCD_putstr("STATUS:");
	
    while (1)
    {
        lcd_print_c(8, 0, !P14);
        Timer0_Delay1ms(3000);
        P14 = !P14;
        write_data_byte(5000, P14);
    }
}

void lcd_print_c(unsigned char x_pos, unsigned char y_pos, unsigned char value) {  
    LCD_goto(x_pos, y_pos);
    LCD_putchar(value/100 + '0');
    LCD_putchar(value/10 % 10 + '0');
    LCD_putchar(value % 10 + '0');
}

void lcd_print_i(unsigned char x_pos, unsigned char y_pos, unsigned int value) {  
    LCD_goto(x_pos, y_pos);
    LCD_putchar(value/10000 + '0');
    LCD_putchar(value/1000 % 10 + '0');
    LCD_putchar(value/100 % 10 + '0');
    LCD_putchar(value/10 % 10 + '0');
    LCD_putchar(value % 10 + '0');
}
