/*
 * MyPowerTrainXWD_types.h
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

#ifndef RTW_HEADER_MyPowerTrainXWD_types_h_
#define RTW_HEADER_MyPowerTrainXWD_types_h_
#include "rtwtypes.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_cm8EngineIn_
#define DEFINED_TYPEDEF_FOR_cm8EngineIn_

typedef struct {
  real_T set_ISC;
  real_T FuelCutOff;
  real_T Load;
  real_T Trq_trg;
  real_T rotv_trg;
} cm8EngineIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8MotorIn_
#define DEFINED_TYPEDEF_FOR_cm8MotorIn_

typedef struct {
  real_T Load;
  real_T Trq_trg;
  real_T rotv_trg;
} cm8MotorIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8MotorInArray_
#define DEFINED_TYPEDEF_FOR_cm8MotorInArray_

typedef struct {
  cm8MotorIn m0;
  cm8MotorIn m1;
  cm8MotorIn m2;
  cm8MotorIn m3;
} cm8MotorInArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8ClutchIn_
#define DEFINED_TYPEDEF_FOR_cm8ClutchIn_

typedef struct {
  real_T Pos;
  real_T rotv_out_trg;
  real_T Trq_out_trg;
} cm8ClutchIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GearBoxIn_
#define DEFINED_TYPEDEF_FOR_cm8GearBoxIn_

typedef struct {
  real_T GearNoTrg;
  real_T GearNoTrg_dis;
  real_T i_trg;
  real_T set_ParkBrake;
  real_T rotv_in_trg;
  real_T Trq_out_trg;
  cm8ClutchIn Clutch;
  cm8ClutchIn Clutch_dis;
} cm8GearBoxIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GearBoxInArray_
#define DEFINED_TYPEDEF_FOR_cm8GearBoxInArray_

typedef struct {
  cm8GearBoxIn GB_m0;
  cm8GearBoxIn GB_m1;
  cm8GearBoxIn GB_m2;
  cm8GearBoxIn GB_m3;
} cm8GearBoxInArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8PwrSupplyIn_
#define DEFINED_TYPEDEF_FOR_cm8PwrSupplyIn_

typedef struct {
  real_T Pwr_HV1toLV_trg;
} cm8PwrSupplyIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8WheelIn_
#define DEFINED_TYPEDEF_FOR_cm8WheelIn_

typedef struct {
  real_T rot;
  real_T rotv;
} cm8WheelIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8WheelInArray_
#define DEFINED_TYPEDEF_FOR_cm8WheelInArray_

typedef struct {
  cm8WheelIn FL;
  cm8WheelIn FR;
  cm8WheelIn RL;
  cm8WheelIn RR;
} cm8WheelInArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cmPowerTrainXWDIn_
#define DEFINED_TYPEDEF_FOR_cmPowerTrainXWDIn_

typedef struct {
  real_T Ignition;
  real_T Gas;
  real_T SelectorCtrl;
  real_T Velocity;
  cm8EngineIn EngineIn;
  cm8MotorIn ISGIn;
  cm8MotorInArray MotorIn;
  cm8ClutchIn ClutchIn;
  cm8GearBoxIn GearBoxIn;
  cm8GearBoxInArray GearBoxM_In;
  cm8PwrSupplyIn PwrSupplyIn;
  cm8WheelInArray WheelIn;
} cmPowerTrainXWDIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cmPowerTrainXWDCfgIn_
#define DEFINED_TYPEDEF_FOR_cmPowerTrainXWDCfgIn_

typedef struct {
  real_T nWheels;
} cmPowerTrainXWDCfgIn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8DriveSourceArray_
#define DEFINED_TYPEDEF_FOR_cm8DriveSourceArray_

typedef struct {
  real_T d0;
  real_T d1;
  real_T d2;
  real_T d3;
} cm8DriveSourceArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8DriveLine_
#define DEFINED_TYPEDEF_FOR_cm8DriveLine_

typedef struct {
  real_T iDiff_mean;
  cm8DriveSourceArray DriveSourcePos;
} cm8DriveLine;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8FGearArray_
#define DEFINED_TYPEDEF_FOR_cm8FGearArray_

typedef struct {
  real_T Gear1;
  real_T Gear2;
  real_T Gear3;
  real_T Gear4;
  real_T Gear5;
  real_T Gear6;
  real_T Gear7;
  real_T Gear8;
  real_T Gear9;
  real_T Gear10;
  real_T Gear11;
  real_T Gear12;
  real_T Gear13;
  real_T Gear14;
  real_T Gear15;
  real_T Gear16;
} cm8FGearArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8BGearArray_
#define DEFINED_TYPEDEF_FOR_cm8BGearArray_

typedef struct {
  real_T Gear1;
  real_T Gear2;
  real_T Gear3;
  real_T Gear4;
} cm8BGearArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GBCfgOut_
#define DEFINED_TYPEDEF_FOR_cm8GBCfgOut_

typedef struct {
  real_T GBKind;
  real_T ClKind;
  real_T nFGears;
  cm8FGearArray iFGear;
  real_T nBGears;
  cm8BGearArray iBGear;
} cm8GBCfgOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GBMArray_
#define DEFINED_TYPEDEF_FOR_cm8GBMArray_

typedef struct {
  cm8GBCfgOut GB_m0;
  cm8GBCfgOut GB_m1;
  cm8GBCfgOut GB_m2;
  cm8GBCfgOut GB_m3;
} cm8GBMArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8PlanetGear_
#define DEFINED_TYPEDEF_FOR_cm8PlanetGear_

typedef struct {
  real_T Ratio;
} cm8PlanetGear;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8Batt_
#define DEFINED_TYPEDEF_FOR_cm8Batt_

typedef struct {
  real_T SOC_min;
  real_T SOC_max;
  real_T Capacity;
  real_T Voltage;
} cm8Batt;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8Map_
#define DEFINED_TYPEDEF_FOR_cm8Map_

typedef struct {
  real_T x[100];
  real_T z[100];
} cm8Map;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8Engine_
#define DEFINED_TYPEDEF_FOR_cm8Engine_

typedef struct {
  real_T Fuel_l2kWh;
  real_T rotv_off;
  real_T rotv_max;
  real_T rotv_idle;
  real_T rotv_opt;
  cm8Map TrqFull;
  cm8Map TrqDrag;
  cm8Map TrqOpt;
} cm8Engine;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8Motor_
#define DEFINED_TYPEDEF_FOR_cm8Motor_

typedef struct {
  real_T Level;
  real_T Ratio;
  cm8Map TrqMot_max;
  real_T rotv_Mot_max;
  cm8Map TrqGen_max;
  real_T rotv_Gen_max;
} cm8Motor;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8MotorArray_
#define DEFINED_TYPEDEF_FOR_cm8MotorArray_

typedef struct {
  cm8Motor m0;
  cm8Motor m1;
  cm8Motor m2;
  cm8Motor m3;
} cm8MotorArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cmPowerTrainXWDCfgOut_
#define DEFINED_TYPEDEF_FOR_cmPowerTrainXWDCfgOut_

typedef struct {
  real_T PTKind;
  real_T ClKind;
  real_T nMotor;
  real_T nGearBoxM;
  real_T nPlanetGear;
  cm8DriveLine DriveLine;
  cm8GBCfgOut GearBox;
  cm8GBMArray GearBoxM;
  cm8PlanetGear PlanetGear;
  cm8Batt BattLV;
  cm8Batt BattHV;
  cm8Engine Engine;
  cm8Motor ISG;
  cm8MotorArray Motor;
} cmPowerTrainXWDCfgOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8EngineOut_
#define DEFINED_TYPEDEF_FOR_cm8EngineOut_

typedef struct {
  real_T Engine_on;
  real_T rotv;
  real_T Trq;
  real_T TrqDrag;
  real_T TrqFull;
  real_T TrqOpt;
  real_T FuelFlow;
} cm8EngineOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8Wheels_
#define DEFINED_TYPEDEF_FOR_cm8Wheels_

typedef struct {
  real_T FL;
  real_T FR;
  real_T RL;
  real_T RR;
} cm8Wheels;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8MotorOut_
#define DEFINED_TYPEDEF_FOR_cm8MotorOut_

typedef struct {
  real_T rotv;
  real_T Trq;
  real_T TrqMot_max;
  real_T TrqGen_max;
  real_T PwrElec;
  cm8Wheels i_M2W;
} cm8MotorOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8MotorOutArray_
#define DEFINED_TYPEDEF_FOR_cm8MotorOutArray_

typedef struct {
  cm8MotorOut m0;
  cm8MotorOut m1;
  cm8MotorOut m2;
  cm8MotorOut m3;
} cm8MotorOutArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8ClutchOut_
#define DEFINED_TYPEDEF_FOR_cm8ClutchOut_

typedef struct {
  real_T Pos;
  real_T rotv_in;
  real_T rotv_out;
  real_T Trq_in;
  real_T Trq_out;
  real_T i_TrqIn2Out;
} cm8ClutchOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GearBoxOut_
#define DEFINED_TYPEDEF_FOR_cm8GearBoxOut_

typedef struct {
  real_T GearNo;
  real_T GearNo_dis;
  real_T Trq_DriveSrc_trg;
  real_T i;
  real_T rotv_in;
  real_T rotv_out;
  real_T Trq_in;
  real_T Trq_out;
  cm8ClutchOut Clutch;
  cm8ClutchOut Clutch_dis;
} cm8GearBoxOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8GearBoxOutArray_
#define DEFINED_TYPEDEF_FOR_cm8GearBoxOutArray_

typedef struct {
  cm8GearBoxOut GB_m0;
  cm8GearBoxOut GB_m1;
  cm8GearBoxOut GB_m2;
  cm8GearBoxOut GB_m3;
} cm8GearBoxOutArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8BattOut_
#define DEFINED_TYPEDEF_FOR_cm8BattOut_

typedef struct {
  real_T SOC;
  real_T SOH;
  real_T Current;
  real_T AOC;
  real_T Temp;
  real_T Energy;
  real_T Pwr_max;
} cm8BattOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8PwrSupplyOut_
#define DEFINED_TYPEDEF_FOR_cm8PwrSupplyOut_

typedef struct {
  real_T Pwr_LV;
  real_T Pwr_HV1;
  real_T Pwr_HV2;
  real_T Voltage_LV;
  real_T Voltage_HV1;
  real_T Voltage_HV2;
  real_T Pwr_HV1toLV;
  real_T Pwr_HV1toHV2;
  real_T Pwr_HV1toLV_max;
  real_T Pwr_HV1toHV2_max;
  real_T Eta_HV1toLV;
  real_T Eta_HV1toHV2;
} cm8PwrSupplyOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm83DTrq_
#define DEFINED_TYPEDEF_FOR_cm83DTrq_

typedef struct {
  real_T rx;
  real_T ry;
  real_T rz;
} cm83DTrq;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm82DTrq_
#define DEFINED_TYPEDEF_FOR_cm82DTrq_

typedef struct {
  real_T rx;
  real_T ry;
} cm82DTrq;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8WheelOut_
#define DEFINED_TYPEDEF_FOR_cm8WheelOut_

typedef struct {
  real_T Inert_in;
  real_T Trq_Drive;
  real_T Trq_Supp2WC;
} cm8WheelOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8WheelOutArray_
#define DEFINED_TYPEDEF_FOR_cm8WheelOutArray_

typedef struct {
  cm8WheelOut FL;
  cm8WheelOut FR;
  cm8WheelOut RL;
  cm8WheelOut RR;
} cm8WheelOutArray;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cm8PowerDelta_
#define DEFINED_TYPEDEF_FOR_cm8PowerDelta_

typedef struct {
  real_T PlanetGear;
  real_T Diffs;
  real_T Shafts;
  real_T Spring_DL;
  real_T Inert_DL;
  real_T Inert;
  real_T PowerSupply;
} cm8PowerDelta;

#endif

#ifndef DEFINED_TYPEDEF_FOR_cmPowerTrainXWDOut_
#define DEFINED_TYPEDEF_FOR_cmPowerTrainXWDOut_

typedef struct {
  real_T ECU_Status;
  cm8EngineOut EngineOut;
  real_T MCU_Status;
  cm8MotorOut ISGOut;
  cm8MotorOutArray MotorOut;
  real_T TCU_Status;
  cm8ClutchOut ClutchOut;
  cm8GearBoxOut GearBoxOut;
  cm8GearBoxOutArray GearBoxM_Out;
  real_T BCU_Status;
  cm8BattOut BattLVOut;
  cm8BattOut BattHVOut;
  cm8PwrSupplyOut PwrSupplyOut;
  cm83DTrq Trq_Supp2Bdy1;
  cm83DTrq Trq_Supp2Bdy1B;
  cm82DTrq Trq_Supp2BdyEng;
  real_T DL_iDiff_mean;
  cm8WheelOutArray WheelOut;
  cm8PowerDelta PowerDelta;
} cmPowerTrainXWDOut;

#endif

/* Parameters (default storage) */
typedef struct P_MyPowerTrainXWD_T_ P_MyPowerTrainXWD_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_MyPowerTrainXWD_T RT_MODEL_MyPowerTrainXWD_T;

#endif                                 /* RTW_HEADER_MyPowerTrainXWD_types_h_ */
