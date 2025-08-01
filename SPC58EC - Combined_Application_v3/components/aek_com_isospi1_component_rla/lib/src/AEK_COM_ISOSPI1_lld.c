/****************************************************************************
 *
 * Copyright � 2019 STMicroelectronics - All Rights Reserved
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
 * @file    AEK_COM_ISOSPI1_lld.c
 * @brief   SPC5xx AEK_COM_ISOSPI1_lld Utils code.
 *
 * @addtogroup AEK_COM_ISOSPI1_lld
 * @{
 */
#include "AEK_COM_ISOSPI1_lld.h"
#define SPI_TRANSFER_LENGTH 5
typedef enum { spi_burst_read, spi_single_read, spi_write } spi_rw_t;
#if (AEK_COM_ISOSPI_LIST_ELEMENT!=0)
/* PAL/PAD-based functions */
/**
* @brief   Sets the logical state of a pad of the AEK-COM-ISOSPI1.
*
* @param[in] l9963t         pointer to the @p L9963Driver object
* @param[in] l9963t_pal_ch   the pad to select
* @param[in] value          the value to write
* @return    void.
*
* @api
*/
void l9963t_PALWritePad(ISOSPI_Driver_t l9963t, ISOSPI_pal_ch_t l9963t_pal_ch, uint8_t value) {
  if( l9963t.pad_listp[l9963t_pal_ch].PIN_PORT != 255 &&  l9963t.pad_listp[l9963t_pal_ch].PIN_GPIO != 255 ) {
    if( value == (uint8_t)PAL_HIGH ) {
    	pal_lld_setpad(l9963t.pad_listp[l9963t_pal_ch].PIN_PORT, l9963t.pad_listp[l9963t_pal_ch].PIN_GPIO );
    } else {
    	pal_lld_clearpad(l9963t.pad_listp[l9963t_pal_ch].PIN_PORT, l9963t.pad_listp[l9963t_pal_ch].PIN_GPIO );
    }
  }
};
/**
* @brief   Reads the logical state of a pad of the AEK-COM-ISOSPI1..
*
* @param[in] l9963t         pointer to the @p L9963Driver object
* @param[in] l9963t_pal_ch   the pad to select
* @return                   the read value
*
* @api
*/
uint8_t l9963t_PALReadPad(ISOSPI_Driver_t l9963t, ISOSPI_pal_ch_t l9963t_pal_ch) {
  uint8_t pad_read;
  if( l9963t.pad_listp[l9963t_pal_ch].PIN_PORT != 255 && l9963t.pad_listp[l9963t_pal_ch].PIN_GPIO != 255 ) {
    pad_read = pal_lld_readpad(l9963t.pad_listp[l9963t_pal_ch].PIN_PORT, l9963t.pad_listp[l9963t_pal_ch].PIN_GPIO );
  } else {
    pad_read = 255;
  }
  return (uint8_t)pad_read;
};


// ******************************************************************************* //
// ********************************* SLAVE APIs ********************************** //
// ******************************************************************************* //

/**
* @brief   Sets the AEK-COM-ISOSPI1 as a slave.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SetAsSlave( ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_NSLAVE, PAL_LOW);
}

/**
* @brief   Enable the Transceiver Communication.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_EnableTransceiverComm(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_EN, PAL_HIGH);
}

/**
* @brief   Disabled the Transceiver Communication.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_DisableTransceiverComm(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_EN, PAL_LOW);
}

//BNE set automatically from l9963T

// ******************************************************************************* //
// ******************************** MASTER APIs ********************************** //
// ******************************************************************************* //
/**
* @brief   Configuration API. Sets the AEK-COM-ISOSPI1 as a Master..
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SetAsMaster(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_NSLAVE, PAL_HIGH);
}

/**
* @brief   Configuration API. SPI will sample the signal starting from the First square wave of the Clock.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SampleSDI_firstclk(ISOSPI_DEVICE dev) { //set CPHA so SDI will be sampled upon first SCK edge after NCS
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_EN, PAL_LOW);
}

/**
* @brief   Configuration API. SPI will sample the signal starting from the Second square wave of the Clock.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SampleSDI_secondclk(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_EN, PAL_HIGH); //L9963T_PAL_TX_EN
}

/**
* @brief   Configuration API. Sets CPOL Low (this function can be used only if NSLAVE = 1).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_CPOL_low(ISOSPI_DEVICE dev) {  // if NSLAVE=0 it have to warn about packets, if NSL=1 0/1 sets clock inactive state
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_BNE, PAL_LOW);
}

/**
* @brief   Configuration API. Sets CPOL High (this function can be used only if NSLAVE = 1).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_CPOL_high(ISOSPI_DEVICE dev) { // if NSLAVE=0 it have to warn about packets, if NSL=1 0/1 sets clock inactive state
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_BNE, PAL_HIGH);
}

// ******************************************************************************* //
// ******************************** Common APIs ********************************** //
// ******************************************************************************* //
/**
* @brief   Enables the Transceiver.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_EnableTransceiver(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_DIS, PAL_LOW);
}

/**
* @brief   Disables the Transceiver.
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_DisableTransceiver(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_DIS, PAL_HIGH);
}

/**
* @brief   Configuration API. Sets the ISOFREQ to low (this establishes a slow communication equal to 333 kHz).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SetISOCommSlow(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_ISO_FREQ, PAL_LOW);
}

/**
* @brief   Configuration API. Sets the ISOFREQ to high (this establishes a slow communication equal to 2.66 MHz).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_SetISOCommFast(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_ISO_FREQ, PAL_HIGH);
}

/**
* @brief   Configuration API. Sets TXAMP to low (SPI signal not amplified).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_ISOTX_Attenuate(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_AMP, PAL_LOW);
}

/**
* @brief   Configuration API. Sets TXAMP to high (SPI signal amplified).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/
void AEK_COM_ISOSPI_ISOTX_Amplify(ISOSPI_DEVICE dev) {
			l9963t_PALWritePad(AEK_ISOSPI_ARRAY_DRIVER[dev], L9963T_PAL_TX_AMP, PAL_HIGH);
}


/**
* @brief   Reads the value of the FAULT pin and updates a fault flag, which is included in the driver data structure (ISOSPI_Driver_t).
*
* @param[in] dev - the integer representing the Transceiver to configure.
*
* @api
*/

