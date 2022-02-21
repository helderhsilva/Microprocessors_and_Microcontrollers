/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 19/02/2022
* Funcionalidade:
* Suponha um reservatório de água inicialmente vazio.
* Uma bomba puxa água do rio para o reservatório
* Qaundo a água atinge um certo nível, ativa o sensor de nível no reservatório, a bomba é desligada e liga o aquecedor
* O aquecedor fica ligado até que o sensor de temperatura atinja 40ºC
* Ao atingir 40ºC o aquecedor é desligado e o misturador é ligado por 10 segundos para homogenização
* Após os 10 segundos o misturador é desligado e a válvula de saída é aberta
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        if (Sensor_Nivel_Cheio == 0 && Sensor_Nivel_Vazio == 1)         // Parece ambiguo, mas pra mim faz sentido (verificação dupla)
        {                                                               // Se o sensor de cheio estiver ativo e o sensor de vazio estiver desativado
            Desliga_Bomba();
        }
        else if (Sensor_Nivel_Cheio == 1 && Sensor_Nivel_Vazio == 0)    // Se não se, Se o sensor de cheio estiver desativado e o sensor de vazio estiver ativado
        {
            Liga_Bomba();
        }
    }
}
