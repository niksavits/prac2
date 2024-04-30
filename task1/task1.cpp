#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) //функция определения простого числа
{
    for (int i = 2; i <= sqrt(n); i++)
    {
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
    int result = 1; //искомое число, начинаем с единицы, чтобы работал цикл

    if (isPrime(p)) { //проверка модуля на простоту
        if (a % p == 0) { //проверка условия Ферма
            cout << "Условие теоремы Ферма не выполнено!";
        } else {
            for (int i = 1; i <= degree; i++) { //вычисляем число
                result = (result * a) % p;
            }
            cout << "Результат: " << result;
        }
    } else {
        cout << "Модуль не является простым числом!";
    }
    return 0;
}
