/* 
 * File:   header.h
 * Author: Helder
 *
 * Created on 10 de Fevereiro de 2022, 10:12
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
    OPTION_REG = 0b00111111;                    // Resistores Pull-up ativados e INTEDG sensível a descida em 0 "bit 6"
    
    INTCON = 0b10010000;                        // Ativa os bits GIE e INTE, u seha, a interrupção através do pino RB0
    //INTCONbits.GIE = 1;                       // Pode ser feito assim também
    //INTCONbits.INTE = 1;                      // Pode ser feito assim também
    
    /* Inicialização das portas */
    TRISB = 255;                                // Port B como entrada
    TRISD = 0;                                  // Port D como saída
    
    PORTB = 0;                                  // Inicialização do Port B com 0V em todas as saídas
    PORTD = 0;                                  // Inicialização do Port D com 0V em todas as saídas
};

int flag;
int aux;
__bit start;
__bit SN;

// Rotina de Interrupção
void __interrupt() SOS(void)
{
    if (INTF)
    {
        INTCONbits.INTF = 0;
        Y1 = 0;
        Y2 = 0;
        Y3 = 1;
        M1 = 0;
        
        flag = 1;
    }
    return;
}

// Rotina para verificar se o botão de ligar foi acionado
int verifyStart()
{
    start = PORTBbits.RB3;
    
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