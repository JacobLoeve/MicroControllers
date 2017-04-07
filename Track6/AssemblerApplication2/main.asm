;
; AssemblerApplication2.asm
;
; Created: 16-3-2017 12:09:32
; Author : Jacob
;


main:
; initialisatie data geheugen

		ldi	  	xh, $60		; X is source adres, high byte = 05H
		ldi	  	xl, 00		; X low byte = 00H
		ldi	  	yh, $70		; Y is destination adres, high byte = 0cH
		ldi	  	yl, 00		; Y low byte = 00H
		ldi	  	r16, 10	; lusteller, r16 = 200

lus:	ld	  	r8, X+		; laad waarde met pointer X in R8
		inc		r8			; one’s complement
		st	  	Y+, r8		; en schrijf weg naar plaats met pntr 
		cp		xl,	r16		; vergelijk zl met 200, sets Z if zero
		brne	lus			; branch indien niet nul (Zero)
;
		
no_end:   					; unlimited loop, when done
		rjmp no_end	
