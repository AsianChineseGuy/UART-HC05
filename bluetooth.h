/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: Ronald Ch'ng Yong Hern
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#define _XTAL_FREQ 20000000
void USART_Init() {
    TXSTAbits.SYNC = 0;       // Asynchronous
    RCSTAbits.SPEN = 1;       // Serial Port Enabled
    TXSTAbits.TXEN = 1;       // Transmitter Enabled
    RCSTAbits.CREN = 1;       // Continuous Receiver   
    
    TXSTAbits.BRGH = 1;       // High baud rate
    BAUDCTLbits.BRG16 = 0;
    
    /*
        -----   HC-05 bluetooth module default baud rate is 9600           -----
        -----   Check PIC16f887 datasheet for correct SPBRG decimal value  -----
        -----   under 12.0 EUSART                                          -----
     */
    SPBRGH = 0;
    SPBRG = 129;      // 20MHz FOSC with baud rate bit = HIGH  
    
    /*
        -----  Turning on RCIE,PEIE,GIE from PIE1, INTCON bits             -----
        -----  Enables RCIF interrupt flag                                 -----
    */
    PIE1bits.RCIE = 1;      // Receiver Interrupt
    INTCONbits.PEIE = 1;    // Peripheral Interrupt 
    INTCONbits.GIE = 1;     // Global Interrupt
}

void UART_WRITE(uint8_t *send) {
    TXREG = *send;
    while(!TXSTAbits.TRMT);  // WAIT FOR TXREG to become empty
}

void UART_GET(uint8_t *value) {
    *value = RCREG;
}