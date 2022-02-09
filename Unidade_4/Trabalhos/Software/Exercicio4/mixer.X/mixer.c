/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio 4 - Mixer (Misturador de F�brica de tinta)
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Inicializa��o -> Tanques A e B fechados = V�lvulas Y1 e Y2 fehadas
* Tanque C aberto = V�lvula Y3 aberta
* Sistema inerte at� o bot�o de ligar ser acionado:
 * Quando acionado, Y1 e Y2 s�o abertas e Y3 fechado at� que o sensor de n�vel (SN) seja acionado
 * Ap�s SN ser acionado, Y1 e Y2 s�o fechadas e M1 � ligado por 10 segundos
 * Ap�s os 10 segundos, Y3 abre e espera novo ciclo
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        // Inicializa��o das v�vulas em modo standby
        Y1 = 0;
        Y2 = 0;
        Y3 = 1;
        
        if (verifyStart() == 1)                             // Verifica se o bot�o liga foi pressionado (conferir no header.h)
        {
            // Fecha Y1 e Y2 e abre Y3
            Y1 = 1;
            Y2 = 1;
            Y3 = 0;
            
            while (Y1 == 1 && Y2 == 1 && Y3 == 0)           // Enquanto o tanque estiver sendo enxido
            {
                if (verifySN() == 1)                        // Verifica se o sensor de n�vel foi ativado (conferir no header.h)
                {
                    // Fecha Y1 e Y2 e liga o misturador
                    Y1 = 0;
                    Y2 = 0;
                    M1 = 1;
                    __delay_ms(10000);                      // Misturador funciona por 10s
                    M1 = 0;                                 // Desliga o misturador e volta para standby
                }
            }
        }  
    }
}
