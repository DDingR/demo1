/***************************************************** target specific file ***/
/*  Wrapper module for Simulink models                                        */
/*  ------------------------------------------------------------------------  */
/*  (c) IPG Automotive GmbH    www.ipg-automotive.com   Fon: +49.721.98520-0  */
/*  Bannwaldallee 60      D-76185 Karlsruhe   Germany   Fax: +49.721.98520-99 */
/******************************************************************************/

#ifndef IS_CAR
# define IS_CAR
#endif

#include "Global.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "simstruc.h"
#include "rt_sim.h"
#include "simstruc_types.h"

#include "InfoUtils.h"
#include "SimCore.h"
#include "Log.h"
#include "MatSupp.h"
#include "ModelManager.h"
#include "LinMap.h"

#if defined (IS_CAR) || defined (IS_TRUCK)
# include "Car/PowerTrain.h"
#elif defined(IS_MCYCLE)
# include "MCycle/PowerTrain.h"
#endif

#include "MyPowerTrainXWD.h"
#include "MyPowerTrainXWD_wrap.h"


#define QUOTE1(name)	#name
#define QUOTE(name)	QUOTE1(name)		/* need to expand name */

#ifndef CLASSIC_INTERFACE
# define EXPAND_CONCAT(name1,name2) name1 ## name2
# define CONCAT(name1,name2) EXPAND_CONCAT(name1,name2)
# define MODEL_INITIALIZE CONCAT(MODEL,_initialize)
# define MODEL_STEP       CONCAT(MODEL,_step)
# define MODEL_TERMINATE  CONCAT(MODEL,_terminate)
# define RT_MDL_TYPE      CONCAT(MODEL,_M_TYPE)
#endif

extern const char MyPowerTrainXWD_LibIdent[];
const char MyPowerTrainXWD_LibIdent[] = "(@@)" QUOTE(MODEL) " " ARCH " 1.0 " BUILDDATE;

static const char Modelname[] = QUOTE(MODEL);
static const tModelClass Modelclass = ModelClass_PowerTrainXWD;
static tMatSuppSampling SampleParams;

static void
DoOneStep (rtModel_MyPowerTrainXWD *rtm)
{
#ifdef CLASSIC_INTERFACE
    real_T tnext;

    tnext = rt_SimGetNextSampleHit(rtmGetTimingData(rtm),
				   rtmGetNumSampleTimes(rtm));
    rtsiSetSolverStopTime(rtmGetRTWSolverInfo(rtm),tnext);

    rtmiOutputs(rtmGetRTWRTModelMethodsInfo(rtm),0);
    rtmiUpdate(rtmGetRTWRTModelMethodsInfo(rtm),0);
    rt_SimUpdateDiscreteTaskSampleHits(rtmGetNumSampleTimes(rtm),
				       rtmGetTimingData(rtm),
				       rtmGetSampleHitPtr(rtm),
				       rtmGetTPtr(rtm));

    if (rtmGetSampleTime(rtm,0) == CONTINUOUS_SAMPLE_TIME) {
	if (rtmGetNumContStates(rtm) > 0) {
	    rt_ODEUpdateContinuousStates(rtmGetRTWSolverInfo(rtm));
	} else {
	    rtsiSetT(rtmGetRTWSolverInfo(rtm), rtsiGetSolverStopTime(rtmGetRTWSolverInfo(rtm)));
	}
    }
#else
    MODEL_STEP(rtm);
#endif
}


/*
 * Define dictionary entries made from tunable parameters.
 * The function will actually be called twice, first with tuns==NULL.
 */
static void
DeclParameterQuants (struct tMatSuppTunables *tuns)
{
    /*MatSupp_TunDDictDefScalar(tuns, "MyParam", INFOMAT_DOUBLE, "kappa", "kg/s");*/
}


static void
MyPowerTrainXWD_DeclQuants (void *MP)
{
    rtModel_MyPowerTrainXWD *rtm = (rtModel_MyPowerTrainXWD *)MP;
    int i;

    /*Log("%s_DeclQuants()\n", Modelname);*/

    if (rtm == NULL) {
	/* Remember body frames defined in this model for later registration. */
        MdlBdyFrame_Add(MyPowerTrainXWD_BdyFrameDefines);

	/* Define dict entries for non-dynamically allocated variables. */
	if ((i = MatSupp_DeclQuants(MyPowerTrainXWD_DictDefines)) >= 0) {
	    LogErrF(EC_Init, "Model '%s': Error defining quantity '%s'",
		    Modelname, MyPowerTrainXWD_DictDefines[i].Name);
	}

	/* Define dict entries for tunable parameters (with dummy address). */
	DeclParameterQuants(NULL);
    } else {
	/* Define dict entries for dynamically allocated variables. */
    }
}


/*
 * MyPowerTrainXWD_SetParams() will be invoked indirectly by the generated
 * model C code each time MyPowerTrainXWD_New() is called.
 */
void
MyPowerTrainXWD_SetParams (rtModel_MyPowerTrainXWD *rtm, struct tMatSuppTunables *tuns,
		   struct tInfos *Inf)
{
    /*Log("%s_SetParams()\n", Modelname);*/

    /*
     * Parameter tuning - Part 1
     * This is the place to modify parameters of a storage class
     * other than 'SimulinkGlobal'.
     */

    if (tuns == NULL)
        return;

    /* Define dict entries for tunable parameters (address update). */
    DeclParameterQuants(tuns);

    /*
     * Parameter tuning - Part 2
     * This is the place to modify parameters of storage class
     * 'SimulinkGlobal', e.g. using the CarMaker target's tunable parameter
     * interface.
     */

    const char *prefix = Model_Class2Str(Modelclass);
    MatSupp_TunReadAllOpt(tuns, Inf, prefix);
    /*MatSupp_TunReadAll(tuns, ...);*/
    /*MatSupp_TunReadDef(tuns, ...);*/
    /*MatSupp_TunRead(tuns, ...);*/
}

static void
CfgLinMaptoBus (tLM *CfgInput, int arraydim, char* key, double *BusInputx, double *BusInputz)
{
    int xdim, i;
    tLM *lm;

    if (CfgInput != NULL) {
	lm = LMCopy(CfgInput);
	xdim = LMXGetDim(CfgInput);
	
	if (xdim > arraydim) {
	    Log("Model '%s': %s mapping will be resized to %i points.\n", Modelname, key, arraydim);
	    LMDelete(lm);
	    lm = LMResizeAequi(CfgInput, arraydim);
	    xdim = LMXGetDim(lm);
	}
	
	for (i=0; i<xdim; i++) {
	    BusInputx[i] = LMXGetVal(lm, i);
	    BusInputz[i] = LMEval(lm, BusInputx[i]);
	}
	for (i=xdim; i<arraydim; i++) {
	    BusInputx[i] = BusInputx[xdim-1];
	    BusInputz[i] = BusInputz[xdim-1];
	}
	LMDelete(lm);
    }
}

