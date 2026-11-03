//
// Created by senyachka on 02.11.2026.
//

#include <cstdint>
#include <cstring>
#include <ctime>
#include <random>

#include "config.h"


template <typename IndexFn>
mask_t get_mask(const int8_t *field, IndexFn index) {
    mask_t mask = NUM_MASK;
    for (int8_t i = 0; i < FIELD_SIZE; i++)
        if (const int8_t v = field[index(i)]; v != -1) mask ^= 1 << v;
    return mask;
}

mask_t get_row_mask(const int8_t row, const int8_t *field) {
    return get_mask(field, [=](const int8_t i){ return row * FIELD_SIZE + i; });
}
mask_t get_col_mask(const int8_t col, const int8_t *field) {
    return get_mask(field, [=](const int8_t i){ return i * FIELD_SIZE + col; });
}

mask_t get_tile_mask(const int8_t row, const int8_t col, const int8_t *field) {
    mask_t mask = NUM_MASK;
    for (int8_t r = TILE_SIZE*(row/TILE_SIZE); r < TILE_SIZE*(row/TILE_SIZE+1); r++)
        for (int8_t c = TILE_SIZE*(col/TILE_SIZE); c < TILE_SIZE*(col/TILE_SIZE+1); c++)
            if (const int8_t v = field[r * FIELD_SIZE + c]; v != -1) mask ^= 1 << v;
    return mask;
}

int8_t cell_generate(const int8_t row, const int8_t col, const int8_t *field) {
    const mask_t mask = get_row_mask(row, field) & get_col_mask(col, field) & get_tile_mask(row, col, field);
    if (mask == 0) return -1;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int8_t> dis(0, FIELD_SIZE-1);

    for (;;) {
        if (const int8_t random_num = dis(gen); mask & (1 << random_num)) return random_num;
    }
}

bool tile_generate(const int8_t row, const int8_t col, int8_t *field) {
    for (int8_t r = TILE_SIZE*row; r < TILE_SIZE*row+TILE_SIZE; r++)
        for (int8_t c = TILE_SIZE*col; c < TILE_SIZE*col+TILE_SIZE; c++)
            field[r * FIELD_SIZE + c] = -1;
    for (int8_t r = TILE_SIZE*row; r < TILE_SIZE*row+TILE_SIZE; r++) {
        for (int8_t c = TILE_SIZE*col; c < TILE_SIZE*col+TILE_SIZE; c++) {
            const int8_t value = cell_generate(r, c, field);
            if (value == -1) return false;
            field[r * FIELD_SIZE + c] = value;
        }
    } return true;
}

int8_t* solve_field(const int8_t *field) {
    int8_t *local_field = new int8_t[FIELD_SIZE*FIELD_SIZE];
    int8_t *req_field = nullptr;
    bool is_complete = true;
    std::memcpy(local_field, field, FIELD_SIZE*FIELD_SIZE*sizeof(int8_t));

    for (int8_t row = 0; row < FIELD_SIZE && is_complete; row++) {
        for (int8_t col = 0; col < FIELD_SIZE && is_complete; col++) {
            if (local_field[row * FIELD_SIZE + col] != -1) continue;
            is_complete = false;
            const mask_t mask = get_row_mask(row, field) & get_col_mask(col, field) & get_tile_mask(row, col, field);
            if (mask == 0) goto exit;
            for (int8_t value = 0; value < FIELD_SIZE; value++) {
                if (!(mask & (1 << value))) continue;
                local_field[row * FIELD_SIZE + col] = value;
                req_field = solve_field(local_field);
                if (req_field != nullptr) goto exit;
            }
        }
    } if (is_complete) return local_field;
exit:
    delete[] local_field;
    return req_field;
}

int8_t* field_generate() {
    int8_t* field = new int8_t[FIELD_SIZE*FIELD_SIZE];
    for (mask_t i = 0; i < FIELD_SIZE*FIELD_SIZE; i++) field[i] = -1;

    tile_generate(0, 0, field);

    for (int8_t k = 0; k < 2; k++) for (int8_t i = 1; i < TILE_SIZE; i++)
        if (k) for (bool f = true; f;) f = !tile_generate(0, i, field); else for (bool f = true; f;) f = !tile_generate(i, 0, field);

    int8_t *result_field = solve_field(field);

    delete[] field;
    return result_field;
}
