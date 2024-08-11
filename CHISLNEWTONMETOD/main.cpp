#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

double Function(double x)
{
    return double(pow(x, 3) + (4 * pow(x, 2)) - 5); // f(x)
}

double Function_(double x)
{
    return double(3 * pow(x, 2) + (8 * x)); // f'(x)
}

bool first_root_found = false;

void newton_Method_one_equation(double a, double b, double eps, vector<double>& res)
{
    // x_k, x_k+1
    double x_01, x_k;
    cout << "������� ��������� �����������: ";
    cin >> x_01;

    int count = 0;
    cout << "\n��������� (x_01): " << x_01 << '\n';
    while (true)
    {
        count++;

        x_k = x_01 - Function(x_01) / Function_(x_01);

        cout << "������������� (x_k): " << x_k << '\n';

        double delta = (x_k - x_01);
        if (abs(delta) < eps)
        {
            if (x_k >= a && x_k <= b) // ���� ������ � ���������
            {
                cout << "�������� (x_k+1): " << x_k << "\n\n";
                if(res.size() < 2){
                    res.push_back(x_k);
                    first_root_found = false;
                }

                if (!first_root_found)
                {
                    first_root_found = true; // ������ ������ ������
                    if (res[0] < x_01 || res[0] == 1){ // ����� ���������� �����������
                        x_01 = a;
                    }
                    else if(x_01 <= res[0]){
                        x_01 = b;
                    }
                    continue; // ������� ������� ��������
                }
                if (res.size() == 2) break;
            }
        }
        x_01 = x_k;
    }
    cout << "���������� ��������: " << count << "\n";
}


void print_Solution_One(vector<double>& result)
{
    cout << "�����: (";
    for (size_t i = 0; i < result.size(); i++)
    {
        if (i != result.size() - 1)
            cout << result[i] << "; ";
        else
            cout << result[i];
    }
    cout << ")\n";
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "f(x) = x^3 + 4x^2 - 5\n\n";
    double a = -100; //����� �������� ���������
    double b = 100; //������ �������� ���������
    double eps = 1e-4; // ��������
    vector<double> result;
    newton_Method_one_equation(a, b, eps, result);
    print_Solution_One(result);
    return 0;
}
