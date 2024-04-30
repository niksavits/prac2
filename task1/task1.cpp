#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) //������� ����������� �������� �����
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
    cout << "������� ���������: ";
    int a;
    cin >> a;
    cout << "������� ������: ";
    int p;
    cin >> p;
    cout << "������� �������: ";
    int degree;
    cin >> degree;
    int result = 1; //������� �����, �������� � �������, ����� ������� ����

    if (isPrime(p)) { //�������� ������ �� ��������
        if (a % p == 0) { //�������� ������� �����
            cout << "������� ������� ����� �� ���������!";
        } else {
            for (int i = 1; i <= degree; i++) { //��������� �����
                result = (result * a) % p;
            }
            cout << "���������: " << result;
        }
    } else {
        cout << "������ �� �������� ������� ������!";
    }
    return 0;
}
