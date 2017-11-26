/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Real time clock driver. Implemented by software on timer 1.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: driver_rtc.h
 *  File type: Header (.h)  
 *------------------------------------------------------------------------------
 * @DEVELOPMENT
 *  MCU:       Microchip® PIC16LF88
 *  IDE:       MPLAB® X v3.50  
 *  Compiler:  MPLAB® XC8 v1.40
 *------------------------------------------------------------------------------
 * @AUTHOR 
 *  Name:   Andre Marcos Perez
 *  E-mail: andre.marcos.perez@usp.br | andre_mperez@hotmail.com
 *------------------------------------------------------------------------------
 * @LEGACY
 *  Based on the original project 'tdi.X' of December 2014, developed by main 
 *  author Rafael Ferrarezzi and coop-authors Daniel Espanhol, Andre Torre Neto 
 *  and Vinicius Garcia. @see ./backupOriginal_TDI.rar
 *------------------------------------------------------------------------------
 * @VERSION
 *  First:  November of 2016
 *  Last:   March of 2017
 *------------------------------------------------------------------------------
 * @REVISION
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
 *  Author: 
 *  Date:   
 *  Mod:    
 ******************************************************************************/

/**
 * @HeaderGuard
 *  Pre-processor header guard opening conditional statement
 */ 
#ifndef DRIVER_RTC_H
#define	DRIVER_RTC_H

/**
 * @Include
 *  MPLAB® XC8 v1.40 compiler library
 *  uP library
 */
#ifndef COMPILER
#include <xc.h>
#include <pic16lf88.h>
#endif

/**
 * @Oscillator 
 *  Crystal oscillator frequency
 */
#ifndef OSCILLATOR
#define _XTAL_FREQ 4000000
#endif

/*
 * @CodeConvention
 */
#ifndef byte
typedef unsigned char byte;
#define byte byte
#define BYTE_MIN 0
#define BYTE_MAX 255
#endif

/**
 * @Macro
 * Macro to disable real time clock interrupt on timer 1
 */
#define disableRtcInterrupt() (PIE1bits.TMR1IE = 0)

/**
 * @Macro
 * Macro to enable real time clock interrupt on timer 1
 */
#define enableRtcInterrupt() (PIE1bits.TMR1IE = 1)

/**
 * @Description
 *  Handles real time clock configuration, enabling it's interrupt on timer 1. 
 * @Param
 *  void  
 * @Returns
 *  void
 */
void bootRtc(void);

/**
 * @Description
 *  Configures real time clock for 1 second overflow on timer 1. 
 * @Param
 *  void  
 * @Returns
 *  void
 */
void rtcReload(void);

/**
 * @Description
 *  Sets up real time clock time and date.
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  year   | The real time clock year
 *  month  | The real time clock month
 *  day    | The real time clock day
 *  hour   | The real time clock hour
 *  minute | The real time clock minute 
 *  second | The real time clock second 
 * @Returns
 *  void 
 */
void rtcSetClock(byte year, byte month, byte day,
                 byte hour, byte minute, byte second);

/**
 * @Description
 *  Returns the real time clock second
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  second | The real time clock second  
 */
byte rtcGetSecond(void);

/**
 * @Description
 *  Returns the real time clock minute
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  minute | The real time clock minute  
 */
byte rtcGetMinute(void);

/**
 * @Description
 *  Returns the real time clock hour
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  hour | The real time clock hour  
 */
byte rtcGetHour(void);

/**
 * @Description
 *  Returns the real time clock day
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  day | The real time clock day  
 */
byte rtcGetDay(void);

/**
 * @Description
 *  Returns the real time clock month
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  month | The real time clock month  
 */
byte rtcGetMonth(void);

/**
 * @Description
 *  Returns the real time clock year
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  year | The real time clock year  
 */
byte rtcGetYear(void);

/**
 * @Description
 *  Updates the real time clock by 1 second
 * @Precondition
 *  rtcManager#rtcInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  void 
 */
void rtcUpdate(void);

#endif