/***************************************************** target specific file ***/
/*  Wrapper module for Simulink models                                        */
/*  ------------------------------------------------------------------------  */
/*  (c) IPG Automotive GmbH    www.ipg-automotive.com   Fon: +49.721.98520-0  */
/*  Bannwaldallee 60      D-76185 Karlsruhe   Germany   Fax: +49.721.98520-99 */
/******************************************************************************/

#ifndef __MYPOWERTRAINXWD_WRAP_H__
#define __MYPOWERTRAINXWD_WRAP_H__

#ifndef IS_CAR
# define IS_CAR
#endif

#ifdef __cplusplus
extern "C" {
#endif


struct tInfos;
struct tMdlBdyFrame;
struct tMatSuppDictDef;
struct tMatSuppTunables;


#ifdef CLASSIC_INTERFACE
# define rtModel_MyPowerTrainXWD          RT_MODEL_MyPowerTrainXWD_T
#else
# define rtModel_MyPowerTrainXWD          tag_RTM_MyPowerTrainXWD_T
#endif //CLASSIC_INTERFACE

#define ExternalInputs_MyPowerTrainXWD   ExtU_MyPowerTrainXWD_T
#define ExternalOutputs_MyPowerTrainXWD  ExtY_MyPowerTrainXWD_T

#ifndef MyPowerTrainXWD_rtModel
typedef struct rtModel_MyPowerTrainXWD rtModel_MyPowerTrainXWD;
#endif

/* Model registration function */
rtModel_MyPowerTrainXWD *MyPowerTrainXWD (struct tInfos *Inf);

#if defined(CLASSIC_INTERFACE) && !defined(CM4SLDS)
void rt_ODECreateIntegrationData (RTWSolverInfo *si);
void rt_ODEUpdateContinuousStates(RTWSolverInfo *si);
void rt_ODEDestroyIntegrationData(RTWSolverInfo *si);
#endif


/* Dictionary variables and other items of the model */
extern struct tMatSuppDictDef *MyPowerTrainXWD_DictDefines;
extern struct tMdlBdyFrame *MyPowerTrainXWD_BdyFrameDefines;


/* Wrapper functions */
void MyPowerTrainXWD_SetParams (rtModel_MyPowerTrainXWD *rtm,
			struct tMatSuppTunables *tuns,
			struct tInfos *Inf);
int MyPowerTrainXWD_Register (void);


#ifdef __cplusplus
}
#endif

#endif /* __MYPOWERTRAINXWD_WRAP_H__ */

