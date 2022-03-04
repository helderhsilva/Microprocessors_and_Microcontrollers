/* 
 * File:   header.h
 * Author: Helder Henrique da Silva e Lucas Floriano Garcia
 * 
 * Created on 02 de Mar�o de 2022, 18:00
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                                 // Include Biblioteca padr�o do compilador
#include <stdio.h>                                              // Include Biblioteca padr�o "C"
#include <pic16f877a.h>                                         // Include Biblioteca Standart padr�o do Chip que ser� usado
#include "lcd.h"                                                // Include Define dos pinos do LCD e fun��es de inicializa��o

#define _XTAL_FREQ 4000000                                      // Frequ�ncia do clock no Cristal definida em 4Mhz

// Fun��o de inicializa��o
void inicializar()
{    
    // Inicializa��o das portas
    TRISB = 0xFF;                                               // Configura os pinos do PORTB como entrada
    TRISC = 0x00;                                               // Configura os pinos do PORTC como sa�da - Motores de Passo
    TRISD = 0x00;                                               // Configura os pinos do PORTD como sa�da - LCD
    
    OPTION_REG = 0b00111111;                                    // Resistores Pull-up ativados e INTEDG sens�vel a descida em 0 "bit 6"
    
    // Configura��es das interrup��es    
    INTCONbits.GIE = 1;                                         // Habilita a INT global
    INTCONbits.PEIE = 1;                                        // Habilita a INT dos perif�ricos
    INTCONbits.INTE = 1;                                        // Habiliata a INT externa do RB0/INT
    PIE1bits.TMR1IE = 1;                                        // Habilita a INT do timer 1
    
    // Configura��o do timer 1
    T1CONbits.TMR1CS = 0;                                       // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                                      // Bit para configurar pr�-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                                      // Bit para configurar pr�-escala como 1:8
    
    TMR1L = 0xDC;                                               // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                                               // 3036. Quando estourar contou 62500, passou 0,5s
    
    //****** congiguration bits  **************************************************
    #pragma config WDTE = OFF                                   // Desabilita o uso do WDT
    #pragma config FOSC = HS                                    // Define uso do clock externo EM 4 OU 20mHZ
    #pragma config PWRTE = ON                                   // Habilita reset ao ligar
    #pragma config BOREN = ON                                   // Habilita o reset por Brown-out 

    // Define os pinos de entradas
    #define S_TAMPA_SUPERIOR    PORTBbits.RB1                   // Sensor para a tampa superior fechada
    #define TAMPA_INFERIOR      PORTBbits.RB2                   // Bot�o para a tampa inferior
    #define S_TAMPA_INFERIOR    PORTBbits.RB3                   // Sensor para a tampa inferior fechada
    #define S_VASILHA           PORTBbits.RB4                   // Sensor de n�vel da vasilha
    #define INICIAR_PROCESSO    PORTBbits.RB5                   // Switch para iniciar o processo de contagem

    // Define os pinos do motor de passo
    #define C1 PORTCbits.RC0                                    // Motor da tampa superior 1C
    #define C2 PORTCbits.RC1                                    // Motor da tampa superior 2C
    #define C3 PORTCbits.RC2                                    // Motor da tampa superior 3C
    #define C4 PORTCbits.RC3                                    // Motor da tampa superior 4C

    #define C5 PORTCbits.RC4                                    // Motor da tampa inferior 1C
    #define C6 PORTCbits.RC5                                    // Motor da tampa inferior 2C
    #define C7 PORTCbits.RC6                                    // Motor da tampa inferior 3C
    #define C8 PORTCbits.RC7                                    // Motor da tampa inferior 4C

    // Inicializa��o das portas em 0
    PORTB = 1;                                                  // Inicializa��o do Port B com 5V em todas os pinos
    PORTC = 0;                                                  // Inicializa��o do Port C com 0V em todas os pinos
    PORTD = 0;                                                  // Inicializa��o do Port D com 0V em todas os pinos
    

    // Configura��o do conversor anal�gico/digital
    // Ficar� somente com o pino AN0 como entrada anal�gica. (TABELA NO DATASHEET)
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;

    // Define o clock de convers�o
    // Confirmando default Fosc/2
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 0;

    ADCON1bits.ADFM = 0   ;                                     // Default � 0. Pra mostrar que pegar� os dados em 8 bits 
                                                                // no ADRESH, pois est� justifica � esquerda
                                                                // Passando pra 1 pode pegar os dados em 10 bits 
                                                                // usando os dois registradores ADRESHL justificado � direita

    //inicializa registradores do AD
    ADRESL = 0x00;                                              // Inicializar valor anal�gico com 0
    ADRESH = 0x00;

    ADCON0bits.ADON = 1;                                        //Liga o conversor A/D
   
    Lcd_Init();                                                 // Inicializa��o do LCD
    
};

// Fun��es Auxiliares
void abreTampaSuperior(){
         C1 = 1;
         C2 = 0;
         C3 = 0;
         C4 = 1;        
}

void fechaTampaSuperior(){
         C1 = 0;
         C2 = 1;
         C3 = 0;
         C4 = 1;
}

// Rotina de Interrup��o
void __interrupt() TrataInt(void)
{
    if(INTF)
    {    
        INTCONbits.INTF = 0; //Interrupcao ta ativa
                  
    }

    return;
};

#endif	/* HEADER_H */
