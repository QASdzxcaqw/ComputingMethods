#include <iostream>
#include <vector>
#include <algorithm>
#include "cmath"
#include <iomanip>

int m;
double a, h;

struct Table{
    double x0;
    double fx;
    double fpx1;
    double fpxError1;
    double fpx2;
    double fpxError2;
};

std::vector<Table> result;

double f(double x){
    return exp(1.5*x);
}

double fp(double x){
    return 1.5*exp(1.5*x);
}

double fpp(double x){
    return 2.25*exp(1.5*x);
}

void fillAndOutputTable(std::vector<std::pair<double, double>>& sorted_table){
    for (int i = 0; i <= m; i++) {
        sorted_table[i].first = a + i * h;
        sorted_table[i].second = f(a + i * h);
    }

    std::cout << "Таблица (или набор узлов):" << std::endl;
    for (int i = 0; i <= m; i++) {
        std::cout << "x[" << i << "] = " << sorted_table[i].first << ", y[" << i << "] = " << sorted_table[i].second << std::endl;
    }
}
void derivativeCalculation(std::vector<std::pair<double, double>>& sorted_table){
    for(auto it = sorted_table.begin(); it != sorted_table.end(); ++it){

        if (it + 1 != sorted_table.end() && it != sorted_table.begin()){

            double fp1 = ((*(it+1)).second - (*(it-1)).second )/(2*h);
            double fp2 = ((*(it+1)).second -2*(*(it)).second + (*(it-1)).second)/(h*h);
            result.push_back({(*it).first, (*it).second, fp1, fabs(fp1 - fp((*it).first)), fp2, fabs(fp2 - fpp((*it).first))});
        }
    }
}

void printTable(){
    std::cout << std::left << std::setw(10) << "x_i" << std::left << std::setw(30) << "f(x_i)" << std::left
              << std::setw(30)<< "f'(x_i)ЧД" << std::left << std::setw(30) << "|f'(x_i)ЧД - f'(x_i)|" << std::left
              << std::setw(30) << "f''(x_i)ЧД" << std::left<< std::setw(30)
              << "|f''(x_i)ЧД - f''(x_i)|" <<std::endl;
    for(auto it : result){
        std::cout << std::left << std::setw(10) << it.x0
        << std::left << std::setw(30) << it.fx
        << std::left << std::setw(30) << it.fpx1
        << std::left << std::setw(30) << it.fpxError1
        << std::left << std::setw(30) << it.fpx2
        << std::left << std::setw(30) << it.fpxError2
        << std::endl;
    }
}

int main() {
    std::cout << "Задача обратного алгебраического интерполирования" << std::endl;

    // Ввод параметров задачи
    std::cout << "Введите число значений в таблице (m+1): ";
    std::cin >> m;
    std::cout << "Введите начало отрезка:";
    std::cin >> a;
    std::cout<<"Введите шаг:";
    std::cin>> h;
    std::vector<std::pair<double, double>> sorted_table(m+1);
    fillAndOutputTable(sorted_table);
    derivativeCalculation(sorted_table);
    printTable();
}