uint8_t AEK_COM_ISOSPI_GetFault (ISOSPI_DEVICE dev){
		if(l9963t_PALReadPad(AEK_ISOSPI_ARRAY_DRIVER[dev],L9963T_PAL_FAULT)){
			AEK_ISOSPI_ARRAY_DRIVER[dev].ISOSPI_fault_sts = L9963T_FAULT_ACTIVE;
		}	
		else{
			AEK_ISOSPI_ARRAY_DRIVER[dev].ISOSPI_fault_sts = L9963T_FAULT_NOT_ACTIVE;
	    }
		return  AEK_ISOSPI_ARRAY_DRIVER[dev].ISOSPI_fault_sts;
}	


// ******************************************************************************* //
// ***************************** COMPREHENSIVE APIs ****************************** //
// ******************************************************************************* //

/**
 * @brief   Configures the NSLAVE according to the user interface configuration.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 * @param[in] l9963t_mode - The mode configured from the User Interface .
 *
 * @api
 */
void AEK_COM_ISOSPI_ConfigMode( ISOSPI_DEVICE dev, ISOSPI_mode_t l9963t_mode ) {
		  switch( l9963t_mode ) {
			case L9963T_MODE_SLAVE :
				AEK_COM_ISOSPI_SetAsSlave(dev);
			break;
			case L9963T_MODE_MASTER :
				AEK_COM_ISOSPI_SetAsMaster(dev);
			  break;
		  }
}

/**
 * @brief   Configures the ISOFREQ according to the user interface configuration.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 * @param[in] l9963t_iso_freq - The mode configured from the User Interface .
 *
 * @api
 */
void AEK_COM_ISOSPI_ConfigISOFreq( ISOSPI_DEVICE dev, ISOSPI_iso_freq_t l9963t_iso_freq ) {
		  switch( l9963t_iso_freq ) {
			case L9963T_ISO_FREQ_LOW :
				AEK_COM_ISOSPI_SetISOCommSlow(dev);
			  break;
			case L9963T_ISO_FREQ_HIGH :
				AEK_COM_ISOSPI_SetISOCommFast(dev);
			  break;
		  }
}

/**
 * @brief   Configures the TXAMP according to the user interface configuration.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 * @param[in] l9963t_tx_amp - The Amplification mode configured from the User Interface .
 *
 * @api
 */
void AEK_COM_ISOSPI_ConfigISOAmp( ISOSPI_DEVICE dev, ISOSPI_tx_amp_t l9963t_tx_amp ) {
		  switch( l9963t_tx_amp ) {
			case L9963T_TX_AMP_LOW :
				AEK_COM_ISOSPI_ISOTX_Attenuate(dev);
			  break;
			case L9963T_TX_AMP_HIGH :
				AEK_COM_ISOSPI_ISOTX_Amplify(dev);
			  break;
		  }
}

/**
 * @brief   Configures the CPOL according to the user interface configuration.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 * @param[in] l9963t_cpol - The CLOCK polarity configured from the User Interface .
 *
 * @api
 */
void AEK_COM_ISOSPI_ConfigCPOL( ISOSPI_DEVICE dev, ISOSPI_master_cpol_t l9963t_cpol ) {
	
		  switch( l9963t_cpol ) {
			case L9963T_MASTER_CPOL_LOW :
				AEK_COM_ISOSPI_CPOL_low(dev);
			  break;
			case L9963T_MASTER_CPOL_HIGH :
				AEK_COM_ISOSPI_CPOL_high(dev);
			  break;
		  }
}
/**
 * @brief   Configures the CPHA according to the user interface configuration.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 * @param[in] l9963t_cpha - The CLOCK phase configured from the User Interface .
 *
 * @api
 */
