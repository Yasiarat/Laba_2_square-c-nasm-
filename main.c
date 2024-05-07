#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#define dx (double)(b - a)/n
#define MAX_ITER 1000000

// Функции написанные на асемблере
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

int iter = 0;
double eps = 0.001;

// для отладки
double f(double x) {
    double y = 5*x*x-3*x - 4;
    return y;
}

// метод хорд
double method_chord(double prev, double now, double e)
{
    double next = 0;
    double tmp;

    while (abs(next - now) > e) {
        tmp = next;
        next = now - f(now) * (prev - now) / (f(prev) - f(now));
        prev = now;
        now = tmp;
        iter++;
    }

    return next;
}

// поиск тосчки разности функций на [a, b]
double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) {
    double a0 = f(a) - g(a); 
    double b0 = f(b) - g(b); 
    
    // если совпадает с границами
    if (a0 == 0) return a; 
    if (b0 == 0) return b; 
    // если функции одного знака - корня не существует 
    if (a0 * b0 > 0) {
        printf("Корень уравнения f(x) = g(x) на отрезке [%.3lf, %.3lf] не существует или не изолирован.\n", a, b);
        return 0.0/0.0; // NONE
    }
    
    double r = method_chord(a0, b0, eps1); 
    
    // Если потребовалось слишком большое кол-во итераций, то
	// задан неоптимальный отрезок
    	if (iter >= MAX_ITER) {
		printf("Поиск корня уравнения f(x) - g(x) = 0 на отрезке ");
		printf("[%.2lf, %.2lf] занял слишком много времени.\n", a0, b0);
		iter = 0; 
		return 0.0/0.0;
	}

	return r;
}

// метод прямоугоольников подсчёта интегралов
// n - кол-во отрезков разб-я
// a - левая граница, b - правая граница
int integ(double (*f)(double x), double a, double b, double eps1) {
    int i = 1, n = 1;
    double x = 0, y = 0, s = 0;// s - площадь
    double err = eps + 1.0; 
    for(x = a, s = 0, i = 1; i <= n; i++) {
        if (err > eps / 2) break; 
        y = (*f)(x);
        s += y * dx;
        x += dx;
    }
    return s;
}

// функция площади фигуры
double area(int flag_x) {
    double eps1 = eps/10.0; 
    // считаем границы
    double r13 = root(f1, f3, -3.0, -2.0, eps1); 
    double r12 = root(f1, f2, 1.0, 2.0, eps1); 
    double r23 = root(f2, f3, 0.5, 1.0, eps1); 
    
    if (flag_x)
		printf("Абсциссы точек пересечения кривых:\n\tf1 и f2: %.5lf,\n\tf1 и f3: %.5lf,\n\tf2 и f3: %.5lf\n", r12, r13, r23);
    // Значения интегралв ф-ий на нужных отрезках
	double inf1 = integ(f1, r13, r12, eps1);
	double inf2 = integ(f2, r23, r12, eps1);
	double inf3 = integ(f3, r13, r23, eps1);

	double area = inf1 - (inf2 + inf3); // нужная часть
	return area;
}

int main(int argc, char** argv)
{   
    // Для корректного вывода кириллицы в консоль
	setlocale(LC_ALL, ".UTF-8");
	
	// Программа вызвана без параметров
	if (argc == 1) {
		
		return -1;
	}
	
    double x0 = 3;
    double x1 = 10;
    double e = 0.03;
    double x = method_chord(x0, x1, e);
    printf("%f", x);

    return 0;
}

// стартовый вывод
void start(void) {
    printf("\t\t Доброго времени суток! \n   Вы находитесь в проекте Ратовой Ярославы, студента 105 группы ВМК МГУ:\n");
    printf("\t\t 'СРАВНЕНИЕ СОРТИРОВОК' \n ");
    printf("\n");
    printf("\t Не знаете, как пользоваться? - Не проблема!\n");
    printf("  Введите '--help' или просто '-H' и Вам высветится справка.\n");
    printf("  Будьте внимательны: ключ '--help' не используется в сочетании с другими ключами!!!\n");
    printf("\n");
    printf("\tНемного о том, что происходит:\n");
    printf("  В программе реализованы две сортировки: быстрая и выбором\n");
    printf("  Здесь сортируются числа двойной точности\n");
    printf("  Числа упорядочиваются по невозрастанию модулей, т.е. при сравнении элементов не учитывается знак.\n");
    printf("  После выполнения сортировки программа выведет число сравнений и обменов элементов массива\n");

}

// справка
void help(void) {
    printf("\t\tВот справка:\n  1) --dim (-D) - размер массива. По умолчанию 100\n");
    printf("  2) --arr (-A) |1|2|3|4|- вид входного массива. По умолчанию 1\n");
    printf("\tВ качестве аргумента принимает число от 1 до 4:\n");
    printf("\t 1 - элементы упорядочены\n");
    printf("\t 2 - элементы упорядочены в обратном порядке\n");
    printf("\t 3 - случайный порядок элементов\n");
    printf("\t 4 - случайный порядок элементов, но не как в предыдущем\n");
    printf("  3) --sort (-S) |1|2| - вид сортировки. По умолчанию 1\n");
    printf("\tВ качестве аргумента принимает числа 1 или 2:\n");
    printf("\t 1 - сортировка выбором\n");
    printf("\t 2 - быстрая сортировка\n");
    printf("  4) --print (-P) |0|1| - выводит отсортированный массив. По умолчанию 0\n");
    printf("\tВ качестве аргумента принимает числа 0 или 1:\n");
    printf("\t 0 - не выводить\n");
    printf("\t 1 - вывести массив\n");
    printf("\n");
    printf("  Пример ввода:\n");
    printf("\t --dim 10 -A 2 - выполнит сортировку 10 элементов, упорядоченных по невозрастанию\n");
    printf("\n");
    printf("\t\t Пользуйтесь на здоровье!\n");
}
