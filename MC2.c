/*
 * MC2.c
 *
 *  Created on: Sep 8, 2021
 *      Author: salem salem
 */
#include"../LIB/STD_Types.h"
#include"../LIB/ATMEGA32_REGISTERS.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_int.h"
#include<avr/delay.h>

int main(void)
{
	//Setting Port D pin 0 as input high to be able to communicate with other MC
	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_0,DIO_u8INPUT);
	DIO_vidSetPinVal(u8PORTD,DIO_u8PIN_0,DIO_u8HIGH);

	//Setting port direction for LED as output
	DIO_vidSetPinDirection(u8PORTB,DIO_u8PIN_0,DIO_u8OUTPUT);

	while(1)
	{
		//If MC 1 sends high value turn on the motor and Red LED
		if(DIO_u8GetPin(u8PORTD,DIO_u8PIN_0) == DIO_u8HIGH )
		{

			//Set the direction of PORTA to output to turn on the motor
			DIO_vidSetPortDirection(u8PORTA,0b00000011);

			//Making the motor turn clockwise
			DIO_vidSetPortVal(u8PORTA,0b00000001);

			//Turn on Red LED
			DIO_vidSetPinVal(u8PORTB,DIO_u8PIN_0,DIO_u8HIGH);

		}

		//If MC 1 sends low value turn off the motor and Red LED
		else
		{
			//Set the direction of PORTC to input so that the motor stops
			DIO_vidSetPortDirection(u8PORTA,0b00000000);

			//Turn off Red LED
			DIO_vidSetPinVal(u8PORTB,DIO_u8PIN_0,DIO_u8LOW);

		}



	}
	return 0;

}
