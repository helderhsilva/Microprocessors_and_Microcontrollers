/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 02/03/2022
* Funcionalidade:
*1. O dispenser, inicialmente, vem vázio e com suas tampas (inferior e superior) fechadas;
*1.1. O LCD é inicializado e aguarda a contagem do timer 0 e sensor analógico;
*1.2. O sensor analógico pega a posição em cm em que a ração se encontra no dispenser;
*1.3. O timer 0 atualiza essa posição e joga para o LCD;
*
*2. Em cada tampa há um sensor que indica se a tampa está fechada ou não;
*2.1. Quando as tampas estão fechadas, um led vermelho é indicado;
*2.2. Quando as tampas estão abertas, um led verde é indicado;
*
*3. Para carregar o dispenser (inicialmente vázio), deve ser acionado a chave da tampa superior (RB0/INT);
*3.1. Quando acionado a chave, o motor de passo gira +90° e o sensor da tampa superior deve ser desativado (tampa aberta);
*3.2. Quando a chave volta ao estado inicial, o motor de passo gira -90° e o sensor da tampa superior é ativado (tampa fechada);
*
*4. Uma vez que o dispenser se encontra cheio (ou com ração acima de um certo nível), a vasilha é enchida pela primeira vez;
*4.1. É verificado se é o primeiro enchimento após carregar o dispenser;
*4.2. É verificado se a vasilha está vazia e se o dispenser tem ração;
*4.3. Verifica se a tampa inferior está fechada;
*4.4. Abre a tampa inferior, o motor de passo gira +45° e o sensor da tampa inferior deve ser desativado (tampa aberta);
*
*5. Se o sensor da vasilha indicar que ela está cheia;
*5.1. Verifica se a tampa inferior está aberta;
*5.2. Fecha a tampa inferior, o motor de passo gira -45° e o sensor da tampa inferior é ativado (tampa fechada);
*
*6. O timer 1 é iniciado ao ligar o microcontrolador (funcionamento de 8 em 8 horas para o comercial);
*6.1. A cada 20 segundos ele verifica se a vasilha está vázia e se tem ração no dispenser;
*6.2. Abre a tampa inferior, o motor de passo gira +45° e o sensor da tampa inferior deve ser desativado (tampa aberta);
*
*7. Se o dispenser estiver ficando vázio e não for feita a recarga;
*7.1. O processo é bloqueado até que o dispenser seja carregado.
*/

#include "header.h"

void main(void)
{
    inicializar();                                                      // Inicialização Full
    
    // Inicialização do lcd - Modo de espera até que o timer 0 comece a funcionar
    Lcd_Set_Cursor(1,1);  
    Lcd_Write_String("Carregando");
    Lcd_Set_Cursor(2,1);  
    Lcd_Write_String("Aguarde");
    __delay_ms(500);
  
    while (1)
    {
        CLRWDT();
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Fechar a tampa superior após sair da sua interrupção
        while (recarga == 1 && TAMPA_SUPERIOR == 1)                     // Houve a recarga do dispenser e a tampa superior está aberta?
        {
            CLRWDT();
            if (S_TAMPA_SUPERIOR == 1)                                  // Se o sensor da tampa superior estiver aberta
            {
                fechaTampaSuperior();                                   // Fecha a tampa superior
                recarga = 0;                                            // Reseta a variável de recarga
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Verificação dos sensores das tampas
        verificaSensorSuperior();        
        verificaSensorInferior();
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Abrir a tampa inferior manualmente através de um botão
        if (TAMPA_INFERIOR == 0 && S_VASILHA == 1)                      // Se o botão da tampa inferior for pressionado e a vasilha não estiver cheia
        {
            CLRWDT();
            if (S_TAMPA_INFERIOR == 0)                                  // Se o sensor da tampa inferior fechada estiver ativado
            {
                abreTampaInferior();                                    // Abre a tampa inferior do dispenser em 45°
            }
        }

        //--------------------------------------------------------------------------------------------------------------------------
        // Fecha a tampa inferior, toda vez que a vasilha estiver cheia
        if (S_VASILHA == 0)                                             // Se o sensor de nível da vasilha indicar que ela está cheia
        { 
            CLRWDT();
            if (S_TAMPA_INFERIOR == 1)                                  // Se o sensor da tampa inferior fechada estiver desativado
            {
                fechaTampaInferior();                                   // Fecha a tampa inferior do dispenser em 45°
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Encher a vasilha pela primeira vez automaticamente caso dispenser não esteja vázio
        if (primeiroEnchimento == 0)                                    // Se o primeiro enchimento da vasilha não ocorreu
        {
            if (S_VASILHA == 1 && posicaoDaComida >= 10)                // Se a vasilha está vazia e e tem comida no dispenser
            {
               CLRWDT();
               if (S_TAMPA_INFERIOR == 0)                               // Se o sensor da tampa inferior fechada estiver ativado
                {
                    abreTampaInferior();                                // Abre a tampa inferior do dispenser em 45°
                    primeiroEnchimento = 1;                             // Indica que foi preenchido pela primeira vez.
                } 
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------------------
        // Bloqueio por dispenser totalmente vazio - Reset do primeiro enchimento após recarga
        while (posicaoDaComida < 10 && recarga != 1)
        {
            CLRWDT();
            primeiroEnchimento = 0;
        }  
    }
}