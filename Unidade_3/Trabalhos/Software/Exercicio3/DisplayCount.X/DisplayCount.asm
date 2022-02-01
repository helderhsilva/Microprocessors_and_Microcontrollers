;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: Exerc�cio 3 - Display Incrementa/Decrementa (0-99)
; Autor: Helder Henrique da Silva
; Se apertar o bot�o de incrementar o display de 7 segmentos � incrementado
; Se apertar o bot�o de decrementar o display de 7 segmentos � decrementado
;*******************************************************************************

    
#include <P16F877A.INC>			    ; Arquivo de include do uC usado, no caso PIC16F877A

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
		; Vari�veis para verifica��o de incremento e decremento
	endc 

; Entrada
	#define	    botao1	PORTB,RB1	    ; Bot�o ligado em RB1
	#define	    botao2	PORTB,RB2	    ; Bot�o ligado em RB2

; Sa�da
	#define	    In_A_U	PORTD,RD0	    ; Entrada A para a unidade ligado em RD0
	#define	    In_B_U	PORTD,RD1	    ; Entrada B para a unidade ligado em RD1
	#define	    In_C_U	PORTD,RD2	    ; Entrada C para a unidade ligado em RD2
	#define	    In_D_U	PORTD,RD3	    ; Entrada D para a unidade ligado em RD3
	
	#define	    In_A_D	PORTD,RD4	    ; Entrada A para a dezena ligado em RD4
	#define	    In_B_D	PORTD,RD5	    ; Entrada B para a dezena ligado em RD5
	#define	    In_C_D	PORTD,RD6	    ; Entrada C para a dezena ligado em RD6
	#define	    In_D_D	PORTD,RD7	    ; Entrada D para a dezena ligado em RD7
    
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
	movlw	    .1				    ; vai carrega tempo2 com constante  
	movwf	    tempo2			    ; carrega tempo2   
denovo2:
	movlw	    .255			    ; vai carrega tempo1 com constante
	movwf	    tempo1			    ; Carrega tempo1 
denovo:	
	movlw	    .255			    ; vai carregar tempo0 com constante
	movwf	    tempo0			    ; Carrega tempo0 
volta:	
	nop					    ; gasta 1 ciclo de m�quina(1us para clock 4Mhz)
	decfsz	    tempo0,F			    ; Fim de tempo0 ? (gasta 2 us)
	goto	    volta			    ; N�o - Volta (gasta 1us)
						    ; Sim - Passou-se 1ms. (1us x 255 = 255us)
	decfsz	    tempo1,F			    ; Fim de tempo1?
	goto	    denovo			    ; N�o - Volta 
						    ; Sim. 255 x 1ms = 255us	
	decfsz	    tempo2,F			    ; Fim de tempo2?
	goto	    denovo2			    ; N�o - Volta 
						    ; Sim. 1 x 255 = 255us				
	return					    ; Retorna.
	
; Rotina de Incrementar
Incremento:
	call	    verificaUnidadeNove
	incf	    PORTD
	call	    delay_ms
	goto	    loop
	
; Rotina de Verifica��o se a Unidade � Nove
verificaUnidadeNove:
	btfss	    In_A_U
	return
	
	btfsc	    In_B_U
	return
	
	btfsc	    In_C_U
	return
	
	btfss	    In_D_U
	return
	
	movlw	    0x07
	addwf	    PORTD
	call	    delay_ms
	
	goto loop
    

; Rotina de Verifica��o de Incremento M�ximo (99)
verificaIncremento:
	btfss	    In_A_D
	goto	    Incremento
	
	btfsc	    In_B_D
	goto	    Incremento
	
	btfsc	    In_C_D
	goto	    Incremento
	
	btfss	    In_D_D
	goto	    Incremento
	    
	btfss	    In_A_U
	goto	    Incremento
	
	btfsc	    In_B_U
	goto	    Incremento
	
	btfsc	    In_C_U
	goto	    Incremento
	
	btfss	    In_D_U
	goto	    Incremento
	
	movlw	    0x99
	subwf	    PORTD
	call	    delay_ms
	
	goto loop

; Rotina de Dencrementar
Decremento:
	call	    verificaUnidadeZero
	decf	    PORTD
	call	    delay_ms
	goto	    loop
	
; Rotina de Verifica��o se a Unidade � Zero
verificaUnidadeZero:
	btfsc	    In_A_U
	return
	
	btfsc	    In_B_U
	return
	
	btfsc	    In_C_U
	return
	
	btfsc	    In_D_U
	return
	
	movlw	    0x07
	subwf	    PORTD
	call	    delay_ms
	
	goto loop
		
; Rotina de Verifica��o de Decremento M�ximo (00)
verificaDecremento:
	btfsc	    In_A_D
	goto	    Decremento
	
	btfsc	    In_B_D
	goto	    Decremento
	
	btfsc	    In_C_D
	goto	    Decremento
	
	btfsc	    In_D_D
	goto	    Decremento
    
	btfsc	    In_A_U
	goto	    Decremento
	
	btfsc	    In_B_U
	goto	    Decremento
	
	btfsc	    In_C_U
	goto	    Decremento
	
	btfsc	    In_D_U
	goto	    Decremento
		
	movlw	    0x99
	addwf	    PORTD
	call	    delay_ms
	
	goto loop

 
;****************** Inicio do programa *****************************************
inicio:
	clrf	    PORTB			    ; Inicializa o Port B com zero
	clrf	    PORTD			    ; Inicializa o Port D com zero

	banksel	    TRISA			    ; Seleciona banco de mem�ria 1
	
	movlw	    0x06
	movwf	    TRISB			    ; Configura PortB, bit 1 e bit 2 como entrada e o resto sa�da
	
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
	btfss	    botao1
	goto	    verificaIncremento
	btfss	    botao2
	goto	    verificaDecremento
	goto	    loop
	
    end
