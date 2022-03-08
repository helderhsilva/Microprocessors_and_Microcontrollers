/* 
 * File:   header.h
 * Author: Helder Henrique da Silva e Lucas Floriano Garcia
 * 
 * Created on 02 de Mar�o de 2022, 18:00
 */

#ifndef HEADER_H
#define	HEADER_H

//--------------------------------------------------------------------------------------------------------------------------
#include <xc.h>                                                         // Include Biblioteca padr�o do compilador
#include <stdio.h>                                                      // Include Biblioteca padr�o "C"
#include <pic16f877a.h>                                                 // Include Biblioteca Standart padr�o do Chip que ser� usado
#include "lcd.h"                                                        // Include e Define dos pinos do LCD e fun��es de inicializa��o
#include "stepper.h"                                                    // Include e Define dos pinos para os motores de passo e suas fun��es auxiliares

#define _XTAL_FREQ 4000000                                              // Frequ�ncia do clock no Cristal definida em 4Mhz

//--------------------------------------------------------------------------------------------------------------------------
// Define os pinos de entradas
#define TAMPA_SUPERIOR      PORTBbits.RB0                               // Chave para a tampa superior
#define S_TAMPA_SUPERIOR    PORTBbits.RB1                               // Sensor para a tampa superior fechada
#define TAMPA_INFERIOR      PORTBbits.RB2                               // Bot�o para a tampa inferior
#define S_TAMPA_INFERIOR    PORTBbits.RB3                               // Sensor para a tampa inferior fechada
#define S_VASILHA           PORTBbits.RB4                               // Sensor de n�vel da vasilha

#define SA                  PORTBbits.RB6                               // Tampa superior aberta
#define SF                  PORTBbits.RB7                               // Tampa superior fechada

#define IA                  PORTDbits.RD0                               // Tampa infperior aberta
#define IF                  PORTDbits.RD1                               // Tampa inferior fechada

// Fun��o de inicializa��o
void inicializar()
{
    //--------------------------------------------------------------------------------------------------------------------------
    // Inicializa��o das portas
    TRISA = 0xFF;                                                       // Configura os pinos do PORTA Como entrada - Conversor A/D
    TRISB = 0x3F;                                                       // Configura os pinos do PORTB como entrada de 0 � 5 e como sa�da de 6 � 7
    TRISC = 0x00;                                                       // Configura os pinos do PORTC como sa�da - Motores de Passo
    TRISD = 0x00;                                                       // Configura os pinos do PORTD como sa�da - LCD
    OPTION_REG = 0b00111111;                                            // Resistores Pull-up ativados e INTEDG sens�vel a descida em 0 "bit 6"
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Bits de Configura��o
    #pragma config WDTE = ON                                            // Habilita o uso do WDT
    #pragma config FOSC = HS                                            // Define uso do clock externo EM 4 OU 20mHZ
    #pragma config PWRTE = ON                                           // Habilita reset ao ligar
    #pragma config BOREN = ON                                           // Habilita o reset por Brown-out 

    //--------------------------------------------------------------------------------------------------------------------------
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

    ADCON1bits.ADFM = 0   ;                                             // Default � 0. Pra mostrar que pegar� os dados em 8 bits 
                                                                        // no ADRESH, pois est� justifica � esquerda
                                                                        // Passando pra 1 pode pegar os dados em 10 bits 
                                                                        // usando os dois registradores ADRESHL justificado � direita

    // Inicializa registradores do AD
    ADRESL = 0x00;                                                      // Inicializar valor anal�gico com 0
    ADRESH = 0x00;

    ADCON0bits.ADON = 1;                                                //Liga o conversor A/D
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configura��es das interrup��es    
    INTCONbits.GIE = 1;                                                 // Habilita a INT global
    INTCONbits.PEIE = 1;                                                // Habilita a INT dos perif�ricos
    INTCONbits.INTE = 1;                                                // Habiliata a INT externa do RB0/INT
    PIE1bits.TMR1IE = 1;                                                // Habilita a INT do timer 1
    INTCONbits.TMR0IE = 1;                                              // Habilita a int do timer 0
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configura��o do timer 1
    T1CONbits.TMR1CS = 0;                                               // Define timer 1 como temporizador (Fosc/4)
    T1CONbits.T1CKPS0 = 1;                                              // Bit para configurar pr�-escala como 1:8
    T1CONbits.T1CKPS1 = 1;                                              // Bit para configurar pr�-escala como 1:8
    
    TMR1L = 0xDC;                                                       // Carga do valor inicial no contador (65536 - 62500)
    TMR1H = 0x0B;                                                       // 3036. Quando estourar contou 62500, passou 0,5s
    
    T1CONbits.TMR1ON = 1;                                               //Liga o timer1
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Configura��es do timer 0
    OPTION_REGbits.T0CS = 0;                                            // Define o timer 0 como contador interno 
    OPTION_REGbits.T0SE = 0;                                            // Vai contar na borda de 1 para 0, esse � o default
    
    OPTION_REGbits.PSA = 1;                                             // defini pr�-escalar para WDT, por reset j� fica assim
    
    // Configura a taxa de temporiza��o do WDT para 1:64 - Timer 0 conta 1:1
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    TMR0 = 0;                                                           // Inicializar o contador em 0, vai contar 256, 256 estoura
     
    //--------------------------------------------------------------------------------------------------------------------------
    // Inicializa��es iniciais
    SA = 1;                                                             // Tampa superior aberta desaativado
    SF = 0;                                                             // Tampa superior fechada ativado
    IA = 1;                                                             // Tampa inferior aberta desativado
    IF = 0;                                                             // Tampa inferior fechada ativado
    
    PORTC = 0b00110011;                                                 // Motores desligados em posi��o inicial (tampa fechada)
    
    Lcd_Init();                                                         // Inicializa��o do LCD
    CLRWDT();                                                           // Reseta a contagem do WDT para n�o resetar
};

