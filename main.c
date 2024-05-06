#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define dx (double)(b - a)/n

// Функции написанные на асемблере
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

int iter;

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
    }

    return next;
}



// метод прямоугоольников подсчёта интегралов
// n - кол-во отрезков разб-я
// a - левая граница, b - правая граница
int rect(double (*f)(double x), double a, double b, double eps) {
    int i = 1, n = 1;
    double x = 0, y = 0, s = 0;// s - площадь
    for(x = a, s = 0, i = 1; i <= n; i++) {
        y = (*f)(x);
        s += y * dx;
        x += dx;
    }
    return s;
}


int main(int argc, char** argv)
{
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
