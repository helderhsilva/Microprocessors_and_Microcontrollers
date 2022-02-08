/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício 1 - Key Led
* Autor: Helder Henrique da Silva - 20250326
* Create File: 08/02/2022
* Funcionalidade:
* Chave aberta = Led desligado -> Chave fechada = Led ligado.
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        On_Off_Key();                           // Chama a rotina no header.h
    }
}
