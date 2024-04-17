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
    cout << "������� ���������: ";
    int a;
    cin >> a;
    cout << "������� ������: ";
    int p;
    cin >> p;
    cout << "������� �������: ";
    int degree;
    cin >> degree;
    int result = 1;

    if (isPrime(p)) {
        if (a % p == 0) {
            cout << "������� ������� ����� �� ���������!";
        } else {
            int logDegree = log2(degree);
            int j = logDegree;
            vector<int> binary(32, 0); // ������������� ������� � 32 ����������, ������ ����� 0

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

            cout << "���������: " << result << endl;
        }
    } else {
        cout << "������ �� �������� ������� ������!";
    }
    return 0;
}