//--------------------------------------------------------------------------------------------------------------------------
// Vari�veis Auxiliares para o Sensor Anal�gico e LCD
int valorAnalogico = 0;                                                 // Vari�vel que receber� o valor anal�gico do pot�nciometro
int valorEmCentimetro = 0;                                              // Vari�vel que receber� o valor convertido para cent�metro - Dispenser de 85 cm
int k = 3;                                                              // Constante de convers�o do valor anal�gico para cent�metro
int posicaoDaComida = 0;                                                // Vari�vel para converter o valor obtido na posi��o em que se encontra a comida
char buffer[20];                                                        // Vari�vel para a fun��o sprintf do LCD

//--------------------------------------------------------------------------------------------------------------------------
// Vari�veis Auxiliares para o Timer0
int contadorPosicao = 0;                                                // Vari�vel para mediar a temporiza��o dos dados que aparececr�o no LCD

//--------------------------------------------------------------------------------------------------------------------------
// Vari�vel Auxiliar para o RB0
__bit recarga = 0;                                                      // Vari�vel auxiliar para representaa��o da recarga do dispenser

//--------------------------------------------------------------------------------------------------------------------------
// Vari�vel Auxiliar para o Processo de reabastecimento autom�tico Timer 1
__bit primeiroEnchimento = 0;                                           // V�ri�vel auxiliar para o primeiro enchimento autom�tico da vasilha
int contadorEnchimento = 0;                                             // Vari�vel para temporizador - encher a vasilha em per�odos

//--------------------------------------------------------------------------------------------------------------------------
// Verifica��o dos Sensores das Tampas
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
// Pega os valores em centimetros, converte para posi��o para mostrar no LCD
void pegaValorEmCentimetro()
{
    CLRWDT();
    //Seleciona canal de entrada 0 como entrada anal�gica
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
        
    ADCON0bits.GO = 1;                                                  // Converte
    __delay_us(10);                                                     // Tempo de convers�o
    valorAnalogico = ADRESH;                                            // Passa valores convertido do registrador para a vari�vel
    valorEmCentimetro = valorAnalogico/k;                               // Convers�o do valor anal�gico para centimetros
    posicaoDaComida = 85 - valorEmCentimetro;                           // Posi��o em cm em que a comida se encontra no recipiente de baixo para cima
}

