#include <ctime>
#include <iostream>
#include <chrono>

#include "config.h"

int8_t* field_generate();



int main() {
    auto start = std::chrono::steady_clock::now();
    const int8_t* field = field_generate();
    auto end = std::chrono::steady_clock::now();

    // Вычисляем разницу
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Время выполнения: " << duration.count() << " мс\n";


    for (int8_t i = 0; i < FIELD_SIZE; i++) {
        if (i % TILE_SIZE == 0) {
            for (int j = 0; j < FIELD_SIZE*4+1; j++) std::cout << "═";
            std::cout << std::endl;
        }
        for (int8_t j = 0; j < FIELD_SIZE; j++) {
            std::cout << (j % TILE_SIZE ? "│" : "║" ) << " " << KEYMAP[field[i * FIELD_SIZE + j]] << " ";
        }
        std::cout << " ║"<< std::endl;
    }

    return 0;
}
