/*
 * File:   Libreria.c
 * Author: karla
 *
 * Created on 13 de julio de 2023, 04:13 PM
 */


#include <xc.h>
#include "Libreria.h"
#define _XTAL_FREQ 8000000 



int adc_readValor (){
    return ((ADRESH<<8) | ADRESL); // Leer el resultado de la conversión ADC de los registros ADRESH y ADRESL;
}



void adc_init(int channel){
    
    if (channel==1){
        ADCON0bits.CHS = 0b0001; // Seleccionar el canal AN1 para la conversión ADC
    }
    if (channel==2){
        ADCON0bits.CHS = 0b0010; // Seleccionar el canal AN1 para la conversión ADC
    }
}

void confi_Botones (int Botones){
    if (Botones==1)
    TRISB = 0b00000001;
    if (Botones==2)
    TRISB = 0b00000011;
    if (Botones==3)
    TRISB = 0b00000111;
    if (Botones==4)
    TRISB = 0b00001111;
    if (Botones==5)
    TRISB = 0b00011111;
    if (Botones==6)
    TRISB = 0b00111111;
    if (Botones==7)
    TRISB = 0b01111111;
    if (Botones==8)
    TRISB = 0b11111111;
}

void adc_read (int Habilitar){
    if(Habilitar==1)
    ADCON0bits.GO_DONE = 1; // Iniciar la conversión ADC
    if(Habilitar==0)
    ADCON0bits.GO_DONE = 0; // Iniciar la conversión ADC
    
}

void ConfigDisplay1(int digit1){
    int VALOR;
    switch (digit1) {
        case 0:
            VALOR = 0b00111111;
            break;
        case 1:
            VALOR = 0b10000110;
            break;
        case 2:
            VALOR = 0b11011011;
            break;
        case 3:
            VALOR = 0b11001111;
            break;
        case 4:
            VALOR = 0b01100110;
            break;
        case 5:
            VALOR = 0b11101101;
            break;
        case 6:
            VALOR = 0b11111101;
            break;
        case 7:
            VALOR = 0b10000111;
            break;
        case 8:
            VALOR = 0b11111111;
            break;
        case 9:
            VALOR = 0b11100111;
            break;
        default:
            break;
    }

    //Mostrar valor en display

}


void ConfigDisplay2(int digit2){
    int VALOR;
    switch (digit2) {
        case 0:
            VALOR = 0b00111111;
            break;
        case 1:
            VALOR = 0b00000110;
            break;
        case 2:
            VALOR = 0b01011011;
            break;
        case 3:
            VALOR = 0b01001111;
            break;
        case 4:
            VALOR = 0b01100110;
            break;
        case 5:
            VALOR = 0b01101101;
            break;
        case 6:
            VALOR = 0b01111101;
            break;
        case 7:
            VALOR = 0b00000111;
            break;
        case 8:
            VALOR = 0b01111111;
            break;
        case 9:
            VALOR = 0b01100111;
            break;
        default:
            break;
    }


    PORTEbits.RE1 = 1; // Encender primer ánodo común
    PORTD=VALOR;
    PORTEbits.RE1 = 0; // Encender primer ánodo común
    
   
}