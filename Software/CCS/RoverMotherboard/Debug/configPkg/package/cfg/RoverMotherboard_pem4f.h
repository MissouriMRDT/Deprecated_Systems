/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A44
 */

#include <xdc/std.h>

#include <ti/sysbios/knl/Mailbox.h>
extern const ti_sysbios_knl_Mailbox_Handle fromBaseStationMailbox;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle roveTcpHandlerTask;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle roveCmdCntrlTask;

#include <ti/sysbios/knl/Mailbox.h>
extern const ti_sysbios_knl_Mailbox_Handle toBaseStationMailbox;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle roveTelemCntrlTask;

#define TI_DRIVERS_WIFI_INCLUDED 0

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

#ifndef ti_sysbios_knl_Task__include
#ifndef __nested__
#define __nested__
#include <ti/sysbios/knl/Task.h>
#undef __nested__
#else
#include <ti/sysbios/knl/Task.h>
#endif
#endif

extern ti_sysbios_knl_Task_Struct TSK_idle;

