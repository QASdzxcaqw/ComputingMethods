#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
int m, n;
double a, b, x0;


double f(double x){
    return cos(x) + 2*x;
}

bool compareByDifference( const std::pair<double, double>& target1, const std::pair<double, double>& target2) {
    return std::abs(target1.first - x0) < std::abs(target2.first - x0);
}

void fillTable(std::vector<double>& table_x, std::vector<double>& table_y){
    for (int i = 0; i <= m; i++) {
        table_x[i] = a + i * (b - a) / m;
        table_y[i] = f(a + i * (b - a) / m);
    }
}

void sortTableByProximity(std::vector<std::pair<double, double>>& sorted_table,  std::vector<double>& table_x,  std::vector<double>& table_y) {
    for (int i = 0; i <= n; i++) {
        sorted_table[i].first = table_x[i];
        sorted_table[i].second = table_y[i];
    }
    std::sort(sorted_table.begin(), sorted_table.end(), [&](const std::pair<double, double>& target1, const std::pair<double, double>& target2) {
        return compareByDifference(target1, target2);
    });

    sorted_table.resize(n+1);

    std::cout << "Отсортированная таблица (или набор узлов, ближайших к точке x):" << std::endl;
    for (int i = 0; i <= n; i++) {
        std::cout << "x[" << i << "] = " << sorted_table[i].first << ", y[" << i << "] = " << sorted_table[i].second << std::endl;
    }

}

double lagrangeInterpolation(std::vector<std::pair<double, double>>& sorted_table) {
    double result = 0.0;
    for (int i = 0; i <= n; i++) {
        double term = sorted_table[i].second;
        for (int j = 0; j <= n; j++) {
            if (i != j) {
                term *= (x0 - sorted_table[j].first) / (sorted_table[i].first - sorted_table[j].first);
            }
        }
        result += term;
    }
    return result;
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
    std::vector<std::pair<double, double>> sorted_table(m+1);

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

    double lagrangeResult = lagrangeInterpolation(sorted_table);
    std::cout<<"Результат в форме лагранжа: "<<lagrangeResult<<std::endl;

    return 0;
}
