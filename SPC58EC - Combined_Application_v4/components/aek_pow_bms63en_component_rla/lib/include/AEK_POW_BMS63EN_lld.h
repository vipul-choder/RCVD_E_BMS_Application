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
 * @file    AEK_POW_BMS63EN_lld.h
 * @brief   AEK_POW_BMS63EN Driver macros and structures.
 *
 * @addtogroup AEK_POW_BMS63EN_LLD
 * @{
 */

#ifndef _AEK_POW_BMS63EN_LLD_H_
#define _AEK_POW_BMS63EN_LLD_H_

#include "components.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    AEK_POW_BMS63EN Device Identifiers
 * @{
 */
#define AEK_POW_BMS63EN_DEVICE_ID_ALL   0
#define AEK_POW_BMS63EN_DEVICE_ID(n)    n
#define AEK_POW_BMS63EN_DEVICE(n)       n-1

/** @} */

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
 * @brief   Type of an AEK_POW_BMS63EN SPI register.
 */
typedef uint32_t AEK_POW_BMS63EN_register_t;


/**
 * @brief   AEK_POW_BMS63EN cell unit identifier.
 */
typedef enum {
          AEK_POW_BMS63EN_CELL1 = 0,
          AEK_POW_BMS63EN_CELL2 = 1,
          AEK_POW_BMS63EN_CELL3 = 2,
          AEK_POW_BMS63EN_CELL4 = 3,
          AEK_POW_BMS63EN_CELL5 = 4,
          AEK_POW_BMS63EN_CELL6 = 5,
          AEK_POW_BMS63EN_CELL7 = 6,
          AEK_POW_BMS63EN_CELL8 = 7,
          AEK_POW_BMS63EN_CELL9 = 8,
          AEK_POW_BMS63EN_CELL10 = 9,
          AEK_POW_BMS63EN_CELL11 = 10,
          AEK_POW_BMS63EN_CELL12 = 11,
          AEK_POW_BMS63EN_CELL13 = 12,
          AEK_POW_BMS63EN_CELL14 = 13,
          AEK_POW_BMS63EN_CELL_ALL = 14
} AEK_POW_BMS63EN_cell_id_t;


/**
 * @brief   AEK_POW_BMS63EN cell connection status.
 */
typedef enum {
          AEK_POW_BMS63EN_RATIOMETRIC = 0,   /**< Ratiometric measurement.   */
          AEK_POW_BMS63EN_ABSOLUTE = 1      /**< Absolute measurement.     */
} AEK_POW_BMS63EN_gpio_measurement_t;



/**
 * @brief   AEK_POW_BMS63EN cell connection status.
 */
typedef enum {
          AEK_POW_BMS63EN_CELL_UNCONNECTED = 0,   /**< Cell unconnected.   */
          AEK_POW_BMS63EN_CELL_CONNECTED = 1      /**< Cell connected.     */
} AEK_POW_BMS63EN_cell_conn_t;


/**
 * @brief   AEK_POW_BMS63EN cell enable/disable status.
 */
typedef enum {
          AEK_POW_BMS63EN_CELL_DISABLED = 0,   /**< Cell disabled.   */
          AEK_POW_BMS63EN_CELL_ENABLED = 1     /**< Cell enabled.    */
} AEK_POW_BMS63EN_cell_en_t;

/**
 * @brief   AEK_POW_BMS63EN GPIO 9 - 3 property.
 */
typedef enum {
          AEK_POW_BMS63EN_gpio_analog_input,    /**<    GPIO set as analog input    */
          AEK_POW_BMS63EN_gpio_digital_input,   /**<    GPIO set as digital input   */
          AEK_POW_BMS63EN_gpio_digital_output   /**<    GPIO set as digital output  */
} AEK_POW_BMS63EN_gpio_conf_t;



/**
 * @brief   AEK_POW_BMS63EN cell PCB status.
 */
typedef enum {
          AEK_POW_BMS63EN_CELL_PCB_UNKNOWN = 0,   /**< Unknown pcb cell status.   */
          AEK_POW_BMS63EN_CELL_PCB_OPEN = 1,      /**< Open cell.                 */
          AEK_POW_BMS63EN_CELL_PCB_CONNECTED = 2  /**< Connected wired cell.      */
} AEK_POW_BMS63EN_cell_pcb_conn_t;


/**
 * @brief   AEK_POW_BMS63EN cell global status.
 */
typedef struct {
          const AEK_POW_BMS63EN_cell_id_t cell_id;        /**< Cell identifier.                           */
          const AEK_POW_BMS63EN_cell_conn_t cell_conn;    /**< Cell connection status.                    */
          AEK_POW_BMS63EN_cell_en_t cell_en;              /**< Cell enable status.                        */
          AEK_POW_BMS63EN_cell_pcb_conn_t cell_pcb_conn;  /**< Cell connection status after the PCB diag. */
} AEK_POW_BMS63EN_cell_status_t;


/**
 * @brief   AEK_POW_BMS63EN stack of cell status.
 */
typedef struct {
  AEK_POW_BMS63EN_cell_status_t cell_1;   /**< Cell #1. */
  AEK_POW_BMS63EN_cell_status_t cell_2;   /**< Cell #2. */
  AEK_POW_BMS63EN_cell_status_t cell_3;   /**< Cell #3. */
  AEK_POW_BMS63EN_cell_status_t cell_4;   /**< Cell #4. */
  AEK_POW_BMS63EN_cell_status_t cell_5;   /**< Cell #5. */
  AEK_POW_BMS63EN_cell_status_t cell_6;   /**< Cell #6. */
  AEK_POW_BMS63EN_cell_status_t cell_7;   /**< Cell #7. */
  AEK_POW_BMS63EN_cell_status_t cell_8;   /**< Cell #8. */
  AEK_POW_BMS63EN_cell_status_t cell_9;   /**< Cell #9. */
  AEK_POW_BMS63EN_cell_status_t cell_10;  /**< Cell #10. */
  AEK_POW_BMS63EN_cell_status_t cell_11;  /**< Cell #11. */
  AEK_POW_BMS63EN_cell_status_t cell_12;  /**< Cell #12. */
  AEK_POW_BMS63EN_cell_status_t cell_13;  /**< Cell #13. */
  AEK_POW_BMS63EN_cell_status_t cell_14;  /**< Cell #14. */
} AEK_POW_BMS63EN_cell_stack_state_t;


/**
 * @brief   AEK_POW_BMS63EN device unit identifier.
 */
typedef enum {
          AEK_POW_BMS63EN_DEVICE_ALL = 0,
          AEK_POW_BMS63EN_DEVICE1 = 1,
          AEK_POW_BMS63EN_DEVICE2 = 2,
          AEK_POW_BMS63EN_DEVICE3 = 3,
          AEK_POW_BMS63EN_DEVICE4 = 4,
          AEK_POW_BMS63EN_DEVICE5 = 5,
          AEK_POW_BMS63EN_DEVICE6 = 6,
          AEK_POW_BMS63EN_DEVICE7 = 7,
          AEK_POW_BMS63EN_DEVICE8 = 8,
          AEK_POW_BMS63EN_DEVICE9 = 9,
          AEK_POW_BMS63EN_DEVICE10 = 10,
          AEK_POW_BMS63EN_DEVICE11 = 11,
          AEK_POW_BMS63EN_DEVICE12 = 12,
          AEK_POW_BMS63EN_DEVICE13 = 13,
          AEK_POW_BMS63EN_DEVICE14 = 14,
          AEK_POW_BMS63EN_DEVICE15 = 15,
          AEK_POW_BMS63EN_DEVICE16 = 16,
          AEK_POW_BMS63EN_DEVICE17 = 17,
          AEK_POW_BMS63EN_DEVICE18 = 18,
          AEK_POW_BMS63EN_DEVICE19 = 19,
          AEK_POW_BMS63EN_DEVICE20 = 20,
          AEK_POW_BMS63EN_DEVICE21 = 21,
          AEK_POW_BMS63EN_DEVICE22 = 22,
          AEK_POW_BMS63EN_DEVICE23 = 23,
          AEK_POW_BMS63EN_DEVICE24 = 24,
          AEK_POW_BMS63EN_DEVICE25 = 25,
          AEK_POW_BMS63EN_DEVICE26 = 26,
          AEK_POW_BMS63EN_DEVICE27 = 27,
          AEK_POW_BMS63EN_DEVICE28 = 28,
          AEK_POW_BMS63EN_DEVICE29 = 29,
          AEK_POW_BMS63EN_DEVICE30 = 30,
          AEK_POW_BMS63EN_DEVICE31 = 31
} AEK_POW_BMS63EN_device_id_t;

 
/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
          AEK_POW_BMS63EN_UNINIT   = 0,   /**< Not initialized.                   */
          AEK_POW_BMS63EN_STOP     = 1,   /**< Stopped.                           */
          AEK_POW_BMS63EN_STARTING = 2,   /**< Starting.                          */
          AEK_POW_BMS63EN_STOPPING = 3,   /**< Starting.                          */
          AEK_POW_BMS63EN_READY    = 4    /**< Ready.                             */
} AEK_POW_BMS63EN_drv_state_t;

/**
 * @brief   Device state machine possible states.
 */
typedef enum {
      AEK_POW_BMS63EN_POR              = 0,    /**< Power on reset (dummy state).   */
      AEK_POW_BMS63EN_RESET            = 1,    /**< Reset.                          */
      AEK_POW_BMS63EN_SLEEP            = 2,    /**< Sleep Memory Read.              */
      AEK_POW_BMS63EN_SILENT_BALANCING = 3,    /**< Silent balancing.               */
      AEK_POW_BMS63EN_CYCLIC_WAKEUP    = 4,    /**< Cyclic wake-up.                 */
      AEK_POW_BMS63EN_TRIMMING         = 5,    /**< Trimming.                       */
      AEK_POW_BMS63EN_INIT             = 6,    /**< Init.                           */
      AEK_POW_BMS63EN_NORMAL           = 7,    /**< Normal.                         */
      AEK_POW_BMS63EN_DIAG             = 8     /**< Diagnostic (dummy state).       */
} AEK_POW_BMS63EN_dev_state_t;


/**
 * @brief   Type of a structure representing a AEK_POW_BMS63EN driver.
 */
typedef struct AEK_POW_BMS63EN_Driver AEK_POW_BMS63EN_Driver;


/**
 * @brief   Type of a structure representing a AEK_POW_BMS63EN device unit state.
 */
typedef struct { 
        const AEK_POW_BMS63EN_device_id_t device_id;            /*!< current device unit number */
        AEK_POW_BMS63EN_dev_state_t device_state;               /*!< current device state */
        AEK_POW_BMS63EN_cell_stack_state_t *cell_stack_state;   /*!< current cell stack state */
} AEK_POW_BMS63EN_dev_status_t;


/**
 * @brief   Type of a structure representing a AEK_POW_BMS63EN driver state.
 */
typedef struct { 
        AEK_POW_BMS63EN_drv_state_t driver_state;     /*!< current driver state */
        AEK_POW_BMS63EN_dev_status_t *device_status;  /*!< current device(s) state */
} AEK_POW_BMS63EN_status_t;


/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  SPIDriver         *spip;
  SPIConfig   *spicfgp;
  SPIDriver         *spip_dual;
  SPIConfig   *spicfgp_dual;
} AEK_POW_BMS63EN_Config;


