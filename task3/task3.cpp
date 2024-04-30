#include <iostream>

using namespace std;

int advEuclid(int a, int b, int &u, int &v) { // ����������� ������
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int u1, v1;
    // ����������� ����� ���������
    int nod = advEuclid(b, a % b, u1, v1);
    // ���������� �������������
    u = v1;
    v = u1 - a / b * v1;
    cout << "a: " << a << "\tb: " << b << "\tu: " << u << "\tv: " << v << endl;
    return nod;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "������� c: ";
    int c;
    cin >> c;
    cout << "������� m: ";
    int m;
    cin >> m;

    // �������� �� ���� � �����������
    if (m == 0) {
        cout << "������: m �� ����� ���� ����� 0." << endl;
        return 1;
    }

    int u, v;
    int nod = advEuclid(c, m, u, v);
    if (nod != 1) {
        cout << "�� ���������� ���������������� �����." << endl;
        return 1;
    }
    // ���������� ��������� ��������
    int d = (u % m + m) % m;
    cout << "d: " << d << endl;
    return 0;
}
