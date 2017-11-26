/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Analog-Digital Converter driver.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: driver_adc.h
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
#ifndef DRIVER_ADC_H
#define	DRIVER_ADC_H

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
 *  Handles Analogic Digital Converter initial configuration.  
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  # of Channels : 5               | ANSEL.<6:0>  = 0011111
 *  Format Result : Left justified  | ADCON1.ADFM = 0
 *  Clock Division: Disabled        | ADCON1.ADCS2 = 0
 *  Voltage Ref.  : VREF+           | ADCON1.VCFG<1:0> = 10
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Param
 *  void  
 * @Returns
 *  void
 */
void bootAdc(void);

/**
 * @Description
 *  Performs and returns adc data
 * @Precondition
 *  driver_adc#adcInitialize must have been called previously
 * @Param   
 *  channel | Is the adc channel
 * @Returns 
 *  ADRESH  | Is the register that the adc data is stored
 */
byte adcRead(byte channel);

/**
 * @Description
 *  Collects the data from the adc channels and stores them in the buffer.
 * @Precondition
 *  driver_adc#adcInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  void
 */
void adcReadChannels(void);

#endif
