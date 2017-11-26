/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Serial user interface command interpreter.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: parser_command.h
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
#ifndef PARSER_COMMAND_H
#define	PARSER_COMMAND_H

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
 *  Parses and interprets the array of text commands received during the usart 
 *  serial communication stored in the reception buffer, flushing it at the end. 
 *  Possible commands are:
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: B
 *  Function:        Group
 * 
 *      Full Command:   B<CR>        
 *      Description:    Queries node's group id
 * 
 *      Full Command:   B=XX<CR>        
 *      Description:    Sets node to the group GG
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: C
 *  Function:        Data collection 
 * 
 *      Full Command:   C<CR>        
 *      Description:    Queries data collection parameters
 * 
 *      Full Command:   C=20YY-MM-DD HH:MM:SS II<CR>        
 *      Description:    Sets data collection parameters    
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: D
 *  Function:          
 * 
 *      Full Command:   <CR>        
 *      Description:    
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: F
 *  Function:        Freeze 
 * 
 *      Full Command:   F<CR>        
 *      Description:    Disable ADC and RTC features and interrupts.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: G
 *  Function:        Go
 * 
 *      Full Command:   G<CR>        
 *      Description:    Enables ADC and RTC features and interrupts. 
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: I
 *  Function:        
 * 
 *      Full Command:   <CR>        
 *      Description:    
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: L
 *  Function:        List parameters
 * 
 *      Full Command:   LP<CR>        
 *      Description:    Queries node's model, group, sensor, collect and wakeup 
 *                      time
 * 
 *      Full Command:   LS<CR>        
 *      Description:    Queries node's status: running or frozen
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: M
 *  Function:        Node model
 * 
 *      Full Command:  M<CR>        
 *      Description:   Queries node model
 * 
 *      Full Command:  M=AAAA<CR>        
 *      Description:   Sets node model
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: R
 *  Function:        Reset        
 * 
 *      Full Command:   R<CR>        
 *      Description:    Reset uP 
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: S
 *  Function:        Sensors      
 * 
 *      Full Command:   S<CR>        
 *      Description:    Queries sensors model
 * 
 *      Full Command:   S=XX<CR>        
 *      Description:    Sets sensors channel
 * 
 *      Full Command:   SX=XX<CR>        
 *      Description:    Sets the sensor's X model to XX
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: T
 *  Function:        Real time clock      
 * 
 *      Full Command:   T<CR>        
 *      Description:    Queries uP real time clock (RTC)
 *  
 *      Full Command:   T=20YY-MM-DD HH:MM:SS<CR>        
 *      Description:    Sets uP real time clock (RTC)
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  First character: W
 *  Function:        Wake Up        
 * 
 *      Full Command:   W<CR>        
 *      Description:    Queries uP wake up parameters
 *  
 *      Full Command:   W=20YY-MM-DD HH:MM:SS<CR>        
 *      Description:    Sets uP wake up parameters  
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @Param   
 *  void
 * @Returns 
 *  void
 * @Error
 *  error[4] | Invalid Command.
 *  error[5] | Invalid Command Format.
 * @See
 *  errorParser#interpretError
 */
void interpretCommand(void);

#endif