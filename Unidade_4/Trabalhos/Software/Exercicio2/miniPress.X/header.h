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
#define Y1 PORTDbits.RD6
#define Y2 PORTDbits.RD2

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicializa��o das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como sa�da
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
    PORTD = 0;                                  // Inicializa��o do Port D com 0V em todas as sa�das
};

__bit button1;
__bit button2;

// Verifica se os dois bot�es foram pressionados
int buttonPressVerify()
{
    button1 = PORTBbits.RB2;
    button2 = PORTBbits.RB7;
    
    if (button1 == 0 && button2 == 0)           // O bot�o 1 AND o bot�o 2 foram pressionados?
    {
        return 1;                               // Sim - Retorna Verdadeiro
    }
    return 0;                                   // N�o - Retorna Falso
};

#endif	/* HEADER_H */