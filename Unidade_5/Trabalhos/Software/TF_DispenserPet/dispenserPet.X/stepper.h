/* 
 * File:   stepper.h
 * Author: Helder Henrique da Silva e Lucas Floriano Garcia
 * 
 * Created on 05 de Março de 2022, 19:05
 */
#ifndef STEPPER_H
#define	STEPPER_H

#define _XTAL_FREQ 4000000                                      // Frequência do clock no Cristal definida em 4Mhz

    // Define os pinos do motor de passo
    #define C1 PORTCbits.RC0                                    // Motor da tampa superior 1C
    #define C2 PORTCbits.RC1                                    // Motor da tampa superior 2C
    #define C3 PORTCbits.RC2                                    // Motor da tampa superior 3C
    #define C4 PORTCbits.RC3                                    // Motor da tampa superior 4C

    #define C5 PORTCbits.RC4                                    // Motor da tampa inferior 1C
    #define C6 PORTCbits.RC5                                    // Motor da tampa inferior 2C
    #define C7 PORTCbits.RC6                                    // Motor da tampa inferior 3C
    #define C8 PORTCbits.RC7                                    // Motor da tampa inferior 4C

// Funções Auxiliares para o Motor de Passo
void abreTampaSuperior()
{
    C1 = 0;
    C2 = 1;
    C3 = 1;
    C4 = 0;
    __delay_ms(1000);  
}

void fechaTampaSuperior()
{
    C1 = 1;
    C2 = 1;
    C3 = 0;
    C4 = 0;
    __delay_ms(1000);  
}

void abreTampaInferior()
{
    C5 = 0;
    C6 = 1;
    C7 = 0;
    C8 = 0;
    __delay_ms(1000);      
}

void fechaTampaInferior()
{
    C5 = 1;
    C6 = 1;
    C7 = 0;
    C8 = 0;
    __delay_ms(1000);
}

#endif	/* STEPPER_H */

