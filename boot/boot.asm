org 0x7c00      ; Start from this address offset,
BITS 16         ; Use 16bit Architecture, Real Mode, make sure assembler only
                ; assembles 16 bit code.

CODE_SEG equ gdt_code - gdt_start   ; Calculate the CS offset
DATA_SEG equ gdt_data - gdt_start   ; Calculate the DS offset

; Fake BIOS Partition Block BPB structure (disk formatting information)
; First 3 bytes jump over the disk formatting information (the BPB)
; Pad reamaining with 33 bytes.
; If BIOS writes data to the usb drive it does not overwrite boot code
; It just overwrites our fake BPB structure.

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0:step2 ; Set code segment to 0 so offsets from 0x7c00 work.

step2:

    cli     ; Clear interrupts, we do not want hardware interrupts interrputing
            ; our segment register setup

    ; Set Memory Segments to ensure data offsets correctly
    ; For Example:
    ; lodsb uses DS:SI (address:offset)
    ; mov ax, 0x7c0
    ; mov ds, ax
    ; DS = 0x7c0 * 16 = 0x7c00
    ; If SI has an address of 0x14
    ; The absolute address is 0x7c00+0x14 = 0x7c14
    ;[address 0x14 (held in SI) - becomes an offset from DS.]
    mov ax, 0x00
    mov ds, ax          ; Set Data segment
    mov es, ax          ; Set Extra segment
    mov ss, ax          ; Set stack segment to Zero
    mov sp, 0x7c00      ; Set stack pointer

    sti ; Enable interrupts


.load_protected:
    cli                     ; Disable interrupts
    lgdt[gdt_descriptor]    ; load GDT register with the start address of
                            ; the global descriptor table.
    mov eax, cr0
    or eax, 0x1             ; Bitwise OR Mask, set PR (Protection Enable)
                            ; bit in the CR0 Reg (Control Register 0)
    mov cr0, eax            ; Apply the new value after applying OR mask

    jmp CODE_SEG:load32

; GDT - Global Descriptor Table.
; The entries in the GDT are 8 bytes long and form a table like this:
; +---------------------------+
; |Address	        | Content |
; |GDTR Offset + 0	| Null    | -> Empty 8 bytes
; |GDTR Offset + 8	| Entry 1 | -> CS: code segment
; |GDTR Offset + 16	| Entry 2 | -> DS: data segment
; |GDTR Offset + 24	| Entry 3 | -> NO ENTRY
; |...               |...     |
; +---------------------------+
;
; The first entry in the GDT (Entry 0) should always be null and subsequent
; entries should be used instead.

gdt_start:  ; GDT Table Start Address
gdt_null:           ; NULL Entry - Offset 0x00
    dd 0x0
    dd 0x0

gdt_code:           ; CODE SEGMENT Offset 0x08
    dw 0xffff       ; 0-15bits LIMIT: 0xfffff limit spans the full 4Gb address
                    ; space
    dw 0            ; 16-31 bits BASE: Address where segment begins (Will use
                    ; paging this may be ignored
    db 0            ; 32-39 bits : BASE
    db 0x9a         ; 40-47 bits : ACCESS BYTE
    db 0xcf         ; 48-51 bits (nibble, lower half of the byte) : Limit, as
                    ; above, this is a 20 bit value and setting value to
                    ; 0xfffff makes full use of the 4gb address space
                    ; 52 - 55 bits (nibble, upper half of the byte)
    db 0            ; Base 56-63 bits

gdt_data:           ; DATA SEGMENT Offset 0x10
    dw 0xffff       ; 0-15bits LIMIT: 0xfffff limit spans the full 4Gb address
                    ; space
    dw 0            ; 16-31 bits BASE: Address where segment begins (Will use
                    ; paging this may be ignored
    db 0            ; 32-39 bits : BASE
    db 0x92         ; 40-47 bits : ACCESS BYTE
    db 0xcf         ; 48-51 bits (nibble, lower half of the byte) : Limit, as
                    ; above, this is a 20 bit value and setting value to
                    ; 0xfffff makes full use of the 4gb address space
                    ; 52 - 55 bits (nibble, upper half of the byte)
    db 0            ; Base 56-63 bits
gdt_end:

; The GDT is pointed to by the value in the GDTR register. This is loaded
; using the LGDT assembly instruction, whose argument is a pointer to a GDT
; Descriptor structure:
; Size: The size of the table in bytes subtracted by 1. This subtraction
; occurs because the maximum value of Size is 65535, while the GDT can be up
; to 65536 bytes in length (8192 entries). Further, no GDT can have a size of
; 0 bytes.
; Offset: The linear address of the GDT (not the physical address, paging
; applies).
;
; [32 bit mode]
; +----------------------+
; | Offset   |   Size    |
; |31-0 bits | 15-0 bits |
; +----------|-----------+

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; 0-15 bits: Calculate the size of the gdt
                                ; structure.
    dd gdt_start                ; 0-31 bits: Offset

; Swtich to 32 bit protected mode and set the data segments
; NO ACCESS to BIOS.
[BITS 32]
load32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000           
    mov esp, ebp            ; Set stack pointer further in memory, as we can 
                            ; now access more memory
    jmp $
    

times 510 - ($-$$) db 0     ; Fill upto 510 bytes of data
                            ; pad with 0's upto 510th byte
                            ; leaving two bytes for the magic word.

dw 0xAA55           ; 0x55AA last two bytes, word is defined for little endian
                    ; (bytes will be swapped to 55AA in memory)