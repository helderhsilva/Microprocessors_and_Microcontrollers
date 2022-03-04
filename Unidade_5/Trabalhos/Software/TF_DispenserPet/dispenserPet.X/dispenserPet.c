/*
* UFSC- Universidade Federal de Santa Catarina
* Projeto: Exercício Processo Industrial
* Autor: Helder Henrique da Silva - 20250326 e Lucas Floriano Garcia - 20203503
* Create File: 02/03/2022
* Funcionalidade:
*
*/

#include "header.h"

void main(void)
{
    inicializar();
    
    unsigned int a;
    float f = 1.414;
    char buffer[20];
    
    while (1)
    {
        Lcd_Clear();                    //limpa LCD
    Lcd_Set_Cursor(1,1);            //P?e curso linha 1 coluna 1
    
    Lcd_Write_String("OLA MUNDO");  //escreve string
    __delay_ms(1000);
    
    Lcd_Set_Cursor(2,1);             //linha 2 coluna 1
    Lcd_Write_String("MUNDO DOIDO"); //escreve string]
    __delay_ms(2000);
    
    C1 = 1;
    C2 = 0;
    C3 = 0;
    C4 = 1;
    
    C5 = 1;
    C6 = 0;
    C7 = 0;
    C8 = 1;
    __delay_ms(2000);
        
    C1 = 0;
    C2 = 1;
    C3 = 1;
    C4 = 0;
    
    C5 = 0;
    C6 = 1;
    C7 = 1;
    C8 = 0;
    __delay_ms(2000);
    
    }
}