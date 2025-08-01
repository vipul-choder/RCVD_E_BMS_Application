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
 * @file    AEK_COM_ISOSPI1_lld.h
 * @brief   SPC5xx AEK_COM_ISOSPI1_lld header file.
 *
 * @addtogroup AEK_COM_ISOSPI1_lld
 * @{
 */
#ifndef AEK_COM_ISOSPI1_LLD_H_
#define AEK_COM_ISOSPI1_LLD_H_

#include "components.h"
#include "AEK_COM_ISOSPI1_cfg.h"

#if (AEK_COM_ISOSPI_LIST_ELEMENT!=0)

void l9963t_PALWritePad(ISOSPI_Driver_t l9963t, ISOSPI_pal_ch_t L9963T_pal_ch, uint8_t value);

uint8_t l9963t_PALReadPad(ISOSPI_Driver_t l9963t, ISOSPI_pal_ch_t L9963T_pal_ch);

// [-------------- SLAVE APIs --------------]
void AEK_COM_ISOSPI_SetAsSlave(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_EnableTransceiverComm(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_DisableTransceiverComm(ISOSPI_DEVICE dev);
// [-------------- MASTER APIs --------------]
void AEK_COM_ISOSPI_SetAsMaster(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_SampleSDI_firstclk(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_SampleSDI_secondclk(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_CPOL_low(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_CPOL_high(ISOSPI_DEVICE dev);
// [-------------- common APIs --------------]
void AEK_COM_ISOSPI_EnableTransceiver (ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_DisableTransceiver(ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_SetISOCommSlow( ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_SetISOCommFast( ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_ISOTX_Attenuate( ISOSPI_DEVICE dev);
void AEK_COM_ISOSPI_ISOTX_Amplify (ISOSPI_DEVICE dev);
uint8_t AEK_COM_ISOSPI_GetFault (ISOSPI_DEVICE dev);
// [-------------- COMPREHENSIVE APIs --------------]
void AEK_COM_ISOSPI_ConfigMode( ISOSPI_DEVICE dev, ISOSPI_mode_t l9963t_mode );
void AEK_COM_ISOSPI_ConfigISOFreq( ISOSPI_DEVICE dev, ISOSPI_iso_freq_t l9963t_iso_freq );
void AEK_COM_ISOSPI_ConfigISOAmp( ISOSPI_DEVICE dev, ISOSPI_tx_amp_t l9963t_tx_amp );
//void AEK_COM_ISOSPI_ConfigclkFreq( ISOSPI_DEVICE dev, ISOSPI_master_clk_freq_t l9963t_clkfreq ) ;
void AEK_COM_ISOSPI_ConfigCPOL( ISOSPI_DEVICE dev, ISOSPI_master_cpol_t l9963t_cpol );
void AEK_COM_ISOSPI_ConfigCPHA( ISOSPI_DEVICE dev, ISOSPI_master_cpha_t l9963t_cpha );

void config_Transceiver (ISOSPI_Driver_t driver);  //COMPREHENSIVE FUNCTION
void slave_debug_config(ISOSPI_DEVICE dev);
void slave_example_config(ISOSPI_DEVICE dev);
void master_example_config(ISOSPI_DEVICE dev);
#endif
#endif /* AEK_COM_ISOSPI1_LLD_H_ */
/** @} */
