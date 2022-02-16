org 0           ; Start from this address offset,
BITS 16         ; Use 16bit Architecture, Real Mode, make sure assembler only
                ; assembles 16 bit code.

; Fake BIOS Partition Block BPB structure (disk formatting information)
; First 3 bytes jump over the disk formatting information (the BPB)
; Pad reamaining with 33 bytes.
; If BIOS writes data to the usb drive it does not overwrite boot code
; It just overwrites our fake BPB structure.
_main:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0x7c0:step2 ; Set code segment to 0x7c0 * 0x10 (16 in decimal) = 0x7c00

step2:

    cli     ; Clear interrupts, we do not want hardware interrupts interrputing
            ; our segment register setup

    ; Set Memory Segments to ensure data offsets correctly
    ; For Example:
    ; lodsb use DS:SI (DataSegment address : Address stored in SI)
    ; mov ax, 0x7c0
    ; mov ds, ax
    ; DS = 0x7c0 * 16 = 0x7c00
    ; If SI has an address of 0x14
    ; The absolute address is 0x7c00+0x14 = 0x7c14
    ;[address 0x14 (held in SI) - becomes an offset from DS.]

    mov ax, 0x7c0
    mov ds, ax          ; Set Data segment
    mov es, ax          ; Set Extra segment
    mov ax, 0x00
    mov ss, ax          ; Set stack segment to Zero
    mov sp, 0x7c00      ; Set stack pointer

    sti ; Enable interrupts

    mov si, msg     ; Move address of the start of message
                    ; (first byte/character) into SI register
    call print_msg
    jmp $           ; Infinite loop

print_msg:
    lodsb           ; Move character into AL register and increment SI register
                    ; to point to next character.
    cmp al, 0       ; Check end of string for NULL terminator
    je .done        ; Jmp to done when we have reached the NULL terminator

    mov ah, 0eh     ; BIOS Routine for outputting scrolling text.
                    ; Display a character on the screen, advance the cursor
                    ; scrolling the screen.
    int 0x10        ; Trigger teletype output.
    jmp print_msg   ; Print next char.

.done:
    ret
msg:
    db 'Successfully booted the bootloader...', 0

times 510 - ($-$$) db 0     ; Fill upto 510 bytes of data
                            ; pad with 0's upto 510th byte
                            ; leaving two bytes for the magic word.

dw 0xAA55           ; 0x55AA last two bytes, word is defined for little endian
                    ; (bytes will be swapped to 55AA in memory)