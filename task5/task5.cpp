#include <iostream>
using namespace std;

int lastNum(int num, int degree) {
    if (degree == 0) return 1; // ����� ����� � ������� 0 ����� 1

    num = num % 10; // ��������� ��������� � �������

    // ������� ������� �� ������� �� 4, �.�. ������ ����� 4 ��� ��������� ���� ���������� ����� � �������
    int ostatok = degree % 4;
    if (ostatok == 0) ostatok = 4; // ������������ ��� ����������������� �����

    int result = 1;
    for (int i = 0; i < ostatok; ++i) {
        result = (result * num) % 10; // ������� ��������� ����� ���������� ����� � �������
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "������� �����: ";
    int num;
    cin >> num;
    cout << "������� ������ �������: ";
    int degree1;
    cin >> degree1;
    cout << "������� ������ �������: ";
    int degree2;
    cin >> degree2;

    int finalDegree = lastNum(degree1, degree2);
    int result = lastNum(num, finalDegree);

    cout << "��������� ����� ����� " << num << "^(" << degree1 << "^" << degree2 << ") �����: " << result << endl;

    return 0;
}
