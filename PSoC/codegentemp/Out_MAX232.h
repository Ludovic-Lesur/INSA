/*******************************************************************************
* File Name: Out_MAX232.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Out_MAX232_H)
#define CY_PWM_Out_MAX232_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Out_MAX232_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Out_MAX232_Resolution                     (16u)
#define Out_MAX232_UsingFixedFunction             (0u)
#define Out_MAX232_DeadBandMode                   (0u)
#define Out_MAX232_KillModeMinTime                (0u)
#define Out_MAX232_KillMode                       (0u)
#define Out_MAX232_PWMMode                        (1u)
#define Out_MAX232_PWMModeIsCenterAligned         (0u)
#define Out_MAX232_DeadBandUsed                   (0u)
#define Out_MAX232_DeadBand2_4                    (0u)

#if !defined(Out_MAX232_PWMUDB_genblk8_stsreg__REMOVED)
    #define Out_MAX232_UseStatus                  (0u)
#else
    #define Out_MAX232_UseStatus                  (0u)
#endif /* !defined(Out_MAX232_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Out_MAX232_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Out_MAX232_UseControl                 (0u)
#else
    #define Out_MAX232_UseControl                 (0u)
#endif /* !defined(Out_MAX232_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Out_MAX232_UseOneCompareMode              (0u)
#define Out_MAX232_MinimumKillTime                (1u)
#define Out_MAX232_EnableMode                     (1u)

#define Out_MAX232_CompareMode1SW                 (0u)
#define Out_MAX232_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Out_MAX232__B_PWM__DISABLED 0
#define Out_MAX232__B_PWM__ASYNCHRONOUS 1
#define Out_MAX232__B_PWM__SINGLECYCLE 2
#define Out_MAX232__B_PWM__LATCHED 3
#define Out_MAX232__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Out_MAX232__B_PWM__DBMDISABLED 0
#define Out_MAX232__B_PWM__DBM_2_4_CLOCKS 1
#define Out_MAX232__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Out_MAX232__B_PWM__ONE_OUTPUT 0
#define Out_MAX232__B_PWM__TWO_OUTPUTS 1
#define Out_MAX232__B_PWM__DUAL_EDGE 2
#define Out_MAX232__B_PWM__CENTER_ALIGN 3
#define Out_MAX232__B_PWM__DITHER 5
#define Out_MAX232__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Out_MAX232__B_PWM__LESS_THAN 1
#define Out_MAX232__B_PWM__LESS_THAN_OR_EQUAL 2
#define Out_MAX232__B_PWM__GREATER_THAN 3
#define Out_MAX232__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Out_MAX232__B_PWM__EQUAL 0
#define Out_MAX232__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Out_MAX232_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Out_MAX232_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Out_MAX232_PWMModeIsCenterAligned) */
        #if (Out_MAX232_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Out_MAX232_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_256_CLOCKS || \
            Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Out_MAX232_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Out_MAX232_KillModeMinTime) */

        /* Backup control register */
        #if(Out_MAX232_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Out_MAX232_UseControl) */

    #endif /* (!Out_MAX232_UsingFixedFunction) */

}Out_MAX232_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Out_MAX232_Start(void) ;
void    Out_MAX232_Stop(void) ;

#if (Out_MAX232_UseStatus || Out_MAX232_UsingFixedFunction)
    void  Out_MAX232_SetInterruptMode(uint8 interruptMode) ;
    uint8 Out_MAX232_ReadStatusRegister(void) ;
#endif /* (Out_MAX232_UseStatus || Out_MAX232_UsingFixedFunction) */

#define Out_MAX232_GetInterruptSource() Out_MAX232_ReadStatusRegister()

#if (Out_MAX232_UseControl)
    uint8 Out_MAX232_ReadControlRegister(void) ;
    void  Out_MAX232_WriteControlRegister(uint8 control)
          ;
#endif /* (Out_MAX232_UseControl) */

#if (Out_MAX232_UseOneCompareMode)
   #if (Out_MAX232_CompareMode1SW)
       void    Out_MAX232_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Out_MAX232_CompareMode1SW) */
#else
    #if (Out_MAX232_CompareMode1SW)
        void    Out_MAX232_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Out_MAX232_CompareMode1SW) */
    #if (Out_MAX232_CompareMode2SW)
        void    Out_MAX232_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Out_MAX232_CompareMode2SW) */
