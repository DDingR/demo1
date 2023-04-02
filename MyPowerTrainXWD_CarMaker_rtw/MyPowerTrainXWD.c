/*
 * MyPowerTrainXWD.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "MyPowerTrainXWD".
 *
 * Model version              : 1.3
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Wed Mar 22 12:45:22 2023
 *
 * Target selection: CarMaker.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MyPowerTrainXWD.h"
#include "MyPowerTrainXWD_types.h"
#include <string.h>
#include "MyPowerTrainXWD_private.h"
#include <infoc.h>
#include <Log.h>
#include <InfoParam.h>
#include <DataDict.h>
#include <MatSupp.h>
#include "MyPowerTrainXWD_wrap.h"

/* CarMaker: Compile- and link-time checks for the right Matlab version. */
#if MATSUPP_NUMVER == 91200

/* The following statement will cause an "unresolved symbol" error when
   linking with a MatSupp library built for the wrong Matlab version. */
extern int MATSUPP_VARNAME(MatSupp, MATSUPP_NUMVER);
void *MATSUPP_VARNAME(MODEL, MATSUPP_NUMVER) = &MATSUPP_VARNAME(MatSupp,
  MATSUPP_NUMVER);

#else
# error Compiler options unsuitable for C code created with Matlab 9.12
#endif

/* Block parameters (default storage) */
P_MyPowerTrainXWD_T MyPowerTrainXWD_P = {
  /* Expression: 0
   * Referenced by: '<S1>/ECU_Status'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.Engine_on'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.TrqDrag'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.TrqFull'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.TrqOpt'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/EngineOut.FuelFlow'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MCU_Status'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.TrqMot_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.TrqGen_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.PwrElec'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.i_M2W.FL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.i_M2W.FR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.i_M2W.RL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ISGOut.i_M2W.RR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.TrqMot_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.TrqGen_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.PwrElec'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.i_M2W.FL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.i_M2W.FR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.i_M2W.RL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m0.i_M2W.RR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.TrqMot_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.TrqGen_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.PwrElec'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.i_M2W.FL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.i_M2W.FR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.i_M2W.RL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m1.i_M2W.RR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.TrqMot_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.TrqGen_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.PwrElec'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.i_M2W.FL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.i_M2W.FR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.i_M2W.RL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m2.i_M2W.RR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.rotv'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.Trq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.TrqMot_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.TrqGen_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.PwrElec'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.i_M2W.FL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.i_M2W.FR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.i_M2W.RL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/MotorOut.m3.i_M2W.RR'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/TCU_Status'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/ClutchOut.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.GearNo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.GearNo_dis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Trq_DriveSrc_trg'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.i'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxOut.Clutch_dis.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.GearNo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.GearNo_dis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Trq_DriveSrc_trg'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.i'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.GearNo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.GearNo_dis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Trq_DriveSrc_trg'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.i'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.GearNo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.GearNo_dis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Trq_DriveSrc_trg'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.i'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.GearNo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.GearNo_dis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Trq_DriveSrc_trg'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.i'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Pos'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.rotv_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.rotv_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Trq_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Trq_out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.i_TrqIn2Out'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BCU_Status'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.SOC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.SOH'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.Current'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.AOC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.Temp'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.Energy'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattLVOut.Pwr_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.SOC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.SOH'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.Current'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.AOC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.Temp'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.Energy'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/BattHVOut.Pwr_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_LV'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Voltage_LV'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Voltage_HV1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Voltage_HV2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV1toLV'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV1toHV2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV1toLV_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Pwr_HV1toHV2_max'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Eta_HV1toLV'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PwrSupplyOut.Eta_HV1toHV2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1.rx'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1.ry'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1.rz'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1B.rx'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1B.ry'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2Bdy1B.rz'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2BdyEng.rx'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Trq_Supp2BdyEng.ry'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/DL_iDiff_mean'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.FL.Inert_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.FL.Trq_Supp2WC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.FR.Inert_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.FR.Trq_Supp2WC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.RL.Inert_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.RL.Trq_Supp2WC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.RR.Inert_in'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/WheelOut.RR.Trq_Supp2WC'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.PlanetGear'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.Diffs'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.Shafts'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.Spring_DL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.Inert_DL'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.Inert'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/PowerDelta.PowerSupply'
   */
  0.0
};

