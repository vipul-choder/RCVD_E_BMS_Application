/***********************************************************************************
*
* Copyright © 2019, 2020, 2022 STMicroelectronics - All Rights Reserved
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
 * @file    AEK_POW_BMS63EN_id.c
 * @brief   AEK_POW_BMS63EN Driver code.
 *
 * @addtogroup AEK_POW_BMS63EN_ID
 * @{
 */

#include "AEK_POW_BMS63EN_id.h"
#include "AEK_COM_ISOSPI1_lld.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   AEK_POW_BMS63EN Resistor NTC GPIO.
 */
#define AEK_POW_BMS63EN_RP_NTC 10000 // ohm


/**
 * @brief   AEK_POW_BMS63EN Cell UV/OV ADC's resolution.
 */
#define AEK_POW_BMS63EN_VCELL_OV_UV_RES   22784 /**<    Undervoltage/Overvoltage cell resolution (in microvolt) */


/**
 * @brief   AEK_POW_BMS63EN Battery UV/OV ADC's resolution.
 */
#define AEK_POW_BMS63EN_VBATT_OV_UV_RES   364544  /**<    Undervoltage/Overvoltage battery resolution (in microvolt) */


/**
 * @brief   AEK_POW_BMS63EN Battery Overcurrent ADC's resolution.
 */
#define AEK_POW_BMS63EN_VBATT_OVC_CSA_RES   1330 /**<    Overcurrent battery resolution (in nanovolt) */

/**
 * @brief   AEK_POW_BMS63EN Current sensing ADC's timer resolution.
 */
#define AEK_POW_BMS63EN_TCYCLE_ADC_CUR_RES   328.25 /**<    Current sensing ADC's timer resolution (in microseconds) */

/**
 * @brief   AEK_POW_BMS63EN GPIO UV/OV resolution in 'absolute' mode.
 */
#define AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES    11392 /**<    Undervoltage/Overvoltage cell resolution (in microvolt) */


/**
 * @brief   AEK_POW_BMS63EN VBAT_SUM_RES.
 */
#define AEK_POW_BMS63EN_VSUM_BAT_RES         89/1000000

/**
 * @brief   AEK_POW_BMS63EN VCELL_RES.
 */
#define AEK_POW_BMS63EN_VCELL_RES         89/1000000


/**
 * @brief   AEK_POW_BMS63EN VCELL_RES.
 */
#define AEK_POW_BMS63EN_VISENSE_RES         1.33/1000000

/**
 * @brief   AEK_POW_BMS63EN VGPIO ABS_RES
 */
#define VGPIO_ABS_RES  89/1000000

/**
 * @brief   AEK_POW_BMS63EN VGPIO ABS_RES
 */
#define VGPIO_RATIO_RES  0.000015

/**
 * @brief   AEK_POW_BMS63EN WakeUp time in milliseconds.
 */
#define AEK_POW_BMS63EN_WAKEUP_TIME 3



#define ABS(x) (x>0) ? x : (-x)

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/* * * * * * * * * * * * * * * * * * * * */
/*   G E N E R A L   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * * * * */
/*
 *  AEK_POW_BMS63EN Driver initialization.
**/
void AEK_POW_BMS63EN_Init(void) {
  int i = 0;
  AEK_POW_BMS63EN_cfg_objects_init();
  AEK_POW_BMS63EN_Start(&AEK_POW_BMS63EN_Drv, &AEK_POW_BMS63EN_config);
	/* Enable Tranceiver and Trasmission*/
    for(i = 0; i<AEK_POW_BMS63EN_N_TRANCEIVER;i++){
    	AEK_COM_ISOSPI_EnableTransceiver(i);
    	AEK_COM_ISOSPI_EnableTransceiverComm(i);
		AEK_COM_ISOSPI_ISOTX_Attenuate(i);
		AEK_COM_ISOSPI_SetAsSlave(i);
    }

    /*StartUpWKUP Driver with all AEK_POW_BMS63ENE devices*/;
	AEK_POW_BMS63EN_StartUpWKUP();

	for(i = 0; i<AEK_POW_BMS63EN_N_TRANCEIVER;i++){
		AEK_COM_ISOSPI_ConfigISOFreq(i,AEK_POW_BMS63EN_Drv.param_conf[0].AEK_POW_BMS63EN_iso_freq);
	}

	/*Set Fault sts*/
    for(i = 0; i<AEK_POW_BMS63EN_N_TRANCEIVER;i++){
    		AEK_COM_ISOSPI_GetFault(i);
    }
    
	AEK_POW_BMS63EN_ParameterConfiguration();
}

 /*
  *  AEK_POW_BMS63EN Driver Parameter Configuration.
 **/
 void AEK_POW_BMS63EN_ParameterConfiguration(void){
	 int j =1;
	 uint8_t cell_idx = 0;

	 for(j=1;j<(AEK_POW_BMS63EN_N_BMS+1);j++) {

		    /*Enable Couloub Counting Routine to read current synchronized with Voltage readings*/
	 	    if(AEK_POW_BMS63EN_Drv.param_conf[j-1].coulomb_counting_en == AEK_POW_BMS63EN_CoulombCounting_Enabled){
	 	    	AEK_POW_BMS63EN_EnableCoulombCounting(AEK_POW_BMS63EN_DEVICE_ID(j));
	 	    }
	 	    else{}

	 		/* VBATT OV-UV threshold */
	 		AEK_POW_BMS63EN_SetVBattOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_Drv.param_conf[j-1].VBattOVThreshold);
	 		AEK_POW_BMS63EN_SetVBattUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_Drv.param_conf[j-1].VBattUVThreshold);

	 		/* VCELL OV threshold - VCELL UV threshold */
	 		AEK_POW_BMS63EN_SetVCellOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_Drv.param_conf[j-1].VCellOVThreshold);
	 		AEK_POW_BMS63EN_SetVCellUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_Drv.param_conf[j-1].VCellUVThreshold);

	 		/* Set GPIO Configuration */
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_3, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio3_conf);
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_4, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio4_conf);
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_5, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio5_conf);
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_6, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio6_conf);
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_9, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio9_conf);
	 		AEK_POW_BMS63EN_ConfigGPIO( AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_8, AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio8_conf);

	 		/*GPIO Configuration */
	 		if(AEK_POW_BMS63EN_Drv.param_conf[j-1].gpio_meas == AEK_POW_BMS63EN_RATIOMETRIC){
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_3);
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_4);
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_5);
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_6);
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_9);
	 			AEK_POW_BMS63EN_SetGPIOModeRatiometric(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_8);
	 		}
	 		else{
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_3);
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_4);
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_5);
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_6);
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_9);
	 			AEK_POW_BMS63EN_SetGPIOModeAbsolute(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_8);
	 		}

	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_3, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO3OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_3, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO3UVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_4, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO4OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_4, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO4UVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_5, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO5OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_5, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO5UVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_6, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO6OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_6, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO6UVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_9, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO9OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_9, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO9UVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOOVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_8, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO8OVThreshold);
	 		AEK_POW_BMS63EN_SetGPIOUVThreshold(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_gpio_8, AEK_POW_BMS63EN_Drv.param_conf[j-1].GPIO8UVThreshold);

			/*Mask Fault GPIO7*/
			AEK_POW_BMS63EN_GPIO7_OT_UT_Mask(AEK_POW_BMS63EN_DEVICE_ID(j));

	 		/* Cells Enabling */
			//Enable Model Cells by reading configuration
			for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx ++){
				if(AEK_POW_BMS63EN_isEnabled(AEK_POW_BMS63EN_DEVICE_ID(j), cell_idx)){
			 	    AEK_POW_BMS63EN_EnableCell( AEK_POW_BMS63EN_DEVICE_ID(j),cell_idx);
				}
				else{
			 	    AEK_POW_BMS63EN_DisableCell( AEK_POW_BMS63EN_DEVICE_ID(j),cell_idx);
				}
			}

			/* Set Balancing mode Manual */
	 		if(AEK_POW_BMS63EN_Drv.param_conf[j-1].cell_bal_mode == AEK_POW_BMS63EN_cell_man_bal_mode){
	 			AEK_POW_BMS63EN_SetBalancingMode(AEK_POW_BMS63EN_DEVICE_ID(j),AEK_POW_BMS63EN_cell_manual_bal_mode);
	 		}
	 		else{
	 			AEK_POW_BMS63EN_SetBalancingMode(AEK_POW_BMS63EN_DEVICE_ID(j),AEK_POW_BMS63EN_cell_timed_bal_mode);
	 		}

	 		if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_290us){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_290us);
	 	    }
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_1ms16){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_1ms16);
	 		}
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_2ms32){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_2ms32);
	 		}
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_18ms56){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_18ms56);
	 		}
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_37ms12){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_37ms12);
	 		}
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_74ms24){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_74ms24);
	 		}
	 		else if(AEK_POW_BMS63EN_Drv.param_conf[j-1].adc_filter_soc == AEK_POW_BMS63EN_adc_flt_soc_148ms48){
	 		    AEK_POW_BMS63EN_SetADCFilterSOC(AEK_POW_BMS63EN_DEVICE_ID(j), AEK_POW_BMS63EN_adc_filter_soc_148ms48);
	 		}
	 		else{}
	 }

 }