static void *
assignCfgIF (struct tPowerTrainXWD_CfgIF *CfgIF, void *MP)
{
    rtModel_MyPowerTrainXWD *rtm = (rtModel_MyPowerTrainXWD *)MP;
    int arraydim, nError = GetInfoErrorCount() + Log_nError;
    ExternalInputs_MyPowerTrainXWD  *in  = (ExternalInputs_MyPowerTrainXWD *) rtmGetU(rtm);

    /* CfgIF Input */
    in->CfgInFromCM.nWheels		= CfgIF->nWheels;

    /* CfgIF Output */
    in->CfgOutFromCM.PTKind		= CfgIF->PTKind;
    in->CfgOutFromCM.ClKind		= CfgIF->ClKind;
    in->CfgOutFromCM.nMotor		= CfgIF->nMotor;
    in->CfgOutFromCM.nGearBoxM		= CfgIF->nGearBoxM;
    in->CfgOutFromCM.nPlanetGear	= CfgIF->nPlanetGear;

    in->CfgOutFromCM.DriveLine.iDiff_mean	 = CfgIF->DriveLine.iDiff_mean;
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d0 = CfgIF->DriveLine.DriveSourcePos[0];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d1 = CfgIF->DriveLine.DriveSourcePos[1];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d2 = CfgIF->DriveLine.DriveSourcePos[2];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d3 = CfgIF->DriveLine.DriveSourcePos[3];
#if defined (IS_TRUCK)
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d4 = CfgIF->DriveLine.DriveSourcePos[4];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d5 = CfgIF->DriveLine.DriveSourcePos[5];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d6 = CfgIF->DriveLine.DriveSourcePos[6];
    in->CfgOutFromCM.DriveLine.DriveSourcePos.d7 = CfgIF->DriveLine.DriveSourcePos[7];
#endif

    in->CfgOutFromCM.GearBox.GBKind		= CfgIF->GearBox.GBKind;
    in->CfgOutFromCM.GearBox.ClKind		= CfgIF->GearBox.ClKind;
    in->CfgOutFromCM.GearBox.nFGears		= CfgIF->GearBox.nFGears;
    in->CfgOutFromCM.GearBox.iFGear.Gear1	= CfgIF->GearBox.iFGear[1];
    in->CfgOutFromCM.GearBox.iFGear.Gear2	= CfgIF->GearBox.iFGear[2];
    in->CfgOutFromCM.GearBox.iFGear.Gear3	= CfgIF->GearBox.iFGear[3];
    in->CfgOutFromCM.GearBox.iFGear.Gear4	= CfgIF->GearBox.iFGear[4];
    in->CfgOutFromCM.GearBox.iFGear.Gear5	= CfgIF->GearBox.iFGear[5];
    in->CfgOutFromCM.GearBox.iFGear.Gear6	= CfgIF->GearBox.iFGear[6];
    in->CfgOutFromCM.GearBox.iFGear.Gear7	= CfgIF->GearBox.iFGear[7];
    in->CfgOutFromCM.GearBox.iFGear.Gear8	= CfgIF->GearBox.iFGear[8];
    in->CfgOutFromCM.GearBox.iFGear.Gear9	= CfgIF->GearBox.iFGear[9];
    in->CfgOutFromCM.GearBox.iFGear.Gear10	= CfgIF->GearBox.iFGear[10];
    in->CfgOutFromCM.GearBox.iFGear.Gear11	= CfgIF->GearBox.iFGear[11];
    in->CfgOutFromCM.GearBox.iFGear.Gear12	= CfgIF->GearBox.iFGear[12];
    in->CfgOutFromCM.GearBox.iFGear.Gear13	= CfgIF->GearBox.iFGear[13];
    in->CfgOutFromCM.GearBox.iFGear.Gear14	= CfgIF->GearBox.iFGear[14];
    in->CfgOutFromCM.GearBox.iFGear.Gear15	= CfgIF->GearBox.iFGear[15];
    in->CfgOutFromCM.GearBox.iFGear.Gear16	= CfgIF->GearBox.iFGear[16];
    in->CfgOutFromCM.GearBox.nBGears		= CfgIF->GearBox.nBGears;
    in->CfgOutFromCM.GearBox.iBGear.Gear1	= CfgIF->GearBox.iBGear[1];
    in->CfgOutFromCM.GearBox.iBGear.Gear2	= CfgIF->GearBox.iBGear[2];
    in->CfgOutFromCM.GearBox.iBGear.Gear3	= CfgIF->GearBox.iBGear[3];
    in->CfgOutFromCM.GearBox.iBGear.Gear4	= CfgIF->GearBox.iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m0.GBKind		= CfgIF->GearBoxM[0].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m0.ClKind		= CfgIF->GearBoxM[0].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m0.nFGears		= CfgIF->GearBoxM[0].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear1	= CfgIF->GearBoxM[0].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear2	= CfgIF->GearBoxM[0].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear3	= CfgIF->GearBoxM[0].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear4	= CfgIF->GearBoxM[0].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear5	= CfgIF->GearBoxM[0].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear6	= CfgIF->GearBoxM[0].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear7	= CfgIF->GearBoxM[0].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear8	= CfgIF->GearBoxM[0].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear9	= CfgIF->GearBoxM[0].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear10	= CfgIF->GearBoxM[0].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear11	= CfgIF->GearBoxM[0].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear12	= CfgIF->GearBoxM[0].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear13	= CfgIF->GearBoxM[0].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear14	= CfgIF->GearBoxM[0].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear15	= CfgIF->GearBoxM[0].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m0.iFGear.Gear16	= CfgIF->GearBoxM[0].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m0.nBGears		= CfgIF->GearBoxM[0].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m0.iBGear.Gear1	= CfgIF->GearBoxM[0].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m0.iBGear.Gear2	= CfgIF->GearBoxM[0].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m0.iBGear.Gear3	= CfgIF->GearBoxM[0].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m0.iBGear.Gear4	= CfgIF->GearBoxM[0].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m1.GBKind		= CfgIF->GearBoxM[1].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m1.ClKind		= CfgIF->GearBoxM[1].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m1.nFGears		= CfgIF->GearBoxM[1].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear1	= CfgIF->GearBoxM[1].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear2	= CfgIF->GearBoxM[1].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear3	= CfgIF->GearBoxM[1].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear4	= CfgIF->GearBoxM[1].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear5	= CfgIF->GearBoxM[1].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear6	= CfgIF->GearBoxM[1].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear7	= CfgIF->GearBoxM[1].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear8	= CfgIF->GearBoxM[1].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear9	= CfgIF->GearBoxM[1].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear10	= CfgIF->GearBoxM[1].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear11	= CfgIF->GearBoxM[1].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear12	= CfgIF->GearBoxM[1].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear13	= CfgIF->GearBoxM[1].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear14	= CfgIF->GearBoxM[1].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear15	= CfgIF->GearBoxM[1].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m1.iFGear.Gear16	= CfgIF->GearBoxM[1].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m1.nBGears		= CfgIF->GearBoxM[1].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m1.iBGear.Gear1	= CfgIF->GearBoxM[1].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m1.iBGear.Gear2	= CfgIF->GearBoxM[1].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m1.iBGear.Gear3	= CfgIF->GearBoxM[1].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m1.iBGear.Gear4	= CfgIF->GearBoxM[1].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m2.GBKind		= CfgIF->GearBoxM[2].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m2.ClKind		= CfgIF->GearBoxM[2].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m2.nFGears		= CfgIF->GearBoxM[2].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear1	= CfgIF->GearBoxM[2].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear2	= CfgIF->GearBoxM[2].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear3	= CfgIF->GearBoxM[2].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear4	= CfgIF->GearBoxM[2].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear5	= CfgIF->GearBoxM[2].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear6	= CfgIF->GearBoxM[2].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear7	= CfgIF->GearBoxM[2].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear8	= CfgIF->GearBoxM[2].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear9	= CfgIF->GearBoxM[2].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear10	= CfgIF->GearBoxM[2].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear11	= CfgIF->GearBoxM[2].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear12	= CfgIF->GearBoxM[2].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear13	= CfgIF->GearBoxM[2].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear14	= CfgIF->GearBoxM[2].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear15	= CfgIF->GearBoxM[2].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m2.iFGear.Gear16	= CfgIF->GearBoxM[2].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m2.nBGears		= CfgIF->GearBoxM[2].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m2.iBGear.Gear1	= CfgIF->GearBoxM[2].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m2.iBGear.Gear2	= CfgIF->GearBoxM[2].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m2.iBGear.Gear3	= CfgIF->GearBoxM[2].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m2.iBGear.Gear4	= CfgIF->GearBoxM[2].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m3.GBKind		= CfgIF->GearBoxM[3].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m3.ClKind		= CfgIF->GearBoxM[3].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m3.nFGears		= CfgIF->GearBoxM[3].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear1	= CfgIF->GearBoxM[3].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear2	= CfgIF->GearBoxM[3].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear3	= CfgIF->GearBoxM[3].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear4	= CfgIF->GearBoxM[3].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear5	= CfgIF->GearBoxM[3].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear6	= CfgIF->GearBoxM[3].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear7	= CfgIF->GearBoxM[3].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear8	= CfgIF->GearBoxM[3].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear9	= CfgIF->GearBoxM[3].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear10	= CfgIF->GearBoxM[3].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear11	= CfgIF->GearBoxM[3].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear12	= CfgIF->GearBoxM[3].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear13	= CfgIF->GearBoxM[3].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear14	= CfgIF->GearBoxM[3].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear15	= CfgIF->GearBoxM[3].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m3.iFGear.Gear16	= CfgIF->GearBoxM[3].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m3.nBGears		= CfgIF->GearBoxM[3].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m3.iBGear.Gear1	= CfgIF->GearBoxM[3].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m3.iBGear.Gear2	= CfgIF->GearBoxM[3].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m3.iBGear.Gear3	= CfgIF->GearBoxM[3].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m3.iBGear.Gear4	= CfgIF->GearBoxM[3].iBGear[4];

#if defined (IS_TRUCK)
    in->CfgOutFromCM.GearBoxM.GB_m4.GBKind		= CfgIF->GearBoxM[4].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m4.ClKind		= CfgIF->GearBoxM[4].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m4.nFGears		= CfgIF->GearBoxM[4].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear1	= CfgIF->GearBoxM[4].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear2	= CfgIF->GearBoxM[4].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear3	= CfgIF->GearBoxM[4].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear4	= CfgIF->GearBoxM[4].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear5	= CfgIF->GearBoxM[4].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear6	= CfgIF->GearBoxM[4].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear7	= CfgIF->GearBoxM[4].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear8	= CfgIF->GearBoxM[4].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear9	= CfgIF->GearBoxM[4].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear10	= CfgIF->GearBoxM[4].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear11	= CfgIF->GearBoxM[4].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear12	= CfgIF->GearBoxM[4].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear13	= CfgIF->GearBoxM[4].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear14	= CfgIF->GearBoxM[4].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear15	= CfgIF->GearBoxM[4].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m4.iFGear.Gear16	= CfgIF->GearBoxM[4].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m4.nBGears		= CfgIF->GearBoxM[4].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m4.iBGear.Gear1	= CfgIF->GearBoxM[4].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m4.iBGear.Gear2	= CfgIF->GearBoxM[4].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m4.iBGear.Gear3	= CfgIF->GearBoxM[4].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m4.iBGear.Gear4	= CfgIF->GearBoxM[4].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m5.GBKind		= CfgIF->GearBoxM[5].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m5.ClKind		= CfgIF->GearBoxM[5].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m5.nFGears		= CfgIF->GearBoxM[5].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear1	= CfgIF->GearBoxM[5].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear2	= CfgIF->GearBoxM[5].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear3	= CfgIF->GearBoxM[5].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear4	= CfgIF->GearBoxM[5].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear5	= CfgIF->GearBoxM[5].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear6	= CfgIF->GearBoxM[5].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear7	= CfgIF->GearBoxM[5].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear8	= CfgIF->GearBoxM[5].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear9	= CfgIF->GearBoxM[5].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear10	= CfgIF->GearBoxM[5].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear11	= CfgIF->GearBoxM[5].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear12	= CfgIF->GearBoxM[5].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear13	= CfgIF->GearBoxM[5].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear14	= CfgIF->GearBoxM[5].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear15	= CfgIF->GearBoxM[5].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m5.iFGear.Gear16	= CfgIF->GearBoxM[5].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m5.nBGears		= CfgIF->GearBoxM[5].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m5.iBGear.Gear1	= CfgIF->GearBoxM[5].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m5.iBGear.Gear2	= CfgIF->GearBoxM[5].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m5.iBGear.Gear3	= CfgIF->GearBoxM[5].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m5.iBGear.Gear4	= CfgIF->GearBoxM[5].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m6.GBKind		= CfgIF->GearBoxM[6].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m6.ClKind		= CfgIF->GearBoxM[6].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m6.nFGears		= CfgIF->GearBoxM[6].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear1	= CfgIF->GearBoxM[6].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear2	= CfgIF->GearBoxM[6].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear3	= CfgIF->GearBoxM[6].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear4	= CfgIF->GearBoxM[6].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear5	= CfgIF->GearBoxM[6].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear6	= CfgIF->GearBoxM[6].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear7	= CfgIF->GearBoxM[6].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear8	= CfgIF->GearBoxM[6].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear9	= CfgIF->GearBoxM[6].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear10	= CfgIF->GearBoxM[6].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear11	= CfgIF->GearBoxM[6].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear12	= CfgIF->GearBoxM[6].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear13	= CfgIF->GearBoxM[6].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear14	= CfgIF->GearBoxM[6].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear15	= CfgIF->GearBoxM[6].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m6.iFGear.Gear16	= CfgIF->GearBoxM[6].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m6.nBGears		= CfgIF->GearBoxM[6].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m6.iBGear.Gear1	= CfgIF->GearBoxM[6].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m6.iBGear.Gear2	= CfgIF->GearBoxM[6].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m6.iBGear.Gear3	= CfgIF->GearBoxM[6].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m6.iBGear.Gear4	= CfgIF->GearBoxM[6].iBGear[4];

    in->CfgOutFromCM.GearBoxM.GB_m7.GBKind		= CfgIF->GearBoxM[7].GBKind;
    in->CfgOutFromCM.GearBoxM.GB_m7.ClKind		= CfgIF->GearBoxM[7].ClKind;
    in->CfgOutFromCM.GearBoxM.GB_m7.nFGears		= CfgIF->GearBoxM[7].nFGears;
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear1	= CfgIF->GearBoxM[7].iFGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear2	= CfgIF->GearBoxM[7].iFGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear3	= CfgIF->GearBoxM[7].iFGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear4	= CfgIF->GearBoxM[7].iFGear[4];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear5	= CfgIF->GearBoxM[7].iFGear[5];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear6	= CfgIF->GearBoxM[7].iFGear[6];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear7	= CfgIF->GearBoxM[7].iFGear[7];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear8	= CfgIF->GearBoxM[7].iFGear[8];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear9	= CfgIF->GearBoxM[7].iFGear[9];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear10	= CfgIF->GearBoxM[7].iFGear[10];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear11	= CfgIF->GearBoxM[7].iFGear[11];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear12	= CfgIF->GearBoxM[7].iFGear[12];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear13	= CfgIF->GearBoxM[7].iFGear[13];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear14	= CfgIF->GearBoxM[7].iFGear[14];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear15	= CfgIF->GearBoxM[7].iFGear[15];
    in->CfgOutFromCM.GearBoxM.GB_m7.iFGear.Gear16	= CfgIF->GearBoxM[7].iFGear[16];
    in->CfgOutFromCM.GearBoxM.GB_m7.nBGears		= CfgIF->GearBoxM[7].nBGears;
    in->CfgOutFromCM.GearBoxM.GB_m7.iBGear.Gear1	= CfgIF->GearBoxM[7].iBGear[1];
    in->CfgOutFromCM.GearBoxM.GB_m7.iBGear.Gear2	= CfgIF->GearBoxM[7].iBGear[2];
    in->CfgOutFromCM.GearBoxM.GB_m7.iBGear.Gear3	= CfgIF->GearBoxM[7].iBGear[3];
    in->CfgOutFromCM.GearBoxM.GB_m7.iBGear.Gear4	= CfgIF->GearBoxM[7].iBGear[4];
#endif

    in->CfgOutFromCM.PlanetGear.Ratio	= CfgIF->PlanetGear[0].Ratio;

    in->CfgOutFromCM.BattLV.SOC_min	= CfgIF->BattLV.SOC_min;
    in->CfgOutFromCM.BattLV.SOC_max	= CfgIF->BattLV.SOC_max;
    in->CfgOutFromCM.BattLV.Capacity	= CfgIF->BattLV.Capacity;
    in->CfgOutFromCM.BattLV.Voltage	= CfgIF->BattLV.Voltage;

    in->CfgOutFromCM.BattHV.SOC_min	= CfgIF->BattHV.SOC_min;
    in->CfgOutFromCM.BattHV.SOC_max	= CfgIF->BattHV.SOC_max;
    in->CfgOutFromCM.BattHV.Capacity	= CfgIF->BattHV.Capacity;
    in->CfgOutFromCM.BattHV.Voltage	= CfgIF->BattHV.Voltage;

    if (CfgIF->PTKind != PTKind_BEV) {
	arraydim = sizeof(in->CfgOutFromCM.Engine.TrqFull.x) / sizeof(in->CfgOutFromCM.Engine.TrqFull.x[0]);
	CfgLinMaptoBus (CfgIF->Engine.TrqFull, arraydim, "Maximum engine full torque",
			in->CfgOutFromCM.Engine.TrqFull.x, in->CfgOutFromCM.Engine.TrqFull.z);

	arraydim = sizeof(in->CfgOutFromCM.Engine.TrqDrag.x) / sizeof(in->CfgOutFromCM.Engine.TrqDrag.x[0]);
	CfgLinMaptoBus (CfgIF->Engine.TrqDrag, arraydim, "Maximum engine drag torque",
			in->CfgOutFromCM.Engine.TrqDrag.x, in->CfgOutFromCM.Engine.TrqDrag.z);

	arraydim = sizeof(in->CfgOutFromCM.Engine.TrqOpt.x) / sizeof(in->CfgOutFromCM.Engine.TrqOpt.x[0]);
	CfgLinMaptoBus (CfgIF->Engine.TrqOpt, arraydim, "Engine torque with opt. consumption",
			in->CfgOutFromCM.Engine.TrqOpt.x, in->CfgOutFromCM.Engine.TrqOpt.z);

	in->CfgOutFromCM.Engine.Fuel_l2kWh	= CfgIF->Engine.Fuel_l2kWh;
	in->CfgOutFromCM.Engine.rotv_off	= CfgIF->Engine.rotv_off;
	in->CfgOutFromCM.Engine.rotv_max	= CfgIF->Engine.rotv_max;
	in->CfgOutFromCM.Engine.rotv_idle	= CfgIF->Engine.rotv_idle;
	in->CfgOutFromCM.Engine.rotv_opt	= CfgIF->Engine.rotv_opt;

	arraydim = sizeof(in->CfgOutFromCM.ISG.TrqMot_max.x) / sizeof(in->CfgOutFromCM.ISG.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->ISG.TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.ISG.TrqMot_max.x, in->CfgOutFromCM.ISG.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.ISG.TrqGen_max.x) / sizeof(in->CfgOutFromCM.ISG.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->ISG.TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.ISG.TrqGen_max.x, in->CfgOutFromCM.ISG.TrqGen_max.z);

	in->CfgOutFromCM.ISG.Level		= CfgIF->ISG.Level;
	in->CfgOutFromCM.ISG.Ratio		= CfgIF->ISG.Ratio;
	in->CfgOutFromCM.ISG.rotv_Mot_max	= CfgIF->ISG.rotv_Mot_max;
	in->CfgOutFromCM.ISG.rotv_Gen_max	= CfgIF->ISG.rotv_Gen_max;
    }

    if (CfgIF->nMotor>=1) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m0.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m0.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[0].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m0.TrqMot_max.x, in->CfgOutFromCM.Motor.m0.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m0.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m0.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[0].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m0.TrqGen_max.x, in->CfgOutFromCM.Motor.m0.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m0.Level		= CfgIF->Motor[0].Level;
	in->CfgOutFromCM.Motor.m0.Ratio		= CfgIF->Motor[0].Ratio;
	in->CfgOutFromCM.Motor.m0.rotv_Mot_max	= CfgIF->Motor[0].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m0.rotv_Gen_max	= CfgIF->Motor[0].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=2) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m1.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m1.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[1].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m1.TrqMot_max.x, in->CfgOutFromCM.Motor.m1.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m1.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m1.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[1].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m1.TrqGen_max.x, in->CfgOutFromCM.Motor.m1.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m1.Level		= CfgIF->Motor[1].Level;
	in->CfgOutFromCM.Motor.m1.Ratio		= CfgIF->Motor[1].Ratio;
	in->CfgOutFromCM.Motor.m1.rotv_Mot_max	= CfgIF->Motor[1].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m1.rotv_Gen_max	= CfgIF->Motor[1].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=3) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m2.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m2.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[2].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m2.TrqMot_max.x, in->CfgOutFromCM.Motor.m2.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m2.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m2.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[2].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m2.TrqGen_max.x, in->CfgOutFromCM.Motor.m2.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m2.Level		= CfgIF->Motor[2].Level;
	in->CfgOutFromCM.Motor.m2.Ratio		= CfgIF->Motor[2].Ratio;
	in->CfgOutFromCM.Motor.m2.rotv_Mot_max	= CfgIF->Motor[2].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m2.rotv_Gen_max	= CfgIF->Motor[2].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=4) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m3.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m3.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[3].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m3.TrqMot_max.x, in->CfgOutFromCM.Motor.m3.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m3.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m3.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[3].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m3.TrqGen_max.x, in->CfgOutFromCM.Motor.m3.TrqGen_max.z);
    
	in->CfgOutFromCM.Motor.m3.Level		= CfgIF->Motor[3].Level;
	in->CfgOutFromCM.Motor.m3.Ratio		= CfgIF->Motor[3].Ratio;
	in->CfgOutFromCM.Motor.m3.rotv_Mot_max	= CfgIF->Motor[3].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m3.rotv_Gen_max	= CfgIF->Motor[3].rotv_Gen_max;
    }

