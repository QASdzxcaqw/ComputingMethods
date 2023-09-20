#include <iostream>
#include <cmath>

namespace task_1 {

    constexpr double epsilon = 1.0e-10; // 1 * 10^{-10}
    constexpr int max_iter_count = 100;

    struct founded_root {
        double root;
        double nev_abs;
        int count_of_iter;

        void print_info() const {
            if (count_of_iter != -1) {
                std::cout << "корень " << root << " найден за " << count_of_iter << " итераций, модуль невязки "
                          << nev_abs << '\n';
            } else {
                std::cout << "не удалось найти корень" << '\n';
            }

        }
    };

    // Определяем нашу функцию f(x) - для варианта 1
    inline double f(double x) {
        return x - 10 * sin(x);
    }

    // Определяем производную f'(x)
    inline double fp(double x) {
        return 1 - 10 * cos(x);
    }

    // Метод половинного деления для отделения корней
    void bisection(double A, double B, founded_root &potential_root) {
        double a = A;
        double b = B;
        double c;

        while ((b - a) >= epsilon) {
            c = (a + b) / 2;
            ++potential_root.count_of_iter;
            if (f(c) == 0.0) {
                break;
            } else if (f(c) * f(a) < 0) {
                b = c;
            } else {
                a = c;
            }
        }

        potential_root.root = (a + b) / 2;
        potential_root.nev_abs = std::abs(f(c));
    }

// Метод Ньютона для уточнения корней
    void newton(double x0, founded_root &potential_root) {
        double x = x0;
        double x_past = x0;
        for (int i = 0; i < max_iter_count; i++) {
            x = x - f(x) / fp(x);
            if (std::abs(x - x_past) < epsilon) {
                potential_root.root = x;
                potential_root.nev_abs = std::abs(f(x));
                potential_root.count_of_iter = i;
                return; // Найден корень
            }
            x_past = x;
        }
        potential_root.count_of_iter = -1; // Возвращаем -1, чтобы показать ошибку
    }

// Модифицированный метод Ньютона для уточнения корней
    void modified_newton(double x0, founded_root &potential_root) {
        double x = x0;
        double x_past = x0;
        double fpx0 = fp(x0);
        for (int i = 0; i < max_iter_count; i++) {
            double fx = f(x);
            x = x - fx / fpx0;
            if (std::abs(x - x_past) < epsilon) {
                potential_root.root = x;
                potential_root.nev_abs = std::abs(f(x));
                return; // Найден корень
            }
            x_past = x;
        }
        potential_root.count_of_iter = -1;
    }

//Метода секущих для уточнения корней
    void secant(double A, double B, founded_root &potential_root) {
        double xkmin1 = A;
        double xk = B;
        double xkplus1 = 0;
        potential_root.count_of_iter = 0;

        while (std::abs(xk - xkmin1) >= epsilon) {
            xkplus1 = xk - f(xk) * (xk - xkmin1) / (f(xk) - f(xkmin1));
            xkmin1 = xk;
            xk = xkplus1;
            ++potential_root.count_of_iter;
        }
        potential_root.root = xkplus1;
        potential_root.nev_abs = std::abs(f(xkplus1));
    }

    void solutionMethod(double start, double end) {
        double x_0 = (start + end) / 2;

        founded_root root = {0, 0, 0};

        std::cout << ", информация о корне: \n";
        std::cout << "Начальное приближение = " << x_0 << '\n';

        bisection(start, end, root);
        std::cout << "Бисекция: ";
        root.print_info();

        newton(x_0, root);
        std::cout << "Ньютон: ";
        root.print_info();

        modified_newton(x_0, root);
        std::cout << "Модифицированны Ньютон: ";
        root.print_info();

        secant(start, end, root);
        std::cout << "Секущие: ";
        root.print_info();

        std::cout << "\n";
    }

    void rootsSeparation(double A, double B, double h) {
        bool check = false;
        std::cout.precision(18); // Для изменения количества знаков у double после запятой

        for (double i = A; i <= B; i += h) {
            if (f(i) * f(i + h) < 0) {
                std::cout << "Отрезок содержаший корень нечтной кратности : [" << i << ", " << i + h << "]";
                solutionMethod(i, i + h); // Уточнение корней разными методами
                check = true;
            }
        }
        if (!check) {
            std::cout << "Корни не найдены";
        }
    }
}

int main() {
    double A, B, h;
    int N;

    std::cout << "Задача - отыскание корней нечётной кратности нелинейного уравнения \n\n";
    // Задаем интервал [A, B]
    std::cout << "Введите начало интервала: ";
    std::cin >> A; // Задайте начало интервала
    std::cout << "Введите конец интервала: ";
    std::cin >> B;// Задайте конец интервала
    std::cout << "Введите N: ";
    std::cin >> N;
    h = (B - A) / N;
    std::cout << "Длина разбиения h = " << h << ", функция \"x - 10*sin(x)\", epsilon = " << task_1::epsilon << "\n\n";

    // Отделение и последующее уточнение корней
    task_1::rootsSeparation(A, B, h);

    return 0;
}
