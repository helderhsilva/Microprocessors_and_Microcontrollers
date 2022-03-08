/* 
 * File:   header.h
 * Author: Helder Henrique da Silva e Lucas Floriano Garcia
 * 
 * Created on 02 de Março de 2022, 18:00
 */

#ifndef HEADER_H
#define	HEADER_H

//--------------------------------------------------------------------------------------------------------------------------
#include <xc.h>                                                         // Include Biblioteca padrão do compilador
#include <stdio.h>                                                      // Include Biblioteca padrão "C"
#include <pic16f877a.h>                                                 // Include Biblioteca Standart padrão do Chip que será usado
#include "lcd.h"                                                        // Include e Define dos pinos do LCD e funções de inicialização
#include "stepper.h"                                                    // Include e Define dos pinos para os motores de passo e suas funções auxiliares

#define _XTAL_FREQ 4000000                                              // Frequência do clock no Cristal definida em 4Mhz

//--------------------------------------------------------------------------------------------------------------------------
// Define os pinos de entradas
#define TAMPA_SUPERIOR      PORTBbits.RB0                               // Chave para a tampa superior
#define S_TAMPA_SUPERIOR    PORTBbits.RB1                               // Sensor para a tampa superior fechada
#define TAMPA_INFERIOR      PORTBbits.RB2                               // Botão para a tampa inferior
#define S_TAMPA_INFERIOR    PORTBbits.RB3                               // Sensor para a tampa inferior fechada
#define S_VASILHA           PORTBbits.RB4                               // Sensor de nível da vasilha

#define SA                  PORTBbits.RB6                               // Tampa superior aberta
#define SF                  PORTBbits.RB7                               // Tampa superior fechada

#define IA                  PORTDbits.RD0                               // Tampa infperior aberta
#define IF                  PORTDbits.RD1                               // Tampa inferior fechada

// Função de inicialização
void inicializar()
{
    //--------------------------------------------------------------------------------------------------------------------------
    // Inicialização das portas
    TRISA = 0xFF;                                                       // Configura os pinos do PORTA Como entrada - Conversor A/D
    TRISB = 0x3F;                                                       // Configura os pinos do PORTB como entrada de 0 à 5 e como saída de 6 à 7
    TRISC = 0x00;                                                       // Configura os pinos do PORTC como saída - Motores de Passo
    TRISD = 0x00;                                                       // Configura os pinos do PORTD como saída - LCD
    OPTION_REG = 0b00111111;                                            // Resistores Pull-up ativados e INTEDG sensível a descida em 0 "bit 6"
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Bits de Configuração
    #pragma config WDTE = ON                                            // Habilita o uso do WDT
    #pragma config FOSC = HS                                            // Define uso do clock externo EM 4 OU 20mHZ
    #pragma config PWRTE = ON                                           // Habilita reset ao ligar
    #pragma config BOREN = ON                                           // Habilita o reset por Brown-out 

    //--------------------------------------------------------------------------------------------------------------------------
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

    ADCON1bits.ADFM = 0   ;                                             // Default é 0. Pra mostrar que pegará os dados em 8 bits 
                                                                        // no ADRESH, pois está justifica à esquerda
                                                                        // Passando pra 1 pode pegar os dados em 10 bits 
                                                                        // usando os dois registradores ADRESHL justificado à direita

    // Inicializa registradores do AD
    ADRESL = 0x00;                                                      // Inicializar valor analógico com 0
    ADRESH = 0x00;

    ADCON0bits.ADON = 1;                                                //Liga o conversor A/D
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configurações das interrupções    
    INTCONbits.GIE = 1;                                                 // Habilita a INT global
    INTCONbits.PEIE = 1;                                                // Habilita a INT dos periféricos
    INTCONbits.INTE = 1;                                                // Habiliata a INT externa do RB0/INT
    PIE1bits.TMR1IE = 1;                                                // Habilita a INT do timer 1
    INTCONbits.TMR0IE = 1;                                              // Habilita a int do timer 0
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configuração do timer 1
    T1CONbits.TMR1CS = 0;                                               // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                                              // Bit para configurar pré-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                                              // Bit para configurar pré-escala como 1:8
    
    TMR1L = 0xDC;                                                       // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                                                       // 3036. Quando estourar contou 62500, passou 0,5s
    
    T1CONbits.TMR1ON = 1;                                               //Liga o timer1
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configurações do timer 0
    OPTION_REGbits.T0CS = 0;                                            // Define o timer 0 como contador interno 
    OPTION_REGbits.T0SE = 0;                                            // Vai contar na borda de 1 para 0, esse é o default
    
    OPTION_REGbits.PSA = 1;                                             // defini pré-escalar para WDT, por reset já fica assim
    
    // Configura a taxa de temporização do WDT para 1:64 - Timer 0 conta 1:1
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    TMR0 = 0;                                                           // Inicializar o contador em 0, vai contar 256, 256 estoura
     
    //--------------------------------------------------------------------------------------------------------------------------
    // Inicializações iniciais
    SA = 1;                                                             // Tampa superior aberta desaativado
    SF = 0;                                                             // Tampa superior fechada ativado
    IA = 1;                                                             // Tampa inferior aberta desativado
    IF = 0;                                                             // Tampa inferior fechada ativado
    
    PORTC = 0b00110011;                                                 // Motores desligados em posição inicial (tampa fechada)
    
    Lcd_Init();                                                         // Inicialização do LCD
    CLRWDT();                                                           // Reseta a contagem do WDT para não resetar
};

