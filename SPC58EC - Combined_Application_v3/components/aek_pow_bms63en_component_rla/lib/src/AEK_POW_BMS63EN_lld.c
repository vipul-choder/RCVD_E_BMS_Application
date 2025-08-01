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
 * @file    AEK_POW_BMS63EN_lld.c
 * @brief   AEK_POW_BMS63EN Driver code.
 *
 * @addtogroup AEK_POW_BMS63EN_LLD
 * @{
 */

#include "AEK_POW_BMS63EN_cfg.h"
#include "AEK_POW_BMS63EN_lld.h"
#include "AEK_POW_BMS63EN_registry.h"
#include "spi_lld.h"

#ifdef AEK_COM_ISOSPI1_ALLOCATED

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/**

 * @details If set to @p TRUE the support for the AEK_POW_BMS63EN RLA is included.
 */

#define osalSysLock osalEnterCritical
#define osalSysUnlock osalExitCritical

#define spiStart spi_lld_start
#define spiStop spi_lld_stop
#define spiSelect spi_lld_select
#define spiUnselect spi_lld_unselect
#define spiSend spi_lld_send
#define spiExchange spi_lld_exchange 
#define spiReceive spi_lld_receive 


/* * * * * * * * * */
/** @} */

/* Device SPI frame definitions */
/* 
 * @name    Device SPI frame definitions.
 * @{
 */
#define AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH 5 /*  device spi length
                                        in terms of #bytes */                                             

#define AEK_POW_BMS63EN_CRC_POLY_GEN              0x2C
#define AEK_POW_BMS63EN_CRC_SEED                  0x70
#define AEK_POW_BMS63EN_CRC_POLY_MASK             0xFF
#define AEK_POW_BMS63EN_CRC_LENGTH                6
#define AEK_POW_BMS63EN_SPI_ERROR                 (1U << 7)
#define AEK_POW_BMS63EN_SPI_FCNT_MASK             (1U << 1) // (1U << 25)
#define AEK_POW_BMS63EN_SPI_FRAME_PA              (1U << 7)
#define AEK_POW_BMS63EN_SPI_FRAME_RW              (1U << 6)
#define AEK_POW_BMS63EN_SPI_FRAME_GSW_MASK        (3U << 24)
#define AEK_POW_BMS63EN_SPI_FRAME_GSW_INT_FAILURE (1U << 25)
#define AEK_POW_BMS63EN_REGISTER_MASK             0x3FFFF
#define AEK_POW_BMS63EN_BURST_CMD_MASK            0x7F
#define AEK_POW_BMS63EN_WRITE_DATA_SH1            17
#define AEK_POW_BMS63EN_WRITE_DATA_SH2            10
#define AEK_POW_BMS63EN_WRITE_DATA_SH3            2
#define AEK_POW_BMS63EN_WRITE_DATA_SH4            6
/** @} */

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/
typedef enum { spi_burst_read, spi_single_read, spi_write } AEK_POW_BMS63EN_spi_rw_t;

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/


/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/



#ifdef DUAL_ACCESS_RING
	#define ISOL 0
	#define ISOH 1
	uint8_t dual_ring_tx = ISOL;
	void AEK_POW_BMS63EN_DualRingTX_reverse(void){
		if(dual_ring_tx == ISOL) dual_ring_tx = ISOH;
		else dual_ring_tx = ISOL;
	}
#endif

/**
 * @brief   Sets up the input spi word(s) to write and/or read a register.
 *
 * @param[in] spiWord         array write/read spi words
 * @param[in] devnum          selected device in a daisy chain
 * @param[in] regnum          register number to access
 * @param[in] value           word to write
 * @param[in] read_write      single or burst reading or writing command
 * @return                    void
 *
 * @notapi
 */
static void AEK_POW_BMS63EN_SetUpSPIData(uint8_t *spiWord,
                              unsigned devnum,
                              unsigned regnum,
                              AEK_POW_BMS63EN_register_t value,
                              AEK_POW_BMS63EN_spi_rw_t read_write)
{
  uint8_t crc_index, seed_byte;
  uint32_t crc_xored, crc_word, curr_poly, div_mask;
  int i = 0;
  for(i=0;i<5;i++) spiWord[i] = 0;
  /* 
  building words for the device taking into account the FCNT bit
  */
  spiWord[0] = (uint8_t)(AEK_POW_BMS63EN_SPI_FRAME_PA | (devnum << 1) | (regnum >> 6));
  spiWord[1] = (uint8_t)(regnum << 2);
 
  /* setting up the device word */
  switch( read_write ) {
    /*** TODO: spi_burst_read and spi_single_read have the same case ***/ 
    case spi_burst_read : //case spi_single_read :
      spiWord[2] = 0;
      spiWord[3] = 0;
      spiWord[4] = 0;
      break;
    
    case spi_single_read :
      spiWord[0] &= 0xBF;
      spiWord[2] = 0;
      spiWord[3] = 0;
      spiWord[4] = 0;
      break;
        
    case spi_write :
      spiWord[0] |= (uint8_t)(AEK_POW_BMS63EN_SPI_FRAME_RW);
      spiWord[2] = (uint8_t)((value & 0x3FC00) >> AEK_POW_BMS63EN_WRITE_DATA_SH2);
      spiWord[3] = (uint8_t)((value & 0x3FF) >> AEK_POW_BMS63EN_WRITE_DATA_SH3);
      spiWord[4] = (uint8_t)((value & 0x3) << AEK_POW_BMS63EN_WRITE_DATA_SH4);
      break;
      
    default: /***/
      break;
  } /* switch( read_write ) */
    
  /* evaluating the crc bits */
  seed_byte = (uint8_t)(spiWord[0] ^ (AEK_POW_BMS63EN_CRC_SEED << 1));  /* seed XOR-ed byte */
  crc_word = (uint32_t)((seed_byte << 24) | (spiWord[1] << 16) | (spiWord[2] << 8) | spiWord[3]);

#if !defined(_AEK_POW_BMS63EN_CRC_DISABLED_)

  /* CRC calculated over bits 39 -> 16 */
  for ( crc_index = 31; crc_index >= 24; crc_index-- ) {
    if( crc_word & (1 << crc_index) ) {
      curr_poly = (uint32_t)(((AEK_POW_BMS63EN_CRC_POLY_GEN << 1) | 0x1) << (crc_index - AEK_POW_BMS63EN_CRC_LENGTH));
      div_mask = (uint32_t)(AEK_POW_BMS63EN_CRC_POLY_MASK << (crc_index - AEK_POW_BMS63EN_CRC_LENGTH));
      crc_xored = (uint32_t)((crc_word & div_mask) ^ curr_poly);
      crc_word = (uint32_t)((crc_word & (~div_mask)) | crc_xored);
    } /* if( crc_word & (1 << (crc_index - AEK_POW_BMS63EN_CRC_LENGHT - 1)) */
  } /* for ( crc_index = 31; crc_index >= AEK_POW_BMS63EN_CRC_LENGTH; crc_index-- ) */
    
  crc_word = (uint32_t)((crc_word << 8) | spiWord[4]);
  
  /* CRC calculated over bits 15 -> 0 */
  for ( crc_index = 31; crc_index >= AEK_POW_BMS63EN_CRC_LENGTH; crc_index-- ) {
    if( crc_word & (1 << crc_index) ) {
      curr_poly = (uint32_t)(((AEK_POW_BMS63EN_CRC_POLY_GEN << 1) | 0x1) << (crc_index - AEK_POW_BMS63EN_CRC_LENGTH));
      div_mask = (uint32_t)(AEK_POW_BMS63EN_CRC_POLY_MASK << (crc_index - AEK_POW_BMS63EN_CRC_LENGTH));
      crc_xored = (uint32_t)((crc_word & div_mask) ^ curr_poly);
      crc_word = (uint32_t)((crc_word & (~div_mask)) | crc_xored);
    } /* if( crc_word & (1 << (crc_index - AEK_POW_BMS63EN_CRC_LENGHT - 1)) */
  } /* for ( crc_index = 15; crc_index >= AEK_POW_BMS63EN_CRC_LENGTH; crc_index-- ) */
  
#endif /* if !defined(_AEK_POW_BMS63EN_CRC_DISABLED_) */

  spiWord[4] |= (uint8_t)(crc_word);

}



/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/* * * * * * * * * * * * * * * * * */
/*   I N I T   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * * */

/*
 *  Initializes the standard part of a AEK_POW_BMS63EN_Driver structure.
**/
void AEK_POW_BMS63EN_ObjectInit(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp) {
  uint8_t dev_idx;

  for( dev_idx = 0; dev_idx < AEK_POW_BMS63EN_N_BMS; dev_idx++ ) {
    AEK_POW_BMS63ENp->status->device_status[dev_idx].device_state = AEK_POW_BMS63EN_RESET;
  }
  AEK_POW_BMS63ENp->config = NULL;
}


/*
 *  Configures and activates the AEK_POW_BMS63EN device.
**/
void AEK_POW_BMS63EN_Start(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, AEK_POW_BMS63EN_Config *config) {
  uint8_t dev_idx;
  osalSysLock();
  AEK_POW_BMS63ENp->config = config;
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_STARTING;
  osalSysUnlock();
  if( config->spip != NULL && config->spicfgp != NULL )
	  spiStart(config->spip, config->spicfgp);
#ifdef DUAL_ACCESS_RING
  if( config->spip_dual != NULL && config->spicfgp_dual != NULL )
      spiStart(config->spip_dual, config->spicfgp_dual);
#endif
  osalSysLock();
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_READY;
  for( dev_idx = 0; dev_idx < AEK_POW_BMS63EN_N_BMS; dev_idx++ ) {
    AEK_POW_BMS63ENp->status->device_status[dev_idx].device_state = AEK_POW_BMS63EN_SLEEP;
  }
  osalSysUnlock();
}


/**
 *  Deactivates the AEK_POW_BMS63EN peripheral.
**/
void AEK_POW_BMS63EN_Stop(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp) {
  
  uint8_t dev_idx;
  osalSysLock();

  if (AEK_POW_BMS63ENp->status->driver_state != AEK_POW_BMS63EN_STOP) {
    AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_STOPPING;
    osalSysUnlock();

  /* Stopping the associated interface driver.*/
    /* SPI stop */
    if(AEK_POW_BMS63ENp->config->spip != NULL )
      spiStop(AEK_POW_BMS63ENp->config->spip);
    /* * * * * * */ 
#ifdef DUAL_ACCESS_RING
	   spiStop(AEK_POW_BMS63ENp->config->spip_dual);
#endif
    osalSysLock();
    AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_STOP;
    for( dev_idx = 0; dev_idx < AEK_POW_BMS63EN_N_BMS; dev_idx++ ) {
      AEK_POW_BMS63ENp->status->device_status[dev_idx].device_state =  AEK_POW_BMS63EN_SLEEP;
    } 
  }
  osalSysUnlock();
  
}
/* * * * * * * * * * * * * * * * * */



/* * * * * * * * * * * * * * * * */
/*   S P I   F U N C T I O N S   */
/* * * * * * * * * * * * * * * * */
/**
 * Send a 'write' command to all the device units.
**/
void AEK_POW_BMS63EN_SPIBroadcastAccess(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned regnum, AEK_POW_BMS63EN_register_t value) {
  AEK_POW_BMS63EN_SPIWriteRegister(AEK_POW_BMS63ENp, AEK_POW_BMS63EN_DEVICE_ID_ALL, regnum, value);
  osalSysLock();
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_READY;
  osalSysUnlock();
} 

  
/*
 * Reads a list of registers in a burst from a device.
**/
void AEK_POW_BMS63EN_SPIBurstAccess(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned command, AEK_POW_BMS63EN_register_t *reg_values) {

  uint8_t burst_idx, n_burst, spiWriteData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH], spiReadData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH];
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  /*  1. Setting up the AEK_POW_BMS63EN input data */
  AEK_POW_BMS63EN_SetUpSPIData( &spiWriteData[0], devnum, command, (AEK_POW_BMS63EN_register_t)0x0, spi_burst_read );
  /* * * * * * * * * * * * * * * * */

  /*  2. Sending input data to the AEK_POW_BMS63EN and reading back from the device */
  AEK_POW_BMS63EN_SPIQueuedAccess(AEK_POW_BMS63ENp, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  switch( command ) {
    case AEK_POW_BMS63EN_BURST_CMD1 : n_burst = 18; break;
    case AEK_POW_BMS63EN_BURST_CMD2 : n_burst = 13; break;
    case AEK_POW_BMS63EN_BURST_CMD3 : n_burst = 14; break;
    default : n_burst = 0; break;  
  } /* switch( command ) */
  

  for( burst_idx = 0; burst_idx < n_burst; burst_idx++ ) {

#ifndef DUAL_ACCESS_RING
    spiReceive(AEK_POW_BMS63ENp->config->spip, (size_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiReadData[0]);
#else
    if(dual_ring_tx == ISOL){
    	spiReceive(AEK_POW_BMS63ENp->config->spip, (size_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiReadData[0]);
    }
    else if(dual_ring_tx == ISOH){
    	spiReceive(AEK_POW_BMS63ENp->config->spip_dual, (size_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiReadData[0]);
    }
    else{}
#endif

    AEK_POW_BMS63EN_reg = (AEK_POW_BMS63EN_register_t)((spiReadData[4])       |
                                   (spiReadData[3] << 8)  |
                                   (spiReadData[2] << 16) |
                                   (spiReadData[1] << 24) );

    if( ((burst_idx == 0) && (((((uint16_t)(spiReadData[0] << 8 | spiReadData[1])) >> 2) & AEK_POW_BMS63EN_BURST_CMD_MASK) == command)) ||
        ((burst_idx + 1) == ((spiReadData[1] >> 2) & 0x1F)) ) {

      reg_values[burst_idx] = (AEK_POW_BMS63EN_register_t)((AEK_POW_BMS63EN_reg >> AEK_POW_BMS63EN_CRC_LENGTH) & AEK_POW_BMS63EN_REGISTER_MASK);
    } /* if( (burst_idx == 0) && (spiReadData[1] >> 3) */

  } /* for( burst_idx = 0; burst_idx < n_burst; burst_idx++ ) */
  
  /* * * * * * * * * * * * * * * * * * * * * * * * */

}  

  
/*
 *  Writes a queue.
**/
void AEK_POW_BMS63EN_SPIQueuedAccess(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, uint8_t n_bytes, const uint8_t *txqueue, uint8_t *rxqueue) {

  uint8_t buf_index, queue_index, spiReadData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH], spiWriteData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH];
  uint32_t AEK_POW_BMS63EN_spi_words;

  AEK_POW_BMS63EN_spi_words = (uint32_t)(n_bytes/((uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH));

  for( queue_index = 0; queue_index < AEK_POW_BMS63EN_spi_words; queue_index = queue_index + ((uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH) ) {
    
    for( buf_index = 0; buf_index < (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH; buf_index++ ) {
      spiWriteData[buf_index] = txqueue[queue_index+buf_index];
    } /* for( buf_index = 0; buf_index < (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH; buf_index++ ... */

#ifndef DUAL_ACCESS_RING
    spiExchange(AEK_POW_BMS63ENp->config->spip, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
#else
    if(dual_ring_tx == ISOL){
       spiExchange(AEK_POW_BMS63ENp->config->spip, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
     }
    else if(dual_ring_tx == ISOH){
       spiExchange(AEK_POW_BMS63ENp->config->spip_dual, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
    }
    else{}
#endif

    for( buf_index = 0; buf_index < (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH; buf_index++ ) {
      rxqueue[queue_index+buf_index] = spiReadData[buf_index];
    }
  
  }
  
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_READY;
};


/*
 *  Writes a register.
**/
void AEK_POW_BMS63EN_SPIWriteRegister(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned regnum,
                           AEK_POW_BMS63EN_register_t value) {
  uint8_t spiWriteData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH], spiReadData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH];
  
  /*  1. Setting up the AEK_POW_BMS63EN input data */
  AEK_POW_BMS63EN_SetUpSPIData( &spiWriteData[0], devnum, regnum, (AEK_POW_BMS63EN_register_t)value, spi_write );
  /* * * * * * * * * * * * * * * * */
  
  /*  2. Sending input data to the AEK_POW_BMS63EN and reading back from the device */
  AEK_POW_BMS63EN_SPIQueuedAccess(AEK_POW_BMS63ENp, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*  3. Checking the correctness of the read data */
  
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_READY;
 
}


/*
 *  Reads a register.
**/
AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_SPIReadRegister(AEK_POW_BMS63EN_Driver *AEK_POW_BMS63ENp, unsigned devnum, unsigned regnum) {

  uint8_t spiWriteData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH], spiReadData[AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH];
  AEK_POW_BMS63EN_register_t AEK_POW_BMS63EN_reg;

  /*  1. Setting up the AEK_POW_BMS63EN input data */
  AEK_POW_BMS63EN_SetUpSPIData( &spiWriteData[0], devnum, regnum, (AEK_POW_BMS63EN_register_t)0x0, spi_single_read );
  /* * * * * * * * * * * * * * * * */
  
  /*  2. Sending input data to the AEK_POW_BMS63EN and reading back from the device */
  AEK_POW_BMS63EN_SPIQueuedAccess(AEK_POW_BMS63ENp, (uint8_t)AEK_POW_BMS63EN_SPI_TRANSFER_LENGTH, &spiWriteData[0], &spiReadData[0]);
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  AEK_POW_BMS63EN_reg = (AEK_POW_BMS63EN_register_t)(spiReadData[4]         |
                                 (spiReadData[3] << 8)  |
                                 (spiReadData[2] << 16) |
                                 (spiReadData[1] << 24) 
                                 );
  
  AEK_POW_BMS63ENp->status->driver_state = AEK_POW_BMS63EN_READY;
  
  return (AEK_POW_BMS63EN_register_t)((AEK_POW_BMS63EN_reg >> AEK_POW_BMS63EN_CRC_LENGTH) & AEK_POW_BMS63EN_REGISTER_MASK);
  
}







/** @} */

#endif