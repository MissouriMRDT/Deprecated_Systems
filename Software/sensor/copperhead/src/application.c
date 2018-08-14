/*
===============================================================================
 Name        : application.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include "IOP_pub.h"
#include "NVM_pub.h"
#include <cr_section_macros.h>

int main(void)
    {
	NVM_pwrp();
	hwm_timer_pwrp();
	hwm_can_pwrp();
	IOP_pwrp();

	hwm_timer_init();
	HWM_adc_init();
	hwm_can_init();
	IOP_init();
	heading_init();

    while(1)
        {
        HWM_adc_tsk();
        HWM_can_tsk();
        IOP_main_tsk();
        }
    return 0 ;
    }
