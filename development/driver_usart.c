/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis® ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Universal synchronous/asynchronous receiver/transmitter driver.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: driver_driver_usart.c
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
#include "driver_usart.h"
#include "parser_error.h"

/**
 * @Macro
 *  Defines the reception circular buffer capacity
 */
#define USART_RX_BUFFER_CAPACITY 28

/**
 * @Variable
 *  Reception circular buffer variables
 */
static byte rxFront = 0;
static byte rxRear  = 0;
static byte rxSize  = 0;
static byte rxBuffer[USART_RX_BUFFER_CAPACITY];
static const byte RX_CAPACITY = USART_RX_BUFFER_CAPACITY;

/**
 * @Link 
 *  driver_usart.h#usartInitialize
 */
void bootUsart(void){
    
    disableRxInterrupt();
    SPBRG = 12;
    TXSTAbits.TX9  = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9  = 0;
    RCSTAbits.CREN = 1;
    enableRxInterrupt();
}

/**
 * @Link 
 *  driver_usart.h#usartRead
 */
byte usartRead(void){
    
    return RCREG;
}

/**
 * @Link 
 *  driver_usart.h#usartReadRxBuffer
 */
byte usartReadRxBuffer(void){
    
    disableRxInterrupt();
    byte rxData = 0x00;
    if(0 != rxSize){
                
        rxData = *(rxBuffer + rxFront);
        *(rxBuffer + rxFront) = 0;
        rxFront = (rxFront + 1) % RX_CAPACITY;
        rxSize = (RX_CAPACITY + rxRear - rxFront) % RX_CAPACITY;
    }

    enableRxInterrupt();
    return rxData;
}

/**
 * @Link 
 *  driver_usart.h#usartReadRxBufferNumber
 */
byte usartReadRxBufferNumber(void){
    
    return 10*(usartReadRxBuffer() - 0x30) + (usartReadRxBuffer() - 0x30);
}

/**
 * @Link 
 *  driver_usart.h#usartReadRxBufferTimestamp
 */
byte *usartReadRxBufferTimestamp(void){
    
    static byte timestamp[13];
    
    *(timestamp + 0)  = '2';
    *(timestamp + 1)  = '0';
    *(timestamp + 2)  = usartReadRxBufferNumber();
    *(timestamp + 3)  = usartReadRxBuffer();
    *(timestamp + 4)  = usartReadRxBufferNumber();
    *(timestamp + 5)  = usartReadRxBuffer();
    *(timestamp + 6)  = usartReadRxBufferNumber();
    *(timestamp + 7)  = usartReadRxBuffer();
    *(timestamp + 8)  = usartReadRxBufferNumber();
    *(timestamp + 9)  = usartReadRxBuffer();
    *(timestamp + 10) = usartReadRxBufferNumber();
    *(timestamp + 11) = usartReadRxBuffer();
    *(timestamp + 12) = usartReadRxBufferNumber();
    
    return timestamp;
}

/**
 * @Link 
 *  driver_usart.h#usartWrite
 */
void usartWrite(byte txData){
    
    while(!TXSTAbits.TRMT);
    TXREG = txData;
}

/**
 * @Link 
 *  driver_usart.h#usartWriteNumber
 */
void usartWriteNumber(byte txData){
    
    byte number;
    number = txData / 10;
    usartWrite(number + 0x30);
    number = txData - number*10;
    usartWrite(number + 0x30);
}

/**
 * @Link 
 *  driver_usart.h#usartWriteString
 */
void usartWriteString(const byte *txDataString){
    
    while(*txDataString != '\0'){
        
        usartWrite(*txDataString);
        txDataString++;
    }
}

/**
 * @Link 
 *  driver_usart.h#usartWriteNewLine
 */
void usartWriteNewLine(void){
    
    usartWrite(0x0D);
    usartWrite(0x0A);
}

/**
 * @Link 
 *  driver_usart.h#usartReceive
 */
void usartReceive(byte rxData){
    
    if(RX_CAPACITY == rxSize){
        
        rxSize = 0;
        usartFlushRxBuffer();
        usartWriteNewLine();
        interpretError(3);
        usartWriteNewLine();
        usartWriteNewLine();
    }
    else{
        
        *(rxBuffer + rxRear) = rxData;
        rxRear = (rxRear + 1) % RX_CAPACITY;
        rxSize = (RX_CAPACITY + rxRear - rxFront) % RX_CAPACITY;
        if(0 == rxSize){
           
            rxSize = RX_CAPACITY;
        }
    } 
}

/**
 * @Link 
 *  driver_usart.h#usartPeekRxBufferHead
 */
byte usartPeekRxBufferHead(void){
    
    return *(rxBuffer + rxFront);
}

/**
 * @Link 
 *  driver_usart.h#usartFlushRxBuffer
 */
void usartFlushRxBuffer(void){
    
    while(rxFront != rxRear){
        
        usartReadRxBuffer();
    }
}