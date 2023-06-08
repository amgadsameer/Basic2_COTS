#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

#if CLCD_u8CONNECTION_MODE  == FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D4_PIN, GET_BIT(copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D5_PIN, GET_BIT(copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D6_PIN, GET_BIT(copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D7_PIN, GET_BIT(copy_u8FourBitData,3));
}

#endif

static void voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_LOW);
}

void CLCD_voidSendCommand(uint8 copy_u8Command)
{
	/*1- Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_LOW);

	/*2- Set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE  == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

	/*3- Send the command*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, copy_u8Command);

	/* Send enable pulse*/
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT

	/*Send the higher 4 bits of the command*/
	voidSetHalfDataPort(copy_u8Command >> 4u);
	/* Send enable pulse*/
	voidSendEnablePulse();

	/*Send the lower 4 bits of the command*/
	voidSetHalfDataPort(copy_u8Command);
	/* Send enable pulse*/
	voidSendEnablePulse();
#endif
}
void CLCD_voidSendData(uint8 copy_u8Data)
{
	/*1- Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_HIGH);

	/*2- Set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE  == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

	/*3- Send the data*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, copy_u8Data);

	/* Send enable pulse*/
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT

	/*Send the higher 4 bits of the data*/
	voidSetHalfDataPort(copy_u8Data >> 4u);
	/* Send enable pulse*/
	voidSendEnablePulse();

	/*Send the lower 4 bits of the data*/
	voidSetHalfDataPort(copy_u8Data);
	/* Send enable pulse*/
	voidSendEnablePulse();
#endif
}
void CLCD_voidInit(void)
{
	/*1- Wait for more than 30ms after poweron*/
	_delay_ms(40);

	/*2- Function set command: 2 lines, font size 5x7*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif

	/*3- Display on/off control: Display on, cursor off, blink cursor off*/
	CLCD_voidSendCommand(0b00001100);

	/*4- Display clear*/
	CLCD_voidSendCommand(1);
}

void CLCD_voidWriteNumber(sint32 copy_s32Number)
{
	char Local_chNumber[10];
	uint8 Local_u8RightDigit, Local_u8Counter1=0;
	sint8 Local_s8Counter2;
	if(copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(copy_s32Number < 0)
	{
		/*Number is negative, print -ve sign*/
		CLCD_voidSendData('-');
		copy_s32Number *= -1;
	}

	while(copy_s32Number != 0)
	{
		Local_u8RightDigit = copy_s32Number % 10; /*Get the right most digit*/
		copy_s32Number /= 10;					/*Get rid of the right most digit*/
		Local_chNumber[Local_u8Counter1] = Local_u8RightDigit + '0';
		Local_u8Counter1++;
	}

	for(Local_s8Counter2 = (sint8)Local_u8Counter1 -1 ; Local_s8Counter2 >= 0 ; Local_s8Counter2-- )
	{
		CLCD_voidSendData(Local_chNumber[(uint8)Local_s8Counter2]);
	}
	
}

void CLCD_voidGoToXY(uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8DDRamAdd = (copy_u8YPos * 0x40u) + copy_u8XPos;

	/*if (copy_YPos == 0u)
	 * {
	 * 		Local_u8DDRamAdd = copy_u8XPos;
	 * }
	 * else
	 * {
	 * 		Local_u8DDRamAdd = 0x40u + copy_u8XPos;
	 * }
	 * */

	/*Set bit 7 for Setting DDRAM address command*/
	SET_BIT(Local_u8DDRamAdd,7u);

	/*send the setting DDRAM address command*/
	CLCD_voidSendCommand(Local_u8DDRamAdd);
}

uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_u8PatternNumber,uint8 copy_pu8PatternArr[],uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8ErrorStatus = OK;

	if(copy_pu8PatternArr != NULL)
	{
		uint8 Local_u8CGRAMAdd = copy_u8PatternNumber * 8u;
		uint8 Local_u8Iterator;

		/*Set bit6 clear bit7 for setting CGRAM address command*/
		SET_BIT(Local_u8CGRAMAdd ,6u);

		/*Set CGRAM address*/
		CLCD_voidSendCommand(Local_u8CGRAMAdd);

		/*write the pattern inside CGRAM*/
		for(Local_u8Iterator=0u; Local_u8Iterator<8u; Local_u8Iterator++)
		{
			CLCD_voidSendData(copy_pu8PatternArr[Local_u8Iterator]);
		}

		/*Set DDRAM address*/
		CLCD_voidGoToXY(copy_u8XPos,copy_u8YPos);

		/*Write the corresponding pattern number to display from CGRAM*/
		CLCD_voidSendData(copy_u8PatternNumber);
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}