const cmPowerTrainXWDOut MyPowerTrainXWD_rtZcmPowerTrainXWDOut = { 0.0,/* ECU_Status */
  { 0.0,                               /* Engine_on */
    0.0,                               /* rotv */
    0.0,                               /* Trq */
    0.0,                               /* TrqDrag */
    0.0,                               /* TrqFull */
    0.0,                               /* TrqOpt */
    0.0                                /* FuelFlow */
  },                                   /* EngineOut */
  0.0,                                 /* MCU_Status */

  { 0.0,                               /* rotv */
    0.0,                               /* Trq */
    0.0,                               /* TrqMot_max */
    0.0,                               /* TrqGen_max */
    0.0,                               /* PwrElec */

    { 0.0,                             /* FL */
      0.0,                             /* FR */
      0.0,                             /* RL */
      0.0                              /* RR */
    }                                  /* i_M2W */
  },                                   /* ISGOut */

  { { 0.0,                             /* rotv */
      0.0,                             /* Trq */
      0.0,                             /* TrqMot_max */
      0.0,                             /* TrqGen_max */
      0.0,                             /* PwrElec */

      { 0.0,                           /* FL */
        0.0,                           /* FR */
        0.0,                           /* RL */
        0.0                            /* RR */
      }                                /* i_M2W */
    },                                 /* m0 */

    { 0.0,                             /* rotv */
      0.0,                             /* Trq */
      0.0,                             /* TrqMot_max */
      0.0,                             /* TrqGen_max */
      0.0,                             /* PwrElec */

      { 0.0,                           /* FL */
        0.0,                           /* FR */
        0.0,                           /* RL */
        0.0                            /* RR */
      }                                /* i_M2W */
    },                                 /* m1 */

    { 0.0,                             /* rotv */
      0.0,                             /* Trq */
      0.0,                             /* TrqMot_max */
      0.0,                             /* TrqGen_max */
      0.0,                             /* PwrElec */

      { 0.0,                           /* FL */
        0.0,                           /* FR */
        0.0,                           /* RL */
        0.0                            /* RR */
      }                                /* i_M2W */
    },                                 /* m2 */

    { 0.0,                             /* rotv */
      0.0,                             /* Trq */
      0.0,                             /* TrqMot_max */
      0.0,                             /* TrqGen_max */
      0.0,                             /* PwrElec */

      { 0.0,                           /* FL */
        0.0,                           /* FR */
        0.0,                           /* RL */
        0.0                            /* RR */
      }                                /* i_M2W */
    }                                  /* m3 */
  },                                   /* MotorOut */
  0.0,                                 /* TCU_Status */

  { 0.0,                               /* Pos */
    0.0,                               /* rotv_in */
    0.0,                               /* rotv_out */
    0.0,                               /* Trq_in */
    0.0,                               /* Trq_out */
    0.0                                /* i_TrqIn2Out */
  },                                   /* ClutchOut */

  { 0.0,                               /* GearNo */
    0.0,                               /* GearNo_dis */
    0.0,                               /* Trq_DriveSrc_trg */
    0.0,                               /* i */
    0.0,                               /* rotv_in */
    0.0,                               /* rotv_out */
    0.0,                               /* Trq_in */
    0.0,                               /* Trq_out */

    { 0.0,                             /* Pos */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */
      0.0                              /* i_TrqIn2Out */
    },                                 /* Clutch */

    { 0.0,                             /* Pos */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */
      0.0                              /* i_TrqIn2Out */
    }                                  /* Clutch_dis */
  },                                   /* GearBoxOut */

  { { 0.0,                             /* GearNo */
      0.0,                             /* GearNo_dis */
      0.0,                             /* Trq_DriveSrc_trg */
      0.0,                             /* i */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      },                               /* Clutch */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      }                                /* Clutch_dis */
    },                                 /* GB_m0 */

    { 0.0,                             /* GearNo */
      0.0,                             /* GearNo_dis */
      0.0,                             /* Trq_DriveSrc_trg */
      0.0,                             /* i */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      },                               /* Clutch */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      }                                /* Clutch_dis */
    },                                 /* GB_m1 */

    { 0.0,                             /* GearNo */
      0.0,                             /* GearNo_dis */
      0.0,                             /* Trq_DriveSrc_trg */
      0.0,                             /* i */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      },                               /* Clutch */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      }                                /* Clutch_dis */
    },                                 /* GB_m2 */

    { 0.0,                             /* GearNo */
      0.0,                             /* GearNo_dis */
      0.0,                             /* Trq_DriveSrc_trg */
      0.0,                             /* i */
      0.0,                             /* rotv_in */
      0.0,                             /* rotv_out */
      0.0,                             /* Trq_in */
      0.0,                             /* Trq_out */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      },                               /* Clutch */

      { 0.0,                           /* Pos */
        0.0,                           /* rotv_in */
        0.0,                           /* rotv_out */
        0.0,                           /* Trq_in */
        0.0,                           /* Trq_out */
        0.0                            /* i_TrqIn2Out */
      }                                /* Clutch_dis */
    }                                  /* GB_m3 */
  },                                   /* GearBoxM_Out */
  0.0,                                 /* BCU_Status */

  { 0.0,                               /* SOC */
    0.0,                               /* SOH */
    0.0,                               /* Current */
    0.0,                               /* AOC */
    0.0,                               /* Temp */
    0.0,                               /* Energy */
    0.0                                /* Pwr_max */
  },                                   /* BattLVOut */

  { 0.0,                               /* SOC */
    0.0,                               /* SOH */
    0.0,                               /* Current */
    0.0,                               /* AOC */
    0.0,                               /* Temp */
    0.0,                               /* Energy */
    0.0                                /* Pwr_max */
  },                                   /* BattHVOut */

  { 0.0,                               /* Pwr_LV */
    0.0,                               /* Pwr_HV1 */
    0.0,                               /* Pwr_HV2 */
    0.0,                               /* Voltage_LV */
    0.0,                               /* Voltage_HV1 */
    0.0,                               /* Voltage_HV2 */
    0.0,                               /* Pwr_HV1toLV */
    0.0,                               /* Pwr_HV1toHV2 */
    0.0,                               /* Pwr_HV1toLV_max */
    0.0,                               /* Pwr_HV1toHV2_max */
    0.0,                               /* Eta_HV1toLV */
    0.0                                /* Eta_HV1toHV2 */
  },                                   /* PwrSupplyOut */

  { 0.0,                               /* rx */
    0.0,                               /* ry */
    0.0                                /* rz */
  },                                   /* Trq_Supp2Bdy1 */

  { 0.0,                               /* rx */
    0.0,                               /* ry */
    0.0                                /* rz */
  },                                   /* Trq_Supp2Bdy1B */

  { 0.0,                               /* rx */
    0.0                                /* ry */
  },                                   /* Trq_Supp2BdyEng */
  0.0,                                 /* DL_iDiff_mean */

  { { 0.0,                             /* Inert_in */
      0.0,                             /* Trq_Drive */
      0.0                              /* Trq_Supp2WC */
    },                                 /* FL */

    { 0.0,                             /* Inert_in */
      0.0,                             /* Trq_Drive */
      0.0                              /* Trq_Supp2WC */
    },                                 /* FR */

    { 0.0,                             /* Inert_in */
      0.0,                             /* Trq_Drive */
      0.0                              /* Trq_Supp2WC */
    },                                 /* RL */

    { 0.0,                             /* Inert_in */
      0.0,                             /* Trq_Drive */
      0.0                              /* Trq_Supp2WC */
    }                                  /* RR */
  },                                   /* WheelOut */

  { 0.0,                               /* PlanetGear */
    0.0,                               /* Diffs */
    0.0,                               /* Shafts */
    0.0,                               /* Spring_DL */
    0.0,                               /* Inert_DL */
    0.0,                               /* Inert */
    0.0                                /* PowerSupply */
  }                                    /* PowerDelta */
};

