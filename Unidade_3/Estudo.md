# Arquitetura de Microprocessador e Programação Assembly

## Microcontroladores PIC
- Fabricante Microcip
- Arquitetura Harvard
- Filosofia RISC - 35 instruções
- Barramento de dados 8, 16, 32 bits
- Barramento instrução 12, 14 ou 16 bits

## PIC 16F877A
- Microcontrolador de 40 pinos
- 33 portas configuráveis como entrada ou saída
- 14 interrupções disponíveis
- Memória de programa Flash de 8Ki Words (8 * 1024 * 14)
- 8 bits

- Modelo usado para fazer protótipos DIP = Dual in-line Package (barramento dos dois lados, mais robusto)

- Modelos SMD = Surface Mounted Device (componentes menores e com terminais mais curtos)

---

- Memória EEPROM (não volátil) interna (256Bytes); <!-- Para gravar constantes -->
- Memória RAM com 386 Bytes; <!-- SRAM (Static) baseada em flip-flops-->
- Três Timers (2x8bits e 1x16bits);
- Comunicação serial (USART, SPI, I2C);
- 8 conversores A/D de 10 bits;
- Dois módulos CCP: Capture, compare e PWM.

---

## PIC 16F877A - Pinagem

- 11, 12, 31, 32 = pinos de alimentação
- 1 = pino de RST (trava o programa se não for habilitado)
- 13, 14 = pinos de clock
- 2, 3, 4, 5, 6, 7 = Porta A de comunicação
- 33, 34, 35, 36, 37, 38, 39, 40 = Porta B de comunicação
- 15, 16, 17, 18, 23, 24, 25, 26 = Porta C de comunicação
- 19, 20, 27, 28, 29, 30 = Porta D de comunicação
- 8, 9, 10 = Porta E de comunicação

> OBS: Portas de comunicação são feitas para determinar as entradas e saídas

## Clock com circuito RC

- Sinal de clock é um sinal elétrico (forma de onda quadrada para os níves lógicos 0 e 1 com um período único). <!--Tempo mínimo para executar uma instrução mais básica do microprocessador ou microcontrolador (NOP)-->

## Os Ciclos de Máquina
- O Clock interno é equivalente ao externo dividido por 4.
- Logo, se CK externo = 4Mhz, interno 1Mhz, ciclo de máquina = 1us (micro segundos).

> Os clocks podem ser obtidos com capacitor e resistor, ou com o cristal piezoeletrico que possui uma melhor sincronia.

## Sistema de reset dos Microprocessadores
- Inicializar os elementos internos para começar a trabalhar.