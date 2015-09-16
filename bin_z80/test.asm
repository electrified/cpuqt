; my little EMUF
 
; define some labels:
anton equ 66
berta equ 88
 
; define code:
        org   0
reset:  di
        jp    _init
 
        org   8
printc: jp    _printc
 
; pad file to eprom size:
;ds 0x2000 - $