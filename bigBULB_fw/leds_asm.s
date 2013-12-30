/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

#include <avr/io.h>

.section .text



; output GBR values to 42 LEDs
; void leds_out(unsigned char data[126]);
.global leds_out
.func leds_out
leds_out:

; save registers
        push    R16
        push    R17
        push    R18
        push    R19
        push    R20
        push    R21
        push    XL
        push    XH

; get parameters: X := R25:R24 = data
        mov     XL,R24
        mov     XH,R25

; pre-init registers
        ldi     R16,0x00                ; output cleared
        ldi     R17,0x04                ; output set
        ldi     R18,0x00                ; output set/cleared (cleared for now)
        ldi     R20,126                 ; init byte counter

; reset
        out     PORTD-0x20,R16          ; clear output
        ldi     R19,150
leds_out_reset:
        dec     R19
        brne    leds_out_reset

; output
        ld      R21,X+                  ; get first byte
        ldi     R19,7                   ; init bit counter
leds_out_loop:
        bst     R21,7                   ; fetch bit
        out     PORTD-0x20,R17          ; set output
        bld     R18,2                   ; output bit
        out     PORTD-0x20,R18
        lsl     R21                     ; next bit
        nop
        out     PORTD-0x20,R16          ; clear output
        dec     R19                     ; bottom of bit loop
        brne    leds_out_loop
                                        ; start of last iteration of bit loop
        ldi     R19,7                   ; init bit counter
        bst     R21,7                   ; fetch bit
        out     PORTD-0x20,R17          ; set output
        bld     R18,2                   ; output bit
        out     PORTD-0x20,R18
        ld      R21,X+                  ; get next byte
        out     PORTD-0x20,R16          ; clear output
        dec     R20                     ; bottom of byte loop
        brne    leds_out_loop

; restore registers
        pop     XH
        pop     XL
        pop     R21
        pop     R20
        pop     R19
        pop     R18
        pop     R17
        pop     R16

; done
        ret

.endfunc

