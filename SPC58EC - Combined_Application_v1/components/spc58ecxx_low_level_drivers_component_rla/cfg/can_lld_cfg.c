/****************************************************************************
*
* Copyright © 2015-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

/**
 * @file    can_lld_cfg.c
 * @brief   CAN Driver configuration code.
 *
 * @addtogroup CAN
 * @{
 */
 
#include "can_lld_cfg.h"

#if (LLD_USE_CAN == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   Structure defining the CAN configuration "mcanconf".
 */
CANConfig can_config_mcanconf = {
  /* loopback */
  CAN_NO_LOOPBACK,
  /* endianness */
  CAN_LITTLE_ENDIAN,
  /* sync jump width */ 
  3U,  
  /* time segment before sample point */
  10U,
  /* time segment after sample point */
  3U,
  /* clock prescaler */
  1U,
  
  /* Canfd configuration */
  FALSE,
  /* canfd bit rate switch */
  FALSE,
   /* sync jump width */ 
  1U,  
  /* time segment before sample point */
  1U,
  /* time segment after sample point */
  0U,
  /* clock prescaler */
  1U,
  /* transceiver delay compensation enabled */
  FALSE,
  /* transmitter delay compensation value */
  0U,
  /* transmitter delay compensation offset */
  0U,
  /* transmitter delay compensation filter window length */
  0U,

  /*can rx interrupt line*/
  CAN_LINE0_INT,
  /*can rx interrupt call back */
  NULL,
  /* FIFO 0 interrupt line */
  CAN_LINE0_INT,
  /*FIFO 0 new message interrupt*/
  CAN_INTERRUPT_ENABLED,
  /*FIFO 0 new message interrupt call back */
  NULL,
  /*FIFO 0 watermark interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
  /*FIFO 0 fifo full interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
   /*FIFO 0 fifo lost interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
  /* FIFO 1 interrupt line */
  CAN_LINE0_INT,
  /*FIFO 1 new message interrupt*/
  CAN_INTERRUPT_ENABLED,
  /*FIFO 1 new message interrupt call back */
  NULL,
  /*FIFO 1 watermark interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
  /*FIFO 1 fifo full interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
   /*FIFO 1 fifo lost interrupt*/
  CAN_INTERRUPT_DISABLED, NULL,
  /* rx standard buffer filters */
  {
  {0x7fUL,12UL,0U,7U}, /* standard filter 0*/
  {0xfUL,0x7fUL,CAN_FILTER_RANGE,CAN_FIFO0}, /* standard filter 1*/
  {0xfUL,0x7fUL,CAN_FILTER_RANGE,CAN_FIFO1}, /* standard filter 2*/
  {0UL,0UL,0U,0U},  /* standard_filter unused 0 (MISRA Compliance) */
  {0UL,0UL,0U,0U},  /* standard_filter unused 1 (MISRA Compliance) */
  },
    /* rx extended buffer filters */
  {
  {0UL,0UL,0U,0U},  /* extended_filter unused 0 (MISRA Compliance) */
  {0UL,0UL,0U,0U},  /* extended_filter unused 1 (MISRA Compliance) */
  },
/* number of standard filters */
  3U,
/* number of extended filters */
  0U,
  /* number of Rx Buffers */
  32U,
/* number of FIFO 0 Buffers */
  16U,
/* number of FIFO 1 Buffers */
  16U,
/* Transmission Mode */
  CAN_DEDICATED_TXBUFFER,
/* number of Tx Buffers */
  16U,
/* number of FIFO or QUEUE Tx Buffers */
  8U,
/* Error Callback*/
  NULL,
};

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

#endif /* LLD_USE_CAN */

/** @} */
