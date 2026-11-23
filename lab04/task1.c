#include <stdio.h>

// Прототипи функцій (обов'язково перед main)
double celsius_to_fahrenheit(double celsius, int *neg_count);
void print_result(double celsius, double fahrenheit, int neg_count);

int main(void) {
    double c_temp;
    int negative_calls = 0;

    printf("=== Конвертер температури (C -> F) ===\n");
    printf("Введіть температуру в градусах Цельсія (або букву для виходу):\n");

    // Інтерфейсна логіка: введення, виклик підпрограм та друк
    while (printf("\nТемпература (°C): ") && scanf("%lf", &c_temp) == 1) {
        double f_temp = celsius_to_fahrenheit(c_temp, &negative_calls);
        print_result(c_temp, f_temp, negative_calls);
    }

    printf("\nРоботу завершено. Всього введено від'ємних температур: %d\n", negative_calls);
    return 0;
}

// Підпрограма розрахунку: приймає температуру за значенням (Pass-by-Value)
double celsius_to_fahrenheit(double celsius, int *neg_count) {
    // Статична змінна зберігає стан між викликами без глобальних змінних
    static int negative_temp_counter = 0;

    if (celsius < 0.0) {
        negative_temp_counter++;
    }

    // Передаємо актуальне значення лічильника назовні для відображення
    if (neg_count != NULL) {
        *neg_count = negative_temp_counter;
    }

    return (celsius * 9.0 / 5.0) + 32.0;
}

void print_result(double celsius, double fahrenheit, int neg_count) {
    printf("Результат: %.2f °C = %.2f °F\n", celsius, fahrenheit);
    printf("Лічильник викликів з від'ємною температурою (static): %d\n", neg_count);
}