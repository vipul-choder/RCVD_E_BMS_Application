
#include "AEK_POW_BMS63EN_Appl.h"

uint8_t buffer[14 * AEK_POW_BMS63EN_N_BMS];

AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_N_BMS];

static RT_MODEL rtMdev1_;
static RT_MODEL *const rtMPtrdev1 = &rtMdev1_; /* Real-time model */
static DW rtDWdev1;

AEK_POW_BMS63EN_soc_elab_sts_t AEK_POW_BMS63EN_soc_elab_sts;

AEK_POW_BMS63EN_soc_elab_sts_t AEK_POW_BMS63EN_GetSOC_Elab_Sts(){
	return AEK_POW_BMS63EN_soc_elab_sts;
}

AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_GetModule(uint8_t dev){
	return AEK_POW_BMS63EN_BatteryModules[dev];
}


void AEK_POW_BMS63EN_Balancing(void){
	uint8_t dev =0;
	uint8_t cell_idx = 0;
	for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_bal_status = AEK_POW_BMS63EN_GetBalancingStatus(AEK_POW_BMS63EN_DEVICE_ID(dev));		//Balancing for N_BMS
		if(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_en_sts){
			if(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_bal_status==AEK_POW_BMS63EN_bal_status_ongoing){
				for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx++){
					if(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_cmd[cell_idx] != AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_sts[cell_idx]){
						AEK_POW_BMS63EN_StopCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev));
						pal_lld_setpad(PORT_F, LED2);
						return;
					}
					else{}
				}
			}
			else{
				for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx++){
					if(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_cmd[cell_idx]){
						AEK_POW_BMS63EN_EnableCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev),cell_idx);
						AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_sts[cell_idx] = 1;
					}
					else{
						AEK_POW_BMS63EN_DisableCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev),cell_idx);
						AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Bal_sts[cell_idx] = 0;
					}
				}
				AEK_POW_BMS63EN_StartCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev));
				pal_lld_clearpad(PORT_F, LED2);
			}
		}
		else{
			if(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_bal_status==AEK_POW_BMS63EN_bal_status_ongoing){
				AEK_POW_BMS63EN_StopCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev));
				pal_lld_setpad(PORT_F, LED2);
				AEK_POW_BMS63EN_DisableCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev),AEK_POW_BMS63EN_CELL_ALL);
			}
			else{}
		}
	}
}



void AEK_POW_BMS63EN_init(void){
	uint8_t dev =0;
	uint8_t cell_idx = 0;

	AEK_POW_BMS63EN_Init();

	for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
		//Enable Model Cells by reading configuration
		for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <= AEK_POW_BMS63EN_CELL14; cell_idx ++){
			if(AEK_POW_BMS63EN_isEnabled(AEK_POW_BMS63EN_DEVICE_ID(dev), cell_idx)){
				AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Cell_Enabled[cell_idx] = 1;
			}
		}
		//Setting Current OverCurrent
		AEK_POW_BMS63EN_SetOvercurrentThreshold(AEK_POW_BMS63EN_DEVICE_ID(dev), 100, 5);
	}

	AEK_POW_BMS63EN_InitModel();
	//START PIT GENERAL
	pit_lld_start(&PITD1, pit0_config);
	//Balancing LED OFF
	pal_lld_setpad(PORT_F, LED2);
	for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
		AEK_POW_BMS63EN_StopCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev));
	}
	AEK_POW_BMS63EN_DisableCellBalancing(AEK_POW_BMS63EN_DEVICE_ID(dev),AEK_POW_BMS63EN_CELL_ALL);
}


void AEK_POW_BMS63EN_InitModel(){
	//INIT MODEL FOR DEV1
	RT_MODEL *const rtMdev1 = rtMPtrdev1;
	rtMdev1->dwork = &rtDWdev1;
	BMS_Controller_initialize(rtMdev1);
}


void AEK_POW_BMS63EN_Start_Mgn_exec(void){
   /* Start PIT1 driver for BMS_MGN*/
   pit_lld_channel_start(&PITD1,PIT0_CHANNEL_CH3);
}



void AEK_POW_BMS63EN_Mgn_exec(){
	pal_lld_togglepad(PORT_F,LED3);
	AEK_POW_BMS63EN_soc_elab_sts = AEK_POW_BMS63EN_SOC_ELABORATION_BUSY;
	AEK_POW_BMS63EN_VA_Measurement();
	AEK_POW_BMS63EN_TEMP_Measurement();
	if(AEK_COM_ISOSPI_GetFault(ISOSPI_DEV0)){
		AEK_POW_BMS63EN_DIAG_Measurement();
	}
	AEK_POW_BMS63EN_Model_exec();
	AEK_POW_BMS63EN_Balancing();
	AEK_POW_BMS63EN_soc_elab_sts = AEK_POW_BMS63EN_SOC_ELABORATION_DONE;
	pal_lld_togglepad(PORT_F,LED3);
}

