/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 02/03/2022
* Funcionalidade:
*
*/

#include "header.h"

void main(void)
{
    inicializar();                                                      // Inicialização Full
  
    while (1)
    {
        //CLRWDT();
        while (recarga == 1 && TAMPA_SUPERIOR == 1)
        {            
            if (S_TAMPA_SUPERIOR == 1)
            {
                fechaTampaSuperior();
                recarga = 0;
            }
        }
        
        verificaSensorSuperior();        
        verificaSensorInferior();
        
        if (TAMPA_INFERIOR == 0 && S_VASILHA == 1)                      // Se o botão da taampa inferior for pressionado e a vasilha não estiver cheia
        {
            if (S_TAMPA_INFERIOR == 0)                                  // Se o sensor da tampa inferior fechada estiver ativado
            {
                abreTampaInferior();                                    // Abre a tampa inferior do dispenser em 45°
            }
        }

        if (S_VASILHA == 0)                                             // Se o sensor de nível da vasilha indicar que ela está cheia
        { 
            if (S_TAMPA_INFERIOR == 1)                                  // Se o sensor da tampa inferior fechada estiver desativado
            {
                fechaTampaInferior();                                   // fecha a tampa inferior do dispenser em 45°
            }
        }

        /*while (INICIAR_PROCESSO == 0)                                 // Enquanto a chave de iniciar processo estiver ativa
        {

        }*/  
    }
}