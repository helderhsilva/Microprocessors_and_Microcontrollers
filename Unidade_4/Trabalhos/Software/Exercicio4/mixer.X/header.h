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

#define Y1 PORTDbits.RD0
#define Y2 PORTDbits.RD1
#define Y3 PORTDbits.RD2
#define M1 PORTDbits.RD3

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicializa��o das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como sa�da
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
    PORTD = 0;                                  // Inicializa��o do Port D com 0V em todas as sa�das
};

__bit start;
__bit SN;

// Rotina para verificar se o bot�o de ligar foi acionado
int verifyStart()
{
    start = PORTBbits.RB0;
    
    if (start == 0)                             // Bot�o liga foi pressionado?
    {
        return 1;                               // Sim - Retorna verdadeiro
    }
    return 0;                                   // N�o - Retorna falso
};

int verifySN()
{
    SN = PORTBbits.RB7;
    
    if (SN == 0)                                // SN ativou?
    {
        return 1;                               // Sim - Retorna verdadeiro
    }
    return 0;                                   // N�o - Retorna falso
};

#endif	/* HEADER_H */