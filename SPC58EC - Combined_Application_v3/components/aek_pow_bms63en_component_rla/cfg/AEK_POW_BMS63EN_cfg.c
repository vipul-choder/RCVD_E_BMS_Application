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
 * @file    AEK_POW_BMS63EN_cfg.c
 * @brief   AEK_POW_BMS63EN Driver configuration code.
 *
 * @addtogroup AEK_POW_BMS63EN_CFG
 * @{
 */


#include "AEK_POW_BMS63EN_cfg.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

#include "spi_lld_cfg.h"


/* List of the L9963 Driver cell status structures. */
static AEK_POW_BMS63EN_cell_stack_state_t AEK_POW_BMS63EN_cell_stack_state_dev1 = {
	    { AEK_POW_BMS63EN_CELL1, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL2, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL3, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL4, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL5, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL6, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL7, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL8, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL9, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL10, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL11, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL12, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL13, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL14, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN }
};	
static AEK_POW_BMS63EN_cell_stack_state_t AEK_POW_BMS63EN_cell_stack_state_dev2 = {
	    { AEK_POW_BMS63EN_CELL1, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL2, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL3, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL4, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL5, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL6, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL7, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL8, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL9, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL10, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL11, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL12, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL13, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN },
	    { AEK_POW_BMS63EN_CELL14, AEK_POW_BMS63EN_CELL_CONNECTED, AEK_POW_BMS63EN_CELL_ENABLED, AEK_POW_BMS63EN_CELL_PCB_UNKNOWN }
};	

/* List of the AEK_POW_BMS63EN Driver status structures. */
static AEK_POW_BMS63EN_dev_status_t AEK_POW_BMS63EN_dev_status[] = {
		  {AEK_POW_BMS63EN_DEVICE1,  AEK_POW_BMS63EN_RESET,  &AEK_POW_BMS63EN_cell_stack_state_dev1},
		  {AEK_POW_BMS63EN_DEVICE2,  AEK_POW_BMS63EN_RESET,  &AEK_POW_BMS63EN_cell_stack_state_dev2}
};

static AEK_POW_BMS63EN_status_t AEK_POW_BMS63EN_status = {
		AEK_POW_BMS63EN_UNINIT,
		AEK_POW_BMS63EN_dev_status
};

/* List of the AEK_POW_BMS63EN Driver parameter structures. */
static AEK_POW_BMS63EN_ParamConf AEK_POW_BMS63EN_ParamConf_dev[] = {
		 {60000,
		  11000,
		  5100,
		  500, 
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_RATIOMETRIC,
		  AEK_POW_BMS63EN_cell_tim_bal_mode,
		  AEK_POW_BMS63EN_adc_flt_soc_290us,
		  AEK_POW_BMS63EN_CoulombCounting_Enabled,
		  AEK_POW_BMS63EN_iso_freq_high,
		   AEK_POW_BMS63EN_commtimeout_2048ms ,
		  AEK_POW_BMS63EN_VTREF_ALWAYS_ENABLED  
		  }
		  ,
		 {60000,
		  11000,
		  5100,
		  500, 
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  1200,
		  5000,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_gpio_analog_input,
		  AEK_POW_BMS63EN_RATIOMETRIC,
		  AEK_POW_BMS63EN_cell_man_bal_mode,
		  AEK_POW_BMS63EN_adc_flt_soc_290us,
		  AEK_POW_BMS63EN_CoulombCounting_Enabled,
		  AEK_POW_BMS63EN_iso_freq_high,
		   AEK_POW_BMS63EN_commtimeout_2048ms ,
		  AEK_POW_BMS63EN_VTREF_ALWAYS_ENABLED  
		  }
		  
};


/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/* List of the AEK_POW_BMS63EN_Driver structures. */
/**
 * @brief   Structure defining the L9963 L9963D instance.
 */
AEK_POW_BMS63EN_Driver AEK_POW_BMS63EN_Drv = {
  &AEK_POW_BMS63EN_status,
  NULL,
  AEK_POW_BMS63EN_ParamConf_dev
};


 /* List of the L9963Config structures. */
/**
 * @brief   Structure defining the L9963 configuration "l9963_config".
 */
 
 
 


		
 
AEK_POW_BMS63EN_Config AEK_POW_BMS63EN_config = {
  &SPID1,
  &spi_config_spi_config_AEK_COM_ISOSPI1_dev0,
  NULL,
  NULL
};

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 *    This function initializes all the configured driver instances.
**/
void AEK_POW_BMS63EN_cfg_objects_init(void) {
	AEK_POW_BMS63EN_ObjectInit(&AEK_POW_BMS63EN_Drv);
}

#endif

/** @} */
