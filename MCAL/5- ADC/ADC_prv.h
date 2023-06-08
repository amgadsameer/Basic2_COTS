#ifndef ADC_PRV_H
#define ADC_PRV_H

#define PREASCALER_MASK			0b11111000

#define CHANNEL_SELECTION_MASK	0b11100000

#define EIGHT_BITS			1u
#define TEN_BITS			2u


#define DIVISION_BY_2		0u
#define DIVISION_BY_4		2u
#define DIVISION_BY_8		3u
#define DIVISION_BY_16		4u
#define DIVISION_BY_32		5u
#define DIVISION_BY_64		6u
#define DIVISION_BY_128		7u

#define IDLE				0u
#define BUSY				1u


#endif
