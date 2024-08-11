#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

void print_Solution_Two(set<vector<double>>& results)
{
    cout << "Корни: ";
    int i = 0;
    for (const auto& result : results)
    {
        if (i != 3)
            cout << "(" << result[0] << "; " << result[1] << "), ";
        if (i == 3)
            cout << "(" << result[0] << "; " << result[1] << ")\n";
        i++;
    }
}

double f_xy(double& x, double& y)
{
    return x + pow(y, 0.5) - 19;
}

double g_xy(double& x, double& y)
{
    return pow(x, 0.5) + y - 13;
}

double df_dx(double& x, double& y)
{
    return 1;
}

double df_dy(double& x, double& y)
{
    return 0.5 / pow(y, 0.5);
}

double dg_dx(double& x, double& y)
{
    return 0.5 / pow(x, 0.5);
}

double dg_dy(double& x, double& y)
{
    return 1;
}

// коэффициенты поиска корней системы
double b_1_k(double& x_k, double& y_k)
{
    return -f_xy(x_k, y_k) + df_dx(x_k, y_k) * x_k + df_dy(x_k, y_k) * y_k;
}
double b_2_k(double& x_k, double& y_k)
{
    return -g_xy(x_k, y_k) + dg_dx(x_k, y_k) * x_k + dg_dy(x_k, y_k) * y_k;
}
double a_11_k(double& x_k, double& y_k)
{
    return df_dx(x_k, y_k);
}
double a_12_k(double& x_k, double& y_k)
{
    return df_dy(x_k, y_k);
}
double a_21_k(double& x_k, double& y_k)
{
    return dg_dx(x_k, y_k);
}
double a_22_k(double& x_k, double& y_k)
{
    return dg_dy(x_k, y_k);
}

bool existence_of_system(double& x_0, double& y_0)
{
    return a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0) != 0;
}

double Kramer_x_k(double& x_0, double& y_0)
{
    return (double(b_1_k(x_0, y_0) * a_22_k(x_0, y_0) - b_2_k(x_0, y_0) * a_12_k(x_0, y_0)) / double(a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0)));
}
double Kramer_y_k(double& x_0, double& y_0)
{
    return (double(b_2_k(x_0, y_0) * a_11_k(x_0, y_0) - b_1_k(x_0, y_0) * a_21_k(x_0, y_0)) / double(a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0)));
}

set<vector<double>> newton_Method_two_equation(double epsilon)
{
    set<vector<double>> results;
    pair<double, double> initial_approximations = {8, 10};
    int count = 0;
    // начальное приближение
    double x_0, y_0;
    // переменные для итоговых корней
    double x_k, y_k;
    x_0 = initial_approximations.first;
    y_0 = initial_approximations.second;

        // проверка существования системы
    if (existence_of_system(x_0, y_0))
    {
        cout << "Начальные (x_0, y_0): " << x_0 << ", " << y_0 << '\n';

        // использование формул для поиска корня
        x_k = Kramer_x_k(x_0, y_0);
        y_k = Kramer_y_k(x_0, y_0);

        // поиск корня до заданной точности
        while (sqrt(pow(x_k - x_0, 2) + pow(y_k - y_0, 2)) >= epsilon)
        {
            cout << "Промежуточные (x_k, y_k): " << x_k << ", " << y_k << '\n';
            x_0 = x_k;
            y_0 = y_k;

            x_k = Kramer_x_k(x_0, y_0);
            y_k = Kramer_y_k(x_0, y_0);

            count++;
        }
        cout << "Итоговые (x_k+1, y_k+1): " << x_k << ", " << y_k << "\n\n";
        results.insert({ x_k, y_k });
        }
    else
    {
        abort();
    }
    count++;
    cout << "Количество итераций: " << count << "\n";
    return results;
}

int main()
{
    double eps = 1e-4;
    setlocale(LC_ALL, "rus");
    set<vector<double>> result_two;
    result_two = newton_Method_two_equation(eps);
    print_Solution_Two(result_two);

    return 0;
}
