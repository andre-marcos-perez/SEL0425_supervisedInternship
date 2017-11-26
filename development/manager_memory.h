/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  EEPROM memory mapping and ADC data buffers manager.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: manager_memory.h
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
#ifndef MANAGER_MEMORY_H
#define	MANAGER_MEMORY_H

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
 */

#define EEPROM_ADDRESS_ID_GROUP         0x00
#define EEPROM_ADDRESS_NODE_MODEL       0x01

#define EEPROM_ADDRESS_NODE_OPERATION   0x05

#define EEPROM_ADDRESS_SENSOR_MODEL_0   0x06
#define EEPROM_ADDRESS_SENSOR_MODEL_1   0x07
#define EEPROM_ADDRESS_SENSOR_MODEL_2   0x08
#define EEPROM_ADDRESS_SENSOR_MODEL_4   0x09

#define EEPROM_ADDRESS_WAKE_UP_YEAR     0x0B
#define EEPROM_ADDRESS_WAKE_UP_MOUNTH   0x0C
#define EEPROM_ADDRESS_WAKE_UP_DAY      0x0D
#define EEPROM_ADDRESS_WAKE_UP_HOUR     0x0E
#define EEPROM_ADDRESS_WAKE_UP_MINUTE   0x0F
#define EEPROM_ADDRESS_WAKE_UP_SECOND   0x10

#define EEPROM_ADDRESS_COLLECT_YEAR     0x13
#define EEPROM_ADDRESS_COLLECT_MOUNTH   0x14
#define EEPROM_ADDRESS_COLLECT_DAY      0x15
#define EEPROM_ADDRESS_COLLECT_HOUR     0x16
#define EEPROM_ADDRESS_COLLECT_MINUTE   0x17
#define EEPROM_ADDRESS_COLLECT_SECOND   0x18
#define EEPROM_ADDRESS_COLLECT_INTERVAL 0x19

#define EEPROM_ADDRESS_COLLECT_CHANNELS 0x1A

#define EEPROM_ADDRESS_BUFFER_CHANNEL_0
#define EEPROM_ADDRESS_BUFFER_FRONT_0
#define EEPROM_ADDRESS_BUFFER_REAR_0
#define EEPROM_ADDRESS_BUFFER_SIZE_0
#define EEPROM_ADDRESS_BUFFER_CAPACITY_0
#define EEPROM_ADDRESS_BUFFER_NUMBER_0

#define EEPROM_ADDRESS_BUFFER_CHANNEL_1
#define EEPROM_ADDRESS_BUFFER_FRONT_1
#define EEPROM_ADDRESS_BUFFER_REAR_1
#define EEPROM_ADDRESS_BUFFER_SIZE_1
#define EEPROM_ADDRESS_BUFFER_CAPACITY_1
#define EEPROM_ADDRESS_BUFFER_NUMBER_1

#define EEPROM_ADDRESS_BUFFER_CHANNEL_2
#define EEPROM_ADDRESS_BUFFER_FRONT_2
#define EEPROM_ADDRESS_BUFFER_REAR_2
#define EEPROM_ADDRESS_BUFFER_SIZE_2
#define EEPROM_ADDRESS_BUFFER_CAPACITY_2
#define EEPROM_ADDRESS_BUFFER_NUMBER_2

#define EEPROM_ADDRESS_BUFFER_CHANNEL_4
#define EEPROM_ADDRESS_BUFFER_FRONT_4
#define EEPROM_ADDRESS_BUFFER_REAR_4
#define EEPROM_ADDRESS_BUFFER_SIZE_4
#define EEPROM_ADDRESS_BUFFER_CAPACITY_4
#define EEPROM_ADDRESS_BUFFER_NUMBER_4

#endif