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
#define Y1 PORTDbits.RD6
#define Y2 PORTDbits.RD2

void inicializar()
{
    OPTION_REG = 127;                           // Resistores Pull-up ativados "0b01111111"
    
    /* Inicialização das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como saída
    
    PORTB = 0;                                  // Inicialização do Port B com 0V em todas as saídas
    PORTD = 0;                                  // Inicialização do Port D com 0V em todas as saídas
};

__bit button1;
__bit button2;

// Verifica se os dois botões foram pressionados
int buttonPressVerify()
{
    button1 = PORTBbits.RB2;
    button2 = PORTBbits.RB7;
    
    if (button1 == 0 && button2 == 0)           // O botão 1 AND o botão 2 foram pressionados?
    {
        return 1;                               // Sim - Retorna Verdadeiro
    }
    return 0;                                   // Não - Retorna Falso
};

#endif	/* HEADER_H */