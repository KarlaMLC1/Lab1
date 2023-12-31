/*
 * File:   main.c
 * Author: karla
 *
 * Created on 23 de marzo de 2023, 05:50 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "Libreria.h"
#define _tmr0_value 200
#define _XTAL_FREQ 8000000 //Lo utiliza internamente para calcular como sacar el delay
int VALOR;
int counter;

void __interrupt() isr(void){
    if (T0IF){
        TMR0 = _tmr0_value;
        T0IF = 0;
        
    }
 
    if (INTCONbits.RBIF)
    {
        if (RB0 == 1)  // Si se presiona el botón de incremento
        {
            counter++;
            PORTC =counter;
            //__delay_ms(1);
                 
        }
        if (RB1 == 1)  // Si se presiona el botón de decremento
        {
            counter--;
            PORTC =counter;
            //__delay_ms(1);
        }
        INTCONbits.RBIF = 0;  // Limpia la bandera de interrupción externa
        
        
    }
    
}
void setup(void);

void main(void) {

    setup();
    while(1){
        
     
        adc_init(1);
        adc_read (1);
        

        
        while (ADCON0bits.GO_DONE); // Esperar hasta que la conversión ADC termine

        int adc0 = adc_readValor ();
        int voltage = adc0; // Convertir el resultado de la conversión ADC en voltaje

        
        int digit1 = voltage ;
        int digit2 = adc0 / 10;
        
        
        ConfigDisplay1(digit1);
             __delay_ms(1);
        ConfigDisplay2(digit2);
             __delay_ms(1);
         //Tabla Primer display
        
        if (digit1>counter){
            counter=0b11111111;
        }
       
    }
    return;
}

void setup(void){
    ANSEL = 0;
    TRISC = 0x00; // Configurar todo el Puerto C como salida
    PORTC = 0x00; // Inicializar el Puerto C en 0
    TRISD = 0x00;
    TRISE = 0x00; 
    
    ANSELH = 0;
   // TRISB = 0XFF;
    confi_Botones (8);
            
    IOCB = 0xFF;
    INTCONbits.RBIF=0;
    INTCONbits.RBIE=1;
    INTCONbits.GIE = 1;
    
    OSCCONbits.IRCF = 0b111; //8Mhz
    OSCCONbits.SCS = 1;
    //config tmr0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    TMR0 = _tmr0_value;
    
    //configuración de la interrupcion del TMR0
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    
    //Configuración del ADC
    ANSEL = 0b10; // Configurar AN0 y AN1 como entradas analógicas

    TRISA = 0b111; // Configurar RA0 y RA1 como entradas
    ADCON0bits.ADCS = 0b10;
    ADCON1bits.ADFM = 1;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON0bits.ADON = 1;
    ADIF = 0;
          
}
