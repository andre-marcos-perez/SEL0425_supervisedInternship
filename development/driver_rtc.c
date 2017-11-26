/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Real time clock driver. Implemented by software on timer 1.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: driver_rtc.c
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
#include "driver_eeprom.h"
#include "manager_memory.h"

/**
 * @Description
 *  Performs a delay of 1024 clock cycles to stabilize the real time clock
 *  external oscillator, similar to the OST (Oscillator Start Up Timer) feature.
 * @Precondition
 *  Must be called inside the driver_rtc#rtcInitialize function.
 * @Param
 *  void  
 * @Returns
 *  void 
 * @See
 *  driver_rtc#rtcInitialize 
 */
static void rtcStarUpDelay(void);

/**
 * @Macro
 *  Macro to stop the real time clock counter
 */
#define stopRtcCounter() (T1CONbits.TMR1ON = 0)

/**
 * @Macro
 *  Macro to start the real time clock counter
 */
#define startRtcCounter() (T1CONbits.TMR1ON = 1)

/**
 * @Variable
 */
static persistent byte rtcHour;
static persistent byte rtcMinute;
static persistent byte rtcSecond;
static persistent byte rtcMonth;
static persistent byte rtcDay;
static persistent byte rtcYear;

/**
 * @Link 
 *  driver_rtc.h#rtcInitialize
 */
void bootRtc(void){
    
    disableRtcInterrupt();
    T1CONbits.T1INSYNC = 1;
    T1CONbits.T1OSCEN = 1;
    T1CONbits.TMR1CS = 1;
    rtcStarUpDelay();
    TMR1L = 0x00;
    TMR1H = 0x80;
    PIR1bits.TMR1IF = 0;
    startRtcCounter();
    enableRtcInterrupt();
}

/**
 * @Link 
 *  driver_rtc.h#rtcReload
 */
void rtcReload(void){
    
    stopRtcCounter();
    TMR1H |= 0x80;
    startRtcCounter();
}

/**
 * @Link 
 *  driver_rtc.h#rtcSetClock
 */   
void rtcSetClock(byte year, byte month, byte day,
                 byte hour, byte minute, byte second){
    
    rtcYear   = year;
    rtcMonth  = month;
    rtcDay    = day;
    rtcHour   = hour;
    rtcMinute = minute;
    rtcSecond = second;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetSecond
 */
byte rtcGetSecond(void){
    
    return rtcSecond;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetMinute
 */
byte rtcGetMinute(void){
    
    return rtcMinute;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetHour
 */
byte rtcGetHour(void){
    
    return rtcHour;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetDay
 */
byte rtcGetDay(void){
    
    return rtcDay;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetMonth
 */
byte rtcGetMonth(void){
    
    return rtcMonth;
}

/**
 * @Link 
 *  driver_rtc.h#rtcGetYear
 */
byte rtcGetYear(void){
    
    return rtcYear;
}

/**
 * @Link 
 *  driver_rtc.h#rtcUpdate
 */
void rtcUpdate(void){

 if(60 == ++rtcSecond){
        
        rtcSecond = 0;
        if(60 == ++rtcMinute){
            
            rtcMinute = 0;
            if(24 == ++rtcHour){
                
                rtcHour = 0;
                unsigned char endDay = 31;
                switch(rtcMonth){
                    
                    case 2:{
                        
                        (rtcYear % 4) == 0 ? endDay = 29 : endDay = 30;
                        break;
                    }
                    case 4:
                    case 6:
                    case 9:
                    case 11:{
                        
                        endDay = 30;
                        break;
                    }
                }
                
                if(endDay + 1 == ++rtcDay){
                    
                    rtcDay = 0;
                    if(13 == ++rtcMonth){
                        
                        rtcMonth = 0;
                        if(100 == ++rtcYear){
                            
                            rtcYear = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @Link 
 *  driver_rtc.c#rtcStarUpDelay
 */
static void rtcStarUpDelay(void){
    
    TMR1L = 0x00;
    TMR1H = 0xFC;
    PIR1bits.TMR1IF = 0;
    startRtcCounter();
    while(PIR1bits.TMR1IF);
    stopRtcCounter();
}