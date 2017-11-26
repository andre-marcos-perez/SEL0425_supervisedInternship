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
 *  File name: parser_command.c
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
#include "manager_bios.h"
#include "driver_eeprom.h"
#include "manager_memory.h"

/*
 * @CodeConvention
 */
#ifndef BOOLEAN
#define TRUE  1
#define FALSE 0
#endif

/**
 * @Description
 *  Prints the node's model.
 * @Param
 *  void
 * @Returns
 *  void
 * @See  
 */ 
static void printNodeModel(void);

/**
 * @Description
 *  Prints the node's group.
 * @Param
 *  void
 * @Returns
 *  void
 * @See  
 */
static void printNodeGroup(void);

/**
 * @Description
 *  Prints the node's sensor model.
 * @Param
 *  void
 * @Returns
 *  void
 * @See  
 */
static void printNodeSensor(void);

/**
 * @Description
 *  Prints the node's collect time parameters.
 * @Param
 *  void
 * @Returns
 *  void
 * @See  
 */
static void printNodeCollectTime(void);

/**
 * @Description
 *  Prints the node's wake up time parameters.
 * @Param
 *  void
 * @Returns
 *  void
 * @See  
 */
static void printNodeWakeUpTime(void);

/**
 * @Description
 *  Gets the timestamp format characters from a timestamp array.
 * @Param
 *  timestamp  | is the timestamp array
 * @Returns
 *  formatChars | the array containing the timestamp format characters
 * @See
 *  driver_usart.h#usartRxBufferTimestamp
 *  parser_command.h#interpretCommand  
 */
static byte *getTimestampFormatChar(byte *timestamp);

/**
 * @Description
 *  Checks whether the characters received matches the characters expected of a
 *  given format.
 * @Param
 *  charQuantity  | the quantity of characters
 *  formatChars   | the received characters
 *  expectedChars | the expected characters
 * @Returns
 *  1 | if all the characters received matches the expected
 *  0 | if at least one of the characters received does not match the expected
 * @Error
 *  error[5] | Invalid Command Format.  
 */
static bit isFormatCorrect(byte charQuantity, byte *formatChars, byte *expectedChars);

/**
 * @Link 
 *  parser_command.h#interpretCommand
 */
