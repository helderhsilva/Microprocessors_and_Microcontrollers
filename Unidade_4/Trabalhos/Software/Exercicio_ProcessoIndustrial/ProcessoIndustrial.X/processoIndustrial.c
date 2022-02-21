/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exerc�cio Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 19/02/2022
* Funcionalidade:
* Suponha um reservat�rio de �gua inicialmente vazio.
* Uma bomba puxa �gua do rio para o reservat�rio
* Qaundo a �gua atinge um certo n�vel, ativa o sensor de n�vel no reservat�rio, a bomba � desligada e liga o aquecedor
* O aquecedor fica ligado at� que o sensor de temperatura atinja 40�C
* Ao atingir 40�C o aquecedor � desligado e o misturador � ligado por 10 segundos para homogeniza��o
* Ap�s os 10 segundos o misturador � desligado e a v�lvula de sa�da � aberta
*/

#include "header.h"

void main(void) {
    
    inicializar();
    
    while (1)
    {
        if (Sensor_Nivel_Cheio == 0 && Sensor_Nivel_Vazio == 1)         // Parece ambiguo, mas pra mim faz sentido (verifica��o dupla)
        {                                                               // Se o sensor de cheio estiver ativo e o sensor de vazio estiver desativado
            Desliga_Bomba();
        }
        else if (Sensor_Nivel_Cheio == 1 && Sensor_Nivel_Vazio == 0)    // Se n�o se, Se o sensor de cheio estiver desativado e o sensor de vazio estiver ativado
        {
            Liga_Bomba();
        }
    }
}
