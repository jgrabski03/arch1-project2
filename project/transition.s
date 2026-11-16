	.arch msp430g2553
	.p2align 1,0

	.data
	.global state
state:	.word 2			; start in state 2 (dim, quiet)

	.text
jt:	.word case0		; jump table: one entry per button
	.word case1
	.word case2
	.word case3

	;; void transition(int button)   -- button (0..3) arrives in r12
	.global transition
transition:
	cmp #4, r12		; r12 - 4: carry set if r12 >= 4 (unsigned)
	jhs done		; ignore out-of-range buttons
	add r12, r12		; each table entry is 2 bytes, so index *= 2
	mov jt(r12), r0		; jump to jt[button]
case0:	mov #0, &state		; S1 -> siren
	jmp done
case1:	mov #1, &state		; S2 -> blink
	jmp done
case2:	mov #2, &state		; S3 -> dim
	jmp done
case3:	mov #3, &state		; S4 -> song
done:	pop r0			; return (same as ret)