#endif /* (Out_MAX232_UseOneCompareMode) */

#if (!Out_MAX232_UsingFixedFunction)
    uint16   Out_MAX232_ReadCounter(void) ;
    uint16 Out_MAX232_ReadCapture(void) ;

    #if (Out_MAX232_UseStatus)
            void Out_MAX232_ClearFIFO(void) ;
    #endif /* (Out_MAX232_UseStatus) */

    void    Out_MAX232_WriteCounter(uint16 counter)
            ;
#endif /* (!Out_MAX232_UsingFixedFunction) */

void    Out_MAX232_WritePeriod(uint16 period)
        ;
uint16 Out_MAX232_ReadPeriod(void) ;

#if (Out_MAX232_UseOneCompareMode)
    void    Out_MAX232_WriteCompare(uint16 compare)
            ;
    uint16 Out_MAX232_ReadCompare(void) ;
#else
    void    Out_MAX232_WriteCompare1(uint16 compare)
            ;
    uint16 Out_MAX232_ReadCompare1(void) ;
    void    Out_MAX232_WriteCompare2(uint16 compare)
            ;
    uint16 Out_MAX232_ReadCompare2(void) ;
#endif /* (Out_MAX232_UseOneCompareMode) */


#if (Out_MAX232_DeadBandUsed)
    void    Out_MAX232_WriteDeadTime(uint8 deadtime) ;
    uint8   Out_MAX232_ReadDeadTime(void) ;
#endif /* (Out_MAX232_DeadBandUsed) */

#if ( Out_MAX232_KillModeMinTime)
    void Out_MAX232_WriteKillTime(uint8 killtime) ;
    uint8 Out_MAX232_ReadKillTime(void) ;
#endif /* ( Out_MAX232_KillModeMinTime) */

void Out_MAX232_Init(void) ;
void Out_MAX232_Enable(void) ;
void Out_MAX232_Sleep(void) ;
void Out_MAX232_Wakeup(void) ;
void Out_MAX232_SaveConfig(void) ;
void Out_MAX232_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Out_MAX232_INIT_PERIOD_VALUE          (299u)
#define Out_MAX232_INIT_COMPARE_VALUE1        (150u)
#define Out_MAX232_INIT_COMPARE_VALUE2        (150u)
#define Out_MAX232_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Out_MAX232_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Out_MAX232_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Out_MAX232_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Out_MAX232_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Out_MAX232_DEFAULT_COMPARE2_MODE      (uint8)((uint8)2u <<  Out_MAX232_CTRL_CMPMODE2_SHIFT)
#define Out_MAX232_DEFAULT_COMPARE1_MODE      (uint8)((uint8)4u <<  Out_MAX232_CTRL_CMPMODE1_SHIFT)
#define Out_MAX232_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Out_MAX232_UsingFixedFunction)
   #define Out_MAX232_PERIOD_LSB              (*(reg16 *) Out_MAX232_PWMHW__PER0)
   #define Out_MAX232_PERIOD_LSB_PTR          ( (reg16 *) Out_MAX232_PWMHW__PER0)
   #define Out_MAX232_COMPARE1_LSB            (*(reg16 *) Out_MAX232_PWMHW__CNT_CMP0)
   #define Out_MAX232_COMPARE1_LSB_PTR        ( (reg16 *) Out_MAX232_PWMHW__CNT_CMP0)
   #define Out_MAX232_COMPARE2_LSB            (0x00u)
   #define Out_MAX232_COMPARE2_LSB_PTR        (0x00u)
   #define Out_MAX232_COUNTER_LSB             (*(reg16 *) Out_MAX232_PWMHW__CNT_CMP0)
   #define Out_MAX232_COUNTER_LSB_PTR         ( (reg16 *) Out_MAX232_PWMHW__CNT_CMP0)
   #define Out_MAX232_CAPTURE_LSB             (*(reg16 *) Out_MAX232_PWMHW__CAP0)
   #define Out_MAX232_CAPTURE_LSB_PTR         ( (reg16 *) Out_MAX232_PWMHW__CAP0)
   #define Out_MAX232_RT1                     (*(reg8 *)  Out_MAX232_PWMHW__RT1)
   #define Out_MAX232_RT1_PTR                 ( (reg8 *)  Out_MAX232_PWMHW__RT1)

