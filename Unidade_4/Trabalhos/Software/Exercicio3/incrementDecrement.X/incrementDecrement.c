/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício 3 - Incrementa / Decrementa
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Ao apertar o botão de incremento a variável é incrementada
* Ao apertar o botão de decremento a variável é decrementada
 * Se a variável for igual a 0, ascende o Led 0
 * Se a variável for igual a 10, ascende o Led 10
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    int value = 0;
    
    while (1)
    {
        increment = PORTBbits.RB0;
        decrement = PORTBbits.RB7;
        
        if (increment == 0 && decrement == 1)               // O botão de incremento está pressionado e o de decrementão não?
        {
            incrementValue(&value);                         // Sim - Incrementa o valor por referência (verificar função no header.h)
        }
        else if (increment == 1 && decrement == 0)          // O botão de incremento não está pressionado e o de decrementão sim?
        {
            value = decrementValue(value);                  // Sim - Decrementa o valor por passagem de parâmetros (verificar função no header.h)
        }
        
        // Verificação do valor
        if (value == 0)                                     // A variável value é igual a 0?
        {
            Led0 = 1;                                       // Sim - Ascende o Led 0
        }
        else
        {
            Led0 = 0;                                       // Não - Apaga o Led 0
        }
        
        if (value == 10)                                    // A variável value é igual a 10?
        {
            Led10 = 1;                                      // Sim - Ascende o Led 10
        }
        else
        {
            Led10 = 0;                                      // Não - Apaga o Led 0
        }
    }
}
