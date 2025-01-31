#include "functions.h"

double f(double x) {
    return log10(x);
}

double f_prime (double x) {
    return 1/(x*log(10));
}

double f_double_prime(double x) {
    return -1 / (x * x * log(10));
}

double f_triple_prime(double x) {
    return 2 / (x * x * x * log(10));
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}