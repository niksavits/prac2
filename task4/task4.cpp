#include <iostream>
#include <cmath>
using namespace std;

// ������� ��� ���������� � ������� �� ������
int modExp(int base, int exp, int mod) {
    int result = 1;
    base %= mod;

    // ������� ���������� � ������� �� ������
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

    cout << "������� ����� g: ";
    int g;
    cin >> g;
    cout << "������� ����� ������ ";
    int p;
    cin >> p;

    cout << "������� ����� Alice: ";
    int numberAlice;
    cin >> numberAlice;
    cout << "������� ����� Bob: ";
    int numberBob;
    cin >> numberBob;

    // ���������� �������� ������ ��� Alice � Bob
    int publicKeyAlice = modExp(g, numberAlice, p);
    int publicKeyBob = modExp(g, numberBob, p);

    // ����� ��������� ������� � ���������� ������ ���������� ����� ��� Alice � Bob
    int secretKeyAlice = modExp(publicKeyBob, numberAlice, p);
    int secretKeyBob = modExp(publicKeyAlice, numberBob, p);

    // ����� �����������
    cout << "�������� ���� �����: " << publicKeyAlice << endl;
    cout << "�������� ���� ����: " << publicKeyBob << endl;
    cout << "��������� ���� ��� �����: " << secretKeyAlice << endl;
    cout << "��������� ���� ��� ����: " << secretKeyBob << endl;

    return 0;
}
