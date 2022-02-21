/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 18 de Fevereiro de 2022, 23:00
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal

#define LED PORTBbits.RB0                       //Pino RB0 definido com o nome LED

__bit inverte;                                  // Variável para inverter o valor do LED. Tipo de dados bit precisa ser global

void inicializar()
{    
    /* Inicialização das portas */
    TRISB = 0;                                  // Configura pinos como saída
    TRISC = 255;                                // Configura pinos como entrada
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configurações das interrupções    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.PEIE = 1;                        // Habilita a int dos periféricos
    PIE1bits. TMR1IE = 1;                       // Habilita a int do timer 1
    
    // Configuração do timer 1
    T1CONbits.TMR1CS = 1;                       // Define timer 1 como contador (externo)
    T1CONbits.T1CKPS0 = 0;                      // Bit para configurar pré-escala, neste caso 1:2
    T1CONbits.T1CKPS1 = 0;                      // Bit para configurar pré-escala, neste caso 1:2
    
    TMR1L = 0xEC;                               // Inicializar o contador em 65526
    TMR1H = 0xFF;                               // vai contar 10 pulsos, 65536 estoura
    
    T1CONbits.TMR1ON = 1;                       // Liga o timer
    
    // Inicialização das saídas    
    LED = 0;
};

// Rotina de Interrupção
void __interrupt() TrataInt(void)
{
    if (TMR1IF)                                 // Foi a interrupção externa que chamou a int?
    {
        PIR1bits.TMR1IF = 0;                    // Reseta o flag da interrupção
        TMR1L = 0xEC;                           // Reinicia a contagem com 65526
        TMR1H = 0xFF;
        
        // Comandos para tratar a interrupção
        inverte = ~inverte;                     // Inverte a variável
        LED = inverte;                          // Passa o valor invertido para o pino físico
    }
    return;
}


#endif	/* HEADER_H */