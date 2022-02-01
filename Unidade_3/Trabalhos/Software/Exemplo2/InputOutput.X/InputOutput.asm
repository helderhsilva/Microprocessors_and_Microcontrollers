;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: segundo exemplo de programa�ao assembler para PIC
; Autor: Roderval Marcelino editado por Helder Henrique
; Pisca Led com delay
;*******************************************************************************

    
#include <P16F877A.INC>				; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configura��o, desabilita e habilita algumas op��es internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC
  
; Entrada
    #define	    botao	PORTB,RB1	; Bot�o ligado em RB1

; Sa�da
    #define	    led		PORTD,RD7	; Bot�o ligado em RD7

;******** Vetor de Reset do uC**************
    org		    0x00			; Vetor de reset do uC.
    goto	    inicio			; Desvia para o inicio do programa.
 
;******** Vetor de Interrup��o do uC**************
;   org		    0x04			; Vetor de reset do uC.
;   retfie					; Retorna da interrup��o.


;****************** Inicio do programa *****************************************
inicio:
    clrf	    PORTB			; Inicializa o Port B com zero
    clrf	    PORTD			; Inicializa o Port D com zero

    banksel	    TRISA			; Seleciona banco de mem�ria 1
	
    movlw	    0xFF
    movwf	    TRISB			; Configura PortB como entrada
	
    movlw	    0x00
    movwf	    TRISD			; Configura PortD como sa�da
	
    movlw	    0x00
    movwf	    OPTION_REG			; Configura Op��es:
						; Pull-Up habilitados.
						; Interrup��o na borda de subida do sinal no pino B0.
						; Timer0 incrementado pelo oscilador interno.
						; Prescaler WDT 1:1.
						; Prescaler Timer0 1:2.
    banksel	    PORTA			; Seleciona banco de mem�ria 0.

;*********************** Loop principal ****************************************
loop:
    btfsc	    botao			; Bot�o foi pressionado?
    goto	    apaga_led			; N�o, desvia para label apaga_led
    bsf		    led				; Sim, liga o led
    goto	    loop			; Volta para a label loop
    
apaga_led:
    bcf		    led				; Apaga o led
    goto	    loop			; Volta para o loop
   
    end