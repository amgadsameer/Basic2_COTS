#include "STD_TYPES.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_prv.h"
#include "KPD_cfg.h"

uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8RowCounter, Local_u8ColCounter, Local_u8KeyState,Local_u8PressedKey= KPD_u8NO_PRESSED_KEY_VAL;

	static uint8 Local_u8ColArr[COL_NUM]= {KPD_u8C0_PIN,KPD_u8C1_PIN,KPD_u8C2_PIN,KPD_u8C3_PIN};
	static uint8 Local_u8RowArr[ROW_NUM]= {KPD_u8R0_PIN,KPD_u8R1_PIN,KPD_u8R2_PIN,KPD_u8R3_PIN};
	static uint8 Local_u8KPDArr[ROW_NUM][COL_NUM] = KPD_u8BUTTON_ARR;

	/*Activate the column pins*/
	for(Local_u8ColCounter =0u ; Local_u8ColCounter < COL_NUM ; Local_u8ColCounter++)
	{
		/*Activate he current column*/
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_LOW);

		/*Read the row pins*/
		for(Local_u8RowCounter =0u; Local_u8RowCounter< ROW_NUM; Local_u8RowCounter++)
		{
			/*Read the current row*/
			DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);

			if(Local_u8KeyState == DIO_PIN_LOW)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];

				/*wait until key is released (polling with blocking on pin reading)*/
				while(Local_u8KeyState == DIO_PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				}

				return Local_u8PressedKey;
			}
		}
		/*Deactivate the current column*/
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_HIGH);
	}
	return Local_u8PressedKey;
}
