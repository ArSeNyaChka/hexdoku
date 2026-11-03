//
// Created by senyachka on 02.11.2026.
//

#ifndef HEXDOKU_CONFIG_H
#define HEXDOKU_CONFIG_H
#include <cstdint>

#define DEF_TILE_SIZE 3
typedef uint16_t mask_t;

constexpr int8_t TILE_SIZE = DEF_TILE_SIZE;
constexpr int8_t FIELD_SIZE = TILE_SIZE * TILE_SIZE;
constexpr mask_t NUM_MASK = (1 << FIELD_SIZE) - 1;  // 0x01FF from 9x9

#if DEF_TILE_SIZE < 4
constexpr char KEYMAP[] = "123456789";
#else
constexpr char KEYMAP[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#endif

#endif //HEXDOKU_CONFIG_H
