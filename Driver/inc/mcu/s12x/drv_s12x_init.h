/**
 * @file mcu_init.h
 *
 * @brief S12XS64 Series MCU Clock initializing for ESS Board
 *        Tier Company:KOA AUTOMOTIVE, Target: S12XS64MAE
 *
 ********************************************************************************
* \copyright
* copyright 2025. autocrypt, inc. all rights reserved.
* you may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef DRV_S12X_INIT_H
#define DRV_S12X_INIT_H

#ifdef __cplusplus
extern "c" {
#endif

#if defined(__HIWARE__) && defined(__HCS12X__)/* MCU */
/*
 * DevNote.HardWare Config Info
 * 1. Ext. Osc. Freq: 8MHz
 * 2. Core Clock    : 32MHz
 * 3. BUS Clock     : 32MHz
 */
//...
#define CPU_BUS_CLK_HZ              32000000UL /* Initial value of the bus clock frequency in Hz */

#define CPU_INSTR_CLK_HZ            32000000UL /* Initial value of the instruction clock frequency in Hz */

#define CPU_EXT_CLK_HZ              8000000UL /* Value of the main clock frequency (crystal or external clock) in Hz */

#define CPU_TICK_NS                 125U /* CPU tick is a unit derived from the frequency of external clock source. If no external clock is enabled or available it is derived from the value of internal clock source. The value of this constant represents period of the clock source in ns. */
//...

/* Whole peripheral register access macros */
#define setReg8(RegName, val)                                    (RegName = (byte)(val))
//...

/* Bits peripheral register access macros */
//...
#define setReg8Bits(RegName, SetMask)                            (RegName |= (byte)(SetMask))
//...

void INIT_setup_Mcu_Clk(void);

#endif /* defined(__HIWARE__) && defined(__HCS12X__) *//* MCU */

#ifdef __cplusplus
}
#endif

#endif /* DRV_S12X_INIT_H */
