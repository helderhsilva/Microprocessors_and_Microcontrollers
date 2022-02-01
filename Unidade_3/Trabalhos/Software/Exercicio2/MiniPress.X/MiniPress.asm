;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: Exec�cio 2 de Microcontroladores e Microprocessadores: Mini Prensa
; Autor: Helder Henrique da Silva
; Mini Prensa:
;	Y1 = v�lvula 1	// Come�a ativa (led vermelho ligado) representando que a prensa subiu.
;	Y2 = v�lvula 2	// Come�a desativada (led verde desligado)
;			   e � ativado se os dois bot�es estiverem pressionados
;			   representando que a prensa est� ligada e descendo.
;			   Se os dois bot�es forem pressionaos a led vermelha apaga e a verde ascende,
;			   ap�s soltas os bot�es � aguardado dois segundos e volta ao estado inicial.
;*******************************************************************************

    
#include <P16F877A.INC>			    ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configura��o, desabilita e habilita algumas op��es internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** defini��o de Vari�veis  *****************************
;cria constantes para o programa

	cblock  0x20
		    tempo0		
		    tempo1			    ; Vari�veis usadas na rotina de delay.
		    tempo2
		    filtro			
	endc 

; Entrada
	#define	    botao1	PORTB,RB1	    ; Bot�o ligado em RB1
	#define	    botao2	PORTD,RD7	    ; Bot�o ligado em RD7

; Sa�da
	#define	    led_Y1	PORTB,RB7	    ; Bot�o ligado em RB7
	#define	    led_Y2	PORTD,RD1	    ; Bot�o ligado em RD1
    
;******** Vetor de Reset do uC**************
	org	    0x00			    ; Vetor de reset do uC.
	goto	    inicio			    ; Desvia para o inicio do programa.
 
;******** Vetor de Interrup��o do uC**************
    ;	org	    0x04			    ; Vetor de reset do uC.
    ;	retfie					    ; Retorna da interrup��o.
;
;*************** Rotinas e Sub-Rotinas *****************************************
; Rotina de delay (De 1ms at� 256 ms)
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
 
;****************** Inicio do programa *****************************************
inicio:
	clrf	    PORTB			    ; Inicializa o Port B com zero
	clrf	    PORTD			    ; Inicializa o Port D com zero

	banksel	    TRISA			    ; Seleciona banco de mem�ria 1
	
	movlw	    0x02
	movwf	    TRISB			    ; Configura PortB, bit 1 como entrada e o resto sa�da
	
	movlw	    0x80
	movwf	    TRISD			    ; Configura PortD, bit 7 como entrada e o resto sa�da
	
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
	bsf	    led_Y1			    ; Ascende o led vermelho = valvula 1 ativa = prensa inativa
	btfsc	    botao1			    ; Bot�o 1 foi pressionado?
	goto	    loop			    ; N�o, volta para o come�o
	btfsc	    botao2			    ; Bot�o 2 foi pressionado?
	goto	    loop			    ; N�o, volta para o come�o
	goto	    ativo			    ; Sim, move para a label ativo
	
ativo:
	bcf	    led_Y1			    ; Apaga o led vermelho = v�lvula 1 inativa
	bsf	    led_Y2			    ; Ascende o led verde = v�lvula 2 ativa = prensa ativa
	btfsc	    botao1			    ; Bot�o 1 foi pressionado?
	goto	    inativo			    ; N�o, move para a label inativo
	btfsc	    botao2			    ; Bot�o 1 foi pressionado?
	goto	    inativo			    ; N�o, move para a label inativo
	goto	    ativo			    ; Retorna para o ativo.
	
inativo:
	call	    delay_ms			    ; Delay de 2 segundos = prensa continua ativa por 2 segundos
	bcf	    led_Y2			    ; Apaga o led verde = Prensa inativa
	goto	    loop			    ; Retorna ao in�cio 
    end