/*
 *    Configures the isolated communication frequency.
**/
void AEK_POW_BMS63EN_ConfigISOFreq(AEK_POW_BMS63EN_iso_freq_t AEK_POW_BMS63EN_iso_freq ) {
 
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;
  
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_DEV_GEN_CFG);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_DEV_GEN_CFG);


  switch( AEK_POW_BMS63EN_iso_freq ) {
  
    case AEK_POW_BMS63EN_iso_freq_low :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO3us);
      AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEV_GEN_CFG, AEK_POW_BMS63EN_reg);
      break;
      
    case AEK_POW_BMS63EN_iso_freq_high :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO375ns);
      AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEV_GEN_CFG, AEK_POW_BMS63EN_reg);
      break;
	  
	  default:
	  break;
      
  } /* switch( AEK_POW_BMS63EN_iso_freq ) */
  
}  
  

/*
 *    Disables the communication timeout.
**/
void AEK_POW_BMS63EN_DisableCommTimeout( unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BAL_1_COMM_TIMEOUT_DIS;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1, AEK_POW_BMS63EN_reg);
  
}
  
  
/*
 *    Enables the communication timeout.
**/
void AEK_POW_BMS63EN_EnableCommTimeout(unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;
  
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_1_COMM_TIMEOUT_DIS);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1, AEK_POW_BMS63EN_reg);
  
};


/*
 *  Sends the device(s) to into the 'SLEEP' or 'SILENT BALANCING' state.
**/
void AEK_POW_BMS63EN_EnterSleepMode( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_FSM_GO2SLP;
  
  if( !(AEK_POW_BMS63EN_read & AEK_POW_BMS63EN_BAL_1_SLP_BAL_CONF) ) {
    (&(AEK_POW_BMS63EN_Drv.status->device_status[AEK_POW_BMS63EN_devnum-1]))->device_state = AEK_POW_BMS63EN_SLEEP;
  } else {
    (&(AEK_POW_BMS63EN_Drv.status->device_status[AEK_POW_BMS63EN_devnum-1]))->device_state = AEK_POW_BMS63EN_SILENT_BALANCING;
  };  /* if( !(AEK_POW_BMS63EN_read & (AEK_POW_BMS63EN_register_t(AEK_POW_BMS63EN_BAL_1_SLP_BAL_CONF))) ) */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM, AEK_POW_BMS63EN_write);
 
}


/*
 *    Performs a software reset.
**/
void AEK_POW_BMS63EN_SWReset( unsigned AEK_POW_BMS63EN_devnum) {
 
  uint8_t dev_idx;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_FSM_SW_RST | AEK_POW_BMS63EN_FSM_GO2SLP) ;
  
  if( AEK_POW_BMS63EN_devnum != 0 ) {
    (&(AEK_POW_BMS63EN_Drv.status->device_status[AEK_POW_BMS63EN_devnum-1]))->device_state = AEK_POW_BMS63EN_SLEEP;
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM, AEK_POW_BMS63EN_write);
  } else {
    for( dev_idx = 1; dev_idx <= AEK_POW_BMS63EN_N_BMS; dev_idx++ ) {
      (&(AEK_POW_BMS63EN_Drv.status->device_status[AEK_POW_BMS63EN_devnum-1]))->device_state = AEK_POW_BMS63EN_SLEEP;
    } /* for( dev_idx = 0; dev_idx < AEK_POW_BMS63ENp->n_stacked_devices; dev_idx++ ) */
    AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_FSM, AEK_POW_BMS63EN_write);
  };  /* if( ( AEK_POW_BMS63EN_devnum != 0 ) */
 
}  

 
/*
 *    Wakes up the overall stack of devices.
**/

