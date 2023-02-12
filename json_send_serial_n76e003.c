#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#define bit_to_voltage_ratio 0.001220703125 // 5.0V divided by 4096 For 12-Bit ADC

#define LED P14
 FOSC_240000;
 
unsigned int ADC_read(void);
float voltage;
char str_voltage[20];

int myArray[9];
 unsigned int ADC_average(void);

int p=0;
int adc_data;

void main(void){	
	
               EX0 = 1; // enable external interrupt 0
               EA = 1; // enable global interrupt

	  //P05_OpenDrain_Mode;
     // Set_All_GPIO_Quasi_Mode;
   // Enable_ADC_AIN0;
	  InitialUART0_Timer3(115200); // timer diffrent Timer1_Delay10ms(50);
	 // TI = 1;
	
 // LED_Quasi_Mode;
  P15_Quasi_Mode;
  P12_Input_Mode;  
	Set_All_GPIO_Quasi_Mode;
	//Enable_ADC_AIN7;       
	
  while(1){
									 						 
					//    P14 = 1;
       // Timer0_Delay1ms(100);
							 
		   //  printf("\n Hello world!");						 
												 
			  				 Enable_ADC_AIN0;
						//	 printf(" ADC0:%d",ADC_read());	
							 myArray[0]= ADC_average();
							   Disable_ADC;
							 
							Enable_ADC_AIN1;
						//	printf(" ADC1:%d",ADC_read()); 
							 myArray[1]= ADC_average();
                 Disable_ADC;							 
							 
								 Enable_ADC_AIN2;
						//	 printf(" ADC2:%d",ADC_read());	
							 myArray[2]= ADC_average();
							   Disable_ADC;
							 
						/*	Enable_ADC_AIN3;
							printf(" ADC3:%d",ADC_average());	  
							    Disable_ADC;  */
									
							 Enable_ADC_AIN4;
					 // printf(" ADC4:%d",ADC_read());	 
							 myArray[4]= ADC_average();
							 Disable_ADC;
							 
							Enable_ADC_AIN5;
					//	printf(" ADC5:%d",ADC_read());	
							myArray[5]= ADC_average();
							 Disable_ADC;
							 
							  Enable_ADC_AIN6;
						// printf(" ADC6:%d",ADC_read());	 
							 myArray[6]= ADC_average();
					  	 Disable_ADC;
							 
							Enable_ADC_AIN7;
					//	printf("  ADC7:%d",ADC_read());	 
							myArray[7]= ADC_average();
							 Disable_ADC;
							 
							Enable_ADC_BandGap;
			  	//	printf(" ADCref:%d",ADC_read());	
							myArray[8]= ADC_average();
						  	Disable_ADC;
							 
         //  voltage = ADC_read() * bit_to_voltage_ratio;
         //  sprintf( str_voltage, "Volt: %0.2fV", voltage);
         //    printf(" ADCr:%s",str_voltage); 
							 
		 						 	
 if(P12 == 0){ P15 = 0; } // printf(" P12:0"); }
     else { P15 = 1; } // printf(" P12:1"); }				 
			 						 					 					
 printf("\n"); 
  printf("{\"ADC0\":%u,\"ADC1\":%u,\"ADC2\":%u,\"ADC3\":%u,\"ADC4\":%u}",myArray[0] ,myArray[1] ,myArray[2],myArray[3], myArray[4]);
   printf("{\"ADC5\":%u,\"ADC6\":%u,\"ADC7\":%u,\"ADCRef\":%u}",myArray[5],myArray[6],myArray[7],myArray[8]);	 
		 
		 LED =! LED;
		 
		 Timer1_Delay10ms(50);  // Timer1_Delay10ms(50);  50==500MS
		 
    }
  }


unsigned int ADC_read(void){
  register unsigned int adc_value = 0x0000;
  clr_ADCF;
  set_ADCS;                  
  while(ADCF == 0);
  adc_value = ADCRH;
  adc_value <<= 4;
  adc_value |= ADCRL;
  return adc_value;
}


 unsigned int ADC_average(void){
    int number_of_samples = 50;
    unsigned long sum_of_readings = 0;
    int average , count = 0;
    
    while (count < number_of_samples)
    {
        sum_of_readings += ADC_read();
        count++;
    }
    average = sum_of_readings / number_of_samples;
    return average;
}


void INT0_ISR (void) interrupt 0{
   // P14=0;  
	printf(" interrupt "); 
        
} 
