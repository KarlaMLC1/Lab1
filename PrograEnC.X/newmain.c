/*
 * File:   newmain.c
 * Author: karla
 *
 * Created on 24 de marzo de 2023, 02:49 PM
 */

/*
 * File:   main.c
 * Author: karla
 *
 * Created on 23 de marzo de 2023, 05:50 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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


#define _tmr0_value 200

#define _XTAL_FREQ 8000000

void __interrupt() isr(void){
  if(ADIF){
      if (ADCON0bits.CHS == 0) {
          PORTC = ADRESH;
          ADCON0bits.CHS = 1;
      } else {
          PORTD = ADRESH;
          ADCON0bits.CHS = 0;
      }
      ADIF = 0;
  }  
}

void setup(void);
void main(void){
    
    setup();
    while(1){
        ADCON0bits.GO= 1; 
        __delay_us(50);
    }
    return;
}

void setup(void){
  ANSEL=0b00000011;   // Selecciona AN0 y AN1 como entradas analógicas
  ANSELH=0;
  TRISC=0;
  TRISD=0;
  
  OSCCONbits.IRCF= 0b111; //8Mhz
  OSCCONbits.SCS= 1;
  
  // Configuración del ADC
  ADCON0bits.ADCS= 0b10;    // FOSC/32
  ADCON0bits.CHS = 0;       // Selecciona AN0 como entrada analógica
  ADCON0bits.ADON= 1;       // Enciende el módulo ADC
  ADCON1bits.ADFM= 1;       // Resultados justificados a la derecha
  ADCON1bits.VCFG0= 0;      // Voltaje de referencia en VSS
  ADCON1bits.VCFG1= 0;      // Voltaje de referencia en VDD
  
  // Configuración de la interrupción del ADC
  PIE1bits.ADIE = 1;        // Habilita la interrupción del ADC
  PIR1bits.ADIF = 0;        // Limpia la bandera de interrupción del ADC
  INTCONbits.PEIE = 1;      // Habilita las interrupciones de periféricos
  INTCONbits.GIE = 1;       // Habilita las interrupciones globales
  
  return;
}
