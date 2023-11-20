#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Expected CRC32 checksum (calculate this checksum based on your application)
uint32_t expected_crc32 __attribute__((section(".sig"))) = 0xCAFEBABE;

extern uint8_t __start_application[];
extern uint8_t __stop_application[];
extern uint8_t __start_rodata[];
extern uint8_t __stop_rodata[];

// Function to calculate the CRC32 checksum of a memory section
uint32_t calculate_crc32() {
    uint32_t crc = crc32(0L, Z_NULL, 0);
    uint32_t application_size = __stop_application-__start_application;
    uint32_t rodata_size = __stop_rodata-__start_rodata;
    crc = crc32(crc, __start_application, application_size);
    crc = crc32(crc, __start_rodata, rodata_size);
    return crc;
}

// Function to verify the CRC32 checksum of a memory section
int verify_crc32(uint32_t expected_crc32) {
    uint32_t actual_crc32 = calculate_crc32();
    if (actual_crc32 != expected_crc32)
    {
	printf("Actual CRC:\t0x%X\nExpected CRC:\t0x%X\n",actual_crc32,expected_crc32);
    }
    return actual_crc32 == expected_crc32;
}

// Entry point of the bootloader
void main() {
    printf("%X - %X\n",__start_application, __stop_application);
    // Memory section to be verified (adjust the address and size accordingly)
    // Verify the CRC32 checksum
    if (verify_crc32(expected_crc32)) {
        // CRC32 verification passed, jump to the application
        void (*application_entry_point)() = (void (*)())__start_application;
        application_entry_point();
    } else {
	printf("Checksum is not valid.\n");
	return;
    }
}

