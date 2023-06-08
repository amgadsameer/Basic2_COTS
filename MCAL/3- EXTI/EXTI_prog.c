#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "EXTI_interface.h"
#include "EXTI_prv.h"
#include "EXTI_cfg.h"
#include "EXTI_reg.h"

static void (*EXTI_pfFuncPtr[3])(void)= {NULL,NULL,NULL};


void EXTI_voidInit(void)
{
#if EXTI_u8INT0_TRIG_SRC == LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG_SRC == ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG_SRC == FALLING_EDGE
	CLR_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);
#elif EXTI_u8INT0_TRIG_SRC == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);
#else
#error "Wrong EXTI_u8INT0_TRIG_SRC configuration option"
#endif

#if EXTI_u8INT1_TRIG_SRC == LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);
#elif EXTI_u8INT1_TRIG_SRC == ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);
#elif EXTI_u8INT1_TRIG_SRC == FALLING_EDGE
	CLR_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);
#elif EXTI_u8INT1_TRIG_SRC == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);
#else
#error "Wrong EXTI_u8INT1_TRIG_SRC configuration option"
#endif


#if EXTI_u8INT2_TRIG_SRC == FALLING_EDGE
	CLR_BIT(MCUCSR, MCUCSR_ISC2);
#elif EXTI_u8INT2_TRIG_SRC == RISING_EDGE
	SET_BIT(MCUCSR, MCUCSR_ISC2);
#else
#error "Wrong EXTI_u8INT2_TRIG_SRC configuration option"
#endif

#if EXTI_u8INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#elif EXTI_u8INT0_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#else
#error "Wrong EXTI_u8INT0_INIT_STATE configuration option"
#endif

#if EXTI_u8INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#elif EXTI_u8INT1_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#else
#error "Wrong EXTI_u8INT1_INIT_STATE configuration option"
#endif

#if EXTI_u8INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#elif EXTI_u8INT2_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#else
#error "Wrong EXTI_u8INT2_INIT_STATE configuration option"
#endif

}

uint8 EXTI_u8SetSenseCtrl(EXTI_IntNum_t copy_IntNum, uint8 copy_u8SenseCtrl)
{
	uint8 Local_u8ErrorState = OK;

	if (copy_IntNum == INT0)
	{
		switch(copy_u8SenseCtrl)
		{
		case LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case FALLING_EDGE:	CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		case RISING_EDGE: 	SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}
	else if (copy_IntNum == INT1)
	{
		switch(copy_u8SenseCtrl)
		{
		case LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case FALLING_EDGE:	CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case RISING_EDGE: 	SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}
	else if (copy_IntNum == INT2)
	{
		switch(copy_u8SenseCtrl)
		{
		case FALLING_EDGE:	CLR_BIT(MCUCSR, MCUCSR_ISC2); break;
		case RISING_EDGE: 	SET_BIT(MCUCSR, MCUCSR_ISC2); break;
		default : Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8IntEnable(EXTI_IntNum_t copy_IntNum)
{
	uint8 Local_u8ErrorState = OK;

	switch(copy_IntNum)
	{
	case INT0:	SET_BIT(GICR,GICR_INT0); break;
	case INT1:	SET_BIT(GICR,GICR_INT1); break;
	case INT2:	SET_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8IntDisable(EXTI_IntNum_t copy_IntNum)
{
	uint8 Local_u8ErrorState = OK;

	switch(copy_IntNum)
	{
	case INT0:	CLR_BIT(GICR,GICR_INT0); break;
	case INT1:	CLR_BIT(GICR,GICR_INT1); break;
	case INT2:	CLR_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8SetCallBack(EXTI_IntNum_t copy_IntNum, void(*copy_pvFuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	if(copy_pvFuncPtr != NULL)
	{
		if((copy_IntNum >= INT0) && (copy_IntNum<= INT2))
		{
			EXTI_pfFuncPtr[copy_IntNum] = copy_pvFuncPtr;
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

/*INT0 ISR*/
void __vector_1 (void)		__attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pfFuncPtr[INT0] != NULL)
	{
		EXTI_pfFuncPtr[INT0]();
	}
	else
	{
		/*Do nothing*/
	}
}

/*INT1 ISR*/
void __vector_2 (void)		__attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pfFuncPtr[INT1] != NULL)
	{
		EXTI_pfFuncPtr[INT1]();
	}
	else
	{
		/*Do nothing*/
	}
}


/*INT2 ISR*/
void __vector_3 (void)		__attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pfFuncPtr[INT2] != NULL)
	{
		EXTI_pfFuncPtr[INT2]();
	}
	else
	{
		/*Do nothing*/
	}
}

