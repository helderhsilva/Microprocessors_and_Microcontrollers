/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 18 de Fevereiro de 2022, 16:02
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal

#define LED PORTAbits.RA5                       //Pino RA5 definido com o nome LED

__bit inverte;                                  // Variável para inverter o valor do LED. Tipo de dados bit precisa ser global

void inicializar()
{    
    /* Inicialização das portas */
    TRISA = 0b00011111;                         // Configura pinos de entradas (1) e saída (0)
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configurações das interrupções
    OPTION_REGbits.T0CS = 1;                    // Define o timer 0 como contador externo 
    OPTION_REGbits.T0SE = 0;                    // Vai contar na borda de 1 para 0, esse é o default
    OPTION_REGbits.PS0 = 1;                     // Configura pré-escalar
    OPTION_REGbits.PS1 = 1;                     // Configura pré-escalar
    OPTION_REGbits.PS2 = 1;                     // Configura pré-escalar
    OPTION_REGbits.PSA = 1;                     // Configura pré-escalar para WDT, logo fica 1:1
    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.TMR0IE = 1;                      // habilita a int do timer 0
    
    TMR0 = 251;                                 // Inicializar o contador em 251, vai contar 5, 256 estoura
    
    LED = 0;
};

// Rotina de Interrupção
void __interrupt() TrataInt(void)
{
    if (TMR0IF)                                 // Foi a interrupção externa que chamou a int?
    {
        INTCONbits.TMR0IF = 0;                  // Reseta o flag da interrupção
        TMR0 = 251;                             // Reinicializa a contagem
        
        // Comandos para tratar a interrupção
        inverte = ~inverte;                     // Inverte a variável
        LED = inverte;                          // Passa o valor invertido para o pino físico
    }
    return;
}


#endif	/* HEADER_H */