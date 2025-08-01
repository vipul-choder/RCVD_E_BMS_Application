/****************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

#include "board.h"
#include "clock.h"

/*
 * Initial setup of MSCR_IO registers, the list is terminated
 * by a {-1, 0, 0}.
 */
static spc_mscr_io_init_t spc_mscr_io_init[] = {
  {(int16_t)MSCR_IO_PIN_RXD_4, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_DIS_GPIO1, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_FAULT_EIRQ2, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_BNECPOL_GPIO2, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_TXENCPHA_GPIO3, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_FREQ_GPIO4, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN1_NCS0_CS0_0, (iomode_t)(PAL_SPC5_SSS(8) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0)), PAL_HIGH},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN1_SDIexMOSI_MOSI_0, (iomode_t)(PAL_SPC5_SSS(1) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN1_SCKexSCK_SCK_0, (iomode_t)(PAL_SPC5_SSS(1) | PAL_SPC5_OERC(1) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN1_SDOexMISO_MISO_0, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_LED3, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_NSLAVE_GPIO9, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_RX_4_1, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(0) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE | PAL_SPC5_WPUE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_TX_4_1, (iomode_t)(PAL_SPC5_SSS(2) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_LED2, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_TXD_4, (iomode_t)(PAL_SPC5_SSS(1) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0)), PAL_LOW},
  {(int16_t)MSCR_IO_PIN_AEK_COM_ISOSPI1Board0_CN2_TXAMP_GPIO8, (iomode_t)(PAL_SPC5_SSS(0) | PAL_SPC5_OERC(0) | PAL_SPC5_ODC(2) | PAL_SPC5_SMC | PAL_SPC5_ILS(0) | PAL_SPC5_IBE), PAL_LOW},
  {-1, 0, 0}
};

/*
 * Initial setup of MSCR_MUX registers, the list is terminated
 * by a {-1, 0}.
 */
static spc_mscr_mux_init_t spc_mscr_mux_init[] = {
  {(int16_t)(MSCR_MUX_PIN_RXD_4), 2U},
  {(int16_t)(MSCR_MUX_PIN_AEK_COM_ISOSPI1Board0_CN1_SDOexMISO_MISO_0), 7U},
  {(int16_t)(MSCR_MUX_PIN_RX_4_1), 5U},
  {-1, 0}
};

/**
 * @brief   PAL setup.
 */
static PALConfig pal_default_config = {
  spc_mscr_io_init,
  spc_mscr_mux_init
};

/*
 * Board-specific initialization code.
 */
void boardInit(void) {

  pal_init(&pal_default_config);
}
