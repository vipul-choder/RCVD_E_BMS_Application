/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BMS_Controller.h
 *
 * Code generated for Simulink model 'BMS_Controller'.
 *
 * Model version                  : 2.93
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sun Feb  5 21:19:08 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BMS_Controller_h_
#define RTW_HEADER_BMS_Controller_h_
#ifndef BMS_Controller_COMMON_INCLUDES_
#define BMS_Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* BMS_Controller_COMMON_INCLUDES_ */

#include "BMS_Controller_types.h"

/* Includes for objects with custom storage classes */
#include "Cell_Model_parameter.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals and states (default storage) for system '<S1>/BAL_Cell' */
typedef struct {
  boolean_T Merge[14];                 /* '<S2>/Merge' */
  boolean_T Compare[14];               /* '<S12>/Compare' */
} DW_BAL_Cell;

/* Block signals and states (default storage) for system '<S4>/SOC Estimator (Adaptive Kalman Filter)' */
typedef struct {
  real32_T Probe[2];                   /* '<S24>/Probe' */
  real32_T Sum[3];                     /* '<S22>/Sum' */
  real32_T Delay_DSTATE_p[3];          /* '<S23>/Delay' */
  real32_T UnitDelayP_DSTATE[9];       /* '<S21>/Unit Delay - P' */
  real32_T Delay1_DSTATE;              /* '<S14>/Delay1' */
  real32_T Delay_DSTATE;               /* '<S14>/Delay' */
  real32_T Delay2_DSTATE;              /* '<S14>/Delay2' */
  boolean_T icLoad;                    /* '<S14>/Delay1' */
  boolean_T icLoad_e;                  /* '<S14>/Delay' */
  boolean_T icLoad_g;                  /* '<S14>/Delay2' */
  boolean_T icLoad_p;                  /* '<S23>/Delay' */
  boolean_T KalmanFilter_MODE;         /* '<S14>/KalmanFilter' */
} DW_CoreSubsys_fwu;

/* Block signals and states (default storage) for system '<S1>/SOC_Estimation' */
typedef struct {
  DW_CoreSubsys_fwu CoreSubsys[14];
                             /* '<S4>/SOC Estimator (Adaptive Kalman Filter)' */
  real32_T R0Table[14];                /* '<S4>/R0 Table' */
  uint32_T m_bpIndex[28];              /* '<S4>/R0 Table' */
} DW_SOC_Estimation;

/* Block signals and states (default storage) for system '<Root>/BMS_Controller' */
typedef struct {
  DW_SOC_Estimation SOC_Estimation_p;  /* '<S1>/SOC_Estimation' */
  DW_BAL_Cell BAL_Cell_e;              /* '<S1>/BAL_Cell' */
  real32_T ImpAsg_InsertedFor_InitSOC_at_i[14];/* '<S3>/1-D Lookup Table' */
} DW_BMS_Controller;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_BMS_Controller BMS_Controller_pd; /* '<Root>/BMS_Controller' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S22>/Constant2'
   */
  real32_T Constant2_Value[9];

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S24>/Constant'
   */
  real32_T Constant_Value[9];

  /* Computed Parameter: uDLookupTabledOCV_tableData
   * Referenced by: '<S24>/2-D Lookup Table dOCV'
   */
  real32_T uDLookupTabledOCV_tableData[85];

  /* Expression: C1_mat
   * Referenced by: '<S24>/2-D Lookup Table C1'
   */
  real32_T uDLookupTableC1_tableData[85];

  /* Expression: P0
   * Referenced by: '<S21>/Unit Delay - P'
   */
  real32_T UnitDelayP_InitialCondition[9];

  /* Expression: Q
   * Referenced by: '<S25>/Constant'
   */
  real32_T Constant_Value_n[9];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S4>/R0 Table'
   *   '<S26>/2-D Lookup Table R0 EOL'
   *   '<S26>/2-D Lookup Table R0 new'
   *   '<S24>/2-D Lookup Table C1'
   *   '<S24>/2-D Lookup Table OCV'
   *   '<S24>/2-D Lookup Table R1'
   *   '<S24>/2-D Lookup Table dOCV'
   */
  uint32_T pooled5[2];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern uint8_T TH_Bal;                 /* Variable: TH_Bal
                                        * Referenced by: '<S12>/Constant'
                                        */

/* Model entry point functions */
extern void BMS_Controller_initialize(RT_MODEL *const rtM);
extern void BMS_Controller_step(RT_MODEL *const rtM, real32_T
  rtU_CellTemperatureNTC[14], real32_T rtU_CellVoltage[14], real32_T
  rtU_PackCurrent, uint8_T rtU_Enable_Bal, uint8_T rtU_Enable_Discharge, uint8_T
  rtU_Enable_Cell[14], real32_T rtY_SOC[14], real32_T rtY_SOH[14], uint8_T
  rtY_Bal_cmd[14], uint8_T *rtY_Bal_sts);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S14>/Scope' : Unused code path elimination
 * Block '<S14>/Scope1' : Unused code path elimination
 * Block '<S21>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S21>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S21>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S21>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S21>/Rate Transition4' : Eliminated since input and output rates are identical
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('BMS_Controller_model_optimized/BMS_Controller')    - opens subsystem BMS_Controller_model_optimized/BMS_Controller
 * hilite_system('BMS_Controller_model_optimized/BMS_Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BMS_Controller_model_optimized'
 * '<S1>'   : 'BMS_Controller_model_optimized/BMS_Controller'
 * '<S2>'   : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell'
 * '<S3>'   : 'BMS_Controller_model_optimized/BMS_Controller/InitSOC'
 * '<S4>'   : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation'
 * '<S5>'   : 'BMS_Controller_model_optimized/BMS_Controller/SOH_Estimation'
 * '<S6>'   : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Discharge_Enabled'
 * '<S7>'   : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled'
 * '<S8>'   : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/SOCcorrection'
 * '<S9>'   : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled/Passive Cell Balancing'
 * '<S10>'  : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled/SOCcorrection'
 * '<S11>'  : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled/Passive Cell Balancing/Enabled Subsystem'
 * '<S12>'  : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled/Passive Cell Balancing/Enabled Subsystem/Compare To Constant'
 * '<S13>'  : 'BMS_Controller_model_optimized/BMS_Controller/BAL_Cell/Local_Balancing_Enabled/Passive Cell Balancing/Enabled Subsystem/MATLAB Function'
 * '<S14>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)'
 * '<S15>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/Compare To Constant'
 * '<S16>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/Compare To Constant1'
 * '<S17>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/Compare To Zero'
 * '<S18>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/Compare To Zero1'
 * '<S19>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter'
 * '<S20>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter'
 * '<S21>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter/EKF'
 * '<S22>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter/EKF/Correction'
 * '<S23>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter/EKF/Delay - X'
 * '<S24>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter/EKF/Jacobian'
 * '<S25>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOC_Estimation/SOC Estimator (Adaptive Kalman Filter)/KalmanFilter/Kalman Filter/EKF/Prediction'
 * '<S26>'  : 'BMS_Controller_model_optimized/BMS_Controller/SOH_Estimation/SOH Estimator'
 */
#endif                                 /* RTW_HEADER_BMS_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