void AEK_COM_ISOSPI_ConfigCPHA( ISOSPI_DEVICE dev, ISOSPI_master_cpha_t l9963t_cpha ) {
		  switch( l9963t_cpha ) {
			case L9963T_MASTER_CPHA_LOW :
				AEK_COM_ISOSPI_SampleSDI_firstclk(dev);
			  break;
			case L9963T_MASTER_CPHA_HIGH :
				AEK_COM_ISOSPI_SampleSDI_secondclk(dev);
			  break;
		  }
}
//void AEK_COM_ISOSPI_ConfigclkFreq( ISOSPI_DEVICE dev, L9963T_master_clk_freq_t l9963t_clkfreq ) { //Requires HW modifications
//		  switch( l9963t_clkfreq ) {
//			case L9963T_250_KHZ :
//				break;
//			case L9963T_1_MHZ :
//				break;
//			case L9963T_4_MHZ :
//				break;
//			case L9963T_8_MHZ :
//				break;
//			  break;
//		  }
//}

/**
 * @brief   Comprehensive API, which recalls ConfigMode, ConfigISOFreq, ConfigISOAmp, ConfigCPOL, ConfigCPHA functions.
 *
 * @param[in] driver - the driver pointer of the transceiver we want to configure.
 *
 * @api
 */
void config_Transceiver(ISOSPI_Driver_t driver){   //
	AEK_COM_ISOSPI_ConfigMode( driver.Devnum,  driver.mode );
	AEK_COM_ISOSPI_ConfigISOFreq( driver.Devnum,  driver.isofreq );
	AEK_COM_ISOSPI_ConfigISOAmp( driver.Devnum,  driver.txamp );
	if(driver.mode==L9963T_MODE_MASTER){
		//AEK_COM_ISOSPI_ConfigclkFreq(  driver.Devnum,  driver.mclk ) ;
		AEK_COM_ISOSPI_ConfigCPOL( driver.Devnum,  driver.mcpol );
		AEK_COM_ISOSPI_ConfigCPHA( driver.Devnum,  driver.mcpha );
	}
}

/**
 * @brief   DEBUG function, Sets high and then low every configuration pin of the transceiver
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 *
 * @api
 */
void debug_config(ISOSPI_DEVICE dev){
	AEK_COM_ISOSPI_SetAsMaster(dev);				//NSLAVE
	AEK_COM_ISOSPI_SetAsSlave(dev);				//NSLAVE
	AEK_COM_ISOSPI_DisableTransceiver(dev);		//DIS
	AEK_COM_ISOSPI_EnableTransceiver(dev);		//DIS
	AEK_COM_ISOSPI_EnableTransceiverComm(dev);	//TXEN/CPHA
	AEK_COM_ISOSPI_DisableTransceiverComm(dev);	//TXEN/CPHA
	AEK_COM_ISOSPI_CPOL_high(dev);				//BNE/CPOL
	AEK_COM_ISOSPI_CPOL_low(dev);				//BNE/CPOL
	AEK_COM_ISOSPI_ISOTX_Amplify(dev);			//ISOTX
	AEK_COM_ISOSPI_ISOTX_Attenuate(dev);			//ISOTX
	AEK_COM_ISOSPI_SetISOCommFast(dev);			//ISOFREQ
	AEK_COM_ISOSPI_SetISOCommSlow(dev);			//ISOFREQ
}
/**
 * @brief   Slave configuration function example, which drives every configuration pin of the transceiver setting it as a slave.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 *
 * @api
 */
void slave_example_config( ISOSPI_DEVICE dev){
	AEK_COM_ISOSPI_SetAsSlave(dev);				//NSLAVE	0
	AEK_COM_ISOSPI_EnableTransceiver(dev);		//DIS		0
	AEK_COM_ISOSPI_EnableTransceiverComm(dev);	//TXEN/CPHA	1
	//BNE auto set from dev during tx					//BNE/CPOL
	AEK_COM_ISOSPI_ISOTX_Attenuate(dev);			//ISOTX		0
	AEK_COM_ISOSPI_SetISOCommSlow(dev);			//ISOFREQ	0
}
/**
 * @brief   Master configuration function example, which drives every configuration pin of the transceiver setting it as a master.
 *
 * @param[in] dev - the integer representing the Transceiver to configure.
 *
 * @api
 */
void master_example_config( ISOSPI_DEVICE dev){
	AEK_COM_ISOSPI_SetAsMaster(dev);				//NSLAVE	1
	AEK_COM_ISOSPI_EnableTransceiver(dev);		//DIS		0
	AEK_COM_ISOSPI_SampleSDI_secondclk(dev);		//TXEN/CPHA	1
	AEK_COM_ISOSPI_CPOL_low(dev);				//BNE/CPOL	0
	AEK_COM_ISOSPI_ISOTX_Attenuate(dev);			//ISOTX		0
	AEK_COM_ISOSPI_SetISOCommSlow(dev);			//ISOFREQ	0
}

/** @} */
#endif