/* Model step function */
void MyPowerTrainXWD_step(RT_MODEL_MyPowerTrainXWD_T *const MyPowerTrainXWD_M)
{
  ExtU_MyPowerTrainXWD_T *MyPowerTrainXWD_U = (ExtU_MyPowerTrainXWD_T *)
    MyPowerTrainXWD_M->inputs;
  ExtY_MyPowerTrainXWD_T *MyPowerTrainXWD_Y = (ExtY_MyPowerTrainXWD_T *)
    MyPowerTrainXWD_M->outputs;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/EngineOut.Engine_on'
   *  Constant: '<S1>/EngineOut.FuelFlow'
   *  Constant: '<S1>/EngineOut.Trq'
   *  Constant: '<S1>/EngineOut.TrqDrag'
   *  Constant: '<S1>/EngineOut.TrqFull'
   *  Constant: '<S1>/EngineOut.TrqOpt'
   *  Constant: '<S1>/EngineOut.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.EngineOut.Engine_on =
    MyPowerTrainXWD_P.EngineOutEngine_on_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.rotv = MyPowerTrainXWD_P.EngineOutrotv_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.Trq = MyPowerTrainXWD_P.EngineOutTrq_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.TrqDrag =
    MyPowerTrainXWD_P.EngineOutTrqDrag_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.TrqFull =
    MyPowerTrainXWD_P.EngineOutTrqFull_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.TrqOpt =
    MyPowerTrainXWD_P.EngineOutTrqOpt_Value;
  MyPowerTrainXWD_Y->ToCM.EngineOut.FuelFlow =
    MyPowerTrainXWD_P.EngineOutFuelFlow_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/ISGOut.i_M2W.FL'
   *  Constant: '<S1>/ISGOut.i_M2W.FR'
   *  Constant: '<S1>/ISGOut.i_M2W.RL'
   *  Constant: '<S1>/ISGOut.i_M2W.RR'
   */
  MyPowerTrainXWD_Y->ToCM.ISGOut.i_M2W.FL =
    MyPowerTrainXWD_P.ISGOuti_M2WFL_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.i_M2W.FR =
    MyPowerTrainXWD_P.ISGOuti_M2WFR_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.i_M2W.RL =
    MyPowerTrainXWD_P.ISGOuti_M2WRL_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.i_M2W.RR =
    MyPowerTrainXWD_P.ISGOuti_M2WRR_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/ISGOut.PwrElec'
   *  Constant: '<S1>/ISGOut.Trq'
   *  Constant: '<S1>/ISGOut.TrqGen_max'
   *  Constant: '<S1>/ISGOut.TrqMot_max'
   *  Constant: '<S1>/ISGOut.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.ISGOut.rotv = MyPowerTrainXWD_P.ISGOutrotv_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.Trq = MyPowerTrainXWD_P.ISGOutTrq_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.TrqMot_max =
    MyPowerTrainXWD_P.ISGOutTrqMot_max_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.TrqGen_max =
    MyPowerTrainXWD_P.ISGOutTrqGen_max_Value;
  MyPowerTrainXWD_Y->ToCM.ISGOut.PwrElec = MyPowerTrainXWD_P.ISGOutPwrElec_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m0.i_M2W.FL'
   *  Constant: '<S1>/MotorOut.m0.i_M2W.FR'
   *  Constant: '<S1>/MotorOut.m0.i_M2W.RL'
   *  Constant: '<S1>/MotorOut.m0.i_M2W.RR'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.i_M2W.FL =
    MyPowerTrainXWD_P.MotorOutm0i_M2WFL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.i_M2W.FR =
    MyPowerTrainXWD_P.MotorOutm0i_M2WFR_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.i_M2W.RL =
    MyPowerTrainXWD_P.MotorOutm0i_M2WRL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.i_M2W.RR =
    MyPowerTrainXWD_P.MotorOutm0i_M2WRR_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m0.PwrElec'
   *  Constant: '<S1>/MotorOut.m0.Trq'
   *  Constant: '<S1>/MotorOut.m0.TrqGen_max'
   *  Constant: '<S1>/MotorOut.m0.TrqMot_max'
   *  Constant: '<S1>/MotorOut.m0.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.rotv =
    MyPowerTrainXWD_P.MotorOutm0rotv_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.Trq =
    MyPowerTrainXWD_P.MotorOutm0Trq_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.TrqMot_max =
    MyPowerTrainXWD_P.MotorOutm0TrqMot_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.TrqGen_max =
    MyPowerTrainXWD_P.MotorOutm0TrqGen_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m0.PwrElec =
    MyPowerTrainXWD_P.MotorOutm0PwrElec_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m1.i_M2W.FL'
   *  Constant: '<S1>/MotorOut.m1.i_M2W.FR'
   *  Constant: '<S1>/MotorOut.m1.i_M2W.RL'
   *  Constant: '<S1>/MotorOut.m1.i_M2W.RR'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.i_M2W.FL =
    MyPowerTrainXWD_P.MotorOutm1i_M2WFL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.i_M2W.FR =
    MyPowerTrainXWD_P.MotorOutm1i_M2WFR_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.i_M2W.RL =
    MyPowerTrainXWD_P.MotorOutm1i_M2WRL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.i_M2W.RR =
    MyPowerTrainXWD_P.MotorOutm1i_M2WRR_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m1.PwrElec'
   *  Constant: '<S1>/MotorOut.m1.Trq'
   *  Constant: '<S1>/MotorOut.m1.TrqGen_max'
   *  Constant: '<S1>/MotorOut.m1.TrqMot_max'
   *  Constant: '<S1>/MotorOut.m1.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.rotv =
    MyPowerTrainXWD_P.MotorOutm1rotv_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.Trq =
    MyPowerTrainXWD_P.MotorOutm1Trq_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.TrqMot_max =
    MyPowerTrainXWD_P.MotorOutm1TrqMot_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.TrqGen_max =
    MyPowerTrainXWD_P.MotorOutm1TrqGen_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m1.PwrElec =
    MyPowerTrainXWD_P.MotorOutm1PwrElec_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m2.i_M2W.FL'
   *  Constant: '<S1>/MotorOut.m2.i_M2W.FR'
   *  Constant: '<S1>/MotorOut.m2.i_M2W.RL'
   *  Constant: '<S1>/MotorOut.m2.i_M2W.RR'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.i_M2W.FL =
    MyPowerTrainXWD_P.MotorOutm2i_M2WFL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.i_M2W.FR =
    MyPowerTrainXWD_P.MotorOutm2i_M2WFR_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.i_M2W.RL =
    MyPowerTrainXWD_P.MotorOutm2i_M2WRL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.i_M2W.RR =
    MyPowerTrainXWD_P.MotorOutm2i_M2WRR_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m2.PwrElec'
   *  Constant: '<S1>/MotorOut.m2.Trq'
   *  Constant: '<S1>/MotorOut.m2.TrqGen_max'
   *  Constant: '<S1>/MotorOut.m2.TrqMot_max'
   *  Constant: '<S1>/MotorOut.m2.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.rotv =
    MyPowerTrainXWD_P.MotorOutm2rotv_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.Trq =
    MyPowerTrainXWD_P.MotorOutm2Trq_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.TrqMot_max =
    MyPowerTrainXWD_P.MotorOutm2TrqMot_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.TrqGen_max =
    MyPowerTrainXWD_P.MotorOutm2TrqGen_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m2.PwrElec =
    MyPowerTrainXWD_P.MotorOutm2PwrElec_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m3.i_M2W.FL'
   *  Constant: '<S1>/MotorOut.m3.i_M2W.FR'
   *  Constant: '<S1>/MotorOut.m3.i_M2W.RL'
   *  Constant: '<S1>/MotorOut.m3.i_M2W.RR'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.i_M2W.FL =
    MyPowerTrainXWD_P.MotorOutm3i_M2WFL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.i_M2W.FR =
    MyPowerTrainXWD_P.MotorOutm3i_M2WFR_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.i_M2W.RL =
    MyPowerTrainXWD_P.MotorOutm3i_M2WRL_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.i_M2W.RR =
    MyPowerTrainXWD_P.MotorOutm3i_M2WRR_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/MotorOut.m3.PwrElec'
   *  Constant: '<S1>/MotorOut.m3.Trq'
   *  Constant: '<S1>/MotorOut.m3.TrqGen_max'
   *  Constant: '<S1>/MotorOut.m3.TrqMot_max'
   *  Constant: '<S1>/MotorOut.m3.rotv'
   */
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.rotv =
    MyPowerTrainXWD_P.MotorOutm3rotv_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.Trq =
    MyPowerTrainXWD_P.MotorOutm3Trq_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.TrqMot_max =
    MyPowerTrainXWD_P.MotorOutm3TrqMot_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.TrqGen_max =
    MyPowerTrainXWD_P.MotorOutm3TrqGen_max_Value;
  MyPowerTrainXWD_Y->ToCM.MotorOut.m3.PwrElec =
    MyPowerTrainXWD_P.MotorOutm3PwrElec_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/ClutchOut.Pos'
   *  Constant: '<S1>/ClutchOut.Trq_in'
   *  Constant: '<S1>/ClutchOut.Trq_out'
   *  Constant: '<S1>/ClutchOut.i_TrqIn2Out'
   *  Constant: '<S1>/ClutchOut.rotv_in'
   *  Constant: '<S1>/ClutchOut.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.ClutchOut.Pos = MyPowerTrainXWD_P.ClutchOutPos_Value;
  MyPowerTrainXWD_Y->ToCM.ClutchOut.rotv_in =
    MyPowerTrainXWD_P.ClutchOutrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.ClutchOut.rotv_out =
    MyPowerTrainXWD_P.ClutchOutrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.ClutchOut.Trq_in =
    MyPowerTrainXWD_P.ClutchOutTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.ClutchOut.Trq_out =
    MyPowerTrainXWD_P.ClutchOutTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.ClutchOut.i_TrqIn2Out =
    MyPowerTrainXWD_P.ClutchOuti_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/GearBoxOut.Clutch.Pos'
   *  Constant: '<S1>/GearBoxOut.Clutch.Trq_in'
   *  Constant: '<S1>/GearBoxOut.Clutch.Trq_out'
   *  Constant: '<S1>/GearBoxOut.Clutch.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxOut.Clutch.rotv_in'
   *  Constant: '<S1>/GearBoxOut.Clutch.rotv_out'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.Pos'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.Trq_in'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.Trq_out'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.rotv_in'
   *  Constant: '<S1>/GearBoxOut.Clutch_dis.rotv_out'
   *  Constant: '<S1>/GearBoxOut.GearNo'
   *  Constant: '<S1>/GearBoxOut.GearNo_dis'
   *  Constant: '<S1>/GearBoxOut.Trq_DriveSrc_trg'
   *  Constant: '<S1>/GearBoxOut.Trq_in'
   *  Constant: '<S1>/GearBoxOut.Trq_out'
   *  Constant: '<S1>/GearBoxOut.i'
   *  Constant: '<S1>/GearBoxOut.rotv_in'
   *  Constant: '<S1>/GearBoxOut.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.GearNo =
    MyPowerTrainXWD_P.GearBoxOutGearNo_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.GearNo_dis =
    MyPowerTrainXWD_P.GearBoxOutGearNo_dis_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Trq_DriveSrc_trg =
    MyPowerTrainXWD_P.GearBoxOutTrq_DriveSrc_trg_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.i = MyPowerTrainXWD_P.GearBoxOuti_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.rotv_in =
    MyPowerTrainXWD_P.GearBoxOutrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.rotv_out =
    MyPowerTrainXWD_P.GearBoxOutrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Trq_in =
    MyPowerTrainXWD_P.GearBoxOutTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Trq_out =
    MyPowerTrainXWD_P.GearBoxOutTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.Pos =
    MyPowerTrainXWD_P.GearBoxOutClutchPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.rotv_in =
    MyPowerTrainXWD_P.GearBoxOutClutchrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.rotv_out =
    MyPowerTrainXWD_P.GearBoxOutClutchrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.Trq_in =
    MyPowerTrainXWD_P.GearBoxOutClutchTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.Trq_out =
    MyPowerTrainXWD_P.GearBoxOutClutchTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxOutClutchi_TrqIn2Out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.Pos =
    MyPowerTrainXWD_P.GearBoxOutClutch_disPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.rotv_in =
    MyPowerTrainXWD_P.GearBoxOutClutch_disrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.rotv_out =
    MyPowerTrainXWD_P.GearBoxOutClutch_disrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.Trq_in =
    MyPowerTrainXWD_P.GearBoxOutClutch_disTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.Trq_out =
    MyPowerTrainXWD_P.GearBoxOutClutch_disTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxOut.Clutch_dis.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxOutClutch_disi_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Clutch_dis.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.GearNo'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.GearNo_dis'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Trq_DriveSrc_trg'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.i'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m0.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.GearNo =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0GearNo_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.GearNo_dis =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0GearNo_dis_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Trq_DriveSrc_trg =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Trq_DriveSrc_trg_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.i =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0i_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0rotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0rotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Trq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Trq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0ClutchPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutchrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutchrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0ClutchTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0ClutchTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutchi_TrqIn2Out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m0Clutch_disi_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Clutch_dis.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.GearNo'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.GearNo_dis'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Trq_DriveSrc_trg'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.i'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m1.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.GearNo =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1GearNo_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.GearNo_dis =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1GearNo_dis_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Trq_DriveSrc_trg =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Trq_DriveSrc_trg_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.i =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1i_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1rotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1rotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Trq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Trq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1ClutchPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutchrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutchrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1ClutchTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1ClutchTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutchi_TrqIn2Out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m1Clutch_disi_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Clutch_dis.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.GearNo'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.GearNo_dis'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Trq_DriveSrc_trg'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.i'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m2.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.GearNo =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2GearNo_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.GearNo_dis =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2GearNo_dis_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Trq_DriveSrc_trg =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Trq_DriveSrc_trg_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.i =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2i_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2rotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2rotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Trq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Trq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2ClutchPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutchrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutchrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2ClutchTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2ClutchTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutchi_TrqIn2Out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m2Clutch_disi_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Pos'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.i_TrqIn2Out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Clutch_dis.rotv_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.GearNo'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.GearNo_dis'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Trq_DriveSrc_trg'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Trq_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.Trq_out'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.i'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.rotv_in'
   *  Constant: '<S1>/GearBoxM_Out.GB_m3.rotv_out'
   */
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.GearNo =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3GearNo_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.GearNo_dis =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3GearNo_dis_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Trq_DriveSrc_trg =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Trq_DriveSrc_trg_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.i =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3i_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3rotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3rotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Trq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Trq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3ClutchPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutchrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutchrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3ClutchTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3ClutchTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutchi_TrqIn2Out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Pos =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disPos_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.rotv_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disrotv_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.rotv_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disrotv_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Trq_in =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disTrq_in_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Trq_out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disTrq_out_Value;
  MyPowerTrainXWD_Y->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.i_TrqIn2Out =
    MyPowerTrainXWD_P.GearBoxM_OutGB_m3Clutch_disi_TrqIn2Out_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/BattLVOut.AOC'
   *  Constant: '<S1>/BattLVOut.Current'
   *  Constant: '<S1>/BattLVOut.Energy'
   *  Constant: '<S1>/BattLVOut.Pwr_max'
   *  Constant: '<S1>/BattLVOut.SOC'
   *  Constant: '<S1>/BattLVOut.SOH'
   *  Constant: '<S1>/BattLVOut.Temp'
   */
  MyPowerTrainXWD_Y->ToCM.BattLVOut.SOC = MyPowerTrainXWD_P.BattLVOutSOC_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.SOH = MyPowerTrainXWD_P.BattLVOutSOH_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.Current =
    MyPowerTrainXWD_P.BattLVOutCurrent_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.AOC = MyPowerTrainXWD_P.BattLVOutAOC_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.Temp = MyPowerTrainXWD_P.BattLVOutTemp_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.Energy =
    MyPowerTrainXWD_P.BattLVOutEnergy_Value;
  MyPowerTrainXWD_Y->ToCM.BattLVOut.Pwr_max =
    MyPowerTrainXWD_P.BattLVOutPwr_max_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/BattHVOut.AOC'
   *  Constant: '<S1>/BattHVOut.Current'
   *  Constant: '<S1>/BattHVOut.Energy'
   *  Constant: '<S1>/BattHVOut.Pwr_max'
   *  Constant: '<S1>/BattHVOut.SOC'
   *  Constant: '<S1>/BattHVOut.SOH'
   *  Constant: '<S1>/BattHVOut.Temp'
   */
  MyPowerTrainXWD_Y->ToCM.BattHVOut.SOC = MyPowerTrainXWD_P.BattHVOutSOC_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.SOH = MyPowerTrainXWD_P.BattHVOutSOH_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.Current =
    MyPowerTrainXWD_P.BattHVOutCurrent_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.AOC = MyPowerTrainXWD_P.BattHVOutAOC_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.Temp = MyPowerTrainXWD_P.BattHVOutTemp_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.Energy =
    MyPowerTrainXWD_P.BattHVOutEnergy_Value;
  MyPowerTrainXWD_Y->ToCM.BattHVOut.Pwr_max =
    MyPowerTrainXWD_P.BattHVOutPwr_max_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/PwrSupplyOut.Eta_HV1toHV2'
   *  Constant: '<S1>/PwrSupplyOut.Eta_HV1toLV'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV1'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV1toHV2'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV1toHV2_max'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV1toLV'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV1toLV_max'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_HV2'
   *  Constant: '<S1>/PwrSupplyOut.Pwr_LV'
   *  Constant: '<S1>/PwrSupplyOut.Voltage_HV1'
   *  Constant: '<S1>/PwrSupplyOut.Voltage_HV2'
   *  Constant: '<S1>/PwrSupplyOut.Voltage_LV'
   */
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_LV =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_LV_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV1 =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV1_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV2 =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV2_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Voltage_LV =
    MyPowerTrainXWD_P.PwrSupplyOutVoltage_LV_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Voltage_HV1 =
    MyPowerTrainXWD_P.PwrSupplyOutVoltage_HV1_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Voltage_HV2 =
    MyPowerTrainXWD_P.PwrSupplyOutVoltage_HV2_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV1toLV =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV1toLV_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV1toHV2 =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV1toHV2_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV1toLV_max =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV1toLV_max_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Pwr_HV1toHV2_max =
    MyPowerTrainXWD_P.PwrSupplyOutPwr_HV1toHV2_max_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Eta_HV1toLV =
    MyPowerTrainXWD_P.PwrSupplyOutEta_HV1toLV_Value;
  MyPowerTrainXWD_Y->ToCM.PwrSupplyOut.Eta_HV1toHV2 =
    MyPowerTrainXWD_P.PwrSupplyOutEta_HV1toHV2_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/Trq_Supp2BdyEng.rx'
   *  Constant: '<S1>/Trq_Supp2BdyEng.ry'
   */
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2BdyEng.rx =
    MyPowerTrainXWD_P.Trq_Supp2BdyEngrx_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2BdyEng.ry =
    MyPowerTrainXWD_P.Trq_Supp2BdyEngry_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/WheelOut.FL.Inert_in'
   *  Constant: '<S1>/WheelOut.FL.Trq_Supp2WC'
   *  Inport: '<Root>/FromCM'
   */
  MyPowerTrainXWD_Y->ToCM.WheelOut.FL.Inert_in =
    MyPowerTrainXWD_P.WheelOutFLInert_in_Value;
  MyPowerTrainXWD_Y->ToCM.WheelOut.FL.Trq_Drive =
    MyPowerTrainXWD_U->FromCM.MotorIn.m0.Trq_trg;
  MyPowerTrainXWD_Y->ToCM.WheelOut.FL.Trq_Supp2WC =
    MyPowerTrainXWD_P.WheelOutFLTrq_Supp2WC_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/WheelOut.FR.Inert_in'
   *  Constant: '<S1>/WheelOut.FR.Trq_Supp2WC'
   *  Inport: '<Root>/FromCM'
   */
  MyPowerTrainXWD_Y->ToCM.WheelOut.FR.Inert_in =
    MyPowerTrainXWD_P.WheelOutFRInert_in_Value;
  MyPowerTrainXWD_Y->ToCM.WheelOut.FR.Trq_Drive =
    MyPowerTrainXWD_U->FromCM.MotorIn.m1.Trq_trg;
  MyPowerTrainXWD_Y->ToCM.WheelOut.FR.Trq_Supp2WC =
    MyPowerTrainXWD_P.WheelOutFRTrq_Supp2WC_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/WheelOut.RL.Inert_in'
   *  Constant: '<S1>/WheelOut.RL.Trq_Supp2WC'
   *  Inport: '<Root>/FromCM'
   */
  MyPowerTrainXWD_Y->ToCM.WheelOut.RL.Inert_in =
    MyPowerTrainXWD_P.WheelOutRLInert_in_Value;
  MyPowerTrainXWD_Y->ToCM.WheelOut.RL.Trq_Drive =
    MyPowerTrainXWD_U->FromCM.MotorIn.m2.Trq_trg;
  MyPowerTrainXWD_Y->ToCM.WheelOut.RL.Trq_Supp2WC =
    MyPowerTrainXWD_P.WheelOutRLTrq_Supp2WC_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/WheelOut.RR.Inert_in'
   *  Constant: '<S1>/WheelOut.RR.Trq_Supp2WC'
   *  Inport: '<Root>/FromCM'
   */
  MyPowerTrainXWD_Y->ToCM.WheelOut.RR.Inert_in =
    MyPowerTrainXWD_P.WheelOutRRInert_in_Value;
  MyPowerTrainXWD_Y->ToCM.WheelOut.RR.Trq_Drive =
    MyPowerTrainXWD_U->FromCM.MotorIn.m3.Trq_trg;
  MyPowerTrainXWD_Y->ToCM.WheelOut.RR.Trq_Supp2WC =
    MyPowerTrainXWD_P.WheelOutRRTrq_Supp2WC_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/PowerDelta.Diffs'
   *  Constant: '<S1>/PowerDelta.Inert'
   *  Constant: '<S1>/PowerDelta.Inert_DL'
   *  Constant: '<S1>/PowerDelta.PlanetGear'
   *  Constant: '<S1>/PowerDelta.PowerSupply'
   *  Constant: '<S1>/PowerDelta.Shafts'
   *  Constant: '<S1>/PowerDelta.Spring_DL'
   */
  MyPowerTrainXWD_Y->ToCM.PowerDelta.PlanetGear =
    MyPowerTrainXWD_P.PowerDeltaPlanetGear_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.Diffs =
    MyPowerTrainXWD_P.PowerDeltaDiffs_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.Shafts =
    MyPowerTrainXWD_P.PowerDeltaShafts_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.Spring_DL =
    MyPowerTrainXWD_P.PowerDeltaSpring_DL_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.Inert_DL =
    MyPowerTrainXWD_P.PowerDeltaInert_DL_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.Inert =
    MyPowerTrainXWD_P.PowerDeltaInert_Value;
  MyPowerTrainXWD_Y->ToCM.PowerDelta.PowerSupply =
    MyPowerTrainXWD_P.PowerDeltaPowerSupply_Value;

  /* BusCreator generated from: '<Root>/ToCM' incorporates:
   *  Constant: '<S1>/BCU_Status'
   *  Constant: '<S1>/DL_iDiff_mean'
   *  Constant: '<S1>/ECU_Status'
   *  Constant: '<S1>/MCU_Status'
   *  Constant: '<S1>/TCU_Status'
   *  Constant: '<S1>/Trq_Supp2Bdy1.rx'
   *  Constant: '<S1>/Trq_Supp2Bdy1.ry'
   *  Constant: '<S1>/Trq_Supp2Bdy1.rz'
   *  Constant: '<S1>/Trq_Supp2Bdy1B.rx'
   *  Constant: '<S1>/Trq_Supp2Bdy1B.ry'
   *  Constant: '<S1>/Trq_Supp2Bdy1B.rz'
   *  Outport: '<Root>/ToCM'
   */
  MyPowerTrainXWD_Y->ToCM.ECU_Status = MyPowerTrainXWD_P.ECU_Status_Value;
  MyPowerTrainXWD_Y->ToCM.MCU_Status = MyPowerTrainXWD_P.MCU_Status_Value;
  MyPowerTrainXWD_Y->ToCM.TCU_Status = MyPowerTrainXWD_P.TCU_Status_Value;
  MyPowerTrainXWD_Y->ToCM.BCU_Status = MyPowerTrainXWD_P.BCU_Status_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1.rx =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1rx_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1.ry =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1ry_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1.rz =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1rz_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1B.rx =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1Brx_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1B.ry =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1Bry_Value;
  MyPowerTrainXWD_Y->ToCM.Trq_Supp2Bdy1B.rz =
    MyPowerTrainXWD_P.Trq_Supp2Bdy1Brz_Value;
  MyPowerTrainXWD_Y->ToCM.DL_iDiff_mean = MyPowerTrainXWD_P.DL_iDiff_mean_Value;
}

