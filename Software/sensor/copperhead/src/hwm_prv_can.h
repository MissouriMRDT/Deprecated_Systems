/*********************************************************************
*
*   HEADER NAME:
*       hwm_prv_can.h - Private declarations for CAN
*
* Copyright 2006-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/


#if !defined _HWM_PRV_CAN_H
#define _HWM_PRV_CAN_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "HWM_pub.h"

#include "hwm_prv_can_s.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

typedef uint8 hwm_can_cfg_t; enum
    {
    CFG_ID_BIT            = 0,
    CFG_RTR_BIT           = 1,

    CFG_USE_STANDARD      = 0,
    CFG_USE_EXTENDED      = (1 << CFG_ID_BIT),
    CFG_RTR_DATA          = 0,
    CFG_RTR_REMOTE_FRAME  = (1 << CFG_RTR_BIT)
    };

typedef uint8 hwm_can_mob_id_t; enum
    {
    MOB_0,
    MOB_1,
    MOB_2,
    MOB_3,
    MOB_4,
    MOB_5,
    MOB_6,
    MOB_7,
    MOB_8,
    MOB_9,
    MOB_10,
    MOB_11,
    MOB_12,
    MOB_13,
    MOB_14,
    MOB_15,
    MOB_16,
    MOB_17,
    MOB_18,
    MOB_19,
    MOB_20,
    MOB_21,
    MOB_22,
    MOB_23,
    MOB_24,
    MOB_25,
    MOB_26,
    MOB_27,
    MOB_28,
    MOB_29,
    MOB_30,
    MOB_31,

    NUM_MOB,

    MOB_INV = 0xFF
    };

typedef struct
    {
    hwm_can_cfg_t       cfg;            /* Std/Ext, etc. */
    HWM_can_id_t        ident;          /* Identifier */
    HWM_can_id_t        ident_msk;      /* Identifier Mask */
    uint8               dlc;            /* Data Length Code */
    uint8              *data;           /* Data */
    } hwm_can_mob_t;

typedef struct
    {
    hwm_can_mob_id_t    mob_id;         /* MOb number */
    HWM_can_id_t        ident;          /* Identifier */
    boolean             extended;       /* Is Extended? */
    boolean             dlcw;           /* Data length code warning */
    uint8               dlc;            /* Data length code */
    uint8               data[8];        /* Data */
    /*------------------------------------------------------
    Do NOT change this struct without verifying that
    hwm_can_isr.s still works. It fills bytes on receive.
    ------------------------------------------------------*/
    } hwm_can_rx_t;

typedef struct
    {
    HWM_can_id_t        ident;          /* Identifier */
    uint8               dlc;            /* Data length code */
    uint8               data[8];        /* Data */
    } hwm_can_tx_t;

typedef uint8 hwm_can_bus_status_t8;

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "hwm_prv_can_prj.h"
#include "hwm_prv_can_prj_s.h"

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/
extern hwm_can_bus_status_t8 hwm_can_tx_status;
extern uint8    mob_free[NUM_MOB];

extern unsigned int tx_count;
/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
CAN General Control Register - CANGCON
----------------------------------------------------------*/
#define hwm_can_reset()                 ( hwm_io_cangcon = hwm_CANGCON_SWRES_RESET )
#define hwm_can_enable()                                        \
    {                                                           \
    hwm_io_cangcon |= setbit(hwm_CANGCON_ENA_BIT);              \
    while( !(hwm_io_cangsta & setbit(hwm_CANGSTA_ENFG_BIT)) );  \
    }
#define hwm_can_disable()               ( hwm_io_cangcon &= clrbit(hwm_CANGCON_ENA_BIT) )

