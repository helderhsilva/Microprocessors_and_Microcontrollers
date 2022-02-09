/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio 3 - Incrementa / Decrementa
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Ao apertar o bot�o de incremento a vari�vel � incrementada
* Ao apertar o bot�o de decremento a vari�vel � decrementada
 * Se a vari�vel for igual a 0, ascende o Led 0
 * Se a vari�vel for igual a 10, ascende o Led 10
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    int value = 0;
    
    while (1)
    {
        increment = PORTBbits.RB0;
        decrement = PORTBbits.RB7;
        
        if (increment == 0 && decrement == 1)               // O bot�o de incremento est� pressionado e o de decrement�o n�o?
        {
            incrementValue(&value);                         // Sim - Incrementa o valor por refer�ncia (verificar fun��o no header.h)
        }
        else if (increment == 1 && decrement == 0)          // O bot�o de incremento n�o est� pressionado e o de decrement�o sim?
        {
            value = decrementValue(value);                  // Sim - Decrementa o valor por passagem de par�metros (verificar fun��o no header.h)
        }
        
        // Verifica��o do valor
        if (value == 0)                                     // A vari�vel value � igual a 0?
        {
            Led0 = 1;                                       // Sim - Ascende o Led 0
        }
        else
        {
            Led0 = 0;                                       // N�o - Apaga o Led 0
        }
        
        if (value == 10)                                    // A vari�vel value � igual a 10?
        {
            Led10 = 1;                                      // Sim - Ascende o Led 10
        }
        else
        {
            Led10 = 0;                                      // N�o - Apaga o Led 0
        }
    }
}
