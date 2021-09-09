#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const long double Pi = 3.14159265;

long double to_interval(long double x) {
    while (x > Pi) {
        x -= 2*Pi;
    }
    while(x < -Pi) {
        x += 2*Pi;
    }

    if (x < -Pi/2) {
        x = -Pi - x;
    }
    if (x > Pi/2) {
        x = Pi - x;
    }
    return x;
}

int main() {
    long double x;
    string eps;
    cin >> x >> eps;
    x = to_interval(x);

    int precision = eps.length() - 2;
    long double e = stold(eps);

    long double sum = 0;
    int n = 0;
    long double prev_pow = x * x * x;
    int prev_fact = 6;
    int prev_n_fact = 3;

    long double next = x;
    int sign = -1;

    while (fabs(next) >= e) {
        sum += next;
        next = sign * prev_pow / prev_fact;
        sign = -sign;
        prev_pow *= x * x;
        prev_fact = prev_fact * (prev_n_fact + 1) * (prev_n_fact + 2);
        n++;
        prev_n_fact += 2;
    }

    n = (n == 0) ? 1 : n;
    cout << setprecision(precision) << sum << endl << n;
    return 0;
}
