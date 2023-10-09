#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
int m, n;
double a, b, x0;


double f(double x){
    return log(x);
}

bool compareByDifference( const std::pair<double, double>& target1, const std::pair<double, double>& target2) {
    return std::abs(target1.first - x0) < std::abs(target2.first - x0);
}


void fillSortTableByProximity(std::vector<std::pair<double, double>>& sorted_table) {
    for (int i = 0; i <= m; i++) {
        sorted_table[i].first = a + i * (b - a) / m;
        sorted_table[i].second = f(a + i * (b - a) / m);
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

double newton_interpolation(std::vector<std::pair<double, double>>& sorted_table) {
    double result = 0.0;

    // Вычисление разделенных разностей
    std::vector<std::vector<double>> divided_diff(n+1, std::vector<double>(n+1, 0.0));
    for (int i = 0; i <= n; i++) {
        divided_diff[i][0] = sorted_table[i].second;
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= n - j; i++) {
            divided_diff[i][j] = (divided_diff[i + 1][j - 1] - divided_diff[i][j - 1]) / (sorted_table[i + j].first - sorted_table[i].first);
        }
    }
//    std::cout<<"Таблица разностей для метода Ньютона:"<<std::endl;
//    for (auto& row :divided_diff){
//        for(auto& cell: row){
//            std::cout <<cell << "\t";
//        }
//        std::cout<<std::endl;
//    }

    // Вычисление интерполяционного значения
    for (int i = 0; i < n; i++) {
        double term = divided_diff[0][i];
        for (int j = 0; j < i; j++) {
            term *= (x0 - sorted_table[j].first);
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

    fillSortTableByProximity(sorted_table);

    // Вывод результатов
    double lagrangeResult = lagrangeInterpolation(sorted_table);
    double newtonResult = newton_interpolation(sorted_table);
    double actualErrorLagrange = std::abs(lagrangeResult - f(x0));
    double actualErrorNewton = std::abs(newtonResult - f(x0));

    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    std::cout<<"Результат в форме лагранжа: "<<lagrangeResult<<std::endl;
    std::cout<<"Результат в форме ньютона: "<<newtonResult<<std::endl;
    std::cout << "Значение абсолютной фактической погрешности для формы Лагранжа: " << actualErrorLagrange << std::endl;
    std::cout << "Значение абсолютной фактической погрешности для формы Ньютона: " << actualErrorNewton << std::endl;
    return 0;
}
