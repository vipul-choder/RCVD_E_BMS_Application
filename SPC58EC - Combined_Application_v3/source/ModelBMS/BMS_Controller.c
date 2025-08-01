/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BMS_Controller.c
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
#include "rtwtypes.h"
#include <math.h>
#include "Cell_Model_parameter.h"

/* Exported block parameters */
uint8_T TH_Bal = 3U;                   /* Variable: TH_Bal
                                        * Referenced by: '<S12>/Constant'
                                        */
static real32_T look2_iflf_binlx(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride);
static real32_T look2_iflf_pbinlc(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], uint32_T prevIndex[], const
  uint32_T maxIndex[], uint32_T stride);
static uint32_T plook_u32ff_linc(real32_T u, const real32_T bp[], uint32_T
  maxIndex, real32_T *fraction);
static real32_T look1_iflf_binlc(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T maxIndex);
static real32_T look1_iflf_binlx(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T maxIndex);
static uint32_T linsearch_u32f(real32_T u, const real32_T bp[], uint32_T
  startIndex);
static void BAL_Cell(const real32_T rtu_SOCs[14], const uint8_T rtu_CellEnable
                     [14], uint8_T rtu_Enable_Bal, uint8_T rtu_Enable_Discharge,
                     uint8_T rty_Command[14], uint8_T *rty_Bal_sts, DW_BAL_Cell *
                     localDW);
static void SOC_Estimation_Init(DW_SOC_Estimation *localDW);
static void SOC_Estimation(const real32_T rtu_InitialSOC[14], const real32_T
  rtu_CellTemperature[14], const real32_T rtu_CellVoltage[14], real32_T
  rtu_PackCurrent, const uint8_T rtu_CellEnable[14], real32_T rty_SOC[14],
  real32_T rty_R0[14], DW_SOC_Estimation *localDW);
static void SOH_Estimation(const real32_T rtu_SOC[14], const real32_T
  rtu_Temperature[14], const real32_T rtu_R0[14], real32_T rty_SOH[14]);
static void BMS_Controller_Init(DW_BMS_Controller *localDW);
static void BMS_Controller_p(const real32_T rtu_CellTemperatureNTC[14], const
  real32_T rtu_CellVoltage[14], real32_T rtu_PackCurrent, uint8_T rtu_Enable_Bal,
  uint8_T rtu_Enable_Discharge, const uint8_T rtu_CellEnable[14], real32_T
  rty_SOC[14], real32_T rty_SOH[14], uint8_T rty_Bal_cmd[14], uint8_T
  *rty_Bal_sts, DW_BMS_Controller *localDW);
static real32_T look2_iflf_binlx(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T fractions[2];
  real32_T frac;
  real32_T yL_0d0;
  real32_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = (u0 - bp0[0UL]) / (bp0[1UL] - bp0[0UL]);
  } else if (u0 < bp0[maxIndex[0UL]]) {
    /* Binary Search */
    bpIdx = maxIndex[0UL] >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex[0UL];
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0UL] - 1UL;
    frac = (u0 - bp0[maxIndex[0UL] - 1UL]) / (bp0[maxIndex[0UL]] - bp0[maxIndex
      [0UL] - 1UL]);
  }

  fractions[0UL] = frac;
  bpIndices[0UL] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0UL]) {
    iLeft = 0UL;
    frac = (u1 - bp1[0UL]) / (bp1[1UL] - bp1[0UL]);
  } else if (u1 < bp1[maxIndex[1UL]]) {
    /* Binary Search */
    bpIdx = maxIndex[1UL] >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex[1UL];
    while (iRght - iLeft > 1UL) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1UL] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1UL] - 1UL;
    frac = (u1 - bp1[maxIndex[1UL] - 1UL]) / (bp1[maxIndex[1UL]] - bp1[maxIndex
      [1UL] - 1UL]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0UL];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1UL] - yL_0d0) * fractions[0UL];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1UL] - yL_0d1) * fractions[0UL] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

static real32_T look2_iflf_pbinlc(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], uint32_T prevIndex[], const
  uint32_T maxIndex[], uint32_T stride)
{
  real32_T fractions[2];
  real32_T frac;
  real32_T yL_0d0;
  real32_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T found;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex[0UL]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0UL];
    iLeft = 0UL;
    iRght = maxIndex[0UL];
    found = 0UL;
    while (found == 0UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1UL;
        bpIdx = ((bpIdx + iLeft) - 1UL) >> 1UL;
      } else if (u0 < bp0[bpIdx + 1UL]) {
        found = 1UL;
      } else {
        iLeft = bpIdx + 1UL;
        bpIdx = ((bpIdx + iRght) + 1UL) >> 1UL;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1UL] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0UL] - 1UL;
    frac = 1.0F;
  }

  prevIndex[0UL] = bpIdx;
  fractions[0UL] = frac;
  bpIndices[0UL] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u1 < bp1[maxIndex[1UL]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[1UL];
    iLeft = 0UL;
    iRght = maxIndex[1UL];
    found = 0UL;
    while (found == 0UL) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx - 1UL;
        bpIdx = ((bpIdx + iLeft) - 1UL) >> 1UL;
      } else if (u1 < bp1[bpIdx + 1UL]) {
        found = 1UL;
      } else {
        iLeft = bpIdx + 1UL;
        bpIdx = ((bpIdx + iRght) + 1UL) >> 1UL;
      }
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1UL] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1UL] - 1UL;
    frac = 1.0F;
  }

  prevIndex[1UL] = bpIdx;

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  iLeft = bpIdx * stride + bpIndices[0UL];
  yL_0d0 = table[iLeft];
  yL_0d0 += (table[iLeft + 1UL] - yL_0d0) * fractions[0UL];
  iLeft += stride;
  yL_0d1 = table[iLeft];
  return (((table[iLeft + 1UL] - yL_0d1) * fractions[0UL] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

static uint32_T plook_u32ff_linc(real32_T u, const real32_T bp[], uint32_T
  maxIndex, real32_T *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0UL]) {
    bpIndex = 0UL;
    *fraction = 0.0F;
  } else if (u < bp[maxIndex]) {
    bpIndex = linsearch_u32f(u, bp, maxIndex >> 1UL);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1UL] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1UL;
    *fraction = 1.0F;
  }

  return bpIndex;
}

