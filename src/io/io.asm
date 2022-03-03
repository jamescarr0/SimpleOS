; /**
;  * @file io.asm
;  * @author James Carr
;  * @brief Read and write bytes to the specified port.
;  * @version 0.1
;  * @date 2022-03-03
;  * 
;  * Global functions called from C.  Allows for higher
;  * level input/output for reading/writing bytes &
;  * words to and from specified ports.
;  * 
;  */

; x86 Instruction Set Reference
; IN
; Input from Port (READ)
;
; IN AL,DX	- Input byte from I/O port in DX into AL.
; IN AX,DX	- Input word from I/O port in DX into AX.
;   
; https://c9x.me/x86/html/file_module_x86_id_139.html

section .asm

global io_read_byte
global io_read_word

global io_write_byte
global io_write_word

io_read_byte:
    push ebp
    mov ebp, esp

    xor eax, eax    ; Zero eax register.
    in al, dx       ; read a byte from port in DX into AL

    pop ebp
    ret

io_read_word:
    push ebp
    mov ebp, esp

    xor eax, eax    ; Zero eax register
    in ax, dx       ; Read a word from port in DX to AX

    pop ebp
    ret


; x86 Instruction Set Reference
; OUT
; Output to Port (WRITE)
; OUT DX, AL	Output byte in AL to I/O port address in DX.
; OUT DX, AX	Output word in AX to I/O port address in DX.
;
; https://c9x.me/x86/html/file_module_x86_id_222.html

io_write_byte:
    push ebp
    mov ebp, esp

    mov eax, [ebp+12]
    mov edx, [ebp+8]
    out dx, al

    pop ebp
    ret

io_write_word:
    push ebp
    mov ebp, esp

    mov eax, [ebp+12]
    mov edx, [ebp+8]
    out dx, ax

    pop ebp
    ret