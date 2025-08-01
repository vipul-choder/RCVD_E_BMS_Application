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


/**  _AEK_COM_ISOSPI1_CFG_H_
 * @file    AEK_COM_ISOSPI1_cfg.h
 * @brief   AEK_COM_ISOSPI Driver configuration macros and structures.
 *
 * @addtogroup AEK_COM_ISOSPI1
 * @{
 */ 

#ifndef _AEK_COM_ISOSPI1_CFG_H_
#define _AEK_COM_ISOSPI1_CFG_H_

#include "spc5_lld.h"
#include "lldconf.h"
#include "spi_lld.h"
#include "spi_lld_cfg.h"



#define AEK_COM_ISOSPI_LIST_ELEMENT 1

typedef enum {
ISOSPI_DEV0=0
}ISOSPI_DEVICE;


typedef struct {
  uint8_t PIN_PORT;
  uint8_t PIN_GPIO;
} ISOSPI_pad_list_t;
typedef enum {
          L9963T_PAL_DIS = 0, //0 normal, 1 slp
          L9963T_PAL_BNE = 1, //BNE 1 se rx ha dati  /CPOL 0/1 interpretazione clk inactive lv
          L9963T_PAL_TX_EN = 2, //TX_EN 1 en tx /CPHA 0/1 SDI sampled at 1st/2nd clk edge after NCS
          L9963T_PAL_ISO_FREQ = 3, //come slave
          L9963T_PAL_TX_AMP = 4, //come slave
          L9963T_PAL_NSLAVE = 5, //1 mst, 0 slv
          L9963T_PAL_FAULT = 6 //Fault line
} ISOSPI_pal_ch_t;

typedef enum {
		L9963T_MODE_SLAVE,   	/**<    NSLAVE low	*/
		L9963T_MODE_MASTER   	/**<    NSLAVE high */
} ISOSPI_mode_t;

typedef enum {
        L9963T_ISO_FREQ_LOW,   /**<    low isolated frequency: 333 Kbps		*/
        L9963T_ISO_FREQ_HIGH   /**<    high isolated frequency: 2.66 Mbps	*/
} ISOSPI_iso_freq_t;

typedef enum {
        L9963T_TX_AMP_LOW,   /**<    ISO msgs low amplitude   */
        L9963T_TX_AMP_HIGH   /**<    ISO msgs high amplitude  */
} ISOSPI_tx_amp_t;

typedef enum {
        L9963T_250_KHZ,	/**<    default config   */
		L9963T_1_MHZ,   /**<    WARNING, this conf requires R6=9.31kOhm assembled   */
		L9963T_4_MHZ,	/**<    WARNING, this conf requires R6=16.2kOhm assembled   */
		L9963T_8_MHZ	/**<    WARNING, this conf requires R6=22.9kOhm assembled   */
} ISOSPI_master_clk_freq_t;

typedef enum {
        L9963T_MASTER_CPOL_LOW,   /**<    l9963t_CPOL_low   */
        L9963T_MASTER_CPOL_HIGH   /**<    l9963t_CPOL_high  */
} ISOSPI_master_cpol_t;

typedef enum {
        L9963T_MASTER_CPHA_LOW,   /**<    l9963t_SampleSDI_firstclk   */
        L9963T_MASTER_CPHA_HIGH   /**<    l9963t_SampleSDI_secondclk  */
} ISOSPI_master_cpha_t;

typedef enum{
		L9963T_FAULT_NOT_ACTIVE,
		L9963T_FAULT_ACTIVE
}ISOSPI_fault_t;

typedef struct {
	ISOSPI_DEVICE Devnum;
    ISOSPI_pad_list_t *pad_listp;
    ISOSPI_mode_t mode;
    ISOSPI_iso_freq_t isofreq;
    ISOSPI_tx_amp_t txamp;

	//ISOSPI_master_clk_freq_t mclk;
	ISOSPI_master_cpol_t mcpol;
	ISOSPI_master_cpha_t mcpha;
		SPIDriver	*spip;
		const SPIConfig	*spicfgp;
 	ISOSPI_fault_t ISOSPI_fault_sts;
} ISOSPI_Driver_t;
 
extern ISOSPI_Driver_t AEK_ISOSPI_ARRAY_DRIVER[1];




#endif /* _AEK_COM_ISOSPI1_CFG_H_ */

/** @} */