#else
   #if (Out_MAX232_Resolution == 8u) /* 8bit - PWM */

       #if(Out_MAX232_PWMModeIsCenterAligned)
           #define Out_MAX232_PERIOD_LSB      (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Out_MAX232_PERIOD_LSB_PTR  ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Out_MAX232_PERIOD_LSB      (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Out_MAX232_PERIOD_LSB_PTR  ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Out_MAX232_PWMModeIsCenterAligned) */

       #define Out_MAX232_COMPARE1_LSB        (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Out_MAX232_COMPARE1_LSB_PTR    ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Out_MAX232_COMPARE2_LSB        (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Out_MAX232_COMPARE2_LSB_PTR    ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Out_MAX232_COUNTERCAP_LSB      (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Out_MAX232_COUNTERCAP_LSB_PTR  ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Out_MAX232_COUNTER_LSB         (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Out_MAX232_COUNTER_LSB_PTR     ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Out_MAX232_CAPTURE_LSB         (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Out_MAX232_CAPTURE_LSB_PTR     ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Out_MAX232_PWMModeIsCenterAligned)
               #define Out_MAX232_PERIOD_LSB      (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Out_MAX232_PERIOD_LSB_PTR  ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Out_MAX232_PERIOD_LSB      (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Out_MAX232_PERIOD_LSB_PTR  ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Out_MAX232_PWMModeIsCenterAligned) */

            #define Out_MAX232_COMPARE1_LSB       (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Out_MAX232_COMPARE1_LSB_PTR   ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Out_MAX232_COMPARE2_LSB       (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Out_MAX232_COMPARE2_LSB_PTR   ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Out_MAX232_COUNTERCAP_LSB     (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Out_MAX232_COUNTERCAP_LSB_PTR ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Out_MAX232_COUNTER_LSB        (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Out_MAX232_COUNTER_LSB_PTR    ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Out_MAX232_CAPTURE_LSB        (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Out_MAX232_CAPTURE_LSB_PTR    ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Out_MAX232_PWMModeIsCenterAligned)
               #define Out_MAX232_PERIOD_LSB      (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Out_MAX232_PERIOD_LSB_PTR  ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Out_MAX232_PERIOD_LSB      (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Out_MAX232_PERIOD_LSB_PTR  ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Out_MAX232_PWMModeIsCenterAligned) */

            #define Out_MAX232_COMPARE1_LSB       (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Out_MAX232_COMPARE1_LSB_PTR   ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Out_MAX232_COMPARE2_LSB       (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Out_MAX232_COMPARE2_LSB_PTR   ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Out_MAX232_COUNTERCAP_LSB     (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Out_MAX232_COUNTERCAP_LSB_PTR ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Out_MAX232_COUNTER_LSB        (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Out_MAX232_COUNTER_LSB_PTR    ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Out_MAX232_CAPTURE_LSB        (*(reg16 *) Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Out_MAX232_CAPTURE_LSB_PTR    ((reg16 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Out_MAX232_AUX_CONTROLDP1          (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Out_MAX232_AUX_CONTROLDP1_PTR      ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Out_MAX232_Resolution == 8) */

   #define Out_MAX232_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Out_MAX232_AUX_CONTROLDP0          (*(reg8 *)  Out_MAX232_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Out_MAX232_AUX_CONTROLDP0_PTR      ((reg8 *)   Out_MAX232_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Out_MAX232_UsingFixedFunction) */

#if(Out_MAX232_KillModeMinTime )
    #define Out_MAX232_KILLMODEMINTIME        (*(reg8 *)  Out_MAX232_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Out_MAX232_KILLMODEMINTIME_PTR    ((reg8 *)   Out_MAX232_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Out_MAX232_KillModeMinTime ) */