/**
 * @brief   AEK_POW_BMS63EN cell balancing mode.
 */
typedef enum {

        AEK_POW_BMS63EN_cell_man_bal_mode = 1,     /**< manual balancing mode  */
        AEK_POW_BMS63EN_cell_tim_bal_mode = 2       /**< timed balancing mode   */
} AEK_POW_BMS63EN_cell_bal_mode;


/**
 * @brief   AEK_POW_BMS63EN Coulomb Counting Enable/Disable
 */
typedef enum {

        AEK_POW_BMS63EN_CoulombCounting_Enabled = 1,       /**< Coulomb counting Enabled  */
		AEK_POW_BMS63EN_CoulombCounting_Disabled = 2       /**< Coulomb counting Disabled  */
} AEK_POW_BMS63EN_coulomb_counting_t;


/**
 * @brief   AEK_POW_BMS63EN ADC filter soc period.
 */
typedef enum {
        AEK_POW_BMS63EN_adc_flt_soc_290us = 0,     /**< filter_soc = 290 us             */
        AEK_POW_BMS63EN_adc_flt_soc_1ms16 = 1,     /**< filter_soc = 1 ms and 160 us    */
        AEK_POW_BMS63EN_adc_flt_soc_2ms32 = 2,     /**< filter_soc = 2 ms and 320 us    */
        AEK_POW_BMS63EN_adc_flt_soc_9ms28 = 3,     /**< filter_soc = 9 ms and 280 us    */
        AEK_POW_BMS63EN_adc_flt_soc_18ms56 = 4,    /**< filter_soc = 18 ms and 560 ms   */
        AEK_POW_BMS63EN_adc_flt_soc_37ms12 = 5,    /**< filter_soc = 37 ms and 120 us   */
        AEK_POW_BMS63EN_adc_flt_soc_74ms24 = 6,    /**< filter_soc = 74 ms and 240 us   */
        AEK_POW_BMS63EN_adc_flt_soc_148ms48 = 7    /**< filter_soc = 148 ms and 480 us  */
} AEK_POW_BMS63EN_adc_flt_soc_t;