#if defined (IS_TRUCK)
    if (CfgIF->nMotor>=5) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m4.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m4.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[4].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m4.TrqMot_max.x, in->CfgOutFromCM.Motor.m4.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m4.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m4.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[4].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m4.TrqGen_max.x, in->CfgOutFromCM.Motor.m4.TrqGen_max.z);
    
	in->CfgOutFromCM.Motor.m4.Level		= CfgIF->Motor[4].Level;
	in->CfgOutFromCM.Motor.m4.Ratio		= CfgIF->Motor[4].Ratio;
	in->CfgOutFromCM.Motor.m4.rotv_Mot_max	= CfgIF->Motor[4].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m4.rotv_Gen_max	= CfgIF->Motor[4].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=6) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m5.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m5.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[5].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m5.TrqMot_max.x, in->CfgOutFromCM.Motor.m5.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m5.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m5.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[5].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m5.TrqGen_max.x, in->CfgOutFromCM.Motor.m5.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m5.Level		= CfgIF->Motor[5].Level;
	in->CfgOutFromCM.Motor.m5.Ratio		= CfgIF->Motor[5].Ratio;
	in->CfgOutFromCM.Motor.m5.rotv_Mot_max	= CfgIF->Motor[5].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m5.rotv_Gen_max	= CfgIF->Motor[5].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=7) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m6.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m6.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[6].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m6.TrqMot_max.x, in->CfgOutFromCM.Motor.m6.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m6.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m6.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[6].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m6.TrqGen_max.x, in->CfgOutFromCM.Motor.m6.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m6.Level		= CfgIF->Motor[6].Level;
	in->CfgOutFromCM.Motor.m6.Ratio		= CfgIF->Motor[6].Ratio;
	in->CfgOutFromCM.Motor.m6.rotv_Mot_max	= CfgIF->Motor[6].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m6.rotv_Gen_max	= CfgIF->Motor[6].rotv_Gen_max;
    }

    if (CfgIF->nMotor>=8) {
	arraydim = sizeof(in->CfgOutFromCM.Motor.m7.TrqMot_max.x) / sizeof(in->CfgOutFromCM.Motor.m7.TrqMot_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[7].TrqMot_max, arraydim, "Maximum motor torque",
			in->CfgOutFromCM.Motor.m7.TrqMot_max.x, in->CfgOutFromCM.Motor.m7.TrqMot_max.z);

	arraydim = sizeof(in->CfgOutFromCM.Motor.m7.TrqGen_max.x) / sizeof(in->CfgOutFromCM.Motor.m7.TrqGen_max.x[0]);
	CfgLinMaptoBus (CfgIF->Motor[7].TrqGen_max, arraydim, "Maximum generator torque",
			in->CfgOutFromCM.Motor.m7.TrqGen_max.x, in->CfgOutFromCM.Motor.m7.TrqGen_max.z);

	in->CfgOutFromCM.Motor.m7.Level		= CfgIF->Motor[7].Level;
	in->CfgOutFromCM.Motor.m7.Ratio		= CfgIF->Motor[7].Ratio;
	in->CfgOutFromCM.Motor.m7.rotv_Mot_max	= CfgIF->Motor[7].rotv_Mot_max;
	in->CfgOutFromCM.Motor.m7.rotv_Gen_max	= CfgIF->Motor[7].rotv_Gen_max;
    }
#endif

    if (GetInfoErrorCount() + Log_nError != nError) {
    	goto ErrorReturn;
    }

    return rtm;

  ErrorReturn:
    return NULL;
}


