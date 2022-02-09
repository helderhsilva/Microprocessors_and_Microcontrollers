/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 8 de Fevereiro de 2022, 12:12
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padr�o
#include <stdio.h>                              // Include Biblioteca padr�o C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequ�ncia do Cristal
#define Led10 PORTDbits.RD0
#define Led0 PORTDbits.RD7

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicializa��o das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como sa�da
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
    PORTD = 0;                                  // Inicializa��o do Port D com 0V em todas as sa�das
};

__bit increment;
__bit decrement;

// Rotina para incrementar o valor
void incrementValue(int *valueInc)
{
    *valueInc = *valueInc + 1;
    __delay_ms(400);                            // Debounce
};

int decrementValue(int valueDec)
{
    valueDec--;
    __delay_ms(400);                            // Debounce
    
    return valueDec;
};

#endif	/* HEADER_H */