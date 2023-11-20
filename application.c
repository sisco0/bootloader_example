#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Define the memory section for the application code
void application_code()  __attribute__((section(".application")));

void application_code() {
    printf("Welcome to application 3!, correct checksum\n");
    return;
}