#if(Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_256_CLOCKS)
    #define Out_MAX232_DEADBAND_COUNT         (*(reg8 *)  Out_MAX232_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Out_MAX232_DEADBAND_COUNT_PTR     ((reg8 *)   Out_MAX232_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Out_MAX232_DEADBAND_LSB_PTR       ((reg8 *)   Out_MAX232_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Out_MAX232_DEADBAND_LSB           (*(reg8 *)  Out_MAX232_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Out_MAX232_UsingFixedFunction)
        #define Out_MAX232_DEADBAND_COUNT         (*(reg8 *)  Out_MAX232_PWMHW__CFG0)
        #define Out_MAX232_DEADBAND_COUNT_PTR     ((reg8 *)   Out_MAX232_PWMHW__CFG0)
        #define Out_MAX232_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Out_MAX232_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Out_MAX232_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Out_MAX232_DEADBAND_COUNT         (*(reg8 *)  Out_MAX232_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Out_MAX232_DEADBAND_COUNT_PTR     ((reg8 *)   Out_MAX232_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Out_MAX232_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Out_MAX232_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Out_MAX232_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Out_MAX232_UsingFixedFunction) */
#endif /* (Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_256_CLOCKS) */



#if (Out_MAX232_UsingFixedFunction)
    #define Out_MAX232_STATUS                 (*(reg8 *) Out_MAX232_PWMHW__SR0)
    #define Out_MAX232_STATUS_PTR             ((reg8 *) Out_MAX232_PWMHW__SR0)
    #define Out_MAX232_STATUS_MASK            (*(reg8 *) Out_MAX232_PWMHW__SR0)
    #define Out_MAX232_STATUS_MASK_PTR        ((reg8 *) Out_MAX232_PWMHW__SR0)
    #define Out_MAX232_CONTROL                (*(reg8 *) Out_MAX232_PWMHW__CFG0)
    #define Out_MAX232_CONTROL_PTR            ((reg8 *) Out_MAX232_PWMHW__CFG0)
    #define Out_MAX232_CONTROL2               (*(reg8 *) Out_MAX232_PWMHW__CFG1)
    #define Out_MAX232_CONTROL3               (*(reg8 *) Out_MAX232_PWMHW__CFG2)
    #define Out_MAX232_GLOBAL_ENABLE          (*(reg8 *) Out_MAX232_PWMHW__PM_ACT_CFG)
    #define Out_MAX232_GLOBAL_ENABLE_PTR      ( (reg8 *) Out_MAX232_PWMHW__PM_ACT_CFG)
    #define Out_MAX232_GLOBAL_STBY_ENABLE     (*(reg8 *) Out_MAX232_PWMHW__PM_STBY_CFG)
    #define Out_MAX232_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Out_MAX232_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Out_MAX232_BLOCK_EN_MASK          (Out_MAX232_PWMHW__PM_ACT_MSK)
    #define Out_MAX232_BLOCK_STBY_EN_MASK     (Out_MAX232_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Out_MAX232_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Out_MAX232_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Out_MAX232_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Out_MAX232_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Out_MAX232_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Out_MAX232_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Out_MAX232_CTRL_ENABLE            (uint8)((uint8)0x01u << Out_MAX232_CTRL_ENABLE_SHIFT)
    #define Out_MAX232_CTRL_RESET             (uint8)((uint8)0x01u << Out_MAX232_CTRL_RESET_SHIFT)
    #define Out_MAX232_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Out_MAX232_CTRL_CMPMODE2_SHIFT)
    #define Out_MAX232_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Out_MAX232_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Out_MAX232_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Out_MAX232_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Out_MAX232_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Out_MAX232_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Out_MAX232_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Out_MAX232_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Out_MAX232_STATUS_TC_INT_EN_MASK_SHIFT            (Out_MAX232_STATUS_TC_SHIFT - 4u)
    #define Out_MAX232_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Out_MAX232_STATUS_CMP1_INT_EN_MASK_SHIFT          (Out_MAX232_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Out_MAX232_STATUS_TC              (uint8)((uint8)0x01u << Out_MAX232_STATUS_TC_SHIFT)
    #define Out_MAX232_STATUS_CMP1            (uint8)((uint8)0x01u << Out_MAX232_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Out_MAX232_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Out_MAX232_STATUS_TC >> 4u)
    #define Out_MAX232_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Out_MAX232_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Out_MAX232_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Out_MAX232_RT1_MASK              (uint8)((uint8)0x03u << Out_MAX232_RT1_SHIFT)
    #define Out_MAX232_SYNC                  (uint8)((uint8)0x03u << Out_MAX232_RT1_SHIFT)
    #define Out_MAX232_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Out_MAX232_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Out_MAX232_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Out_MAX232_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Out_MAX232_SYNCDSI_SHIFT)


