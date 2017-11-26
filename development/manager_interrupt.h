/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Interruption service routine manager.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: manager_interrupt.h
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
#ifndef MANAGER_INTERRUPT_H
#define	MANAGER_INTERRUPT_H

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
 * @Description 
 *  Handles hardware and software interrupts. The priority is defined as follows
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  TIMER 1
 *
 *      Flag: PIR1.TMR1IF
 *      Description: After every second, reloads timer 1 and update rtc.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  ADC
 *
 *      Flag: PIR1.ADIF
 *      Description:
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  USART RECEIVE
 *
 *      Flag: PIR1.RCIF
 *      Description: Process string commands received via serial port.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Param   
 *  void  
 * @Returns 
 *  void
 * @Error
 *  error[1] | Reception Overrun Error.
 *  error[2] | Reception Framing Error.
 * @See     
 *  errorParser#interpretError 
 */
void interrupt interruptServiceRoutine(void);

#endif