void AEK_POW_BMS63EN_StartUpWKUP() {

  uint8_t chip_idx = 1;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read=0, AEK_POW_BMS63EN_write=0;

  //Wakeup chip_idx device from spleep status and wait wakup timing
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(2), AEK_POW_BMS63EN_DEV_GEN_CFG);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(2), AEK_POW_BMS63EN_DEV_GEN_CFG);
  osalThreadDelayMilliseconds(AEK_POW_BMS63EN_WAKEUP_TIME);

  do {

        //Send Broadcast command with:
        // - chip_idx = X (starting from 1)
        // - ISO_TX_EN_H = 1
        // - ISOFREQ_SEL = 00
        // - HEARTBEAT_EN = 0 optional
        // - FAULTL_FORICE = 0 optional
        // - FAULT_EN = 1 (to propagate Fault status) optional
        AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t) (AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO3us & AEK_POW_BMS63EN_DEV_GEN_CFG_CHIP_ID(chip_idx));
        AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t) (AEK_POW_BMS63EN_write | AEK_POW_BMS63EN_DEV_GEN_CFG_ISOTX_EN_H);
        AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t) (AEK_POW_BMS63EN_write & ~(AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_EN));
        AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t) (AEK_POW_BMS63EN_write & ~(AEK_POW_BMS63EN_DEV_GEN_CFG_FAULTL_FORCE));
        AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t) (AEK_POW_BMS63EN_write | AEK_POW_BMS63EN_DEV_GEN_CFG_FAULT_EN);
 	  	AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEV_GEN_CFG, AEK_POW_BMS63EN_write);

 	  	// Enable VTREF optional
		if(AEK_POW_BMS63EN_Drv.param_conf[chip_idx-1].AEK_POW_BMS63EN_VTREF_sts == AEK_POW_BMS63EN_VTREF_ALWAYS_ENABLED){
			AEK_POW_BMS63EN_SetVTREFAlwaysEnabled(AEK_POW_BMS63EN_DEVICE_ID(chip_idx));
		}
		else if(AEK_POW_BMS63EN_Drv.param_conf[chip_idx-1].AEK_POW_BMS63EN_VTREF_sts == AEK_POW_BMS63EN_VTREF_ON_CONV_ENABLED){
			AEK_POW_BMS63EN_SetVTREFEnabled(AEK_POW_BMS63EN_DEVICE_ID(chip_idx));
		}
		else{
			AEK_POW_BMS63EN_SetVTREFDisabled(AEK_POW_BMS63EN_DEVICE_ID(chip_idx));
		}
        
		
		//Setting Communication Timeout
		AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(chip_idx), AEK_POW_BMS63EN_FASTCH_BALUV);
		AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(chip_idx), AEK_POW_BMS63EN_FASTCH_BALUV);
		if(AEK_POW_BMS63EN_Drv.param_conf[0].commtimeout == AEK_POW_BMS63EN_commtimeout_2048ms){
			AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_2048ms;
		}
		else if(AEK_POW_BMS63EN_Drv.param_conf[0].commtimeout == AEK_POW_BMS63EN_commtimeout_1024ms){
			AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_1024ms;
		}
		else{
			AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_32ms;
		}
	
		AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(chip_idx), AEK_POW_BMS63EN_FASTCH_BALUV, AEK_POW_BMS63EN_write);

		//Reading DEV_GEN_CFG and Check ID if ID is correct
		AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(chip_idx), AEK_POW_BMS63EN_DEV_GEN_CFG);
		AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(chip_idx), AEK_POW_BMS63EN_DEV_GEN_CFG);
		if ((AEK_POW_BMS63EN_read>>13 & 0b11111) == chip_idx) chip_idx++;


  }
  while (chip_idx <= AEK_POW_BMS63EN_N_BMS);

 //Sending Broadcast command with:
 // - OUT_RES_TX = 11
 // - ISOFREQ_SEL = 11
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_DEV_GEN_CFG);
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_DEV_GEN_CFG);
 AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write | ( AEK_POW_BMS63EN_DEV_GEN_CFG_OUT_RES_TX_ISO_MASK));
 if(AEK_POW_BMS63EN_Drv.param_conf[0].AEK_POW_BMS63EN_iso_freq == AEK_POW_BMS63EN_iso_freq_high){
	AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write | (AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO375ns));
 }
 else{
	AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write | (AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO3us));
 }
 AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEV_GEN_CFG, AEK_POW_BMS63EN_write);

 //Sending Write Command to the farthest unit with:
 // - FARTHEST_UNIT = 1
 // - ISOTX_EN_H = 0 if not dual ring
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(AEK_POW_BMS63EN_N_BMS), AEK_POW_BMS63EN_DEV_GEN_CFG);
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(AEK_POW_BMS63EN_N_BMS), AEK_POW_BMS63EN_DEV_GEN_CFG);
 AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write | (AEK_POW_BMS63EN_DEV_GEN_CFG_FARTHEST_UNIT));
#ifndef DUAL_ACCESS_RING
 AEK_POW_BMS63EN_write =(AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write & (~(AEK_POW_BMS63EN_DEV_GEN_CFG_ISOTX_EN_H)));
#endif
 AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(AEK_POW_BMS63EN_N_BMS), AEK_POW_BMS63EN_DEV_GEN_CFG, AEK_POW_BMS63EN_write);

 //Sending Broadcast command with:
 // - LOCK_ISOH_ISOFREQ = 1
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_BAL_3);
 AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_BAL_3);
 AEK_POW_BMS63EN_write =(AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_write | ( AEK_POW_BMS63EN_BAL_3_LOCK_ISOH_ISOFREQ));
 AEK_POW_BMS63EN_SPIBroadcastAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_BAL_3, AEK_POW_BMS63EN_write);
}



/*
 *    Gets the current state.
**/
AEK_POW_BMS63EN_dev_state_t AEK_POW_BMS63EN_GetState( unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg = 0;
  AEK_POW_BMS63EN_dev_state_t AEK_POW_BMS63EN_dev_state = 0;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FSM);
   
  AEK_POW_BMS63EN_reg = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_reg & AEK_POW_BMS63EN_FSM_FSM_STATUS_MASK);
    
  switch( AEK_POW_BMS63EN_reg ) {
    case AEK_POW_BMS63EN_FSM_FSM_STATUS_SLEEP :
      AEK_POW_BMS63EN_dev_state = AEK_POW_BMS63EN_SLEEP;
      break;
        
    case AEK_POW_BMS63EN_FSM_FSM_STATUS_INIT :
      AEK_POW_BMS63EN_dev_state = AEK_POW_BMS63EN_INIT;
      break;
      
    case AEK_POW_BMS63EN_FSM_FSM_STATUS_NORMAL :
      AEK_POW_BMS63EN_dev_state = AEK_POW_BMS63EN_NORMAL;
      break;
                 
    case AEK_POW_BMS63EN_FSM_FSM_STATUS_CYC_WKUP :
      AEK_POW_BMS63EN_dev_state = AEK_POW_BMS63EN_CYCLIC_WAKEUP;
      break;
      
    default : /***/;
      break;
        
  } /* switch( AEK_POW_BMS63EN_dev_state ) { */
  
  (&(AEK_POW_BMS63EN_Drv.status->device_status[AEK_POW_BMS63EN_devnum-1]))->device_state = AEK_POW_BMS63EN_dev_state;
  
  return AEK_POW_BMS63EN_dev_state;
 
}   
/* * * * * * * * * * * * * * * * * * * * * * * * */ 


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*     A   p   p   l   i  c   a   t   i   o   n     F   u   n   c   t   i   o   n   s      */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 *    Performs the Coulomb counting.
**/

void AEK_POW_BMS63EN_CoulombCounterReset(unsigned AEK_POW_BMS63EN_devnum) {
	  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_burst_read[18];
	 /* 1. reading the current Coulomb counter values */
	 AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD3, &AEK_POW_BMS63EN_burst_read[0]);
}



float AEK_POW_BMS63EN_CoulombCounting(unsigned AEK_POW_BMS63EN_devnum, float qtc_R_shunt, float qtk) {

  uint32_t qc_burst_value;
  float delta_t, qtc, qtc_r, vdiff_curr_sense;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_burst_read[18];


  /* 1. reading the current Coulomb counter values */
  AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD3, &AEK_POW_BMS63EN_burst_read[0]);
  
  qc_burst_value = (uint32_t)((AEK_POW_BMS63EN_burst_read[1] << 16) | (AEK_POW_BMS63EN_burst_read[2] & AEK_POW_BMS63EN_BURST_CMD3_FR3_COULOMBCOUNTER_LSB_MASK));

  if( qc_burst_value & (1U << 31) ) {
    /* negative value */    
    vdiff_curr_sense = -(float)((((uint32_t)(~qc_burst_value)-1) * ((float)(AEK_POW_BMS63EN_VBATT_OVC_CSA_RES)))/(float)1000);
  } else {
    vdiff_curr_sense = (float)(qc_burst_value*AEK_POW_BMS63EN_VBATT_OVC_CSA_RES)/(float)1000;
  } /* if( qc_burst_value & (1U << 31) ) */
  
  //delta_t = (float)((AEK_POW_BMS63EN_burst_read[0] & AEK_POW_BMS63EN_BURST_CMD3_FR1_COULOMBCNTTIME_MASK) * (float)AEK_POW_BMS63EN_TCYCLE_ADC_CUR_RES);
  delta_t = (float)AEK_POW_BMS63EN_TCYCLE_ADC_CUR_RES;
  
  qtc = (float)(vdiff_curr_sense * delta_t)/(float)qtc_R_shunt;
  
  qtc_r = (float)(qtk + ((float)(qtc)/(float)3600000000)); 
  
  if( qtc_r > 0 ) {
    return qtc_r; 
  } else {
    return 0; 
  } /* if( qtc > 0 ) */

}

