/*
 * MC1.c
 *
 *  Created on: Sep 8, 2021
 *      Author: salem salem
 */

#include"../LIB/STD_Types.h"
#include"../LIB/ATMEGA32_REGISTERS.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_int.h"
#include"LCD_int.h"
#include"ADC.h"


int main(void)
{
	//Initializing the LCD
	LCD_vidInit();

	//Initializing the ADC
	ADC_vidInit();


	f32 Adc_result = 0.0;

	u8 ADC_val = 0;


	//SET PIN 0 OF PORT D OUTPUT LOW, SO THAT WE CAN COMMUNICATE WITH THE OTHER MICROCONTROLLER
	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_0,DIO_u8OUTPUT);
	DIO_vidSetPinVal(u8PORTD,DIO_u8PIN_0,DIO_u8LOW);

	while(1)
	{

		//Reading the ADC result from ADC 0
		Adc_result = ADC_Read(ADC_ADMUX_CHANNEL_ADC0);

		//Converting the ADC result to digital value
		ADC_val= (Adc_result*100)/1024;


		//Printing the percentage of emptiness in the tank
		LCD_vidGoTo(0,0);
		LCD_vidWriteData((((u8)ADC_val/10)%10)+ '0');
		LCD_vidGoTo(0,1 );
		LCD_vidWriteData((((u8)ADC_val)%10)+ '0');
		LCD_vidGoTo(0,2);
		LCD_vidWriteString("%");
		LCD_vidGoTo(0,4);
		LCD_vidWriteString("EMPTY");

		//If the ADC value is greater than 0 set Port D Pin 0 high to communicate with the other MC
		if(ADC_val > 0)
		{
			DIO_vidSetPinVal(u8PORTD,DIO_u8PIN_0,DIO_u8HIGH);
		}

		//If the ADC value is equal to 0 set Port D Pin 0 low to communicate with the other MC
		else
		{

			DIO_vidSetPinVal(u8PORTD,DIO_u8PIN_0,DIO_u8LOW);

		}


	}
	
	return 0;

}
