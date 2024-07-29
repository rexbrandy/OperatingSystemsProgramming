#include<stdio.h>
#include<stdint.h>
#include"bits.h"

void print_bits(uint8_t value)
{
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

uint8_t reverse_bits(uint8_t value)
{
    uint8_t reversed = 0;
    for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

uint8_t check_bit(uint8_t value, uint8_t bit)
{
    return (value & (1 << bit)) != 0;
}

uint8_t toggle_bit(uint8_t *value, uint8_t bit)
{
    return (*value ^= (1 << bit));
}

uint8_t get_subfield(uint8_t value, uint8_t start, uint8_t stop)
{
    uint8_t mask = ((1 << (stop - start + 1)) - 1) << start;
    return ((value & mask) >> start);
}