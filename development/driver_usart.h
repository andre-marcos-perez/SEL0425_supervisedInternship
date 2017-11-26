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
 *  File name: driver_usart.h
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
#ifndef DRIVER_USART_H
#define	DRIVER_USART_H

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
 *  Macro to disable usart reception interrupt.
 */
#define disableRxInterrupt() (PIE1bits.RCIE = 0)

/**
 * @Macro
 *  Macro to enable usart reception interrupt.
 */
#define enableRxInterrupt() (PIE1bits.RCIE = 1)

/**
 * @Description  
 *  Handles USART configuration: 19200 | 8 | N | 1, enabling it's interrupt.
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Mode:      Asynchronous | TXSTA.SYNC = 0
 *  Baud Rate: 19200 bauds  | TXSTA.BRGH = 1 | SPBRG = 12
 *  Tx Data:   1 byte       | TXSTA.TX9  = 0
 *  Rx Data:   1 byte       | RCSTA.RX9  = 0
 *  Parity:    None
 *  Stop Bits: 1
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * @Param   
 *  void
 * @Returns 
 *  void
 */
void bootUsart(void);

/**
 * @Description
 *  Reads the data received through usart
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  rxData | The data stored in the RCREG register
 */
byte usartRead(void);

/**
 * @Description
 *  Reads and remove the data stored in the front of the reception circular 
 *  buffer
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  rxData | The data in the head of the reception buffer
 * @See
 *  driver_usart.h#usartReceive
 *  wikipedia.org/wiki/Circular_buffer
 */
byte usartReadRxBuffer(void);

/**
 * @Description
 *  Based on the Horner's rule for polynomials, reads and removes a two digit 
 *  number stored in the head of the reception circular buffer, converting them 
 *  from the ASCII code to it's decimal notation.
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  rxData | The two digit number in the head of the reception circular buffer
 * @See
 *  driver_usart.h#usartReadRxBuffer
 *  wikipedia.org/wiki/Horner's_method
 */
byte usartReadRxBufferNumber(void);

/**
 * @Description
 *  Reads and removes a timestamp (20YY-MM-DD HH:MM:SS) in the reception circular 
 *  buffer, converting all the two digits numbers from their ASCII code to their
 *  decimal notation.
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  timestamp | Is the timestamp stored in the reception circular buffer
 * @See
 *  driver_usart.h#usartReadRxBufferNumber
 */
byte *usartReadRxBufferTimestamp(void);

/**
 * @Description
 *  Sends one byte of data through USART
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  txData | The data to be transmitted
 * @Returns 
 *  void
 */
void usartWrite(byte txData);

/**
 * @Description
 *  Based on the Horner's rule for polynomials, converts and sends a two digit 
 *  number stored in a char data type into its equivalent ASCII characters. 
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  txData | The number to be transmitted
 * @Returns 
 *  void
 * @See
 *  driver_usart.h#usartWrite
 *  wikipedia.org/wiki/Horner's_method
 */
void usartWriteNumber(byte txData);

/**
 * @Description
 *  Sends bytes of data through USART
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  txData | The data to be transmitted
 * @Returns 
 *  void
 * @See
 *  driver_usart.h#usartWrite
 */
void usartWriteString(const byte *txDataString);

/**
 * @Description
 *  Starts a new line by writing the carriage return and line feed characters.
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param
 *  void  
 * @Returns
 *  void
 * @See
 *  driver_usart.h#usartWrite 
 */
void usartWriteNewLine(void);

/**
 * @Description
 *  Stores the data received through usart interruption service in the reception
 *  circular buffer
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  rxData | The data received
 * @Returns 
 *  void
 * @Error
 *  error[3] | Reception Buffer Overflow.
 * @See     
 *  manager_interrupt#interruptServiceRoutine
 *  parser_error#interpretError
 *  wikipedia.org/wiki/Circular_buffer
 */
void usartReceive(byte rxData);

/**
 * @Description
 *  Returns the reception buffer's first data entry.
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  rxBuffer(first) | The reception buffer's first data entry.
 * @See     
 *  manager_interrupt#interruptServiceRoutine
 */
byte usartPeekRxBufferHead(void);

/**
 * @Description
 *  Flushes the reception buffer, pointing rear and front on the same memory
 *  address.
 * @Precondition
 *  usart#usartInitialize must have been called previously
 * @Param   
 *  void
 * @Returns 
 *  void
 * @See
 *  driver_usart.h#usartReadRxBuffer
 */
void usartFlushRxBuffer(void);

#endif