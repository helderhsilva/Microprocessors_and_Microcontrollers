Exercícios com timers:

**1. Desejo configurar o timer 1 para uma temporização de 100ms. Quantos pulsos devo contar? Qual pre-escaler usar? Supor cristal de 4Mhz.**

> Com clock = 4Mhz
> 4Mhz/4 = 1Mhz
> p = 1us
> Pré-escala T1_DIV_BY_2
> 1Mhz/2 = 0,5khz -> p = 2us
> Um pulso e uma contagem a cada 2us
> Se quiser 100ms de tempo, dividi por 2us = 50000 pulsos de 2us
> Basta o timer 1 contar 50000 pulsos.
> TIMER1 = 65536 - 50000 = 15536

**2. Preciso configurar o timer 0 para uma contagem de 1ms. Como configurá-lo? Supor cristal de 4Mhz.**

> Com clock = 4Mhz
> 4Mhz/4 = 1Mhz
> p = 1us
> Pré-escala T0_DIV_BY_8
> 1Mhz/8 = 125khz -> p = 8us
> Um pulso e uma contagem a cada 8us
> Se quiser 1ms de tempo, dividi por 8us = 125 pulsos de 8us
> Basta o timer 0 contar 125 pulsos.
> TIMER0 = 256 - 125 = 131