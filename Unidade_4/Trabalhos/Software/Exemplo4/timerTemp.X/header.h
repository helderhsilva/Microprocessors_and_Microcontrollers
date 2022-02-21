/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 18 de Fevereiro de 2022, 23:03
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padr�o
#include <stdio.h>                              // Include Biblioteca padr�o C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 20000000                     // Frequ�ncia do Cristal

#define LED PORTBbits.RB0                       //Pino RB0 definido com o nome LED

__bit inverte;                                  // Vari�vel para inverter o valor do LED. Tipo de dados bit precisa ser global
int conta = 0;                                  // vari�vel auxiliar conta. Inicia com 0

void inicializar()
{    
    /* Inicializa��o das portas */
    TRISB = 0b00000000;                         // Configura pinos como sa�da
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configura��es das interrup��es    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.PEIE = 1;                        // Habilita a int dos perif�ricos
    PIE1bits. TMR1IE = 1;                       // Habilita a int do timer 1
    
    // Configura��o do timer 1
    T1CONbits.TMR1CS = 0;                       // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                      // Bit para configurar pr�-escala, neste caso 1:8
    T1CONbits.T1CKPS1 = 1;                      // Bit para configurar pr�-escala, neste caso 1:8
    
    TMR1L = 0xDC;                               // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                               // 3036. Quando estourar contou 62500, passou 0,1s
    
    T1CONbits.TMR1ON = 1;                       // Liga o timer
    
    // Inicializa��o das sa�das    
    LED = 0;
};

// Rotina de Interrup��o
void __interrupt() TrataInt(void)
{
    if (TMR1IF)                                 // Foi a interrup��o de estouro do timer 1 que chamou a int?
    {
        PIR1bits.TMR1IF = 0;                    // Reseta o flag da interrup��o
        TMR1L = 0xDC;                           // Reinicia a contagem com 3036
        TMR1H = 0x0B;
        
        // Tratamento da interrup��o
        conta++;
        if (conta == 10)
        {
            inverte = ~inverte;                 // Inverte a vari�vel;
            LED = inverte;                      // Passa o valor invertido para o LED
            conta = 0;
        }
    }
    return;
}


#endif	/* HEADER_H */
