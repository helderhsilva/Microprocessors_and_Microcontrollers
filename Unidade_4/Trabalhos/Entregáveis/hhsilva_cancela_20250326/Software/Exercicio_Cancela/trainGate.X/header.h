/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 13 de Fevereiro de 2022, 11:36
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal

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
    OPTION_REG = 0b00111111;                    // Resistores Pull-up ativados e INTEDG sensível a descida em 0 "bit 6"
    
    INTCON = 0b10010000;                        // Ativa os bits GIE e INTE, u seha, a interrupção através do pino RB0
    //INTCONbits.GIE = 1;                       // Pode ser feito assim também
    //INTCONbits.INTE = 1;                      // Pode ser feito assim também
    
    /* Inicialização das portas */
    TRISB = 255;                                // Port B como entrada
    TRISC = 0;                                  // Port C como saída
    TRISD = 0;                                  // Port D como saída
    
    PORTB = 0;                                  // Inicialização do Port B com 0V em todas as saídas
    PORTC = 0;                                  // Inicialização do Port C com 0V em todas as saídas
    PORTD = 0;                                  // Inicialização do Port D com 0V em todas as saídas
};


int flag;                                       // Variável de verificação da interrupção
int aux;                                        // Variável para verificação de processo

// Rotina de Interrupção
void __interrupt() AiVemOTrem(void)
{
    if (INTF)
    {
        INTCONbits.INTF = 0;
        
        if (SA == 0 && SCA == 0)                // Se o sensor de automóvel estiver ativado e a cancela aberta
        {
            for (int i = 0; i < 5; i++)         // Ativa a sirene por 20 segundos (5 segundos para exemplificação)
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
                
                if (SCF != 0)       // Se a cancela não estiver fechada
                {
                    MCF = 1;                    // Liga o motor de fechar a cancela
                    fechando = 1;               // Liga a luz sinalizandor que a cancela está sendo fechada
                }
                else                            // Se não
                {
                    MCF = 0;                    // Desliga o motor para fechar a cancela
                    fechando = 0;               // Desliga o sinalizador que a cancela está fechando
                }
            }
            
            flag = 1;                           // Atribui a flag que houve interrupção
        }
        else                                    // Se não
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
            
            flag = 1;                           // Atribui a flag que houve interrupção
        }    
    }
    return;
}

void abreCancela()
{
    MCF = 0;                                    // Desliga o motor de fechar a cancela
    fechando = 0;                               // Desliga o sinalizador que a cancela está fechando
    MCA = 1;                                    // Liga o motor de abrir a cancela
    abrindo = 1;                                // Liga o sinalizazdor que a cancela está abrindo
};

void fechaCancela()
{
    MCF = 1;                                    // Liga o motor de fechar a cancela
    fechando = 1;                               // Liga o sinalizador que a cancela está fechando
    MCA = 0;                                    // Desliga o motor de abrir a cancela
    abrindo = 0;                                // Desliga o sinalizazdor que a cancela está abrindo
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