void interpretCommand(void){
    
    usartWriteNewLine();
    switch(usartReadRxBuffer()){
        
        case 'B':{
            
            switch(usartReadRxBuffer()){
                
                case '\r':{
                    
                    printNodeGroup();
                    break;
                }
                case '=':{
                    
                    eepromWrite(EEPROM_ADDRESS_ID_GROUP, usartReadRxBufferNumber());
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
           
            break;
        }
        case 'C':{
            
            switch(usartReadRxBuffer()){
                
                case '\r':{
                    
                    printNodeCollectTime();
                    break;
                }
                case '=':{

                    byte *timestamp;
                    byte *formatChar;
                    byte expectedChars[] = {'2','0','-','-',' ',':',':',' '};
                    
                    timestamp = usartReadRxBufferTimestamp();
                    formatChar = getTimestampFormatChar(timestamp);                   
                    *(formatChar + 7) = usartReadRxBuffer();
                    *(timestamp + 13) = usartReadRxBufferNumber();
                    if(isFormatCorrect(8,formatChar,expectedChars)){
                        
                        for(char i=0 ; i<7; i++){
                            
                            eepromWrite(EEPROM_ADDRESS_COLLECT_YEAR + i, *(timestamp + i));
                        }

                        usartWriteString("C: Set up ok");
                    }
                    
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
            
            break;
        }
        case 'D':{
            
        break;
        }
        case 'F':{
            
            if('\r' == usartReadRxBuffer()){
                
                freezeNode();
                usartWriteString("Frozen");
            }
            else{
                
                interpretError(4);
            }
            
            break;
        }
        case 'G':{
            
            if('\r' == usartReadRxBuffer()){
                
                resumeNode();
                usartWriteString("Running");
            }
            else{
                
                interpretError(4);
            }
            
            break;
        }
        case 'I':{
          
        break;
        }  
        case 'L':{
            
            switch(usartReadRxBuffer()){
                
                case 'P':{
                    
                    usartWriteString("LP:");
                    usartWriteNewLine();
                    printNodeModel();
                    usartWriteNewLine();
                    printNodeGroup();
                    usartWriteNewLine();
                    printNodeSensor();
                    usartWriteNewLine();
                    printNodeCollectTime();
                    usartWriteNewLine();
                    printNodeWakeUpTime();
                    break;
                }
                case 'S':{
                    
                    usartWriteString("LS: ");
                    if(isNodeFrozen()){
                        
                        usartWriteString("Frozen");
                    }
                    else{
                        
                        usartWriteString("Running");
                    }
                    
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
           
            break;
        }  
        case 'M':{
            
            switch(usartReadRxBuffer()){
                
                case '\r':{
                    
                    printNodeModel();                  
                    break;
                }
                case '=':{
                    
                    for(char i=0 ; i<4; i++){
                        
                        eepromWrite(EEPROM_ADDRESS_NODE_MODEL + i, usartReadRxBuffer());
                    }

                    usartWriteString("M: Set up ok");
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
            
            break;
        } 
        case 'R':{
            
            if('\r' == usartReadRxBuffer()){
                
                resetNode();
                usartWriteString("Reset");
            }
            else{
                
                interpretError(4);
            }
            
            break;
        }
        case 'S':{
            
            switch(usartPeekRxBufferHead()){
                
                case '\r':{
                    
                    printNodeSensor();
                    break;
                }
                case '=':{
                    
                    eepromWrite(EEPROM_ADDRESS_COLLECT_CHANNELS, usartReadRxBufferNumber());
                    break;
                }
                case '0':
                case '1':
                case '2':
                case '4':{
                    
                    byte sensorNumber;
                    
                    sensorNumber = usartReadRxBuffer();
                    if('=' == usartReadRxBuffer()){
                        
                        eepromWrite(EEPROM_ADDRESS_SENSOR_MODEL_0 + (sensorNumber - 0x30), 
                                 usartReadRxBufferNumber());
                    }
                    else{
                        
                        interpretError(4);
                    }
                    break;
                }  
                default:{
                    
                    interpretError(4);
                }
            }
            
            break;
        }
        case 'T':{
            
            switch(usartReadRxBuffer()){
                
                case '\r':{
                    
                    usartWriteString("T: 20");
                    usartWriteNumber(rtcGetYear());
                    usartWrite('-');
                    usartWriteNumber(rtcGetMonth());
                    usartWrite('-');
                    usartWriteNumber(rtcGetDay());
                    usartWrite(' ');
                    usartWriteNumber(rtcGetHour());
                    usartWrite(':');
                    usartWriteNumber(rtcGetMinute());
                    usartWrite(':');
                    usartWriteNumber(rtcGetSecond());
                    break;
                }
                case '=':{
                    
                    byte *timestamp;
                    byte *formatChar;
                    byte expectedChars[] = {'2','0','-','-',' ',':',':'};
                    
                    timestamp = usartReadRxBufferTimestamp();
                    formatChar = getTimestampFormatChar(timestamp);
                    if(isFormatCorrect(7,formatChar,expectedChars)){
                        
                        rtcSetClock(*(timestamp + 2), *(timestamp + 4), 
                                    *(timestamp + 6), *(timestamp + 8), 
                                    *(timestamp + 10), *(timestamp + 12));
                        usartWriteString("T: Set up ok");
                    }
                    else{
                        
                        interpretError(5);
                    }
                   
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
           
            break;
        } 
        case 'W':{
            
            switch(usartReadRxBuffer()){
                
                case '\r':{
                    
                    printNodeWakeUpTime();
                    break;
                }
                case '=':{

                    byte *timestamp;
                    byte *formatChar;
                    byte expectedChars[] = {'2','0','-','-',' ',':',':'};
                    
                    timestamp = usartReadRxBufferTimestamp();
                    formatChar = getTimestampFormatChar(timestamp);                   
                    if(isFormatCorrect(7,formatChar,expectedChars)){
                        
                        for(char i=0 ; i<7; i++){
                            
                            eepromWrite(EEPROM_ADDRESS_WAKE_UP_YEAR + i, *(timestamp + i));
                        }

                        usartWriteString("W: Set up ok");
                    }
                    
                    break;
                }
                default:{
                    
                    interpretError(4);
                }
            }
            
            break;
        }
        default:{
            
            interpretError(4);
        }
    }
    
    usartWriteNewLine();
    usartWriteNewLine();
    usartFlushRxBuffer();
}

/*
 * @Link 
 *  parser_command.c#printNodeModel
 */
static void printNodeModel(void){
    
    usartWriteString("M: ");
    for(char i=0 ; i<4; i++){
                                                
        usartWrite(eepromRead(EEPROM_ADDRESS_NODE_MODEL + i));
    }
}

/*
 * @Link 
 *  parser_command.c#printNodeGroup
 */
static void printNodeGroup(void){
    
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_ID_GROUP));
}

/*
 * @Link 
 *  parser_command.c#printNodeSensor
 */
static void printNodeSensor(void){
    
    usartWriteString("C: ");
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_CHANNELS));
    usartWriteNewLine();
    for(char i=0 ; i<4; i++){
        
        if(i==3){
            
            i++;
        }
        
        usartWriteString("S");
        usartWriteNumber(i);
        usartWriteString(" = ");
        usartWrite(eepromRead(EEPROM_ADDRESS_SENSOR_MODEL_0 + i));
        usartWriteNewLine();
    }
}

/*
 * @Link 
 *  parser_command.c#printNodeCollectTime
 */
static void printNodeCollectTime(void){
    
    usartWriteString("C: 20");
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_YEAR));
    usartWrite('-');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_MOUNTH));
    usartWrite('-');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_DAY));
    usartWrite(' ');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_HOUR));
    usartWrite(':');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_MINUTE));
    usartWrite(':');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_SECOND));
    usartWrite(' ');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_COLLECT_INTERVAL));
}

