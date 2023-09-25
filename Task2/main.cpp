#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm>
int m, n;
static double a, b, x0;


double f(double x){
    return cos(x) + 2*x;
};

void fillTable(std::vector<double>& table_x, std::vector<double>& table_y){
    for (int i = 0; i <= m; i++) {
        table_x[i] = a + i * (b - a) / m;
        table_y[i] = f(a + i * (b - a) / m);
    }
};

void sortTableByProximity(std::vector<std::pair<double, double>>& sorted_table, const std::vector<double>& table_x, const std::vector<double>& table_y) {
    for (int i = 0; i <= m; i++) {
        sorted_table.push_back({std::abs(table_x[i] - x0), table_y[i]});
    }
    std::sort(sorted_table.begin(), sorted_table.end());
}


int main() {
    std::cout << "Задача алгебраического интерполирования" << std::endl;

    // Ввод параметров задачи

    std::cout << "Введите число значений в таблице (m+1): ";
    std::cin >> m;
    std::cout << "Введите концы отрезка [a, b]: ";
    std::cin >> a >> b;

    std::vector<double> table_x(m + 1);
    std::vector<double> table_y(m + 1);
    std::vector<std::pair<double, double>> sorted_table(m + 1);

    // Ввод точки интерполирования x
    std::cout << "Введите точку интерполирования x0: ";
    std::cin >> x0;

    // Ввод степени интерполяционного многочлена n (n <= m)
    std::cout << "Введите степень интерполяционного многочлена n (n <= m): ";
    std::cin >> n;

    if (n > m) {
        std::cout << "Введено недопустимое значение n." << std::endl;
        return 1;
    }

    fillTable(table_x, table_y);
    sortTableByProximity(sorted_table, table_x, table_y);

    // Вывод результатов
    std::cout << "Отсортированная таблица (или набор узлов, ближайших к точке x):" << std::endl;
    for (int i = 0; i <= n; i++) {
        std::cout << "x[" << i << "] = " << sorted_table[i].second << ", y[" << i << "] = " << sorted_table[i].second << std::endl;
    }
    return 0;
}
