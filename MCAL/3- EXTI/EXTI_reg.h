#ifndef EXTI_REG_H
#define EXTI_REG_H

#define MCUCR			*((volatile uint8*)0x55)		/*MCU ctrl register*/
#define MCUCR_ISC00 	0U								/*Int. Sense Ctrl 0 bit 0*/
#define MCUCR_ISC01		1U								/*Int. Sense Ctrl 0 bit 1*/
#define MCUCR_ISC10		2U                              /*Int. Sense Ctrl 1 bit 0*/
#define MCUCR_ISC11		3U                              /*Int. Sense Ctrl 1 bit 1*/

#define MCUCSR			*((volatile uint8*)0x54)		/*MCU ctrl an status register*/
#define MCUCSR_ISC2		6U								/*Int. Sense Ctrl 2*/


#define GICR			*((volatile uint8*)0x5B)		/*General Int. ctrl register*/
#define GICR_INT1		7u								/*Interrupt 1*/
#define GICR_INT0		6u                              /*Interrupt 0*/
#define GICR_INT2		5u                              /*Interrupt 2*/

#endif