static void *
MyPowerTrainXWD_New (struct tInfos *Inf, struct tPowerTrainXWD_CfgIF *CfgIF, const char *KindKey)
{
    rtModel_MyPowerTrainXWD *rtm;
    double rtmSampleTime;
    const char *ModelKind;
    int VersionId = 0;

    if ((ModelKind = SimCore_GetKindInfo(Inf, Modelclass, KindKey,
	 				 0, PARAMID, &VersionId)) == NULL)
	return NULL;

    /*Log("%s_New()\n", Modelname);*/

    MatSupp_ResetQuants(MyPowerTrainXWD_DictDefines);

    rtm = MODEL(Inf);

#ifdef CLASSIC_INTERFACE
    rtmSetT(rtm, 0.0);
    rtmSetTFinal(rtm, -1 /*run forever*/);

    rtmiInitializeSizes(rtmGetRTWRTModelMethodsInfo(rtm));
    rtmiInitializeSampleTimes(rtmGetRTWRTModelMethodsInfo(rtm));
    rt_SimInitTimingEngine(rtmGetNumSampleTimes(rtm),
			   rtmGetStepSize(rtm),
			   rtmGetSampleTimePtr(rtm),
			   rtmGetOffsetTimePtr(rtm),
			   rtmGetSampleHitPtr(rtm),
			   rtmGetSampleTimeTaskIDPtr(rtm),
			   rtmGetTStart(rtm),
			   &rtmGetSimTimeStep(rtm),
			   &rtmGetTimingData(rtm));
    if (rtmGetNumContStates(rtm) > 0) {
	rt_ODECreateIntegrationData(rtmGetRTWSolverInfo(rtm));
    } else {
	rtsiSetSolverName(rtmGetRTWSolverInfo(rtm), "FixedStepDiscrete");
    }
    rtsiSetVariableStepSolver(rtmGetRTWSolverInfo(rtm), 0);
#endif

    rtmSampleTime = (double) rtmGetStepSize(rtm);
    if (MatSupp_Sampling (&SampleParams, SimCore.DeltaT/PowerTrain.OSRate, rtmSampleTime) !=0) {
	LogErrF(EC_Init, "Model '%s': The sample times of the plugin model and the application have to be integer multiples",Modelname);
	return NULL;
    }

    /* get CfgIF parameters */
    if (PowerTrainXWD_GetCfgOutIF (Inf, CfgIF, ModelKind) != 0)
	return NULL;

    /* assign CfgIF struct */
    if ((assignCfgIF(CfgIF, rtm)) == NULL)  {
	LogErrF(EC_Init, "Model '%s': failed to assign CfgIF",Modelname);
	return NULL;
    }

#ifdef CLASSIC_INTERFACE
    rtmiStart(rtmGetRTWRTModelMethodsInfo(rtm));
#else
    MODEL_INITIALIZE(rtm);
#endif

    return rtm; /* Will be passed as MP to the other functions. */
}


static void
MyPowerTrainXWD_Delete (void *MP)
{
    rtModel_MyPowerTrainXWD *rtm = (rtModel_MyPowerTrainXWD *)MP;

    /*Log("%s_Delete()\n", Modelname);*/

#ifdef CLASSIC_INTERFACE
    rt_SimDestroyTimingEngine(rtmGetTimingData(rtm));
    if (rtmGetNumContStates(rtm) > 0)
	rt_ODEDestroyIntegrationData(rtmGetRTWSolverInfo(rtm));
    rtmiTerminate(rtmGetRTWRTModelMethodsInfo(rtm));
#else
    MODEL_TERMINATE(rtm);
#endif
}


