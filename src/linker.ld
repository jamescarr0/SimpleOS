ENTRY(_start)
OUTPUT_FORMAT(binary)
SECTIONS
{
    /*  Kernel is loaded 1 megebyte into memory. 1024*1024 = 0x100000 
     *  Sections start at 1mb (0x100000).  When objects are linked the
     * origin will start at 0x100000
     */

    . = 1M;

    .text : 
    {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}