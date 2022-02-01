;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: Exerc�cio 5 - Carro de Transporte
; Autor: Helder Henrique da Silva - 20250326
; Funcionalidade:
;   O carro come�a no sensor A (switch A fechado)
;   Ao apertar o bot�o M o processo de transporte � come�ado
;	O carro sai do sensor A (switch A aberto) e se move at� o sensor B (LED da direita aceso durante o movimento)
;	Quando o carro chega no sensor B (switch B fechado), o LED da direita se apaga e o LED da comporta ascende
;	    Ao apertar o bot�o P (sensor de peso), o led da comporta aguarda 5 segundos, apaga e ascende o LED da Esquerda (switch B aberto)
;	    Quando o carro chegar no sensor A (switch A fechado), o LED da esquerda apaga e espera um novo ciclo.
;*******************************************************************************

#include <P16F877A.INC>				     ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configura��o, desabilita e habilita algumas op��es internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** defini��o de Vari�veis  *****************************
;cria constantes para o programa

	cblock  0x20
		    ; Vari�veis usadas na rotina de delay.
		    tempo0		
		    tempo1
		    tempo2
		    filtro			
	endc 

; Entrada
	#define	    botaoM	PORTB,RB0	    ; Bot�o M ligado em RB0
	#define	    sensorA	PORTB,RB2	    ; Chave A ligado em RB2
	#define	    sensorB	PORTB,RB5	    ; Chave B ligado em RB5
	#define	    botaoP	PORTB,RB7	    ; Bot�o P ligado em RB7

; Sa�da
	#define	    esquerda	PORTD,RD2	    ; Led de representa��o do movimento do carro para a esquerda
	#define	    direita	PORTD,RD4	    ; Led de representa��o do movimento do carro para a direita
	#define	    comporta	PORTD,RD6	    ; Led de representa��o do funcionamento da comporta
    
;******** Vetor de Reset do uC**************
	org	    0x00			    ; Vetor de reset do uC.
	goto	    inicio			    ; Desvia para o inicio do programa.
 
;******** Vetor de Interrup��o do uC**************
    ;	org	    0x04			    ; Vetor de reset do uC.
    ;	retfie					    ; Retorna da interrup��o.
;
    
;************************** Rotinas e Sub-Rotinas ******************************
; Rotina de delay (De 1ms at� 256 ms)
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
	nop					    ; gasta 1 ciclo de m�quina(1us para clock 4Mhz)
	decfsz	    tempo0,F			    ; Fim de tempo0 ? (gasta 2 us)
	goto	    volta			    ; N�o - Volta (gasta 1us)
						    ; Sim - Passou-se 1ms. (4us x 250 = 1ms)
	decfsz	    tempo1,F			    ; Fim de tempo1?
	goto	    denovo			    ; N�o - Volta 
						    ; Sim. 250 x 1ms = 250ms	
	decfsz	    tempo2,F			    ; Fim de tempo2?
	goto	    denovo2			    ; N�o - Volta 
						    ; Sim. 4 x 250 = 1s				
	return					    ; Retorna. 
	
;********************* Rotina do Processo de Transporte ************************
; Rotina de Transporte de A para B
transporteAB:
	bsf	    direita			    ; Ascende Led Direita - Carro saiu da posi��o A em dire��o a posi��o B
	goto	    verificaB			    ; Verifica se o sensor B est� ligado

; Rotina para verificar se o sensor B est� ligado
verificaB:
	btfss	    sensorA			    ; Verifica se o sensor A est� ligado
	goto	    verificaB			    ; Sim - Retorna a verifica��o
	btfss	    sensorB			    ; N�o - Verifica se o sensor B est� ligado
	goto	    abreComporta		    ; Sim - Ativa a comporta
	goto	    verificaB			    ; N�o - Retornaa a verifica��o
	
; Rotina de abrir a comporta para carregamento do carro
abreComporta:
	bcf	    direita			    ; Apaga Led Direita - Carro chegou na posi��o B
	bsf	    comporta			    ; Liga o sensor da comporta - O carro est� sendo carregado
	goto	    verificaPeso		    ; Verifica se o sensor de peso foi acionado
	
; Rotina para verificar se o sensor de peso foi acionado
verificaPeso:
	btfss	    botaoP			    ; Bot�oP (sensor P) foi pressionado?
	goto	    fechaComporta		    ; Sim - Come�aa o proceesso de fechar a comporta
	goto	    verificaPeso		    ; N�o - Volta para a verifica��o

; Rotina para fechar a comporta
fechaComporta:
	movlw	    .20
	call	    delay_ms			    ; Aguarda 5 segundos para o fechamento da comporta
	bcf	    comporta			    ; Sensor da comporta � desligado - Comporta fechada
	goto	    transporteBA		    ; Come�a o processo de transporte de B para A
	
; Rotina de Transporte de B para A
transporteBA:
	bsf	    esquerda			    ; Ascende Led Esquerda - Carro saiu da posi��o B em dire��o a posi��o A
	goto	    verificaA			    ; Verifica se o sensor A est� ligado

; Rotina para verificar se o sensor A est� ligado
verificaA:
	btfss	    sensorB			    ; Verifica se o sensor B est� ligado
	goto	    verificaA			    ; Sim - Retorna a verifica��o
	btfss	    sensorA			    ; N�o - Verifica se o sensor A est� ligado
	goto	    novoCiclo			    ; Sim - Apaga a Led Esquerda e joga para um novo ciclo
	goto	    verificaA			    ; N�o - Retorna a verifica��o
	
; Rotina para gerar um novo ciclo
novoCiclo:
	bcf	    esquerda			    ; Apaga a Led Esquerda - Carro chegou na posi��o A
	goto	    loop			    ; Retorna para o loop
	
;****************** Inicio do programa *****************************************
inicio:
	clrf	    PORTB			    ; Inicializa o Port B com zero
	clrf	    PORTD			    ; Inicializa o Port D com zero

	banksel	    TRISA			    ; Seleciona banco de mem�ria 1
	
	movlw	    0xFF
	movwf	    TRISB			    ; Configura PortB como entrada
	
	movlw	    0x00
	movwf	    TRISD			    ; Configura PortD como sa�da
	
	movlw	    0x00
	movwf	    OPTION_REG			    ; Configura Op��es:
						    ; Pull-Up habilitados.
						    ; Interrup��o na borda de subida do sinal no pino B0.
						    ; Timer0 incrementado pelo oscilador interno.
						    ; Prescaler WDT 1:1.
						    ; Prescaler Timer0 1:2.
	banksel	    PORTA			    ; Seleciona banco de mem�ria 0.

;*********************** Loop principal ****************************************
loop:    
	btfss	    botaoM			    ; Bot�oM foi pressionado?
	goto	    transporteAB		    ; Sim - Come�a o processo de transporte de A para B
	goto	    loop			    ; N�o - Volta para o in�cio
    end