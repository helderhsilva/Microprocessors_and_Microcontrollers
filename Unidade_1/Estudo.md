 # Evolução dos Microprocessadores

## Presidente da intel em 1965: Gordon Moore
- _A velocidade dos proceessadores dobra a cada 24 meses (Gordon Moore (1965))_

---

## Funções de im Microprocessador:
1. Elaboração: transformação dos dados (dentro do processador acontece dentro da ULA - Unidade Lógica Aritimética);
2. Controle: transição de dados (enviar e receber dados para periféricos, softwares, etc)

## Um sistema Microprocessado:
- Qualquer dispositivo que tenha um microprocessador (esse possui memória de dados, memória de programa, I/O, barramento de dados).

## Potência de um processador:

- Principais parâmetros:

  - O tamanho de sua palavra de dados (quantidade de bits que vai para a ULA para ser processado);
  - A capacidade de memória externa que pode controlar;
  - A velocidade com qual efetua uma instrução (clock);
  - Memória cache;
  - Velocidade dos periféricaos;
  - Quantidade de núcleos;
  - Dentre outros.

## Diagramas de Blocos Interno

 - Registrador: memórias pequenas e rápidas que armazenam as informações dentro do processador. Possui como célula básica que armazena um bit o componente flip-flop Ex. Um registrador de 8 bits possui 8 flip-flops;

- Elaboração/Transformação dos dados:
  - ULA: Unidade Lógica Aritimética: onde ocorre as manipulações das informações (portas lógicas);
  - Registrador de Estados: mostra acontecimentos especiais da ULA;
  - Acumulador: registrador que recebe o resultado da ULA e envia os dados para outros registradores e barramentos de dados;
- Decodificação da instrução:
  - Registrador de instrução: Armazena a instrução que vem pelo barramento de dados a ser dedcodificada;
  - Decode de instrução: interpreta o que dedve ser feito;
  - Lógica de Controle: executa a innstrução, mandando-a para o barramento de controle.
- Registradores B, C, D, etc: funcionam como memórias caches (possui a célula básica o flip-flop), armazenam dados gerais;
- Contador de Programa: contem o endedreço da próxima instrução a ser executada. No microprocessador genérico de 8 bits, se o contador possui um contador da parte baixa (LOW) e um da parte alta (HIGH), e trabalha com barramento de endereços então ele pode trabalhar com endereços de até 16 bits (2^16 bits), ou seja pode acessar até 65.536 posições da memória, ou ainda, 64 Kbytes da memória.
- O barramento de endereços dá a quantidade de memória que podem ser colocados para um determinado processador.

## Transistor:

- O primeiro transistor media cerca de 1,5 centímetro e não era feito de silício, mas de germânio e ouro, montado sobre suportes de plástico.
- Os transistores fabricados em escala industrial hoje medem 22 nanômetros (na verdade 7 hoje em dia 2021), mais de 330.000 vezes menores.
- Foram vendidos centenas a um preço médio de $3.000,00.

## Circuitos Integrados:

- Implementaram componentes discretos em uma única pastilha de silício.
- Possuem diversos invólucros.
- Cada vez estão integrando mais funções.

## Primerio Processador do Mundo:

