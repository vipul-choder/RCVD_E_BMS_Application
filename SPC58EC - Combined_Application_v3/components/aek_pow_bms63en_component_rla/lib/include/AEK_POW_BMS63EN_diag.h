/***********************************************************************************
*
* Copyright © 2019 - 2020 STMicroelectronics - All Rights Reserved
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
 * @brief   AEK_POW_BMS63EN Driver diagnostics macros and structures.
 *
 * @addtogroup AEK_POW_BMS63EN_DIAG
 * @{
 */

#ifndef _AEK_POW_BMS63EN_DIAG_H_
#define _AEK_POW_BMS63EN_DIAG_H_

#include "AEK_POW_BMS63EN_lld.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

typedef enum {
	AEK_POW_BMS63EN_NOFAULT = 0,
	AEK_POW_BMS63EN_FAULT = 1
} AEK_POW_BMS63EN_fault_t;

/**
 * @brief   AEK_POW_BMS63EN GPIO 9 - 3 list.
 */
typedef enum {
          AEK_POW_BMS63EN_gpio_3 = 0,   /**<    GPIO #3 */
          AEK_POW_BMS63EN_gpio_4 = 1,   /**<    GPIO #4 */
          AEK_POW_BMS63EN_gpio_5 = 2,   /**<    GPIO #5 */
          AEK_POW_BMS63EN_gpio_6 = 3,   /**<    GPIO #6 */
          AEK_POW_BMS63EN_gpio_7 = 4,   /**<    GPIO #7 */
          AEK_POW_BMS63EN_gpio_8 = 5,   /**<    GPIO #8 */
          AEK_POW_BMS63EN_gpio_9 = 6    /**<    GPIO #9 */
} AEK_POW_BMS63EN_gpio_t;


/**
 * @brief   AEK_POW_BMS63EN GPIO generic status.
 */
typedef struct {
          AEK_POW_BMS63EN_gpio_conf_t gpio_conf;          /**< GPIO configuration.                                                */
          AEK_POW_BMS63EN_fault_t gpio_open;              /**< GPIO open fault (for "analog input configuration" only).           */
          AEK_POW_BMS63EN_fault_t gpio_overvoltage;       /**< GPIO overvoltage fault (for "analog input configuration" only).    */
          AEK_POW_BMS63EN_fault_t gpio_undervoltage;      /**< GPIO undervoltage fault (for "analog input configuration" only).   */
          AEK_POW_BMS63EN_fault_t gpio_short;             /**< GPIO short fault (for "digital input/output configuration" only).  */
} AEK_POW_BMS63EN_gpio_status_t;


/**
 * @brief   AEK_POW_BMS63EN GPIO's diagnostic status.
 */
typedef struct {
          AEK_POW_BMS63EN_gpio_status_t gpio_3;   /**< GPIO #3. */
          AEK_POW_BMS63EN_gpio_status_t gpio_4;   /**< GPIO #4. */
          AEK_POW_BMS63EN_gpio_status_t gpio_5;   /**< GPIO #5. */
          AEK_POW_BMS63EN_gpio_status_t gpio_6;   /**< GPIO #6. */
          AEK_POW_BMS63EN_gpio_status_t gpio_7;   /**< GPIO #7. */
          AEK_POW_BMS63EN_gpio_status_t gpio_8;   /**< GPIO #8. */
          AEK_POW_BMS63EN_gpio_status_t gpio_9;   /**< GPIO #9. */
} AEK_POW_BMS63EN_gpio_state_t;


/**
 * @brief   AEK_POW_BMS63EN FAULTL line diagnostic status.
 */
typedef struct {
      AEK_POW_BMS63EN_fault_t faultl;                             /**< Device fault line .  */
      AEK_POW_BMS63EN_register_t faultl_burst_cmd7A_status[14];   /**< Results of 0x7A (CMD2) burst.  */
} AEK_POW_BMS63EN_faultl_state_t;


/**
 * @brief   AEK_POW_BMS63EN FAULT1 enum
 */
typedef enum {
	AEK_POW_BMS63EN_Comm_timeout_flt = 0,
	AEK_POW_BMS63EN_Fault_L_line_status = 3,
	AEK_POW_BMS63EN_FaultHline_fault = 4,
	AEK_POW_BMS63EN_HeartBeat_fault = 5,
	AEK_POW_BMS63EN_VCOM_UV = 6,
	AEK_POW_BMS63EN_VCOM_OV = 7,
	AEK_POW_BMS63EN_VREG_OV = 8,
	AEK_POW_BMS63EN_VREG_UV = 9,
	AEK_POW_BMS63EN_VTREF_OV = 10,
	AEK_POW_BMS63EN_VTREF_UV = 11,
	AEK_POW_BMS63EN_VDIG_OV = 12,
	AEK_POW_BMS63EN_VANA_OV = 13
} AEK_POW_BMS63EN_fault1_t;

