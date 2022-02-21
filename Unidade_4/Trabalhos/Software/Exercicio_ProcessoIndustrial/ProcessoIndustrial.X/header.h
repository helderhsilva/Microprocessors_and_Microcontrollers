/* 
 * File:   header.h
 * Author: Helder e Lucas
 *
 * Created on 19 de Fevereiro de 2022, 18:49
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                 // Include Biblioteca Padrão
#include <stdio.h>                              // Include Biblioteca padrão C
#include <pic16f877a.h>                         // Include Biblioteca do Chip

#define _XTAL_FREQ 4000000                      // Frequência do Cristal 4Mhz

#define Sensor_Nivel_Cheio PORTBbits.RB1        // Pino RB1 definido como sensor de nível do reservatório para quando estiver cheio
#define Sensor_Nivel_Vazio PORTBbits.RB4        // Pino RB1 definido como sensor de nível do reservatório para quando estiver vazio
#define Sensor_Temperatura PORTBbits.RB5        // Pino RB1 definido como sensor de temperatura da água

#define Bomba PORTDbits.RD0                     // Pino RD0 definido como bomba d'água
#define Misturador PORTDbits.RD2                // Pino RD2 definido como misturador
#define Aquecedor PORTDbits.RD4                 // Pino RD4 definido como aquecedor
#define Saida PORTDbits.RD6                     // Pino RD6 definido como válvula de saída


__bit mistura;                                  // Variável para auxiliar a entrada e saída da interrupão. Tipo de dados bit precisa ser global
int contador = 0;                               // Variável auxiliar contador. Inicia com 0

void inicializar()
{    
    /* Inicialização das portas */
    TRISB = 0xFF;                               // Configura os pinos do PORTB como entrada
    TRISD = 0x00;                               // Configura os pinos do PORTD como saída
    
    OPTION_REGbits.nRBPU = 0;                   // Ativa os resistores de pull-ups
    
    // Configurações das interrupções    
    INTCONbits.GIE = 1;                         // Habilita a int global
    INTCONbits.PEIE = 1;                        // Habilita a int dos periféricos
    PIE1bits.TMR1IE = 1;                        // Habilita a int do timer 1
    
    // Configuração do timer 1
    T1CONbits.TMR1CS = 0;                       // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                      // Bit para configurar pré-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                      // Bit para configurar pré-escala como 1:8
    
    TMR1L = 0xDC;                               // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                               // 3036. Quando estourar contou 62500, passou 0,5s
    
    //T1CONbits.TMR1ON = 1;                     // Liga o timer
    
    // Inicialização das saídas    
    Bomba = 0;
    Misturador = 0;
    Aquecedor = 0;
    Saida = 0;
};

// Rotina de Interrupção
void __interrupt() TrataInt(void)
{
    if (TMR1IF)                                 // Foi a interrupção de estouro do timer 1 que chamou a int?
    {
        PIR1bits.TMR1IF = 0;                    // Reseta o flag da interrupção
        TMR1L = 0xDC;                           // Reinicia a contagem com 3036
        TMR1H = 0x0B;
        
        // Tratamento da interrupção
        contador++;
        if (contador == 20)
        {
            mistura = 1;                        // Finalizou os 10 segundos
            Misturador = 0;                     // Desligou o misturador
            Saida = 1;                          // Abre a válvula de saída
            contador = 0;                       // Reseta o contador do temporizador
            T1CONbits.TMR1ON = 0;               // Desliga o Timer
        }
    }
    return;
};

// Desliga a bomba e verifica com um if se o sensor de temperatura foi ativado
// Se o sensor não foi ativado, liga o aquecedor e indica que ainda não houve mistura (mistura = 0)
// Se não, desliga o aquecedor e liga o misturador e a interrupção de temporizador TMR1ON = 1 "if (T1CONbits.TMR1ON == 0 && mistura == 0)"
// Para sair da verificação do misturador devemos ter TM1ON = 0 e misturou = 1 na interrupção
void Desliga_Bomba()
{
    Bomba = 0;
    
    if (Saida == 0)                             // Se a saida estiver fechada
    {
        if (Sensor_Temperatura == 0)            // Se o sensor de temperatura for ativado - T = 40ºC
        {
            Aquecedor = 0;                      // Desliga o aquecedor

            // Se o Timer estiver desligado e não tiver ocorrido a mistura ainda
            if (T1CONbits.TMR1ON == 0 && mistura == 0)
            {
                Misturador = 1;                 // Liga o misturador
                T1CONbits.TMR1ON = 1;           // Liga o timer por 10 segundos
            }
        }
        else                                    // Se não, liga o aquecedor e avisa que a mistura ainda não ocorreu
        {
            Aquecedor = 1;
            mistura = 0; 
        }
    }
};

// É obvio o que ocorre aqui. Liga a bomba
void Liga_Bomba()
{
    Saida = 0;
    Bomba = 1;
    Aquecedor = 0;
    Misturador = 0;
};

#endif	/* HEADER_H */

