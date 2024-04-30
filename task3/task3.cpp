#include <iostream>

using namespace std;

int advEuclid(int a, int b, int &u, int &v) { // расширенный Евклид
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int u1, v1;
    // рекурсивный вызов алгоритма
    int nod = advEuclid(b, a % b, u1, v1);
    // обновление коэффициентов
    u = v1;
    v = u1 - a / b * v1;
    cout << "a: " << a << "\tb: " << b << "\tu: " << u << "\tv: " << v << endl;
    return nod;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите c: ";
    int c;
    cin >> c;
    cout << "Введите m: ";
    int m;
    cin >> m;

    // проверка на ноль в знаменателе
    if (m == 0) {
        cout << "Ошибка: m не может быть равно 0." << endl;
        return 1;
    }

    int u, v;
    int nod = advEuclid(c, m, u, v);
    if (nod != 1) {
        cout << "Не существует взаимнообратного числа." << endl;
        return 1;
    }
    // вычисление обратного элемента
    int d = (u % m + m) % m;
    cout << "d: " << d << endl;
    return 0;
}