- Novembro de 1971, INTEL 4004 (Patente Americana #3,821,715).
- Federico Faggin, Marcian Hoff e Stan Mazor.
- Após a invenção do circuito integrado chegou o microprocessador.
- Tecnologia MOS, 2.300 transistores em uma área de apenas 3x4 milímetros.
- CPU de 4-bit, fazia 6000 operações por segundo
- Os processadores de 64-bit ainda são baseados no 4004.
- Busicon (máquina de calcular japonesa de onde se originou o intel 4004).

## 8008

- Abril de 1972.
- 8 bits. Podia endereçar 16 KB de memória.
- 45 instruções e tinha a velocidade de 300.000 operações por segundo

---

- 8080
  - Abril de 1974.
  - Podia endereçar 64 KB de memória, com 75 instruçoes e com preços a começarem em $360.

## 6800

- Motorola
- 8 bits. O construtor chefe foi Chuck Peddle.
- Fabricou periféricos como os 6820 e 6850.

---

- 6501 e 6502
  - MOS Technology x Chuck Peddle.
  - 8 bits com 56 instruções e uma capacidade de endereçamento de 64 KB de memória.
  - 1975, exposição WESCON nos Estados Unidos.
  - Microprocessadores 6501 e 6502 ao preço de U$25.
  - KIM-1, Apple I, Apple II, Atari, Comodore, Acorn, Oric, Galeb, Orao, Ultra.

## Z80

- Frederico Fraggin deixa a Intel e funda a Zilog.
- Em 1976, a Zilog anuncia o Z80.
- Compatível com o 8080.
- Podia endereçar diretamente 64 KB de memória e tinha 176 instruções, um grande número de registros, uma opção para refrescamento de memória RAM dinâmica, uma única alimentação, maior velocidade de fincionamento.

---

- Em 1976 - 8085
- 8 bits, inferior ao z80

---

- Em 1978 - 8068/8088. 5 Mhz.
- 16 bits / 8 bits
- Os primeiros computadores IBM usaram o 8088, popular XT.

## 80286

- 1982.
- Barramento de 16 bits.
- Usado no PC AT em 1984.
- 16MB de RAM máximo.
- 134.000 transistores.
- 6, 8, 10, 12.5, e 16 Mhz.

## 80386

- Podia executar multitarefas preemptiva.
- Barramento de 32 bits
- 275.000 transistores
- 16, 20, 25, 33 e 40 Mhz (SX, DX)
- 4GB de RAM máximo.

---

- 80486.
- Cache de dados.
- Executava instruções por ciclo de clock.
- 1.200.000 Transistores
- 16, 25, 33, 50, 66 e 100Mhz (SX, DX2, DX, SL).

## Apple

- A Apple nos seus computadores inicialmente utilizava os chips da MOS Technology, depois passou a usar os processadores da Motorola, a família 68000 (de 32 bits).
- Anos depois utilizou o Power PC, chip da IBM e Motorola. Power PC ainda é usado nos dias de hoje, o PS3, por exemplo, utiliza este processador.
- Hoje passou a usar a família INTEL por vários motivos de mercado e tecnológicos.

## Pentium

- Surgiu porque não foi possível patentear números como o 80486.
- Deu continuidade a família x86.
- Pentium, Pentium Pro, Pentium MMX, Pentium II, Pentium III e Pentium IV, Pentium Dual Core.

## AMD

- O PRIMEIRO processador para PC de 64 bits que roda aplicações de 32 bits sendo compatível com Windows. Família Athlon.
- Microsoft lança S.O. compatível com o processador AMD Athlon 64, proporcionando alta performance tanto em aplicativos de 32 bits quanto de 64 bits.

## Core 2 due

- Com os dois núcleos de execução, o processador Intel Core 2 due é otimizado para aplicativos de vários processos e multitarefas.
- Possui dois núcleos físicos ao contrário do Pentium dual core que possui um físico e outro lógico.

## Algumas Tecnologias

- Hyper-threading:
  - Tecnologia para simular que o processador possui mais núcleos do que realmente possui.

- Intel Turbo Boost:
  - Aumenta a velocidade de clock conforme a demanda gerada pelo sistema operacional. Também chamado de "Overcclock dinâmico".

- Virtualização:
  - É a funcionalidade que permite que vários sistemas operacionais compartilhem recursos do processador ao mesmo tempo.

- EM64T:
  - Representa a implementação de uma nova arquitetura fabricação de chips, neste caso, 64 bits.

- DirectX:
  - Suporte para a API do directX, tomando aplicações como jogos mais perfeitas.

## Sandy Bridge (i3, i5 e i7)

- Integoru recursos gráficos e ponte norte no chip.
- Tecnologia de 32 nm.
- Defeito no suporte ao chip set (SATA-II).

---

# Introdução aos Microprocessadores ARM

## ARM Introdução

- ARM - orginalmente Acorn Risc Machine... depois Advanced RISC Machine
- Projetado por Arm Holdings, empresa britânica, desde 1990.
- Nvidia comprou em 2020.
- Não vende chip, vende IP, intelectual Property, licença de uso.

## ARM Características

- Arquitetura RISC.
- Processadores ded baixo consumo.
- Pipeline.
- Custo menor.
- Menor dissipação de calor
- Perfeito para portáteis.
- Ganhando espaço em capacidade de processamento, Apple M1. (Fim da da família x86?)

## Apple M1

- Primeiro System-on-chip (SoC) baseado em ARM projetado pela Appel como uma (CPU).
- Produtos com este processador: MacBook Air e Mac Mini.
- Menor consumo de energia do que o "chip mais recente para um notebook"
- A tecnologia de tradução binária dinâmica Rosetta 2 permite que produtos equipados com M1 executem software desenvolvidos para CPUs Intel x86