/**
 * @brief   AEK_POW_BMS63EN FAULT2 enum
 */
typedef enum {
	AEK_POW_BMS63EN_curr_sense_ovc_norm = 0,
	AEK_POW_BMS63EN_curr_sense_ovc_sleep = 1,
	AEK_POW_BMS63EN_EoBtimeerror = 2,
	AEK_POW_BMS63EN_CoCouOvF = 3,
	AEK_POW_BMS63EN_loss_gndref = 5,
	AEK_POW_BMS63EN_loss_cgnd = 6,
	AEK_POW_BMS63EN_loss_dgnd = 7,
	AEK_POW_BMS63EN_loss_agnd = 8,
	AEK_POW_BMS63EN_OSCFail = 10,
	AEK_POW_BMS63EN_SPIENlatch = 12
} AEK_POW_BMS63EN_fault2_t;

/**
 * @brief   AEK_POW_BMS63EN VCELLUV fault enum
 */
typedef enum {
	AEK_POW_BMS63EN_VCELL1_UV = 0,
	AEK_POW_BMS63EN_VCELL2_UV = 1,
	AEK_POW_BMS63EN_VCELL3_UV = 2,
	AEK_POW_BMS63EN_VCELL4_UV = 3,
	AEK_POW_BMS63EN_VCELL5_UV = 4,
	AEK_POW_BMS63EN_VCELL6_UV = 5,
	AEK_POW_BMS63EN_VCELL7_UV = 6,
	AEK_POW_BMS63EN_VCELL8_UV = 7,
	AEK_POW_BMS63EN_VCELL9_UV = 8,
	AEK_POW_BMS63EN_VCELL10_UV = 9,
	AEK_POW_BMS63EN_VCELL11_UV = 10,
	AEK_POW_BMS63EN_VCELL12_UV = 11,
	AEK_POW_BMS63EN_VCELL13_UV = 12,
	AEK_POW_BMS63EN_VCELL14_UV = 13,
	AEK_POW_BMS63EN_VSUM_UV = 14,
	AEK_POW_BMS63EN_VBATTCRIT_UV = 15,
	AEK_POW_BMS63EN_VBATWRN_UV = 16
}AEK_POW_BMS63EN_vcell_uv_fault_t;


/**
 * @brief   AEK_POW_BMS63EN VCELLOV fault enum
 */
typedef enum {
	AEK_POW_BMS63EN_VCELL1_OV = 0,
	AEK_POW_BMS63EN_VCELL2_OV = 1,
	AEK_POW_BMS63EN_VCELL3_OV = 2,
	AEK_POW_BMS63EN_VCELL4_OV = 3,
	AEK_POW_BMS63EN_VCELL5_OV = 4,
	AEK_POW_BMS63EN_VCELL6_OV = 5,
	AEK_POW_BMS63EN_VCELL7_OV = 6,
	AEK_POW_BMS63EN_VCELL8_OV = 7,
	AEK_POW_BMS63EN_VCELL9_OV = 8,
	AEK_POW_BMS63EN_VCELL10_OV = 9,
	AEK_POW_BMS63EN_VCELL11_OV = 10,
	AEK_POW_BMS63EN_VCELL12_OV = 11,
	AEK_POW_BMS63EN_VCELL13_OV = 12,
	AEK_POW_BMS63EN_VCELL14_OV = 13,
	AEK_POW_BMS63EN_VSUM_OV = 14,
	AEK_POW_BMS63EN_VBATTCRIT_OV = 15,
	AEK_POW_BMS63EN_VBATWRN_OV = 16
}AEK_POW_BMS63EN_vcell_ov_fault_t;


/**
 * @brief   AEK_POW_BMS63EN GPIO_UT_OT fault enum
 */
typedef enum {
	AEK_POW_BMS63EN_GPIO3_UT = 0,
	AEK_POW_BMS63EN_GPIO4_UT = 1,
	AEK_POW_BMS63EN_GPIO5_UT = 2,
	AEK_POW_BMS63EN_GPIO6_UT = 3,
	AEK_POW_BMS63EN_GPIO7_UT = 4,
	AEK_POW_BMS63EN_GPIO8_UT = 5,
	AEK_POW_BMS63EN_GPIO9_UT = 6,
	AEK_POW_BMS63EN_GPIO3_OT = 7,
	AEK_POW_BMS63EN_GPIO4_OT = 8,
	AEK_POW_BMS63EN_GPIO5_OT = 9,
	AEK_POW_BMS63EN_GPIO6_OT = 10,
	AEK_POW_BMS63EN_GPIO7_OT = 11,
	AEK_POW_BMS63EN_GPIO8_OT = 12,
	AEK_POW_BMS63EN_GPIO9_OT = 13
}AEK_POW_BMS63EN_gpio_ot_ut_fault_t;