/**
 * @brief   AEK_POW_BMS63EN Communication timeouy
 */
typedef enum {
        AEK_POW_BMS63EN_commtimeout_32ms = 0,      /**< communication_timeout = 32msec             */
        AEK_POW_BMS63EN_commtimeout_1024ms = 1,      /**< communication_timeout = 32msec             */
        AEK_POW_BMS63EN_commtimeout_2048ms = 2,      /**< communication_timeout = 32msec             */
} AEK_POW_BMS63EN_commtimeout_t;


/**
 * @brief   AEK_POW_BMS63EN Isolated frequency.
 */
typedef enum {
        AEK_POW_BMS63EN_iso_freq_low,   /**<    low isolated frequency: 333 Kbps    */
        AEK_POW_BMS63EN_iso_freq_high   /**<    high isolated frequency: 2.66 Mbps  */
} AEK_POW_BMS63EN_iso_freq_t;



typedef enum{
		AEK_POW_BMS63EN_VTREF_DISABLED,
		AEK_POW_BMS63EN_VTREF_ON_CONV_ENABLED,
		AEK_POW_BMS63EN_VTREF_ALWAYS_ENABLED
}AEK_POW_BMS63EN_VTRef_sts_t;

/*
* @brief   AEK_POW_BMS63EN configuration Param
*/
typedef struct{
	uint16_t	             VBattOVThreshold;
	uint16_t    		     VBattUVThreshold;
	uint16_t 	             VCellOVThreshold;
	uint16_t    		     VCellUVThreshold;
	uint16_t    		     GPIO3OVThreshold;
	uint16_t    		  	 GPIO3UVThreshold;
	uint16_t    		     GPIO4OVThreshold;
	uint16_t    		  	 GPIO4UVThreshold;
	uint16_t    		     GPIO5OVThreshold;
	uint16_t    		  	 GPIO5UVThreshold;
	uint16_t    		     GPIO6OVThreshold;
	uint16_t    		  	 GPIO6UVThreshold;
	uint16_t    		     GPIO9OVThreshold;
	uint16_t    		  	 GPIO9UVThreshold;
	uint16_t    		     GPIO8OVThreshold;
	uint16_t    		  	 GPIO8UVThreshold;
	AEK_POW_BMS63EN_gpio_conf_t     	 gpio3_conf;
	AEK_POW_BMS63EN_gpio_conf_t     	 gpio4_conf;
	AEK_POW_BMS63EN_gpio_conf_t    	 gpio5_conf;
	AEK_POW_BMS63EN_gpio_conf_t        gpio6_conf;
	AEK_POW_BMS63EN_gpio_conf_t        gpio9_conf;
	AEK_POW_BMS63EN_gpio_conf_t        gpio8_conf;
	AEK_POW_BMS63EN_gpio_measurement_t gpio_meas;
	AEK_POW_BMS63EN_cell_bal_mode      cell_bal_mode;
	AEK_POW_BMS63EN_adc_flt_soc_t      adc_filter_soc;
	AEK_POW_BMS63EN_coulomb_counting_t coulomb_counting_en;
    AEK_POW_BMS63EN_iso_freq_t AEK_POW_BMS63EN_iso_freq;
	AEK_POW_BMS63EN_commtimeout_t commtimeout;
	AEK_POW_BMS63EN_VTRef_sts_t AEK_POW_BMS63EN_VTREF_sts;
}AEK_POW_BMS63EN_ParamConf;


