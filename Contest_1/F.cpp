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

int factorial(int n)
{
    if (n == 0) {
        return 1;
    }
    else
        return n*factorial(n - 1);
}

int main() {
    long double x, e;
    cin >> x >> e;
    x = to_interval(x);

    long double sum = 0;
    int n = 0;

    long double next = x;
    while (fabs(next) >= e) {
        sum += next;
        next = pow(-1, n + 1) * pow(x, n + n + 3) / factorial(n + n + 3);
        n++;
    }

    int precision = 0;
    while (fabs(e - 1) > 1e-18) {
        e *= 10;
        precision++;
    }

    n = (n == 0) ? 1 : n;
    cout << setprecision(precision) << sum << endl << n;
    return 0;
}
