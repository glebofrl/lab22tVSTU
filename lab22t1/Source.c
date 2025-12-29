#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef double (*Tfun)(double);

double fun1(double);
double fun2(double);
double fun3(double);
void out_rez(Tfun func, double start, double end, double step);
double calculate(Tfun prtf, double* x, int n);


void main() {
	setlocale(LC_CTYPE, "RUS");
	double x;
	printf("Введите x (x > 0): ");
	scanf("%lf", &x);




	printf("Введите конец интервала: ");
	double end;
	scanf("%lf", &end);
	printf("Введите шаг табуляции: ");
	double step;
	scanf("%lf", &step);
	printf("\n");

	int choice;

	printf("\nВыберите функцию для табуляции (1-3): ");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		puts("fun1");
		if (x <= 0) {
			printf("Ошибка: x должен быть больше 0! ");
			break;
		}
		out_rez(fun1, x, end, step);
		break;
	case 2:
		puts("fun2");
		out_rez(fun2, x, end, step);
		break;
	case 3:
		puts("fun3");
		out_rez(fun3, x, end, step);
		break;
	default:
		printf("Неверный выбор функции!\n");
		return 1;
	}


}

double fun1(double x) {

	return (3.0 / 2.0) * log(x);
}

double fun2(double x) {
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

double fun3(double x) {
	double t = (x - 1.0) / (x + 1.0);
	double t_squared = t * t;

	return t * (1.0 + t_squared * (1.0 / 3.0 + t_squared * (1.0 / 5.0 + t_squared * (1.0 / 7.0))));
}

void out_rez(Tfun func, double start, double end, double step) {
	for (double x = start; x <= end + 0.00001; x += step) {
		double result = func(x);
		printf("%9.3lf | %12.6lf\n", x, result);
	}
}
