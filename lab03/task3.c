#include <stdio.h>

#define MAX_LEN 100

int main(void) {
    // Правило N + 1 байт під нуль-термінатор
    char str[MAX_LEN + 1];

    printf("Введіть рядок (до %d символів): ", MAX_LEN);
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Помилка зчитування рядка.\n");
        return 1;
    }

    // Видалення символу нового рядка '\n', якщо fgets його захопив
    int k = 0;
    while (str[k] != '\0') {
        if (str[k] == '\n') {
            str[k] = '\0';
            break;
        }
        k++;
    }

    // Метод двох вказівників (індексів) для видалення цифр за один прохід O(n)
    int read_idx = 0;
    int write_idx = 0;

    while (str[read_idx] != '\0') {
        // Якщо символ НЕ є цифрою ('0'..'9'), записуємо його
        if (str[read_idx] < '0' || str[read_idx] > '9') {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }

    // Обов'язкове встановлення завершального нуль-термінатора
    str[write_idx] = '\0';

    printf("Результат після видалення цифр: \"%s\"\n", str);

    return 0;
}