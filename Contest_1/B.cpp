#include <iostream>
#include <iomanip>

using namespace std;

double power(double num, int pow){
    if (!pow){
        return 1;
    }
    if (pow % 2){
        return power(num, pow - 1) * num;
    }
    else{
        double prev_pow = power(num, pow / 2);
        return prev_pow * prev_pow;
    }
}

int main() {
    int b;
    double a;
    cin >> a >> b;
    cout << fixed << setprecision(5) << power(a, b);
}


