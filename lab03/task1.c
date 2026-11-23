#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

int main(void) {
    int arr[SIZE];
    int a, b;

    srand((unsigned int)time(NULL));

    // Заповнення масиву випадковими числами [-50; 50]
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 101 - 50;
    }

    printf("Вихідний масив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n\n");

    // Введення меж діапазону [A, B]
    printf("Введіть межі діапазону A та B (через пробіл): ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Помилка вводу.\n");
        return 1;
    }

    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // 1. Підрахунок елементів у діапазоні [A, B] та пошук індексу максимального
    int count_in_range = 0;
    int max_val = arr[0]; // Обов'язкова ініціалізація нульовим елементом
    int max_idx = 0;

    for (int i = 0; i < SIZE; i++) {
        if (arr[i] >= a && arr[i] <= b) {
            count_in_range++;
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_idx = i;
        }
    }

    // 2. Реверс елементів після першого максимального (in-place)
    int left = max_idx + 1;
    int right = SIZE - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }

    printf("\nКількість елементів у діапазоні [%d; %d]: %d\n", a, b, count_in_range);
    printf("Максимальний елемент: %d (індекс %d)\n", max_val, max_idx);

    printf("\nПеретворений масив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");

    return 0;
}