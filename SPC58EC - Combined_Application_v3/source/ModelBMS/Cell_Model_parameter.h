/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Cell_Model_parameter.h
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

#ifndef RTW_HEADER_Cell_Model_parameter_h_
#define RTW_HEADER_Cell_Model_parameter_h_
#include "rtwtypes.h"
#include "BMS_Controller_types.h"

/* Exported data declaration */

/* Declaration for custom storage class: ExportToFile */
extern real32_T Cap_Nom;               /* Referenced by: '<S24>/Gain1' */
extern real32_T KELVIN_CON;            /* Referenced by: '<S1>/ToKelvin' */
extern real32_T NTC_Temp_Vector[33];   /* Referenced by: '<S1>/NTC_LKT' */
extern real32_T NTC_Vector[33];        /* Referenced by: '<S1>/NTC_LKT' */
extern real32_T OCV_Vector[85];        /* Referenced by:
                                        * '<S3>/Constant1'
                                        * '<S24>/2-D Lookup Table OCV'
                                        */
extern real32_T R0_EOL_Vector[85];
                            /* Referenced by: '<S26>/2-D Lookup Table R0 EOL' */
extern real32_T R0_Vector[85];         /* Referenced by:
                                        * '<S4>/R0 Table'
                                        * '<S26>/2-D Lookup Table R0 new'
                                        */
extern real32_T R1_Vector[85];  /* Referenced by: '<S24>/2-D Lookup Table R1' */
extern real32_T SOC_MAX;               /* Referenced by:
                                        * '<S10>/SOC_MAX'
                                        * '<S16>/Constant'
                                        * '<S11>/SOC_MAX'
                                        */
extern real32_T SOC_MIN;               /* Referenced by: '<S15>/Constant' */
extern real32_T SOC_Vector[17];        /* Referenced by:
                                        * '<S3>/1-D Lookup Table'
                                        * '<S4>/R0 Table'
                                        * '<S26>/2-D Lookup Table R0 EOL'
                                        * '<S26>/2-D Lookup Table R0 new'
                                        * '<S24>/2-D Lookup Table C1'
                                        * '<S24>/2-D Lookup Table OCV'
                                        * '<S24>/2-D Lookup Table R1'
                                        * '<S24>/2-D Lookup Table dOCV'
                                        */
extern real32_T SOH_MAX;               /* Referenced by: '<S26>/Saturation' */
extern real32_T SOH_MIN;               /* Referenced by: '<S26>/Saturation' */
extern real32_T Temperature_Vector[5]; /* Referenced by:
                                        * '<S3>/Prelookup'
                                        * '<S4>/R0 Table'
                                        * '<S26>/2-D Lookup Table R0 EOL'
                                        * '<S26>/2-D Lookup Table R0 new'
                                        * '<S24>/2-D Lookup Table C1'
                                        * '<S24>/2-D Lookup Table OCV'
                                        * '<S24>/2-D Lookup Table R1'
                                        * '<S24>/2-D Lookup Table dOCV'
                                        */

#endif                                 /* RTW_HEADER_Cell_Model_parameter_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
