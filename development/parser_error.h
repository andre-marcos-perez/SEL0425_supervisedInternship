/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Error interpreter.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: parser_error.h
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
#ifndef PARSER_ERROR_H
#define	PARSER_ERROR_H

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
 *  Outputs the error number to inform the user the occurrence of an error. 
 *  Possible errors are:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Error
 *  error[01]: Reception Overrun Error.
 * @Cause
 *  The reception register RCREG was still full when new data was received 
 *  through usart.
 * @Action
 *  Software resets RCSTA<CREN> and flushes reception buffer.
 * @Solution
 *  Send the command again.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Error
 *  error[02]: Reception Framing Error.
 * @Cause
 *  The stop bit state in the usart reception was detected as low, violating the 
 *  standard Non-Return-to-Zero (NRZ) format used.
 * @Action
 *  Software flushes reception buffer.
 * @Solution
 *  Send the command again.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Error
 *  error[03]: Reception Buffer Overflow.
 * @Cause
 *  The reception buffer overflowed because the command sent was bigger than
 *  the biggest valid command.
 * @Action
 *  Software flushes reception buffer.
 * @Solution
 *  Send a valid command.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Error
 *  error[04]: Invalid Command.
 * @Cause
 *  The software could not parse the command sent because it is invalid.
 * @Action
 *  Software flushes reception buffer.
 * @Solution
 *  Send a valid command.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Error
 *  error[05]: Invalid Command Format.
 * @Cause
 *  The software could not perform the command sent because there was a mismatch
 *  between the command sent and the expected command format.
 * @Action
 *  Software flushes reception buffer.
 * @Solution
 *  Check command formats and send the command again.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Param   
 *  errorNumber | Is the number of the error occurred.
 * @Returns 
 *  void
 * @See
 *  commandParser#interpretCommand
 */
void interpretError(byte errorNumber);

#endif