static real32_T look1_iflf_binlc(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T maxIndex)
{
  real32_T frac;
  real32_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex;
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1UL;
    frac = 1.0F;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1UL] - yL_0d0) * frac + yL_0d0;
}

static real32_T look1_iflf_binlx(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T maxIndex)
{
  real32_T frac;
  real32_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = (u0 - bp0[0UL]) / (bp0[1UL] - bp0[0UL]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex;
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1UL;
    frac = (u0 - bp0[maxIndex - 1UL]) / (bp0[maxIndex] - bp0[maxIndex - 1UL]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1UL] - yL_0d0) * frac + yL_0d0;
}

static uint32_T linsearch_u32f(real32_T u, const real32_T bp[], uint32_T
  startIndex)
{
  uint32_T bpIndex;

  /* Linear Search */
  for (bpIndex = startIndex; u < bp[bpIndex]; bpIndex--) {
  }

  while (u >= bp[bpIndex + 1UL]) {
    bpIndex++;
  }

  return bpIndex;
}

/* Output and update for atomic system: '<S1>/BAL_Cell' */
static void BAL_Cell(const real32_T rtu_SOCs[14], const uint8_T rtu_CellEnable
                     [14], uint8_T rtu_Enable_Bal, uint8_T rtu_Enable_Discharge,
                     uint8_T rty_Command[14], uint8_T *rty_Bal_sts, DW_BAL_Cell *
                     localDW)
{
  real32_T rtb_ImpAsg_InsertedFor_SOC_out_[14];
  int16_T ForEach_itr_i;
  uint8_T rtb_Gain;

  /* If: '<S2>/If_Discharge' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion3'
   */
  if (rtu_Enable_Discharge != 0) {
    /* Outputs for IfAction SubSystem: '<S2>/Discharge_Enabled' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
      /* Merge: '<S2>/Merge' incorporates:
       *  SignalConversion generated from: '<S6>/Command'
       */
      localDW->Merge[ForEach_itr_i] = true;
    }

    /* End of Outputs for SubSystem: '<S2>/Discharge_Enabled' */
  } else {
    /* Outputs for IfAction SubSystem: '<S2>/Local_Balancing_Enabled' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Outputs for Iterator SubSystem: '<S7>/SOCcorrection' incorporates:
     *  ForEach: '<S10>/For Each'
     */
    for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
      /* MultiPortSwitch: '<S10>/Multiport Switch1' incorporates:
       *  ForEachSliceSelector generated from: '<S10>/CellEnable'
       */
      if (rtu_CellEnable[ForEach_itr_i] == 0) {
        /* ForEachSliceAssignment generated from: '<S10>/SOC_out' incorporates:
         *  Constant: '<S10>/SOC_MAX'
         */
        rtb_ImpAsg_InsertedFor_SOC_out_[ForEach_itr_i] = SOC_MAX;
      } else {
        /* ForEachSliceAssignment generated from: '<S10>/SOC_out' incorporates:
         *  ForEachSliceSelector generated from: '<S10>/SOC_in'
         */
        rtb_ImpAsg_InsertedFor_SOC_out_[ForEach_itr_i] = rtu_SOCs[ForEach_itr_i];
      }

      /* End of MultiPortSwitch: '<S10>/Multiport Switch1' */
    }

    /* End of Outputs for SubSystem: '<S7>/SOCcorrection' */

    /* Outputs for Enabled SubSystem: '<S9>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S11>/Enable'
     */
    if (rtu_Enable_Bal != 0) {
      real32_T minim;

      /* MATLAB Function: '<S11>/MATLAB Function' incorporates:
       *  Constant: '<S11>/SOC_MAX'
       */
      minim = SOC_MAX;
      for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
        real32_T rtb_ImpAsg_InsertedFor_SOC_ou_b;
        rtb_ImpAsg_InsertedFor_SOC_ou_b =
          rtb_ImpAsg_InsertedFor_SOC_out_[ForEach_itr_i];
        if (rtb_ImpAsg_InsertedFor_SOC_ou_b < minim) {
          minim = rtb_ImpAsg_InsertedFor_SOC_ou_b;
        }
      }

      /* Gain: '<S11>/Gain' incorporates:
       *  MATLAB Function: '<S11>/MATLAB Function'
       */
      rtb_Gain = (uint8_T)(100.0F * minim);
      for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
        /* RelationalOperator: '<S12>/Compare' incorporates:
         *  Constant: '<S12>/Constant'
         *  Gain: '<S11>/Gain1'
         *  Sum: '<S11>/Sum1'
         */
        localDW->Compare[ForEach_itr_i] = ((uint8_T)((uint8_T)(100.0F *
          rtb_ImpAsg_InsertedFor_SOC_out_[ForEach_itr_i]) - rtb_Gain) >= TH_Bal);
      }
    }

    /* End of Outputs for SubSystem: '<S9>/Enabled Subsystem' */
    for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
      /* Merge: '<S2>/Merge' incorporates:
       *  SignalConversion generated from: '<S7>/Command'
       */
      localDW->Merge[ForEach_itr_i] = localDW->Compare[ForEach_itr_i];
    }

    /* End of Outputs for SubSystem: '<S2>/Local_Balancing_Enabled' */
  }

  /* End of If: '<S2>/If_Discharge' */

  /* Outputs for Iterator SubSystem: '<S2>/SOCcorrection' incorporates:
   *  ForEach: '<S8>/For Each'
   */
  /* DataTypeConversion: '<S2>/Data Type Conversion' */
  for (ForEach_itr_i = 0; ForEach_itr_i < 14; ForEach_itr_i++) {
    boolean_T rtb_ImpAsg_InsertedFor_BAL_cm_k;

    /* MultiPortSwitch: '<S8>/Multiport Switch' incorporates:
     *  ForEachSliceSelector generated from: '<S8>/CellEnable'
     */
    if (rtu_CellEnable[ForEach_itr_i] == 0) {
      /* ForEachSliceAssignment generated from: '<S8>/BAL_cmd_out' incorporates:
       *  Constant: '<S8>/Constant'
       */
      rtb_ImpAsg_InsertedFor_BAL_cm_k = false;
    } else {
      /* ForEachSliceAssignment generated from: '<S8>/BAL_cmd_out' incorporates:
       *  ForEachSliceSelector generated from: '<S8>/BAL_cmd_in'
       */
      rtb_ImpAsg_InsertedFor_BAL_cm_k = localDW->Merge[ForEach_itr_i];
    }

    /* End of MultiPortSwitch: '<S8>/Multiport Switch' */
    rty_Command[ForEach_itr_i] = rtb_ImpAsg_InsertedFor_BAL_cm_k;
  }

  /* End of DataTypeConversion: '<S2>/Data Type Conversion' */
  /* End of Outputs for SubSystem: '<S2>/SOCcorrection' */

  /* MinMax: '<S2>/MinMax' */
  rtb_Gain = rty_Command[0];
  for (ForEach_itr_i = 0; ForEach_itr_i < 13; ForEach_itr_i++) {
    uint8_T u1;
    u1 = rty_Command[(int32_T)(ForEach_itr_i + 1)];
    if (rtb_Gain < u1) {
      rtb_Gain = u1;
    }
  }

  *rty_Bal_sts = rtb_Gain;

  /* End of MinMax: '<S2>/MinMax' */
}

