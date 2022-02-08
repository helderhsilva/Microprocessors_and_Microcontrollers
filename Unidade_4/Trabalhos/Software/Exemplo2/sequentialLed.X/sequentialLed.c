/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exemplo 2 - Pisca Leds Sequencial em C
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Liga e Desliga os Leds de forma sequencial.
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        sequentialLed();                                    // Chama a rotina no header.h
    }
}
