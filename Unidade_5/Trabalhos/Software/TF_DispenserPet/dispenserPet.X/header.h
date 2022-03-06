/* 
 * File:   header.h
 * Author: Helder Henrique da Silva e Lucas Floriano Garcia
 * 
 * Created on 02 de Março de 2022, 18:00
 */

#ifndef HEADER_H
#define	HEADER_H

#include <xc.h>                                                 // Include Biblioteca padrão do compilador
#include <stdio.h>                                              // Include Biblioteca padrão "C"
#include <pic16f877a.h>                                         // Include Biblioteca Standart padrão do Chip que será usado
#include "lcd.h"                                                // Include e Define dos pinos do LCD e funções de inicialização
#include "stepper.h"                                            // Include e Define dos pinos para os motores de passo e suas funções auxiliares

#define _XTAL_FREQ 4000000                                      // Frequência do clock no Cristal definida em 4Mhz

// Define os pinos de entradas
#define TAMPA_SUPERIOR      PORTBbits.RB0                       // Chave para a tampa superior
#define S_TAMPA_SUPERIOR    PORTBbits.RB1                       // Sensor para a tampa superior fechada
#define TAMPA_INFERIOR      PORTBbits.RB2                       // Botão para a tampa inferior
#define S_TAMPA_INFERIOR    PORTBbits.RB3                       // Sensor para a tampa inferior fechada
#define S_VASILHA           PORTBbits.RB4                       // Sensor de nível da vasilha
#define INICIAR_PROCESSO    PORTBbits.RB5                       // Switch para iniciar o processo de contagem

#define SA                  PORTBbits.RB6                       // Tampa superior aberta
#define SF                  PORTBbits.RB7                       // Tampa superior fechada

#define IA                  PORTDbits.RD0                       // Tampa infperior aberta
#define IF                  PORTDbits.RD1                       // Tampa inferior fechada

#define Alarme              PORTEbits.RE1                       // Buzzer

// Função de inicialização
void inicializar()
{
    // Inicialização das portas
    TRISA = 0xFF;                                               // Configura os pinos do PORTA Como entrada - Conversor A/D
    TRISB = 0x3F;                                               // Configura os pinos do PORTB como entrada de 0 à 5 e como saída de 6 à 7
    TRISC = 0x00;                                               // Configura os pinos do PORTC como saída - Motores de Passo
    TRISD = 0x00;                                               // Configura os pinos do PORTD como saída - LCD
    TRISE = 0x00;                                               // Configura os pinos do PORTC como saída - Alarme
    OPTION_REG = 0b00111111;                                    // Resistores Pull-up ativados e INTEDG sensível a descida em 0 "bit 6"
    
    // Configurações auxiliares
    #pragma config WDTE = OFF                                   // Desabilita o uso do WDT
    #pragma config FOSC = HS                                    // Define uso do clock externo EM 4 OU 20mHZ
    #pragma config PWRTE = ON                                   // Habilita reset ao ligar
    #pragma config BOREN = ON                                   // Habilita o reset por Brown-out 

    // Configuração do conversor analógico/digital
    // Ficará somente com o pino AN0 como entrada analógica. (TABELA NO DATASHEET)
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;

    // Define o clock de conversão
    // Confirmando default Fosc/2
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 0;

    ADCON1bits.ADFM = 0   ;                                     // Default é 0. Pra mostrar que pegará os dados em 8 bits 
                                                                // no ADRESH, pois está justifica à esquerda
                                                                // Passando pra 1 pode pegar os dados em 10 bits 
                                                                // usando os dois registradores ADRESHL justificado à direita

    // Inicializa registradores do AD
    ADRESL = 0x00;                                              // Inicializar valor analógico com 0
    ADRESH = 0x00;

    ADCON0bits.ADON = 1;                                        //Liga o conversor A/D
    
    // Configurações das interrupções    
    INTCONbits.GIE = 1;                                         // Habilita a INT global
    INTCONbits.PEIE = 1;                                        // Habilita a INT dos periféricos
    INTCONbits.INTE = 1;                                        // Habiliata a INT externa do RB0/INT
    PIE1bits.TMR1IE = 1;                                        // Habilita a INT do timer 1
    INTCONbits.TMR0IE = 1;                                      // Habilita a int do timer 0
    
    // Configuração do timer 1
    T1CONbits.TMR1CS = 0;                                       // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                                      // Bit para configurar pré-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                                      // Bit para configurar pré-escala como 1:8
    
    TMR1L = 0xDC;                                               // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                                               // 3036. Quando estourar contou 62500, passou 0,5s
    
    /*
    // Configurações do timer 0
    OPTION_REGbits.T0CS = 0;                                    // Define o timer 0 como contador interno 
    OPTION_REGbits.T0SE = 0;                                    // Vai contar na borda de 1 para 0, esse é o default
    
    OPTION_REGbits.PSA = 1;                                     // defini pré-escalar para WDT, por reset já fica assim
    
    // Configura a taxa de temporização do WDT para 1:128 - Timer 0 conta 1:1
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    TMR0 = 246;                                                 // Inicializar o contador em 246, vai contar 10, 256 estoura
    
    CLRWDT();                                                   // Reseta a contagem do WDT para não resetar
    */
 
    // Inicializações iniciais
    SA = 0;                                                     // Tampa superior aberta desaativado
    SF = 1;                                                     // Tampa superior fechada ativado
    IA = 0;                                                     // Tampa inferior aberta desativado
    IF = 1;                                                     // Tampa inferior fechada ativado
    
    PORTC = 0;                                                  // Motores desligados em posição inicial (tampa fechada)
    
    Lcd_Init();                                                 // Inicialização do LCD 
};

