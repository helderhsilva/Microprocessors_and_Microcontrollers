/* 
 * File:   header.h
 * Author: Helder e Lucas
 *
 * Created on 19 de Fevereiro de 2022, 18:49
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padr�o
#include <stdio.h>                              // Include Biblioteca padr�o C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequ�ncia do Cristal 4Mhz

#define Sensor_Nivel_Cheio PORTBbits.RB1        // Pino RB1 definido como sensor de n�vel do reservat�rio para quando estiver cheio
#define Sensor_Nivel_Vazio PORTBbits.RB4        // Pino RB1 definido como sensor de n�vel do reservat�rio para quando estiver vazio
#define Sensor_Temperatura PORTBbits.RB5        // Pino RB1 definido como sensor de temperatura da �gua

#define Bomba PORTDbits.RD0                     // Pino RD0 definido como bomba d'�gua
#define Misturador PORTDbits.RD2                // Pino RD2 definido como misturador
#define Aquecedor PORTDbits.RD4                 // Pino RD4 definido como aquecedor
#define Saida PORTDbits.RD6                     // Pino RD6 definido como v�lvula de sa�da


__bit mistura;                                  // Vari�vel para auxiliar a entrada e sa�da da interrup�o. Tipo de dados bit precisa ser global
int contador = 0;                               // Vari�vel auxiliar contador. Inicia com 0

void inicializar()
{    
    /* Inicializa��o das portas */
    TRISB = 0xFF;                               // Configura os pinos do PORTB como entrada
    TRISD = 0x00;                               // Configura os pinos do PORTD como sa�da
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configura��es das interrup��es    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.PEIE = 1;                        // Habilita a int dos perif�ricos
    PIE1bits.TMR1IE = 1;                        // Habilita a int do timer 1
    
    // Configura��o do timer 1
    T1CONbits.TMR1CS = 0;                       // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                      // Bit para configurar pr�-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                      // Bit para configurar pr�-escala como 1:8
    
    TMR1L = 0xDC;                               // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                               // 3036. Quando estourar contou 62500, passou 0,5s
    
    //T1CONbits.TMR1ON = 1;                     // Liga o timer
    
    // Inicializa��o das sa�das    
    Bomba = 0;
    Misturador = 0;
    Aquecedor = 0;
    Saida = 0;
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
        contador++;
        if (contador == 20)
        {
            mistura = 1;                        // Finalizou os 10 segundos
            Misturador = 0;                     // Desligou o misturador
            Saida = 1;                          // Abre a v�lvula de sa�da
            contador = 0;                       // Reseta o contador do temporizador
            T1CONbits.TMR1ON = 0;               // Desliga o Timer
        }
    }
    return;
};

// Desliga a bomba e verifica com um if se o sensor de temperatura foi ativado
// Se o sensor n�o foi ativado, liga o aquecedor e indica que ainda n�o houve mistura (mistura = 0)
// Se n�o, desliga o aquecedor e liga o misturador e a interrup��o de temporizador TMR1ON = 1 "if (T1CONbits.TMR1ON == 0 && mistura == 0)"
// Para sair da verifica��o do misturador devemos ter TM1ON = 0 e misturou = 1 na interrup��o
void Desliga_Bomba()
{
    Bomba = 0;
    
    if (Saida == 0)                             // Se a saida estiver fechada
    {
        if (Sensor_Temperatura == 0)            // Se o sensor de temperatura for ativado - T = 40�C
        {
            Aquecedor = 0;                      // Desliga o aquecedor

            // Se o Timer estiver desligado e n�o tiver ocorrido a mistura ainda
            if (T1CONbits.TMR1ON == 0 && mistura == 0)
            {
                Misturador = 1;                 // Liga o misturador
                T1CONbits.TMR1ON = 1;           // Liga o timer por 10 segundos
            }
        }
        else                                    // Se n�o, liga o aquecedor e avisa que a mistura ainda n�o ocorreu
        {
            Aquecedor = 1;
            mistura = 0; 
        }
    }
};

// � obvio o que ocorre aqui. Liga a bomba
void Liga_Bomba()
{
    Saida = 0;
    Bomba = 1;
    Aquecedor = 0;
    Misturador = 0;
};

#endif	/* HEADER_H */

