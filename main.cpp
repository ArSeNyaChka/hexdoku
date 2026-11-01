#include <ctime>
#include <iostream>

#include "config.h"

int8_t* field_generate();

int main() {
    const int8_t* field = field_generate();
    for (int8_t i = 0; i < FIELD_SIZE; i++) {
        for (int8_t j = 0; j < FIELD_SIZE; j++) {
            std::cout << (int)field[i * FIELD_SIZE + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