// Variáveis Auxiliares para o Sensor Analógico e LCD
int valorAnalogico = 0;                                         // Variável que receberá o valor analógico do potênciometro
int valorEmCentimetro = 0;                                      // Variável que receberá o valor convertido para centímetro - Recipiente de 80 cm
int k = 3;                                                      // Constante de conversão do valor analógico para centímetro
int posicaoDaComida = 0;                                        // Variável para converter o valor da distância no valor dad posição em que se encontra a comida
char buffer[20];                                                // Variável para a função sprintf do LCD

// Variáveis Auxiliares para o Timer1
int contadorPosicao = 0;                                        // Váriavel para mediar a temporização dos dados que aparececrão no LCD
//int contadorVerificaDispenser = 0;                              // Variável para mediar a temporização de verificar o container após iniciar o processo

// Verificação dos Sensores das Tampas
void verificaSensorInferior()
{
    if (S_TAMPA_INFERIOR == 0 && C5 == 1)
    {
        IF = 1;
        IA = 0;
    }
    else if (S_TAMPA_INFERIOR == 1 && C5 == 0)
    {
        IF = 0;
        IA = 1;
    }
}

void verificaSensorSuperior()
{
    if (S_TAMPA_SUPERIOR == 0 && C1 == 1)
    {
        SF = 1;
        SA = 0;
    }
    else if (S_TAMPA_SUPERIOR == 1 && C1 == 0)
    {
        SF = 0;
        SA = 1;
    }
}

// Pega os valores em centimetros, converte para posição e mostra no LCD
void pegaValorEmCentimetro()
{
    //Seleciona canal de entrada 0 como entrada analógica
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
        
    ADCON0bits.GO = 1;                                          // Converte
    __delay_us(10);                                             // Tempo de conversão
    valorAnalogico = ADRESH;                                    // Passa valores convertido do registrador para a variável
    valorEmCentimetro = valorAnalogico/k;                       // Conversão do valor analógico para centimetros
    posicaoDaComida = 85 - valorEmCentimetro;                   // Posição em cm em que a comida se encontra no recipiente de baixo para cima
        
    // Mostra uma string e o conteúdo de uma variável
    Lcd_Clear();                                                // Limpa o LCD
    sprintf(buffer, "Comida = %d ", posicaoDaComida);           // Armazena em buffer o conteúdo da variável valorEmCentímetro formatado com duas casas
    
    if (posicaoDaComida >= 60)
    {
        Lcd_Set_Cursor(1,1);                                   // Posiciona o cursor do LCD na 1° linha e 1° coluna   
        Lcd_Write_String(buffer);                              // Escreve o conteúdo de buffer no LCD
        Lcd_Set_Cursor(1,12);                                  // Posiciona o cursor do LCD na 1° linha e 12° coluna   
        Lcd_Write_String(" cm");                               // Escreve a unidade
        Lcd_Set_Cursor(2,1);                                   // Posiciona o cursor do LCD na 2° linha e 1° coluna   
        Lcd_Write_String("Dispenser-Cheio");                   // Escreve que o dispenser está cheio
        __delay_ms(500);
    }
    else if (posicaoDaComida < 60 && posicaoDaComida >= 10)
    {
        Lcd_Set_Cursor(1,1);                                   // Posiciona o cursor do LCD na 1° linha e 1° coluna   
        Lcd_Write_String(buffer);                              // Escreve o conteúdo de buffer no LCD
        Lcd_Set_Cursor(1,12);                                  // Posiciona o cursor do LCD na 1° linha e 12° coluna   
        Lcd_Write_String(" cm");                               // Escreve a unidade
        Lcd_Set_Cursor(2,1);                                   // Posiciona o cursor do LCD na 2° linha e 1° coluna   
        Lcd_Write_String("Dispenser-Metade");                  // Escreve que o dispenser está na metade
        __delay_ms(500);
    }
    else
    {
        Lcd_Set_Cursor(1,1);                                   // Posiciona o cursor do LCD na 1° linha e 1° coluna   
        Lcd_Write_String(buffer);                              // Escreve o conteúdo de buffer no LCD
        Lcd_Set_Cursor(1,11);                                  // Posiciona o cursor do LCD na 1° linha e 11° coluna   
        Lcd_Write_String(" cm");                               // Escreve a unidade
        Lcd_Set_Cursor(2,1);                                   // Posiciona o cursor do LCD na 2° linha e 1° coluna   
        Lcd_Write_String("Dispenser-Vazio");                   // Escreve que o dispenser está vazio
        __delay_ms(500);
    }
    
}

// Rotina de Interrupção
void __interrupt() TrataInt(void)
{
    if(INTF)
    {    
        INTCONbits.INTF = 0; //Interrupcao ta ativa
                  
    }
    
    /*
    if (TMR0IF)                                                 // Foi a interrupção externa que chamou a int?
    {
        INTCONbits.TMR0IF = 0;                                  // Reseta o flag da interrupção
        TMR0 = 246;                                             // Reinicializa a contagem
        
        // Tratamento da interrupção
        contadorPosicao++;
        if (contadorPosicao == 10)                              // Faz a acontagem 20 vezes. Equivalente a 10 segundos
        {
            pegaValorEmCentimetro();                            // Mostra a situação no LCD
            contadorPosicao = 0;                                // Reseta o contador do temporizador
        }
    }
    */
    return;
};

#endif	/* HEADER_H */
