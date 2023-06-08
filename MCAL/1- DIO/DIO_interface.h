#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

typedef enum
{
	DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
}DIO_Port_t;

typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}DIO_Pin_t;

typedef enum
{
	DIO_PIN_INPUT,
	DIO_PIN_OUTPUT
}DIO_PinDir_t;

typedef enum
{
	DIO_PIN_LOW,
	DIO_PIN_HIGH
}DIO_PinVal_t;

uint8 DIO_u8SetPinDirection(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum, DIO_PinDir_t copy_Dir);
uint8 DIO_u8SetPortDirection(DIO_Port_t copy_Port, uint8 copy_u8PortDir);

uint8 DIO_u8SetPinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum, DIO_PinVal_t copy_Val);
uint8 DIO_u8SetPortValue(DIO_Port_t copy_Port, uint8 copy_u8PortVal);

uint8 DIO_u8GetPinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum, DIO_PinVal_t* copy_pVal);

uint8 DIO_u8TogglePinValue(DIO_Port_t copy_Port, DIO_Pin_t copy_PinNum);

#endif
