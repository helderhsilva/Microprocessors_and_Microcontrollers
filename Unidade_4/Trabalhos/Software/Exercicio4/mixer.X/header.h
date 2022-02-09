/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 8 de Fevereiro de 2022, 12:12
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal

#define Y1 PORTDbits.RD0
#define Y2 PORTDbits.RD1
#define Y3 PORTDbits.RD2
#define M1 PORTDbits.RD3

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicialização das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como saída
    
    PORTB = 0;                                  // Inicialização do Port B com 0V em todas as saídas
    PORTD = 0;                                  // Inicialização do Port D com 0V em todas as saídas
};

__bit start;
__bit SN;

// Rotina para verificar se o botão de ligar foi acionado
int verifyStart()
{
    start = PORTBbits.RB0;
    
    if (start == 0)                             // Botão liga foi pressionado?
    {
        return 1;                               // Sim - Retorna verdadeiro
    }
    return 0;                                   // Não - Retorna falso
};

int verifySN()
{
    SN = PORTBbits.RB7;
    
    if (SN == 0)                                // SN ativou?
    {
        return 1;                               // Sim - Retorna verdadeiro
    }
    return 0;                                   // Não - Retorna falso
};

#endif	/* HEADER_H */