;65C02 instruction set
.pc02

;Commander X16 definitions
.include "cx16.inc"

;Kernal subroutines and definitions
.include "x16kernal.inc"

;Switch to code segment
.code

;Our "Hello ASM" function, called from the C code
.export _helloasm
.proc _helloasm
    ;Print a string
    lda #<asm_msg
    sta ZP_PTR_1
    lda #>asm_msg
    sta ZP_PTR_1+1
    jsr println

    ;Return back to the caller
    rts
.endproc


;Print ASCII text to screen, at the given address in ZP_PTR_1
.proc println
    ;Y register will be the iterator (so max 256 character strings allowed) 
    ldy #0
@charloop:
    ;Load the current character
    lda (ZP_PTR_1), y
    ;If it is a string terminator (\0) we stop
    beq @done
    ;Otherwise we print it
    jsr CHROUT
    ;Next character
    iny
    ;If the counter overflows, we stop, else we go back to the loop
    bne @charloop
@done:
    rts
.endproc


;Read-only data segment (to store text, characters, etc.)
;Note that characters are not the same on the X16 as in regular ASCII
;so some text will look different if you check the .prg in a hex editor
.rodata
;Null-terminated (ends with \0) string to print out
asm_msg: .asciiz "Hello Assembly!"