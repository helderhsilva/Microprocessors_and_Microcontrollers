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
    TRISB = 0;
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
};


// Liga e Desliga sequencial -> Verde -> Amarelo -> Amarelo -> Vermelho -> Retorna para o verde (Sem�foro), 1s cada
void sequentialLed()
{  
    PORTBbits.RB3 = 1;                          // Ascende o Led Verde em RB3
    __delay_ms(1000);                           // Aguarda 1s
    PORTBbits.RB3 = 0;                          // Apaga o Led em RB3
    
    PORTBbits.RB2 = 1;
    __delay_ms(1000);
    PORTBbits.RB2 = 0;
    
    PORTBbits.RB1 = 1;
    __delay_ms(1000);
    PORTBbits.RB1 = 0;
    
    PORTBbits.RB0 = 1;
    __delay_ms(1000);
    PORTBbits.RB0 = 0; 
};

#endif	/* HEADER_H */

