#include "functions.h"

optional<double> findDerivative(const vector<vector<double>>& data, double x, int order) {
    for (const auto& row : data) {
        if (row[0] == x && order + 2 < row.size()) {
            cout << "x = " << x <<" row[0] = " << row[0] << " order = " << order << "row[order+2] = " << row[order+2]<< endl;
            return row[order + 2];
        }
    }
    return nullopt;
}

vector<vector<double>> calculateDivDifferences(const vector<vector<double> > &data) {
    vector<vector<double>> divDifferences;
    for (const auto& row : data) {
        int derivativesCount = row.size() - 2;
        for (int i = 0; i <= derivativesCount; ++i) {
            divDifferences.push_back({row[0], row[1]});
        }
    }

    int m = divDifferences.size();
    for (int col = 2; col < m + 1; ++col) {
        for (int row = 0; row < m - col + 1; ++row) {
            if (divDifferences[row][0] == divDifferences[row + col - 1][0]) {
                int order = col - 2;
                auto derivative = findDerivative(data, divDifferences[row][0], order);
                if (derivative.has_value()) {
                    double value = derivative.value() / factorial(col-1);
                    divDifferences[row].push_back(value);
                    //cout << "row:" << row <<  " col = " << col-1 << " fact = "  << factorial(col-1) << " value = " << value << endl;
                } else {
                    divDifferences[row].push_back(0);
                }
            } else {
                double numerator = divDifferences[row + 1][col - 1] - divDifferences[row][col - 1];
                double denominator = divDifferences[row + col - 1][0] - divDifferences[row][0];
                divDifferences[row].push_back(numerator / denominator);
            }
        }
    }

    cout << setw(20) << "x" << setw(20) << "f(x)";
    for (int i = 1; i < m; ++i) {
        cout << setw(20) << "I" << i;
    }
    cout << endl;

    for (const auto& row : divDifferences) {
        for (double value : row) {
            cout << std::setw(12)  << value;
        }
        cout << endl;
    }

    ofstream outFile("divDifferences.txt");
    if (outFile.is_open()) {
        outFile << setw(14)<< left << "x" << setw(14) << left << "f(x)";
        for (int i = 1; i < m; ++i) {
            outFile << setw(14) << left <<"I" + to_string(i);
        }
        outFile << endl;

        for (const auto& row : divDifferences) {
            for (double value : row) {
                outFile << setw(14) << left << value ;
            }
            outFile << endl;
        }
        outFile.close();
    } else {
        cerr << "Error opening file!" << endl;
    }

    return divDifferences;
}

void generateHermiteData(const vector<double>& x_points, vector<vector<double>>& data) {
    for (int i = 0; i < x_points.size(); i++) {
        vector<double> row = {x_points[i], f(x_points[i])};

        if (i == 1 || i == 3) {
            row.push_back(f_prime(x_points[i]));  // f'(x)
            data.push_back(row);
        }  else if (i == 9 || i == 11) {
            row.push_back(f_prime(x_points[i]));  // f'(x)
            data.push_back(row);
        }

        else if (i == 4 || i == 6 || i  == 8 || i == 10 || i == 12 || i == 14) {
            row.push_back(f_prime(x_points[i]));
            row.push_back(f_double_prime(x_points[i])); // f''(x)
            data.push_back(row);
        }

        else if (i == 7 || i == 13) {
            row.push_back(f_prime(x_points[i]));
            row.push_back(f_double_prime(x_points[i]));
            row.push_back(f_triple_prime(x_points[i]));
            data.push_back(row);
        }
        else{
            data.push_back(row);
        }
    }
}

double calculateHermitPolynomial(const vector<vector<double>>& divDifferences, double x) {
    double result = divDifferences[0][1];

    for (int i = 1; i < divDifferences.size(); ++i) {
        double term = divDifferences[0][i + 1];

        double factor = 1.0;

        for (int j = 0; j < i; ++j) {
            factor *= (x - divDifferences[j][0]);
        }

        result += term * factor;
    }

    return result;
}

string getHermitePolynomial(const vector<vector<double>>& divDifferences) {
    cout << "H(x) = ";
    stringstream polynomial;

    for (int i = 0; i < divDifferences.size(); ++i) {
        double coefficient = divDifferences[0][i + 1];
        //cout << "c[" << i << "] = " << scientific << coefficient << "\t" << endl;
        if (coefficient == 0) continue;
        //cout << "i" <<  i << endl;
        if (i > 1 && coefficient > 0) {
            polynomial << " + ";
        } else if (coefficient < 0) {
            polynomial << " - ";
            coefficient = abs(coefficient);
        }

        polynomial << scientific << coefficient;
        for (int j = 0; j < i; ++j) {
            polynomial << " * (x - "  << defaultfloat << divDifferences[j][0] << ")";
        }
    }
     return polynomial.str();
}

void hermit() {
    const int num_points = 15;
    const double x_min = 1.0, x_max = 100.0;

    vector<double> x_points(num_points);
    vector<vector<double>> data;

    for (int i = 0; i < num_points; ++i) {
        x_points[i] = x_min + i * (x_max - x_min) / (num_points - 1);
    }

    generateHermiteData(x_points, data);
    cout << setw(15) << left << "x" << setw(15) << "f(x)" << setw(15) << "f'(x)" << setw(15) << "f''(x)" << setw(15) << "f(x)'''" <<   endl;
    for (const auto& row : data) {
        for (const auto& value : row) {
            cout << setw(15) << left << value;
        }
        cout << endl;

    }
        cout << endl;

    auto diff = calculateDivDifferences(data);

    cout << getHermitePolynomial(diff) << endl;

    const int plot_points = 50;
    const double step = (x_max - x_min) / (plot_points - 1);

    ofstream outFile("polynomial_plot_data.txt");
    if (outFile.is_open()) {
        for (double x = x_min; x <= x_max; x += step) {
            double y = calculateHermitPolynomial(diff, x);
            double log = f(x);
            outFile << x << " " << y << " " << log << endl;
        }
        outFile.close();
        cout << "Data to draw Hermit graphic - 'polynomial_plot_data.txt'." << endl;
    } else {
        cerr << "Error opening file!" << endl;
    }
}