/*----------------------------------------------------------
CAN General Interrupt Enable Register - CANGIE
----------------------------------------------------------*/
#define hwm_can_enable_all_int()        ( hwm_io_cangie |= setbit(hwm_CANGIE_ENIT_BIT) )
#define hwm_can_disable_all_int()       ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENIT_BIT) )
#define hwm_can_enable_bus_off_int()    ( hwm_io_cangie |= setbit(hwm_CANGIE_ENBOFF_BIT) )
#define hwm_can_disable_bus_off_int()   ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENBOFF_BIT) )
#define hwm_can_enable_rx_int()         ( hwm_io_cangie |= setbit(hwm_CANGIE_ENRX_BIT) )
#define hwm_can_disable_rx_int()        ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENRX_BIT) )
#define hwm_can_enable_tx_int()         ( hwm_io_cangie |= setbit(hwm_CANGIE_ENTX_BIT) )
#define hwm_can_disable_tx_int()        ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENTX_BIT) )
#define hwm_can_enable_MOb_err_int()    ( hwm_io_cangie |= setbit(hwm_CANGIE_ENERR_BIT) )
#define hwm_can_disable_MOb_err_int()   ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENERR_BIT) )
#define hwm_can_enable_bx_int()         ( hwm_io_cangie |= setbit(hwm_CANGIE_ENBX_BIT) )
#define hwm_can_disable_bx_int()        ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENBX_BIT) )
#define hwm_can_enable_gen_err_int()    ( hwm_io_cangie |= setbit(hwm_CANGIE_ENERG_BIT) )
#define hwm_can_disable_gen_err_int()   ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENERG_BIT) )
#define hwm_can_enable_tmr_ovr_int()    ( hwm_io_cangie |= setbit(hwm_CANGIE_ENOVRT_BIT) )
#define hwm_can_disable_tmr_ovr_int()   ( hwm_io_cangie &= clrbit(hwm_CANGIE_ENOVRT_BIT) )

#define hwm_can_enable_ints()           ( hwm_io_cangie = setbit(hwm_CANGIE_ENIT_BIT)   | \
                                                          setbit(hwm_CANGIE_ENBOFF_BIT) | \
                                                          setbit(hwm_CANGIE_ENRX_BIT)   | \
                                                          setbit(hwm_CANGIE_ENTX_BIT)   | \
                                                          setbit(hwm_CANGIE_ENERR_BIT)  | \
                                                          setbit(hwm_CANGIE_ENERG_BIT) )

/*----------------------------------------------------------
CAN Interrupt Enable MOb Registers - CANIE2, CANIE1
----------------------------------------------------------*/
#define hwm_can_enable_MOb_int( mob_id )                    \
    ( ((uint8)mob_id > MOB_7) ? (hwm_io_canie1 |= (1<<((uint8)mob_id - MOB_8))) : (hwm_io_canie2 |= (1<<(uint8)mob_id)) )

/*----------------------------------------------------------
CAN Page MOb Register - CANPAGE
----------------------------------------------------------*/
#define hwm_can_get_mob()               ( hwm_io_canpage >> hwm_CANPAGE_MOBNB0_BIT )
#define hwm_can_set_mob(mob)            ( hwm_io_canpage = ((mob) << hwm_CANPAGE_MOBNB0_BIT) )
#define hwm_can_set_mob_imediate(mob)   ( hwm_io_canpage = (uint8)(mob) )

/*----------------------------------------------------------
CAN Highest Priority MOb Register - CANHPMOB
----------------------------------------------------------*/
#define hwm_can_get_mob_num()       ( hwm_io_canhpmob >> hwm_CANHPMOB_HPMOB0_BIT )  /* returns 0x0F if invalid */

/*----------------------------------------------------------
CAN MOb Contorl and DLC Register - CANCDMOB
----------------------------------------------------------*/
/* Data Length Code */
#define hwm_can_set_dlc(dlc)        ( hwm_io_cancdmob |= (uint8)(dlc & 0x0F) )
#define hwm_can_clear_dlc()         ( hwm_io_cancdmob &= ~hwm_CANCDMOB_DLC_MASK )
#define hwm_can_get_dlc()           ( (hwm_io_cancdmob & hwm_CANCDMOB_DLC_MASK) >> hwm_CANCDMOB_DLC0_BIT )

