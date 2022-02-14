/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 13 de Fevereiro de 2022, 11:36
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padr�o
#include <stdio.h>                              // Include Biblioteca padr�o C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequ�ncia do Cristal

#define ST PORTBbits.RB0
#define SA PORTBbits.RB1
#define SCF PORTBbits.RB2
#define SCA PORTBbits.RB3

#define BUZZ PORTCbits.RC0
#define abrindo PORTCbits.RC4
#define MCA PORTCbits.RC7

#define fechando PORTDbits.RD0
#define MCF PORTDbits.RD3

void inicializar()
{
    OPTION_REG = 0b00111111;                    // Resistores Pull-up ativados e INTEDG sens�vel a descida em 0 "bit 6"
    
    INTCON = 0b10010000;                        // Ativa os bits GIE e INTE, u seha, a interrup��o atrav�s do pino RB0
    //INTCONbits.GIE = 1;                       // Pode ser feito assim tamb�m
    //INTCONbits.INTE = 1;                      // Pode ser feito assim tamb�m
    
    /* Inicializa��o das portas */
    TRISB = 255;                                // Port B como entrada
    TRISC = 0;                                  // Port C como sa�da
    TRISD = 0;                                  // Port D como sa�da
    
    PORTB = 0;                                  // Inicializa��o do Port B com 0V em todas as sa�das
    PORTC = 0;                                  // Inicializa��o do Port C com 0V em todas as sa�das
    PORTD = 0;                                  // Inicializa��o do Port D com 0V em todas as sa�das
};


int flag;                                       // Vari�vel de verifica��o da interrup��o
int aux;                                        // Vari�vel para verifica��o de processo

// Rotina de Interrup��o
void __interrupt() AiVemOTrem(void)
{
    if (INTF)
    {
        INTCONbits.INTF = 0;
        
        if (SA == 0 && SCA == 0)                // Se o sensor de autom�vel estiver ativado e a cancela aberta
        {
            for (int i = 0; i < 5; i++)         // Ativa a sirene por 20 segundos (5 segundos para exemplifica��o)
            {
                BUZZ = 1;                       // Liga a sirene
                __delay_ms(500);
                BUZZ = 0;                       // Desliga a sirene
                __delay_ms(500);
            }
            
            while (ST != 1)                     // Enquanto o sensor do trem estiver ativado
            {
                BUZZ = 1;                       // Liga a sirene
                __delay_ms(500);
                BUZZ = 0;                       // Desliga a sirene
                __delay_ms(500);
                
                if (SCF != 0)       // Se a cancela n�o estiver fechada
                {
                    MCF = 1;                    // Liga o motor de fechar a cancela
                    fechando = 1;               // Liga a luz sinalizandor que a cancela est� sendo fechada
                }
                else                            // Se n�o
                {
                    MCF = 0;                    // Desliga o motor para fechar a cancela
                    fechando = 0;               // Desliga o sinalizador que a cancela est� fechando
                }
            }
            
            flag = 1;                           // Atribui a flag que houve interrup��o
        }
        else                                    // Se n�o
        {
            while (ST != 1)                     // Enquanto o ensor do trem estiver ativado
            {
                BUZZ = 1;                       // Liga a sirene
                __delay_ms(500);
                BUZZ = 0;                       // Desliga a sirene
                __delay_ms(500);
                
                MCF = 0;                        // Desliga o motor de fechar a cancela
                MCA = 0;                        // Desliga o motor de abrir a cancela
                abrindo = 0;                    // Desliga o sinalizador de abrir a cancela
                fechando = 0;                   // Desliga o sinalizador de fechar a cancela
            }
            
            flag = 1;                           // Atribui a flag que houve interrup��o
        }    
    }
    return;
}

void abreCancela()
{
    MCF = 0;                                    // Desliga o motor de fechar a cancela
    fechando = 0;                               // Desliga o sinalizador que a cancela est� fechando
    MCA = 1;                                    // Liga o motor de abrir a cancela
    abrindo = 1;                                // Liga o sinalizazdor que a cancela est� abrindo
};

void fechaCancela()
{
    MCF = 1;                                    // Liga o motor de fechar a cancela
    fechando = 1;                               // Liga o sinalizador que a cancela est� fechando
    MCA = 0;                                    // Desliga o motor de abrir a cancela
    abrindo = 0;                                // Desliga o sinalizazdor que a cancela est� abrindo
};

void desligaMotores()
{
    // Desliga todos os componentes da cancela
    abrindo = 0;
    fechando = 0;
    MCA = 0;
    MCF = 0;
}

#endif	/* HEADER_H */