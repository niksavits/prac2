#include <iostream>
using namespace std;

int genEuclid(int a, int b) {
    int r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int multInvers(int c, int m) {
    if(genEuclid(c, m) != 1) {
        cout << "Такого не существует!";
        return -1;
        }
    for (int d = 1; d < m; d++) {
        if ((c*d)%m == 1) {
            return d;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите c: ";
    int c;
    cin >> c;
    cout << "Введите m: ";
    int m;
    cin >> m;
    int d = multInvers(c, m);
    if (d != -1) {
        cout << "Число d равно: " << d;
    }
    return 0;
}
