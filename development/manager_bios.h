/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Basic input/output system manager.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: manager_bios.h
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
#ifndef MANAGER_BIOS_H
#define	MANAGER_BIOS_H

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
 * @Configuration Bits 
 *  CONFIG1
 */
#pragma config FOSC  = XT
#pragma config WDTE  = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config BOREN = OFF
#pragma config LVP   = OFF
#pragma config CPD   = OFF
#pragma config WRT   = OFF
#pragma config CCPMX = RB0
#pragma config CP    = OFF

/**
 * @Configuration Bits 
 *  CONFIG2
 */
#pragma config FCMEN = OFF
#pragma config IESO  = OFF

/**
 * @ID Locations
 *  Software version: v1.00
 */
#pragma config IDLOC0 = 0x01
#pragma config IDLOC1 = 0x00

/**
 * @ID Locations
 *  Project ID: T, where it stands for TDI
 */
#pragma config IDLOC2 = 0x05
#pragma config IDLOC3 = 0x04

/**
 * @Description
 *  Calls routines to configure the uP, enabling interruptions
 * @Param
 *  void  
 * @Returns
 *  void
 */
void bootBios(void);

/**
 * @Description
 *  Resume the uP, enabling ADC and RTC features and interrupts.
 * @Param
 *  void  
 * @Returns
 *  void
 */
void resumeNode(void);

/**
 * @Description
 *  Freeze the uP, disabling ADC and RTC features and interrupts.
 * @Param
 *  void  
 * @Returns
 *  void
 */
void freezeNode(void);

/**
 * @Description
 *  Returns whether the uP is frozen or not.
 * @Param
 *  void  
 * @Returns
 *  freezeFlag | the uP is frozen flag
 */
bit isNodeFrozen(void);

/**
 * @Description
 *  Sets the uP awaken flag.
 * @Param
 *  void  
 * @Returns
 *  void
 */
void awakeNode(void);

/**
 * @Description
 *  Returns whether the uP is awaken to collect data from adc or not.
 * @Param
 *  void  
 * @Returns
 *  awakenFlag | the uP is awaken flag
 */
bit isNodeAwaken(void);

/**
 * @Description
 *  Sets the uP freeze flag.
 * @Param
 *  void  
 * @Returns
 *  void
 */
void resetNode(void);

/**
 * @Description
 *  Returns whether the uP must soft reset or not.
 * @Param
 *  void  
 * @Returns
 *  resetFlag | the uP is reset flag
 */
bit hasToResetNode(void);

#endif