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
 *  File name: manager_bios.c
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
#include "driver_adc.h"
#include "driver_rtc.h"
#include "driver_usart.h"
#include "manager_bios.h"

/*
 * @CodeConvention
 */
#ifndef BOOLEAN
#define TRUE  1
#define FALSE 0
#endif

/**
 * @Variable
 *  Flag to indicate whether to soft reset the uP or not
 */
static bit resetFlag;

/**
 * @Variable
 *  Flag to indicate whether the uP is frozen or not
 */
static bit freezeFlag;

/**
 * @Variable
 *  Flag to indicate whether the uP is awaken to collect data from adc or not
 */
static bit awakenFlag;

/**
 * @Description
 *  Configure microcontroller initial pins state
 * @Param
 *  void  
 * @Returns
 *  void
 */
static void bootPin(void);

/**
 * @Description
 *  Configure microcontroller initial flag state
 * @Param
 *  void  
 * @Returns
 *  void
 */
static void bootFlag(void);

/**
 * @Link 
 *  manager_bios.h#bootBios
 */
void bootBios(void){
    
    bootAdc();
    bootRtc();
    bootUsart();
    bootPin();
    bootFlag();
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

/**
 * @Link 
 *  manager_bios.h#resumeNode
 */
void resumeNode(void){
    
    freezeFlag = 0;
    PIE1bits.ADIE = 1;
    PIE1bits.TMR1IE = 1;
    T1CONbits.TMR1ON = 1;
}

/**
 * @Link 
 *  manager_bios.h#freezeNode
 */
void freezeNode(void){
    
    freezeFlag = 1;
    PIE1bits.ADIE = 0;
    PIE1bits.TMR1IE = 0;
    T1CONbits.TMR1ON = 0;
}

/**
 * @Link 
 *  manager_bios.h#isNodeFrozen
 */
bit isNodeFrozen(void){
    
    return freezeFlag;
}

/**
 * @Link 
 *  manager_bios.h#awakeNode
 */
void awakeNode(void){
    
    awakenFlag = TRUE;
}

/**
 * @Link 
 *  manager_bios.h#isNodeAwaken
 */
bit isNodeAwaken(void){
    
    return awakenFlag;
}

/**
 * @Link 
 *  manager_bios.h#resetNode
 */
void resetNode(void){
    
    resetFlag = TRUE;
}

/**
 * @Link 
 *  manager_bios.h#hasToResetNode
 */
bit hasToResetNode(void){
    
    return resetFlag;
}

/**
 * @Link 
 *  manager_bios.c#bootPin
 */
static void bootPin(void){
    
    PIR1  = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    TRISA = 0b00111111;
    TRISB = 0b11111111;
    OPTION_REG = 0b00000111;
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 1;
}

/**
 * @Link 
 *  manager_bios.c#bootFlag
 */
static void bootFlag(void){
    
    resetFlag = 0;
    freezeFlag = 0;
    awakenFlag = 0;
}