/**
	 *  Get Configuration Override latched status
	 */
uint8_t AEK_POW_BMS63EN_Get_Conf_OVL(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

    AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(AEK_POW_BMS63EN_devnum), AEK_POW_BMS63EN_ADCV_CONV);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(AEK_POW_BMS63EN_devnum), AEK_POW_BMS63EN_ADCV_CONV);

	 return (AEK_POW_BMS63EN_read>>14 & 1);
}
  
/*
 *    Disables the Coulomb counting.
**/
void AEK_POW_BMS63EN_DisableCoulombCounting( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_CSA_GPIO_MSK_COULOMBCOUNTER_EN);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK, AEK_POW_BMS63EN_reg);

}  


/*
 *    Enables the Coulomb counting.
**/
void AEK_POW_BMS63EN_EnableCoulombCounting(unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_CSA_GPIO_MSK_COULOMBCOUNTER_EN;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK, AEK_POW_BMS63EN_reg);

}  



/**
 *  Mask Over/Under Temperature fault detection for GPIO7
 */
void AEK_POW_BMS63EN_GPIO7_OT_UT_Mask( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);

  AEK_POW_BMS63EN_reg |= 0x10;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK, AEK_POW_BMS63EN_reg);

}

/**
 *  Mask Over/Under Temperature fault detection
 */
void AEK_POW_BMS63EN_GPIO_OT_UT_Mask( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);

  AEK_POW_BMS63EN_reg |= 0x7F;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK, AEK_POW_BMS63EN_reg);

}

/**
 *    Mask CSA GPIO over/under current detection
*/
void AEK_POW_BMS63EN_GPIO_CSA_Mask( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);

  AEK_POW_BMS63EN_reg |= 0xFFF;  //Instead 400

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK, AEK_POW_BMS63EN_reg);

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_GPIO_MSK);
}




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



/* * * * * * * * * * * * * * * * */
/*   A D C   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * */ 
/*
 *    Sets the ADC's continous mode.
**/
void AEK_POW_BMS63EN_SetADCContinuousMode( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  
  AEK_POW_BMS63EN_reg |= AEK_POW_BMS63EN_ADCV_CONV_CYCLIC_CONTINOUS;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_reg);

};


/*
 *  Sets the ADC's filter time.
**/
void AEK_POW_BMS63EN_SetADCFilterSOC( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adc_filter_soc_t filter_soc) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_ADC_FILTER_SOC_MASK);
  
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_ADC_FILTER_SOC(filter_soc);

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_reg);
  
}


/*
 *    Sets the ADC's sampling cycle period.
**/
void AEK_POW_BMS63EN_SetADCTcycle(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adc_conv_tcycle_t tcycle) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_MASK);
  
  switch( tcycle ) {
    case  AEK_POW_BMS63EN_adc_conv_tcycle_100ms :
      break;
      
    case AEK_POW_BMS63EN_adc_conv_tcycle_200ms :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_200ms;
      break;
      
    case AEK_POW_BMS63EN_adc_conv_tcycle_400ms :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_400ms;
      break;
    
    case AEK_POW_BMS63EN_adc_conv_tcycle_800ms :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_800ms;
      break;
      
    case AEK_POW_BMS63EN_adc_conv_tcycle_1s6 :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_1s6;
    break;
    
    case AEK_POW_BMS63EN_adc_conv_tcycle_3s2 :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_3s2;
      break;      
       
    case AEK_POW_BMS63EN_adc_conv_tcycle_6s4 :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_6s4;
      break;
      
    case AEK_POW_BMS63EN_adc_conv_tcycle_12s8 :
      AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_12s8;
      break; 
  } /* switch( tcycle ) */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_reg);
  
};


/*
 *    Sets the ADC's overcurrent (CSA) threshold.
**/
void AEK_POW_BMS63EN_SetVBattOVCThreshold( unsigned AEK_POW_BMS63EN_devnum, int32_t vbatt_ovc_thr) {
  
  uint32_t vbatt_ovc_thr_val;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  if( vbatt_ovc_thr < 0 ) {
    vbatt_ovc_thr_val = (((ABS(vbatt_ovc_thr))*1000)/AEK_POW_BMS63EN_VBATT_OVC_CSA_RES);
    /* now compute the 2's complement for init */
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(((~(uint32_t)vbatt_ovc_thr_val) + (uint32_t)0x1) & 0x3FFFF);
  } else {
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((vbatt_ovc_thr*1000)/AEK_POW_BMS63EN_VBATT_OVC_CSA_RES);
  } /* if( vabtt_ovc_thr < 0 ) */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_THRESH_NORM, AEK_POW_BMS63EN_write);
  
};


/*
 *    Sets the ADC's overvoltage threshold (sum of cells).
**/
void AEK_POW_BMS63EN_SetVBattOVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint32_t vbatt_ov_thr) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH);
  

  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_OV_TH_MASK);
  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((vbatt_ov_thr * 1000)/AEK_POW_BMS63EN_VBATT_OV_UV_RES);
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_OV_TH(AEK_POW_BMS63EN_write);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH, AEK_POW_BMS63EN_reg);
  
};


/*
 *    Sets the ADC's undervoltage threshold (sum of cells).
**/
void AEK_POW_BMS63EN_SetVBattUVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint32_t vbatt_uv_thr) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_UV_TH_MASK);
  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((vbatt_uv_thr * 1000)/AEK_POW_BMS63EN_VBATT_OV_UV_RES);
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_UV_TH(AEK_POW_BMS63EN_write);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATT_SUM_TH, AEK_POW_BMS63EN_reg);
  
};


/*
 *    Sets the ADC's overvoltage threshold.
**/
void AEK_POW_BMS63EN_SetVCellOVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint16_t vcell_ov_thr) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_write;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLOV_MASK);
  
  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((vcell_ov_thr * 1000)/AEK_POW_BMS63EN_VCELL_OV_UV_RES);

  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLOV(AEK_POW_BMS63EN_write);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV, AEK_POW_BMS63EN_reg);
  
};


/*
 *    Sets the ADC's undervoltage threshold.
**/
void AEK_POW_BMS63EN_SetVCellUVThreshold(unsigned AEK_POW_BMS63EN_devnum, uint16_t vcell_uv_thr) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_write;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV);
  
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLUV_MASK);
  
  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((vcell_uv_thr * 1000)/AEK_POW_BMS63EN_VCELL_OV_UV_RES);

  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLUV(AEK_POW_BMS63EN_write);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_THRESH_UV_OV, AEK_POW_BMS63EN_reg);
  
};

/*
 *    Get VTREF Regulator
**/
float AEK_POW_BMS63EN_GetVTREFVoltMeasurement(unsigned AEK_POW_BMS63EN_devnum) {

	  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;


	  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VTREF);
	  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VTREF);

	  return ((float)((uint16_t)(AEK_POW_BMS63EN_read & AEK_POW_BMS63EN_VCELL1_VCELL1_MASK))) * AEK_POW_BMS63EN_VCELL_RES;
};



