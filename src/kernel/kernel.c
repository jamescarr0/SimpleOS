/**
 * @file Kernel Entry: Main() function.
 * @date 19/02/2022
 * **Author:** James Carr
 * ## Role
 * Kernel entry point, main() function called from the assembly bootloader.
 */

#include "stdio.h"

void main() {

    clear();
    printf("Welcome to SimpleOS.\n");
    printf("The simple operating system that currently does nothing :-)\n");
    
}