/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exempplo 1 - Pisca Led em C
* Autor: Helder Henrique da Silva - 20250326
* Create File: 01/02/2022
* Funcionalidade:
* Liga e Desliga os Leds
*/

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal

// Primeira Rotina
void primeiraRotina()
{
    PORTBbits.RB1 = 1;
    PORTBbits.RB3 = 1;
    PORTBbits.RB6 = 1;
    PORTBbits.RB7 = 1;
    __delay_ms(300);
    
    PORTBbits.RB2 = 1;
    PORTBbits.RB5 = 1;
    __delay_ms(300);
    
    PORTBbits.RB4 = 1;
    __delay_ms(300);
    
    PORTBbits.RB4 = 0;
    __delay_ms(300);
    
    PORTBbits.RB2 = 0;
    PORTBbits.RB5 = 0;
    __delay_ms(300);
    
    PORTBbits.RB1 = 0;
    PORTBbits.RB3 = 0;
    PORTBbits.RB6 = 0;
    PORTBbits.RB7 = 0;
    __delay_ms(300);
}

// Segunda Rotina
void segundaRotina()
{
    PORTBbits.RB1 = 1;
    PORTBbits.RB2 = 1;
    PORTBbits.RB3 = 1;
    PORTBbits.RB4 = 1;
    PORTBbits.RB5 = 1;
    PORTBbits.RB6 = 1;
    PORTBbits.RB7 = 1;
    __delay_ms(900);
    
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    PORTBbits.RB3 = 0;
    PORTBbits.RB4 = 0;
    PORTBbits.RB5 = 0;
    PORTBbits.RB6 = 0;
    PORTBbits.RB7 = 0;
    __delay_ms(900);

}

void main(void) {
    
    TRISB = 0;                                  // Port B como saída
    
    while (1)
    {
       primeiraRotina();
       primeiraRotina();
       primeiraRotina();
       segundaRotina();
       segundaRotina();
    }
}