void AEK_POW_BMS63EN_VA_Measurement(void){
	   uint8_t dev =0;
	   uint8_t cell_idx = 0;
	   for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
			AEK_POW_BMS63EN_StartManualConversion( AEK_POW_BMS63EN_DEVICE_ID(dev),AEK_POW_BMS63EN_GPIO_CONV_EN,AEK_POW_BMS63EN_GPIO_TERM_CONV_DIS,AEK_POW_BMS63EN_CELL_TERM_CONV_DIS,AEK_POW_BMS63EN_BAL_TERM_CONV_DIS,AEK_POW_BMS63EN_HWSC_DIS, AEK_POW_BMS63EN_ADC_CROSS_CHECK_DIS);
			//Acquire VBatt voltage value device
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Vbatt = AEK_POW_BMS63EN_GetBatteryPackVoltMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev));
			//Acquire VCell voltage values device
			for(cell_idx = AEK_POW_BMS63EN_CELL1; cell_idx <=AEK_POW_BMS63EN_CELL14; cell_idx++){
				if(AEK_POW_BMS63EN_isEnabled(AEK_POW_BMS63EN_DEVICE_ID(dev),cell_idx)) {
					AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellVoltage[cell_idx] = AEK_POW_BMS63EN_GetCellVoltMeasurement(AEK_POW_BMS63EN_DEVICE_ID(dev), cell_idx);
				}
			}
			//Acquire Current value device
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_Current = AEK_POW_BMS63EN_GetInstCurrentMeasurement(AEK_POW_BMS63EN_DEVICE_ID(dev), 100);
	   }
}

void AEK_POW_BMS63EN_TEMP_Measurement(void){
	   uint8_t dev =0;
	   for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
		AEK_POW_BMS63EN_StartManualConversion( AEK_POW_BMS63EN_DEVICE_ID(dev),AEK_POW_BMS63EN_GPIO_CONV_EN,AEK_POW_BMS63EN_GPIO_TERM_CONV_DIS,AEK_POW_BMS63EN_CELL_TERM_CONV_DIS,AEK_POW_BMS63EN_BAL_TERM_CONV_DIS,AEK_POW_BMS63EN_HWSC_DIS, AEK_POW_BMS63EN_ADC_CROSS_CHECK_DIS);

		//Acquire Vref voltage device
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref = AEK_POW_BMS63EN_GetVTREFVoltMeasurement(AEK_POW_BMS63EN_DEVICE_ID(dev));
		//Acquire Resistor GPIO device
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL1] = AEK_POW_BMS63EN_GetNTCMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev), AEK_POW_BMS63EN_gpio_3, AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref, AEK_POW_BMS63EN_RATIO_MODE);
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL2] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL1];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL3] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL1];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL4] = AEK_POW_BMS63EN_GetNTCMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev), AEK_POW_BMS63EN_gpio_4, AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref, AEK_POW_BMS63EN_RATIO_MODE);
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL5] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL4];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL6] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL4];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL7] = AEK_POW_BMS63EN_GetNTCMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev), AEK_POW_BMS63EN_gpio_5, AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref, AEK_POW_BMS63EN_RATIO_MODE);
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL8] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL7];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL9] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL7];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL10] = AEK_POW_BMS63EN_GetNTCMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev), AEK_POW_BMS63EN_gpio_6, AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref, AEK_POW_BMS63EN_RATIO_MODE);
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL11] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL10];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL12] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL10];
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL13] = AEK_POW_BMS63EN_GetNTCMeasurement( AEK_POW_BMS63EN_DEVICE_ID(dev), AEK_POW_BMS63EN_gpio_9, AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Vref, AEK_POW_BMS63EN_RATIO_MODE);
		AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL14] = AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC[AEK_POW_BMS63EN_CELL13];
	   }
}






//End of Custom functions

void AEK_POW_BMS63EN_DIAG_Measurement(){
	   uint8_t dev =0;
	   for(dev = AEK_POW_BMS63EN_DEVICE1; dev<=AEK_POW_BMS63EN_N_BMS; dev++){
		   if(AEK_COM_ISOSPI_GetFault(ISOSPI_DEV0)){
			//Acquire Faults device
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Fault1_data = AEK_POW_BMS63EN_GetFaults1(AEK_POW_BMS63EN_DEVICE_ID(dev));
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_Fault2_data = AEK_POW_BMS63EN_GetFaults2(AEK_POW_BMS63EN_DEVICE_ID(dev));
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_VcellOV_Fault_data = AEK_POW_BMS63EN_GetVCELLOVFaults(AEK_POW_BMS63EN_DEVICE_ID(dev));
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_VcellUV_Fault_data = AEK_POW_BMS63EN_GetVCELLUVFaults(AEK_POW_BMS63EN_DEVICE_ID(dev));
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_GPIOOTUT_Fault_data = AEK_POW_BMS63EN_GetGPIOOTUTFaults(AEK_POW_BMS63EN_DEVICE_ID(dev));
			//Acquire OverLatch status device
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(dev)].AEK_POW_BMS63EN_OverLatch = AEK_POW_BMS63EN_Get_Conf_OVL(AEK_POW_BMS63EN_DEVICE_ID(dev));
		   }
	   }
}


void AEK_POW_BMS63EN_Model_exec(void){

	RT_MODEL *const rtMdev1 = rtMPtrdev1;
	rtMdev1->dwork = &rtDWdev1;

	AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Enable_Bal = 1;
	AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Enable_Discharge = 0;

	BMS_Controller_step(rtMdev1,                     							\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_CellTemperatureNTC,\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_CellVoltage, 		\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Current,			\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Enable_Bal,		\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Enable_Discharge,	\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Cell_Enabled,		    \
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_SOC,				\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_SOH,				\
			AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Bal_cmd,			\
			&(AEK_POW_BMS63EN_BatteryModules[AEK_POW_BMS63EN_DEVICE(1)].AEK_POW_BMS63EN_Pack_Bal_en_sts));
}


