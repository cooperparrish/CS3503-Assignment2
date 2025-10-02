#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

void oct_to_bin(const char* oct, char* out) {
    int pos = 0;
    while (*oct) {
        int digit = *oct - '0';
        if (digit < 0 || digit > 7) {
            strcpy(out, "Invalid octal input");
            return;
        }
        out[pos++] = ((digit >> 2) & 1) ? '1' : '0';
        out[pos++] = ((digit >> 1) & 1) ? '1' : '0';
        out[pos++] = ((digit >> 0) & 1) ? '1' : '0';
        oct++;
    }
    out[pos] = '\0';
}

void oct_to_hex(const char* oct, char* out) {
    char bin[100] = { 0 };
    oct_to_bin(oct, bin);

    size_t len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;

    char padded_bin[104] = { 0 };
    memset(padded_bin, '0', pad);
    strncpy(padded_bin + pad, bin, 104 - pad - 1);
    padded_bin[103] = '\0';

    int hex_pos = 0;
    for (int i = 0; i < (int)strlen(padded_bin); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; ++j) {
            val = (val << 1) | (padded_bin[i + j] - '0');
        }
        out[hex_pos++] = (val < 10) ? (val + '0') : (val - 10 + 'A');
    }
    out[hex_pos] = '\0';
}

void hex_to_bin(const char* hex, char* out) {
    int pos = 0;
    while (*hex) {
        char c = *hex;
        int val;

        if (isdigit(c)) val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;
        else {
            strcpy(out, "Invalid hex input");
            return;
        }

        out[pos++] = ((val >> 3) & 1) ? '1' : '0';
        out[pos++] = ((val >> 2) & 1) ? '1' : '0';
        out[pos++] = ((val >> 1) & 1) ? '1' : '0';
        out[pos++] = ((val >> 0) & 1) ? '1' : '0';
        hex++;
    }
    out[pos] = '\0';
}

// extra function to reuse 
void to_32bit_binary(uint32_t value, char* out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_sign_magnitude(int32_t n, char* out) {
    uint32_t magnitude = (n < 0) ? (uint32_t)(-n) : (uint32_t)n;
    uint32_t result = magnitude & 0x7FFFFFFF;
    if (n < 0) {
        result |= 0x80000000;
    }
    to_32bit_binary(result, out);
}

void to_ones_complement(int32_t n, char* out) {
    uint32_t result;
    if (n >= 0) {
        result = (uint32_t)n;
    }
    else {
        result = ~((uint32_t)(-n));
    }
    to_32bit_binary(result, out);
}

void to_twos_complement(int32_t n, char* out) {
    uint32_t result = (uint32_t)n;
    to_32bit_binary(result, out);
}

