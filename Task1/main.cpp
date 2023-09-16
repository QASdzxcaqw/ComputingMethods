#include <iostream>
#include <cmath>
#include <windows.h>
// Определяем нашу функцию f(x)
double f(double x) {
    return x*x*x-3*x-5;
    // Здесь опишите вашу функцию
    // Пример: return x*x - 4; для уравнения x^2 = 4
}

// Метод половинного деления для отделения корней
double bisection(double A, double B, double epsilon) {
    double a = A;
    double b = B;
    double c;

    if (f(a) * f(b) >= 0) {
        std::cout << "Не удовлетворяет условию: f(a) * f(b) должно быть < 0" << std::endl;
        return 0.0; // Возвращаем ноль, чтобы показать ошибку
    }

    while ((b - a) >= epsilon) {
        c = (a + b) / 2;
        if (f(c) == 0.0) {
            return c; // Найден корень
        } else if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return (a + b) / 2;
}

// Метод Ньютона для уточнения корней
double newton(double x0, double epsilon, int max_iterations) {
    double x = x0;
    for (int i = 0; i < max_iterations; i++) {
        double fx = f(x);
        double fpx = (f(x + epsilon) - fx) / epsilon;
        x = x - fx / fpx;
        if (std::abs(f(x)) < epsilon) {
            return x; // Найден корень
        }
    }
    return 0.0; // Возвращаем ноль, чтобы показать ошибку
}

int main() {
    double A, B;
    double epsilon = 0.0001; // Точность
    int max_iterations = 100; // Максимальное количество итераций для метода Ньютона

    // Задаем интервал [A, B]
    std::cout<<"Введите начало интервала: ";
    std::cin>>A; // Задайте начало интервала
    std::cout<<"Введите конец интервала: ";
    std::cin>>B;// Задайте конец интервала
    std::cout<<"\n";
    // Отделение корней
    double root = bisection(A, B, epsilon);

    std::cout<<"Неуточненный: "<<root<<"\n";

    if (root != 0.0) {
        // Уточнение корней методом Ньютона
        double refined_root = newton(root, epsilon, max_iterations);
        std::cout << "Корень уточненный: " << refined_root << std::endl;

        // Дополнительный контроль и анализ результатов, если необходимо
        // ...

    } else {
        std::cout << "Корень не найден на заданном интервале." << std::endl;
    }

    return 0;
}
