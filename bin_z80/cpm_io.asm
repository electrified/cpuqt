;zasm -v2 -i cpm_io.asm -o cpm_io.rom
;#target bin
; SYMBOLIC DEFINES
; $8x selects the UART addressing lines
UART_PORT	equ 80h	; The UART's data buffer for in/out
UART_DLL	equ	80h	; LSB of divisor latch
UART_DLM	equ 81h	; MSB of divisor latch (DLAB=1)
UART_FCR	equ	82h	; FIFO control register
UART_IER	equ	81h	; Interrupt Enable register (DLAB=0)
UART_LCR	equ	83h	; Line Control Register
UART_MCR	equ 84h	; Modem Control Register (for OUT1/OUT2)
UART_LSR	equ	85h	; Line Status Register (used for transmitter empty bit)

    org 0
    out (0), A
    ;Ensure is at memory address 5, for CP/M BDOS
    defs 5-$, 0
    PUSH AF
    push de
    ld a, c
    cp 2
    call z, preoutchar
    cp 9
    call z, outmulti
    pop de
    POP AF
    ret
;----------------------------------------------------
preoutchar:
    ld a, e
outchar:
    PUSH AF
    OUT (UART_PORT), A
; wait until transmitted
oloop:
    IN A, (UART_LSR)	; read LSR
    BIT 6, A	; bit 6 is transmitter empty
    JP Z, oloop
    POP AF
    RET
;----------------------------------------------------
outmulti:
    ld a, (de)
    cp a, '$'
    jp z, outend
    call outchar
    inc de
    jp outmulti
outend:
    ret
