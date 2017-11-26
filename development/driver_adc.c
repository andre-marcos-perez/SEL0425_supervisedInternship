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
 *  File name: driver_adc.c
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
 *  Check whether the adc channel was selected by the user.
 * @Param
 *  eepromChannels | Is the byte on eeprom data memory with selected adc channels
 *  channel        | Is the channel to be checked   
 * @Returns
 *  TRUE  | If the channel was selected by the user
 *  FALSE | If the channel was not selected by the user
 */
static bit isChannelSelected(byte eepromChannels, byte channel);

/**
 * @Macro
 *  Macro to disable the adc
 */
#define disableAdc() (ADCON0bits.ADON = 0)

/**
 * @Macro
 *  Macro to enable the adc
 */
#define enableAdc() (ADCON0bits.ADON = 1)

/**
 * @Macro
 *  Macro to disable the adc operational amplifier
 */
#define disableOperationalAmplifier() (PORTBbits.RB4 = 0)

/**
 * @Macro
 *  Macro to enable the adc operational amplifier
 */
#define enableOperationalAmplifier() (PORTBbits.RB4 = 1)

/**
 * @Variable
 */

/**
 * @Link 
 *  driver_adc.h#bootAdc
 */
void bootAdc(void){
    
    ANSEL = 0b00011111;
    ADCON1bits.ADFM  = 0;
    ADCON1bits.ADCS2 = 0;
    ADCON1bits.VCFG1 = 1;
    ADCON1bits.VCFG0 = 0;
    disableOperationalAmplifier();
}

/**
 * @Link 
 *  driver_adc.h#adcRead
 */
byte adcRead(byte channel){
    
    ADCON0bits.ADON = 1;
    enableOperationalAmplifier();
    __delay_ms(4);
    ADCON0bits.CHS = channel;
    while(ADCON0bits.GO);
    return ADRESH;
}

/**
 * @Link 
 *  driver_adc.h#adcReadChannels
 */
void adcReadChannels(void){
    
    byte adcData;
    byte eepromChannels = eepromRead(EEPROM_ADDRESS_COLLECT_CHANNELS);
    
    enableAdc();
    if(isChannelSelected(eepromChannels, 0)){
        
        adcData = adcRead(0);
        //adc buffer write
    }
    
    if(isChannelSelected(eepromChannels, 1)){
        
        adcData = adcRead(1);
        //adc buffer write
    }
    
    if(isChannelSelected(eepromChannels, 2)){
        
        adcData = adcRead(2);
        //adc buffer write
    }
    
    if(isChannelSelected(eepromChannels, 4)){
        
        adcData = adcRead(4);
        //adc buffer write
    }
    
    disableAdc();
}

/**
 * @Link 
 *  driver_adc.c#isChannelSelected
 */
static bit isChannelSelected(byte eepromChannels, byte channel){
        
    if(((0x01 == eepromChannels >> channel) & 0x01)){
        
        return TRUE;
    }
    
    return FALSE;
}