/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio 5 - Cancela de trem
* Autor: Helder Henrique da Silva - 20250326
* Create File: 13/02/2022
* Funcionalidade:
* Inicia-se com a cancela fechada (SCF fechado) e com as luzes apagadas (abrindo e fechando apagado)
* Qaundo um carro acionar o sensor de presen�a de carro (SA) a cancela deve abrir, ou seja MCA e abrindo s�o ligados at� que
* o sensor de cancela aberta seja ativado (SCA)
* Quando SCA estiver ativo, a luz abrindo e o MCA s�o desligados e aguarda-se 20 segundos para o carro passar
* Ap�s os 20 segundos, o MCF e a luz fechanddo s�o ativos at� que o SCF seja ativo
* Quando SCF estiver ativo volta ao inicio
 * Se o sensor do trem (ST) for ativado, chama a interrup��o
 * Mantem a cancela fechada e aciona a sirene
 * Se SA estiver ativo quando a interrup��o for chama, aguarda 20 segundos  e fecha a cancela
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        flag = 0;                                   // Retorna a verifica��o de interrup��o para 0 para que possa ser feito novamente
        aux = 0;
        
        desligaMotores();
        BUZZ = 0;
        
        while (aux != 3 && flag == 0)               // Enquanto n�o tiver entrado numa interrup��o e n�o tiver chegado no �ltimo processo
        {
            if (aux == 0 && SA == 0)                // Se est� no primeiro processo e o sensor de autom�vel � ativado
            {                   
                abreCancela();                      // Abre a cancela (verificar no header.h)
                aux = 1;                            // Ativa o pr�ximo processo
            }
            
            if (aux == 1 && SCA == 0 & SCF == 1)    // Se a cancela abriu e seu sensor foi ativado
            {
                desligaMotores();                   // Desliga os motores e sinalizadores
                __delay_ms(5000);                   // Aguarda 20 segundos (5 segundos para exemplifica��o)
                fechaCancela();                     // Come�a a fechar a cancela
                aux = 2;                            // Ativa o pr�ximo processo
            }
            
            if (aux == 2 && SCF == 0 && SCA == 1)
            {
                desligaMotores();                   // Desliga tudo
                __delay_ms(1000);                   // Aguarda 1 segundo por seguran�a
                aux = 3;                            // Retorna para o in�cio
            }
        }
    }
}