/* System initialize for atomic system: '<S1>/SOC_Estimation' */
static void SOC_Estimation_Init(DW_SOC_Estimation *localDW)
{
  int16_T ForEach_itr;
  int16_T i;

  /* SystemInitialize for Iterator SubSystem: '<S4>/SOC Estimator (Adaptive Kalman Filter)' */
  for (ForEach_itr = 0; ForEach_itr < 14; ForEach_itr++) {
    /* InitializeConditions for Delay: '<S14>/Delay1' */
    localDW->CoreSubsys[ForEach_itr].icLoad = true;

    /* InitializeConditions for Delay: '<S14>/Delay' */
    localDW->CoreSubsys[ForEach_itr].icLoad_e = true;

    /* InitializeConditions for Delay: '<S14>/Delay2' */
    localDW->CoreSubsys[ForEach_itr].icLoad_g = true;

    /* SystemInitialize for Enabled SubSystem: '<S14>/KalmanFilter' */
    /* Start for Probe: '<S24>/Probe' */
    localDW->CoreSubsys[ForEach_itr].Probe[0] = 1.0F;
    localDW->CoreSubsys[ForEach_itr].Probe[1] = 0.0F;

    /* InitializeConditions for Delay: '<S23>/Delay' */
    localDW->CoreSubsys[ForEach_itr].icLoad_p = true;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay - P' */
    for (i = 0; i < 9; i++) {
      localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[i] =
        rtConstP.UnitDelayP_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S21>/Unit Delay - P' */
    /* End of SystemInitialize for SubSystem: '<S14>/KalmanFilter' */
  }

  /* End of SystemInitialize for SubSystem: '<S4>/SOC Estimator (Adaptive Kalman Filter)' */
}

/* Output and update for atomic system: '<S1>/SOC_Estimation' */
static void SOC_Estimation(const real32_T rtu_InitialSOC[14], const real32_T
  rtu_CellTemperature[14], const real32_T rtu_CellVoltage[14], real32_T
  rtu_PackCurrent, const uint8_T rtu_CellEnable[14], real32_T rty_SOC[14],
  real32_T rty_R0[14], DW_SOC_Estimation *localDW)
{
  real32_T rtb_Assignment[9];
  real32_T rtb_Sum1_b[9];
  real32_T tmp[9];
  real32_T rtb_Product3[3];
  real32_T rtb_TmpSignalConversionAtProduc[3];
  real32_T tmp_0[3];
  int16_T ForEach_itr;
  int16_T i;
  int16_T iU;

  /* Lookup_n-D: '<S4>/R0 Table' */
  for (iU = 0; iU < 14; iU++) {
    localDW->R0Table[iU] = look2_iflf_pbinlc(rtu_InitialSOC[iU],
      rtu_CellTemperature[iU], &SOC_Vector[0], &Temperature_Vector[0],
      &R0_Vector[0], &localDW->m_bpIndex[iU << 1], rtConstP.pooled5, 17UL);
  }

  /* End of Lookup_n-D: '<S4>/R0 Table' */

  /* Outputs for Iterator SubSystem: '<S4>/SOC Estimator (Adaptive Kalman Filter)' incorporates:
   *  ForEach: '<S14>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 14; ForEach_itr++) {
    real32_T rtb_MathFunction;
    real32_T rtb_uDLookupTableR1;
    boolean_T rtb_AND2;

    /* Delay: '<S14>/Delay1' incorporates:
     *  ForEachSliceSelector generated from: '<S14>/InitialSOC'
     */
    if (localDW->CoreSubsys[ForEach_itr].icLoad) {
      localDW->CoreSubsys[ForEach_itr].Delay1_DSTATE =
        rtu_InitialSOC[ForEach_itr];
    }

    /* Delay: '<S14>/Delay' incorporates:
     *  Delay: '<S14>/Delay1'
     */
    if (localDW->CoreSubsys[ForEach_itr].icLoad_e) {
      localDW->CoreSubsys[ForEach_itr].Delay_DSTATE = localDW->
        CoreSubsys[ForEach_itr].Delay1_DSTATE;
    }

    /* Logic: '<S14>/AND2' incorporates:
     *  Constant: '<S15>/Constant'
     *  Constant: '<S16>/Constant'
     *  Constant: '<S17>/Constant'
     *  Constant: '<S18>/Constant'
     *  Delay: '<S14>/Delay'
     *  ForEachSliceSelector generated from: '<S14>/CellEnable'
     *  Logic: '<S14>/AND'
     *  Logic: '<S14>/AND1'
     *  RelationalOperator: '<S15>/Compare'
     *  RelationalOperator: '<S16>/Compare'
     *  RelationalOperator: '<S17>/Compare'
     *  RelationalOperator: '<S18>/Compare'
     */
    rtb_AND2 = (((!(localDW->CoreSubsys[ForEach_itr].Delay_DSTATE >= SOC_MAX)) ||
                 (!(rtu_PackCurrent > 0.0F))) && ((!(localDW->
      CoreSubsys[ForEach_itr].Delay_DSTATE <= SOC_MIN)) || (!(rtu_PackCurrent <
      0.0F))) && (rtu_CellEnable[ForEach_itr] != 0));

    /* Delay: '<S14>/Delay2' incorporates:
     *  ForEachSliceSelector generated from: '<S14>/InitialR0'
     */
    if (localDW->CoreSubsys[ForEach_itr].icLoad_g) {
      localDW->CoreSubsys[ForEach_itr].Delay2_DSTATE = localDW->
        R0Table[ForEach_itr];
    }

    /* Outputs for Enabled SubSystem: '<S14>/KalmanFilter' incorporates:
     *  EnablePort: '<S19>/Enable'
     */
    if (rtb_AND2) {
      real32_T rtb_Sum_ls;
      int16_T rtb_Sum1_a_tmp;
      if (!localDW->CoreSubsys[ForEach_itr].KalmanFilter_MODE) {
        /* InitializeConditions for Delay: '<S23>/Delay' */
        localDW->CoreSubsys[ForEach_itr].icLoad_p = true;

        /* InitializeConditions for UnitDelay: '<S21>/Unit Delay - P' */
        for (i = 0; i < 9; i++) {
          localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[i] =
            rtConstP.UnitDelayP_InitialCondition[i];
        }

        /* End of InitializeConditions for UnitDelay: '<S21>/Unit Delay - P' */
        localDW->CoreSubsys[ForEach_itr].KalmanFilter_MODE = true;
      }

      /* Delay: '<S23>/Delay' incorporates:
       *  Constant: '<S23>/Constant1'
       *  Delay: '<S14>/Delay1'
       *  Delay: '<S14>/Delay2'
       *  SignalConversion generated from: '<S23>/Delay'
       */
      if (localDW->CoreSubsys[ForEach_itr].icLoad_p) {
        localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[0] = localDW->
          CoreSubsys[ForEach_itr].Delay1_DSTATE;
        localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[1] = 0.0F;
        localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[2] = localDW->
          CoreSubsys[ForEach_itr].Delay2_DSTATE;
      }

      /* SignalConversion generated from: '<S24>/Transpose1' incorporates:
       *  Constant: '<S24>/Constant4'
       *  Delay: '<S23>/Delay'
       *  ForEachSliceSelector generated from: '<S14>/CellTemperature'
       *  Gain: '<S14>/Gain'
       *  Lookup_n-D: '<S24>/2-D Lookup Table dOCV'
       */
      rtb_Product3[0] = look2_iflf_binlx(localDW->CoreSubsys[ForEach_itr].
        Delay_DSTATE_p[0], rtu_CellTemperature[ForEach_itr], &SOC_Vector[0],
        &Temperature_Vector[0], rtConstP.uDLookupTabledOCV_tableData,
        rtConstP.pooled5, 17UL);
      rtb_Product3[1] = -1.0F;
      rtb_Product3[2] = rtu_PackCurrent;

      /* Lookup_n-D: '<S24>/2-D Lookup Table R1' incorporates:
       *  Delay: '<S23>/Delay'
       *  ForEachSliceSelector generated from: '<S14>/CellTemperature'
       */
      rtb_uDLookupTableR1 = look2_iflf_binlx(localDW->CoreSubsys[ForEach_itr].
        Delay_DSTATE_p[0], rtu_CellTemperature[ForEach_itr], &SOC_Vector[0],
        &Temperature_Vector[0], &R1_Vector[0], rtConstP.pooled5, 17UL);

      /* Math: '<S24>/Math Function' incorporates:
       *  Delay: '<S23>/Delay'
       *  ForEachSliceSelector generated from: '<S14>/CellTemperature'
       *  Gain: '<S24>/-Ts'
       *  Lookup_n-D: '<S24>/2-D Lookup Table C1'
       *  Product: '<S24>/Product'
       *  Product: '<S24>/Product2'
       *
       * About '<S24>/Math Function':
       *  Operator: exp
       */
      rtb_MathFunction = expf(-localDW->CoreSubsys[ForEach_itr].Probe[0] /
        (rtb_uDLookupTableR1 * look2_iflf_binlx(localDW->CoreSubsys[ForEach_itr]
        .Delay_DSTATE_p[0], rtu_CellTemperature[ForEach_itr], &SOC_Vector[0],
        &Temperature_Vector[0], rtConstP.uDLookupTableC1_tableData,
        rtConstP.pooled5, 17UL)));

      /* SignalConversion generated from: '<S24>/Assignment' incorporates:
       *  Assignment: '<S24>/Assignment'
       *  Constant: '<S24>/Constant'
       */
      for (i = 0; i < 9; i++) {
        rtb_Assignment[i] = rtConstP.Constant_Value[i];
      }

      /* End of SignalConversion generated from: '<S24>/Assignment' */

      /* Assignment: '<S24>/Assignment' */
      rtb_Assignment[4] = rtb_MathFunction;

      /* Product: '<S25>/Product2' incorporates:
       *  Assignment: '<S24>/Assignment'
       *  Math: '<S25>/Transpose'
       *  UnitDelay: '<S21>/Unit Delay - P'
       */
      for (iU = 0; iU < 3; iU++) {
        for (i = 0; i < 3; i++) {
          rtb_Sum1_a_tmp = 3 * i + iU;
          tmp[rtb_Sum1_a_tmp] = 0.0F;
          tmp[rtb_Sum1_a_tmp] += localDW->CoreSubsys[ForEach_itr].
            UnitDelayP_DSTATE[iU] * rtb_Assignment[i];
          tmp[rtb_Sum1_a_tmp] += localDW->CoreSubsys[ForEach_itr].
            UnitDelayP_DSTATE[iU + 3] * rtb_Assignment[i + 3];
          tmp[rtb_Sum1_a_tmp] += localDW->CoreSubsys[ForEach_itr].
            UnitDelayP_DSTATE[iU + 6] * rtb_Assignment[i + 6];
        }
      }

      /* Product: '<S22>/Product2' */
      rtb_Sum_ls = 0.0F;
      for (iU = 0; iU < 3; iU++) {
        /* Product: '<S22>/Product2' incorporates:
         *  Product: '<S22>/Product'
         */
        rtb_TmpSignalConversionAtProduc[iU] = 0.0F;
        for (i = 0; i < 3; i++) {
          real32_T rtb_Sum1_n;

          /* Sum: '<S25>/Sum1' incorporates:
           *  Assignment: '<S24>/Assignment'
           *  Constant: '<S25>/Constant'
           *  Product: '<S25>/Product2'
           */
          rtb_Sum1_a_tmp = 3 * i + iU;
          rtb_Sum1_n = ((tmp[3 * i + 1] * rtb_Assignment[iU + 3] + tmp[3 * i] *
                         rtb_Assignment[iU]) + tmp[3 * i + 2] *
                        rtb_Assignment[iU + 6]) +
            rtConstP.Constant_Value_n[rtb_Sum1_a_tmp];
          rtb_Sum1_b[rtb_Sum1_a_tmp] = rtb_Sum1_n;

          /* Product: '<S22>/Product2' incorporates:
           *  Math: '<S22>/Transpose'
           *  Product: '<S22>/Product3'
           */
          rtb_TmpSignalConversionAtProduc[iU] += rtb_Sum1_n * rtb_Product3[i];
        }

        /* Product: '<S22>/Product2' incorporates:
         *  Product: '<S22>/Product3'
         */
        rtb_Sum_ls += rtb_Product3[iU] * rtb_TmpSignalConversionAtProduc[iU];
      }

      /* Product: '<S22>/Divide' incorporates:
       *  Constant: '<S22>/Constant'
       *  Constant: '<S22>/Constant1'
       *  Product: '<S22>/Product2'
       *  Sum: '<S22>/Sum2'
       */
      rtb_Sum_ls = 1.0F / (rtb_Sum_ls + 0.1F);

      /* Product: '<S22>/Product1' incorporates:
       *  Product: '<S22>/Product'
       *  SignalConversion generated from: '<S25>/Product1'
       */
      rtb_TmpSignalConversionAtProduc[0] *= rtb_Sum_ls;
      rtb_TmpSignalConversionAtProduc[1] *= rtb_Sum_ls;
      rtb_TmpSignalConversionAtProduc[2] *= rtb_Sum_ls;

      /* Sum: '<S21>/Sum' incorporates:
       *  Delay: '<S23>/Delay'
       *  ForEachSliceSelector generated from: '<S14>/CellTemperature'
       *  ForEachSliceSelector generated from: '<S14>/CellVoltage'
       *  Gain: '<S14>/Gain'
       *  Lookup_n-D: '<S24>/2-D Lookup Table OCV'
       *  Product: '<S24>/Product6'
       *  Sum: '<S24>/Sum2'
       */
      rtb_Sum_ls = rtu_CellVoltage[ForEach_itr] - ((look2_iflf_binlx
        (localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[0],
         rtu_CellTemperature[ForEach_itr], &SOC_Vector[0], &Temperature_Vector[0],
         &OCV_Vector[0], rtConstP.pooled5, 17UL) - localDW->
        CoreSubsys[ForEach_itr].Delay_DSTATE_p[2] * -rtu_PackCurrent) -
        localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[1]);

      /* SignalConversion generated from: '<S25>/Product1' incorporates:
       *  Constant: '<S24>/Constant1'
       *  Constant: '<S24>/Constant2'
       *  Gain: '<S14>/Gain'
       *  Gain: '<S24>/-Ts'
       *  Gain: '<S24>/Gain1'
       *  Product: '<S24>/Product4'
       *  Product: '<S25>/Product1'
       *  Sum: '<S24>/Sum'
       */
      tmp_0[0] = 1.0F / (Cap_Nom * 3600.0F) * -localDW->CoreSubsys[ForEach_itr].
        Probe[0] * -rtu_PackCurrent;
      tmp_0[1] = (1.0F - rtb_MathFunction) * rtb_uDLookupTableR1 *
        -rtu_PackCurrent;
      tmp_0[2] = 0.0F * -rtu_PackCurrent;
      for (iU = 0; iU < 3; iU++) {
        /* Sum: '<S22>/Sum' incorporates:
         *  Assignment: '<S24>/Assignment'
         *  Delay: '<S23>/Delay'
         *  Product: '<S22>/Product3'
         *  Product: '<S25>/Product'
         *  SignalConversion generated from: '<S25>/Product1'
         *  Sum: '<S25>/Sum'
         */
        localDW->CoreSubsys[ForEach_itr].Sum[iU] = (((rtb_Assignment[iU + 3] *
          localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[1] + rtb_Assignment[iU]
          * localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[0]) +
          rtb_Assignment[iU + 6] * localDW->CoreSubsys[ForEach_itr].
          Delay_DSTATE_p[2]) + tmp_0[iU]) + rtb_TmpSignalConversionAtProduc[iU] *
          rtb_Sum_ls;
      }

      /* Update for Delay: '<S23>/Delay' incorporates:
       *  Product: '<S22>/Product3'
       *  Product: '<S22>/Product4'
       */
      localDW->CoreSubsys[ForEach_itr].icLoad_p = false;
      for (i = 0; i < 3; i++) {
        rtb_Sum_ls = rtb_Product3[i];
        localDW->CoreSubsys[ForEach_itr].Delay_DSTATE_p[i] = localDW->
          CoreSubsys[ForEach_itr].Sum[i];

        /* Sum: '<S22>/Sum3' incorporates:
         *  Constant: '<S22>/Constant2'
         *  Product: '<S22>/Product3'
         *  Product: '<S22>/Product4'
         *  SignalConversion generated from: '<S25>/Product1'
         */
        tmp[3 * i] = rtConstP.Constant2_Value[3 * i] -
          rtb_TmpSignalConversionAtProduc[0] * rtb_Sum_ls;
        iU = 3 * i + 1;
        tmp[iU] = rtConstP.Constant2_Value[iU] -
          rtb_TmpSignalConversionAtProduc[1] * rtb_Sum_ls;
        iU = 3 * i + 2;
        tmp[iU] = rtConstP.Constant2_Value[iU] -
          rtb_TmpSignalConversionAtProduc[2] * rtb_Sum_ls;
      }

      /* End of Update for Delay: '<S23>/Delay' */

      /* Update for UnitDelay: '<S21>/Unit Delay - P' incorporates:
       *  Product: '<S22>/Product5'
       *  Sum: '<S25>/Sum1'
       */
      for (iU = 0; iU < 3; iU++) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S22>/Product5' */
          rtb_Sum1_a_tmp = 3 * i + iU;
          localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[rtb_Sum1_a_tmp] =
            0.0F;
          localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[rtb_Sum1_a_tmp] +=
            rtb_Sum1_b[3 * i] * tmp[iU];
          localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[rtb_Sum1_a_tmp] +=
            rtb_Sum1_b[3 * i + 1] * tmp[iU + 3];
          localDW->CoreSubsys[ForEach_itr].UnitDelayP_DSTATE[rtb_Sum1_a_tmp] +=
            rtb_Sum1_b[3 * i + 2] * tmp[iU + 6];
        }
      }

      /* End of Update for UnitDelay: '<S21>/Unit Delay - P' */
    } else {
      localDW->CoreSubsys[ForEach_itr].KalmanFilter_MODE = false;
    }

    /* End of Outputs for SubSystem: '<S14>/KalmanFilter' */

    /* MultiPortSwitch: '<S14>/R0_sw' incorporates:
     *  Delay: '<S14>/Delay2'
     */
    if (!rtb_AND2) {
      rtb_uDLookupTableR1 = localDW->CoreSubsys[ForEach_itr].Delay2_DSTATE;

      /* MultiPortSwitch: '<S14>/SOC_sw' incorporates:
       *  Delay: '<S14>/Delay1'
       *  Delay: '<S14>/Delay2'
       */
      rtb_MathFunction = localDW->CoreSubsys[ForEach_itr].Delay1_DSTATE;
    } else {
      rtb_uDLookupTableR1 = localDW->CoreSubsys[ForEach_itr].Sum[2];

      /* MultiPortSwitch: '<S14>/SOC_sw' */
      rtb_MathFunction = localDW->CoreSubsys[ForEach_itr].Sum[0];
    }

    /* End of MultiPortSwitch: '<S14>/R0_sw' */

    /* Update for Delay: '<S14>/Delay1' */
    localDW->CoreSubsys[ForEach_itr].icLoad = false;
    localDW->CoreSubsys[ForEach_itr].Delay1_DSTATE = rtb_MathFunction;

    /* Update for Delay: '<S14>/Delay' */
    localDW->CoreSubsys[ForEach_itr].icLoad_e = false;
    localDW->CoreSubsys[ForEach_itr].Delay_DSTATE = rtb_MathFunction;

    /* Update for Delay: '<S14>/Delay2' */
    localDW->CoreSubsys[ForEach_itr].icLoad_g = false;
    localDW->CoreSubsys[ForEach_itr].Delay2_DSTATE = rtb_uDLookupTableR1;

    /* ForEachSliceAssignment generated from: '<S14>/SOC' */
    rty_SOC[ForEach_itr] = rtb_MathFunction;

    /* ForEachSliceAssignment generated from: '<S14>/R0' */
    rty_R0[ForEach_itr] = rtb_uDLookupTableR1;
  }

  /* End of Outputs for SubSystem: '<S4>/SOC Estimator (Adaptive Kalman Filter)' */
}