#else
    #define Out_MAX232_STATUS                (*(reg8 *)   Out_MAX232_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Out_MAX232_STATUS_PTR            ((reg8 *)    Out_MAX232_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Out_MAX232_STATUS_MASK           (*(reg8 *)   Out_MAX232_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Out_MAX232_STATUS_MASK_PTR       ((reg8 *)    Out_MAX232_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Out_MAX232_STATUS_AUX_CTRL       (*(reg8 *)   Out_MAX232_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Out_MAX232_CONTROL               (*(reg8 *)   Out_MAX232_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Out_MAX232_CONTROL_PTR           ((reg8 *)    Out_MAX232_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Out_MAX232_CTRL_ENABLE_SHIFT      (0x07u)
    #define Out_MAX232_CTRL_RESET_SHIFT       (0x06u)
    #define Out_MAX232_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Out_MAX232_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Out_MAX232_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Out_MAX232_CTRL_ENABLE            (uint8)((uint8)0x01u << Out_MAX232_CTRL_ENABLE_SHIFT)
    #define Out_MAX232_CTRL_RESET             (uint8)((uint8)0x01u << Out_MAX232_CTRL_RESET_SHIFT)
    #define Out_MAX232_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Out_MAX232_CTRL_CMPMODE2_SHIFT)
    #define Out_MAX232_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Out_MAX232_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Out_MAX232_STATUS_KILL_SHIFT          (0x05u)
    #define Out_MAX232_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Out_MAX232_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Out_MAX232_STATUS_TC_SHIFT            (0x02u)
    #define Out_MAX232_STATUS_CMP2_SHIFT          (0x01u)
    #define Out_MAX232_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Out_MAX232_STATUS_KILL_INT_EN_MASK_SHIFT          (Out_MAX232_STATUS_KILL_SHIFT)
    #define Out_MAX232_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Out_MAX232_STATUS_FIFONEMPTY_SHIFT)
    #define Out_MAX232_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Out_MAX232_STATUS_FIFOFULL_SHIFT)
    #define Out_MAX232_STATUS_TC_INT_EN_MASK_SHIFT            (Out_MAX232_STATUS_TC_SHIFT)
    #define Out_MAX232_STATUS_CMP2_INT_EN_MASK_SHIFT          (Out_MAX232_STATUS_CMP2_SHIFT)
    #define Out_MAX232_STATUS_CMP1_INT_EN_MASK_SHIFT          (Out_MAX232_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Out_MAX232_STATUS_KILL            (uint8)((uint8)0x00u << Out_MAX232_STATUS_KILL_SHIFT )
    #define Out_MAX232_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Out_MAX232_STATUS_FIFOFULL_SHIFT)
    #define Out_MAX232_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Out_MAX232_STATUS_FIFONEMPTY_SHIFT)
    #define Out_MAX232_STATUS_TC              (uint8)((uint8)0x01u << Out_MAX232_STATUS_TC_SHIFT)
    #define Out_MAX232_STATUS_CMP2            (uint8)((uint8)0x01u << Out_MAX232_STATUS_CMP2_SHIFT)
    #define Out_MAX232_STATUS_CMP1            (uint8)((uint8)0x01u << Out_MAX232_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Out_MAX232_STATUS_KILL_INT_EN_MASK            (Out_MAX232_STATUS_KILL)
    #define Out_MAX232_STATUS_FIFOFULL_INT_EN_MASK        (Out_MAX232_STATUS_FIFOFULL)
    #define Out_MAX232_STATUS_FIFONEMPTY_INT_EN_MASK      (Out_MAX232_STATUS_FIFONEMPTY)
    #define Out_MAX232_STATUS_TC_INT_EN_MASK              (Out_MAX232_STATUS_TC)
    #define Out_MAX232_STATUS_CMP2_INT_EN_MASK            (Out_MAX232_STATUS_CMP2)
    #define Out_MAX232_STATUS_CMP1_INT_EN_MASK            (Out_MAX232_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Out_MAX232_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Out_MAX232_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Out_MAX232_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Out_MAX232_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Out_MAX232_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Out_MAX232_UsingFixedFunction */

#endif  /* CY_PWM_Out_MAX232_H */


/* [] END OF FILE */
