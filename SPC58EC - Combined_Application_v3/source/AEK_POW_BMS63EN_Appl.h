
#include "components.h"
#include "AEK_POW_BMS63EN_id.h"
#include "pit_lld_cfg.h"
#include "BMS_Controller.h"

typedef enum{
	AEK_POW_BMS63EN_SOC_ELABORATION_BUSY,
	AEK_POW_BMS63EN_SOC_ELABORATION_DONE
}AEK_POW_BMS63EN_soc_elab_sts_t;

typedef struct{
		float AEK_POW_BMS63EN_Pack_CellTemperatureNTC[14];
		float AEK_POW_BMS63EN_Pack_CellVoltage[14];
		float AEK_POW_BMS63EN_Pack_Current;
		uint8_t AEK_POW_BMS63EN_Pack_Enable_Bal;
		float AEK_POW_BMS63EN_Pack_SOC[14];
		float AEK_POW_BMS63EN_Pack_SOH[14];
		uint8_t AEK_POW_BMS63EN_Pack_Bal_cmd[14];
		uint8_t AEK_POW_BMS63EN_Pack_Bal_sts[14];
		uint8_t AEK_POW_BMS63EN_Pack_Bal_en_sts;
		float AEK_POW_BMS63EN_Pack_Vbatt;
		float AEK_POW_BMS63EN_Vref;
		uint8_t AEK_POW_BMS63EN_Cell_Enabled[14];
		uint8_t AEK_POW_BMS63EN_Pack_Enable_Discharge;
		uint32_t AEK_POW_BMS63EN_Fault1_data;
		uint32_t AEK_POW_BMS63EN_Fault2_data;
		uint32_t AEK_POW_BMS63EN_VcellOV_Fault_data;
		uint32_t AEK_POW_BMS63EN_VcellUV_Fault_data;
		uint32_t AEK_POW_BMS63EN_GPIOOTUT_Fault_data;
		uint8_t AEK_POW_BMS63EN_OverLatch;
		AEK_POW_BMS63EN_bal_status_t AEK_POW_BMS63EN_bal_status;
}AEK_POW_BMS63EN_module_t;

void AEK_POW_BMS63EN_init(void);
void AEK_POW_BMS63EN_InitModel(void);

void AEK_POW_BMS63EN_Start_Mgn_exec(void);

void AEK_POW_BMS63EN_Balancing(void);
void AEK_POW_BMS63EN_Model_exec(void);

void AEK_POW_BMS63EN_VA_Measurement(void);
void AEK_POW_BMS63EN_TEMP_Measurement(void);
void AEK_POW_BMS63EN_DIAG_Measurement(void);

AEK_POW_BMS63EN_module_t AEK_POW_BMS63EN_GetModule(uint8_t dev);

AEK_POW_BMS63EN_soc_elab_sts_t AEK_POW_BMS63EN_GetSOC_Elab_Sts(void);
