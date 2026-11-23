#include <stdio.h>
#include <math.h>

int main(void) {
    double x_start, x_end, dx;

    printf("Введіть початкове значення X_start: ");
    if (scanf("%lf", &x_start) != 1) {
        fprintf(stderr, "Помилка: некоректне введення X_start.\n");
        return 1;
    }

    printf("Введіть кінцеве значення X_end: ");
    if (scanf("%lf", &x_end) != 1) {
        fprintf(stderr, "Помилка: некоректне введення X_end.\n");
        return 1;
    }

    printf("Введіть крок табулювання dX: ");
    if (scanf("%lf", &dx) != 1) {
        fprintf(stderr, "Помилка: некоректне введення dX.\n");
        return 1;
    }

    // Валідація вхідних параметрів
    if (x_start >= x_end || dx <= 0.0) {
        fprintf(stderr, "Помилка: необхідно, щоб виконувались умови X_start < X_end та dX > 0.\n");
        return 1;
    }

    printf("\n+--------------+----------------+\n");
    printf("|      X       |      Y(X)      |\n");
    printf("+--------------+----------------+\n");

    // Додаємо малий допуск (dx * 1e-9), щоб уникнути втрати крайньої правої точки через похибку double
    for (double x = x_start; x <= x_end + dx * 1e-9; x += dx) {
        double y;

        if (x < 0.0) {
            y = x * x * x;
        } else if (x <= 3.14159) {
            y = sin(x);
        } else {
            y = -1.0;
        }

        if (!isfinite(y)) {
            printf("| %12.4lf | [Не визначено] |\n", x);
        } else {
            printf("| %12.4lf | %14.6lf |\n", x, y);
        }
    }

    printf("+--------------+----------------+\n");

    return 0;
}