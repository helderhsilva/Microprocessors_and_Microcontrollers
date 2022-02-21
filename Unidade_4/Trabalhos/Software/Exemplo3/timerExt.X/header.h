/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 18 de Fevereiro de 2022, 16:02
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padr�o
#include <stdio.h>                              // Include Biblioteca padr�o C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequ�ncia do Cristal

#define LED PORTAbits.RA5                       //Pino RA5 definido com o nome LED

__bit inverte;                                  // Vari�vel para inverter o valor do LED. Tipo de dados bit precisa ser global

void inicializar()
{    
    /* Inicializa��o das portas */
    TRISA = 0b00011111;                         // Configura pinos de entradas (1) e sa�da (0)
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configura��es das interrup��es
    OPTION_REGbits.T0CS = 1;                    // Define o timer 0 como contador externo 
    OPTION_REGbits.T0SE = 0;                    // Vai contar na borda de 1 para 0, esse � o default
    OPTION_REGbits.PS0 = 1;                     // Configura pr�-escalar
    OPTION_REGbits.PS1 = 1;                     // Configura pr�-escalar
    OPTION_REGbits.PS2 = 1;                     // Configura pr�-escalar
    OPTION_REGbits.PSA = 1;                     // Configura pr�-escalar para WDT, logo fica 1:1
    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.TMR0IE = 1;                      // habilita a int do timer 0
    
    TMR0 = 251;                                 // Inicializar o contador em 251, vai contar 5, 256 estoura
    
    LED = 0;
};

// Rotina de Interrup��o
void __interrupt() TrataInt(void)
{
    if (TMR0IF)                                 // Foi a interrup��o externa que chamou a int?
    {
        INTCONbits.TMR0IF = 0;                  // Reseta o flag da interrup��o
        TMR0 = 251;                             // Reinicializa a contagem
        
        // Comandos para tratar a interrup��o
        inverte = ~inverte;                     // Inverte a vari�vel
        LED = inverte;                          // Passa o valor invertido para o pino f�sico
    }
    return;
}


#endif	/* HEADER_H */