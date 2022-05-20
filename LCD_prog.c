/*
 * LCD_prog.c
 *
 *  Created on: Aug 16, 2021
 *      Author: salem salem
 */


#include"../LIB/STD_TYPES.h"
#include"../LIB/ATMEGA32_REGISTERS.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_int.h"
#include"LCD_int.h"
#include<avr/delay.h>

void LCD_vidWriteData(u8 Copy_Data)
{

	DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_0,DIO_u8HIGH);
	DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_1,DIO_u8LOW);
	DIO_vidSetPortVal(u8PORTB,Copy_Data);
	DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_2,DIO_u8HIGH);
	_delay_ms(1.53);
	DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_2,DIO_u8LOW);
}



void LCD_vidSendCommand(u8 Copy_Command)
{
	DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_0,DIO_u8LOW);
		DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_1,DIO_u8LOW);
		DIO_vidSetPortVal(u8PORTB,Copy_Command);
		DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_2,DIO_u8HIGH);
		_delay_ms(1.53);
		DIO_vidSetPinVal(u8PORTC,DIO_u8PIN_2,DIO_u8LOW);
}




void LCD_vidWriteString(u8 * Copy_String)
{
	u8 iterator=0;
		for(iterator = 0 ; Copy_String[iterator] != '\0' ; iterator++)
		{
			LCD_vidWriteData(Copy_String[iterator]);
		}
}




void LCD_vidInit()
{
	DIO_vidSetPinDirection(u8PORTC,DIO_u8PIN_0,DIO_u8OUTPUT);
		DIO_vidSetPinDirection(u8PORTC,DIO_u8PIN_1,DIO_u8OUTPUT);
		DIO_vidSetPinDirection(u8PORTC,DIO_u8PIN_2,DIO_u8OUTPUT);
		DIO_vidSetPortDirection(u8PORTB,0xFF);

		_delay_ms(30); /** STEP 1 **/
		LCD_vidSendCommand(0b00111000); /** STEP 2 **/
		_delay_us(39); /** STEP 3 **/
		LCD_vidSendCommand(0b00001111);
		_delay_us(39);
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		_delay_ms(1.53);
		LCD_vidSendCommand(0b00000110);
}




void LCD_vidGoTo(u8 Copy_Row, u8 Copy_Column)
{
	if((Copy_Column >= 0) && (Copy_Column <= 15))
		{
			switch(Copy_Row)
			{
			case 0:
				LCD_vidSendCommand((0b10000000)+Copy_Column);
				break;
			case 1:
				LCD_vidSendCommand((0b11000000)+Copy_Column);
				break;
			default:
				// Wrong row Entry
				break;
			}
		}
		else
		{
			//Wrong column Entry
		}
}
