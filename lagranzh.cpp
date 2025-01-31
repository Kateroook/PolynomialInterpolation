#include "functions.h"

double lagrangeInterpolation(double x, const vector<double>& x_points, const vector<double>& y_points) {
    double result = 0.0;
    int n = x_points.size();

    for (int k = 0; k < n; ++k) {
        double fx = y_points[k];
        for (int j = 0; j < n; ++j) {
            if (j != k) {
                fx *= (x - x_points[j]) / (x_points[k] - x_points[j]);
            }
        }
        result += fx;
    }
    return result;
}

string getOmegaFormula(const vector<double>& x_points) {
    stringstream omega;
    omega << "Omega(x) = ";
    for (size_t i = 0; i < x_points.size(); ++i) {
        if (i > 0) omega << " * ";
        omega << "(x - " << x_points[i] << ")";
    }
    return omega.str();
}

string getLagrangePolynomial(const vector<double>& x_points, const vector<double>& y_points) {
    stringstream polynomial;
    int n = x_points.size();

    polynomial << "L(x) = ";
    for (int k = 0; k < n; ++k) {
        if (k > 0) polynomial << " + ";
        polynomial << y_points[k] << " / ";

        double denominator = 1.0;
        for (int j = 0; j < n; ++j) {
            if (j != k) denominator *= (x_points[k] - x_points[j]);
        }
        polynomial << denominator;

        for (int j = 0; j < n; ++j) {
            if (j != k) {
                polynomial << " * (x - " << x_points[j] << ")";
            }
        }
    }
    return polynomial.str();
}
void lagranzh() {
    const int num_points = 15;
    const double x_min = 1.0, x_max = 100.0;

    vector<double> x_points(num_points), y_points(num_points);

    cout << setw(10) << "x" << setw(15) << "f(x)" << endl;
    for (int i = 0; i < num_points; ++i) {
        x_points[i] = x_min + i * (x_max - x_min) / (num_points - 1);
        y_points[i] = f(x_points[i]);
        cout << setw(10) << x_points[i] << setw(15) << y_points[i] << endl;
    }

    //
    //    cout << "Table of values:" << endl;
    //    cout << setw(10) << "x" << setw(15) << "f(x)" << setw(15) << "f'(x)" << setw(15) << "f''(x)" << setw(15) << "f(x)'''" <<    endl;
    //    for (int i = 0; i < num_points; ++i) {
    //        cout << setw(10) << x_points[i] << setw(15) << y_points[i] << setw(15) << f_prime(x_points[i]) << setw(15)
    //            << f_double_prime(x_points[i]) << setw(15) << f_triple_prime(x_points[i]) <<endl;
    //    }


    cout << "\nLagranzh Interpolation on [1, 100]:" << endl;
    cout << setw(10) << "x" << setw(15) << "f(x)" << setw(20) << "P(x)" << endl;
    for (double x = x_min; x <= x_max; x += 4.0) {
        double interpolated = lagrangeInterpolation(x, x_points, y_points);
        cout << setw(10) << x << setw(15) << f(x) << setw(20) << interpolated << endl;
    }

    cout << endl;
    string omega = getOmegaFormula(x_points);
    cout << omega << endl;

    cout << "\nLagranzh polynomial:" << endl;
    string polynomial = getLagrangePolynomial(x_points, y_points);
    cout << polynomial << endl;


    ofstream outFile("results.csv");
    outFile << "x,f(x),P(x)\n";
    for (double x = x_min; x <= x_max; x += 2.0) {
        double interpolated = lagrangeInterpolation(x, x_points, y_points);
        outFile << x << "," << f(x) << "," << interpolated << "\n";
    }
    outFile.close();
}