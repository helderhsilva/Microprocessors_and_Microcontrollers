/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício 4 - Mixer (Misturador de Fábrica de tinta)
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Inicialização -> Tanques A e B fechados = Válvulas Y1 e Y2 fehadas
* Tanque C aberto = Válvula Y3 aberta
* Sistema inerte até o botão de ligar ser acionado:
 * Quando acionado, Y1 e Y2 são abertas e Y3 fechado até que o sensor de nível (SN) seja acionado
 * Após SN ser acionado, Y1 e Y2 são fechadas e M1 é ligado por 10 segundos
 * Após os 10 segundos, Y3 abre e espera novo ciclo
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        // Inicialização das vávulas em modo standby
        Y1 = 0;
        Y2 = 0;
        Y3 = 1;
        
        if (verifyStart() == 1)                             // Verifica se o botão liga foi pressionado (conferir no header.h)
        {
            // Fecha Y1 e Y2 e abre Y3
            Y1 = 1;
            Y2 = 1;
            Y3 = 0;
            
            while (Y1 == 1 && Y2 == 1 && Y3 == 0)           // Enquanto o tanque estiver sendo enxido
            {
                if (verifySN() == 1)                        // Verifica se o sensor de nível foi ativado (conferir no header.h)
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