/**
 * @brief   AEK_POW_BMS63EN VCELLOV fault enum
 */
typedef enum {
	AEK_POW_BMS63EN_VCELL1_BAL_UV = 0,
	AEK_POW_BMS63EN_VCELL2_BAL_UV = 1,
	AEK_POW_BMS63EN_VCELL3_BAL_UV = 2,
	AEK_POW_BMS63EN_VCELL4_BAL_UV = 3,
	AEK_POW_BMS63EN_VCELL5_BAL_UV = 4,
	AEK_POW_BMS63EN_VCELL6_BAL_UV = 5,
	AEK_POW_BMS63EN_VCELL7_BAL_UV = 6,
	AEK_POW_BMS63EN_VCELL8_BAL_UV = 7,
	AEK_POW_BMS63EN_VCELL9_BAL_UV = 8,
	AEK_POW_BMS63EN_VCELL10_BAL_UV = 9,
	AEK_POW_BMS63EN_VCELL11_BAL_UV = 10,
	AEK_POW_BMS63EN_VCELL12_BAL_UV = 11,
	AEK_POW_BMS63EN_VCELL13_BAL_UV = 12,
	AEK_POW_BMS63EN_VCELL14_BAL_UV = 13
}AEK_POW_BMS63EN_vcell_bal_uv_fault_t;

/**
 * @brief   AEK_POW_BMS63EN Cell PCB difference voltage reference.
 */
typedef uint16_t AEK_POW_BMS63EN_vpcbdiff_t;

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
/* Inclusion of the configurable data header, it contains mainly external
   declarations so it belongs to this section.*/

extern AEK_POW_BMS63EN_faultl_state_t AEK_POW_BMS63EN_faultl_state[];
extern AEK_POW_BMS63EN_gpio_state_t AEK_POW_BMS63EN_gpio_state[];

  
  /* General Functions */  
  /**
  * @brief    Enables and starts the open diagnostics over the GPIO's 3 - 9.
  * @note     This API can be applied to a single unit of a stack of devices.
  *           The diagnostic results are collected within the example function "isr_AEK_POW_BMS63EN_faultl".
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_EnableGPIOOpenOnDemandDiagnostic( unsigned AEK_POW_BMS63EN_devnum );
  
  /**
  * @brief    Evaluates the open diagnostics of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] vpcbdiff         the PCB difference reference voltage 
  * @return                     void.
  *
  * @api
  */
  void AEK_POW_BMS63EN_PCBOpenDiagnostic(  unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_vpcbdiff_t vpcbdiff );
  /* * * * * * * * * * */
  
  
  /**
  * @brief    Evaluates the Fault1 case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetFault1(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_fault1_t fault_case);

  /**
  * @brief    Evaluates the Fault2 case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetFault2(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_fault2_t fault_case);

  /**
  * @brief    Evaluates the VCell UnderVoltage Fault case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetVCELLUVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_uv_fault_t fault_case);

  /**
  * @brief    Evaluates the VCell OverVoltage Fault case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetVCELLOVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_ov_fault_t fault_case);

  /**
  * @brief    Evaluates the GPIO Under/Over Temperature Fault case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetGPIOOTUTFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_gpio_ot_ut_fault_t fault_case);

  /**
  * @brief    Evaluates the Balancing UnderVoltage Fault case of a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  uint8_t AEK_POW_BMS63EN_GetBALUVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_bal_uv_fault_t fault_case);

  /**
  * @brief    Evaluates the Balancing Fault case for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetFaults1(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Evaluates the Faults2 for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetFaults2(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Evaluates the VCell UnderVoltage Faults for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetVCELLUVFaults( unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Evaluates the VCell OverVoltage Faults for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetVCELLOVFaults(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Evaluates the GPIO Under/Over Temperature Faults for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetGPIOOTUTFaults(unsigned AEK_POW_BMS63EN_devnum);

  /**
  * @brief    Evaluates the Balancing Faults  for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetBALUVFaults(unsigned AEK_POW_BMS63EN_devnum);


  /**
  * @brief    Evaluates the Cell Open Faults  for  a given stack of cells.
  * @note     This API can be applied to a single unit of a stack of devices;
  *
  * @param[in] AEK_POW_BMS63EN_devnum     the selected AEK_POW_BMS63EN instances
  * @param[in] fault_case       the selected fault case
  * @return                     uint8_t 1: fault latched or 0: fault not latched.
  *
  * @api
  */
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetCellOpen(unsigned AEK_POW_BMS63EN_devnum);
	


  /* * * * * * * * * * * * * * */
 
 #endif 

#endif /* _AEK_POW_BMS63EN_DIAG_H_ */

/** @} */
