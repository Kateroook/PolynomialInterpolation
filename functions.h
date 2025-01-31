#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <optional>

using namespace std;

double f(double x);

double f_prime (double x);
double f_double_prime(double x);
double f_triple_prime(double x);

int factorial(int n);

optional<double> findDerivative(const vector<vector<double>>& data, double x, int order);

string getOmegaFormula(const vector<double>& x_points);
string getLagrangePolynomial(const vector<double>& x_points, const vector<double>& y_points);
double lagrangeInterpolation(double x, const vector<double>& x_points, const vector<double>& y_points);
void lagranzh();

vector<vector<double>> calculateDivDifferences(const vector<vector<double> > &data);
void generateHermiteData(const vector<double>& x_points, vector<vector<double>>& data);
double calculateHermitPolynomial(const vector<vector<double>>& divDifferences, double x);
string getHermitePolynomial(const vector<vector<double>>& divDifferences);
void hermit();

#endif //FUNCTIONS_H
