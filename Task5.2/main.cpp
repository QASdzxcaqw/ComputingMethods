#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double lower_limit = 0, upper_limit = M_PI/4;

double f(double x){
    return cos(x*x);
}

double legendre(double x, int n) {
    if (n == 0) {
        return 1.0;
    } else if (n == 1) {
        return x;
    } else {
        return ((2.0 * n - 1) * x * legendre(x,n-1) - (n - 1) * legendre(x, n-2)) / n;
    }
}



double computeGaussianQuadrature(std::vector<double>& nodes, std::vector<double>& coefficients) {
    double integral = 0.0;

    for (size_t i = 0; i < nodes.size(); ++i) {
        double xi = (nodes[i]*(upper_limit-lower_limit) + upper_limit+lower_limit)/2;
        double coefficient = coefficients[i];


        integral += coefficient * f(xi);
        nodes[i] = xi;
        coefficients[i] = coefficient*(upper_limit- lower_limit) / 2;
        std::cout<<nodes[i] << "<->" << coefficients[i] << std::endl;
    }


    return integral * (upper_limit - lower_limit)/2 ;
}

double secant_method_all_roots(int n, double epsilon, double a, double b) {
    std::vector<double> roots;

    double x0 = a;
    double x1 = b;

    double xt = 0;
    while (std::abs(x1 - x0) >= epsilon) {
        xt = x1 - legendre(x1, n)*(x1-x0)/(legendre(x1, n) - legendre(x0, n));
        x0 = x1;
        x1 = xt;
    }

    return xt;
}
std::vector<double> rootsSeparation(int n, double epsilon) {
    std::vector<double> roots;

    double h = 0.02;
    for (double i = -1; i <= 1; i += h) {
        if (legendre(i, n) * legendre(i + h, n) < 0) {
            roots.push_back(secant_method_all_roots(n, epsilon, i, i+h));
        }
        if(roots.size() == n){
            break;
        }
    }
    return roots;
}



int main() {

    const double epsilon = 1e-12;
    int N1, N2, N3;


    std::cout << "Введите N1, N2, N3: ";
    std::cin >> N1 >> N2 >> N3;
    std::vector<int> nodesCount = {N1, N2, N3};




    //std::cout << "Узлы и коэффициенты КФ Гаусса для [" << lower_limit << ", " << upper_limit << "] при N = 1, 2, 3, 4, 5, 6, 7, 8:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::vector<double> nodes = rootsSeparation(nodesCount[i], epsilon);

        std::vector<double> coefficients;
        for (double scaled_node : nodes) {
            double coefficient = ( 2.0 * (1 - scaled_node * scaled_node)) / (nodesCount[i]*nodesCount[i] * legendre(scaled_node, nodesCount[i]-1) * legendre(scaled_node, nodesCount[i]-1));
            coefficients.push_back(coefficient);
        }
        std::cout<< "Значения узлов и коэффициентов(Узел <-> Коэффициент):" << std::endl;
        double result = computeGaussianQuadrature(nodes, coefficients);

        std::cout << "Приближенное значение интеграла для N = " << nodesCount[i] << ": " <<std::setprecision(13) <<result << std::endl;
        std::cout << "\n";
        std::cout << "\n";
    }


    return 0;
}