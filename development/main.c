/*******************************************************************************
 * @2017 Brazilian Agricultural Research Corporation | Embrapa Instrumentation
 *------------------------------------------------------------------------------
 * @PROJECT 
 * Adaptation of TDI for the Telegesis� ETRX357 ZigBee Radio Module
 *------------------------------------------------------------------------------
 * @DESCRIPTION
 *  Software entry point and endless main function.
 *------------------------------------------------------------------------------
 * @FILE
 *  File name: main.c
 *  File type: Source (.c)
 *------------------------------------------------------------------------------
 * @DEVELOPMENT
 *  MCU:       Microchip� PIC16LF88
 *  IDE:       MPLAB� X v3.50  
 *  Compiler:  MPLAB� XC8 v1.40
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
#include "manager_bios.h"

/**
 * @Description
 *  Software entry point and endless main function.   
 * @Param
 *  void    
 * @Returns
 *  void  
 */
void main(void){

    while(1){
        
        bootBios();
        while(!hasToResetNode()){
        
            SLEEP();
        }
    }
}