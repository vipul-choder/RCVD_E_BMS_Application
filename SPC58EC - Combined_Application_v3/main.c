/****************************************************************************
 *
 * Copyright © 2022 STMicroelectronics - All Rights Reserved
 *
 * License terms: STMicroelectronics Proprietary in accordance with licensing
 * terms SLA0089 at www.st.com.
 *
 * THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
 * INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * EVALUATION ONLY – NOT FOR USE IN PRODUCTION
 *****************************************************************************/

/* Inclusion of the main header files of all the imported components in the
 order specified in the application wizard. The file is generated
 automatically.*/

#include "components.h"
#include "AEK_POW_BMS63EN_Appl.h"
#include "wkpu_lld_cfg.h"
#include "serial_lld_cfg.h"
#include "can_lld_cfg.h"
#include "pit_lld_cfg.h"

#include <stdio.h>
#include <string.h>
#include <math.h>


volatile uint8_t i_device_disp=0;


void getTemperatureStats(uint16_t temperatures[], uint16_t *minTemp, uint16_t *maxTemp, uint16_t *tempDiff, int size) {
    *minTemp = temperatures[0];
    *maxTemp = temperatures[0];

    // Loop through the array to find the min, max, and calculate the difference
    for (int i = 1; i < size; i++) {
        if (temperatures[i] > *maxTemp) {
            *maxTemp = temperatures[i];
        }
        if (temperatures[i] < *minTemp) {
            *minTemp = temperatures[i];
        }
    }

    *tempDiff = *maxTemp - *minTemp;
}

void send_temp_data(AEK_POW_BMS63EN_module_t *batteryModule, CANTxFrame *txf_temp, CANTxFrame *txf_temp_stat){
	//Individual Temperature Frame

	uint32_t temp1_r = (uint32_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellTemperatureNTC[0]);
	uint32_t temp2_r = (uint32_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellTemperatureNTC[3]);
	uint32_t temp3_r = (uint32_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellTemperatureNTC[6]);
	uint32_t temp4_r = (uint32_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellTemperatureNTC[9]);
	uint32_t temp5_r = (uint32_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellTemperatureNTC[12]);


	float T0 = 298.15; // Reference temperature in Kelvin
	float R0 = 10000.0; // Reference resistance
	uint16_t B = 3984;

	uint16_t temp1 = ((B / ((B / T0) + log(temp1_r / R0))) - 273.15)*10;
	uint16_t temp2 = ((B / ((B / T0) + log(temp2_r / R0))) - 273.15)*10;
	uint16_t temp3 = ((B / ((B / T0) + log(temp3_r / R0))) - 273.15)*10;
	uint16_t temp4 = ((B / ((B / T0) + log(temp4_r / R0))) - 273.15)*10;
	uint16_t temp5 = ((B / ((B / T0) + log(temp5_r / R0))) - 273.15)*10;


	txf_temp->data32[0] = ((temp1 & 0xFFF) << 0)  |  // 12 bits
	                 ((temp2 & 0xFFF) << 12) |  // 12 bits
	                 ((temp3 & 0xFFF) << 24);   // Upper 8 bits of temp3

	txf_temp->data32[1] = ((temp3 & 0xFFF) >> 8)  |  // Lower 4 bits of temp3
	                 ((temp4 & 0xFFF) << 4)  |  // 12 bits
	                 ((temp5 & 0xFFF) << 16);   // 12 bits

	can_lld_transmit(&CAND7, CAN_DEDICATED_TXBUFFER, txf_temp);

	//Statistics Frame

	uint16_t tempvalues[5] = {temp1, temp2, temp3, temp4, temp5};

	uint16_t maxTemp, minTemp, tempDiff;

	getTemperatureStats(tempvalues, &minTemp, &maxTemp, &tempDiff, 5);

	txf_temp_stat->data32[0] = ((maxTemp & 0xFFF) << 0)  |  // 12 bits
		                 ((minTemp & 0xFFF) << 12) |  // 12 bits
		                 ((tempDiff & 0xFFF) << 24);   // Upper 8 bits of temp3

	txf_temp_stat->data32[1] = ((tempDiff & 0xFFF) >> 8);

	can_lld_transmit(&CAND7, CAN_DEDICATED_TXBUFFER, txf_temp_stat);

}

