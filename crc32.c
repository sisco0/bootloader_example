#include <stdint.h>
#include <stddef.h>

// CRC32 Polynomial (Standard IEEE 802.3)
#define CRC32_POLY 0xEDB88320

// Function to calculate CRC32 checksum
uint32_t calculateCRC32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF; // Initial CRC value

    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i]; // XOR with incoming byte

        for (int j = 0; j < 8; ++j) {
            // Check the least significant bit
            if (crc & 1) {
                crc = (crc >> 1) ^ CRC32_POLY; // If it's 1, perform XOR with polynomial
            } else {
                crc >>= 1; // If it's 0, just shift
            }
        }
    }

    // Finalize the CRC value (invert or XOR with a fixed value)
    return crc ^ 0xFFFFFFFF;
}

// Example usage
#include <stdio.h>

int main() {
    // Example data
    const uint8_t data[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    size_t dataLength = sizeof(data) / sizeof(data[0]);

    // Calculate CRC32
    uint32_t crc32Result = calculateCRC32(data, dataLength);

    // Print the result
    printf("CRC32: 0x%08X\n", crc32Result);

    return 0;
}