/*
 *    Sets VTREF Regulator  Enabled
**/
void AEK_POW_BMS63EN_SetVTREFAlwaysEnabled( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);

  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_ENABLED);
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_D_RDY_VTREF);

  AEK_POW_BMS63EN_reg |= AEK_POW_BMS63EN_VTREF_ENABLED;

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2, AEK_POW_BMS63EN_reg);

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
};


/*
 *    Sets VTREF Regulator  Enabled
**/
void AEK_POW_BMS63EN_SetVTREFEnabled( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);

  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_ENABLED);
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_D_RDY_VTREF);

  AEK_POW_BMS63EN_reg |= AEK_POW_BMS63EN_VTREF_ENABLED;
  AEK_POW_BMS63EN_reg |= AEK_POW_BMS63EN_VTREF_D_RDY_VTREF;

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2, AEK_POW_BMS63EN_reg);

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2);
};


/*
 *    Sets VTREF Regulator  Disabled
**/
void AEK_POW_BMS63EN_SetVTREFDisabled( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_NCYCLE_PROG_2);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_DEVICE_ID(1), AEK_POW_BMS63EN_NCYCLE_PROG_2);

  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_ENABLED);
  AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_VTREF_D_RDY_VTREF);

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_2, AEK_POW_BMS63EN_reg);

};

/*
 *    Starts the manual conversion for a stack of cells.
**/
uint8_t AEK_POW_BMS63EN_StartManualConversion(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_adcv_conv_opt_t GPIO_CONV ,
		AEK_POW_BMS63EN_adcv_conv_opt_t GPIO_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t CELL_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t BAL_TERM_CONV, AEK_POW_BMS63EN_adcv_conv_opt_t HWSC, AEK_POW_BMS63EN_adcv_conv_opt_t ADC_CROSS_CHECK) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);

  if( ((AEK_POW_BMS63EN_write & AEK_POW_BMS63EN_ADCV_CONV_DUTY_ON) >> 12) && ((AEK_POW_BMS63EN_write & AEK_POW_BMS63EN_ADCV_CONV_SOC) >> 15) ){
	  return 0;
  }
  else{
		AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_SOC);
		if(GPIO_CONV == AEK_POW_BMS63EN_GPIO_CONV_EN){
			AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_GPIO_CONV);
		}else if(GPIO_CONV == AEK_POW_BMS63EN_GPIO_CONV_DIS){
			AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_GPIO_CONV);
		}
		else{}
		if(GPIO_TERM_CONV == AEK_POW_BMS63EN_GPIO_TERM_CONV_EN){
					AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_GPIO_TERM_CONV);
				}else if(GPIO_TERM_CONV == AEK_POW_BMS63EN_GPIO_TERM_CONV_DIS){
					AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_GPIO_TERM_CONV);
				}
		else{}
		if(CELL_TERM_CONV == AEK_POW_BMS63EN_CELL_TERM_CONV_EN){
					AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_CELL_TERM_CONV);
				}else if(CELL_TERM_CONV == AEK_POW_BMS63EN_CELL_TERM_CONV_DIS){
					AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_CELL_TERM_CONV);
				}
		else{}
		if(BAL_TERM_CONV == AEK_POW_BMS63EN_BAL_TERM_CONV_EN){
					AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_BAL_TERM_CONV);
				}else if(BAL_TERM_CONV == AEK_POW_BMS63EN_BAL_TERM_CONV_DIS){
					AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_BAL_TERM_CONV);
				}
		else{}
		if(HWSC == AEK_POW_BMS63EN_HWSC_EN){
					AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_HWSC);
				}else if(HWSC == AEK_POW_BMS63EN_HWSC_DIS){
					AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_HWSC);
				}
		else{}
		if(ADC_CROSS_CHECK == AEK_POW_BMS63EN_ADC_CROSS_CHECK_EN){
					AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_ADC_CROSS_CHECK);
				}else if(ADC_CROSS_CHECK == AEK_POW_BMS63EN_ADC_CROSS_CHECK_DIS){
					AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_ADC_CROSS_CHECK);
				}
		else{}
		if((AEK_POW_BMS63EN_write & AEK_POW_BMS63EN_ADCV_CONV_OVR_LATCH) >> 14){
		  AEK_POW_BMS63EN_write &=(AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_ADCV_CONV_CONF_CYCLIC_EN);
		}

		AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);

		do {
		  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
		  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
		} while ((AEK_POW_BMS63EN_write & AEK_POW_BMS63EN_ADCV_CONV_DUTY_ON) >> 12);
  }

   if((AEK_POW_BMS63EN_write & AEK_POW_BMS63EN_ADCV_CONV_OVR_LATCH) >> 14){
	   return 0;
   }
   else {
	   return 1;
   }

};   
/* * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
/*     C   e   l   l   s     F   u   n   c   t   i   o   n   s     */  
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

/*
 *    Disables a selected cell.
**/
void AEK_POW_BMS63EN_DisableCell( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id) {

  uint8_t cell_idx;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  if( cell_id != AEK_POW_BMS63EN_CELL_ALL ) {
    AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN);
    AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN);
    if( (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_id)->cell_conn != AEK_POW_BMS63EN_CELL_UNCONNECTED ) {
      AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~(AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN << (uint8_t)cell_id));
      (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_id)->cell_en = AEK_POW_BMS63EN_CELL_DISABLED;
    } /* if( (&(((AEK_POW_BMS63ENp->status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1) ... */
  } else { /* if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) */
    AEK_POW_BMS63EN_write = 0;
    for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
      if( (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_conn != AEK_POW_BMS63EN_CELL_UNCONNECTED ) {
        AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~(AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN << (uint8_t)cell_idx));
        (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_en = AEK_POW_BMS63EN_CELL_DISABLED;
      } /* if( (&(((AEK_POW_BMS63ENp->status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1 ... */
    } /* for( cell_idx = 0; cell_idx < 14; cell_dx++ ) */
  } /* if( cell_id != AEK_POW_BMS63EN_CELL_ALL ) */
    
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN, AEK_POW_BMS63EN_write);
  
}


/*
 *    Disables the balancing of a selected cell.
**/
void AEK_POW_BMS63EN_DisableCellBalancing( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) {
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_DIS |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_DIS |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_DIS |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_DIS |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_DIS |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_DIS  |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_DIS  |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_DIS  );
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT, AEK_POW_BMS63EN_write);
  
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_DIS |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_DIS |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_DIS |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_DIS |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_DIS |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_DIS );
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT, AEK_POW_BMS63EN_write);
  
  } else { 
  
    if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) {
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
    } else {
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT);
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT);
    } /* if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) */
      
    switch( cell_id ) {
      case AEK_POW_BMS63EN_CELL1 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_DIS;
        break;
      case AEK_POW_BMS63EN_CELL2 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_DIS;
        break;
      case AEK_POW_BMS63EN_CELL3 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_DIS;
        break;
      case AEK_POW_BMS63EN_CELL4 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_DIS;
        break;
      case AEK_POW_BMS63EN_CELL5 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_DIS;
        break;
      case AEK_POW_BMS63EN_CELL6 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_DIS;
        break;
      case AEK_POW_BMS63EN_CELL7 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_DIS;
        break;
      case AEK_POW_BMS63EN_CELL8 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_DIS;
        break;
      case AEK_POW_BMS63EN_CELL9 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_DIS;
        break;
      case AEK_POW_BMS63EN_CELL10 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_DIS;
        break;
      case AEK_POW_BMS63EN_CELL11 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_DIS;
        break;
      case AEK_POW_BMS63EN_CELL12 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_DIS;
        break;
      case AEK_POW_BMS63EN_CELL13 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_DIS;
        break;
      case AEK_POW_BMS63EN_CELL14 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_DIS;
        break;
      default : /*** nothing to do here! ***/; break;
    } /* switch( cell_id ) */
      
    if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) {
      AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT, AEK_POW_BMS63EN_write);
    } else {
      AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT, AEK_POW_BMS63EN_write);
    } /* if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) */
    
  } /* if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) */
  
}