/* Output and update for atomic system: '<S1>/SOH_Estimation' */
static void SOH_Estimation(const real32_T rtu_SOC[14], const real32_T
  rtu_Temperature[14], const real32_T rtu_R0[14], real32_T rty_SOH[14])
{
  int16_T ForEach_itr;

  /* Outputs for Iterator SubSystem: '<S5>/SOH Estimator' incorporates:
   *  ForEach: '<S26>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 14; ForEach_itr++) {
    real32_T rtb_uDLookupTableR0EOL;

    /* Lookup_n-D: '<S26>/2-D Lookup Table R0 EOL' incorporates:
     *  ForEachSliceSelector generated from: '<S26>/SOC'
     *  ForEachSliceSelector generated from: '<S26>/Temperature'
     */
    rtb_uDLookupTableR0EOL = look2_iflf_binlx(rtu_SOC[ForEach_itr],
      rtu_Temperature[ForEach_itr], &SOC_Vector[0], &Temperature_Vector[0],
      &R0_EOL_Vector[0], rtConstP.pooled5, 17UL);

    /* Product: '<S26>/Product3' incorporates:
     *  ForEachSliceSelector generated from: '<S26>/R0'
     *  ForEachSliceSelector generated from: '<S26>/SOC'
     *  ForEachSliceSelector generated from: '<S26>/Temperature'
     *  Lookup_n-D: '<S26>/2-D Lookup Table R0 new'
     *  Sum: '<S26>/Sum1'
     *  Sum: '<S26>/Sum3'
     */
    rtb_uDLookupTableR0EOL = (rtb_uDLookupTableR0EOL - rtu_R0[ForEach_itr]) /
      (rtb_uDLookupTableR0EOL - look2_iflf_binlx(rtu_SOC[ForEach_itr],
        rtu_Temperature[ForEach_itr], &SOC_Vector[0], &Temperature_Vector[0],
        &R0_Vector[0], rtConstP.pooled5, 17UL));

    /* Saturate: '<S26>/Saturation' */
    if (rtb_uDLookupTableR0EOL > SOH_MAX) {
      /* ForEachSliceAssignment generated from: '<S26>/SOH' */
      rty_SOH[ForEach_itr] = SOH_MAX;
    } else if (rtb_uDLookupTableR0EOL < SOH_MIN) {
      /* ForEachSliceAssignment generated from: '<S26>/SOH' */
      rty_SOH[ForEach_itr] = SOH_MIN;
    } else {
      /* ForEachSliceAssignment generated from: '<S26>/SOH' */
      rty_SOH[ForEach_itr] = rtb_uDLookupTableR0EOL;
    }

    /* End of Saturate: '<S26>/Saturation' */
  }

  /* End of Outputs for SubSystem: '<S5>/SOH Estimator' */
}

