#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <time.h>


typedef double (*TFunc)(double);

typedef struct {
    double x;
    double y;
} Point;

double S(double x) {
    double t = (x - 1.0) / (x + 1.0);
    double t_squared = t * t;

    return t * (1.0 + t_squared * (1.0 / 3.0 + t_squared * (1.0 / 5.0 + t_squared * (1.0 / 7.0))));
}
double V(double x) {
    if (x > 1.0) {
        double arg = x * x - 1.0;
        double tan_val = tan(arg);

        if (tan_val < 0) {
            return 0;
        }
        return sqrt(tan_val);
    }
    else if (x <= 1 && x >= 0) {
        return -2.0 * x;
    }
    else {
        return exp(cos(x));
    }
}
double Y(double x) {
    return (3.0 / 2.0) * log(x);
}

double goldenSectionMax(TFunc f, double a, double b, double tol) {
    const double phi = (1 + sqrt(5)) / 2;
    double c = b - (b - a) / phi;
    double d = a + (b - a) / phi;
    while (fabs(c - d) > tol) {
        if (f(c) < f(d)) a = c; else b = d;
        c = b - (b - a) / phi;
        d = a + (b - a) / phi;
    }
    return (b + a) / 2;
}

TFunc selectFunction() {
    int choice;
    printf("Выберите функцию:\n1 - S(x)\n2 - V(x)\n3 - Y(x)\nВаш выбор: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1: return S;
    case 2: return V;
    case 3: return Y;
    default: printf("Неверный выбор, выбрана S(x)\n"); return S;
    }
}

void writeToFile(TFunc f) {
    double x0, x1, step;
    printf("Введите интервал через пробел и шаг: ");
    scanf("%lf %lf %lf", &x0, &x1, &step);
    FILE* fp = fopen("dat.txt", "w");
    if (!fp) {
        printf("Ошибка открытия файла!\n"); 
        return; 
    }
    for (double x = x0; x <= x1; x += step) {
        fprintf(fp, "%lf,%lf\n", x, f(x));
    }
    fclose(fp);
    printf("Данные записаны в dat.txt\n");
}

void readFromFile(TFunc f) {
    FILE* fp = fopen("dat.txt", "r");
    if (!fp) { 
        printf("Ошибка открытия файла!\n");
        return; 
    }
    double x;
    char comma;
    while (fscanf(fp, "%lf%c", &x, &comma) == 2) {
        printf("x=%lf, f(x)=%lf\n", x, f(x));
    }
    fclose(fp);
}

void tabulate(TFunc f) {
    double x0, x1, step;
    printf("Введите интервал через пробел и шаг: ");
    scanf("%lf %lf %lf", &x0, &x1, &step);
    for (double x = x0; x <= x1; x += step) {
        printf("x=%lf, f(x)=%lf\n", x, f(x));
    }
}

void sumMaxMin(TFunc f) {
    double x0, x1, step;
    printf("Введите интервал x0 x1 и шаг: ");
    scanf("%lf %lf %lf", &x0, &x1, &step);

    double min = f(x0), max = f(x0);
    for (double x = x0; x <= x1; x += step) {
        double y = f(x);
        if (y < min) min = y;
        if (y > max) max = y;
    }
    printf("Минимум = %lf, Максимум = %lf\n", min, max);
    printf("Сумма максимума и минимума = %lf\n", min + max);
}

int main() {
    setlocale(LC_CTYPE, "RUS");

    int choice;
    while (1) {
        printf("МЕНЮ:\n");
        printf("1. Вычислить значение функции\n");
        printf("2. Табулировать функцию\n");
        printf("3. Выполнить операцию\n");
        printf("4. Сумма максимума и минимума функции\n");
        printf("5. Выход\n");
        scanf("%d", &choice);

        if (choice == 5) return 0;

        TFunc f;
        double x;
        switch (choice) {
        case 1:
            f = selectFunction();
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f(x)=%lf\n", f(x));
            break;
        case 2:
            f = selectFunction();
            tabulate(f);
            break;
        case 3:
            f = selectFunction();
            printf("Операции:\n1 - Записать в файл\n2 - Вычислить из файла\n3 - Найти максимум\nВыбор: ");
            int op;
            scanf("%d", &op);
            if (op == 1) writeToFile(f);
            else if (op == 2) readFromFile(f);
            else if (op == 3) {
                double a, b;
                printf("Введите интервал a b: ");
                scanf("%lf %lf", &a, &b);
                double xmax = goldenSectionMax(f, a, b, 1e-5);
                printf("Максимум f(x) на интервале [%lf,%lf] достигается в x=%lf, f(x)=%lf\n", a, b, xmax, f(xmax));
            }
            break;
        case 4:
            f = selectFunction();
            sumMaxMin(f);
            break;
        default:
            printf("Неверный выбор\n");
        }
    }
    return 0;
}
