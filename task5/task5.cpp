#include <iostream>
using namespace std;

int lastNum(int num, int degree) {
    if (degree == 0) return 1; // Любое число в степени 0 равно 1

    num = num % 10; // Переводим основание в единицы

    // Находим остаток от деления на 4, т.к. период длины 4 для последних цифр возведений чисел в степень
    int ostatok = degree % 4;
    if (ostatok == 0) ostatok = 4; // Корректируем для четырехстепенного цикла

    int result = 1;
    for (int i = 0; i < ostatok; ++i) {
        result = (result * num) % 10; // Находим последнюю цифру возведения числа в степень
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите число: ";
    int num;
    cin >> num;
    cout << "Введите первую степень: ";
    int degree1;
    cin >> degree1;
    cout << "Введите вторую степень: ";
    int degree2;
    cin >> degree2;

    int finalDegree = lastNum(degree1, degree2);
    int result = lastNum(num, finalDegree);

    cout << "Последняя цифра числа " << num << "^(" << degree1 << "^" << degree2 << ") равна: " << result << endl;

    return 0;
}
