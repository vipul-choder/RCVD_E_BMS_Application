/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BMS_Controller_data.c
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

#include "BMS_Controller.h"

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S22>/Constant2'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S24>/Constant'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: uDLookupTabledOCV_tableData
   * Referenced by: '<S24>/2-D Lookup Table dOCV'
   */
  { 0.0F, 0.300004572F, 0.393335044F, 0.540828645F, 0.94625175F, 1.70291221F,
    1.05737698F, 0.800123274F, 0.619750082F, 0.89662528F, 0.971000552F,
    0.905875921F, 1.11362433F, 0.699584365F, 0.356657922F, 0.340001106F,
    0.636259079F, 0.0F, 0.42155695F, 0.585834205F, 0.98083F, 2.59625173F,
    1.96874881F, 1.06324923F, 0.796375334F, 0.594000876F, 0.903749228F,
    1.00737607F, 0.957374334F, 1.02224803F, 0.58209157F, 0.31625396F,
    0.382074088F, 0.815009236F, 0.0F, 0.731895745F, 1.20375156F, 2.82666636F,
    2.40874338F, 1.55083299F, 1.02612507F, 0.834126532F, 0.577874243F,
    0.897624254F, 1.10637701F, 0.862123787F, 1.01462579F, 0.589577913F,
    0.321674019F, 0.373745322F, 0.817504644F, 0.0F, 1.74285626F, 2.80428743F,
    2.68952012F, 2.20666766F, 1.42761827F, 1.00614321F, 0.861570895F,
    0.577571452F, 0.898999929F, 1.15057266F, 0.799569905F, 1.00557303F,
    0.598097444F, 0.31142202F, 0.388098121F, 0.810002446F, 0.0F, 3.22284389F,
    2.77500153F, 2.52958107F, 1.96083426F, 1.4237479F, 0.980250895F, 0.876875F,
    0.592124522F, 0.874249756F, 1.1446265F, 0.787999451F, 1.00424743F,
    0.634591401F, 0.332498193F, 0.407092154F, 0.823735356F },

  /* Expression: C1_mat
   * Referenced by: '<S24>/2-D Lookup Table C1'
   */
  { 1980.78967F, 1903.82727F, 1816.31287F, 1698.24829F, 1490.07227F, 4002.37769F,
    14050.1211F, 16437.8965F, 21215.5488F, 24079.875F, 27102.5254F, 26302.5156F,
    25008.5176F, 22306.0156F, 22091.752F, 20395.4844F, 16272.7725F, 1620.37817F,
    1513.24524F, 1406.22168F, 1265.64526F, 4560.05469F, 11778.4746F, 20300.4609F,
    19615.168F, 26614.0645F, 31565.9727F, 30357.5957F, 27032.6602F, 32166.5586F,
    32637.0312F, 34846.4023F, 35838.4805F, 30808.2832F, 1837.53699F, 1669.13269F,
    1943.70312F, 7085.66211F, 15244.3564F, 23934.7852F, 33122.3398F, 26464.1133F,
    38822.5156F, 49907.8945F, 39750.2969F, 37705.3164F, 48720.9844F, 51196.0898F,
    60182.2383F, 68542.6797F, 64176.5273F, 2375.98413F, 4374.06F, 12133.7627F,
    23504.3926F, 31379.0371F, 39909.2656F, 51787.7656F, 35667.1719F, 57407.0469F,
    72767.8438F, 51089.6797F, 53360.6289F, 71605.1484F, 77621.3281F, 99366.1719F,
    121490.516F, 120075.969F, 18953.4609F, 42037.0859F, 72095.8125F, 96286.3906F,
    109236.391F, 130481.039F, 169143.0F, 112983.203F, 174621.312F, 231788.141F,
    130606.258F, 167063.281F, 232177.391F, 263222.25F, 353183.25F, 462030.406F,
    464094.406F },

  /* Expression: P0
   * Referenced by: '<S21>/Unit Delay - P'
   */
  { 1.0E-5F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0E-5F },

  /* Expression: Q
   * Referenced by: '<S25>/Constant'
   */
  { 1.0E-6F, 0.0F, 0.0F, 0.0F, 1.0E-6F, 0.0F, 0.0F, 0.0F, 1.0E-6F },

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
  { 16U, 4U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
