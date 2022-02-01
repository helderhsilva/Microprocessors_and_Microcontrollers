;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: Execício 2 de Microcontroladores e Microprocessadores: Mini Prensa
; Autor: Helder Henrique da Silva
; Mini Prensa:
;	Y1 = válvula 1	// Começa ativa (led vermelho ligado) representando que a prensa subiu.
;	Y2 = válvula 2	// Começa desativada (led verde desligado)
;			   e é ativado se os dois botões estiverem pressionados
;			   representando que a prensa está ligada e descendo.
;			   Se os dois botões forem pressionaos a led vermelha apaga e a verde ascende,
;			   após soltas os botões é aguardado dois segundos e volta ao estado inicial.
;*******************************************************************************

    
#include <P16F877A.INC>			    ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuração, desabilita e habilita algumas opções internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** definição de Variáveis  *****************************
;cria constantes para o programa

	cblock  0x20
		    tempo0		
		    tempo1			    ; Variáveis usadas na rotina de delay.
		    tempo2
		    filtro			
	endc 

; Entrada
	#define	    botao1	PORTB,RB1	    ; Botão ligado em RB1
	#define	    botao2	PORTD,RD7	    ; Botão ligado em RD7

; Saída
	#define	    led_Y1	PORTB,RB7	    ; Botão ligado em RB7
	#define	    led_Y2	PORTD,RD1	    ; Botão ligado em RD1
    
;******** Vetor de Reset do uC**************
	org	    0x00			    ; Vetor de reset do uC.
	goto	    inicio			    ; Desvia para o inicio do programa.
 
;******** Vetor de Interrupção do uC**************
    ;	org	    0x04			    ; Vetor de reset do uC.
    ;	retfie					    ; Retorna da interrupção.
;
;*************** Rotinas e Sub-Rotinas *****************************************
; Rotina de delay (De 1ms até 256 ms)
delay_ms:
	movlw	    .4				    ; vai carrega tempo2 com constante  
	movwf	    tempo2			    ; carrega tempo2   
denovo2:
	movlw	    .500			    ; vai carrega tempo1 com constante
	movwf	    tempo1			    ; Carrega tempo1 
denovo:	
	movlw	    .500			    ; vai carregar tempo0 com constante
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
 
;****************** Inicio do programa *****************************************
inicio:
	clrf	    PORTB			    ; Inicializa o Port B com zero
	clrf	    PORTD			    ; Inicializa o Port D com zero

	banksel	    TRISA			    ; Seleciona banco de memória 1
	
	movlw	    0x02
	movwf	    TRISB			    ; Configura PortB, bit 1 como entrada e o resto saída
	
	movlw	    0x80
	movwf	    TRISD			    ; Configura PortD, bit 7 como entrada e o resto saída
	
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
	bsf	    led_Y1			    ; Ascende o led vermelho = valvula 1 ativa = prensa inativa
	btfsc	    botao1			    ; Botão 1 foi pressionado?
	goto	    loop			    ; Não, volta para o começo
	btfsc	    botao2			    ; Botão 2 foi pressionado?
	goto	    loop			    ; Não, volta para o começo
	goto	    ativo			    ; Sim, move para a label ativo
	
ativo:
	bcf	    led_Y1			    ; Apaga o led vermelho = válvula 1 inativa
	bsf	    led_Y2			    ; Ascende o led verde = válvula 2 ativa = prensa ativa
	btfsc	    botao1			    ; Botão 1 foi pressionado?
	goto	    inativo			    ; Não, move para a label inativo
	btfsc	    botao2			    ; Botão 1 foi pressionado?
	goto	    inativo			    ; Não, move para a label inativo
	goto	    ativo			    ; Retorna para o ativo.
	
inativo:
	call	    delay_ms			    ; Delay de 2 segundos = prensa continua ativa por 2 segundos
	bcf	    led_Y2			    ; Apaga o led verde = Prensa inativa
	goto	    loop			    ; Retorna ao início 
    end