void send_cell_voltages_CAN(AEK_POW_BMS63EN_module_t *batteryModule, CANTxFrame *txf_volt1, CANTxFrame *txf_volt2) {

    // Send 7 cell voltages in the first frame
    uint16_t voltage1 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[0] * 100);
    uint16_t voltage2 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[1] * 100);
    uint16_t voltage3 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[2] * 100);
    uint16_t voltage4 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[3] * 100);
    uint16_t voltage5 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[4] * 100);
    uint16_t voltage6 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[5] * 100);
    uint16_t voltage7 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[6] * 100);


    //Send remaining 7 cell voltages in the second frame
    uint16_t voltage8 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[7] * 100);
    uint16_t voltage9 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[8] * 100);
    uint16_t voltage10 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[9] * 100);
    uint16_t voltage11 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[10] * 100);
    uint16_t voltage12 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[11] * 100);
    uint16_t voltage13 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[12] * 100);
    uint16_t voltage14 = (uint16_t)(batteryModule->AEK_POW_BMS63EN_Pack_CellVoltage[13] * 100);


    txf_volt1->data32[0] =  ((voltage1 & 0x1FF) << 0)  |   // 9 bits
             ((voltage2 & 0x1FF) << 9)  |   // 9 bits
             ((voltage3 & 0x1FF) << 18) |   // 9 bits
             ((voltage4 & 0x1FF) << 27);


    txf_volt1->data32[1] =  ((voltage4 >> 5) & 0x1F)  |    // Remaining 4 bits of voltage[3]
            ((voltage5 & 0x1FF) << 4)  |   // 9 bits
            ((voltage6 & 0x1FF) << 13) |   // 9 bits
            ((voltage7 & 0x1FF) << 22);

    txf_volt2->data32[0] =  ((voltage8 & 0x1FF) << 0)  |   // 9 bits
                 ((voltage9 & 0x1FF) << 9)  |   // 9 bits
                 ((voltage10 & 0x1FF) << 18) |   // 9 bits
                 ((voltage11 & 0x1FF) << 27);


    txf_volt2->data32[1] =  ((voltage11 >> 5) & 0x1F)  |    // Remaining 4 bits of voltage[3]
                ((voltage12 & 0x1FF) << 4)  |   // 9 bits
                ((voltage13 & 0x1FF) << 13) |   // 9 bits
                ((voltage14 & 0x1FF) << 22);

    can_lld_transmit(&CAND7, CAN_DEDICATED_TXBUFFER, txf_volt1);
    can_lld_transmit(&CAND7, CAN_DEDICATED_TXBUFFER, txf_volt2);
}


//Adding custom functions for CAN Transmission of Voltage & Temperature
void AEK_POW_BMS63EN_CAN_Voltage_Transmission(){

	  AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModule;
	  AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModule_2;


	  CANTxFrame txf_bm1_volt_1, txf_bm1_volt_2, txf_bm2_volt_1, txf_bm2_volt_2;

	  txf_bm1_volt_1.TYPE = CAN_ID_STD;   // Standard CAN frame
	  txf_bm1_volt_1.ID = 0x602U;          // CAN ID
	  txf_bm1_volt_1.DLC = 8U;            // Data Length (8 bytes per frame)

	  txf_bm1_volt_2.TYPE = CAN_ID_STD;   // Standard CAN frame
	  txf_bm1_volt_2.ID = 0x603U;          // CAN ID
	  txf_bm1_volt_2.DLC = 8U;            // Data Length (8 bytes per frame)

	  txf_bm2_volt_1.TYPE = CAN_ID_STD;   // Standard CAN frame
	  txf_bm2_volt_1.ID = 0x612U;          // CAN ID
	  txf_bm2_volt_1.DLC = 8U;            // Data Length (8 bytes per frame)

	  txf_bm2_volt_2.TYPE = CAN_ID_STD;   // Standard CAN frame
	  txf_bm2_volt_2.ID = 0x613U;          // CAN ID
	  txf_bm2_volt_2.DLC = 8U;            // Data Length (8 bytes per frame)


	  AEK_POW_BMS63EN_BatteryModule = AEK_POW_BMS63EN_GetModule(0);
	  AEK_POW_BMS63EN_BatteryModule_2 = AEK_POW_BMS63EN_GetModule(1);

	  send_cell_voltages_CAN(&AEK_POW_BMS63EN_BatteryModule, &txf_bm1_volt_1, &txf_bm1_volt_2);

	  send_cell_voltages_CAN(&AEK_POW_BMS63EN_BatteryModule_2, &txf_bm2_volt_1, &txf_bm2_volt_2);

	// Write the message to the SD card
	//sd_lld_write(&SD5, (uint8_t *)message_serial, (uint16_t)(strlen(message_serial)));
}