/* Model initialize function */
void MyPowerTrainXWD_initialize(RT_MODEL_MyPowerTrainXWD_T *const
  MyPowerTrainXWD_M)
{
  UNUSED_PARAMETER(MyPowerTrainXWD_M);
}

/* Model terminate function */
void MyPowerTrainXWD_terminate(RT_MODEL_MyPowerTrainXWD_T * MyPowerTrainXWD_M)
{
  /* model code */
  rt_FREE(MyPowerTrainXWD_M->inputs);
  rt_FREE(MyPowerTrainXWD_M->outputs);
  rt_FREE(MyPowerTrainXWD_M);
}

/* Model data allocation function */
RT_MODEL_MyPowerTrainXWD_T *MyPowerTrainXWD(struct tInfos *inf)
{
  RT_MODEL_MyPowerTrainXWD_T *MyPowerTrainXWD_M;
  MyPowerTrainXWD_M = (RT_MODEL_MyPowerTrainXWD_T *) malloc(sizeof
    (RT_MODEL_MyPowerTrainXWD_T));
  if (MyPowerTrainXWD_M == (NULL)) {
    return (NULL);
  }

  (void) memset((char *)MyPowerTrainXWD_M, 0,
                sizeof(RT_MODEL_MyPowerTrainXWD_T));
  MatSupp_Init();

  /* external inputs */
  {
    ExtU_MyPowerTrainXWD_T *MyPowerTrainXWD_U = (ExtU_MyPowerTrainXWD_T *)
      malloc(sizeof(ExtU_MyPowerTrainXWD_T));
    rt_VALIDATE_MEMORY(MyPowerTrainXWD_M,MyPowerTrainXWD_U);
    MyPowerTrainXWD_M->inputs = (((ExtU_MyPowerTrainXWD_T *) MyPowerTrainXWD_U));
  }

  /* external outputs */
  {
    ExtY_MyPowerTrainXWD_T *MyPowerTrainXWD_Y = (ExtY_MyPowerTrainXWD_T *)
      malloc(sizeof(ExtY_MyPowerTrainXWD_T));
    rt_VALIDATE_MEMORY(MyPowerTrainXWD_M,MyPowerTrainXWD_Y);
    MyPowerTrainXWD_M->outputs = (MyPowerTrainXWD_Y);
  }

  /* CarMaker parameter tuning */
  {
    MyPowerTrainXWD_SetParams(MyPowerTrainXWD_M, NULL, inf);
  }

  {
    ExtU_MyPowerTrainXWD_T *MyPowerTrainXWD_U = (ExtU_MyPowerTrainXWD_T *)
      MyPowerTrainXWD_M->inputs;
    ExtY_MyPowerTrainXWD_T *MyPowerTrainXWD_Y = (ExtY_MyPowerTrainXWD_T *)
      MyPowerTrainXWD_M->outputs;

    /* external inputs */
    (void)memset(MyPowerTrainXWD_U, 0, sizeof(ExtU_MyPowerTrainXWD_T));

    /* external outputs */
    MyPowerTrainXWD_Y->ToCM = MyPowerTrainXWD_rtZcmPowerTrainXWDOut;
  }

  return MyPowerTrainXWD_M;
}

