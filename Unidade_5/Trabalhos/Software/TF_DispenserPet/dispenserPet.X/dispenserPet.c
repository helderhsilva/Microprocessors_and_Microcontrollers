/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 02/03/2022
* Funcionalidade:
*1. O dispenser, inicialmente, vem v�zio e com suas tampas (inferior e superior) fechadas;
*1.1. O LCD � inicializado e aguarda a contagem do timer 0 e sensor anal�gico;
*1.2. O sensor anal�gico pega a posi��o em cm em que a ra��o se encontra no dispenser;
*1.3. O timer 0 atualiza essa posi��o e joga para o LCD;
*
*2. Em cada tampa h� um sensor que indica se a tampa est� fechada ou n�o;
*2.1. Quando as tampas est�o fechadas, um led vermelho � indicado;
*2.2. Quando as tampas est�o abertas, um led verde � indicado;
*
*3. Para carregar o dispenser (inicialmente v�zio), deve ser acionado a chave da tampa superior (RB0/INT);
*3.1. Quando acionado a chave, o motor de passo gira +90� e o sensor da tampa superior deve ser desativado (tampa aberta);
*3.2. Quando a chave volta ao estado inicial, o motor de passo gira -90� e o sensor da tampa superior � ativado (tampa fechada);
*
*4. Uma vez que o dispenser se encontra cheio (ou com ra��o acima de um certo n�vel), a vasilha � enchida pela primeira vez;
*4.1. � verificado se � o primeiro enchimento ap�s carregar o dispenser;
*4.2. � verificado se a vasilha est� vazia e se o dispenser tem ra��o;
*4.3. Verifica se a tampa inferior est� fechada;
*4.4. Abre a tampa inferior, o motor de passo gira +45� e o sensor da tampa inferior deve ser desativado (tampa aberta);
*
*5. Se o sensor da vasilha indicar que ela est� cheia;
*5.1. Verifica se a tampa inferior est� aberta;
*5.2. Fecha a tampa inferior, o motor de passo gira -45� e o sensor da tampa inferior � ativado (tampa fechada);
*
*6. O timer 1 � iniciado ao ligar o microcontrolador (funcionamento de 8 em 8 horas para o comercial);
*6.1. A cada 20 segundos ele verifica se a vasilha est� v�zia e se tem ra��o no dispenser;
*6.2. Abre a tampa inferior, o motor de passo gira +45� e o sensor da tampa inferior deve ser desativado (tampa aberta);
*
*7. Se o dispenser estiver ficando v�zio e n�o for feita a recarga;
*7.1. O processo � bloqueado at� que o dispenser seja carregado.
*/

#include "header.h"

void main(void)
{
    inicializar();                                                      // Inicializa��o Full
    
    // Inicializa��o do lcd - Modo de espera at� que o timer 0 comece a funcionar
    Lcd_Set_Cursor(1,1);  
    Lcd_Write_String("Carregando");
    Lcd_Set_Cursor(2,1);  
    Lcd_Write_String("Aguarde");
    __delay_ms(500);
  
    while (1)
    {
        CLRWDT();
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Fechar a tampa superior ap�s sair da sua interrup��o
        while (recarga == 1 && TAMPA_SUPERIOR == 1)                     // Houve a recarga do dispenser e a tampa superior est� aberta?
        {
            CLRWDT();
            if (S_TAMPA_SUPERIOR == 1)                                  // Se o sensor da tampa superior estiver aberta
            {
                fechaTampaSuperior();                                   // Fecha a tampa superior
                recarga = 0;                                            // Reseta a vari�vel de recarga
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Verifica��o dos sensores das tampas
        verificaSensorSuperior();        
        verificaSensorInferior();
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Abrir a tampa inferior manualmente atrav�s de um bot�o
        if (TAMPA_INFERIOR == 0 && S_VASILHA == 1)                      // Se o bot�o da tampa inferior for pressionado e a vasilha n�o estiver cheia
        {
            CLRWDT();
            if (S_TAMPA_INFERIOR == 0)                                  // Se o sensor da tampa inferior fechada estiver ativado
            {
                abreTampaInferior();                                    // Abre a tampa inferior do dispenser em 45�
            }
        }

        //--------------------------------------------------------------------------------------------------------------------------
        // Fecha a tampa inferior, toda vez que a vasilha estiver cheia
        if (S_VASILHA == 0)                                             // Se o sensor de n�vel da vasilha indicar que ela est� cheia
        { 
            CLRWDT();
            if (S_TAMPA_INFERIOR == 1)                                  // Se o sensor da tampa inferior fechada estiver desativado
            {
                fechaTampaInferior();                                   // Fecha a tampa inferior do dispenser em 45�
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Encher a vasilha pela primeira vez automaticamente caso dispenser n�o esteja v�zio
        if (primeiroEnchimento == 0)                                    // Se o primeiro enchimento da vasilha n�o ocorreu
        {
            if (S_VASILHA == 1 && posicaoDaComida >= 10)                // Se a vasilha est� vazia e e tem comida no dispenser
            {
               CLRWDT();
               if (S_TAMPA_INFERIOR == 0)                               // Se o sensor da tampa inferior fechada estiver ativado
                {
                    abreTampaInferior();                                // Abre a tampa inferior do dispenser em 45�
                    primeiroEnchimento = 1;                             // Indica que foi preenchido pela primeira vez.
                } 
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Bloqueio por dispenser totalmente vazio - Reset do primeiro enchimento ap�s recarga
        while (posicaoDaComida < 10 && recarga != 1)
        {
            CLRWDT();
            primeiroEnchimento = 0;
        }  
    }
}