//--------------------------------------------------------------------------------------------------------------------------
// Variáveis Auxiliares para o Sensor Analógico e LCD
int valorAnalogico = 0;                                                 // Variável que receberá o valor analógico do potênciometro
int valorEmCentimetro = 0;                                              // Variável que receberá o valor convertido para centímetro - Dispenser de 85 cm
int k = 3;                                                              // Constante de conversão do valor analógico para centímetro
int posicaoDaComida = 0;                                                // Variável para converter o valor obtido na posição em que se encontra a comida
char buffer[20];                                                        // Variável para a função sprintf do LCD

//--------------------------------------------------------------------------------------------------------------------------
// Variáveis Auxiliares para o Timer0
int contadorPosicao = 0;                                                // Variável para mediar a temporização dos dados que aparececrão no LCD

//--------------------------------------------------------------------------------------------------------------------------
// Variável Auxiliar para o RB0
__bit recarga = 0;                                                      // Variável auxiliar para representaação da recarga do dispenser

//--------------------------------------------------------------------------------------------------------------------------
// Variável Auxiliar para o Processo de reabastecimento automático Timer 1
__bit primeiroEnchimento = 0;                                           // Váriável auxiliar para o primeiro enchimento automático da vasilha
int contadorEnchimento = 0;                                             // Variável para temporizador - encher a vasilha em períodos

//--------------------------------------------------------------------------------------------------------------------------
// Verificação dos Sensores das Tampas
void verificaSensorInferior()
{
    if (S_TAMPA_INFERIOR == 0 && C5 == 1)
    {
        IF = 0;
        IA = 1;
    }
    else if (S_TAMPA_INFERIOR == 1 && C5 == 0)
    {
        IF = 1;
        IA = 0;
    }
}

