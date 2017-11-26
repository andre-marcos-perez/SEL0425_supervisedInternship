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
 *  File name: manager_interrupt.c
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
#include "driver_rtc.h"
#include "driver_usart.h"
#include "parser_error.h"
#include "parser_command.h"
#include "manager_interrupt.h"
#include "manager_bios.h"
#include "driver_eeprom.h"
#include "manager_memory.h"

/**
 * @Variable
 */
static byte rxData;
static bit rxError;

/**
 * @Link 
 *  manager_interrupt.h#interruptServiceRoutine
 */
void interrupt interruptServiceRoutine(void){
    
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF){
        
        disableRtcInterrupt();
        PIR1bits.TMR1IF = 0;
        rtcReload();
        rtcUpdate();
        if(isNodeAwaken()){
            
            if(!isNodeFrozen() && 
               rtcGetMinute() % eepromRead(EEPROM_ADDRESS_COLLECT_INTERVAL) == 0){
                
                //perform adc
            }
        }
        else{
           
            if(eepromRead(EEPROM_ADDRESS_WAKE_UP_YEAR) == rtcGetYear()    ||
               eepromRead(EEPROM_ADDRESS_WAKE_UP_MOUNTH) == rtcGetMonth() ||
               eepromRead(EEPROM_ADDRESS_WAKE_UP_DAY) == rtcGetDay()){
       
                if(eepromRead(EEPROM_ADDRESS_WAKE_UP_HOUR) == rtcGetHour() ||
                   eepromRead(EEPROM_ADDRESS_WAKE_UP_MINUTE) == rtcGetMinute()){
           
                    awakeNode();
                }
            }
        }
        
        enableRtcInterrupt();
    }
    
    if(PIE1bits.RCIE && PIR1bits.RCIF){
        
        disableRxInterrupt();
        rxData = usartRead();
        rxError = 0;
        if(RCSTAbits.OERR){
        
            rxError = 1;
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
            usartFlushRxBuffer();
            usartWriteNewLine();
            interpretError(1);
            usartWriteNewLine();
            usartWriteNewLine();
        }
        
        if(RCSTAbits.FERR){
                
            rxError = 1;
            usartFlushRxBuffer();
            usartWriteNewLine();
            interpretError(2);
            usartWriteNewLine();
            usartWriteNewLine();
        }
        
        if(!rxError){
            
            usartWrite(rxData);
            if('+' != rxData){
                
                usartReceive(rxData);
            }
            if('\r' == rxData){
                
                interpretCommand();
            }
        }

        enableRxInterrupt();
    }
}