/*
 *    Enables the balancing of a selected cell.
**/
void AEK_POW_BMS63EN_EnableCellBalancing(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
  
  if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) {
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_EN |
                                     AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_EN );
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT, AEK_POW_BMS63EN_write);
  
    AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_EN |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_EN |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_EN |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_EN |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_EN |
                                     AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_EN );
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT, AEK_POW_BMS63EN_write);
  
  } else { 
  
    if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) {
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
    } else {
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT);
      AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT);
    } /* if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) */
      
    switch( cell_id ) {
      case AEK_POW_BMS63EN_CELL1 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_EN;
        break;
      case AEK_POW_BMS63EN_CELL2 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_EN;
        break;
      case AEK_POW_BMS63EN_CELL3 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_EN;
        break;
      case AEK_POW_BMS63EN_CELL4 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_EN;
        break;
      case AEK_POW_BMS63EN_CELL5 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_EN;
        break;
      case AEK_POW_BMS63EN_CELL6 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_EN;
        break;
      case AEK_POW_BMS63EN_CELL7 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_EN;
        break;
      case AEK_POW_BMS63EN_CELL8 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_EN;
        break;
      case AEK_POW_BMS63EN_CELL9 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_EN;
        break;
      case AEK_POW_BMS63EN_CELL10 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_EN;
        break;
      case AEK_POW_BMS63EN_CELL11 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_EN;
        break;
      case AEK_POW_BMS63EN_CELL12 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_EN;
        break;
      case AEK_POW_BMS63EN_CELL13 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_EN;
        break;
      case AEK_POW_BMS63EN_CELL14 :
        AEK_POW_BMS63EN_write &= ~((AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_MASK);
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_EN;
        break;
      default : /*** nothing to do here! ***/; break;
    } /* switch( cell_id ) */
      
    if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) {
      AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT, AEK_POW_BMS63EN_write);
    } else {
      AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL14_7ACT, AEK_POW_BMS63EN_write);
    } /* if( (cell_id >= AEK_POW_BMS63EN_CELL1) && (cell_id <= AEK_POW_BMS63EN_CELL6) ) */
    
  } /* if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) */
  
}


/*
 *    Disables the current balancing on the even cells.
**/
void AEK_POW_BMS63EN_DisableBalCurrentEvenCells( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  
};


/*
 *    Disables the current balancing on the odd cells.
**/
void AEK_POW_BMS63EN_DisableBalCurrentOddCells(unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  
};


/*
 *    Enables the current balancing on the even cells.
**/
void AEK_POW_BMS63EN_EnableBalCurrentEvenCells( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
    
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  
};
  
  
/*
 *    Enables the current balancing on the odd cells.
**/
void AEK_POW_BMS63EN_EnableBalCurrentOddCells(unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;

  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR);
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);

}  
  
  
/*
 *    Enables a selected cell.
**/
void AEK_POW_BMS63EN_EnableCell( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id) {
  uint8_t cell_idx = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN);

  if( cell_id == AEK_POW_BMS63EN_CELL_ALL ) {
	  AEK_POW_BMS63EN_write |= 0xFFFF;
	  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
		    	(&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+(cell_idx))->cell_en = AEK_POW_BMS63EN_CELL_ENABLED;
	   }
  }
  else {
      AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN << (uint8_t)cell_id);
    	  (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+(cell_id))->cell_en = AEK_POW_BMS63EN_CELL_ENABLED;
  }
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN, AEK_POW_BMS63EN_write);
};


/*
 *    Gets the current balancing status of a given instance.
**/
AEK_POW_BMS63EN_bal_status_t AEK_POW_BMS63EN_GetBalancingStatus( unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;
  
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BALCELL6_1ACT);
  
  AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_2_BALMODE_MASK);
  
  return (AEK_POW_BMS63EN_bal_status_t)(AEK_POW_BMS63EN_read & AEK_POW_BMS63EN_BALCELL6_1ACT_BAL_ON_EOF_MASK);
  
}  



/**
 *    Get Calib Current Measurement
 */
float AEK_POW_BMS63EN_GetCalibCurrentMeasurement( unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;
  int i = 0;
  int32_t add = 0;
  int32_t value = 0;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum,  AEK_POW_BMS63EN_IBATTERY_CALIB);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv,  AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_IBATTERY_CALIB);

  //2-Complement extraction
  for(i=0; i<18;i++){
	  add = AEK_POW_BMS63EN_read & (1<<i);
	  if((i == 17) && (add>>17)) add = -add;
	  value = value + add;
  }
  return ((((float)value) * AEK_POW_BMS63EN_VISENSE_RES) / (((float)Rshunt) / 1000));
};

/**
 *    Get Inst Current Measurement
 */
float AEK_POW_BMS63EN_GetInstCurrentMeasurement( unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;
  int i = 0;
  int32_t add = 0;
  int32_t value = 0;

  AEK_POW_BMS63EN_CoulombCounterReset(AEK_POW_BMS63EN_devnum);

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum,  AEK_POW_BMS63EN_IBATTERY_SYNCH);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv,  AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_IBATTERY_SYNCH);

  //2-Complement extraction
  for(i=0; i<18;i++){
	  add = AEK_POW_BMS63EN_read & (1<<i);
	  if((i == 17) && (add>>17)) add = -add;
	  value = value + add;
  }
  return ((((float)value) * AEK_POW_BMS63EN_VISENSE_RES) / (((float)Rshunt) / 1000));
};


/*
 *    Reads the ADC conversion data of a selected cell.
**/
float AEK_POW_BMS63EN_GetCellVoltMeasurement(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id) {

  unsigned AEK_POW_BMS63EN_reg;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

  AEK_POW_BMS63EN_reg = (unsigned)(AEK_POW_BMS63EN_VCELL1 + cell_id);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
   
  return ((float)((uint16_t)(AEK_POW_BMS63EN_read & AEK_POW_BMS63EN_VCELL1_VCELL1_MASK))) * AEK_POW_BMS63EN_VCELL_RES;
  
};



/*
 *    Reads the ADC conversion data of a Battery Pack.
**/
float AEK_POW_BMS63EN_GetBatteryPackVoltMeasurement( unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

  uint32_t vsum_batt;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATTDIV);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VBATTDIV);

  vsum_batt = AEK_POW_BMS63EN_read >> 16;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VSUMBATT);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VSUMBATT);

  vsum_batt |= (AEK_POW_BMS63EN_read << 2);

  return ((float)vsum_batt) * AEK_POW_BMS63EN_VSUM_BAT_RES;
};

/*
 *    Sets the balancing mode of a given cell.
**/
void AEK_POW_BMS63EN_SetBalancingMode(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_bal_mode_t cell_bal_mode) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);
  
  AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_2_BALMODE_MASK);
  
  if( cell_bal_mode == AEK_POW_BMS63EN_cell_manual_bal_mode ) {
	AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)0x0FFFF;
    AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BAL_2_BALMODE_MANUAL;
  } else { 
	AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)0x0FFFF;
    AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BAL_2_BALMODE_TIMED;
  }
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2, AEK_POW_BMS63EN_read);

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);

}  