void verificaSensorSuperior()
{
    if (S_TAMPA_SUPERIOR == 0 && C1 == 1)
    {
        SF = 0;
        SA = 1;
    }
    else if (S_TAMPA_SUPERIOR == 1 && C1 == 0)
    {
        SF = 1;
        SA = 0;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Pega os valores em centimetros, converte para posição para mostrar no LCD
void pegaValorEmCentimetro()
{
    CLRWDT();
    //Seleciona canal de entrada 0 como entrada analógica
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
        
    ADCON0bits.GO = 1;                                                  // Converte
    __delay_us(10);                                                     // Tempo de conversão
    valorAnalogico = ADRESH;                                            // Passa valores convertido do registrador para a variável
    valorEmCentimetro = valorAnalogico/k;                               // Conversão do valor analógico para centimetros
    posicaoDaComida = 85 - valorEmCentimetro;                           // Posição em cm em que a comida se encontra no recipiente de baixo para cima
}

//--------------------------------------------------------------------------------------------------------------------------
// Rotina de Interrupção
void __interrupt() TrataInt(void)
{
    //--------------------------------------------------------------------------------------------------------------------------
    // Interrupção do RB0 = Abrir a tampa superior para recarregar o dispenser
    if(INTF)
    {    
        INTCONbits.INTF = 0;                                            // Reseta a flag da interrupção
        
        while (TAMPA_SUPERIOR != 1)                                     // Enquanto a tampa superior estiver aberta
        {
            CLRWDT();
            verificaSensorSuperior();
           
            if (S_TAMPA_SUPERIOR == 0)                                  // Se o sensor da tampa superior fechada estiver ativado
            {
                abreTampaSuperior();                                    // Abre a tampa superior
                
                // Mensagem para aguardar enquanto o dispenser é recarregado
                Lcd_Set_Cursor(1,1);   
                Lcd_Write_String("Tampa Sup Aberta");
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Aguarde Recarga");
                CLRWDT();
            }
        }
        recarga = 1;                                                    // Recarga foi feita e a tampa pode ser fechada
    }
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Interrupção do Timer 0 = Contagem e atualização do status do dispenser
    if (TMR0IF)
    {
        CLRWDT();
        INTCONbits.TMR0IF = 0;                                          // Reseta o flag da interrupção
        TMR0 = 0;                                                       // Reinicializa a contagem
                        
        // Tratamento da interrupção
        contadorPosicao++;
        if (contadorPosicao == 10000)                                   // Equivalente a 5 segundos
        {
            pegaValorEmCentimetro();                                    // Obtém o valor da posição da comida no dispenser
            
            //--------------------------------------------------------------------------------------------------------------------------
            Lcd_Clear();                                                // Limpa o LCD
            sprintf(buffer, "Comida = %d ", posicaoDaComida);           // Armazena em buffer o conteúdo da variável posicaoDaComida

            if (posicaoDaComida >= 60)                                  // Se o dispenser estiver com comida igual ou acima de 60 cm
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conteúdo de buffer no LCD
                Lcd_Set_Cursor(1,12);  
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Dispenser-Cheio");                    // Escreve que o dispenser está cheio
                __delay_ms(500);
            }
            else if (posicaoDaComida < 60 && posicaoDaComida >= 10)     // Se o dispenser estiver com comida entre 10 e 60 cm
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conteúdo de buffer no LCD
                Lcd_Set_Cursor(1,12);  
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);   
                Lcd_Write_String("Dispenser-Metade");                   // Escreve que o dispenser está na metade
                __delay_ms(500);
            }
            else if (posicaoDaComida == 0)                              // Se o dispenser estiver totalmente vázio
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1); 
                Lcd_Write_String(buffer);                               // Escreve o conteúdo de buffer no LCD
                Lcd_Set_Cursor(1,11);   
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1); 
                Lcd_Write_String("Recarregar");                         // Escreve que o dispenser está vazio
                __delay_ms(500);
            }
            else                                                        // Se o dispenser estiver abaixo de 10 cm, mas não totalmente vázio
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conteúdo de buffer no LCD
                Lcd_Set_Cursor(1,11); 
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);  
                Lcd_Write_String("Dispenser-Vazio");                    // Escreve que o dispenser está vazio
                __delay_ms(500);
            }
            //--------------------------------------------------------------------------------------------------------------------------
            
            contadorPosicao = 0;                                        // Reseta o contador do temporizador  
        }
    }
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Interrupção do Timer 1 = Enchimento automático da vasilha de período em período
    if (TMR1IF)
    {
        CLRWDT();
        PIR1bits.TMR1IF = 0;                                            // Reseta o flag da interrupção
        TMR1L = 0xDC;                                                   // Reinicia a contagem com 3036
        TMR1H = 0x0B;
        
        // Tratamento da interrupção
        contadorEnchimento++;
        if (contadorEnchimento == 20)                                   // Equivalente a 10 segundos (Para 8hrs utilizar 57600)
        {
            pegaValorEmCentimetro();                                    // Obtém o valor da posição da comida no dispenser
            
            if (S_VASILHA == 1 && posicaoDaComida >= 10)                // Se a vasilha está vazia e e tem comida no dispenser
            {
               CLRWDT();
               if (S_TAMPA_INFERIOR == 0)                               // Se o sensor da tampa inferior fechada estiver ativado
                {
                    abreTampaInferior();                                // Abre a tampa inferior do dispenser em 45°
                } 
            }
            contadorEnchimento = 0;                                     // Reseta o contador
        }
    }
    return;
};

#endif	/* HEADER_H */
