/****************************************************************************
*
* Copyright © 2021 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0098 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY - NOT FOR USE IN PRODUCTION
*****************************************************************************/


/**  
 * @file    AEK_COM_ISOSPI1_cfg.c
 * @brief   AEK_COM_ISOSPI Driver configuration macros and structures.
 *
 * @addtogroup AEK_COM_ISOSPI1
 * @{
 */ 

#ifndef _AEK_COM_ISOSPI1_CFG_C_
#define _AEK_COM_ISOSPI1_CFG_C_

#include "AEK_COM_ISOSPI1_cfg.h"
#include "spi_lld_cfg.h"
#include "board.h"
#define L9963T_CHANNEL 7




static ISOSPI_pad_list_t isospi_pad_list_dev_0[L9963T_CHANNEL] = { 
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_DIS_GPIO1, PIN_AEK_COM_ISOSPI1Board0_CN2_DIS_GPIO1},
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_BNECPOL_GPIO2, PIN_AEK_COM_ISOSPI1Board0_CN2_BNECPOL_GPIO2 }, 
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_TXENCPHA_GPIO3, PIN_AEK_COM_ISOSPI1Board0_CN2_TXENCPHA_GPIO3 },   
			        { PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_FREQ_GPIO4, PIN_AEK_COM_ISOSPI1Board0_CN2_FREQ_GPIO4 }, 
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_NSLAVE_GPIO9, PIN_AEK_COM_ISOSPI1Board0_CN2_NSLAVE_GPIO9 },  
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_TXAMP_GPIO8, PIN_AEK_COM_ISOSPI1Board0_CN2_TXAMP_GPIO8 },  
				{ PORT_PIN_AEK_COM_ISOSPI1Board0_CN2_FAULT_EIRQ2, PIN_AEK_COM_ISOSPI1Board0_CN2_FAULT_EIRQ2}
};

ISOSPI_Driver_t AEK_ISOSPI_ARRAY_DRIVER[1]={
  {
	ISOSPI_DEV0,
	&isospi_pad_list_dev_0[0],
			L9963T_MODE_SLAVE,
					L9963T_ISO_FREQ_LOW,
			L9963T_TX_AMP_LOW,
			L9963T_MASTER_CPOL_LOW,
			L9963T_MASTER_CPHA_LOW,
			&SPID1,
		&spi_config_spi_config_AEK_COM_ISOSPI1_dev0,
	L9963T_FAULT_NOT_ACTIVE
 }
};



void AEK_COM_ISOSPI1Board0_CN2_FAULT_callback(void){	
	 if(AEK_ISOSPI_ARRAY_DRIVER[ISOSPI_DEV0].ISOSPI_fault_sts == L9963T_FAULT_NOT_ACTIVE) AEK_ISOSPI_ARRAY_DRIVER[ISOSPI_DEV0].ISOSPI_fault_sts = L9963T_FAULT_ACTIVE;
	 else AEK_ISOSPI_ARRAY_DRIVER[ISOSPI_DEV0].ISOSPI_fault_sts = L9963T_FAULT_NOT_ACTIVE;
}



#endif /* _AEK_COM_ISOSPI1_CFG_C_ */

/** @} */