void AEK_POW_BMS63EN_CAN_Temp_Transmission(){
	//pal_lld_togglepad(PORT_F, LED2);

	AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModule;

	CANTxFrame txf_temp, txf_temp_stat;

	AEK_POW_BMS63EN_BatteryModule = AEK_POW_BMS63EN_GetModule(0);

	txf_temp.TYPE = CAN_ID_STD;   // Standard CAN frame
	txf_temp.ID = 0x604;          // CAN ID for Temperature Message
	txf_temp.DLC = 8U;

	txf_temp_stat.TYPE = CAN_ID_STD;   // Standard CAN frame
	txf_temp_stat.ID = 0x605;          // CAN ID for Temperature Message
	txf_temp_stat.DLC = 8U;

	send_temp_data(&AEK_POW_BMS63EN_BatteryModule, &txf_temp,&txf_temp_stat);

}



void main_core0(void) {
  //char message[11];
  //AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModule;
  //AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModule_2;

  //uint8_t cell_idx = 0;
  /* Enable Interrupts */
  //irqIsrEnable();


  /* Application main loop.*/
  for ( ; ; ) {
	  /*
	  if((osalThreadGetMilliseconds()%500)==0){
		    AEK_POW_BMS63EN_BatteryModule = AEK_POW_BMS63EN_GetModule(i_device_disp);


			sprintf(message, "DEV:%d     \n", (int)(i_device_disp+1));
			sd_lld_write(&SD5, (uint8_t *)message, (uint16_t)(sizeof(message)/sizeof(message[0])));

			//Printing Voltages for Module 1
			for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx ++){
					sprintf(message, "V%.2d:%.3f  ", cell_idx+1, AEK_POW_BMS63EN_BatteryModule.AEK_POW_BMS63EN_Pack_CellVoltage[cell_idx]);
					sd_lld_write(&SD5, (uint8_t *)message, (uint16_t)(sizeof(message)/sizeof(message[0])));
			}
			sprintf(message,"          \n");


			AEK_POW_BMS63EN_BatteryModule_2 = AEK_POW_BMS63EN_GetModule(i_device_disp+1);


			sprintf(message, "DEV:%d     \n", (int)(i_device_disp+2));
			sd_lld_write(&SD5, (uint8_t *)message, (uint16_t)(sizeof(message)/sizeof(message[0])));

			//Printing Voltages for Module 2
			for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx ++){
					sprintf(message, "V%.2d:%.3f  ", cell_idx+1, AEK_POW_BMS63EN_BatteryModule_2.AEK_POW_BMS63EN_Pack_CellVoltage[cell_idx]);
					sd_lld_write(&SD5, (uint8_t *)message, (uint16_t)(sizeof(message)/sizeof(message[0])));
			}
			sprintf(message,"          \n");

		}
	*/
  }

}


void *sbrk(size_t incr)
{
	extern uint8_t __heap_base__;
	extern uint8_t __heap_end__;
	static uint8_t *p=&__heap_base__;
	static uint8_t *newp;

	newp = p+ incr;
	if(newp> &__heap_end__)
	{
		return (void*)-1;
	}
	return p =newp;
}


void int28_irq_cb(WKPUDriver *wkpup)
{
	(void)wkpup;
	i_device_disp = i_device_disp+1;
	if (i_device_disp==AEK_POW_BMS63EN_N_BMS) i_device_disp=0;

}


int main(void) {

	componentsInit();
	irqIsrEnable();
	wkpu_lld_start(&WKPUD1, &wkpu_config_wkpu_cfg);

	AEK_POW_BMS63EN_init();
	//runCore0();
	AEK_POW_BMS63EN_Start_Mgn_exec();

	sd_lld_start(&SD5,&serial_config_BMS_serial);

	can_lld_start(&CAND7, &can_config_mcanconf);

	pit_lld_channel_start(&PITD1,PIT0_CHANNEL_CH4);

	pit_lld_channel_start(&PITD1,PIT0_CHANNEL_CH5);

	while (1) {
	}

}