/*
 *    Sets the threshold for the timed balanging for a given cell.
**/
void AEK_POW_BMS63EN_SetCellTimedBalThreshold( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_id, uint16_t cell_thr) {
  
  uint8_t act_cell_thr;
  unsigned AEK_POW_BMS63EN_reg = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read = 0;

  if( (cell_thr >> 2) <= 508 ) {  /* 'fine' accuracy */
    act_cell_thr = (uint8_t)((cell_thr >> 2) | 0x80);    
  } else {  /* 'coarse' accuracy */
    act_cell_thr = (uint8_t)(cell_thr >> 9);    
  }; /* if( (cell_thr >> 2) <= 508 ) */       

  switch( cell_id ) {
    case AEK_POW_BMS63EN_CELL1 : case AEK_POW_BMS63EN_CELL2 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_8;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL1 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL1_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL1(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL2_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL2(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL1 ) */
      break;

    case AEK_POW_BMS63EN_CELL3 : case AEK_POW_BMS63EN_CELL4 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_7;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL3 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL3_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL3(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL4_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL4(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL3 ) */
      break;

    case AEK_POW_BMS63EN_CELL5 : case AEK_POW_BMS63EN_CELL6 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_6;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL5 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL5_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL5(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL6_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL6(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL5 ) */
      break;

    case AEK_POW_BMS63EN_CELL7 : case AEK_POW_BMS63EN_CELL8 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_5;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL7 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL7_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL7(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL8_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL8(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL7 ) */
      break;

    case AEK_POW_BMS63EN_CELL9 : case AEK_POW_BMS63EN_CELL10 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_4;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL9 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL9_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL9(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL10_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL10(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL19 ) */
      break;
    
    case AEK_POW_BMS63EN_CELL11 : case AEK_POW_BMS63EN_CELL12 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_3;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL11 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL11 ) */
      break;
    
    case AEK_POW_BMS63EN_CELL13 : case AEK_POW_BMS63EN_CELL14 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_BAL_2;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      if( cell_id == AEK_POW_BMS63EN_CELL13 ) {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL13_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL13(act_cell_thr & 0x3F));
      } else {
        AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL14_MASK);
        AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL14(act_cell_thr & 0x3F));
      } /* if( cell_id == AEK_POW_BMS63EN_CELL13 ) */
      break;
      
    case AEK_POW_BMS63EN_CELL_ALL :
      /*** TODO: to implement this switch case (needed?) ***/
      break;
    
  };  /* switch( cell_id ) */

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_read);

  if( act_cell_thr & 0x80 ) {
    AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);
    AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2);
    AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_BAL_2_TIMEDBALACC_FINE);
    AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_2, AEK_POW_BMS63EN_read);
  };
  
}  


/*
 *    Starts the balancing on the enabled cells of a device.
**/
void AEK_POW_BMS63EN_StartCellBalancing( unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  
  AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_1_BAL_STOP);
  AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BAL_1_BAL_START;

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1, AEK_POW_BMS63EN_read);
  
}


/*
 *    Stops the balancing on the enabled cells of a device.
**/
void AEK_POW_BMS63EN_StopCellBalancing(unsigned AEK_POW_BMS63EN_devnum) {

  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1);
  
  AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_BAL_1_BAL_START);
  AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_BAL_1_BAL_STOP;

  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BAL_1, AEK_POW_BMS63EN_read);
 
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  


/* * * * * * * * * * * * * * * * * * */
/*   G P I O     F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * * */ 
/*
 *    Get Voltage Value from GPIO the GPIO 3 - 9
**/
float AEK_POW_BMS63EN_GetVoltageGPIOMeasurement( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio,float Vref, AEK_POW_BMS63EN_ratio_abs_mode_t mode){
	float Voltage = 0;

	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

	AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_MEAS + AEK_POW_BMS63EN_gpio);
	AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_MEAS + AEK_POW_BMS63EN_gpio);

	if (mode == AEK_POW_BMS63EN_ABS_MODE){
		Voltage = ((int)(AEK_POW_BMS63EN_reg & 0xFFFF)) * VGPIO_ABS_RES;
	}
	else if(mode == AEK_POW_BMS63EN_RATIO_MODE){
		Voltage = ((int)(AEK_POW_BMS63EN_reg & 0xFFFF)) * VGPIO_RATIO_RES * Vref;
	} else {}

	return Voltage;

}


/*
 *    Get Resistor NTC Value from GPIO the GPIO 3 - 9
**/
float AEK_POW_BMS63EN_GetNTCMeasurement( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio,float Vref, AEK_POW_BMS63EN_ratio_abs_mode_t mode){
	float Voltage = 0;

		AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

		AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_MEAS + AEK_POW_BMS63EN_gpio);
		AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_MEAS + AEK_POW_BMS63EN_gpio);

		if (mode == AEK_POW_BMS63EN_ABS_MODE){
			Voltage = ((int)(AEK_POW_BMS63EN_reg & 0xFFFF)) * VGPIO_ABS_RES;
		}
		else if(mode == AEK_POW_BMS63EN_RATIO_MODE){
			Voltage = ((int)(AEK_POW_BMS63EN_reg & 0xFFFF)) * VGPIO_RATIO_RES * Vref;
		} else {}

		return ((Voltage * AEK_POW_BMS63EN_RP_NTC) / (Vref - Voltage));
}


void AEK_POW_BMS63EN_SetOvercurrentThreshold( unsigned AEK_POW_BMS63EN_devnum, uint16_t Rshunt, float current_th_A){
      AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write;
      AEK_POW_BMS63EN_write=(uint32_t)((current_th_A * Rshunt)/(AEK_POW_BMS63EN_VISENSE_RES*1000));
      AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CSA_THRESH_NORM, AEK_POW_BMS63EN_write);
}


/**
	 *  Enable GPIO Measurement
*/
void AEK_POW_BMS63EN_SetGPIOConv( unsigned AEK_POW_BMS63EN_devnum) {

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);

AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_ADCV_CONV_GPIO_CONV;

AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_reg);

}

/**
*    Configures the GPIO 3 - 9
*/
void AEK_POW_BMS63EN_ConfigGPIO(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, AEK_POW_BMS63EN_gpio_conf_t AEK_POW_BMS63EN_gpio_conf) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_write = 0;

  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_3_CONF);
  AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_3_CONF);
      
  switch( AEK_POW_BMS63EN_gpio ) {
    
    case AEK_POW_BMS63EN_gpio_3 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_3.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_3.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_3.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
    
    case AEK_POW_BMS63EN_gpio_4 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_4.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_4.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_4.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;

   case AEK_POW_BMS63EN_gpio_5 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_5.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_5.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_5.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
      
    case AEK_POW_BMS63EN_gpio_6 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_6.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_6.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_6.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
      
    case AEK_POW_BMS63EN_gpio_7 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_7.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_7.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_7.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
      
    case AEK_POW_BMS63EN_gpio_8 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_8.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_8.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_8.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
      
    case AEK_POW_BMS63EN_gpio_9 :
      AEK_POW_BMS63EN_reg &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_MASK);
      switch( AEK_POW_BMS63EN_gpio_conf ) {
        case AEK_POW_BMS63EN_gpio_analog_input :
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_9.gpio_conf = AEK_POW_BMS63EN_gpio_analog_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_input :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_DI;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_9.gpio_conf = AEK_POW_BMS63EN_gpio_digital_input;
          break;
        case AEK_POW_BMS63EN_gpio_digital_output :
          AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_DO;
          AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_devnum-1].gpio_9.gpio_conf = AEK_POW_BMS63EN_gpio_digital_output;
          break;
      } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
      break;
      
  } /* switch( AEK_POW_BMS63EN_gpio_conf ) */
  
  AEK_POW_BMS63EN_reg |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_write;
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_3_CONF, AEK_POW_BMS63EN_reg);
  
}


