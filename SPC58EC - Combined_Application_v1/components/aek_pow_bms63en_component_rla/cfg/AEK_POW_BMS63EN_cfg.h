/***********************************************************************************
*
* Copyright © 2020, 2022 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms at www.st.com/SLA0098 
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY
*
************************************************************************************/



/**
 * @file    AEK_POW_BMS63EN_id_cfg.h
 * @brief   AEK_POW_BMS63EN Driver exported configuration settings.
 *
 * @addtogroup AEK_POW_BMS63EN_CFG
 * @{
 */

#ifndef _AEK_POW_BMS63EN_CFG_H_
#define _AEK_POW_BMS63EN_CFG_H_

#define AEK_COM_ISOSPI1_ALLOCATED

#ifdef AEK_COM_ISOSPI1_ALLOCATED

#include "AEK_POW_BMS63EN_lld.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/


/**
 * @brief   AEK_POW_BMS63EN_Driver BMS Devices allocated
 */
#define AEK_POW_BMS63EN_N_BMS 1

#define AEK_POW_BMS63EN_N_TRANCEIVER 1

extern AEK_POW_BMS63EN_Driver AEK_POW_BMS63EN_Drv;
extern AEK_POW_BMS63EN_Config AEK_POW_BMS63EN_config;

void AEK_POW_BMS63EN_cfg_objects_init(void);
#endif

#endif /* _AEK_POW_BMS63EN_CFG_H_ */

/** @} */
