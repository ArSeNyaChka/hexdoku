//
// Created by senyachka on 02.11.2026.
//

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>

#include "config.h"


template <typename IndexFn>
uint16_t get_mask(const int8_t *field, IndexFn index) {
    uint16_t mask = 0xFFFF;
    for (int8_t i = 0; i < FIELD_SIZE; i++)
        if (const int8_t v = field[index(i)]; v != -1) mask ^= 1 << v;
    // std::cout << "mask: " << (int)mask << std::endl;
    return mask;
}

uint16_t get_row_mask(const int8_t row, const int8_t *field) {
    // std::cout << "row" << std::endl;
    return get_mask(field, [=](const int8_t i){ return row * FIELD_SIZE + i; });
}
uint16_t get_col_mask(const int8_t col, const int8_t *field) {
    // std::cout << "col" << std::endl;
    return get_mask(field, [=](const int8_t i){ return i * FIELD_SIZE + col; });
}

uint16_t get_tile_mask(const int8_t row, const int8_t col, const int8_t *field) {
    // std::cout << "tile" << std::endl;
    uint16_t mask = 0xFFFF;
    for (int r = TILE_SIZE*(row/TILE_SIZE); r < TILE_SIZE*(row/TILE_SIZE+1); r++)
        for (int c = TILE_SIZE*(col/TILE_SIZE); c < TILE_SIZE*(col/TILE_SIZE+1); c++)
            if (field[r * TILE_SIZE + c] != -1) mask ^= 1 << r;
    // std::cout << "tile mask: " << (int)mask << std::endl;
    return mask;
}

int8_t cell_generate(const int8_t row, const int8_t column, const int8_t *field) {
    const uint16_t mask = get_row_mask(row, field) & get_col_mask(column, field) & get_tile_mask(row, column, field);
    std::srand(std::time(nullptr));
    // std::cout << "mask: " << (int)mask << std::endl;
    for (int i = 0; i < FIELD_SIZE*10; i++) {
        if (const int8_t random_num = std::rand() % FIELD_SIZE; mask & (1 << random_num)) return random_num;
    } return -1;
}

int8_t* field_generate() {
    int8_t* field = new int8_t[FIELD_SIZE*FIELD_SIZE];
    int attempt = 0;  // debah
regenerate:
    attempt++;  // debah
    for (uint16_t i = 0; i < FIELD_SIZE*FIELD_SIZE; i++) field[i] = -1;

    for (int8_t row = 0; row < FIELD_SIZE; row++) {
        for (int8_t col = 0; col < FIELD_SIZE; col++) {
            const int8_t value = cell_generate(row, col, field);
            if (value == -1) goto regenerate;
            field[row*FIELD_SIZE + col] = value;
            // std::cout << (int) row << " " << (int) col << std::endl;
        }
    }

    std::cout << "generating... (" << attempt << ")" << std::endl;
    return field;
}