/*
 *    Sets the GPIO absolute mode (GPIO between 3 and 9) 
**/
void AEK_POW_BMS63EN_SetGPIOModeAbsolute( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio) {
  
  unsigned AEK_POW_BMS63EN_reg = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read = 0;

  switch( AEK_POW_BMS63EN_gpio ) {
    
    case AEK_POW_BMS63EN_gpio_3 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO3_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO3_MEAS_RATIO_ABS_3_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_4 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO4_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO4_MEAS_RATIO_ABS_4_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_5 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO5_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO5_MEAS_RATIO_ABS_5_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_6 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO6_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO6_MEAS_RATIO_ABS_6_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_7 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO7_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO7_MEAS_RATIO_ABS_7_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_8 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO8_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO8_MEAS_RATIO_ABS_8_SEL);
      break;
    
    case AEK_POW_BMS63EN_gpio_9 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO9_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_MEAS_RATIO_ABS_9_SEL);
      break;

  } /* switch( AEK_POW_BMS63EN_gpio ) */
    
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_read);
  
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
};


/*
 *    Sets the GPIO rationmetric mode (GPIO between 3 and 9) 
**/
void AEK_POW_BMS63EN_SetGPIOModeRatiometric(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio) {
  
  unsigned AEK_POW_BMS63EN_reg = 0;
 AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read = 0;
  
  switch( AEK_POW_BMS63EN_gpio ) {
    
    case AEK_POW_BMS63EN_gpio_3 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO3_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO3_MEAS_RATIO_ABS_3_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_4 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO4_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO4_MEAS_RATIO_ABS_4_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_5 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO5_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO5_MEAS_RATIO_ABS_5_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_6 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO6_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO6_MEAS_RATIO_ABS_6_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_7 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO7_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO7_MEAS_RATIO_ABS_7_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_8 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO8_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO8_MEAS_RATIO_ABS_8_SEL;
      break;
    
    case AEK_POW_BMS63EN_gpio_9 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO9_MEAS;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_MEAS_RATIO_ABS_9_SEL;
      break;
    
  } /* switch( AEK_POW_BMS63EN_gpio ) */
    
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_read);
  
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg);
}  
  
  
/*
 *    Sets the GPIO 3 - 9 overvoltage threshold
**/
void AEK_POW_BMS63EN_SetGPIOOVThreshold( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, uint16_t gpio_ov_thr) {
  
  unsigned AEK_POW_BMS63EN_reg = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read = 0; 
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write = 0;

  switch( AEK_POW_BMS63EN_gpio ) {
    
    case AEK_POW_BMS63EN_gpio_3 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO3_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO3_THR_GPIO3_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO3_THR_GPIO3_OT_TH(AEK_POW_BMS63EN_write);
      break;
  
    case AEK_POW_BMS63EN_gpio_4 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO4_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO4_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO4_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO4_THR_GPIO4_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO4_THR_GPIO4_OT_TH(AEK_POW_BMS63EN_write);
      break;

    case AEK_POW_BMS63EN_gpio_5 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO5_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO5_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO5_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO5_THR_GPIO5_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO5_THR_GPIO5_OT_TH(AEK_POW_BMS63EN_write);
      break;
    
    case AEK_POW_BMS63EN_gpio_6 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO6_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO6_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO6_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO6_THR_GPIO6_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO6_THR_GPIO6_OT_TH(AEK_POW_BMS63EN_write);      
      break;
    
    case AEK_POW_BMS63EN_gpio_7 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO7_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO7_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO7_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO7_THR_GPIO7_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO7_THR_GPIO7_OT_TH(AEK_POW_BMS63EN_write);
      break;
      
    case AEK_POW_BMS63EN_gpio_8 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO8_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO8_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO8_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO8_THR_GPIO8_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO8_THR_GPIO8_OT_TH(AEK_POW_BMS63EN_write);
      break;
      
    case AEK_POW_BMS63EN_gpio_9 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO9_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_THR_GPIO9_OT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_ov_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_THR_GPIO9_OT_TH(AEK_POW_BMS63EN_write);
      break;
    
  }; /* switch( AEK_POW_BMS63EN_gpio ) */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_read);
  
} 


/*
 *    Sets the GPIO 3 - 9 undervoltage threshold
**/
void AEK_POW_BMS63EN_SetGPIOUVThreshold( unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_gpio_t AEK_POW_BMS63EN_gpio, uint16_t gpio_uv_thr) {
  
  unsigned AEK_POW_BMS63EN_reg = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read = 0;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_write = 0;

  switch( AEK_POW_BMS63EN_gpio ) {
    
    case AEK_POW_BMS63EN_gpio_3 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO3_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO3_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO3_THR_GPIO3_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO3_THR_GPIO3_UT_TH(AEK_POW_BMS63EN_write);
      break;
  
    case AEK_POW_BMS63EN_gpio_4 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO4_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO4_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO4_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO4_THR_GPIO4_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO4_THR_GPIO4_UT_TH(AEK_POW_BMS63EN_write);
      break;

    case AEK_POW_BMS63EN_gpio_5 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO5_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO5_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO5_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO5_THR_GPIO5_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO5_THR_GPIO5_UT_TH(AEK_POW_BMS63EN_write);
      break;
    
    case AEK_POW_BMS63EN_gpio_6 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO6_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO6_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO6_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO6_THR_GPIO6_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO6_THR_GPIO6_UT_TH(AEK_POW_BMS63EN_write);
      break;
    
    case AEK_POW_BMS63EN_gpio_7 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO7_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO7_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO7_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO7_THR_GPIO7_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO7_THR_GPIO7_UT_TH(AEK_POW_BMS63EN_write);
      break;
      
    case AEK_POW_BMS63EN_gpio_8 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO8_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO8_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO8_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO8_THR_GPIO8_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO8_THR_GPIO8_UT_TH(AEK_POW_BMS63EN_write);
      break;
      
    case AEK_POW_BMS63EN_gpio_9 :
      AEK_POW_BMS63EN_reg = AEK_POW_BMS63EN_GPIO9_THR;
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_THR);
      AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_GPIO9_THR);
      AEK_POW_BMS63EN_read &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_GPIO9_THR_GPIO9_UT_TH_MASK);
      AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)((gpio_uv_thr * 1000)/AEK_POW_BMS63EN_GPIOx_MEAS_ABS_RES);
      AEK_POW_BMS63EN_read |= (AEK_POW_BMS63EN_register_t)AEK_POW_BMS63EN_GPIO9_THR_GPIO9_UT_TH(AEK_POW_BMS63EN_write);
      break;
    
  }; /* switch( AEK_POW_BMS63EN_gpio ) */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_reg, AEK_POW_BMS63EN_read);
  
}

uint8_t AEK_POW_BMS63EN_isEnabled(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_cell_id_t cell_idx){
	return ((& ((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_en;
}


/* * * * * * * * * * * * * * * * * * */


/** @} */
#endif