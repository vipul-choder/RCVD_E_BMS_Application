/***********************************************************************************
*
* Copyright © 2019 - 2020, 2022 STMicroelectronics - All Rights Reserved
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
 * @file    AEK_POW_BMS63EN_diag.c
 * @brief   AEK_POW_BMS63EN driver code for the diagnostics.
 *
 * @addtogroup AEK_POW_BMS63EN_DIAG
 * @{
 */

#include "AEK_POW_BMS63EN_cfg.h"
#include "AEK_POW_BMS63EN_diag.h"
#include "AEK_POW_BMS63EN_registry.h"


#ifdef AEK_COM_ISOSPI1_ALLOCATED

extern AEK_POW_BMS63EN_Driver AEK_POW_BMS63EN_D;

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/
static AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_burst_read[18];

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/
AEK_POW_BMS63EN_faultl_state_t AEK_POW_BMS63EN_faultl_state[AEK_POW_BMS63EN_N_BMS];
AEK_POW_BMS63EN_gpio_state_t AEK_POW_BMS63EN_gpio_state[AEK_POW_BMS63EN_N_BMS];

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/* * * * * * * * * * * * * * * * * */
/*   I N I T   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * */
/*   G E N E R A L   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * * * * */

/**
 *  Runs the diagnostics over the GPIO's 3 - 9.
**/
void AEK_POW_BMS63EN_EnableGPIOOpenOnDemandDiagnostic(unsigned AEK_POW_BMS63EN_devnum) {
  
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_write;


  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  
  AEK_POW_BMS63EN_write = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_read | AEK_POW_BMS63EN_ADCV_CONV_GPIO_TERM_CONV | AEK_POW_BMS63EN_ADCV_CONV_SOC);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);

}
  

