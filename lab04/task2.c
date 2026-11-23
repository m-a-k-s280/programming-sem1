#include <stdio.h>
#include <stdint.h>

// Прототипи функцій
uint32_t set_bit(uint32_t reg, uint8_t bit);
uint32_t clear_bit(uint32_t reg, uint8_t bit);
uint32_t toggle_bit(uint32_t reg, uint8_t bit);
uint8_t check_bit(uint32_t reg, uint8_t bit);
void print_binary(uint32_t reg);

int main(void) {
    // Початковий стан регістра: біт 6 встановлений в 1 (0x00000040), щоб було видно його скидання
    uint32_t gpio_reg = (1U << 6) | (1U << 18);

    printf("Початковий стан регістра:\n");
    print_binary(gpio_reg);

    // 1. Встановити біт 1
    printf("\n1. Встановлення біта 1 (set_bit):\n");
    gpio_reg = set_bit(gpio_reg, 1);
    print_binary(gpio_reg);

    // 2. Скинути біт 6
    printf("\n2. Скидання біта 6 (clear_bit):\n");
    gpio_reg = clear_bit(gpio_reg, 6);
    print_binary(gpio_reg);

    // 3. Інвертувати біт 10 (перший раз: 0 -> 1)
    printf("\n3. Інвертування біта 10 (toggle_bit):\n");
    gpio_reg = toggle_bit(gpio_reg, 10);
    print_binary(gpio_reg);

    // 4. Перевірити стан біта 18
    uint8_t bit18_state = check_bit(gpio_reg, 18);
    printf("\n4. Перевірка стану біта 18 (check_bit): %u\n", bit18_state);

    return 0;
}

uint32_t set_bit(uint32_t reg, uint8_t bit) {
    return reg | (1U << bit);
}

uint32_t clear_bit(uint32_t reg, uint8_t bit) {
    return reg & ~(1U << bit);
}

uint32_t toggle_bit(uint32_t reg, uint8_t bit) {
    return reg ^ (1U << bit);
}

uint8_t check_bit(uint32_t reg, uint8_t bit) {
    return (reg >> bit) & 1U;
}

void print_binary(uint32_t reg) {
    printf("HEX: 0x%08X | BIN: ", reg);
    for (int i = 31; i >= 0; i--) {
        printf("%u", (reg >> i) & 1U);
        if (i % 4 == 0 && i != 0) {
            printf(" "); // Розбиття по 4 біти (нібли)
        }
    }
    printf("\n");
}