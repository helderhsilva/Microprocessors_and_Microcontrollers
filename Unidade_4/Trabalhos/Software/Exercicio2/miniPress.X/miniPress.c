/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio 2 - Mini Prensa
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Ao apertar dois bot�es a prensa funciona por 2 segundos e depois volta a posi��o inicial
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        Y1 = 0;                                         // Apaga o Led Y1 - Prensa na posi��o inicial
        Y2 = 1;                                         // Ascende o Led Y2 - Prensa na posi��o inicial
        
        if (buttonPressVerify() == 1)                   // Verifica - Os bot�es foram pressionados ao mesmo tempo?
        {
            Y2 = 0;                                     // Sim - Apaga o Led Y2 - Prensa come�a a funcionar
            Y1 = 1;                                     // Sim - Ascende o Led Y1 - Prensa come�a a funcionar
            __delay_ms(2000);                           // Aguarda 2 segundos para e recome�a o ciclo.
        }
    }
}
