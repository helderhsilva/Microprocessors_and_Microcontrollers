;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: Exercício 5 - Carro de Transporte
; Autor: Helder Henrique da Silva - 20250326
; Funcionalidade:
;   O carro começa no sensor A (switch A fechado)
;   Ao apertar o botão M o processo de transporte é começado
;	O carro sai do sensor A (switch A aberto) e se move até o sensor B (LED da direita aceso durante o movimento)
;	Quando o carro chega no sensor B (switch B fechado), o LED da direita se apaga e o LED da comporta ascende
;	    Ao apertar o botão P (sensor de peso), o led da comporta aguarda 5 segundos, apaga e ascende o LED da Esquerda (switch B aberto)
;	    Quando o carro chegar no sensor A (switch A fechado), o LED da esquerda apaga e espera um novo ciclo.
;*******************************************************************************

#include <P16F877A.INC>				     ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuração, desabilita e habilita algumas opções internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** definição de Variáveis  *****************************
;cria constantes para o programa

	cblock  0x20
		    ; Variáveis usadas na rotina de delay.
		    tempo0		
		    tempo1
		    tempo2
		    filtro			
	endc 

; Entrada
	#define	    botaoM	PORTB,RB0	    ; Botão M ligado em RB0
	#define	    sensorA	PORTB,RB2	    ; Chave A ligado em RB2
	#define	    sensorB	PORTB,RB5	    ; Chave B ligado em RB5
	#define	    botaoP	PORTB,RB7	    ; Botão P ligado em RB7

; Saída
	#define	    esquerda	PORTD,RD2	    ; Led de representação do movimento do carro para a esquerda
	#define	    direita	PORTD,RD4	    ; Led de representação do movimento do carro para a direita
	#define	    comporta	PORTD,RD6	    ; Led de representação do funcionamento da comporta
    
;******** Vetor de Reset do uC**************
	org	    0x00			    ; Vetor de reset do uC.
	goto	    inicio			    ; Desvia para o inicio do programa.
 
;******** Vetor de Interrupção do uC**************
    ;	org	    0x04			    ; Vetor de reset do uC.
    ;	retfie					    ; Retorna da interrupção.
;
    
;************************** Rotinas e Sub-Rotinas ******************************
; Rotina de delay (De 1ms até 256 ms)
delay_ms:
;	movlw	    .4				    ; vai carrega tempo2 com constante  
	movwf	    tempo2			    ; carrega tempo2   
denovo2:
	movlw	    .250			    ; vai carrega tempo1 com constante
	movwf	    tempo1			    ; Carrega tempo1 
denovo:	
	movlw	    .250			    ; vai carregar tempo0 com constante
	movwf	    tempo0			    ; Carrega tempo0 
volta:	
	nop					    ; gasta 1 ciclo de máquina(1us para clock 4Mhz)
	decfsz	    tempo0,F			    ; Fim de tempo0 ? (gasta 2 us)
	goto	    volta			    ; Não - Volta (gasta 1us)
						    ; Sim - Passou-se 1ms. (4us x 250 = 1ms)
	decfsz	    tempo1,F			    ; Fim de tempo1?
	goto	    denovo			    ; Não - Volta 
						    ; Sim. 250 x 1ms = 250ms	
	decfsz	    tempo2,F			    ; Fim de tempo2?
	goto	    denovo2			    ; Não - Volta 
						    ; Sim. 4 x 250 = 1s				
	return					    ; Retorna. 
	
;********************* Rotina do Processo de Transporte ************************
; Rotina de Transporte de A para B
transporteAB:
	bsf	    direita			    ; Ascende Led Direita - Carro saiu da posição A em direção a posição B
	goto	    verificaB			    ; Verifica se o sensor B está ligado

; Rotina para verificar se o sensor B está ligado
verificaB:
	btfss	    sensorA			    ; Verifica se o sensor A está ligado
	goto	    verificaB			    ; Sim - Retorna a verificação
	btfss	    sensorB			    ; Não - Verifica se o sensor B está ligado
	goto	    abreComporta		    ; Sim - Ativa a comporta
	goto	    verificaB			    ; Não - Retornaa a verificação
	
; Rotina de abrir a comporta para carregamento do carro
abreComporta:
	bcf	    direita			    ; Apaga Led Direita - Carro chegou na posição B
	bsf	    comporta			    ; Liga o sensor da comporta - O carro está sendo carregado
	goto	    verificaPeso		    ; Verifica se o sensor de peso foi acionado
	
; Rotina para verificar se o sensor de peso foi acionado
verificaPeso:
	btfss	    botaoP			    ; BotãoP (sensor P) foi pressionado?
	goto	    fechaComporta		    ; Sim - Começaa o proceesso de fechar a comporta
	goto	    verificaPeso		    ; Não - Volta para a verificação

; Rotina para fechar a comporta
fechaComporta:
	movlw	    .20
	call	    delay_ms			    ; Aguarda 5 segundos para o fechamento da comporta
	bcf	    comporta			    ; Sensor da comporta é desligado - Comporta fechada
	goto	    transporteBA		    ; Começa o processo de transporte de B para A
	
; Rotina de Transporte de B para A
transporteBA:
	bsf	    esquerda			    ; Ascende Led Esquerda - Carro saiu da posição B em direção a posição A
	goto	    verificaA			    ; Verifica se o sensor A está ligado

; Rotina para verificar se o sensor A está ligado
verificaA:
	btfss	    sensorB			    ; Verifica se o sensor B está ligado
	goto	    verificaA			    ; Sim - Retorna a verificação
	btfss	    sensorA			    ; Não - Verifica se o sensor A está ligado
	goto	    novoCiclo			    ; Sim - Apaga a Led Esquerda e joga para um novo ciclo
	goto	    verificaA			    ; Não - Retorna a verificação
	
; Rotina para gerar um novo ciclo
novoCiclo:
	bcf	    esquerda			    ; Apaga a Led Esquerda - Carro chegou na posição A
	goto	    loop			    ; Retorna para o loop
	
;****************** Inicio do programa *****************************************
inicio:
	clrf	    PORTB			    ; Inicializa o Port B com zero
	clrf	    PORTD			    ; Inicializa o Port D com zero

	banksel	    TRISA			    ; Seleciona banco de memória 1
	
	movlw	    0xFF
	movwf	    TRISB			    ; Configura PortB como entrada
	
	movlw	    0x00
	movwf	    TRISD			    ; Configura PortD como saída
	
	movlw	    0x00
	movwf	    OPTION_REG			    ; Configura Opções:
						    ; Pull-Up habilitados.
						    ; Interrupção na borda de subida do sinal no pino B0.
						    ; Timer0 incrementado pelo oscilador interno.
						    ; Prescaler WDT 1:1.
						    ; Prescaler Timer0 1:2.
	banksel	    PORTA			    ; Seleciona banco de memória 0.

;*********************** Loop principal ****************************************
loop:    
	btfss	    botaoM			    ; BotãoM foi pressionado?
	goto	    transporteAB		    ; Sim - Começa o processo de transporte de A para B
	goto	    loop			    ; Não - Volta para o início
    end