#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

 FOSC_240000;

void set_PWM_period(unsigned int value){
  PWMPL = (value & 0x00FF);
  PWMPH = ((value & 0xFF00) >> 8);
}

void set_PWM(unsigned int channel, unsigned int value){
  switch(channel) {
    case 0:
      PWM0L = (value & 0x00FF);
      PWM0H = ((value & 0xFF00) >> 8);
      break;
    case 1:
      PWM1L = (value & 0x00FF);
      PWM1H = ((value & 0xFF00) >> 8);
      break;
    case 2:
      PWM2L = (value & 0x00FF);
      PWM2H = ((value & 0xFF00) >> 8);
      break;
    case 3:
      PWM3L = (value & 0x00FF);
      PWM3H = ((value & 0xFF00) >> 8);
      break;
    case 4:
        set_SFRPAGE; 
      PWM4L = (value & 0x00FF);
      PWM4H = ((value & 0xFF00) >> 8);
       clr_SFRPAGE;
      break;
    case 5:
         set_SFRPAGE; 
      PWM5L = (value & 0x00FF);
      PWM5H = ((value & 0xFF00) >> 8);
        clr_SFRPAGE;
      break; 
  }
   set_LOAD;
}

void main(void){
  signed int value = 0;
  InitialUART0_Timer3(115200);/////
  printf("\nWELLCOME");
  Set_All_GPIO_Quasi_Mode;
  PWM_IMDEPENDENT_MODE;
  PWM_EDGE_TYPE;
  set_CLRPWM;
  PWM_CLOCK_FSYS;
  PWM_CLOCK_DIV_64;
  PWM_OUTPUT_ALL_NORMAL;
  set_PWM_period(1023);

            set_PWMRUN;
	
            while(1){         
            for(value = 0; value < 1024; value += 10){
            PWM1_P14_OUTPUT_ENABLE;   set_PWM(1,value);
            PWM1_P11_OUTPUT_ENABLE;   set_PWM(1,value);
            PWM2_P10_OUTPUT_ENABLE;   set_PWM(2,value);
            PWM2_P05_OUTPUT_ENABLE;   set_PWM(2,value);
            PWM3_P00_OUTPUT_ENABLE;   set_PWM(3,value);
            PWM3_P04_OUTPUT_ENABLE;   set_PWM(3,value);
            PWM0_P12_OUTPUT_ENABLE;   set_PWM(0,value); 
            PWM4_P01_OUTPUT_ENABLE;   set_PWM(4,value);
            PWM5_P03_OUTPUT_ENABLE;   set_PWM(5,value);
            PWM5_P15_OUTPUT_ENABLE;   set_PWM(5,value);
            Timer1_Delay10ms(3);
             printf("\nPWM:%d",value);
            }
							
            for(value = 1023; value > 0; value -= 10){
            PWM1_P14_OUTPUT_ENABLE;   set_PWM(1,value);
            PWM1_P11_OUTPUT_ENABLE;   set_PWM(1,value); 
            PWM2_P10_OUTPUT_ENABLE;   set_PWM(2,value);
            PWM2_P05_OUTPUT_ENABLE;   set_PWM(2,value);
            PWM3_P00_OUTPUT_ENABLE;   set_PWM(3,value);
            PWM3_P04_OUTPUT_ENABLE;   set_PWM(3,value); 
            PWM0_P12_OUTPUT_ENABLE;   set_PWM(0,value);
            PWM5_P03_OUTPUT_ENABLE;   set_PWM(5,value);
            PWM5_P15_OUTPUT_ENABLE;   set_PWM(5,value);	
            PWM4_P01_OUTPUT_ENABLE;   set_PWM(4,value);
            Timer1_Delay10ms(3); 
            printf("\nPWM:%d",value);	  
        }
          printf("\nSTOP!");			
         Timer1_Delay10ms(100);		
    }
}
