#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

typedef enum
{
	ADC0_SINGLE_ENDED=0,
	ADC1_SINGLE_ENDED,
	ADC2_SINGLE_ENDED,
	ADC3_SINGLE_ENDED,
	ADC4_SINGLE_ENDED,
	ADC5_SINGLE_ENDED,
	ADC6_SINGLE_ENDED,
	ADC7_SINGLE_ENDED,
	ADC0_POS_ADC0_NEG_10x_GAIN,
	ADC1_POS_ADC0_NEG_10x_GAIN
}ADC_Channel_t;


typedef struct
{
	uint8 ConversionsNum;
	ADC_Channel_t* ChannelArr;
	uint16* ResultArr;
	void(*NotificationFunc)(void);

}ADC_Chain_t;

void ADC_voidInit(void);

uint8 ADC_u16StartSingleConversionSynch(ADC_Channel_t copy_Channel, uint16* copy_pu16DigResult);

uint8 ADC_u16StartSingleConversionAsynch(ADC_Channel_t copy_Channel, uint16* copy_pu16DigResult,void (*copy_pvNotificationFunc)(void));

uint8 ADC_u8StartChainConversionAsynch(const ADC_Chain_t* copy_ChainData);

#endif
