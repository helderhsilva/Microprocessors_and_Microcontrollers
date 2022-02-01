;*******************************************************************************
; UFSC- Universidade Federal de Santa Catarina
; Projeto: segundo exemplo de programaçao assembler para PIC
; Autor: Roderval Marcelino editado por Helder Henrique
; Pisca Led com delay
;*******************************************************************************

    
#include <P16F877A.INC>				; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuração, desabilita e habilita algumas opções internas
  __CONFIG  _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC
  
; Entrada
    #define	    botao	PORTB,RB1	; Botão ligado em RB1

; Saída
    #define	    led		PORTD,RD7	; Botão ligado em RD7

;******** Vetor de Reset do uC**************
    org		    0x00			; Vetor de reset do uC.
    goto	    inicio			; Desvia para o inicio do programa.
 
;******** Vetor de Interrupção do uC**************
;   org		    0x04			; Vetor de reset do uC.
;   retfie					; Retorna da interrupção.


;****************** Inicio do programa *****************************************
inicio:
    clrf	    PORTB			; Inicializa o Port B com zero
    clrf	    PORTD			; Inicializa o Port D com zero

    banksel	    TRISA			; Seleciona banco de memória 1
	
    movlw	    0xFF
    movwf	    TRISB			; Configura PortB como entrada
	
    movlw	    0x00
    movwf	    TRISD			; Configura PortD como saída
	
    movlw	    0x00
    movwf	    OPTION_REG			; Configura Opções:
						; Pull-Up habilitados.
						; Interrupção na borda de subida do sinal no pino B0.
						; Timer0 incrementado pelo oscilador interno.
						; Prescaler WDT 1:1.
						; Prescaler Timer0 1:2.
    banksel	    PORTA			; Seleciona banco de memória 0.

;*********************** Loop principal ****************************************
loop:
    btfsc	    botao			; Botão foi pressionado?
    goto	    apaga_led			; Não, desvia para label apaga_led
    bsf		    led				; Sim, liga o led
    goto	    loop			; Volta para a label loop
    
apaga_led:
    bcf		    led				; Apaga o led
    goto	    loop			; Volta para o loop
   
    end