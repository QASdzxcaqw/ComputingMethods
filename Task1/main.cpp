#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>


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

void solutionMethod(double start, double end){
    double x_0 = start + end / 2;
    double root1 = bisection(start, end, 0.0001);
    double root2 = newton(x_0, 0.0001, 100);
    std::cout<<"Корень по методу бисекции: "<< root1<<"\n";
    std::cout<<"Корень по методу Ньютона: "<<root2<<"\n";
}

void rootsSeparation(double A, double B, double h ){
    bool check = false;
    for(double i  = A; i <= B; i += h){
        if( f(i) * f(i + h) < 0){
            std::cout<<"Отрезок содержаший корень нечтной кратности : ["<< i << ", "<< i+h<<"]" <<"\n";
            solutionMethod(i, i+h);
            check = true;
        }
    }
    if (!check){
        std::cout<<"Корень не найден";
    }
}

int main() {
    double A, B, h;
//    double epsilon = 0.0001; // Точность
//    int max_iterations = 100; // Максимальное количество итераций для метода Ньютона
    int N;
    // Задаем интервал [A, B]
    std::cout<<"Введите начало интервала: ";
    std::cin>>A; // Задайте начало интервала
    std::cout<<"Введите конец интервала: ";
    std::cin>>B;// Задайте конец интервала
    std::cout<<"Введите N: ";
    std::cin>>N;
    h = (B - A) / N;
    std::cout<<"Длина разбиения h = "<< h;
    std::cout<<"\n";
    // Отделение корней
    rootsSeparation(A, B, h);
    //double root = bisection(A, B, epsilon);

    //std::cout<<"Неуточненный: "<<root<<"\n";



    return 0;
}