/**
 *    Evaluates the open/normal status of a given stack of cells.
**/
void AEK_POW_BMS63EN_PCBOpenDiagnostic(unsigned AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_vpcbdiff_t vpcbdiff) {

  uint8_t cell_idx;
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read[14], AEK_POW_BMS63EN_write;
  
  /*  1a. Enabling even cells only -> write REG ID 0x1C Data 0x2AAA	-> VCELLS_EN */
  AEK_POW_BMS63EN_write = 0;
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( cell_idx % 2 != 0 ) {
      if( (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_conn != AEK_POW_BMS63EN_CELL_UNCONNECTED ) {
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN << cell_idx);
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_en = AEK_POW_BMS63EN_CELL_ENABLED;
      } /* if( (&(((AEK_POW_BMS63ENp->status->device_status->cell_stack_state) ... */
    } else {  
      (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+(cell_idx))->cell_en = AEK_POW_BMS63EN_CELL_DISABLED;
    } /* if( (cell_idx % 2 == 0) */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /*  2a. Starting the manual conversion -> write REG ID 0xD Data 0x8E00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_SOC);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
  /* 3a.  Waiting for the needed acquisition time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 4a.  Reading the acquisition data for the even cells */
  AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD1, &AEK_POW_BMS63EN_burst_read[0]);
  
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN)   &&
        (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_D_RDY_VCELL1) ) {
      AEK_POW_BMS63EN_read[cell_idx] = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK);
    } else {
      AEK_POW_BMS63EN_read[cell_idx] = 0;
    } /* if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN) ... */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 5a.  Waiting for an interval time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 6a.  Enabling the balancing current on the even cells -> write REG ID 0xE Data 0x02 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR);
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /* 7a.  Waiting for an interval time (100 ms) -> (Delay 100) */
  osalThreadDelayMilliseconds(250);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /* 8a.  Starting the manual conversion -> write REG ID 0xD Data 0x8E00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_SOC);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 9a.  Waiting for the needed acquisition time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  10a. Reading the acquisitions for the even cells */
  AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD1, &AEK_POW_BMS63EN_burst_read[0]);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  11a. Waiting for an interval time (100 ms) -> (Delay 100) */
  osalThreadDelayMilliseconds(100);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 12a. Disabling the balancing current on the even cells -> write REG ID 0xE Data 0x00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  13a. Evaluating the voltage difference on the even cells and comparing with the voltage 
      reference: if grater than, then the cell is OPEN, else it is still connected */ 
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN)   &&
        (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_D_RDY_VCELL1) ) {
      if( (AEK_POW_BMS63EN_read[cell_idx] - ((AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK))) <= vpcbdiff ) {
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_pcb_conn = AEK_POW_BMS63EN_CELL_PCB_CONNECTED;
      } else {
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_pcb_conn = AEK_POW_BMS63EN_CELL_PCB_OPEN;
      } /* if( (AEK_POW_BMS63EN_read[cell_idx] - ((AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK))) <= vpcbdiff ) */
    } /* if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN) ... */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  
  /*  1b. Enabling odd cells only -> VCELLS_EN */
  AEK_POW_BMS63EN_write = 0;
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( cell_idx % 2 == 0 ) {
      if( (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_conn != AEK_POW_BMS63EN_CELL_UNCONNECTED ) {
        AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_VCELLS_EN_VCELL1_EN << cell_idx);
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_en = AEK_POW_BMS63EN_CELL_ENABLED;
      } /* if( (&(((AEK_POW_BMS63ENp->status->device_status->cell_stack_state) ... */
    } else {  
      (&(((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+(cell_idx))->cell_en = AEK_POW_BMS63EN_CELL_DISABLED;
    } /* if( (cell_idx % 2 == 0) */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELLS_EN, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /*  2b. Starting the manual conversion -> write REG ID 0xD Data 0x8E00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_SOC);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
  /* 3b.  Waiting for the needed acquisition time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 4b.  Reading the acquisition data for the even cells */
  AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD1, &AEK_POW_BMS63EN_burst_read[0]);
  
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN)   &&
        (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_D_RDY_VCELL1) ) {
      AEK_POW_BMS63EN_read[cell_idx] = (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK);
    } else { 
      AEK_POW_BMS63EN_read[cell_idx] = 0;
    } /* if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN) ... */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 5b.  Waiting for an interval time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 6b.  Enabling the balancing current on the odd cells -> write REG ID 0xE Data 0x02 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_EVEN_CURR);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /* 7b.  Waiting for an interval time (100 ms) -> (Delay 100) */
  osalThreadDelayMilliseconds(250);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  
  /* 8b.  Starting the manual conversion -> write REG ID 0xD Data 0x8E00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV);
  AEK_POW_BMS63EN_write |= (AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_ADCV_CONV_SOC);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_ADCV_CONV, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 9b.  Waiting for the needed acquisition time (200 ms) -> (Delay 200) */
  osalThreadDelayMilliseconds(200);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  10b. Reading the acquisitions for the even cells */
  AEK_POW_BMS63EN_SPIBurstAccess(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_BURST_CMD1, &AEK_POW_BMS63EN_burst_read[0]);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  11b. Waiting for an interval time (100 ms) -> (Delay 100) */
  osalThreadDelayMilliseconds(100);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /* 12b. Disabling the balancing current on the even cells -> write REG ID 0xE Data 0x00 */
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1);
  AEK_POW_BMS63EN_write &= (AEK_POW_BMS63EN_register_t)(~AEK_POW_BMS63EN_NCYCLE_PROG_1_PCB_OPEN_EN_ODD_CURR);
  AEK_POW_BMS63EN_SPIWriteRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_NCYCLE_PROG_1, AEK_POW_BMS63EN_write);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  13b. Evaluating the voltage difference on the even cells and comparing with the voltage 
      reference: if grater than, then the cell is OPEN, else it is still connected */ 
  for( cell_idx = 0; cell_idx < 14; cell_idx++ ) {
    if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN)   &&
        (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_D_RDY_VCELL1) ) {
      if( (AEK_POW_BMS63EN_read[cell_idx] - ((AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK))) <= vpcbdiff ) {
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_pcb_conn = AEK_POW_BMS63EN_CELL_PCB_CONNECTED;
      } else {
        ((&((AEK_POW_BMS63EN_Drv.status->device_status->cell_stack_state)+(AEK_POW_BMS63EN_devnum-1))->cell_1)+cell_idx)->cell_pcb_conn = AEK_POW_BMS63EN_CELL_PCB_OPEN;
      } /* if( (AEK_POW_BMS63EN_read[cell_idx] - ((AEK_POW_BMS63EN_register_t)(AEK_POW_BMS63EN_burst_read[cell_idx] & AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_MASK))) <= vpcbdiff ) */
    } /* if( (AEK_POW_BMS63EN_burst_read[cell_idx] && AEK_POW_BMS63EN_BURST_CMD1_FR1_VCELL1_EN) ... */
  } /* for( cell_idx = 0; cell_idx < 14; cell_idx++ ) { */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
}
/* * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*   R E G I S T E R   B A S E D   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * */

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetCellOpen(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CELL_OPEN);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_CELL_OPEN);

	return AEK_POW_BMS63EN_read;
}

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetFaults1(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FAULTS1);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FAULTS1);

	return AEK_POW_BMS63EN_read;
}

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetFaults2(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FAULTS2);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_FAULTS2);

	return AEK_POW_BMS63EN_read;
}


AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetVCELLUVFaults( unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_UV);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_UV);

	return AEK_POW_BMS63EN_read;
}

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetVCELLOVFaults(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_OV);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_OV);

	return AEK_POW_BMS63EN_read;
}



AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetGPIOOTUTFaults(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VGPIO_OT_UT);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VGPIO_OT_UT);

	return AEK_POW_BMS63EN_read;
}

AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_GetBALUVFaults(unsigned AEK_POW_BMS63EN_devnum){
	AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read;

	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_BAL_UV);
	AEK_POW_BMS63EN_read = AEK_POW_BMS63EN_SPIReadRegister(&AEK_POW_BMS63EN_Drv, AEK_POW_BMS63EN_devnum, AEK_POW_BMS63EN_VCELL_BAL_UV);

	return AEK_POW_BMS63EN_read;
}




uint8_t AEK_POW_BMS63EN_GetFault1(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_fault1_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

uint8_t AEK_POW_BMS63EN_GetFault2(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_fault2_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

uint8_t AEK_POW_BMS63EN_GetVCELLUVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_uv_fault_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

uint8_t AEK_POW_BMS63EN_GetVCELLOVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_ov_fault_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

uint8_t AEK_POW_BMS63EN_GetGPIOOTUTFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_gpio_ot_ut_fault_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

uint8_t AEK_POW_BMS63EN_GetBALUVFault(AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_read, AEK_POW_BMS63EN_vcell_bal_uv_fault_t fault_case){
	return (AEK_POW_BMS63EN_read & (1<<fault_case))>>fault_case;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
  

/** @} */

#endif