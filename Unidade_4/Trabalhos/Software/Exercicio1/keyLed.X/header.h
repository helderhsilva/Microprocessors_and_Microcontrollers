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

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicializa��o das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como sa�da
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
    PORTD = 0;                                  // Inicializa��o do Port D com 0V em todas as sa�das
};

__bit chave;

// Se a chave estiver em 0 o apaga, se n�o o led ascende
void On_Off_Key()
{   
    chave = PORTBbits.RB0;
    
    if (chave == 1)
    {
        PORTDbits.RD7 = 0;
    }
    else
    {
        PORTDbits.RD7 = 1;
    } 
};

#endif	/* HEADER_H */