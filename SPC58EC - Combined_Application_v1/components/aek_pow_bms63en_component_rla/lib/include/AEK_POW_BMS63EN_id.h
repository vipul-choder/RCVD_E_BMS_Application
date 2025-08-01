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
 * @file    AEK_POW_BMS63EN_id.h
 * @brief   AEK_POW_BMS63EN Driver macros and structures.
 *
 * @addtogroup AEK_POW_BMS63EN_ID
 * @{
 */

#ifndef _AEK_POW_BMS63EN_ID_H_
#define _AEK_POW_BMS63EN_ID_H_

#include "AEK_POW_BMS63EN_cfg.h"
#include "AEK_POW_BMS63EN_diag.h"
#include "AEK_POW_BMS63EN_registry.h"
#include "AEK_COM_ISOSPI1_lld.h"
#include "AEK_POW_BMS63EN_lld.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/


/**
 * @brief   AEK_POW_BMS63EN Conversion measurement option identifier.
 */
typedef enum{
	AEK_POW_BMS63EN_ABS_MODE = 0,
	AEK_POW_BMS63EN_RATIO_MODE = 1
}AEK_POW_BMS63EN_ratio_abs_mode_t;

/**
 * @brief   AEK_POW_BMS63EN ADCV CONV option identifier.
 */
typedef enum{
	AEK_POW_BMS63EN_GPIO_CONV_DIS = 0,
	AEK_POW_BMS63EN_GPIO_CONV_EN = 1,
	AEK_POW_BMS63EN_GPIO_TERM_CONV_DIS = 2,
	AEK_POW_BMS63EN_GPIO_TERM_CONV_EN = 3,
	AEK_POW_BMS63EN_CELL_TERM_CONV_DIS = 4,
	AEK_POW_BMS63EN_CELL_TERM_CONV_EN = 5,
	AEK_POW_BMS63EN_BAL_TERM_CONV_DIS = 6,
	AEK_POW_BMS63EN_BAL_TERM_CONV_EN = 7,
	AEK_POW_BMS63EN_HWSC_DIS = 8,
	AEK_POW_BMS63EN_HWSC_EN = 9,
	AEK_POW_BMS63EN_ADC_CROSS_CHECK_DIS = 10,
	AEK_POW_BMS63EN_ADC_CROSS_CHECK_EN = 11
}AEK_POW_BMS63EN_adcv_conv_opt_t;

/**
 * @brief   AEK_POW_BMS63EN ADC cyclic conversion period.
 */
typedef enum {
        AEK_POW_BMS63EN_adc_conv_tcycle_100ms,    /**< t_cycle = 100 ms           */
        AEK_POW_BMS63EN_adc_conv_tcycle_200ms,    /**< t_cycle = 200 ms           */
        AEK_POW_BMS63EN_adc_conv_tcycle_400ms,    /**< t_cycle = 400 ms           */
        AEK_POW_BMS63EN_adc_conv_tcycle_800ms,    /**< t_cycle = 800 ms           */
        AEK_POW_BMS63EN_adc_conv_tcycle_1s6,      /**< t_cycle = 1 s and 600 ms   */
        AEK_POW_BMS63EN_adc_conv_tcycle_3s2,      /**< t_cycle = 3 s and 200 ms   */
        AEK_POW_BMS63EN_adc_conv_tcycle_6s4,      /**< t_cycle = 6 s and 400 ms   */
        AEK_POW_BMS63EN_adc_conv_tcycle_12s8      /**< t_cycle = 12 s and 8000 ms */
} AEK_POW_BMS63EN_adc_conv_tcycle_t;


/**
 * @brief   AEK_POW_BMS63EN ADC filter soc period.
 */
typedef enum {
        AEK_POW_BMS63EN_adc_filter_soc_290us = 0,     /**< filter_soc = 290 us             */
        AEK_POW_BMS63EN_adc_filter_soc_1ms16 = 1,     /**< filter_soc = 1 ms and 160 us    */
        AEK_POW_BMS63EN_adc_filter_soc_2ms32 = 2,     /**< filter_soc = 2 ms and 320 us    */
        AEK_POW_BMS63EN_adc_filter_soc_9ms28 = 3,     /**< filter_soc = 9 ms and 280 us    */
        AEK_POW_BMS63EN_adc_filter_soc_18ms56 = 4,    /**< filter_soc = 18 ms and 560 ms   */
        AEK_POW_BMS63EN_adc_filter_soc_37ms12 = 5,    /**< filter_soc = 37 ms and 120 us   */
        AEK_POW_BMS63EN_adc_filter_soc_74ms24 = 6,    /**< filter_soc = 74 ms and 240 us   */
        AEK_POW_BMS63EN_adc_filter_soc_148ms48 = 7    /**< filter_soc = 148 ms and 480 us  */
} AEK_POW_BMS63EN_adc_filter_soc_t;


/**
 * @brief   AEK_POW_BMS63EN cell balancing mode.
 */
typedef enum {

        AEK_POW_BMS63EN_cell_manual_bal_mode = 1,     /**< manual balancing mode  */
        AEK_POW_BMS63EN_cell_timed_bal_mode = 2       /**< timed balancing mode   */
} AEK_POW_BMS63EN_cell_bal_mode_t;




/**
 * @brief   AEK_POW_BMS63EN cell balancing status.
 */
typedef enum {
        AEK_POW_BMS63EN_bal_status_idle = 0,        /**< 'Idle' balancing status  */
        AEK_POW_BMS63EN_bal_status_over = 1,        /**< 'Over' balancing status (waiting for the 'stop' command) */
        AEK_POW_BMS63EN_bal_status_ongoing = 2,     /**< 'Ongoing' balancing status   */
        AEK_POW_BMS63EN_bal_status_impossible = 3   /**< Unpredicted balancing status */
} AEK_POW_BMS63EN_bal_status_t;


/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/


  /* * * * * * * * * * * * * * * * * * * * */
  /*   G e n e r a l   F u n c t i o n s   */
  /* * * * * * * * * * * * * * * * * * * * */
/**
 * @name    General Porpouse Functions
 * @{  
 */       
  
  /**
  * @brief  AEK_POW_BMS63EN Driver instance(s) initialization.
  *
  * @init
  */
  void AEK_POW_BMS63EN_Init( void );

  /**
  * @brief  AEK_POW_BMS63EN Driver instance(s) Parameter Configuration.
  *
  * @init
  */
  void AEK_POW_BMS63EN_ParameterConfiguration(void);
  
  /**
  * @brief   Configures the isolated communication frequency.
  * @note    This API is meant for a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_iso_freq   isolated frequency mode (high/low)
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_ConfigISOFreq(AEK_POW_BMS63EN_iso_freq_t AEK_POW_BMS63EN_iso_freq);
  
  /**
  * @brief   Disables the communication timeout.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableCommTimeout(unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief   Enables the communication timeout.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableCommTimeout(unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief  Sends the device(s) to into the 'SLEEP' or 'SILENT BALANCING' state.
  * @note   This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */

  void AEK_POW_BMS63EN_EnterSleepMode( unsigned AEK_POW_BMS63EN_devnum );

  /**
  * @brief  Performs a software reset and send the device(s) into the the 'SLEEP' state. 
  * @note   This API can be applied to a single unit or a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     all the AEK_POW_BMS63EN instances
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SWReset(unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Wakes up the overall stack of devices.
  * @note     This API performs the initial transition of a stack of devices 
  *           to the 'NORMAL' state. 
  *
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_StartUpWKUP(void);
  
  
  /**
  * @brief   Gets the current state.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     the current state of a selected device.
  *
  * @api
  */
  AEK_POW_BMS63EN_dev_state_t AEK_POW_BMS63EN_GetState( unsigned AEK_POW_BMS63EN_devnum );
/** @} */    
  /* * * * * * * * * * * * * * * * * * * * */
  
  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /*     A   p   p   l   i  c   a   t   i   o   n     F   u   n   c   t   i   o   n   s      */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @name    Application-oriented Functions
 * @{  
 */       
  
  /**
  * @brief    Performs the Coulomb counting.
  * @note     This API is meant for the first device of a stack unless there are other parallel
  *           stacks of devices.
  *           It is an example only, not required in the final module.  
  *
  * @param[in] AEK_POW_BMS63EN_devnum   the selected AEK_POW_BMS63EN instance
  * @param[in] qtc_R_shunt    the shunt resistance for the current sensing, expressed in microOhm: 
  *                           it's a system parameter, set for example @ 0.1 mΩ
  * @param[in] qtk            the previous Coulomb count value, expressed in Ampere hour [Ah] 
  * @return                   the updated Coulomb count, expressed in Ampere hour [Ah]
  *
  * @api
  */
  float AEK_POW_BMS63EN_CoulombCounting( unsigned AEK_POW_BMS63EN_devnum, float qtc_R_shunt, float qtk );
  
  /**
  * @brief    Disables the Coulomb counting.
  * @note     This API is meant for the first device of a stack unless there are other parallel
  *           stacks of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableCoulombCounting(unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Enables the Coulomb counting.
  * @note     This API is meant for the first device of a stack unless there are other parallel
  *           stacks of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableCoulombCounting(unsigned AEK_POW_BMS63EN_devnum );
/** @} */   
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  /*     C   e   l   l   s     F   u   n   c   t   i   o   n   s     */  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
/**
 * @name    Cell-oriented functions
 * @{  
 */     
  /**
  * @brief    Disables a selected cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_id          the selected cell 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableCell(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id );

  /**
  * @brief    Disables the balancing of a selected cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_id          the selected cell 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableCellBalancing(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id );

  /**
	 * @brief   Get Configuration Override latched status
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @return                     0: Override not latched or 1: Overrride latched
	 *
	 * @api
	 */

  uint8_t AEK_POW_BMS63EN_Get_Conf_OVL(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Enables the balancing of a selected cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_id          the selected cell 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableCellBalancing(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id );

  /**
  * @brief    Disables the balancing current on the even cells.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableBalCurrentEvenCells( unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Disbles the balancing current on the odd cells.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_DisableBalCurrentOddCells(unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Enables the balancing current on the even cells.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableBalCurrentEvenCells( unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Enables the balancing current on the odd cells.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableBalCurrentOddCells( unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Enables a selected cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_id          the selected cell 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableCell( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id );
  
  /**
  * @brief    Gets the current balancing status of a given instance.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance.
  * @return                     the current balancing state.
  *
  * @api
  */
  AEK_POW_BMS63EN_bal_status_t AEK_POW_BMS63EN_GetBalancingStatus( unsigned AEK_POW_BMS63EN_devnum );

  /**
  * @brief    Reads the ADC conversion data of a selected cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance.
  * @param[in] cell_id          the selected cell.
  * @return                     the ADC voltage measurement.
  *
  * @api
  */  
  float AEK_POW_BMS63EN_GetCellVoltMeasurement( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id );

  /**
  * @brief    Sets the balancing mode of a given cell.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_bal_mode    the selected balancing mode ('manual' or 'timed')
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetBalancingMode(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_bal_mode_t cell_bal_mode );

  /**
  * @brief    Sets the threshold for the timed balancing mode of a given cell.
  * @note     This API can be applied to a single unit of a stack of devices; the input 
  *           threshold must be expressed in seconds and the 'coarse' (resolution is
  *           8 min and 32 s) or 'fine' (resolution is 4 s) accuracy is automatically 
  *           selected accordingly: 'fine' resolution is set under the value of 508; 
  *           'coarse' from 512 onwards.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] cell_id          the selected cell 
  * @param[in] cell_thr         the cell threshold 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetCellTimedBalThreshold(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id, uint16_t cell_thr );
  
  /**
  * @brief    Starts the balancing on the enabled cells of a device.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_StartCellBalancing( unsigned AEK_POW_BMS63EN_devnum );

  /**
  * @brief    Stops the balancing on the enabled cells of a device.
  * @note     This API can be applied to a single unit of a stack of devices.
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_StopCellBalancing( unsigned AEK_POW_BMS63EN_devnum );
/** @} */   
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  /*     A   D   C     F   u   n   c   t   i   o   n   s     */  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
/**
 * @name    ADC Configuration Functions
 * @{  
 */   
  /**
  * @brief   Sets the ADC's continous mode.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetADCContinuousMode( unsigned AEK_POW_BMS63EN_devnum );

  /**
  * @brief   Sets the ADC's filter time.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] filter_soc       the filter time to set 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetADCFilterSOC( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adc_filter_soc_t filter_soc );

/**
  * @brief   Sets the ADC's sampling cycle period.
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] tcycle           the period time to set 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetADCTcycle( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adc_conv_tcycle_t tcycle );

  /**
  * @brief    Sets the ADC's overvcurrent (CSA) voltage threshold.
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           overcurrent voltage threshold must be expressed in milliVolt (mV).
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] vbatt_ovc_thr    the requested threshold value in milliVolt  
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVBattOVCThreshold( unsigned AEK_POW_BMS63EN_devnum, int32_t vbatt_ovc_thr );
  
  /**
  * @brief    Sets the ADC's overvoltage threshold (sum of cells).
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           overvoltage threshold must be expressed in microVolt (uV).
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] vbatt_ov_thr     the requested threshold value in milliVolt  
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVBattOVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint32_t vbatt_ov_thr );
  
  /**
  * @brief    Sets the ADC's undervoltage threshold (sum of cells).
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           overvoltage threshold must be expressed in milliVolt (mV)
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the AEK_POW_BMS63EN instance
  * @param[in] vbatt_uv_thr     the requested threshold value in milliVolt 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVBattUVThreshold(  unsigned AEK_POW_BMS63EN_devnum, uint32_t vbatt_uv_thr );
  
  /**
  * @brief    Sets the ADC's overvoltage threshold for a cell.
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           overvoltage threshold must be expressed in milliVolt (mV)
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] vcell_ov_thr     the requested threshold value in milliVolt 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVCellOVThreshold( unsigned AEK_POW_BMS63EN_devnum, uint16_t vcell_ov_thr );
  
  /**
  * @brief    Sets the ADC's undervoltage threshold for a cell.
  * @note     This API can be applied to a single unit of a stack of devices; 
  *           input undervoltage threshold must be expressed in milliVolt (mV)
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] vcell_uv_thr     the requested threshold value in milliVolt 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVCellUVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint16_t vcell_uv_thr );
  
  /**
  * @brief    Sets the ADC's overvoltage threshold for a cell.
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           overvoltage threshold must be expressed in milliVolt (mV)
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] vcell_ov_thr     the requested threshold value in milliVolt 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetVCellOVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint16_t vcell_ov_thr );
  
  /**
  * @brief    Starts the manual conversion for a stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices.)
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @return                     void.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_StartManualConversion( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adcv_conv_opt_t GPIO_CONV ,
  		AEK_POW_BMS63EN_adcv_conv_opt_t GPIO_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t CELL_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t BAL_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t HWSC, AEK_POW_BMS63EN_adcv_conv_opt_t ADC_CROSS_CHECK) ;

/** @} */  
  /* * * * * * * * * * * * * * * * * * * * * * * * */
  
  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  /*     G   P   I   O   9 _ 3    F   u   n   c   t   i   o   n   s    */  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
/**
 * @name    GPIO 9 - 3  Configuration Functions
 * @{  
 */ 
 
  /**
  * @brief    Configures the GPIO 3 - 9
  * @note     This API can be applied to a single unit of a stack of devices
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
  * @param[in] AEK_POW_BMS63EN_gpio_conf  GPIO configuration (analog input, digital input or digital output)
  * @return                     void.
   
  * @api
  */
  void AEK_POW_BMS63EN_ConfigGPIO(  unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, AEK_POW_BMS63EN_gpio_conf_t AEK_POW_BMS63EN_gpio_conf );
  
   /**
  * @brief   Sets the GPIO absolute mode (GPIO between 3 and 9) 
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetGPIOModeAbsolute(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio );

  /**
  * @brief   Sets the GPIO rationmetric mode (GPIO between 3 and 9) 
  * @note    This API can be applied to a single unit of a stack of devices. 
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetGPIOModeRatiometric( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio );
  
  /**
  * @brief    Sets the GPIO 3 -> 9 overvoltage threshold
  * @note     This API can be applied to a single unit of a stack of devices; input
  *           overvoltage threshold must be expressed in milliVolt (mV) or unsigned 
  *           integer (see param 'gpio_ov_thr' below).
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
  * @param[in] gpio_ov_thr      the requested threshold value in milliVolt if in "absolute mode" or 
  *                             unsigned integer between 0 and 512 if in "ratiometric mode"
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetGPIOOVThreshold(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, uint16_t gpio_ov_thr );
  
  /**
  * @brief    Sets the GPIO 3 -> 9 undervoltage threshold
  * @note     This API can be applied to a single unit of a stack of devices; input 
  *           undervoltage threshold must be expressed in milliVolt (mV) or unsigned 
  *           integer (see param 'gpio_uv_thr' below).
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
  * @param[in] gpio_uv_thr      the requested threshold value in milliVolt if in "absolute mode" or 
  *                             unsigned integer between 0 and 512 if in "ratiometric mode"
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SetGPIOUVThreshold(  unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, uint16_t gpio_uv_thr );

  /**
   * @brief    Enables VTref
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @return                     void.
   *
   * @api
   */
  void AEK_POW_BMS63EN_SetVTREFEnabled( unsigned AEK_POW_BMS63EN_devnum);

  /**
   * @brief    Enables Always VTref
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @return                     void.
   *
   * @api
   */
  void AEK_POW_BMS63EN_SetVTREFAlwaysEnabled( unsigned AEK_POW_BMS63EN_devnum);

  /**
    * @brief    Disables VTref
    * @note     This API can be applied to a single unit of a stack of devices;
    *
    * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
    * @return                     void.
    *
    * @api
    */
  void AEK_POW_BMS63EN_SetVTREFDisabled(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Get Calib Current Measurement
  * @note     This API can be applied to a single unit of a stack of devices; input
  *           Rshunt must be expressed in milliOhm (mohm) or unsigned
  *           integer .
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
  * @param[in] Rshunt           Rshunt value in milliohm
  * @return                     Calib current expressed in Ampere
  *
  * @api
  */
  float AEK_POW_BMS63EN_GetCalibCurrentMeasurement(unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt);

  /**
   * @brief    Get Inst Current Measurement
   * @note     This API can be applied to a single unit of a stack of devices; input
   *           Rshunt must be expressed in milliOhm (mohm) or unsigned
   *           integer .
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @param[in] Rshunt           Rshunt value in milliohm
   * @return                     Inst current expressed in Ampere
   *
   * @api
   */
  float AEK_POW_BMS63EN_GetInstCurrentMeasurement( unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt);

  /**
   * @brief    Get GPIO Voltage Measurement
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
   * @return                     Voltage value expressed in volt
   *
   * @api
   */

  float AEK_POW_BMS63EN_GetBatteryPackVoltMeasurement( unsigned AEK_POW_BMS63EN_devnum);

  /**
   * @brief    Get VTREF Voltage Measurement
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @return                     VTREF Voltage value expressed in volt
   *
   * @api
   */
  float AEK_POW_BMS63EN_GetVTREFVoltMeasurement(unsigned AEK_POW_BMS63EN_devnum);

  /**
   * @brief    Get GPIO Voltage Measurement with ABS or RATIO mode
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
   * @param[in] Vref             VTref float value
   * @param[in] mode             AEK_POW_BMS63EN_ratio_abs_mode_t AEK_POW_BMS63EN_ABS_MODE or AEK_POW_BMS63EN_RATIO_MODE
   * @return                     Voltage value expressed in volt
   *
   * @api
   */
  float AEK_POW_BMS63EN_GetVoltageGPIOMeasurement(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio,float Vref, AEK_POW_BMS63EN_ratio_abs_mode_t mode);


  /**
   * @brief    Get GPIO Resistor Measurement with ABS or RATIO mode
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @param[in] AEK_POW_BMS63EN_gpio       GPIO index: AEK_POW_BMS63EN_gpio_x, with x between 3 and 9
   * @param[in] Vref             VTref float value
   * @param[in] mode             AEK_POW_BMS63EN_ratio_abs_mode_t AEK_POW_BMS63EN_ABS_MODE or AEK_POW_BMS63EN_RATIO_MODE
   * @return                     Voltage value expressed in volt
   *
   * @api
   */
  float AEK_POW_BMS63EN_GetNTCMeasurement( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio,float Vref, AEK_POW_BMS63EN_ratio_abs_mode_t mode);

  /**
   * @brief    Mask Over/Under Temperature fault detection for GPIO7
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @return                     void
   *
   * @api
   */
  void AEK_POW_BMS63EN_GPIO7_OT_UT_Mask(unsigned AEK_POW_BMS63EN_devnum);

  /**
   * @brief    Mask Over/Under Temperature fault detection
   * @note     This API can be applied to a single unit of a stack of devices;
   *
   * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
   * @return                     void
   *
   * @api
   */
  void AEK_POW_BMS63EN_GPIO_OT_UT_Mask(unsigned AEK_POW_BMS63EN_devnum);

  /**
	 * @brief   Enable GPIO Measurement
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @return                     void
	 *
	 * @api
	 */
  void AEK_POW_BMS63EN_SetGPIOConv( unsigned AEK_POW_BMS63EN_devnum);

  /**
	 * @brief   Enable GPIO Measurement
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @return                     void
	 *
	 * @api
	 */
  void AEK_POW_BMS63EN_SetGPIOConv( unsigned AEK_POW_BMS63EN_devnum);



  /**
	 * @brief   Mask CSA GPIO over/under current detection
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @return                     void
	 *
	 * @api
	 */
  void AEK_POW_BMS63EN_GPIO_CSA_Mask( unsigned AEK_POW_BMS63EN_devnum);



  /**
	 * @brief   Reset Coulomb Counter
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @return                     void
	 *
	 * @api
	 */
  void AEK_POW_BMS63EN_CoulombCounterReset(unsigned AEK_POW_BMS63EN_devnum);

  /**
	 * @brief   Check Enabled Cell
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @param[in] cell_idx		   Cell idx
	 * @return                     1 Enabled - 0 Disabled
	 *
	 * @api
	 */
  uint8_t AEK_POW_BMS63EN_isEnabled(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_idx);

  /**
	 * @brief   Set OverCurrent Threshold
	 * @note     This API can be applied to a single unit of a stack of devices;
	 *
	 * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instance
	 * @param[in] Rshunt		   Rsense
	 * @param[in] Rshunt		   Current Threshold
	 * @return                     1 Enabled - 0 Disabled
	 *
	 * @api
	 */
  void AEK_POW_BMS63EN_SetOvercurrentThreshold( unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt, float current_th_A);


/** @} */  

#endif
#endif /* _AEK_POW_BMS63EN_ID_H_ */



/** @} */
