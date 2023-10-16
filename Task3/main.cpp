#include <iostream>
#include <vector>
#include <algorithm>
#include "cmath"

constexpr double epsilon = 1.0e-6;
int m, n;
double a, b, F;
bool monotony;
std::vector<double> results;

double f(double x){
    return x*x*x+3;
}

void swap(std::vector<std::pair<double, double>>& sorted_table){
    for(auto& it: sorted_table){
        std::swap(it.first, it.second);
    }
}

double lagrangeInterpolation( double x, std::vector<std::pair<double, double>>& sorted_table) {
    double result = 0.0;
    for (int i = 0; i <= n; i++) {
        double term = sorted_table[i].second;
        for (int j = 0; j <= n; j++) {
            if (i != j) {
                term *= (x - sorted_table[j].first) / (sorted_table[i].first - sorted_table[j].first);
            }
        }
        result += term;
    }
    return result;
}

void bisection(double A, double B, std::vector<std::pair<double, double>>& sorted_table) {
    double c;

    if((lagrangeInterpolation(A, sorted_table)-F) *
      (lagrangeInterpolation(B, sorted_table)-F) > 0){
        return;
    }
    while ((B - A) >= epsilon) {
        c = (A + B) / 2;
        if (lagrangeInterpolation(c, sorted_table) - F == 0.0) {
            break;
        } else if ((lagrangeInterpolation(c, sorted_table)-F) *
                  (lagrangeInterpolation(A, sorted_table)-F) < 0) {
            B = c;
        } else {
            A = c;
        }
    }
    results.push_back((A+B)/2);
}

void fillAndOutputTable(std::vector<std::pair<double, double>>& sorted_table){
    for (int i = 0; i <= m; i++) {
        sorted_table[i].first = a + i * (b - a) / m;
        sorted_table[i].second = f(a + i * (b - a) / m);
    }

    std::cout << "Таблица (или набор узлов):" << std::endl;
    for (int i = 0; i <= m; i++) {
        std::cout << "x[" << i << "] = " << sorted_table[i].first << ", y[" << i << "] = " << sorted_table[i].second << std::endl;
    }
}

bool compareByDifference( const std::pair<double, double>& target1, const std::pair<double, double>& target2) {
    return std::abs(target1.first - F) < std::abs(target2.first - F);
}

void sortTable(std::vector<std::pair<double, double>>& sorted_table){
    std::sort(sorted_table.begin(), sorted_table.end(), [](const std::pair<double, double>& target1, const std::pair<double, double>& target2) {
        return compareByDifference(target1, target2);
    });
}

void printInfo(){
    std::cout<<"Найденные корни:";
    for(auto it: results){
        std::cout<<it<<std::endl;
    }
}

int main() {
    std::cout << "Задача обратного алгебраического интерполирования" << std::endl;

    // Ввод параметров задачи
    std::cout << "Введите число значений в таблице (m+1): ";
    std::cin >> m;
    std::cout << "Введите концы отрезка [a, b]: ";
    std::cin >> a >> b;
    std::vector<std::pair<double, double>> sorted_table(m+1);

    // Ввод значение функции F
    std::cout << "Введите значение функции F: ";
    std::cin >> F;

    std::cout<< "Монотонна ли данная функция: ";
    std::cin>> monotony;

    fillAndOutputTable(sorted_table);

    if(monotony){
        // Ввод степени интерполяционного многочлена n (n <= m)
        std::cout << "Введите степень интерполяционного многочлена n (n <= m): ";
        std::cin >> n;

        swap(sorted_table);
        sortTable(sorted_table);
        results.push_back(lagrangeInterpolation(F, sorted_table));
    }
    else{
        std::cout << "Введите степень интерполяционного многочлена n (n <= m): ";
        std::cin >> n;
        for(int i =0; i < sorted_table.size()-1; i++){
            bisection(sorted_table[i].first, sorted_table[i+1].first, sorted_table);
        }
    }

    printInfo();
    return 0;
}
