/*
 * File:   newmain.c
 * Author: Ronald Ch'ng Yong Hern
 *
 * Created on December 18, 2021, 3:35 AM
 */



// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "bluetooth.h"
#include "pins.h"
#define _XTAL_FREQ 20000000     // System clock frequency is External Oscillator Frequency

uint8_t data = 'T';
uint8_t ferr;
void __interrupt() isr() {
    //GIE = 0;
    //PEIE = 0;
    //RCIE = 0;
    
    ferr = FERR;    // Recommended by datasheet to read FERR before reading RCREG
    if(OERR) {      // 
        CREN = 0;
        CREN = 1;
    } 
    data = RCREG;
    UART_WRITE(data);
    //GIE = 1;
    //PEIE = 1;
    //RCIE = 1;
    
    if (data == 'A') {
        RD0 = !RD0;
    }
    
}
void main() {
    OSCCONbits.SCS = 0;         //  System clock set by FOSC<2,0> CONFIG1
    OSCCONbits.OSTS = 1;        //  Oscillator start up time set by FOSC<2,0> CONFIG1
    
    registers();                // Initiate pinouts
    LED_set_off();
    USART_Init();               // Bluetooth serial uart
    __delay_ms(1000);
    RD3=1;
    //unsigned char data = 'A';
    while(1) {
        
        /*
        while(!PIR1bits.RCIF) {
            
            __delay_ms(1000);
        }
        
        unsigned char ferr = FERR;      // Probably broken, find another way to read FERR
        if (RCSTAbits.OERR) {
            CREN = 0;
            CREN = 1;
        }
       
        data = RCREG;
        UART_WRITE(data);
       RCIF = 0; 
         */
    }
}