static int
MyPowerTrainXWD_Calc (void *MP, struct tPowerTrainXWD_IF  *IF, double dt)
{
    rtModel_MyPowerTrainXWD *rtm = (rtModel_MyPowerTrainXWD *)MP;
    int osCount=0;
    ExternalInputs_MyPowerTrainXWD  *in  = (ExternalInputs_MyPowerTrainXWD *) rtmGetU(rtm);
    ExternalOutputs_MyPowerTrainXWD *out = (ExternalOutputs_MyPowerTrainXWD *)rtmGetY(rtm);

    in->FromCM.Ignition			= IF->Ignition;
    in->FromCM.Gas			= IF->Gas;
    in->FromCM.SelectorCtrl		= IF->SelectorCtrl;
    in->FromCM.Velocity			= IF->Velocity;

    in->FromCM.EngineIn.set_ISC		= IF->EngineIn.set_ISC;
    in->FromCM.EngineIn.FuelCutOff	= IF->EngineIn.FuelCutOff;
    in->FromCM.EngineIn.Load		= IF->EngineIn.Load;
    in->FromCM.EngineIn.Trq_trg		= IF->EngineIn.Trq_trg;
    in->FromCM.EngineIn.rotv_trg	= IF->EngineIn.rotv_trg;

    in->FromCM.ISGIn.Load		= IF->ISGIn.Load;
    in->FromCM.ISGIn.Trq_trg		= IF->ISGIn.Trq_trg;
    in->FromCM.ISGIn.rotv_trg		= IF->ISGIn.rotv_trg;

    in->FromCM.MotorIn.m0.Load		= IF->MotorIn[0].Load;
    in->FromCM.MotorIn.m0.Trq_trg	= IF->MotorIn[0].Trq_trg;
    in->FromCM.MotorIn.m0.rotv_trg	= IF->MotorIn[0].rotv_trg;

    in->FromCM.MotorIn.m1.Load		= IF->MotorIn[1].Load;
    in->FromCM.MotorIn.m1.Trq_trg	= IF->MotorIn[1].Trq_trg;
    in->FromCM.MotorIn.m1.rotv_trg	= IF->MotorIn[1].rotv_trg;

    in->FromCM.MotorIn.m2.Load		= IF->MotorIn[2].Load;
    in->FromCM.MotorIn.m2.Trq_trg	= IF->MotorIn[2].Trq_trg;
    in->FromCM.MotorIn.m2.rotv_trg	= IF->MotorIn[2].rotv_trg;

    in->FromCM.MotorIn.m3.Load		= IF->MotorIn[3].Load;
    in->FromCM.MotorIn.m3.Trq_trg	= IF->MotorIn[3].Trq_trg;
    in->FromCM.MotorIn.m3.rotv_trg	= IF->MotorIn[3].rotv_trg;

#if defined (IS_TRUCK)
    in->FromCM.MotorIn.m4.Load		= IF->MotorIn[4].Load;
    in->FromCM.MotorIn.m4.Trq_trg	= IF->MotorIn[4].Trq_trg;
    in->FromCM.MotorIn.m4.rotv_trg	= IF->MotorIn[4].rotv_trg;

    in->FromCM.MotorIn.m5.Load		= IF->MotorIn[5].Load;
    in->FromCM.MotorIn.m5.Trq_trg	= IF->MotorIn[5].Trq_trg;
    in->FromCM.MotorIn.m5.rotv_trg	= IF->MotorIn[5].rotv_trg;

    in->FromCM.MotorIn.m6.Load		= IF->MotorIn[6].Load;
    in->FromCM.MotorIn.m6.Trq_trg	= IF->MotorIn[6].Trq_trg;
    in->FromCM.MotorIn.m6.rotv_trg	= IF->MotorIn[6].rotv_trg;

    in->FromCM.MotorIn.m7.Load		= IF->MotorIn[7].Load;
    in->FromCM.MotorIn.m7.Trq_trg	= IF->MotorIn[7].Trq_trg;
    in->FromCM.MotorIn.m7.rotv_trg	= IF->MotorIn[7].rotv_trg;
#endif

    in->FromCM.ClutchIn.Pos		= IF->ClutchIn.Pos;
    in->FromCM.ClutchIn.rotv_out_trg	= IF->ClutchIn.rotv_out_trg;
    in->FromCM.ClutchIn.Trq_out_trg	= IF->ClutchIn.Trq_out_trg;

    in->FromCM.GearBoxIn.GearNoTrg		= IF->GearBoxIn.GearNoTrg;
    in->FromCM.GearBoxIn.GearNoTrg_dis		= IF->GearBoxIn.GearNoTrg_dis;
    in->FromCM.GearBoxIn.i_trg			= IF->GearBoxIn.i_trg;
    in->FromCM.GearBoxIn.set_ParkBrake		= IF->GearBoxIn.set_ParkBrake;
    in->FromCM.GearBoxIn.rotv_in_trg		= IF->GearBoxIn.rotv_in_trg;
    in->FromCM.GearBoxIn.Trq_out_trg		= IF->GearBoxIn.Trq_out_trg;
    in->FromCM.GearBoxIn.Clutch.Pos		= IF->GearBoxIn.Clutch.Pos;
    in->FromCM.GearBoxIn.Clutch.rotv_out_trg	= IF->GearBoxIn.Clutch.rotv_out_trg;
    in->FromCM.GearBoxIn.Clutch.Trq_out_trg	= IF->GearBoxIn.Clutch.Trq_out_trg;
    in->FromCM.GearBoxIn.Clutch_dis.Pos		= IF->GearBoxIn.Clutch_dis.Pos;
    in->FromCM.GearBoxIn.Clutch_dis.rotv_out_trg = IF->GearBoxIn.Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxIn.Clutch_dis.Trq_out_trg	= IF->GearBoxIn.Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m0.GearNoTrg		= IF->GearBoxM_In[0].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m0.GearNoTrg_dis		= IF->GearBoxM_In[0].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m0.i_trg			= IF->GearBoxM_In[0].i_trg;
    in->FromCM.GearBoxM_In.GB_m0.set_ParkBrake		= IF->GearBoxM_In[0].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m0.rotv_in_trg		= IF->GearBoxM_In[0].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m0.Trq_out_trg		= IF->GearBoxM_In[0].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m0.Clutch.Pos		= IF->GearBoxM_In[0].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m0.Clutch.rotv_out_trg	= IF->GearBoxM_In[0].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m0.Clutch.Trq_out_trg	= IF->GearBoxM_In[0].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m0.Clutch_dis.Pos		= IF->GearBoxM_In[0].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m0.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[0].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m0.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[0].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m1.GearNoTrg		= IF->GearBoxM_In[1].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m1.GearNoTrg_dis		= IF->GearBoxM_In[1].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m1.i_trg			= IF->GearBoxM_In[1].i_trg;
    in->FromCM.GearBoxM_In.GB_m1.set_ParkBrake		= IF->GearBoxM_In[1].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m1.rotv_in_trg		= IF->GearBoxM_In[1].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m1.Trq_out_trg		= IF->GearBoxM_In[1].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m1.Clutch.Pos		= IF->GearBoxM_In[1].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m1.Clutch.rotv_out_trg	= IF->GearBoxM_In[1].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m1.Clutch.Trq_out_trg	= IF->GearBoxM_In[1].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m1.Clutch_dis.Pos		= IF->GearBoxM_In[1].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m1.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[1].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m1.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[1].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m2.GearNoTrg		= IF->GearBoxM_In[2].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m2.GearNoTrg_dis		= IF->GearBoxM_In[2].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m2.i_trg			= IF->GearBoxM_In[2].i_trg;
    in->FromCM.GearBoxM_In.GB_m2.set_ParkBrake		= IF->GearBoxM_In[2].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m2.rotv_in_trg		= IF->GearBoxM_In[2].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m2.Trq_out_trg		= IF->GearBoxM_In[2].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m2.Clutch.Pos		= IF->GearBoxM_In[2].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m2.Clutch.rotv_out_trg	= IF->GearBoxM_In[2].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m2.Clutch.Trq_out_trg	= IF->GearBoxM_In[2].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m2.Clutch_dis.Pos		= IF->GearBoxM_In[2].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m2.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[2].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m2.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[2].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m3.GearNoTrg		= IF->GearBoxM_In[3].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m3.GearNoTrg_dis		= IF->GearBoxM_In[3].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m3.i_trg			= IF->GearBoxM_In[3].i_trg;
    in->FromCM.GearBoxM_In.GB_m3.set_ParkBrake		= IF->GearBoxM_In[3].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m3.rotv_in_trg		= IF->GearBoxM_In[3].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m3.Trq_out_trg		= IF->GearBoxM_In[3].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m3.Clutch.Pos		= IF->GearBoxM_In[3].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m3.Clutch.rotv_out_trg	= IF->GearBoxM_In[3].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m3.Clutch.Trq_out_trg	= IF->GearBoxM_In[3].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m3.Clutch_dis.Pos		= IF->GearBoxM_In[3].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m3.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[3].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m3.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[3].Clutch_dis.Trq_out_trg;

#if defined (IS_TRUCK)
    in->FromCM.GearBoxM_In.GB_m4.GearNoTrg		= IF->GearBoxM_In[4].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m4.GearNoTrg_dis		= IF->GearBoxM_In[4].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m4.i_trg			= IF->GearBoxM_In[4].i_trg;
    in->FromCM.GearBoxM_In.GB_m4.set_ParkBrake		= IF->GearBoxM_In[4].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m4.rotv_in_trg		= IF->GearBoxM_In[4].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m4.Trq_out_trg		= IF->GearBoxM_In[4].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m4.Clutch.Pos		= IF->GearBoxM_In[4].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m4.Clutch.rotv_out_trg	= IF->GearBoxM_In[4].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m4.Clutch.Trq_out_trg	= IF->GearBoxM_In[4].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m4.Clutch_dis.Pos		= IF->GearBoxM_In[4].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m4.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[4].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m4.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[4].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m5.GearNoTrg		= IF->GearBoxM_In[5].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m5.GearNoTrg_dis		= IF->GearBoxM_In[5].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m5.i_trg			= IF->GearBoxM_In[5].i_trg;
    in->FromCM.GearBoxM_In.GB_m5.set_ParkBrake		= IF->GearBoxM_In[5].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m5.rotv_in_trg		= IF->GearBoxM_In[5].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m5.Trq_out_trg		= IF->GearBoxM_In[5].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m5.Clutch.Pos		= IF->GearBoxM_In[5].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m5.Clutch.rotv_out_trg	= IF->GearBoxM_In[5].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m5.Clutch.Trq_out_trg	= IF->GearBoxM_In[5].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m5.Clutch_dis.Pos		= IF->GearBoxM_In[5].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m5.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[5].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m5.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[5].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m6.GearNoTrg		= IF->GearBoxM_In[6].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m6.GearNoTrg_dis		= IF->GearBoxM_In[6].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m6.i_trg			= IF->GearBoxM_In[6].i_trg;
    in->FromCM.GearBoxM_In.GB_m6.set_ParkBrake		= IF->GearBoxM_In[6].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m6.rotv_in_trg		= IF->GearBoxM_In[6].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m6.Trq_out_trg		= IF->GearBoxM_In[6].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m6.Clutch.Pos		= IF->GearBoxM_In[6].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m6.Clutch.rotv_out_trg	= IF->GearBoxM_In[6].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m6.Clutch.Trq_out_trg	= IF->GearBoxM_In[6].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m6.Clutch_dis.Pos		= IF->GearBoxM_In[6].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m6.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[6].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m6.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[6].Clutch_dis.Trq_out_trg;

    in->FromCM.GearBoxM_In.GB_m7.GearNoTrg		= IF->GearBoxM_In[7].GearNoTrg;
    in->FromCM.GearBoxM_In.GB_m7.GearNoTrg_dis		= IF->GearBoxM_In[7].GearNoTrg_dis;
    in->FromCM.GearBoxM_In.GB_m7.i_trg			= IF->GearBoxM_In[7].i_trg;
    in->FromCM.GearBoxM_In.GB_m7.set_ParkBrake		= IF->GearBoxM_In[7].set_ParkBrake;
    in->FromCM.GearBoxM_In.GB_m7.rotv_in_trg		= IF->GearBoxM_In[7].rotv_in_trg;
    in->FromCM.GearBoxM_In.GB_m7.Trq_out_trg		= IF->GearBoxM_In[7].Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m7.Clutch.Pos		= IF->GearBoxM_In[7].Clutch.Pos;
    in->FromCM.GearBoxM_In.GB_m7.Clutch.rotv_out_trg	= IF->GearBoxM_In[7].Clutch.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m7.Clutch.Trq_out_trg	= IF->GearBoxM_In[7].Clutch.Trq_out_trg;
    in->FromCM.GearBoxM_In.GB_m7.Clutch_dis.Pos		= IF->GearBoxM_In[7].Clutch_dis.Pos;
    in->FromCM.GearBoxM_In.GB_m7.Clutch_dis.rotv_out_trg	= IF->GearBoxM_In[7].Clutch_dis.rotv_out_trg;
    in->FromCM.GearBoxM_In.GB_m7.Clutch_dis.Trq_out_trg	= IF->GearBoxM_In[7].Clutch_dis.Trq_out_trg;
#endif

    in->FromCM.PwrSupplyIn.Pwr_HV1toLV_trg	= IF->PwrSupplyIn.Pwr_HV1toLV_trg;

    in->FromCM.WheelIn.FL.rot	= IF->WheelIn[0].rot;
    in->FromCM.WheelIn.FL.rotv	= IF->WheelIn[0].rotv;
    in->FromCM.WheelIn.FR.rot	= IF->WheelIn[1].rot;
    in->FromCM.WheelIn.FR.rotv	= IF->WheelIn[1].rotv;
    in->FromCM.WheelIn.RL.rot	= IF->WheelIn[2].rot;
    in->FromCM.WheelIn.RL.rotv	= IF->WheelIn[2].rotv;
    in->FromCM.WheelIn.RR.rot	= IF->WheelIn[3].rot;
    in->FromCM.WheelIn.RR.rotv	= IF->WheelIn[3].rotv;
#if defined (IS_TRUCK)
    in->FromCM.WheelIn.RL2.rot	= IF->WheelIn[4].rot;
    in->FromCM.WheelIn.RL2.rotv	= IF->WheelIn[4].rotv;
    in->FromCM.WheelIn.RR2.rot	= IF->WheelIn[5].rot;
    in->FromCM.WheelIn.RR2.rotv	= IF->WheelIn[5].rotv;
    in->FromCM.WheelIn.FL2.rot	= IF->WheelIn[6].rot;
    in->FromCM.WheelIn.FL2.rotv	= IF->WheelIn[6].rotv;
    in->FromCM.WheelIn.FR2.rot	= IF->WheelIn[7].rot;
    in->FromCM.WheelIn.FR2.rotv	= IF->WheelIn[7].rotv;
#endif

    if (SampleParams.UnderSampFac) {	// Undersampling
     	if (++SampleParams.UnderSampCount == SampleParams.UnderSampFac) {
	    SampleParams.UnderSampCount=0;
	    DoOneStep(rtm);
     	}
    } else { 				// Oversampling (1..OverSampFac)
	do {
	    DoOneStep(rtm);
	} while (++osCount < SampleParams.OverSampFac);
    }

    IF->ECU_Status	= out->ToCM.ECU_Status;

    IF->EngineOut.Engine_on	= out->ToCM.EngineOut.Engine_on;
    IF->EngineOut.rotv		= out->ToCM.EngineOut.rotv;
    IF->EngineOut.Trq		= out->ToCM.EngineOut.Trq;
    IF->EngineOut.TrqDrag	= out->ToCM.EngineOut.TrqDrag;
    IF->EngineOut.TrqFull	= out->ToCM.EngineOut.TrqFull;
    IF->EngineOut.TrqOpt	= out->ToCM.EngineOut.TrqOpt;
    IF->EngineOut.FuelFlow	= out->ToCM.EngineOut.FuelFlow;

    IF->MCU_Status	= out->ToCM.MCU_Status;

    IF->ISGOut.rotv		= out->ToCM.ISGOut.rotv;
    IF->ISGOut.Trq		= out->ToCM.ISGOut.Trq;
    IF->ISGOut.TrqMot_max	= out->ToCM.ISGOut.TrqMot_max;
    IF->ISGOut.TrqGen_max	= out->ToCM.ISGOut.TrqGen_max;
    IF->ISGOut.PwrElec		= out->ToCM.ISGOut.PwrElec;
    IF->ISGOut.i_M2W[0]		= out->ToCM.ISGOut.i_M2W.FL;
    IF->ISGOut.i_M2W[1]		= out->ToCM.ISGOut.i_M2W.FR;
    IF->ISGOut.i_M2W[2]		= out->ToCM.ISGOut.i_M2W.RL;
    IF->ISGOut.i_M2W[3]		= out->ToCM.ISGOut.i_M2W.RR;
#if defined (IS_TRUCK)
    IF->ISGOut.i_M2W[4]		= out->ToCM.ISGOut.i_M2W.RL2;
    IF->ISGOut.i_M2W[5]		= out->ToCM.ISGOut.i_M2W.RR2;
    IF->ISGOut.i_M2W[6]		= out->ToCM.ISGOut.i_M2W.FL2;
    IF->ISGOut.i_M2W[7]		= out->ToCM.ISGOut.i_M2W.FR2;
#endif

    IF->MotorOut[0].rotv		= out->ToCM.MotorOut.m0.rotv;
    IF->MotorOut[0].Trq			= out->ToCM.MotorOut.m0.Trq;
    IF->MotorOut[0].TrqMot_max		= out->ToCM.MotorOut.m0.TrqMot_max;
    IF->MotorOut[0].TrqGen_max		= out->ToCM.MotorOut.m0.TrqGen_max;
    IF->MotorOut[0].PwrElec		= out->ToCM.MotorOut.m0.PwrElec;
    IF->MotorOut[0].i_M2W[0]		= out->ToCM.MotorOut.m0.i_M2W.FL;
    IF->MotorOut[0].i_M2W[1]		= out->ToCM.MotorOut.m0.i_M2W.FR;
    IF->MotorOut[0].i_M2W[2]		= out->ToCM.MotorOut.m0.i_M2W.RL;
    IF->MotorOut[0].i_M2W[3]		= out->ToCM.MotorOut.m0.i_M2W.RR;
#if defined (IS_TRUCK)
    IF->MotorOut[0].i_M2W[4]		= out->ToCM.MotorOut.m0.i_M2W.RL2;
    IF->MotorOut[0].i_M2W[5]		= out->ToCM.MotorOut.m0.i_M2W.RR2;
    IF->MotorOut[0].i_M2W[6]		= out->ToCM.MotorOut.m0.i_M2W.FL2;
    IF->MotorOut[0].i_M2W[7]		= out->ToCM.MotorOut.m0.i_M2W.FR2;
#endif

    IF->MotorOut[1].rotv		= out->ToCM.MotorOut.m1.rotv;
    IF->MotorOut[1].Trq			= out->ToCM.MotorOut.m1.Trq;
    IF->MotorOut[1].TrqMot_max		= out->ToCM.MotorOut.m1.TrqMot_max;
    IF->MotorOut[1].TrqGen_max		= out->ToCM.MotorOut.m1.TrqGen_max;
    IF->MotorOut[1].PwrElec		= out->ToCM.MotorOut.m1.PwrElec;
    IF->MotorOut[1].i_M2W[0]		= out->ToCM.MotorOut.m1.i_M2W.FL;
    IF->MotorOut[1].i_M2W[1]		= out->ToCM.MotorOut.m1.i_M2W.FR;
    IF->MotorOut[1].i_M2W[2]		= out->ToCM.MotorOut.m1.i_M2W.RL;
    IF->MotorOut[1].i_M2W[3]		= out->ToCM.MotorOut.m1.i_M2W.RR;
#if defined (IS_TRUCK)
    IF->MotorOut[1].i_M2W[4]		= out->ToCM.MotorOut.m1.i_M2W.RL2;
    IF->MotorOut[1].i_M2W[5]		= out->ToCM.MotorOut.m1.i_M2W.RR2;
    IF->MotorOut[1].i_M2W[6]		= out->ToCM.MotorOut.m1.i_M2W.FL2;
    IF->MotorOut[1].i_M2W[7]		= out->ToCM.MotorOut.m1.i_M2W.FR2;
#endif

    IF->MotorOut[2].rotv		= out->ToCM.MotorOut.m2.rotv;
    IF->MotorOut[2].Trq			= out->ToCM.MotorOut.m2.Trq;
    IF->MotorOut[2].TrqMot_max		= out->ToCM.MotorOut.m2.TrqMot_max;
    IF->MotorOut[2].TrqGen_max		= out->ToCM.MotorOut.m2.TrqGen_max;
    IF->MotorOut[2].PwrElec		= out->ToCM.MotorOut.m2.PwrElec;
    IF->MotorOut[2].i_M2W[0]		= out->ToCM.MotorOut.m2.i_M2W.FL;
    IF->MotorOut[2].i_M2W[1]		= out->ToCM.MotorOut.m2.i_M2W.FR;
    IF->MotorOut[2].i_M2W[2]		= out->ToCM.MotorOut.m2.i_M2W.RL;
    IF->MotorOut[2].i_M2W[3]		= out->ToCM.MotorOut.m2.i_M2W.RR;
#if defined (IS_TRUCK)
    IF->MotorOut[2].i_M2W[4]		= out->ToCM.MotorOut.m2.i_M2W.RL2;
    IF->MotorOut[2].i_M2W[5]		= out->ToCM.MotorOut.m2.i_M2W.RR2;
    IF->MotorOut[2].i_M2W[6]		= out->ToCM.MotorOut.m2.i_M2W.FL2;
    IF->MotorOut[2].i_M2W[7]		= out->ToCM.MotorOut.m2.i_M2W.FR2;
#endif

    IF->MotorOut[3].rotv		= out->ToCM.MotorOut.m3.rotv;
    IF->MotorOut[3].Trq			= out->ToCM.MotorOut.m3.Trq;
    IF->MotorOut[3].TrqMot_max		= out->ToCM.MotorOut.m3.TrqMot_max;
    IF->MotorOut[3].TrqGen_max		= out->ToCM.MotorOut.m3.TrqGen_max;
    IF->MotorOut[3].PwrElec		= out->ToCM.MotorOut.m3.PwrElec;
    IF->MotorOut[3].i_M2W[0]		= out->ToCM.MotorOut.m3.i_M2W.FL;
    IF->MotorOut[3].i_M2W[1]		= out->ToCM.MotorOut.m3.i_M2W.FR;
    IF->MotorOut[3].i_M2W[2]		= out->ToCM.MotorOut.m3.i_M2W.RL;
    IF->MotorOut[3].i_M2W[3]		= out->ToCM.MotorOut.m3.i_M2W.RR;
#if defined (IS_TRUCK)
    IF->MotorOut[3].i_M2W[4]		= out->ToCM.MotorOut.m3.i_M2W.RL2;
    IF->MotorOut[3].i_M2W[5]		= out->ToCM.MotorOut.m3.i_M2W.RR2;
    IF->MotorOut[3].i_M2W[6]		= out->ToCM.MotorOut.m3.i_M2W.FL2;
    IF->MotorOut[3].i_M2W[7]		= out->ToCM.MotorOut.m3.i_M2W.FR2;
#endif

#if defined (IS_TRUCK)
    IF->MotorOut[4].rotv		= out->ToCM.MotorOut.m4.rotv;
    IF->MotorOut[4].Trq			= out->ToCM.MotorOut.m4.Trq;
    IF->MotorOut[4].TrqMot_max		= out->ToCM.MotorOut.m4.TrqMot_max;
    IF->MotorOut[4].TrqGen_max		= out->ToCM.MotorOut.m4.TrqGen_max;
    IF->MotorOut[4].PwrElec		= out->ToCM.MotorOut.m4.PwrElec;
    IF->MotorOut[4].i_M2W[0]		= out->ToCM.MotorOut.m4.i_M2W.FL;
    IF->MotorOut[4].i_M2W[1]		= out->ToCM.MotorOut.m4.i_M2W.FR;
    IF->MotorOut[4].i_M2W[2]		= out->ToCM.MotorOut.m4.i_M2W.RL;
    IF->MotorOut[4].i_M2W[3]		= out->ToCM.MotorOut.m4.i_M2W.RR;
    IF->MotorOut[4].i_M2W[4]		= out->ToCM.MotorOut.m4.i_M2W.RL2;
    IF->MotorOut[4].i_M2W[5]		= out->ToCM.MotorOut.m4.i_M2W.RR2;
    IF->MotorOut[4].i_M2W[6]		= out->ToCM.MotorOut.m4.i_M2W.FL2;
    IF->MotorOut[4].i_M2W[7]		= out->ToCM.MotorOut.m4.i_M2W.FR2;

    IF->MotorOut[5].rotv		= out->ToCM.MotorOut.m5.rotv;
    IF->MotorOut[5].Trq			= out->ToCM.MotorOut.m5.Trq;
    IF->MotorOut[5].TrqMot_max		= out->ToCM.MotorOut.m5.TrqMot_max;
    IF->MotorOut[5].TrqGen_max		= out->ToCM.MotorOut.m5.TrqGen_max;
    IF->MotorOut[5].PwrElec		= out->ToCM.MotorOut.m5.PwrElec;
    IF->MotorOut[5].i_M2W[0]		= out->ToCM.MotorOut.m5.i_M2W.FL;
    IF->MotorOut[5].i_M2W[1]		= out->ToCM.MotorOut.m5.i_M2W.FR;
    IF->MotorOut[5].i_M2W[2]		= out->ToCM.MotorOut.m5.i_M2W.RL;
    IF->MotorOut[5].i_M2W[3]		= out->ToCM.MotorOut.m5.i_M2W.RR;
    IF->MotorOut[5].i_M2W[4]		= out->ToCM.MotorOut.m5.i_M2W.RL2;
    IF->MotorOut[5].i_M2W[5]		= out->ToCM.MotorOut.m5.i_M2W.RR2;
    IF->MotorOut[5].i_M2W[6]		= out->ToCM.MotorOut.m5.i_M2W.FL2;
    IF->MotorOut[5].i_M2W[7]		= out->ToCM.MotorOut.m5.i_M2W.FR2;

    IF->MotorOut[6].rotv		= out->ToCM.MotorOut.m6.rotv;
    IF->MotorOut[6].Trq			= out->ToCM.MotorOut.m6.Trq;
    IF->MotorOut[6].TrqMot_max		= out->ToCM.MotorOut.m6.TrqMot_max;
    IF->MotorOut[6].TrqGen_max		= out->ToCM.MotorOut.m6.TrqGen_max;
    IF->MotorOut[6].PwrElec		= out->ToCM.MotorOut.m6.PwrElec;
    IF->MotorOut[6].i_M2W[0]		= out->ToCM.MotorOut.m6.i_M2W.FL;
    IF->MotorOut[6].i_M2W[1]		= out->ToCM.MotorOut.m6.i_M2W.FR;
    IF->MotorOut[6].i_M2W[2]		= out->ToCM.MotorOut.m6.i_M2W.RL;
    IF->MotorOut[6].i_M2W[3]		= out->ToCM.MotorOut.m6.i_M2W.RR;
    IF->MotorOut[6].i_M2W[4]		= out->ToCM.MotorOut.m6.i_M2W.RL2;
    IF->MotorOut[6].i_M2W[5]		= out->ToCM.MotorOut.m6.i_M2W.RR2;
    IF->MotorOut[6].i_M2W[6]		= out->ToCM.MotorOut.m6.i_M2W.FL2;
    IF->MotorOut[6].i_M2W[7]		= out->ToCM.MotorOut.m6.i_M2W.FR2;

    IF->MotorOut[7].rotv		= out->ToCM.MotorOut.m7.rotv;
    IF->MotorOut[7].Trq			= out->ToCM.MotorOut.m7.Trq;
    IF->MotorOut[7].TrqMot_max		= out->ToCM.MotorOut.m7.TrqMot_max;
    IF->MotorOut[7].TrqGen_max		= out->ToCM.MotorOut.m7.TrqGen_max;
    IF->MotorOut[7].PwrElec		= out->ToCM.MotorOut.m7.PwrElec;
    IF->MotorOut[7].i_M2W[0]		= out->ToCM.MotorOut.m7.i_M2W.FL;
    IF->MotorOut[7].i_M2W[1]		= out->ToCM.MotorOut.m7.i_M2W.FR;
    IF->MotorOut[7].i_M2W[2]		= out->ToCM.MotorOut.m7.i_M2W.RL;
    IF->MotorOut[7].i_M2W[3]		= out->ToCM.MotorOut.m7.i_M2W.RR;
    IF->MotorOut[7].i_M2W[4]		= out->ToCM.MotorOut.m7.i_M2W.RL2;
    IF->MotorOut[7].i_M2W[5]		= out->ToCM.MotorOut.m7.i_M2W.RR2;
    IF->MotorOut[7].i_M2W[6]		= out->ToCM.MotorOut.m7.i_M2W.FL2;
    IF->MotorOut[7].i_M2W[7]		= out->ToCM.MotorOut.m7.i_M2W.FR2;
#endif

    IF->ClutchOut.Pos		= out->ToCM.ClutchOut.Pos;
    IF->ClutchOut.rotv_in	= out->ToCM.ClutchOut.rotv_in;
    IF->ClutchOut.rotv_out	= out->ToCM.ClutchOut.rotv_out;
    IF->ClutchOut.Trq_in	= out->ToCM.ClutchOut.Trq_in;
    IF->ClutchOut.Trq_out	= out->ToCM.ClutchOut.Trq_out;
    IF->ClutchOut.i_TrqIn2Out	= out->ToCM.ClutchOut.i_TrqIn2Out;

    IF->GearBoxOut.GearNo		= out->ToCM.GearBoxOut.GearNo;
    IF->GearBoxOut.GearNo_dis		= out->ToCM.GearBoxOut.GearNo_dis;
    IF->GearBoxOut.Trq_DriveSrc_trg	= out->ToCM.GearBoxOut.Trq_DriveSrc_trg;
    IF->GearBoxOut.i			= out->ToCM.GearBoxOut.i;
    IF->GearBoxOut.rotv_in		= out->ToCM.GearBoxOut.rotv_in;
    IF->GearBoxOut.rotv_out		= out->ToCM.GearBoxOut.rotv_out;
    IF->GearBoxOut.Trq_in		= out->ToCM.GearBoxOut.Trq_in;
    IF->GearBoxOut.Trq_out		= out->ToCM.GearBoxOut.Trq_out;
    IF->GearBoxOut.Clutch.Pos		= out->ToCM.GearBoxOut.Clutch.Pos;
    IF->GearBoxOut.Clutch.rotv_in	= out->ToCM.GearBoxOut.Clutch.rotv_in;
    IF->GearBoxOut.Clutch.rotv_out	= out->ToCM.GearBoxOut.Clutch.rotv_out;
    IF->GearBoxOut.Clutch.Trq_in	= out->ToCM.GearBoxOut.Clutch.Trq_in;
    IF->GearBoxOut.Clutch.Trq_out	= out->ToCM.GearBoxOut.Clutch.Trq_out;
    IF->GearBoxOut.Clutch.i_TrqIn2Out	= out->ToCM.GearBoxOut.Clutch.i_TrqIn2Out;
    IF->GearBoxOut.Clutch_dis.Pos	= out->ToCM.GearBoxOut.Clutch_dis.Pos;
    IF->GearBoxOut.Clutch_dis.rotv_in	= out->ToCM.GearBoxOut.Clutch_dis.rotv_in;
    IF->GearBoxOut.Clutch_dis.rotv_out	= out->ToCM.GearBoxOut.Clutch_dis.rotv_out;
    IF->GearBoxOut.Clutch_dis.Trq_in	= out->ToCM.GearBoxOut.Clutch_dis.Trq_in;
    IF->GearBoxOut.Clutch_dis.Trq_out	= out->ToCM.GearBoxOut.Clutch_dis.Trq_out;
    IF->GearBoxOut.Clutch_dis.i_TrqIn2Out = out->ToCM.GearBoxOut.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[0].GearNo		= out->ToCM.GearBoxM_Out.GB_m0.GearNo;
    IF->GearBoxM_Out[0].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m0.GearNo_dis;
    IF->GearBoxM_Out[0].Trq_DriveSrc_trg	= out->ToCM.GearBoxM_Out.GB_m0.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[0].i		= out->ToCM.GearBoxM_Out.GB_m0.i;
    IF->GearBoxM_Out[0].rotv_in		= out->ToCM.GearBoxM_Out.GB_m0.rotv_in;
    IF->GearBoxM_Out[0].rotv_out	= out->ToCM.GearBoxM_Out.GB_m0.rotv_out;
    IF->GearBoxM_Out[0].Trq_in		= out->ToCM.GearBoxM_Out.GB_m0.Trq_in;
    IF->GearBoxM_Out[0].Trq_out		= out->ToCM.GearBoxM_Out.GB_m0.Trq_out;
    IF->GearBoxM_Out[0].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.Pos;
    IF->GearBoxM_Out[0].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.rotv_in;
    IF->GearBoxM_Out[0].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.rotv_out;
    IF->GearBoxM_Out[0].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.Trq_in;
    IF->GearBoxM_Out[0].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.Trq_out;
    IF->GearBoxM_Out[0].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[0].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Pos;
    IF->GearBoxM_Out[0].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[0].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[0].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[0].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[0].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m0.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[1].GearNo		= out->ToCM.GearBoxM_Out.GB_m1.GearNo;
    IF->GearBoxM_Out[1].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m1.GearNo_dis;
    IF->GearBoxM_Out[1].Trq_DriveSrc_trg	= out->ToCM.GearBoxM_Out.GB_m1.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[1].i		= out->ToCM.GearBoxM_Out.GB_m1.i;
    IF->GearBoxM_Out[1].rotv_in		= out->ToCM.GearBoxM_Out.GB_m1.rotv_in;
    IF->GearBoxM_Out[1].rotv_out	= out->ToCM.GearBoxM_Out.GB_m1.rotv_out;
    IF->GearBoxM_Out[1].Trq_in		= out->ToCM.GearBoxM_Out.GB_m1.Trq_in;
    IF->GearBoxM_Out[1].Trq_out		= out->ToCM.GearBoxM_Out.GB_m1.Trq_out;
    IF->GearBoxM_Out[1].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.Pos;
    IF->GearBoxM_Out[1].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.rotv_in;
    IF->GearBoxM_Out[1].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.rotv_out;
    IF->GearBoxM_Out[1].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.Trq_in;
    IF->GearBoxM_Out[1].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.Trq_out;
    IF->GearBoxM_Out[1].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[1].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Pos;
    IF->GearBoxM_Out[1].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[1].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[1].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[1].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[1].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m1.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[2].GearNo		= out->ToCM.GearBoxM_Out.GB_m2.GearNo;
    IF->GearBoxM_Out[2].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m2.GearNo_dis;
    IF->GearBoxM_Out[2].Trq_DriveSrc_trg	= out->ToCM.GearBoxM_Out.GB_m2.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[2].i		= out->ToCM.GearBoxM_Out.GB_m2.i;
    IF->GearBoxM_Out[2].rotv_in		= out->ToCM.GearBoxM_Out.GB_m2.rotv_in;
    IF->GearBoxM_Out[2].rotv_out	= out->ToCM.GearBoxM_Out.GB_m2.rotv_out;
    IF->GearBoxM_Out[2].Trq_in		= out->ToCM.GearBoxM_Out.GB_m2.Trq_in;
    IF->GearBoxM_Out[2].Trq_out		= out->ToCM.GearBoxM_Out.GB_m2.Trq_out;
    IF->GearBoxM_Out[2].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.Pos;
    IF->GearBoxM_Out[2].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.rotv_in;
    IF->GearBoxM_Out[2].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.rotv_out;
    IF->GearBoxM_Out[2].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.Trq_in;
    IF->GearBoxM_Out[2].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.Trq_out;
    IF->GearBoxM_Out[2].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[2].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Pos;
    IF->GearBoxM_Out[2].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[2].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[2].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[2].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[2].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m2.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[3].GearNo		= out->ToCM.GearBoxM_Out.GB_m3.GearNo;
    IF->GearBoxM_Out[3].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m3.GearNo_dis;
    IF->GearBoxM_Out[3].Trq_DriveSrc_trg	= out->ToCM.GearBoxM_Out.GB_m3.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[3].i		= out->ToCM.GearBoxM_Out.GB_m3.i;
    IF->GearBoxM_Out[3].rotv_in		= out->ToCM.GearBoxM_Out.GB_m3.rotv_in;
    IF->GearBoxM_Out[3].rotv_out	= out->ToCM.GearBoxM_Out.GB_m3.rotv_out;
    IF->GearBoxM_Out[3].Trq_in		= out->ToCM.GearBoxM_Out.GB_m3.Trq_in;
    IF->GearBoxM_Out[3].Trq_out		= out->ToCM.GearBoxM_Out.GB_m3.Trq_out;
    IF->GearBoxM_Out[3].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.Pos;
    IF->GearBoxM_Out[3].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.rotv_in;
    IF->GearBoxM_Out[3].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.rotv_out;
    IF->GearBoxM_Out[3].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.Trq_in;
    IF->GearBoxM_Out[3].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.Trq_out;
    IF->GearBoxM_Out[3].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[3].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Pos;
    IF->GearBoxM_Out[3].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[3].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[3].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[3].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[3].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m3.Clutch_dis.i_TrqIn2Out;

#if defined (IS_TRUCK)
    IF->GearBoxM_Out[4].GearNo		= out->ToCM.GearBoxM_Out.GB_m4.GearNo;
    IF->GearBoxM_Out[4].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m4.GearNo_dis;
    IF->GearBoxM_Out[4].Trq_DriveSrc_trg = out->ToCM.GearBoxM_Out.GB_m4.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[4].i		= out->ToCM.GearBoxM_Out.GB_m4.i;
    IF->GearBoxM_Out[4].rotv_in		= out->ToCM.GearBoxM_Out.GB_m4.rotv_in;
    IF->GearBoxM_Out[4].rotv_out	= out->ToCM.GearBoxM_Out.GB_m4.rotv_out;
    IF->GearBoxM_Out[4].Trq_in		= out->ToCM.GearBoxM_Out.GB_m4.Trq_in;
    IF->GearBoxM_Out[4].Trq_out		= out->ToCM.GearBoxM_Out.GB_m4.Trq_out;
    IF->GearBoxM_Out[4].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.Pos;
    IF->GearBoxM_Out[4].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.rotv_in;
    IF->GearBoxM_Out[4].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.rotv_out;
    IF->GearBoxM_Out[4].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.Trq_in;
    IF->GearBoxM_Out[4].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.Trq_out;
    IF->GearBoxM_Out[4].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[4].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.Pos;
    IF->GearBoxM_Out[4].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[4].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[4].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[4].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[4].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m4.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[5].GearNo		= out->ToCM.GearBoxM_Out.GB_m5.GearNo;
    IF->GearBoxM_Out[5].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m5.GearNo_dis;
    IF->GearBoxM_Out[5].Trq_DriveSrc_trg = out->ToCM.GearBoxM_Out.GB_m5.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[5].i		= out->ToCM.GearBoxM_Out.GB_m5.i;
    IF->GearBoxM_Out[5].rotv_in		= out->ToCM.GearBoxM_Out.GB_m5.rotv_in;
    IF->GearBoxM_Out[5].rotv_out	= out->ToCM.GearBoxM_Out.GB_m5.rotv_out;
    IF->GearBoxM_Out[5].Trq_in		= out->ToCM.GearBoxM_Out.GB_m5.Trq_in;
    IF->GearBoxM_Out[5].Trq_out		= out->ToCM.GearBoxM_Out.GB_m5.Trq_out;
    IF->GearBoxM_Out[5].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.Pos;
    IF->GearBoxM_Out[5].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.rotv_in;
    IF->GearBoxM_Out[5].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.rotv_out;
    IF->GearBoxM_Out[5].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.Trq_in;
    IF->GearBoxM_Out[5].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.Trq_out;
    IF->GearBoxM_Out[5].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[5].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.Pos;
    IF->GearBoxM_Out[5].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[5].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[5].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[5].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[5].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m5.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[6].GearNo		= out->ToCM.GearBoxM_Out.GB_m6.GearNo;
    IF->GearBoxM_Out[6].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m6.GearNo_dis;
    IF->GearBoxM_Out[6].Trq_DriveSrc_trg = out->ToCM.GearBoxM_Out.GB_m6.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[6].i		= out->ToCM.GearBoxM_Out.GB_m6.i;
    IF->GearBoxM_Out[6].rotv_in		= out->ToCM.GearBoxM_Out.GB_m6.rotv_in;
    IF->GearBoxM_Out[6].rotv_out	= out->ToCM.GearBoxM_Out.GB_m6.rotv_out;
    IF->GearBoxM_Out[6].Trq_in		= out->ToCM.GearBoxM_Out.GB_m6.Trq_in;
    IF->GearBoxM_Out[6].Trq_out		= out->ToCM.GearBoxM_Out.GB_m6.Trq_out;
    IF->GearBoxM_Out[6].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.Pos;
    IF->GearBoxM_Out[6].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.rotv_in;
    IF->GearBoxM_Out[6].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.rotv_out;
    IF->GearBoxM_Out[6].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.Trq_in;
    IF->GearBoxM_Out[6].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.Trq_out;
    IF->GearBoxM_Out[6].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[6].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.Pos;
    IF->GearBoxM_Out[6].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[6].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[6].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[6].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[6].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m6.Clutch_dis.i_TrqIn2Out;

    IF->GearBoxM_Out[7].GearNo		= out->ToCM.GearBoxM_Out.GB_m7.GearNo;
    IF->GearBoxM_Out[7].GearNo_dis	= out->ToCM.GearBoxM_Out.GB_m7.GearNo_dis;
    IF->GearBoxM_Out[7].Trq_DriveSrc_trg = out->ToCM.GearBoxM_Out.GB_m7.Trq_DriveSrc_trg;
    IF->GearBoxM_Out[7].i		= out->ToCM.GearBoxM_Out.GB_m7.i;
    IF->GearBoxM_Out[7].rotv_in		= out->ToCM.GearBoxM_Out.GB_m7.rotv_in;
    IF->GearBoxM_Out[7].rotv_out	= out->ToCM.GearBoxM_Out.GB_m7.rotv_out;
    IF->GearBoxM_Out[7].Trq_in		= out->ToCM.GearBoxM_Out.GB_m7.Trq_in;
    IF->GearBoxM_Out[7].Trq_out		= out->ToCM.GearBoxM_Out.GB_m7.Trq_out;
    IF->GearBoxM_Out[7].Clutch.Pos	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.Pos;
    IF->GearBoxM_Out[7].Clutch.rotv_in	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.rotv_in;
    IF->GearBoxM_Out[7].Clutch.rotv_out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.rotv_out;
    IF->GearBoxM_Out[7].Clutch.Trq_in	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.Trq_in;
    IF->GearBoxM_Out[7].Clutch.Trq_out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.Trq_out;
    IF->GearBoxM_Out[7].Clutch.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch.i_TrqIn2Out;
    IF->GearBoxM_Out[7].Clutch_dis.Pos		= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.Pos;
    IF->GearBoxM_Out[7].Clutch_dis.rotv_in	= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.rotv_in;
    IF->GearBoxM_Out[7].Clutch_dis.rotv_out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.rotv_out;
    IF->GearBoxM_Out[7].Clutch_dis.Trq_in	= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.Trq_in;
    IF->GearBoxM_Out[7].Clutch_dis.Trq_out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.Trq_out;
    IF->GearBoxM_Out[7].Clutch_dis.i_TrqIn2Out	= out->ToCM.GearBoxM_Out.GB_m7.Clutch_dis.i_TrqIn2Out;
#endif

    IF->BCU_Status	= out->ToCM.BCU_Status;

    IF->BattLVOut.SOC		= out->ToCM.BattLVOut.SOC;
    IF->BattLVOut.SOH		= out->ToCM.BattLVOut.SOH;
    IF->BattLVOut.Current	= out->ToCM.BattLVOut.Current;
    IF->BattLVOut.AOC		= out->ToCM.BattLVOut.AOC;
    IF->BattLVOut.Temp		= out->ToCM.BattLVOut.Temp;
    IF->BattLVOut.Energy	= out->ToCM.BattLVOut.Energy;
    IF->BattLVOut.Pwr_max	= out->ToCM.BattLVOut.Pwr_max;

    IF->BattHVOut.SOC		= out->ToCM.BattHVOut.SOC;
    IF->BattHVOut.SOH		= out->ToCM.BattHVOut.SOH;
    IF->BattHVOut.Current	= out->ToCM.BattHVOut.Current;
    IF->BattHVOut.AOC		= out->ToCM.BattHVOut.AOC;
    IF->BattHVOut.Temp		= out->ToCM.BattHVOut.Temp;
    IF->BattHVOut.Energy	= out->ToCM.BattHVOut.Energy;
    IF->BattHVOut.Pwr_max	= out->ToCM.BattHVOut.Pwr_max;

    IF->PwrSupplyOut.Pwr_LV		= out->ToCM.PwrSupplyOut.Pwr_LV;
    IF->PwrSupplyOut.Pwr_HV1		= out->ToCM.PwrSupplyOut.Pwr_HV1;
    IF->PwrSupplyOut.Pwr_HV2		= out->ToCM.PwrSupplyOut.Pwr_HV2;
    IF->PwrSupplyOut.Voltage_LV		= out->ToCM.PwrSupplyOut.Voltage_LV;
    IF->PwrSupplyOut.Voltage_HV1	= out->ToCM.PwrSupplyOut.Voltage_HV1;
    IF->PwrSupplyOut.Voltage_HV2	= out->ToCM.PwrSupplyOut.Voltage_HV2;
    IF->PwrSupplyOut.Pwr_HV1toLV	= out->ToCM.PwrSupplyOut.Pwr_HV1toLV;
    IF->PwrSupplyOut.Pwr_HV1toHV2	= out->ToCM.PwrSupplyOut.Pwr_HV1toHV2;
    IF->PwrSupplyOut.Pwr_HV1toLV_max	= out->ToCM.PwrSupplyOut.Pwr_HV1toLV_max;
    IF->PwrSupplyOut.Pwr_HV1toHV2_max	= out->ToCM.PwrSupplyOut.Pwr_HV1toHV2_max;
    IF->PwrSupplyOut.Eta_HV1toLV	= out->ToCM.PwrSupplyOut.Eta_HV1toLV;
    IF->PwrSupplyOut.Eta_HV1toHV2	= out->ToCM.PwrSupplyOut.Eta_HV1toHV2;

    IF->Trq_Supp2Bdy1[0]	= out->ToCM.Trq_Supp2Bdy1.rx;
    IF->Trq_Supp2Bdy1[1]	= out->ToCM.Trq_Supp2Bdy1.ry;
    IF->Trq_Supp2Bdy1[2]	= out->ToCM.Trq_Supp2Bdy1.rz;

    IF->Trq_Supp2Bdy1B[0]	= out->ToCM.Trq_Supp2Bdy1B.rx;
    IF->Trq_Supp2Bdy1B[1]	= out->ToCM.Trq_Supp2Bdy1B.ry;
    IF->Trq_Supp2Bdy1B[2]	= out->ToCM.Trq_Supp2Bdy1B.rz;

    IF->Trq_Supp2BdyEng[0]	= out->ToCM.Trq_Supp2BdyEng.rx;
    IF->Trq_Supp2BdyEng[1]	= out->ToCM.Trq_Supp2BdyEng.ry;

    IF->DL_iDiff_mean	= out->ToCM.DL_iDiff_mean;

    IF->WheelOut[0].Inert_in	= out->ToCM.WheelOut.FL.Inert_in;
    IF->WheelOut[0].Trq_Drive	= out->ToCM.WheelOut.FL.Trq_Drive;
    IF->WheelOut[0].Trq_Supp2WC	= out->ToCM.WheelOut.FL.Trq_Supp2WC;

    IF->WheelOut[1].Inert_in	= out->ToCM.WheelOut.FR.Inert_in;
    IF->WheelOut[1].Trq_Drive	= out->ToCM.WheelOut.FR.Trq_Drive;
    IF->WheelOut[1].Trq_Supp2WC	= out->ToCM.WheelOut.FR.Trq_Supp2WC;

    IF->WheelOut[2].Inert_in	= out->ToCM.WheelOut.RL.Inert_in;
    IF->WheelOut[2].Trq_Drive	= out->ToCM.WheelOut.RL.Trq_Drive;
    IF->WheelOut[2].Trq_Supp2WC	= out->ToCM.WheelOut.RL.Trq_Supp2WC;

    IF->WheelOut[3].Inert_in	= out->ToCM.WheelOut.RR.Inert_in;
    IF->WheelOut[3].Trq_Drive	= out->ToCM.WheelOut.RR.Trq_Drive;
    IF->WheelOut[3].Trq_Supp2WC	= out->ToCM.WheelOut.RR.Trq_Supp2WC;

#if defined (IS_TRUCK)
    IF->WheelOut[4].Inert_in	= out->ToCM.WheelOut.RL2.Inert_in;
    IF->WheelOut[4].Trq_Drive	= out->ToCM.WheelOut.RL2.Trq_Drive;
    IF->WheelOut[4].Trq_Supp2WC	= out->ToCM.WheelOut.RL2.Trq_Supp2WC;

    IF->WheelOut[5].Inert_in	= out->ToCM.WheelOut.RR2.Inert_in;
    IF->WheelOut[5].Trq_Drive	= out->ToCM.WheelOut.RR2.Trq_Drive;
    IF->WheelOut[5].Trq_Supp2WC	= out->ToCM.WheelOut.RR2.Trq_Supp2WC;

    IF->WheelOut[6].Inert_in	= out->ToCM.WheelOut.FL2.Inert_in;
    IF->WheelOut[6].Trq_Drive	= out->ToCM.WheelOut.FL2.Trq_Drive;
    IF->WheelOut[6].Trq_Supp2WC	= out->ToCM.WheelOut.FL2.Trq_Supp2WC;

    IF->WheelOut[7].Inert_in	= out->ToCM.WheelOut.FR2.Inert_in;
    IF->WheelOut[7].Trq_Drive	= out->ToCM.WheelOut.FR2.Trq_Drive;
    IF->WheelOut[7].Trq_Supp2WC	= out->ToCM.WheelOut.FR2.Trq_Supp2WC;
#endif

    IF->PowerDelta.PlanetGear	= out->ToCM.PowerDelta.PlanetGear;
    IF->PowerDelta.Diffs	= out->ToCM.PowerDelta.Diffs;
    IF->PowerDelta.Shafts	= out->ToCM.PowerDelta.Shafts;
    IF->PowerDelta.Spring_DL	= out->ToCM.PowerDelta.Spring_DL;
    IF->PowerDelta.Inert_DL	= out->ToCM.PowerDelta.Inert_DL;
    IF->PowerDelta.Inert	= out->ToCM.PowerDelta.Inert;
    IF->PowerDelta.PowerSupply	= out->ToCM.PowerDelta.PowerSupply;

    return 0;
}


int
MyPowerTrainXWD_Register (void)
{
    tModelClassDescr m;

    /*Log("%s_Register()\n", Modelname);*/

    memset(&m, 0, sizeof(m));

    /* Parameter file identification number.
       You may change CompatVersionId to the the lowest parameter
       file version understood by your model code. */
    m.PowerTrainXWD.VersionId		= PARAMID;
    m.PowerTrainXWD.CompatVersionId	= m.PowerTrainXWD.VersionId;

    m.PowerTrainXWD.DeclQuants		= MyPowerTrainXWD_DeclQuants;
    m.PowerTrainXWD.New			= MyPowerTrainXWD_New;
    m.PowerTrainXWD.Calc		= MyPowerTrainXWD_Calc;
    m.PowerTrainXWD.Delete		= MyPowerTrainXWD_Delete;
    /* Should only be used if the model doesn't read params from extra files */
    // m.PowerTrainXWD.ParamsChanged	= ParamsChanged_IgnoreCheck;

    return Model_Register(Modelclass, Modelname, &m);
}

