#include <stdio.h>
#include <math.h>

#define MAX_ITERATIONS 100000

int main(void) {
    double x, eps;

    printf("Введіть аргумент X (-1 < X <= 1): ");
    if (scanf("%lf", &x) != 1) {
        fprintf(stderr, "Помилка: некоректне введення X.\n");
        return 1;
    }

    printf("Введіть точність eps (наприклад, 1e-6): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0.0) {
        fprintf(stderr, "Помилка: точність eps має бути додатним числом.\n");
        return 1;
    }

    // Перевірка області збіжності ряду для ln(1 + X): -1 < X <= 1
    if (x <= -1.0 || x > 1.0) {
        fprintf(stderr, "Помилка: аргумент X = %.6lf не потрапляє в область збіжності (-1 < X <= 1).\n", x);
        return 1;
    }

    double term = x;       // Перший доданок a_1 = X (при n = 1)
    double sum = 0.0;
    int n = 1;
    int iterations = 0;
    int diverged = 0;

    // Накопичення суми, доки поточний доданок за модулем >= eps
    while (fabs(term) >= eps) {
        if (iterations >= MAX_ITERATIONS) {
            printf("\nПопередження: досягнуто ліміт у %d ітерацій! Точність не досягнута.\n", MAX_ITERATIONS);
            diverged = 1;
            break;
        }

        sum += term;
        iterations++;
        n++;

        // Рекурентний перехід: a_n = a_{n-1} * (-X * (n - 1) / n)
        term = term * (-x * (double)(n - 1) / (double)n);
    }

    double exact = log(1.0 + x);
    double abs_error = fabs(exact - sum);
    double rel_error = (exact != 0.0) ? (abs_error / fabs(exact)) * 100.0 : 0.0;

    printf("\n--- Результати обчислень для X = %.6lf, eps = %.2e ---\n", x, eps);
    printf("Обчислена сума ряду:    %.10lf\n", sum);
    printf("Еталонне log(1 + X):    %.10lf\n", exact);
    printf("Абсолютна похибка:      %.10e\n", abs_error);
    printf("Відносна похибка:       %.6lf %%\n", rel_error);
    printf("Витрачено ітерацій:     %d\n", iterations);

    if (diverged) {
        return 2;
    }

    return 0;
}