/* Identifier extension */
#define hwm_can_set_ide()           ( hwm_io_cancdmob |= setbit(hwm_CANCDMOB_IDE_BIT) )
#define hwm_can_clear_ide()         ( hwm_io_cancdmob &= clrbit(hwm_CANCDMOB_IDE_BIT) )
#define hwm_can_is_ext_id()         ( hwm_io_cancdmob & setbit(hwm_CANCDMOB_IDE_BIT) )

/* Reply Level */
#define hwm_can_set_rplv()          ( hwm_io_cancdmob |= setbit(hwm_CANCDMOB_RPLV_BIT) )
#define hwm_can_clear_rplv()        ( hwm_io_cancdmob &= clrbit(hwm_CANCDMOB_RPLV_BIT) )

#define hwm_can_get_mob_cfg()       ( hwm_io_cancdmob & hwm_CANCDMOB_CONMOB_DSBL_MSK )
#define DISABLE_MOB                 ( hwm_io_cancdmob &= ~hwm_CANCDMOB_CONMOB_DSBL_MSK )
#define hwm_can_mob_disable()       { DISABLE_MOB; }
#define hwm_can_mob_config_tx()     { DISABLE_MOB; hwm_io_cancdmob |= hwm_CANCDMOB_CONMOB_ENBL_TX; }
#define hwm_can_mob_config_rx()     { DISABLE_MOB; hwm_io_cancdmob |= hwm_CANCDMOB_CONMOB_ENBL_RX; }
#define hwm_can_config_rx_buffer()  {              hwm_io_cancdmob |= hwm_CANCDMOB_CONMOB_ENBL_FB; }

/*----------------------------------------------------------
CAN Identifier Tag Registers - CANIDTx
----------------------------------------------------------*/
#define hwm_can_set_std_id(identifier)  { *((hwm_ext_io_t16 *)&hwm_io_canidt2) = ((uint16)identifier << 5); \
                                          hwm_io_cancdmob &= clrbit(hwm_CANCDMOB_IDE_BIT);                  }

#define hwm_can_set_ext_id(identifier)  { *((hwm_ext_io_t32 *)&hwm_io_canidt4) = ((uint32)identifier << 3); \
                                          hwm_io_cancdmob |= setbit(hwm_CANCDMOB_IDE_BIT);                  }

/* Remote transmission request */
#define hwm_can_set_rtr()               ( hwm_io_canidt4 |= setbit(hwm_CANIDT4_RTRTAG_BIT) )
#define hwm_can_clear_rtr()             ( hwm_io_canidt4 &= clrbit(hwm_CANIDT4_RTRTAG_BIT) )

/* Remote transmission request mask */
#define hwm_can_set_rtrmsk()            ( hwm_io_canidm4 |= setbit(hwm_CANIDM4_RTRMSK_BIT) )
#define hwm_can_clear_rtrmsk()          ( hwm_io_canidm4 &= clrbit(hwm_CANIDM4_RTRMSK_BIT) )

/* Identifier mask */
#define hwm_can_set_idemsk()            ( hwm_io_canidm4 |= setbit(hwm_CANIDM4_IDEMSK_BIT) )
#define hwm_can_clear_idemsk()          ( hwm_io_canidm4 &= clrbit(hwm_CANIDM4_IDEMSK_BIT) )

/*----------------------------------------------------------
CAN Identifier MASK Registers - CANIDMx
----------------------------------------------------------*/
#define hwm_can_set_std_msk(mask)        { *((hwm_ext_io_t16 *)&hwm_io_canidm2) = ((uint16)mask << 5); }

#define hwm_can_set_ext_msk(mask)        { *((hwm_ext_io_t32 *)&hwm_io_canidm4) = ((uint32)mask << 3); }

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
hwm_can.c procedures
----------------------------------------------------------*/
void hwm_can_init( void );
void hwm_can_pwrdwn( void );
void hwm_can_pwrp( void );

#endif /* _HWM_PRV_CAN_H */