/*
 * @Link 
 *  parser_command.c#printNodeWakeUpTime
 */
static void printNodeWakeUpTime(void){
    
    usartWriteString("W: 20");
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_YEAR));
    usartWrite('-');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_MOUNTH));
    usartWrite('-');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_DAY));
    usartWrite(' ');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_HOUR));
    usartWrite(':');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_MINUTE));
    usartWrite(':');
    usartWriteNumber(eepromRead(EEPROM_ADDRESS_WAKE_UP_SECOND));
}

/*
 * @Link 
 *  parser_command.c#getTimestampFormatChar
 */
static byte *getTimestampFormatChar(byte *timestamp){
    
    static byte formatChars[7];
    
    *(formatChars + 0) = *(timestamp +  0);
    *(formatChars + 1) = *(timestamp +  1);
    *(formatChars + 2) = *(timestamp +  3);
    *(formatChars + 3) = *(timestamp +  5);
    *(formatChars + 4) = *(timestamp +  7);
    *(formatChars + 5) = *(timestamp +  9);
    *(formatChars + 6) = *(timestamp + 11);
    
    return formatChars;
}

/*
 * @Link 
 *  parser_command.c#isFormatCorrect
 */
static bit isFormatCorrect(byte charQuantity, byte *formatChars, byte *expectedChars){
    
    for(byte i=0 ; i<charQuantity ; i++){
        
        if(*(formatChars + i) != *(expectedChars + i)){
            
            return FALSE;
        }
    }
    
    return TRUE;
}