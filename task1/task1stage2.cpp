#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

bool isPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите основание: ";
    int a;
    cin >> a;
    cout << "Введите модуль: ";
    int p;
    cin >> p;
    cout << "Введите степень: ";
    int degree;
    cin >> degree;
    int result = 1;

    if (isPrime(p)) {
        if (a % p == 0) {
            cout << "Условие теоремы Ферма не выполнено!";
        } else {
            int logDegree = log2(degree);
            int j = logDegree;
            vector<int> binary(32, 0); // Инициализация вектора с 32 элементами, каждый равен 0

            for (int i = logDegree; i >= 0; i--) {
                int bit = ((degree >> i) & 1);
                binary[j] = bit;
                j--;
            }

            result = 1;
            for (int i = logDegree; i >= 0; i--) {
                result = (result * result) % p;
                if (binary[i] == 1) {
                    result = (result * a) % p;
                }
            }

            cout << "Результат: " << result << endl;
        }
    } else {
        cout << "Модуль не является простым числом!";
    }
    return 0;
}
