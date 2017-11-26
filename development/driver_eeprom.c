/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  EEPROM driver.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: driver_nvm.c
 *  File type: Source (.c)  
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
 * @Include
 *  Dependency library
 */
#include "driver_eeprom.h"

/**
 * @Macro
 *  Macro to indicate which non-volatile memory was selected
 */
#define EEPROM 0

/**
 * @Link 
 *  driver_eeprom.h#nvmRead
 */
byte eepromRead(byte address){
    
    static byte memoryRead;
    
    EEADR  = address;
    EECON1bits.EEPGD = EEPROM;
    EECON1bits.RD = 1;
    asm("NOP");
    asm("NOP");    
    memoryRead = EEDATA;
    
    return memoryRead;
}

/**
 * @Link 
 *  driver_eeprom.h#eepromWrite
 */
void eepromWrite(byte address, byte data){
    
    GIE = 0;
    while(EECON1bits.WR);
    EECON1bits.EEPGD = EEPROM;
    EEADR  = address;
    EEDATA = data;
    EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    EECON1bits.WREN = 0;
    GIE = 1;
}