/* System initialize for atomic system: '<Root>/BMS_Controller' */
static void BMS_Controller_Init(DW_BMS_Controller *localDW)
{
  /* SystemInitialize for Atomic SubSystem: '<S1>/SOC_Estimation' */
  SOC_Estimation_Init(&localDW->SOC_Estimation_p);

  /* End of SystemInitialize for SubSystem: '<S1>/SOC_Estimation' */
}

/* Output and update for atomic system: '<Root>/BMS_Controller' */
static void BMS_Controller_p(const real32_T rtu_CellTemperatureNTC[14], const
  real32_T rtu_CellVoltage[14], real32_T rtu_PackCurrent, uint8_T rtu_Enable_Bal,
  uint8_T rtu_Enable_Discharge, const uint8_T rtu_CellEnable[14], real32_T
  rty_SOC[14], real32_T rty_SOH[14], uint8_T rty_Bal_cmd[14], uint8_T
  *rty_Bal_sts, DW_BMS_Controller *localDW)
{
  /* local block i/o variables */
  real32_T rtb_ImpAsg_InsertedFor_R0_at_in[14];
  real32_T Sum[14];
  real32_T rtb_Prelookup_o2;
  int16_T ForEach_itr;
  for (ForEach_itr = 0; ForEach_itr < 14; ForEach_itr++) {
    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<S1>/ToKelvin'
     *  Lookup_n-D: '<S1>/NTC_LKT'
     */
    Sum[ForEach_itr] = look1_iflf_binlx(rtu_CellTemperatureNTC[ForEach_itr],
      &NTC_Vector[0], &NTC_Temp_Vector[0], 32UL) + KELVIN_CON;
  }

  /* Outputs for Iterator SubSystem: '<S1>/InitSOC' incorporates:
   *  ForEach: '<S3>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 14; ForEach_itr++) {
    uint32_T rtb_Prelookup_o1;

    /* PreLookup: '<S3>/Prelookup' incorporates:
     *  ForEachSliceSelector generated from: '<S3>/TemperatureNTC'
     */
    rtb_Prelookup_o1 = plook_u32ff_linc(Sum[ForEach_itr], &Temperature_Vector[0],
      4UL, &rtb_Prelookup_o2);

    /* ForEachSliceAssignment generated from: '<S3>/InitSOC' incorporates:
     *  Constant: '<S3>/Constant1'
     *  ForEachSliceSelector generated from: '<S3>/CellVoltage'
     *  Lookup_n-D: '<S3>/1-D Lookup Table'
     *  Selector: '<S3>/Selector'
     */
    localDW->ImpAsg_InsertedFor_InitSOC_at_i[ForEach_itr] = look1_iflf_binlc
      (rtu_CellVoltage[ForEach_itr], &OCV_Vector[17 * (int16_T)rtb_Prelookup_o1],
       &SOC_Vector[0], 16UL);
  }

  /* End of Outputs for SubSystem: '<S1>/InitSOC' */

  /* Outputs for Atomic SubSystem: '<S1>/SOC_Estimation' */
  SOC_Estimation(localDW->ImpAsg_InsertedFor_InitSOC_at_i, Sum, rtu_CellVoltage,
                 rtu_PackCurrent, rtu_CellEnable, rty_SOC,
                 rtb_ImpAsg_InsertedFor_R0_at_in, &localDW->SOC_Estimation_p);

  /* End of Outputs for SubSystem: '<S1>/SOC_Estimation' */

  /* Outputs for Atomic SubSystem: '<S1>/BAL_Cell' */
  BAL_Cell(rty_SOC, rtu_CellEnable, rtu_Enable_Bal, rtu_Enable_Discharge,
           rty_Bal_cmd, rty_Bal_sts, &localDW->BAL_Cell_e);

  /* End of Outputs for SubSystem: '<S1>/BAL_Cell' */

  /* Outputs for Atomic SubSystem: '<S1>/SOH_Estimation' */
  SOH_Estimation(rty_SOC, Sum, rtb_ImpAsg_InsertedFor_R0_at_in, rty_SOH);

  /* End of Outputs for SubSystem: '<S1>/SOH_Estimation' */
}

