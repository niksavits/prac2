#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool IsPrime(long long n) { //����������� ������� ����� ��� ���
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

long long InDegreeByMod(long long a, long long b, long long m) { //���������� � ������� �� ������
    long long result = 1;
    a = a % m;
    while (b > 0) { //������� ����������
        if (b % 2 == 1) result = (result * a) % m;
        b = b >> 1; //�������� ������ �� ����, ����� ��������� ����� �����. ��� ����������� �������, �� ��-�� ������� �������� ����� �������
        a = (a * a) % m;
    }
    return result;
}

long long FindG(long long p) { //����� ������������ ����� �� �������� �����
    if (!IsPrime(p)) {
        cout << "����� p �� �������� �������!" << endl;
        return -1;
    }

    srand(time(NULL)); //��������� ���������
    long long gRand = rand() % (p - 1) + 1; //���������� ��������� ����� � ��������� �� 1 �� (p - 1)�����

    while (true) { //����� ������������ �����
        bool primSqrt = true; //���� - ����������� ������
        for (long long i = 2; i < p - 1; i++) { //���������� � ������� �� ������
            if (InDegreeByMod(gRand, i, p) == 1) { //���� �� �������� 1, �� ����� �� �������� ����������� ������
                primSqrt = false;
                break;
            }
        }

        if (primSqrt) return gRand;

        gRand = rand() % (p - 1) + 1; //��������� ������ �����
    }

    return -1;
}

long long GenSecKey(long long n) { //���������� ��������� ����
    srand(time(NULL));
    return rand() % (n - 1) + 1;  //+1 ������������ ��� ��������� ������
}

pair<long long, long long> GeneratePublicKey(long long p, long long g, long long x) {
    long long y = InDegreeByMod(g, x, p); //�������� � ������� �� ������
    return make_pair(p, y); // �� ����������� �������� �������� ���� ����� - �������� ����
}

vector<pair<long long, long long>> EncryptString(const string &s, long long p, long long g, long long y) {
    vector<pair<long long, long long>> encrypted; //�������� ������������� �����
    srand(time(NULL));
    for (char m : s) { //RBL
        long long k = rand() % (p - 1) + 1;
        long long c1 = InDegreeByMod(g, k, p); //(g^k) mod p
        long long c2 = (m * InDegreeByMod(y, k, p)) % p; //(m * y^k) mod p
        encrypted.push_back(make_pair(c1, c2)); //������ �������� � ������
    }
    return encrypted;
}

string DecryptString(const vector<pair<long long, long long>>& encrypted, long long p, long long x) { //����������� (������ �� ������ ������ �������� - ������)
    string decrypted;
    for (auto& pair : encrypted) { //RBL
        long long c1 = pair.first;
        long long c2 = pair.second;
        long long m = (c2 * InDegreeByMod(c1, p - 1 - x, p)) % p; //(c2 * c1^(p-1-x)) mod p
        decrypted.push_back(static_cast<char>(m)); //m - �������������� ������ ���������; ���������� ������������� m � char, ����� � ���������� �������� ��������� ������
    }
    return decrypted;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "�������� ��������:" << endl;
    cout << "1. ����������� ���������" << endl;
    cout << "2. ������������ ���������" << endl;
    cout << "3. �����" << endl;
    cout << "��� �����: ";

    int choice;
    cin >> choice;

    long long p, g, x;
    pair<long long, long long> publicKey;

    switch (choice) {
        case 1: {
            cout << "������� �������� ���� (p, g, y): ";
            cin >> p >> g >> x;
            cout << "������� ��������� m ��� ����������: ";
            string m;
            cin >> m;

            vector<pair<long long, long long>> txtEncrypt = EncryptString(m, p, g, x);
            cout << "���������: ";
            for (auto& pair : txtEncrypt) {
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
            break;
        }
        case 2: {
            cout << "������� �������� ���� x: ";
            cin >> x;
            cout << "������� ������� ����� p: ";
            cin >> p;
            cout << "������� ����������� ������ g: ";
            cin >> g;

            cout << "������� ���������� ��� ���������� ��� �����������: ";
            int num_pairs;
            cin >> num_pairs;

            cout << "������� ���������: ";
            vector<pair<long long, long long>> encryptedText;
            long long c1, c2;
            for (int i = 0; i < num_pairs; ++i) {
                cin >> c1 >> c2;
                encryptedText.push_back(make_pair(c1, c2));
            }

            string decrMsg = DecryptString(encryptedText, p, x);
            cout << "�������������� ���������: " << decrMsg << endl;
            break;
        }
        case 3: {
            cout << "������� ������� ����� p: ";
            cin >> p;

            g = FindG(p);
            if (g == -1) {
                cout << "�� ������� ������������ �����!" << endl;
                return 0;
            }

            cout << "��������� ����������� ������ g: " << g << endl;

            x = GenSecKey(p - 1);
            cout << "��������� ���� x: " << x << endl;

            publicKey = GeneratePublicKey(p, g, x);
            cout << "�������� ����: (" << publicKey.first << ", " << g << ", " << publicKey.second << ")" << endl;
            break;
        }
        default: {
            cout << "�������� �����! ����������, �������� 1, 2 ��� 3." << endl;
        }
    }
    return 0;
}
