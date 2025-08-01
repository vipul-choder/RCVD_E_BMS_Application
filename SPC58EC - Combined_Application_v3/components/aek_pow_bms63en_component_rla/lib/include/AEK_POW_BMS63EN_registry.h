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
 * @file    AEK_POW_BMS63EN_registry.h
 * @brief   AEK_POW_BMS63EN registers map and definitions.
 *
 * @addtogroup AEK_POW_BMS63EN_REG
 * @{
 */

#ifndef _AEK_POW_BMS63EN_REG_H_
#define _AEK_POW_BMS63EN_REG_H_

#include "AEK_POW_BMS63EN_cfg.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    AEK_POW_BMS63EN register names
 * @{
 */ 
/*  reserved value: 0x0  */
#define AEK_POW_BMS63EN_DEV_GEN_CFG               0x01
#define AEK_POW_BMS63EN_FASTCH_BALUV              0x02
#define AEK_POW_BMS63EN_BAL_1                     0x03
#define AEK_POW_BMS63EN_BAL_2                     0x04
#define AEK_POW_BMS63EN_BAL_3                     0x05
#define AEK_POW_BMS63EN_BAL_4                     0x06
#define AEK_POW_BMS63EN_BAL_5                     0x07
#define AEK_POW_BMS63EN_BAL_6                     0x08
#define AEK_POW_BMS63EN_BAL_7                     0x09
#define AEK_POW_BMS63EN_BAL_8                     0x0A
#define AEK_POW_BMS63EN_VCELL_THRESH_UV_OV        0x0B
#define AEK_POW_BMS63EN_VBATT_SUM_TH              0x0C
#define AEK_POW_BMS63EN_ADCV_CONV                 0x0D
#define AEK_POW_BMS63EN_NCYCLE_PROG_1             0x0E
#define AEK_POW_BMS63EN_NCYCLE_PROG_2             0x0F
#define AEK_POW_BMS63EN_BALCELL14_7ACT            0x10
#define AEK_POW_BMS63EN_BALCELL6_1ACT             0x11
#define AEK_POW_BMS63EN_FSM                       0x12
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93          0x13
#define AEK_POW_BMS63EN_GPIO9_3_CONF              0x14
#define AEK_POW_BMS63EN_GPIO3_THR                 0x15
#define AEK_POW_BMS63EN_GPIO4_THR                 0x16
#define AEK_POW_BMS63EN_GPIO5_THR                 0x17
#define AEK_POW_BMS63EN_GPIO6_THR                 0x18
#define AEK_POW_BMS63EN_GPIO7_THR                 0x19
#define AEK_POW_BMS63EN_GPIO8_THR                 0x1A
#define AEK_POW_BMS63EN_GPIO9_THR                 0x1B
#define AEK_POW_BMS63EN_VCELLS_EN                 0x1C
#define AEK_POW_BMS63EN_FAULTMASK                 0x1D
#define AEK_POW_BMS63EN_FAULTMASK2                0x1E
#define AEK_POW_BMS63EN_CSA_THRESH_NORM           0x1F
#define AEK_POW_BMS63EN_CSA_GPIO_MSK              0x20
#define AEK_POW_BMS63EN_VCELL1                    0x21
#define AEK_POW_BMS63EN_VCELL2                    0x22
#define AEK_POW_BMS63EN_VCELL3                    0x23
#define AEK_POW_BMS63EN_VCELL4                    0x24
#define AEK_POW_BMS63EN_VCELL5                    0x25
#define AEK_POW_BMS63EN_VCELL6                    0x26
#define AEK_POW_BMS63EN_VCELL7                    0x27
#define AEK_POW_BMS63EN_VCELL8                    0x28
#define AEK_POW_BMS63EN_VCELL9                    0x29
#define AEK_POW_BMS63EN_VCELL10                   0x2A
#define AEK_POW_BMS63EN_VCELL11                   0x2B
#define AEK_POW_BMS63EN_VCELL12                   0x2C
#define AEK_POW_BMS63EN_VCELL13                   0x2D
#define AEK_POW_BMS63EN_VCELL14                   0x2E
#define AEK_POW_BMS63EN_IBATTERY_SYNCH            0x2F
#define AEK_POW_BMS63EN_IBATTERY_CALIB            0x30
#define AEK_POW_BMS63EN_COULCNTRTIME              0x31
#define AEK_POW_BMS63EN_COULCNTRMSB               0x32
#define AEK_POW_BMS63EN_COULCNTRLSB               0x33
#define AEK_POW_BMS63EN_GPIO3_MEAS                0x34
#define AEK_POW_BMS63EN_GPIO4_MEAS                0x35
#define AEK_POW_BMS63EN_GPIO5_MEAS                0x36
#define AEK_POW_BMS63EN_GPIO6_MEAS                0x37
#define AEK_POW_BMS63EN_GPIO7_MEAS                0x38
#define AEK_POW_BMS63EN_GPIO8_MEAS                0x39
#define AEK_POW_BMS63EN_GPIO9_MEAS                0x3A
#define AEK_POW_BMS63EN_TEMPCHIP                  0x3B
#define AEK_POW_BMS63EN_FAULTS1                   0x3C
#define AEK_POW_BMS63EN_FAULTS2                   0x3D
#define AEK_POW_BMS63EN_BAL_OPEN                  0x3E
#define AEK_POW_BMS63EN_BAL_SHORT                 0x3F
#define AEK_POW_BMS63EN_VSUMBATT                  0x40
#define AEK_POW_BMS63EN_VBATTDIV                  0x41
#define AEK_POW_BMS63EN_CELL_OPEN                 0x42
#define AEK_POW_BMS63EN_VCELL_UV                  0x43
#define AEK_POW_BMS63EN_VCELL_OV                  0x44
#define AEK_POW_BMS63EN_VGPIO_OT_UT               0x45
#define AEK_POW_BMS63EN_VCELL_BAL_UV              0x46
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT           0x47
#define AEK_POW_BMS63EN_MUX_BIST_FAIL             0x48
#define AEK_POW_BMS63EN_BIST_COMP                 0x49
#define AEK_POW_BMS63EN_OPEN_BIST_FAIL            0x4A
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL            0x4B
#define AEK_POW_BMS63EN_VTREF                     0x4C
/*  reserved values: 0x4D - 0x7D  */
#define AEK_POW_BMS63EN_DEVICE_SERVICE_RD         0x7E
/** @} */


/**
 * @name    AEK_POW_BMS63EN burst command names
 * @{
 */  
#define AEK_POW_BMS63EN_BURST_CMD1               0x78
#define AEK_POW_BMS63EN_BURST_CMD2               0x7A
#define AEK_POW_BMS63EN_BURST_CMD3               0x7B
/** @} */ 


/**
 * @name    DEV_GEN_CFG (general configuration register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_DEV_GEN_CFG_FAULTL_FORCE              (1U << 0)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_FARTHEST_UNIT             (1U << 1)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_EN              (1U << 2)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_FAULT_EN                  (1U << 3)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_4ms       (~(7U << 4))
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_8ms       (1U << 4)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_32ms      (2U << 4)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_128ms     (3U << 4)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_MASK      (7U << 4)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_HEARTBEAT_CYCLE_128ms_alt (1U << 6)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO3us       (~(3U << 8))
#define AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_TISO375ns     (3U << 8)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_ISOFREQ_SEL_MASK          (3U << 8)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_OUT_RES_TX_ISO_MASK       (3U << 10)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_ISOTX_EN_H                (1U << 12)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_CHIP_ID(n)                ((n) << 13)
#define AEK_POW_BMS63EN_DEV_GEN_CFG_CHIP_ID_MASK              (31U << 13)
/** @} */ 


/**
 * @name    FASTCH_BALUV (fast charge balance under-voltage register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_FASTCH_BALUV_VCELL_BAL_UV_DELTA_THR(n)        ((n) << 0)
#define AEK_POW_BMS63EN_FASTCH_BALUV_VCELL_BAL_UV_DELTA_THR_MASK      (255U << 0)
#define AEK_POW_BMS63EN_FASTCH_BALUV_GPIO_FASTCH_OT_DELTA_THR(n)      ((n) << 8)
#define AEK_POW_BMS63EN_FASTCH_BALUV_GPIO_FASTCH_OT_DELTA_THR_MASK    (255U << 8)
#define AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_32ms                 (~(3U << 16))
#define AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_1024ms               (2U << 16)
#define AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_2048ms               (3U << 16)
#define AEK_POW_BMS63EN_FASTCH_BALUV_COMMTIMEOUT_MASK                 (3U << 16)
/** @} */ 


/**
 * @name    BAL_1 (balance register #1) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_1_WDTIMEBALTIMER_MASK (127U << 0)
#define AEK_POW_BMS63EN_BAL_1_TIMEDBALTIMER       (127U << 7)
#define AEK_POW_BMS63EN_BAL_1_BAL_STOP            (1U << 14)
#define AEK_POW_BMS63EN_BAL_1_BAL_START           (1U << 15)
#define AEK_POW_BMS63EN_BAL_1_SLP_BAL_CONF        (1U << 16)
#define AEK_POW_BMS63EN_BAL_1_COMM_TIMEOUT_DIS    (1U << 17)
/** @} */ 


/**
 * @name    BAL_2 (balance register #2) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL13(n)          ((n) << 0)
#define AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL13_MASK        (127U << 0)
#define AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL14(n)          ((n) << 8)
#define AEK_POW_BMS63EN_BAL_2_THRTIMEDBALCELL14_MASK        (127U << 8)
#define AEK_POW_BMS63EN_BAL_2_TIMEDBALACC_FINE              (1U << 15)
#define AEK_POW_BMS63EN_BAL_2_BALMODE_MANUAL                (1U << 16)
#define AEK_POW_BMS63EN_BAL_2_BALMODE_TIMED                 (2U << 16)
#define AEK_POW_BMS63EN_BAL_2_BALMODE_MASK                  (3U << 16)
/** @} */ 


/**
 * @name    BAL_3 (balance register #3) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11(n)    ((n) << 0)
#define AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL11_MASK  (127U << 0)
#define AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL12(n)    ((n) << 8)
#define AEK_POW_BMS63EN_BAL_3_THRTIMEDBALCELL12_MASK  (127U << 8)
#define AEK_POW_BMS63EN_BAL_3_LOCK_ISOH_ISOFREQ       (1U << 15)
#define AEK_POW_BMS63EN_BAL_3_TRIMMING_RETRIGGER      (1U << 16)
#define AEK_POW_BMS63EN_BAL_3_FIRST_WUP_DONE          (1U << 17)
/** @} */ 


/**
 * @name    BAL_4 (balance register #4) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL9(n)     ((n) << 0)
#define AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL9_MASK   (127U << 0)
#define AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL10(n)    ((n) << 8)
#define AEK_POW_BMS63EN_BAL_4_THRTIMEDBALCELL10_MASK  (127U << 8)
#define AEK_POW_BMS63EN_BAL_4_CLK_MON_INIT_DONE       (1U << 15)
#define AEK_POW_BMS63EN_BAL_4_CLK_MON_EN              (1U << 17)
/** @} */ 


/**
 * @name    BAL_5 (balance register #5) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL7(n)     ((n) << 0)
#define AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL7_MASK   (127U << 0)
#define AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL8(n)     ((n) << 8)
#define AEK_POW_BMS63EN_BAL_5_THRTIMEDBALCELL8_MASK   (127U << 8)
#define AEK_POW_BMS63EN_BAL_5_TRANSCEIVER_VALID_BY_UP (1U << 16)
#define AEK_POW_BMS63EN_BAL_5_TRANSCEIVER_ON_BY_UP    (1U << 17)
/** @} */ 


/**
 * @name    BAL_6 (balance register #6) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL5(n)     ((n) << 0)
#define AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL5_MASK   (127U << 0)
#define AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL6(n)     ((n) << 8)
#define AEK_POW_BMS63EN_BAL_6_THRTIMEDBALCELL6_MASK   (127U << 8)
/** @} */ 


/**
 * @name    BAL_7 (balance register #7) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL3(n)     ((n) << 0)
#define AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL3_MASK   (127U << 0)
#define AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL4(n)     ((n) << 8)
#define AEK_POW_BMS63EN_BAL_7_THRTIMEDBALCELL4_MASK   (127U << 8)
/** @} */


/**
 * @name    BAL_8 (balance register #8) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL1(n)     ((n) << 0)
#define AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL1_MASK   (127U << 0)
#define AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL2(n)     ((n) << 8)
#define AEK_POW_BMS63EN_BAL_8_THRTIMEDBALCELL2_MASK   (127U << 8)
/** @} */


/**
 * @name    VCELL_THRESH_UV_OV (cell under/over voltage register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLUV(n)    ((n) << 0)
#define AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLUV_MASK  (255U << 0)
#define AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLOV(n)    ((n) << 8)
#define AEK_POW_BMS63EN_VCELL_THRESH_UV_OV_TRESHVCELLOV_MASK  (255U << 8)
/** @} */


/**
 * @name    VBATT_SUM_TH (sum of cell under/over voltage register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_UV_TH(n)     ((n) << 0)
#define AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_UV_TH_MASK   (255U << 0)
#define AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_OV_TH(n)     ((n) << 8)
#define AEK_POW_BMS63EN_VBATT_SUM_TH_VBATT_SUM_OV_TH_MASK   (255U << 8)
/** @} */


/**
 * @name    ADC_CONV (ADC conversion register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_ADCV_CONV_CYCLIC_CONTINOUS     (1U << 0)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_100ms         (~(7U << 1))
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_200ms         (1U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_400ms         (2U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_800ms         (3U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_1s6           (4U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_3s2           (5U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_6s4           (6U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_12s8          (7U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_MASK          (7U << 1)
#define AEK_POW_BMS63EN_ADCV_CONV_HWSC                 (1U << 4)
#define AEK_POW_BMS63EN_ADCV_CONV_BAL_TERM_CONV        (1U << 5)
#define AEK_POW_BMS63EN_ADCV_CONV_CELL_TERM_CONV       (1U << 6)
#define AEK_POW_BMS63EN_ADCV_CONV_GPIO_TERM_CONV       (1U << 7)
#define AEK_POW_BMS63EN_ADCV_CONV_GPIO_CONV            (1U << 8)
#define AEK_POW_BMS63EN_ADCV_CONV_ADC_FILTER_SOC(n)    ((n) << 9)
#define AEK_POW_BMS63EN_ADCV_CONV_ADC_FILTER_SOC_MASK  (7U << 9)
#define AEK_POW_BMS63EN_ADCV_CONV_DUTY_ON              (1U << 12)
#define AEK_POW_BMS63EN_ADCV_CONV_CONF_CYCLIC_EN       (1U << 13)
#define AEK_POW_BMS63EN_ADCV_CONV_OVR_LATCH            (1U << 14)
#define AEK_POW_BMS63EN_ADCV_CONV_SOC                  (1U << 15)
#define AEK_POW_BMS63EN_ADCV_CONV_TCYCLE_OVF           (1U << 16)
#define AEK_POW_BMS63EN_ADCV_CONV_ADC_CROSS_CHECK      (1U << 17)
/** @} */


/**
 * @name    NCYCLE_PROG_1 (n_cycle programming register #1) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR (1U << 1)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR  (1U << 2)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_CROSS_ODD_EVEN_CELL   (1U << 3)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_CYCLIC_UPDATE         (1U << 4)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_BAL_AUTO_PAUSE        (1U << 5)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_BAL_TIM_AUTO_PAUSE    (1U << 6)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_BAL_TERM(n)    ((n) << 7)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_BAL_TERM_MASK  (7U << 7)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_CELL_TERM(n)   ((n) << 10)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_CELL_TERM_MASK (7U << 10)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_GPIO_TERM(n)   ((n) << 13)
#define AEK_POW_BMS63EN_NCYCLE_PROG_1_NCYCLE_GPIO_TERM_MASK (7U << 13)
/** @} */


/**
 * @name    NCYCLE_PROG_2 (n_cycle programming register #2) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_ADC_FILTER_SLEEP(n)   ((n) << 6)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_ADC_FILTER_SLEEP_MASK (7U << 6)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_TCYCLE_SLEEP(n)       ((n) << 3)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_TCYCLE_SLEEP_MASK     (7U << 3)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_ADC_FILTER_CYCLE(n)   ((n) << 6)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_ADC_FILTER_CYCLE_MASK (7U << 6)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_NCYCLE_HWSC(n)        ((n) << 10)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_NCYCLE_HWSC_MASK      (7U << 10)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_NCYCLE_GPIO(n)        ((n) << 13)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_NCYCLE_GPIO_MASK      (7U << 13)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_VTFREF_DYN_EN         (1U << 16)
#define AEK_POW_BMS63EN_NCYCLE_PROG_2_VTFREF_EN             (1U << 17)
/** @} */


/**
 * @name    BALCCELL14_7ACT (cell 14 -> 7 balancing enable register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_DIS   (1U << 0)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_EN    (2U << 0)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL7_MASK  (3U << 0)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_DIS   (1U << 2)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_EN    (2U << 2)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL8_MASK  (3U << 2)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_DIS   (1U << 4)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_EN    (2U << 4)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL9_MASK  (3U << 4)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_DIS  (1U << 6)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_EN   (2U << 6)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL10_MASK (3U << 6)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_DIS  (1U << 8)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_EN   (2U << 8)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL11_MASK (3U << 8)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_DIS  (1U << 10)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_EN   (2U << 10)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL12_MASK (3U << 10)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_DIS  (1U << 12)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_EN   (2U << 12)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL13_MASK (3U << 12)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_DIS  (1U << 14)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_EN   (2U << 14)
#define AEK_POW_BMS63EN_BALCELL14_7ACT_BAL14_MASK (3U << 14)
/** @} */


/**
 * @name    BALCCELL6_1ACT (cell 6 -> 1 balancing enable register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_BALCELL6_1ACT_EOF_BAL         (1U << 0)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL_ON_EOF_MASK (3U << 0)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL_ON          (1U << 1)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_DIS        (1U << 4)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_EN         (2U << 4)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL1_MASK       (3U << 4)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_DIS        (1U << 6)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_EN         (2U << 6)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL2_MASK       (3U << 6)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_DIS        (1U << 8)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_EN         (2U << 8)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL3_MASK       (3U << 8)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_DIS        (1U << 10)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_EN         (2U << 10)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL4_MASK       (3U << 10)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_DIS        (1U << 12)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_EN         (2U << 12)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL5_MASK       (3U << 12)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_DIS        (1U << 14)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_EN         (2U << 14)
#define AEK_POW_BMS63EN_BALCELL6_1ACT_BAL6_MASK       (3U << 14)
/** @} */


/**
 * @name    FSM (finite state machine register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_FSM_WU_CYC_WKUP           (1U << 0)
#define AEK_POW_BMS63EN_FSM_WU_FAULTH             (1U << 1)
#define AEK_POW_BMS63EN_FSM_WU_ISOLINE            (1U << 2)
#define AEK_POW_BMS63EN_FSM_WU_SPI                (1U << 3)
#define AEK_POW_BMS63EN_FSM_WU_GPIO7              (1U << 4)
#define AEK_POW_BMS63EN_FSM_FSM_STATUS_SLEEP      (1U << 8)
#define AEK_POW_BMS63EN_FSM_FSM_STATUS_INIT       (2U << 8)
#define AEK_POW_BMS63EN_FSM_FSM_STATUS_NORMAL     (4U << 8)
#define AEK_POW_BMS63EN_FSM_FSM_STATUS_CYC_WKUP   (8U << 8)
#define AEK_POW_BMS63EN_FSM_FSM_STATUS_MASK       (15U << 8)
#define AEK_POW_BMS63EN_FSM_GO2SLP                (2U << 12)
#define AEK_POW_BMS63EN_FSM_SW_RST                (2U << 14)
/** @} */ 


/**
 * @name    GPOxO_AND_GPI93 (GPOx and GPI 9 -> 3 register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI3     (1U << 2)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI4     (1U << 3)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI5     (1U << 4)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI6     (1U << 5)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI7     (1U << 6)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI8     (1U << 7)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPI9     (1U << 8)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO3ON   (1U << 11)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO4ON   (1U << 12)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO5ON   (1U << 13)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO6ON   (1U << 14)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO7ON   (1U << 15)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO8ON   (1U << 16)
#define AEK_POW_BMS63EN_GPOxON_AND_GPI93_GPO9ON   (1U << 17)
/** @} */ 


/**
 * @name    GPIO9_3_CONF (GPIO 9 -> 3 configuration register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_WUP_EN       (1U << 3)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_AI    (~(3U << 4)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_DI    (2U << 4)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_DO    (3U << 4)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO3_CONFIG_MASK  (3U << 4)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_AI    (~(3U << 6)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_DI    (2U << 6)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_DO    (3U << 6)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO4_CONFIG_MASK  (3U << 6)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_AI    (~(3U << 8)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_DI    (2U << 8)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_DO    (3U << 8)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO5_CONFIG_MASK  (3U << 8)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_AI    (~(3U << 10)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_DI    (2U << 10)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_DO    (3U << 10)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO6_CONFIG_MASK  (3U << 10)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_AI    (~(3U << 12)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_DI    (2U << 12)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_DO    (3U << 12)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO7_CONFIG_MASK  (3U << 12)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_AI    (~(3U << 14)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_DI    (2U << 14)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_DO    (3U << 14)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO8_CONFIG_MASK  (3U << 14)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_AI    (~(3U << 16)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_DI    (2U << 16)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_DO    (3U << 16)
#define AEK_POW_BMS63EN_GPIO9_3_CONF_GPIO9_CONFIG_MASK  (3U << 16)
/** @} */


/**
 * @name    GPIO3_THR (GPIO3 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO3_THR_GPIO3_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO3_THR_GPIO3_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO3_THR_GPIO3_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO3_THR_GPIO3_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO4_THR (GPIO4 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO4_THR_GPIO4_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO4_THR_GPIO4_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO4_THR_GPIO4_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO4_THR_GPIO4_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO5_THR (GPIO5 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO5_THR_GPIO5_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO5_THR_GPIO5_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO5_THR_GPIO5_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO5_THR_GPIO5_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO6_THR (GPIO6 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO6_THR_GPIO6_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO6_THR_GPIO6_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO6_THR_GPIO6_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO6_THR_GPIO6_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO7_THR (GPIO7 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO7_THR_GPIO7_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO7_THR_GPIO7_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO7_THR_GPIO7_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO7_THR_GPIO7_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO8_THR (GPIO8 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO8_THR_GPIO8_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO8_THR_GPIO8_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO8_THR_GPIO8_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO8_THR_GPIO8_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    GPIO9_THR (GPIO9 threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO9_THR_GPIO9_UT_TH(n)    ((n) << 0)
#define AEK_POW_BMS63EN_GPIO9_THR_GPIO9_UT_TH_MASK  (511U << 0)
#define AEK_POW_BMS63EN_GPIO9_THR_GPIO9_OT_TH(n)    ((n) << 9)
#define AEK_POW_BMS63EN_GPIO9_THR_GPIO9_OT_TH_MASK  (511U << 9)
/** @} */


/**
 * @name    VCELLS_EN (cell enable register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN       (1U << 0)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL2_EN       (1U << 1)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL3_EN       (1U << 2)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL4_EN       (1U << 3)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL5_EN       (1U << 4)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL6_EN       (1U << 5)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL7_EN       (1U << 6)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL8_EN       (1U << 7)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL9_EN       (1U << 8)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL10_EN      (1U << 9)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL11_EN      (1U << 10)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL12_EN      (1U << 11)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL13_EN      (1U << 12)
#define AEK_POW_BMS63EN_VCELLS_EN_VCELL14_EN      (1U << 13)
/** @} */


/**
 * @name    FAULTMASK (balancing undervoltage fault mask register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_FAULTMASK_VCELL1_BAL_UV_MSK   (1U << 0)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL2_BAL_UV_MSK   (1U << 1)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL3_BAL_UV_MSK   (1U << 2)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL4_BAL_UV_MSK   (1U << 3)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL5_BAL_UV_MSK   (1U << 4)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL6_BAL_UV_MSK   (1U << 5)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL7_BAL_UV_MSK   (1U << 6)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL8_BAL_UV_MSK   (1U << 7)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL9_BAL_UV_MSK   (1U << 8)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL10_BAL_UV_MSK  (1U << 9)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL11_BAL_UV_MSK  (1U << 10)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL12_BAL_UV_MSK  (1U << 11)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL13_BAL_UV_MSK  (1U << 12)
#define AEK_POW_BMS63EN_FAULTMASK_VCELL14_BAL_UV_MSK  (1U << 13)
/** @} */


/**
 * @name    FAULTMASK2 (fault mask register #2) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO3_FASTCHG_OT_MSK       (1U << 0)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO4_FASTCHG_OT_MSK       (1U << 1)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO5_FASTCHG_OT_MSK       (1U << 2)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO6_FASTCHG_OT_MSK       (1U << 3)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO7_FASTCHG_OT_MSK       (1U << 4)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO8_FASTCHG_OT_MSK       (1U << 5)
#define AEK_POW_BMS63EN_FAULTMASK2_GPIO9_FASTCHG_OT_MSK       (1U << 6)
#define AEK_POW_BMS63EN_FAULTMASK2_TRIMCALOK                  (1U << 7)
#define AEK_POW_BMS63EN_FAULTMASK2_TRIM_DWNL_TRIED            (1U << 8)
#define AEK_POW_BMS63EN_FAULTMASK2_RAM_CRC_ERRMSK             (1U << 9)
#define AEK_POW_BMS63EN_FAULTMASK2_RAM_CRC_ERR                (1U << 10)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERRMSK_CAL_FF   (1U << 11)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERR_CAL_FF      (1U << 12)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERRMSK_CAL_RAM  (1U << 13)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERR_CAL_RAM     (1U << 14)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERRMSK_SECT_0   (1U << 15)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_CRC_ERR_SECT_0      (1U << 16)
#define AEK_POW_BMS63EN_FAULTMASK2_EEPROM_DWNLD_DONE          (1U << 17)
/** @} */


/**
 * @name    CSA_THRESH_NORM (current stay-under threshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_CSA_THRESH_NORM_ADC_OVC_CURR_THRESHOLD_NORM(n)    ((n) << 0)
#define AEK_POW_BMS63EN_CSA_THRESH_NORM_ADC_OVC_CURR_THRESHOLD_NORM_MASK  (262143U << 0)
/** @} */


/**
 * @name    CSA_GPIO_MSK (current stay-under GPIO mask register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO3_OT_UT_MSK                  (1U << 0)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO4_OT_UT_MSK                  (1U << 1)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO5_OT_UT_MSK                  (1U << 2)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO6_OT_UT_MSK                  (1U << 3)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO7_OT_UT_MSK                  (1U << 4)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO8_OT_UT_MSK                  (1U << 5)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_GPIO9_OT_UT_MSK                  (1U << 6)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_SENSE_MINUS_OPEN                 (1U << 8)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_SENSE_PLUS_OPEN                  (1U << 9)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_OVC_NORM_MKS                     (1U << 10)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_OVC_SLEEP_MKS                    (1U << 11)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_COULOMBCOUNTER_EN                (1U << 12)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_ADC_OVC_CURR_THRESHOLD_SLEEP(n)  ((n) << 13)
#define AEK_POW_BMS63EN_CSA_GPIO_MSK_ADC_OVC_CURR_THRESHOLD_MASK      (31 << 13)
/** @} */ 


/**
 * @name    VCELL1 (Cell #1 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL1_VCELL1_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL1_D_RDY_VCELL1       (1U << 16)
/** @} */ 


/**
 * @name    VCELL2 (Cell #2 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL2_VCELL2_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL2_D_RDY_VCELL2       (1U << 16)
/** @} */ 


/**
 * @name    VCELL3 (Cell #3 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL3_VCELL3_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL3_D_RDY_VCELL3       (1U << 16)
/** @} */ 


/**
 * @name    VCELL4 (Cell #4 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL4_VCELL4_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL4_D_RDY_VCELL4       (1U << 16)
/** @} */ 


/**
 * @name    VCELL5 (Cell #5 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL5_VCELL1_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL5_D_RDY_VCELL5       (1U << 16)
/** @} */ 


/**
 * @name    VCELL6 (Cell #6 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL6_VCELL6_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL6_D_RDY_VCELL6       (1U << 16)
/** @} */ 


/**
 * @name    VCELL7 (Cell #7 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL7_VCELL7_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL7_D_RDY_VCELL7       (1U << 16)
/** @} */ 


/**
 * @name    VCELL8 (Cell #8 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL8_VCELL8_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL8_D_RDY_VCELL8       (1U << 16)
/** @} */ 


/**
 * @name    VCELL9 (Cell #9 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL9_VCELL9_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_VCELL9_D_RDY_VCELL9       (1U << 16)
/** @} */ 


/**
 * @name    VCELL10 (Cell #10 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL10_VCELL10_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VCELL10_D_RDY_VCELL10     (1U << 16)
/** @} */ 


/**
 * @name    VCELL11 (Cell #11 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL11_VCELL11_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VCELL11_D_RDY_VCELL11     (1U << 16)
/** @} */ 


/**
 * @name    VCELL12 (Cell #12 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL12_VCELL12_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VCELL12_D_RDY_VCELL12     (1U << 16)
/** @} */ 


/**
 * @name    VCELL13 (Cell #13 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL13_VCELL13_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VCELL13_D_RDY_VCELL13     (1U << 16)
/** @} */ 


/**
 * @name    VCELL14 (Cell #14 register) definitions
 * @{
 */  
#define AEK_POW_BMS63EN_VCELL14_VCELL14_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VCELL14_D_RDY_VCELL14     (1U << 16)
/** @} */ 


/**
 * @name    IBATTERY_SYNCH (Interpolated battery synchronization register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_IBATTERY_SYNCH_CUR_INST_SYNCH_MASK  (262143U << 0)
/** @} */ 


/**
 * @name    IBATTERY_CALIB (Interpolated battery calibration register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_IBATTERY_CALIB_CUR_INST_CALIB_MASK  (262143U << 0)
/** @} */ 


/**
 * @name    COULCNTRTIME (Coulomb counter time register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_COULCNTRTIME_COULOMBCNTTIME_MASK  (65535U << 0)
/** @} */ 


/**
 * @name    COULCNTRMSB (Coulomb counter MSB register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_COULCNTRMSB_COULOMBCOUNTER_MSB_MASK (65535U << 0)
/** @} */ 


/**
 * @name    COULCNTRLSB (Coulomb counter LSB register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_COULCNTRLSB_COULOMBCOUNTER_LSB_MASK (65535U << 0)
/** @} */ 


/**
 * @name    GPIO3_MEAS (GPIO #3 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO3_MEAS_GPIO3_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO3_MEAS_D_DRY_GPIO3      (1U << 16)
#define AEK_POW_BMS63EN_GPIO3_MEAS_RATIO_ABS_3_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO4_MEAS (GPIO #4 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO4_MEAS_GPIO4_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO4_MEAS_D_DRY_GPIO4      (1U << 16)
#define AEK_POW_BMS63EN_GPIO4_MEAS_RATIO_ABS_4_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO3_MEAS (GPIO #5 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO5_MEAS_GPIO5_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO5_MEAS_D_DRY_GPIO5      (1U << 16)
#define AEK_POW_BMS63EN_GPIO5_MEAS_RATIO_ABS_5_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO3_MEAS (GPIO #6 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO6_MEAS_GPIO6_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO6_MEAS_D_DRY_GPIO6      (1U << 16)
#define AEK_POW_BMS63EN_GPIO6_MEAS_RATIO_ABS_6_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO3_MEAS (GPIO #7 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO7_MEAS_GPIO7_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO7_MEAS_D_DRY_GPIO7      (1U << 16)
#define AEK_POW_BMS63EN_GPIO7_MEAS_RATIO_ABS_7_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO8_MEAS (GPIO #8 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO8_MEAS_GPIO8_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO8_MEAS_D_DRY_GPIO8      (1U << 16)
#define AEK_POW_BMS63EN_GPIO8_MEAS_RATIO_ABS_8_SEL  (1U << 17)
/** @} */ 


/**
 * @name    GPIO9_MEAS (GPIO #9 measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO9_MEAS_GPIO9_MEAS_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_GPIO9_MEAS_D_DRY_GPIO9      (1U << 16)
#define AEK_POW_BMS63EN_GPIO9_MEAS_RATIO_ABS_9_SEL  (1U << 17)
/** @} */ 


/**
 * @name    TEMPCHI (Chip temperature measurement register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_TEMPCHIP_TEMPCHIP_MASK    (255U << 0)
#define AEK_POW_BMS63EN_TEMPCHIP_OTCHIP           (1U << 8)
/** @} */ 


/**
 * @name    FAULTS1 (Fault status #1 register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_FAULTS1_COMM_TIMEOUT_FLT    (1U << 0)
#define AEK_POW_BMS63EN_FAULTS1_FAULT_L_LINE_STATUS (1U << 3)
#define AEK_POW_BMS63EN_FAULTS1_FAULTHLINE_FAULT    (1U << 4)
#define AEK_POW_BMS63EN_FAULTS1_HEARTBEAT_FAULT     (1U << 5)
#define AEK_POW_BMS63EN_FAULTS1_VCOM_UV             (1U << 6)
#define AEK_POW_BMS63EN_FAULTS1_VCOM_OV             (1U << 7)
#define AEK_POW_BMS63EN_FAULTS1_VREG_OV             (1U << 8)
#define AEK_POW_BMS63EN_FAULTS1_VREG_UV             (1U << 9)
#define AEK_POW_BMS63EN_FAULTS1_VTREF_OV            (1U << 10)
#define AEK_POW_BMS63EN_FAULTS1_VTREF_UV            (1U << 11)
#define AEK_POW_BMS63EN_FAULTS1_VDIG_OV             (1U << 12)
#define AEK_POW_BMS63EN_FAULTS1_VANA_OV             (1U << 13)
/** @} */ 


/**
 * @name    FAULTS2 (Fault status #2 register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_FAULTS2_CURR_SENSE_OVC_NORM   (1U << 0)
#define AEK_POW_BMS63EN_FAULTS2_CURR_SENSE_OVC_SLEEP  (1U << 1)
#define AEK_POW_BMS63EN_FAULTS2_EOBTIMEERROR          (1U << 2)
#define AEK_POW_BMS63EN_FAULTS2_COCOUO                (1U << 3)
#define AEK_POW_BMS63EN_FAULTS2_LOSS_CGND             (1U << 6)
#define AEK_POW_BMS63EN_FAULTS2_LOSS_DGND             (1U << 7)
#define AEK_POW_BMS63EN_FAULTS2_LOSS_AGND             (1U << 8)
#define AEK_POW_BMS63EN_FAULTS2_OSCFAIL               (1U << 10)
#define AEK_POW_BMS63EN_FAULTS2_SPIENLATCH            (1U << 12)
/** @} */ 


/**
 * @name    BAL_OPEN (Balance open register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BAL_OPEN_BAL1_OPEN        (1U << 2)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL2_OPEN        (1U << 3)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL3_OPEN        (1U << 4)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL4_OPEN        (1U << 5)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL5_OPEN        (1U << 6)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL6_OPEN        (1U << 7)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL7_OPEN        (1U << 8)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL8_OPEN        (1U << 9)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL9_OPEN        (1U << 10)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL10_OPEN       (1U << 11)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL11_OPEN       (1U << 12)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL12_OPEN       (1U << 13)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL13_OPEN       (1U << 14)
#define AEK_POW_BMS63EN_BAL_OPEN_BAL14_OPEN       (1U << 15)
/** @} */ 


/**
 * @name    BAL_SHORT (Balance short register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BAL_SHORT_BAL1L_SHORT     (1U << 2)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL2L_SHORT     (1U << 3)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL3L_SHORT     (1U << 4)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL4L_SHORT     (1U << 5)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL5L_SHORT     (1U << 6)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL6L_SHORT     (1U << 7)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL7L_SHORT     (1U << 8)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL8L_SHORT     (1U << 9)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL9L_SHORT     (1U << 10)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL10L_SHORT    (1U << 11)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL11L_SHORT    (1U << 12)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL12L_SHORT    (1U << 13)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL13L_SHORT    (1U << 14)
#define AEK_POW_BMS63EN_BAL_SHORT_BAL14L_SHORT    (1U << 15)
/** @} */ 


/**
 * @name    VSUMBATT (battery voltage sum register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VSUMBATT_VSUM_BATT19_2_MASK (262143U << 0)
/** @} */ 


/**
 * @name    VBATTDIV (battery voltage direct conversion register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VBATTDIV_VBATTDIV_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_VBATTDIV_VSUM_BATT1_0_MASK  (3U << 16)
/** @} */ 


/**
 * @name    CELL_OPEN (open cell register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_CELL_OPEN_CELL0_OPEN          (1U << 0)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL1_OPEN          (1U << 1)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL2_OPEN          (1U << 2)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL3_OPEN          (1U << 3)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL4_OPEN          (1U << 4)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL5_OPEN          (1U << 5)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL6_OPEN          (1U << 6)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL7_OPEN          (1U << 7)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL8_OPEN          (1U << 8)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL9_OPEN          (1U << 9)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL10_OPEN         (1U << 10)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL11_OPEN         (1U << 11)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL12_OPEN         (1U << 12)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL13_OPEN         (1U << 13)
#define AEK_POW_BMS63EN_CELL_OPEN_CELL14_OPEN         (1U << 14)
#define AEK_POW_BMS63EN_CELL_OPEN_BATTERY_OPEN        (1U << 15)
#define AEK_POW_BMS63EN_CELL_OPEN_DATA_READY_VBATTDIV (1U << 16)
#define AEK_POW_BMS63EN_CELL_OPEN_DATA_READY_VSUM     (1U << 17)
/** @} */ 


/**
 * @name    VCELL_UV (cell undervoltage register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VCELL_UV_VCELL1_UV        (1U << 0)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL2_UV        (1U << 1)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL3_UV        (1U << 2)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL4_UV        (1U << 3)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL5_UV        (1U << 4)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL6_UV        (1U << 5)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL7_UV        (1U << 6)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL8_UV        (1U << 7)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL9_UV        (1U << 8)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL10_UV       (1U << 9)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL11_UV       (1U << 10)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL12_UV       (1U << 11)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL13_UV       (1U << 12)
#define AEK_POW_BMS63EN_VCELL_UV_VCELL14_UV       (1U << 13)
#define AEK_POW_BMS63EN_VCELL_UV_VSUM_UV          (1U << 14)
#define AEK_POW_BMS63EN_VCELL_UV_VBATTCRIT_UV     (1U << 15)
#define AEK_POW_BMS63EN_VCELL_UV_VBATT_WRN_UV     (1U << 16)
/** @} */ 


/**
 * @name    VCELL_OV (cell overvoltage register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VCELL_OV_VCELL1_OV        (1U << 0)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL2_OV        (1U << 1)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL3_OV        (1U << 2)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL4_OV        (1U << 3)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL5_OV        (1U << 4)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL6_OV        (1U << 5)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL7_OV        (1U << 6)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL8_OV        (1U << 7)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL9_OV        (1U << 8)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL10_OV       (1U << 9)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL11_OV       (1U << 10)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL12_OV       (1U << 11)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL13_OV       (1U << 12)
#define AEK_POW_BMS63EN_VCELL_OV_VCELL14_OV       (1U << 13)
#define AEK_POW_BMS63EN_VCELL_OV_VSUM_OV          (1U << 14)
#define AEK_POW_BMS63EN_VCELL_OV_VBATTCRIT_OV     (1U << 15)
#define AEK_POW_BMS63EN_VCELL_OV_VBATT_WRN_OV     (1U << 16)
/** @} */ 


/**
 * @name    VGPIO_OT_UT (GPIO Over/Under threshold voltage register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO3_UT      (1U << 0)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO4_UT      (1U << 1)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO5_UT      (1U << 2)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO6_UT      (1U << 3)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO7_UT      (1U << 4)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO8_UT      (1U << 5)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO9_UT      (1U << 6)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO3_OT      (1U << 7)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO4_OT      (1U << 8)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO5_OT      (1U << 9)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO6_OT      (1U << 10)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO7_OT      (1U << 11)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO8_OT      (1U << 12)
#define AEK_POW_BMS63EN_VGPIO_OT_UT_GPIO9_OT      (1U << 13)
/** @} */ 


/**
 * @name    VCELL_BAL_UV (cell balance undervoltage register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL1_BAL_UV  (1U << 0)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL2_BAL_UV  (1U << 1)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL3_BAL_UV  (1U << 2)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL4_BAL_UV  (1U << 3)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL5_BAL_UV  (1U << 4)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL6_BAL_UV  (1U << 5)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL7_BAL_UV  (1U << 6)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL8_BAL_UV  (1U << 7)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL9_BAL_UV  (1U << 8)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL10_BAL_UV (1U << 9)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL11_BAL_UV (1U << 10)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL12_BAL_UV (1U << 11)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL13_BAL_UV (1U << 12)
#define AEK_POW_BMS63EN_VCELL_BAL_UV_VCELL14_BAL_UV (1U << 13)
/** @} */ 


/**
 * @name    GPIO_FASTCHG_OT (GPIO fast charge underthreshold register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO3_FASTCHG_OT  (1U << 0)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO4_FASTCHG_OT  (1U << 1)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO5_FASTCHG_OT  (1U << 2)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO6_FASTCHG_OT  (1U << 3)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO7_FASTCHG_OT  (1U << 4)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO8_FASTCHG_OT  (1U << 5)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO9_FASTCHG_OT  (1U << 6)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO3_OPEN        (1U << 7)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO4_OPEN        (1U << 8)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO5_OPEN        (1U << 9)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO6_OPEN        (1U << 10)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO7_OPEN        (1U << 11)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO8_OPEN        (1U << 12)
#define AEK_POW_BMS63EN_GPIO_FASTCHG_OT_GPIO9_OPEN        (1U << 13)
/** @} */ 


/**
 * @name    MUX_BIST_FAIL (muxed bist failure register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_MUX_BIST_FAIL_MUX_BIST_FAIL_MASK  (16383U << 0)
#define AEK_POW_BMS63EN_MUX_BIST_FAIL_HWSC_DONE           (1U << 14)
/** @} */ 


/**
 * @name    BIST_COMP (comparator bist register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BIST_COMP_BIST_BAL_COMP_LS_FAIL_MASK  (127U << 0)
#define AEK_POW_BMS63EN_BIST_COMP_BIST_BAL_COMP_HS_FAIL_MASK  (127U << 7)
#define AEK_POW_BMS63EN_BIST_COMP_VTREF_COMP_BIST_FAIL        (1U << 14)
#define AEK_POW_BMS63EN_BIST_COMP_VCOM_COMP_BIST_FAIL         (1U << 15)
#define AEK_POW_BMS63EN_BIST_COMP_VREG_COMP_BIST_FAIL         (1U << 16)
#define AEK_POW_BMS63EN_BIST_COMP_VBAT_COMP_BIST_FAIL         (1U << 17)
/** @} */ 


/**
 * @name    OPEN_BIST_FAIL (bist on open mux read register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_OPEN_BIST_FAIL_OPEN_BIST_FAIL_MASK  (16383U << 0)
/** @} */


/**
 * @name    GPIO_BIST_FAIL (bist on GPIO mux read register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPIO_BIST_FAIL_MASK  (127U << 0)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_VTREF_BIST_FAIL      (1U << 7)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_VBAT_DIV_BIST_FAIL   (1U << 8)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO3SHORT            (1U << 11)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO4SHORT            (1U << 12)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO5SHORT            (1U << 13)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO6SHORT            (1U << 14)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO7SHORT            (1U << 15)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO8SHORT            (1U << 16)
#define AEK_POW_BMS63EN_GPIO_BIST_FAIL_GPO9SHORT            (1U << 17)
/** @} */


/**
 * @name    VTREF (voltage reference register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_VTREF_VTREF_MEAS_MASK     (65535U << 0)
#define AEK_POW_BMS63EN_VTREF_D_RDY_VTREF         (1U << 16)
#define AEK_POW_BMS63EN_VTREF_ENABLED             (1U << 17)
/** @} */


/**
 * @name    DEV_SERVICE_ID (service read register) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_DEVICE_SERVICE_RD_TM_FSM_STATUS_MASK      (7U << 0)
#define AEK_POW_BMS63EN_DEVICE_SERVICE_RD_SPI_TEST_EN             (1U << 3)
#define AEK_POW_BMS63EN_DEVICE_SERVICE_RD_TM_PIN_FBCK             (1U << 4)
#define AEK_POW_BMS63EN_DEVICE_SERVICE_RD_CHIPVERSIONID_MASK      (255U << 5)
/** @} */

/**
 * @name    Burst command #1 (0x78) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR1_D_RDY_VCELL1         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR2_VCELL2_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR2_D_RDY_VCELL2         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR2_VCELL2_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR3_VCELL3_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR3_D_RDY_VCELL3         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR3_VCELL3_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR4_VCELL4_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR4_D_RDY_VCELL4         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR4_VCELL4_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR5_VCELL5_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR5_D_RDY_VCELL5         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR5_VCELL5_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR6_VCELL6_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR6_D_RDY_VCELL6         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR6_VCELL6_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR7_VCELL7_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR7_D_RDY_VCELL7         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR7_VCELL7_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR8_VCELL8_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR8_D_RDY_VCELL8         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR8_VCELL8_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR9_VCELL9_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR9_D_RDY_VCELL9         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR9_VCELL9_EN            (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR10_VCELL10_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR10_D_RDY_VCELL10       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR10_VCELL10_EN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR11_VCELL11_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR11_D_RDY_VCELL11       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR11_VCELL11_EN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR12_VCELL12_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR12_D_RDY_VCELL12       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR12_VCELL12_EN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR13_VCELL13_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR13_D_RDY_VCELL13       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR13_VCELL13_EN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR14_VCELL14_MASK        (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR14_D_RDY_VCELL14       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR14_VCELL14_EN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD1_FR15_VSUM_BATT9_2_MASK   (2621431U << 0)

#define AEK_POW_BMS63EN_BURST_CMD1_FR16_VBATT_DIV_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR16_VSUM_BATT1_0_MASK   (3U << 16)

#define AEK_POW_BMS63EN_BURST_CMD1_FR17_EOF_BAL             (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_BAL_ON              (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_TIMEDBALTIMER_MASK  (127U << 2)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_TIMEDBALACC_FINE    (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_VSUM_UV             (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_VSUM_OV             (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_DUTY_ON             (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_CONF_CYCLIC_EN      (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_OVR_LATCH           (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_SOC                 (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_DATA_READY_VBATTDIV (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD1_FR17_DATA_READY_VSUM     (1U << 17)
/** @} */ 


/**
 * @name    Burst command #2 (0x7A) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_WU_CYC_WUP                   (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_WU_FAULTH                    (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_WU_SPI                       (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_WU_ISOLINE                   (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_WU_GPIO7                     (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VCOM_UV                      (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VCOM_OV                      (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VREG_OV                      (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VREG_UV                      (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VTREF_OV                     (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VTREF_UV                     (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VDIG_OV                      (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_VANA_OV                      (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_OTCHIP                       (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_SENSE_MINUS_OPEN             (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_SENSE_PLUS_OPEN              (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_TCYCLE_OVF                   (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR1_OVR_LATCH                    (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO6_OPEN                   (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO7_OPEN                   (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO8_OPEN                   (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO9_OPEN                   (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO3_FASTCHG_OT             (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO4_FASTCHG_OT             (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO5_FASTCHG_OT             (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO6_FASTCHG_OT             (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO7_FASTCHG_OT             (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO8_FASTCHG_OT             (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_GPIO9_FASTCHG_OT             (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_EOBTIMEERROR                 (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_COCOUOVF                     (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_TRIMMCALOK                   (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_LOSS_GNDREF                  (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_LOSS_CNGD                    (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_LOSS_DGND                    (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR2_LOSS_AGND                    (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL1_OPEN                    (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL2_OPEN                    (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL3_OPEN                    (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL4_OPEN                    (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL5_OPEN                    (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL6_OPEN                    (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL7_OPEN                    (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL8_OPEN                    (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL9_OPEN                    (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL10_OPEN                   (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL11_OPEN                   (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL12_OPEN                   (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL13_OPEN                   (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_BAL14_OPEN                   (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_EEPROM_DWNLD_DONE            (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_GPIO3_OPEN                   (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_GPIO4_OPEN                   (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR3_GPIO5_OPEN                   (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL1_SHORT                   (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL2_SHORT                   (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL3_SHORT                   (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL4_SHORT                   (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL5_SHORT                   (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL6_SHORT                   (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL7_SHORT                   (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL8_SHORT                   (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL9_SHORT                   (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL10_SHORT                  (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL11_SHORT                  (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL12_SHORT                  (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL13_SHORT                  (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_BAL14_SHORT                  (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_VBAT_COMP_BIST_FAIL          (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_VREG_COMP_BIST_FAIL          (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_VCOM_COMP_BIST_FAIL          (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR4_VTREF_COMP_BIST_FAIL         (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL0_OPEN                   (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL1_OPEN                   (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL2_OPEN                   (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL3_OPEN                   (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL4_OPEN                   (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL5_OPEN                   (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL6_OPEN                   (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL7_OPEN                   (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL8_OPEN                   (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL9_OPEN                   (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL10_OPEN                  (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL11_OPEN                  (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL12_OPEN                  (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL13_OPEN                  (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_CELL14_OPEN                  (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_EEPROM_CRC_ERR_CAL_FF        (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_HWSC_DONE                    (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR5_VBATT_OPEN                   (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL1_UV                    (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL2_UV                    (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL3_UV                    (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL4_UV                    (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL5_UV                    (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL6_UV                    (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL7_UV                    (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL8_UV                    (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL9_UV                    (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL10_UV                   (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL11_UV                   (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL12_UV                   (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL13_UV                   (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_VCELL14_UV                   (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_RAM_CRC_ERR                  (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_EEPROM_CRC_ERR_CAL_RAM       (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_COMM_IIMEOUT_FLT             (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR6_EEPROM_CRC_ERR_SECT_0        (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL1_OV                    (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL2_OV                    (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL3_OV                    (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL4_OV                    (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL5_OV                    (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL6_OV                    (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL7_OV                    (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL8_OV                    (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL9_OV                    (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL10_OV                   (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL11_OV                   (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL12_OV                   (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL13_OV                   (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VCELL14_OV                   (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VSUM_UV                      (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VBATTCRIT_UV                 (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VBATT_WRN_UV                 (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR7_VBATT_WRN_OV                 (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO3_UT                     (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO4_UT                     (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO5_UT                     (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO6_UT                     (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO7_UT                     (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO8_UT                     (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO9_UT                     (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO3_OT                     (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO4_OT                     (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO5_OT                     (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO6_OT                     (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO7_OT                     (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO8_OT                     (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_GPIO9_OT                     (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_VSUM_OV                      (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_VBATTCRIT_OV                 (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_EOF_BAL                      (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR8_BAL_ON                       (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL1_BAL_UV                (1U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL2_BAL_UV                (1U << 1)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL3_BAL_UV                (1U << 2)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL4_BAL_UV                (1U << 3)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL5_BAL_UV                (1U << 4)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL6_BAL_UV                (1U << 5)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL7_BAL_UV                (1U << 6)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL8_BAL_UV                (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL9_BAL_UV                (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL10_BAL_UV               (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL11_BAL_UV               (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL12_BAL_UV               (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL13_BAL_UV               (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_VCELL14_BAL_UV               (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_GPO3ON                       (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_GPO4ON                       (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_GPO5ON                       (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR9_GPO6ON                       (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPIO_BIST_FAIL_MASK         (127U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO3SHORT                   (1U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO4SHORT                   (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO5SHORT                   (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO6SHORT                   (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO7SHORT                   (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO8SHORT                   (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO9SHORT                   (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO7ON                      (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO8ON                      (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_GPO9ON                      (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR10_FAULT_L_LINE_STATUS         (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR11_MUX_BIST_FAIL_MASK          (16383U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR11_HEARTBEAT_EN                (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR11_FAULTH_EN                   (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR11_FAULTHline_FAULT            (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR11_HEARTBEAT_FAULT             (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR12_BIST_BAL_COMP_LS_FAIL_MASK  (127U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR12_BIST_BAL_COMP_HS_FAIL_MASK  (127U << 7)
#define AEK_POW_BMS63EN_BURST_CMD2_FR12_HEARTBEATCYCLE_MASK         (7U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR12_CURR_SENSE_OVC_SLEEP        (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD2_FR13_OPEN_BIST_FAIL_MASK         (16383U << 0)
#define AEK_POW_BMS63EN_BURST_CMD2_FR13_CLK_MON_INIT_DONE           (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD2_FR13_CLK_MON_EN                  (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD2_FR13_OSCFAIL                     (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD2_FR13_SENSE_OVC_NORM              (1U << 17)
/** @} */ 


/**
 * @name    Burst command #3 (0x7B) definitions
 * @{
 */ 
#define AEK_POW_BMS63EN_BURST_CMD3_FR1_COULOMBCNTTIME_MASK      (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR1_COCOUOVF                 (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR1_COULOMBCOUNTER_EN        (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR2_COULOMBCOUNTER_MSB_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR2_SENSE_MINUS_OPEN         (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR2_SENSE_PLUS_OPEN          (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR3_COULOMBCOUNTER_LSB_MASK  (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR3_CURR_SENSE_OVC_NORM      (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR3_CURR_SENSE_OVC_SLEEP     (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR4_CUR_INST_SYNCH_MASK      (262143U << 0)

#define AEK_POW_BMS63EN_BURST_CMD3_FR5_CUR_INST_CALIB_MASK      (262143U << 0)

#define AEK_POW_BMS63EN_BURST_CMD3_FR6_GPIO3_MEAS_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR6_D_RDY_GPIO3              (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR6_GPIO3_OT                 (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR7_GPIO4_MEAS_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR7_D_RDY_GPIO4              (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR7_GPIO4_OT                 (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR8_GPIO5_MEAS_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR8_D_RDY_GPIO5              (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR8_GPIO5_OT                 (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR9_GPIO6_MEAS_MASK          (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR9_D_RDY_GPIO6              (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR9_GPIO6_OT                 (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR10_GPIO7_MEAS_MASK         (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR10_D_RDY_GPIO7             (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR10_GPIO7_OT                (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR11_GPIO8_MEAS_MASK         (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR11_D_RDY_GPIO8             (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR11_GPIO8_OT                (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR12_GPIO9_MEAS_MASK         (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR12_D_RDY_GPIO9             (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR12_GPIO9_OT                (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR13_VTREF_MEAS              (65535U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR13_D_RDY_VTREF             (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR13_TRIMMCCALOK             (1U << 17)

#define AEK_POW_BMS63EN_BURST_CMD3_FR14_TEMPCHIP                (255U << 0)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_OTCHIP                  (1U << 8)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_EOF_BAL                 (1U << 9)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_BAL_ON                  (1U << 10)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO9_UT                (1U << 11)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO8_UT                (1U << 12)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO7_UT                (1U << 13)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO6_UT                (1U << 14)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO5_UT                (1U << 15)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO4_UT                (1U << 16)
#define AEK_POW_BMS63EN_BURST_CMD3_FR14_GPIO3_UT                (1U << 17)
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

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* _AEK_POW_BMS63EN_REG_H_ */

/** @} */
