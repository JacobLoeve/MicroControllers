;
; AssemblerApplication.asm
;
; Created: 16-3-2017 09:26:33
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

	ldi		r20, $55
	STS		$540, r20
	STS		$541, r20	
	STS		$542, r20	
	STS		$543, r20	
	STS		$544, r20	
	STS		$545, r20	
	STS		$546, r20	
	STS		$547, r20	
	STS		$548, r20		


		
no_end:   					; unlimited loop, when done
		rjmp no_end			
		
