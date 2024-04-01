#include <iostream>
#include <cmath>
using namespace std;

// Функция для возведения в степень по модулю
int modExp(int base, int exp, int mod) {
    int result = 1;
    base %= mod;

    // Быстрое возведение в степень по модулю
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        exp /= 2;
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите общий g: ";
    int g;
    cin >> g;
    cout << "Введите общий модуль ";
    int p;
    cin >> p;

    cout << "Введите число Alice: ";
    int numberAlice;
    cin >> numberAlice;
    cout << "Введите число Bob: ";
    int numberBob;
    cin >> numberBob;

    // Вычисление открытых ключей для Alice и Bob
    int publicKeyAlice = modExp(g, numberAlice, p);
    int publicKeyBob = modExp(g, numberBob, p);

    // Обмен открытыми ключами и вычисление общего секретного ключа для Alice и Bob
    int secretKeyAlice = modExp(publicKeyBob, numberAlice, p);
    int secretKeyBob = modExp(publicKeyAlice, numberBob, p);

    // Вывод результатов
    cout << "Открытый ключ Алисы: " << publicKeyAlice << endl;
    cout << "Открытый ключ Боба: " << publicKeyBob << endl;
    cout << "Секретный ключ для Алисы: " << secretKeyAlice << endl;
    cout << "Секретный ключ для Боба: " << secretKeyBob << endl;

    return 0;
}
