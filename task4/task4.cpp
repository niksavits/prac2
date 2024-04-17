#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

bool IsPrime(long long n)
{
    if (n <= 1)
        return false;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

long long InDegreeByMod(long long a, long long b, long long m)
{
    long long result = 1;
    a = a % m;
    while (b > 0)
    {
        if (b % 2 == 1)
            result = (result * a) % m;
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

long long FindG(long long p)
{
    if (!IsPrime(p))
    {
        cout << "Число p не является простым!" << endl;
        return -1;
    }

    srand(time(NULL));
    long long gRand = rand() % (p - 1) + 1; // Генерируем случайное число для g

    while (true)
    {
        bool primSqrt = true;

        for (long long i = 2; i < p - 1; i++)
        {
            if (InDegreeByMod(gRand, i, p) == 1)
            {
                primSqrt = false;
                break;
            }
        }

        if (primSqrt)
            return gRand;

        gRand = rand() % (p - 1) + 1; // Генерируем новое случайное число для g
    }

    return -1; // Если не удалось найти примитивный корень
}

long long GenSecKey(long long n)
{
    srand(time(NULL));
    return rand() % (n - 1) + 1; // Генерация случайного числа x из диапазона [1, n-1]
}

pair<long long, long long> GeneratePublicKey(long long p, long long g, long long x)
{
    long long y = InDegreeByMod(g, x, p); // Вычисление открытого ключа y
    return make_pair(p, y);
}

pair<long long, long long> ForEncrypt(long long m, long long p, long long g, long long y)
{
    srand(time(NULL));
    long long k = rand() % (p - 1) + 1; // Генерация случайного числа k из диапазона [1, p-1]
    long long c1 = InDegreeByMod(g, k, p);
    long long c2 = (m * InDegreeByMod(y, k, p)) % p;
    return make_pair(c1, c2);
}

long long Decrypt(pair<long long, long long> txtEncrypt, long long p, long long x)
{
    long long c1 = txtEncrypt.first;
    long long c2 = txtEncrypt.second;
    long long m = (c2 * InDegreeByMod(c1, p - 1 - x, p)) % p;
    return m;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Выберите действие:" << endl;
    cout << "1. Зашифровать сообщение" << endl;
    cout << "2. Расшифровать сообщение" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Введите простое число p: ";
        long long p;
        cin >> p;

        long long g = FindG(p);
        if (g == -1)
        {
            cout << "Не найдено примитивного корня!" << endl;
            return 0;
        }

        cout << "Найденный примитивный корень g: " << g << endl;

        long long x = GenSecKey(p - 1);
        cout << "Секретный ключ x: " << x << endl;

        pair<long long, long long> publicKey = GeneratePublicKey(p, g, x);
        cout << "Открытый ключ (p, g, y): (" << publicKey.first << ", " << g << ", " << publicKey.second << ")" << endl;

        cout << "Введите сообщение m для шифрования: ";
        long long m;
        cin >> m;

        pair<long long, long long> txtEncrypt = ForEncrypt(m, publicKey.first, g, publicKey.second);
        cout << "Шифртекст (c1, c2): (" << txtEncrypt.first << ", " << txtEncrypt.second << ")" << endl;
    }
    else if (choice == 2)
    {
        cout << "Введите закрытый ключ x: ";
        long long x;
        cin >> x;

        cout << "Введите простое число p: ";
        long long p;
        cin >> p;

        cout << "Введите примитивный корень g: ";
        long long g;
        cin >> g;

        cout << "Введите шифртекст (c1, c2): ";
        long long c1, c2;
        cin >> c1 >> c2;

        long long decrMsg = Decrypt(make_pair(c1, c2), p, x);
        cout << "Расшифрованное сообщение: " << decrMsg << endl;
    }
    else
    {
        cout << "Неверный выбор. Пожалуйста, выберите 1 или 2." << endl;
    }

    return 0;
}