/**
 * @brief   Structure representing an AEK_POW_BMS63EN driver.
 */
struct AEK_POW_BMS63EN_Driver {
  /**
   * @brief Driver state.
   */
  AEK_POW_BMS63EN_status_t                *status;

  /**
   * @brief Current configuration data.
   */
   AEK_POW_BMS63EN_Config           *config;

  /**
   * @brief Parameter Configuration
   */
  AEK_POW_BMS63EN_ParamConf    *param_conf;
};

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

  /* Init Functions */
  /**
  * @brief   Initializes the standard part of a @p AEK_POW_BMS63EN_Driver structure.
  *
  * @param[in] AEK_POW_BMS63ENp     pointer to the @p AEK_POW_BMS63EN_Driver object
  * @return    void.
  *
  * @init
  */
  void AEK_POW_BMS63EN_ObjectInit( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp );
  
  /**
  * @brief   Configures and activates the AEK_POW_BMS63EN device.
  *
  * @param[in] AEK_POW_BMS63ENp    pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in] config    pointer to the @p AEK_POW_BMS63EN_Config object
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_Start( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, AEK_POW_BMS63EN_Config *config );
  
  /**
  * @brief   Deactivates the AEK_POW_BMS63EN device.
  *
  * @param[in] AEK_POW_BMS63ENp      pointer to the @p AEK_POW_BMS63EN_Driver object
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_Stop( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp );
  /* * * * * * * * */
  
  
  /* SPI-based functions */
  /**
  * @brief    Send a 'write' command to all the device units.
  *
  * @param[in] AEK_POW_BMS63ENp   pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in] regnum   register number
  * @param[in] value    value to be written into the register
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SPIBroadcastAccess( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned regnum, AEK_POW_BMS63EN_register_t value );
  
  /**
  * @brief    Reads registers in a burst from a given device.
  *
  * @param[in]  AEK_POW_BMS63ENp      pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in]  devnum      the device instance to select
  * @param[in]  command     the burst command identifier
  * @param[out] reg_values  pointer to the buffer containing the requested register values
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SPIBurstAccess( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned command, AEK_POW_BMS63EN_register_t *reg_values );
  
  /**
  * @brief   Writes a queue.
  *
  * @param[in] AEK_POW_BMS63ENp    pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in] n_bytes   the amount of bytes to transfer
  * @param[in] txqueue   pointer to the 1st position of the bytes to transfer
  * @param[in] rxqueue   pointer to the 1st position of the bytes to receive
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SPIQueuedAccess( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, uint8_t n_bytes, const uint8_t *txqueue, uint8_t *rxqueue );
  
  /**
  * @brief    Writes a register.
  *
  * @param[in] AEK_POW_BMS63ENp   pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in] devnum   device unit number
  * @param[in] regnum   register number
  * @param[in] value    value to be written into the register
  * @return    void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_SPIWriteRegister( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned regnum, AEK_POW_BMS63EN_register_t value );
  
  /**
  * @brief    Reads a register.
  * @note     This is an atomic function: it sends a single 'read' commands only and 
  *           doesn't perform the sequence required by the 'out-of-frame' device mode.
  *
  * @param[in] AEK_POW_BMS63ENp   pointer to the @p AEK_POW_BMS63EN_Driver object
  * @param[in] devnum   register number
  * @param[in] regnum   register number
  * @return             the register value.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_SPIReadRegister( AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned regnum );


  /**
    * @brief    Reverse TX in dual ring mode
    * @note     This is an atomic function: it change the TX procedure selecting
    *           second transceiver in dual ring mode.
    *
    * @api
    */
  void AEK_POW_BMS63EN_DualRingTX_reverse(void);


  /* * * * * * * * * * * */
  
  

  /* * * * * * * * * * * * * */

#endif

#endif /* _AEK_POW_BMS63EN_ID_H_ */

/** @} */
