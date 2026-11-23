#include <stdio.h>
#include <stdint.h>

// Прототипи функцій пакування та розпакування
uint16_t pack_telemetry(uint8_t light_level, uint8_t relay_on, uint8_t device_id);
void unpack_telemetry(uint16_t packet, uint8_t *light_level, uint8_t *relay_on, uint8_t *device_id);

int main(void) {
    // Вихідні дані телеметрії
    uint8_t orig_light = 85;      // 0..100 (7 біт)
    uint8_t orig_relay = 1;       // 0..1   (1 біт)
    uint8_t orig_dev_id = 0xA4;   // 0..255 (8 біт, 164 у десятковій)

    printf("=== Вихідні параметри ===\n");
    printf("Рівень освітленості : %u\n", orig_light);
    printf("Реле увімкнено      : %u\n", orig_relay);
    printf("ID пристрою         : %u (0x%02X)\n", orig_dev_id, orig_dev_id);

    // Пакування у 16-бітне слово
    uint16_t telemetry_word = pack_telemetry(orig_light, orig_relay, orig_dev_id);
    printf("\n=== Сформований пакет ===\n");
    printf("HEX: 0x%04X (DEC: %u)\n", telemetry_word, telemetry_word);

    // Розпакування назад у змінні
    uint8_t unpacked_light = 0;
    uint8_t unpacked_relay = 0;
    uint8_t unpacked_dev_id = 0;

    unpack_telemetry(telemetry_word, &unpacked_light, &unpacked_relay, &unpacked_dev_id);

    printf("\n=== Відновлені параметри ===\n");
    printf("Рівень освітленості : %u\n", unpacked_light);
    printf("Реле увімкнено      : %u\n", unpacked_relay);
    printf("ID пристрою         : %u (0x%02X)\n", unpacked_dev_id, unpacked_dev_id);

    // Перевірка ідентичності
    if (orig_light == unpacked_light && orig_relay == unpacked_relay && orig_dev_id == unpacked_dev_id) {
        printf("\nСтатус: Дані повністю ідентичні!\n");
    }

    return 0;
}

uint16_t pack_telemetry(uint8_t light_level, uint8_t relay_on, uint8_t device_id) {
    uint16_t packet = 0;
    // Накладаємо маски для захисту від переповнення розрядної сітки
    packet |= ((uint16_t)(light_level & 0x7F) << 0);  // Біти 0..6
    packet |= ((uint16_t)(relay_on & 0x01) << 7);     // Біт 7
    packet |= ((uint16_t)(device_id & 0xFF) << 8);    // Біти 8..15
    return packet;
}

void unpack_telemetry(uint16_t packet, uint8_t *light_level, uint8_t *relay_on, uint8_t *device_id) {
    if (light_level != NULL) {
        *light_level = (packet >> 0) & 0x7F;
    }
    if (relay_on != NULL) {
        *relay_on = (packet >> 7) & 0x01;
    }
    if (device_id != NULL) {
        *device_id = (packet >> 8) & 0xFF;
    }
}