/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício 5 - Cancela de trem
* Autor: Helder Henrique da Silva - 20250326
* Create File: 13/02/2022
* Funcionalidade:
* Inicia-se com a cancela fechada (SCF fechado) e com as luzes apagadas (abrindo e fechando apagado)
* Qaundo um carro acionar o sensor de presença de carro (SA) a cancela deve abrir, ou seja MCA e abrindo são ligados até que
* o sensor de cancela aberta seja ativado (SCA)
* Quando SCA estiver ativo, a luz abrindo e o MCA são desligados e aguarda-se 20 segundos para o carro passar
* Após os 20 segundos, o MCF e a luz fechanddo são ativos até que o SCF seja ativo
* Quando SCF estiver ativo volta ao inicio
 * Se o sensor do trem (ST) for ativado, chama a interrupção
 * Mantem a cancela fechada e aciona a sirene
 * Se SA estiver ativo quando a interrupção for chama, aguarda 20 segundos  e fecha a cancela
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        flag = 0;                                   // Retorna a verificação de interrupção para 0 para que possa ser feito novamente
        aux = 0;
        
        desligaMotores();
        BUZZ = 0;
        
        while (aux != 3 && flag == 0)               // Enquanto não tiver entrado numa interrupção e não tiver chegado no último processo
        {
            if (aux == 0 && SA == 0)                // Se está no primeiro processo e o sensor de automóvel é ativado
            {                   
                abreCancela();                      // Abre a cancela (verificar no header.h)
                aux = 1;                            // Ativa o próximo processo
            }
            
            if (aux == 1 && SCA == 0 & SCF == 1)    // Se a cancela abriu e seu sensor foi ativado
            {
                desligaMotores();                   // Desliga os motores e sinalizadores
                __delay_ms(5000);                   // Aguarda 20 segundos (5 segundos para exemplificação)
                fechaCancela();                     // Começa a fechar a cancela
                aux = 2;                            // Ativa o próximo processo
            }
            
            if (aux == 2 && SCF == 0 && SCA == 1)
            {
                desligaMotores();                   // Desliga tudo
                __delay_ms(1000);                   // Aguarda 1 segundo por segurança
                aux = 3;                            // Retorna para o início
            }
        }
    }
}