/* Model step function */
void BMS_Controller_step(RT_MODEL *const rtM, real32_T rtU_CellTemperatureNTC[14],
  real32_T rtU_CellVoltage[14], real32_T rtU_PackCurrent, uint8_T rtU_Enable_Bal,
  uint8_T rtU_Enable_Discharge, uint8_T rtU_Enable_Cell[14], real32_T rtY_SOC[14],
  real32_T rtY_SOH[14], uint8_T rtY_Bal_cmd[14], uint8_T *rtY_Bal_sts)
{
  DW *rtDW = rtM->dwork;

  /* Outputs for Atomic SubSystem: '<Root>/BMS_Controller' */

  /* Inport: '<Root>/CellTemperatureNTC' incorporates:
   *  Inport: '<Root>/CellEnable'
   *  Inport: '<Root>/CellVoltage'
   *  Inport: '<Root>/Enable_Bal'
   *  Inport: '<Root>/Enable_Discharge'
   *  Inport: '<Root>/PackCurrent'
   *  Outport: '<Root>/Bal_cmd'
   *  Outport: '<Root>/Bal_sts'
   *  Outport: '<Root>/SOC'
   *  Outport: '<Root>/SOH'
   */
  BMS_Controller_p(rtU_CellTemperatureNTC, rtU_CellVoltage, rtU_PackCurrent,
                   rtU_Enable_Bal, rtU_Enable_Discharge, rtU_Enable_Cell,
                   rtY_SOC, rtY_SOH, rtY_Bal_cmd, rtY_Bal_sts,
                   &rtDW->BMS_Controller_pd);

  /* End of Outputs for SubSystem: '<Root>/BMS_Controller' */
}

/* Model initialize function */
void BMS_Controller_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;

  /* SystemInitialize for Atomic SubSystem: '<Root>/BMS_Controller' */
  BMS_Controller_Init(&rtDW->BMS_Controller_pd);

  /* End of SystemInitialize for SubSystem: '<Root>/BMS_Controller' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
