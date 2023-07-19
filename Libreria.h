
/* 
 * File: Libreria   
 * Author: Karla Lopez  
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LIBRERIA_H
#define	LIBRERIA_H

#include <xc.h> // include processor files - each processor file is guarded.  
void ConfigDisplay1(int digit1);

void ConfigDisplay2(int digit2);

void adc_init(int channel);

void adc_read (int Habilitar);

int adc_readValor ();

void confi_Botones (int Botones);


#endif	/* XC_HEADER_TEMPLATE_H */