/* CarMaker dictionary definitions. */
extern tQuantEntry *MyPowerTrainXWD_main_DictDefines[];
static tQuantEntry DictDefines[] = {
  { (void*)0x01234567, (void*)0x89ABCDEF, NULL, 0, 0, 0, "", 0.0, 0.0 },

  { (void*)MyPowerTrainXWD_main_DictDefines, NULL, NULL, 0, 0, 0, "", 0.0, 0.0 },

  { NULL, NULL, NULL, 0, 0, 0, "", 0.0, 0.0 }
};

tQuantEntry *MyPowerTrainXWD_DictDefines = DictDefines;
tQuantEntry *MyPowerTrainXWD_main_DictDefines[] = {
  DictDefines,
  NULL
};

/* CarMaker bodyframe definitions. */
#ifndef RTMAKER

extern tMdlBdyFrame *MyPowerTrainXWD_main_BdyFrameDefines[];
static tMdlBdyFrame BdyFrameDefines[] = {
  { (void*)0x01234567 },

  { (void*)0x89ABCDEF },

  { (void*)MyPowerTrainXWD_main_BdyFrameDefines },

  { NULL }
};

tMdlBdyFrame *MyPowerTrainXWD_BdyFrameDefines = BdyFrameDefines;
tMdlBdyFrame *MyPowerTrainXWD_main_BdyFrameDefines[] = {
  BdyFrameDefines,
  NULL
};

#endif
