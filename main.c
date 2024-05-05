#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define dx (double)(b - a)/n

// Функции написанные на асемблере
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

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
int rect(int n, double a, double b) {
    int i = 1;
    double x = 0, y = 0, s = 0;
    for(x = a, s = 0, i = 1; i <= n; i++) {
        y = f(x);
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
