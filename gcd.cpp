#include <bits/stdc++.h>
using namespace std;

int euclideanAlgorithm(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extendedEuclideanAlgorithm(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedEuclideanAlgorithm(b % a, a, x1, y1);
    
    x = y1 - (b / a) * x1;
    y = x1;
    
    return gcd;
}

int main() {
    int x = 48;
    int y = 18;
    cout << "GCD of " << x << " and " << y << " is " << euclideanAlgorithm(x, y) << endl;
    
    int a = 48;
    int b = 18;
    int gcd = extendedEuclideanAlgorithm(a, b, x, y);
    cout << "GCD of " << a << " and " << b << " is " << gcd << endl;
    cout << "Coefficients are x = " << x << ", y = " << y << endl;
}