//--------------------------------------------------------------------------------------------------------------------------
// Rotina de Interrup��o
void __interrupt() TrataInt(void)
{
    //--------------------------------------------------------------------------------------------------------------------------
    // Interrup��o do RB0 = Abrir a tampa superior para recarregar o dispenser
    if(INTF)
    {    
        INTCONbits.INTF = 0;                                            // Reseta a flag da interrup��o
        
        while (TAMPA_SUPERIOR != 1)                                     // Enquanto a tampa superior estiver aberta
        {
            CLRWDT();
            verificaSensorSuperior();
           
            if (S_TAMPA_SUPERIOR == 0)                                  // Se o sensor da tampa superior fechada estiver ativado
            {
                abreTampaSuperior();                                    // Abre a tampa superior
                
                // Mensagem para aguardar enquanto o dispenser � recarregado
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
    // Interrup��o do Timer 0 = Contagem e atualiza��o do status do dispenser
    if (TMR0IF)
    {
        CLRWDT();
        INTCONbits.TMR0IF = 0;                                          // Reseta o flag da interrup��o
        TMR0 = 0;                                                       // Reinicializa a contagem
                        
        // Tratamento da interrup��o
        contadorPosicao++;
        if (contadorPosicao == 10000)                                   // Equivalente a 5 segundos
        {
            pegaValorEmCentimetro();                                    // Obt�m o valor da posi��o da comida no dispenser
            
            //--------------------------------------------------------------------------------------------------------------------------
            Lcd_Clear();                                                // Limpa o LCD
            sprintf(buffer, "Comida = %d ", posicaoDaComida);           // Armazena em buffer o conte�do da vari�vel posicaoDaComida

            if (posicaoDaComida >= 60)                                  // Se o dispenser estiver com comida igual ou acima de 60 cm
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conte�do de buffer no LCD
                Lcd_Set_Cursor(1,12);  
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Dispenser-Cheio");                    // Escreve que o dispenser est� cheio
                __delay_ms(500);
            }
            else if (posicaoDaComida < 60 && posicaoDaComida >= 10)     // Se o dispenser estiver com comida entre 10 e 60 cm
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conte�do de buffer no LCD
                Lcd_Set_Cursor(1,12);  
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);   
                Lcd_Write_String("Dispenser-Metade");                   // Escreve que o dispenser est� na metade
                __delay_ms(500);
            }
            else if (posicaoDaComida == 0)                              // Se o dispenser estiver totalmente v�zio
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1); 
                Lcd_Write_String(buffer);                               // Escreve o conte�do de buffer no LCD
                Lcd_Set_Cursor(1,11);   
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1); 
                Lcd_Write_String("Recarregar");                         // Escreve que o dispenser est� vazio
                __delay_ms(500);
            }
            else                                                        // Se o dispenser estiver abaixo de 10 cm, mas n�o totalmente v�zio
            {
                CLRWDT();
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(buffer);                               // Escreve o conte�do de buffer no LCD
                Lcd_Set_Cursor(1,11); 
                Lcd_Write_String(" cm");                                // Escreve a unidade
                Lcd_Set_Cursor(2,1);  
                Lcd_Write_String("Dispenser-Vazio");                    // Escreve que o dispenser est� vazio
                __delay_ms(500);
            }
            //--------------------------------------------------------------------------------------------------------------------------
            
            contadorPosicao = 0;                                        // Reseta o contador do temporizador  
        }
    }
    
    //--------------------------------------------------------------------------------------------------------------------------
    // Interrup��o do Timer 1 = Enchimento autom�tico da vasilha de per�odo em per�odo
    if (TMR1IF)
    {
        CLRWDT();
        PIR1bits.TMR1IF = 0;                                            // Reseta o flag da interrup��o
        TMR1L = 0xDC;                                                   // Reinicia a contagem com 3036
        TMR1H = 0x0B;
        
        // Tratamento da interrup��o
        contadorEnchimento++;
        if (contadorEnchimento == 20)                                   // Equivalente a 10 segundos (Para 8hrs utilizar 57600)
        {
            pegaValorEmCentimetro();                                    // Obt�m o valor da posi��o da comida no dispenser
            
            if (S_VASILHA == 1 && posicaoDaComida >= 10)                // Se a vasilha est� vazia e e tem comida no dispenser
            {
               CLRWDT();
               if (S_TAMPA_INFERIOR == 0)                               // Se o sensor da tampa inferior fechada estiver ativado
                {
                    abreTampaInferior();                                // Abre a tampa inferior do dispenser em 45�
                } 
            }
            contadorEnchimento = 0;                                     // Reseta o contador
        }
    }
    return;
};

#endif	/* HEADER_H */
