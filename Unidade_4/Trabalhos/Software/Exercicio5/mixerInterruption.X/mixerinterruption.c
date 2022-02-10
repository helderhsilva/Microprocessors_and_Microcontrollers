/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio 5 - Mixer Interruption (Misturador de F�brica de tinta)
* Autor: Helder Henrique da Silva - 20250326
* Create File: 10/02/2022
* Funcionalidade:
* Inicializa��o -> Tanques A e B fechados = V�lvulas Y1 e Y2 fehadas
* Tanque C aberto = V�lvula Y3 aberta
* Sistema inerte at� o bot�o de ligar ser acionado:
 * Quando acionado, Y1 e Y2 s�o abertas e Y3 fechado at� que o sensor de n�vel (SN) seja acionado
 * Ap�s SN ser acionado, Y1 e Y2 s�o fechadas e M1 � ligado por 10 segundos
 * Ap�s os 10 segundos, Y3 abre e espera novo ciclo
* Quando apertado o bot�o de interrup��o, todo o processo para e reinicia 
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
         flag = 0;                                      // Verificador de interrup��o -> 0 = n�o entrou na interrup��o
         
         // Inicializa��o - V�lvulas 1 e 2 fechadas, v�lvula 3 aberta e motor desligado
         Y1 = 0;
         Y2 = 0;
         Y3 = 1;
         M1 = 0;
         
         aux = 0;                                       // Verificador de processo encerrado -> 0 = processo pronto para come�ar
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
