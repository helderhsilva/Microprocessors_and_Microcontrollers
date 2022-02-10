/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício 5 - Mixer Interruption (Misturador de Fábrica de tinta)
* Autor: Helder Henrique da Silva - 20250326
* Create File: 10/02/2022
* Funcionalidade:
* Inicialização -> Tanques A e B fechados = Válvulas Y1 e Y2 fehadas
* Tanque C aberto = Válvula Y3 aberta
* Sistema inerte até o botão de ligar ser acionado:
 * Quando acionado, Y1 e Y2 são abertas e Y3 fechado até que o sensor de nível (SN) seja acionado
 * Após SN ser acionado, Y1 e Y2 são fechadas e M1 é ligado por 10 segundos
 * Após os 10 segundos, Y3 abre e espera novo ciclo
* Quando apertado o botão de interrupção, todo o processo para e reinicia 
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
         flag = 0;                                      // Verificador de interrupção -> 0 = não entrou na interrupção
         
         // Inicialização - Válvulas 1 e 2 fechadas, válvula 3 aberta e motor desligado
         Y1 = 0;
         Y2 = 0;
         Y3 = 1;
         M1 = 0;
         
         aux = 0;                                       // Verificador de processo encerrado -> 0 = processo pronto para começar
         while (aux != 2 && flag == 0)
         {
             if (verifyStart() == 1 && verifySN() == 0 && aux == 0)
             {
                 Y3 = 0;
                 __delay_ms(1000);
                 
                 Y1 = 1;
                 Y2 = 1;
                 
                 aux = 1;
             }
             
             if (verifyStart() == 0 && verifySN() == 1 && aux == 1)
             {
                 Y1 = 0;
                 Y2 = 0;
                 
                 M1 = 1;
                 __delay_ms(10000);
                 
                 aux = 2;
             }
         }
    }
}
