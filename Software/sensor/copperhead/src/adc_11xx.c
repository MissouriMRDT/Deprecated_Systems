/*
 * @brief LPC11xx ADC example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "HWM_pub_adc.h"
#include "SYC_pub.h"

#if !defined(CHIP_LPC1125)

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define ADC_TASK_PERIOD     100 /* ms */

static void Init_ADC_PinMux(void);

static uint8 adc_buff_count;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
uint16_t adc_value_buff[ADC_BUFF_SIZE];
/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void Init_ADC_PinMux(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_10, FUNC1);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for ADC example
 * @return	Function should not exit
 */
void HWM_adc_init(void)
{
    ADC_CLOCK_SETUP_T ADCSetup;

	memset( &adc_value_buff, 0, sizeof( adc_value_buff ) );
	adc_buff_count = 0;

	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	SystemCoreClockUpdate();
	Init_ADC_PinMux();

	/* ADC Init */
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH6, ENABLE);

	/* Enable Interrupt for channel 0 */
	NVIC_EnableIRQ(ADC_IRQn);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH6, ENABLE);


	SYC_set_timer_expired(SYC_TIMER_ADC_READ);
}

void HWM_adc_tsk(void)
{
	if( SYC_is_timer_expired(SYC_TIMER_ADC_READ) == TRUE )
	{
		/* Start A/D conversion */
		Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		SYC_set_timer(SYC_TIMER_ADC_READ, ADC_TASK_PERIOD);
	}
}

void ADC_IRQHandler(void)
{
    uint16_t dataADC;
	/* Read ADC value */
	if( Chip_ADC_ReadValue(LPC_ADC, ADC_CH6, &dataADC) )
		{
		adc_value_buff[adc_buff_count] = dataADC;
		adc_buff_count++;
		adc_buff_count %= ADC_BUFF_SIZE;
		}
}

#endif /* !defined(CHIP_LPC1125) */
