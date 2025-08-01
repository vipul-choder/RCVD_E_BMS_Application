/****************************************************************************
*
* Copyright © 2018-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/
/**
 * @file    wkpu_lld_cfg.c
 * @brief   WKPU Driver configuration code.
 *
 * @addtogroup WKPU
 * @{
 */

#include "wkpu_lld_cfg.h"

#if (LLD_USE_WKPU == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   Structure defining the configuration "wkpu_config_wkpu_cfg_wk_INT28"
 *          for source INT28.
 */
WakeupConfig wkpu_config_wkpu_cfg_wk_INT28 = {
  FALSE,
  TRUE,
  NULL,
  FALSE,
  TRUE,
  FALSE,
  FALSE
};
  
/**
 * @brief   Structure defining the configuration "wkpu_config_wkpu_cfg".
 */
WKPUConfig wkpu_config_wkpu_cfg = {
  {
    NULL,
    NULL,
    NULL,
    NULL
  },
  {
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      &wkpu_config_wkpu_cfg_wk_INT28,
      NULL,
      NULL,
      NULL,
  }
};

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

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

#endif /* LLD_USE_WKPU */

/** @} */
