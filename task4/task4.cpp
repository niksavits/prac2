#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool IsPrime(long long n) { //определение простое число или нет
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

long long InDegreeByMod(long long a, long long b, long long m) { //возведение в степень по модулю
    long long result = 1;
    a = a % m;
    while (b > 0) { //условие завершения
        if (b % 2 == 1) result = (result * a) % m;
        b = b >> 1; //движемся вправо по биту, чтобы уменьшить число вдвое. Это равносильно делению, но из-за битовой операции будет быстрее
        a = (a * a) % m;
    }
    return result;
}

long long FindG(long long p) { //поиск примитивного корня по простому числу
    if (!IsPrime(p)) {
        cout << "Число p не является простым!" << endl;
        return -1;
    }

    srand(time(NULL)); //объявляем генератор
    long long gRand = rand() % (p - 1) + 1; //генерируем случайное число в диапазоне от 1 до (p - 1)число

    while (true) { //поиск примитивного корня
        bool primSqrt = true; //флаг - примитивный корень
        for (long long i = 2; i < p - 1; i++) { //возведение в степень по модулю
            if (InDegreeByMod(gRand, i, p) == 1) { //если мы получаем 1, то число не является примитивным корнем
                primSqrt = false;
                break;
            }
        }

        if (primSqrt) return gRand;

        gRand = rand() % (p - 1) + 1; //генерация нового числа
    }

    return -1;
}

long long GenSecKey(long long n) { //генерируем секретный ключ
    srand(time(NULL));
    return rand() % (n - 1) + 1;  //+1 используется для избигания ошибки
}

pair<long long, long long> GeneratePublicKey(long long p, long long g, long long x) {
    long long y = InDegreeByMod(g, x, p); //возводим в степень по модулю
    return make_pair(p, y); // из полученного значения создаётся пара чисел - открытый ключ
}

vector<pair<long long, long long>> EncryptString(const string &s, long long p, long long g, long long y) {
    vector<pair<long long, long long>> encrypted; //хранение зашифрованных чисел
    srand(time(NULL));
    for (char m : s) { //RBL
        long long k = rand() % (p - 1) + 1;
        long long c1 = InDegreeByMod(g, k, p); //(g^k) mod p
        long long c2 = (m * InDegreeByMod(y, k, p)) % p; //(m * y^k) mod p
        encrypted.push_back(make_pair(c1, c2)); //вносим шифрпару в вектор
    }
    return encrypted;
}

string DecryptString(const vector<pair<long long, long long>>& encrypted, long long p, long long x) { //расшифровка (вектор не должен менять значение - ссылка)
    string decrypted;
    for (auto& pair : encrypted) { //RBL
        long long c1 = pair.first;
        long long c2 = pair.second;
        long long m = (c2 * InDegreeByMod(c1, p - 1 - x, p)) % p; //(c2 * c1^(p-1-x)) mod p
        decrypted.push_back(static_cast<char>(m)); //m - расшифрованный символ сообщения; необходимо преобразовать m в char, чтобы в дальнейшем получить буквенный формат
    }
    return decrypted;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Выберите действие:" << endl;
    cout << "1. Зашифровать сообщение" << endl;
    cout << "2. Расшифровать сообщение" << endl;
    cout << "3. Обмен" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    long long p, g, x;
    pair<long long, long long> publicKey;

    switch (choice) {
        case 1: {
            cout << "Введите открытый ключ (p, g, y): ";
            cin >> p >> g >> x;
            cout << "Введите сообщение m для шифрования: ";
            string m;
            cin >> m;

            vector<pair<long long, long long>> txtEncrypt = EncryptString(m, p, g, x);
            cout << "Шифртекст: ";
            for (auto& pair : txtEncrypt) {
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
            break;
        }
        case 2: {
            cout << "Введите закрытый ключ x: ";
            cin >> x;
            cout << "Введите простое число p: ";
            cin >> p;
            cout << "Введите примитивный корень g: ";
            cin >> g;

            cout << "Введите количество пар шифртекста для расшифровки: ";
            int num_pairs;
            cin >> num_pairs;

            cout << "Введите шифртекст: ";
            vector<pair<long long, long long>> encryptedText;
            long long c1, c2;
            for (int i = 0; i < num_pairs; ++i) {
                cin >> c1 >> c2;
                encryptedText.push_back(make_pair(c1, c2));
            }

            string decrMsg = DecryptString(encryptedText, p, x);
            cout << "Расшифрованное сообщение: " << decrMsg << endl;
            break;
        }
        case 3: {
            cout << "Введите простое число p: ";
            cin >> p;

            g = FindG(p);
            if (g == -1) {
                cout << "Не найдено примитивного корня!" << endl;
                return 0;
            }

            cout << "Найденный примитивный корень g: " << g << endl;

            x = GenSecKey(p - 1);
            cout << "Секретный ключ x: " << x << endl;

            publicKey = GeneratePublicKey(p, g, x);
            cout << "Открытый ключ: (" << publicKey.first << ", " << g << ", " << publicKey.second << ")" << endl;
            break;
        }
        default: {
            cout << "Неверный выбор! Пожалуйста, выберите 1, 2 или 3." << endl;
        }
    }
    return 0;
}
