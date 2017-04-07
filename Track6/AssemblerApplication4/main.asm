;
; AssemblerApplication4.asm
;
; Created: 16-3-2017 12:42:04
; Author : Jacob
;


.INCLUDE "m128def.inc"
;
.CSEG
.ORG 	$0000
		rjmp main
;
.CSEG
.ORG	$0200
;
main:
; initialisatie data geheugen
;						;
	ldi		yh, $04		; Y <- $0400		adres in data memory
	ldi		yl, $00		;
;	ldi		yh, HIGH(a)	;
;	ldi		yl, LOW(a)	;

	ldd		r8, Y+0		; Haal waarden op uit data memory
	ldd		r9, Y+1		;
	ldd		r6, Y+2		;
	ldd		r7, Y+3		;
	ldd		r18, Y+4
	ldd		r19, Y+5
	ldd		r20, Y+6
	ldd		r21, Y+7

; 16 bits optelling: r5/r4 = r9/r8 + r7/r6  (23 ab + 44 98 = 68 43)
						; Stap 1: 	tel de LSB’s op: r4 = r6+r8 
	MOV		r4, r8		; 		r4 <- r8 		
	ADD		r4, r6		; 		r4 <- r4+r6 		 misschien Carry gezet 
						; Stap 2: 	tel de MSB’s op met 
						;			de (eventuele) carry uit LSB’s:
						;			r3 = r5+r6+C
	MOV		r5, r9		; 		r5 <- r9 
	ADC		r5, r7		; 		r5 <- r5+r7+C 

	MOV		r18, r5		; 		r5 <- r9 
	ADC		r18, r20		; 		r5 <- r5+r7+C 

	MOV		r19, r18		; 		r5 <- r9 
	ADC		r19, r21 	; 		r5 <- r5+r7+C 
;
; Opslag resultaat
;
	STD		Y+4,r18		; Sla resultaat op in data memory
	STD		Y+5,r19		; 

		
no_end:   					; unlimited loop, when done
		rjmp no_end			
		
.DSEG
.ORG	$0400
	a:	.BYTE	2
	b:	.BYTE	2
	c:	.BYTE	2