;X16 Kernal data offsets / subroutine definitions, which are not present in CC65.
;Original code by SlithyMatt (taken from https://github.com/SlithyMatt/x16-hello-cc65/blob/master/asm/x16.inc)
;Modified by nb-programmer (To remove stuff already present in the cc65 include file)

.ifndef X16_INC
X16_INC  = 1

.ifndef __CX16__
__CX16__ = 1
.endif

; X16 addresses, values, and macros
; Accurate for ROM release R38

SD_DEVICE   = 8 ; also host file system on emulator if no SD image mounted
DISK_DEVICE = SD_DEVICE ; change if to be loaded off IEC device

;Parameter taken by LOAD call for the destination bank
FD_LOAD_SYSTEM    = 0
FD_LOAD_VERIFY    = 1
FD_LOAD_VERA00    = 2
FD_LOAD_VERA01    = 3

; RAM Addresses

; Zero-Page userspace
ZP_PTR_1          = $7E   ; four pointers for temporary use only
ZP_PTR_2          = $22
ZP_PTR_3          = $24
ZP_PTR_4          = $26

; ROM Banks
KERNAL_ROM_BANK   = 0
KEYBOARD_ROM_BANK = 1
CBDOS_ROM_BANK    = 2
GEOS_ROM_BANK     = 3
BASIC_ROM_BANK    = 4
MONITOR_ROM_BANK  = 5
CHARSET_ROM_BANK  = 6

; Kernal Subroutines
.include "cbm_kernal.inc"

; BASIC Vectors
BASIC_PANIC       := $C000
BASIC_INIT        := $C003

; VRAM Addresses
VRAM_petscii   = $0F800
VRAM_psg       = $1F9C0
VRAM_palette   = $1FA00
VRAM_sprattr   = $1FC00

; Macros
.macro VERA_SET_ADDR addr, stride
   .ifnblank stride
      .if stride < 0
         lda #((^addr) | $08 | ((0-stride) << 4))
      .else
         lda #((^addr) | (stride << 4))
      .endif
   .else
      lda #(^addr) | $10
   .endif

   sta VERA_addr_bank
   lda #(>addr)
   sta VERA_addr_high
   lda #(<addr)
   sta VERA_addr_low
.endmacro


;Load a file into the given memory address (Either system RAM or VERA VRAM)
;dest_bank is one of the FD_LOAD_* options (see x16kernal.inc)
.macro loadFile fname, fname_len, dest_addr, dest_bank
    ;Set device id to look for the file
    lda #1
    ldx #DISK_DEVICE
    ldy #0
    jsr SETLFS

    ;Tell Kernal which file to look for
    ldx #<fname
    ldy #>fname
    lda #(fname_len)
    jsr SETNAM

    ;Set destination and load the file
    ldx #<dest_addr
    ldy #>dest_addr
    lda #(dest_bank + ^dest_addr)
    jsr LOAD
.endmacro

.endif