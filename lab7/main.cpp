#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
using namespace std;

// f(x,y)
double f(double x, double y)
{
    return (2 * y + x - 4 * log(x)) / x;
}

// точки x_n
void create_X(vector<double>& X, double m, double h, double a)
{
    for (size_t n = 0; n <= m; ++n)
        X.push_back(a + n * h);
}

// аналитическое решение
void method_Analitical(vector<double>& X, vector<double>& Y)
{
    for (size_t i = 0; i < X.size(); ++i)
        Y.push_back(2 * log(X[i]) - X[i] + 1 + 2 * pow(X[i], 2));
}

// метод Эйлера
void method_Euler(vector<double>& X, double h, vector<double>& Y)
{
    double y_0 = 2; // y_n
    double y_n; // y_n+1

    Y.push_back(y_0); // заносим первый Y

    for (size_t i = 0; i < X.size(); ++i)
    {
        y_n = y_0 + h * f(X[i], y_0);
        Y.push_back(y_n);
        y_0 = y_n;
    }

    Y.pop_back(); // ибо мы находим лишний последний Y, когда у нас уже нет X чтобы поставить ему в соответствие
}

// метод Рунге-Кутта
void method_Runge_Kutta(vector<double>& X, double h, vector<double>& Y)
{
    double k_1, k_2, k_3, k_4; // коэффициенты метода

    double y_0 = 2; // y_n
    double y_n; // y_n+1

    Y.push_back(y_0); // заносим первый Y

    for (size_t i = 0; i < X.size(); ++i)
    {
        k_1 = h * f(X[i], y_0);
        k_2 = h * f(X[i] + h / 2, y_0 + k_1 / 2);
        k_3 = h * f(X[i] + h / 2, y_0 + k_2 / 2);
        k_4 = h * f(X[i] + h, y_0 + k_3);

        y_n = y_0 + (k_1 + 2 * k_2 + 2 * k_3 + k_4) / 6;
        Y.push_back(y_n);
        y_0 = y_n;
    }

    Y.pop_back(); // ибо мы находим лишний последний Y, когда у нас уже нет X чтобы поставить ему в соответствие
}

// метод Адамса второго порядка
void method_Adams_Two(vector<double>& X, double h, vector<double>& Y, double y_1)
{
    // y_n-1, y_n, y_n+1
    double y_0 = 2, y_n = y_1, y_n1;

    // заносим первые два Y
    Y.push_back(y_0);
    Y.push_back(y_n);

    for (size_t i = 1; i < X.size(); ++i)
    {
        y_n1 = y_n + h * (3 * f(X[i], y_n) - f(X[i - 1], y_0)) / 2;
        Y.push_back(y_n1);
        y_0 = y_n;
        y_n = y_n1;
    }

    Y.pop_back(); // ибо мы находим лишний последний Y, когда у нас уже нет X чтобы поставить ему в соответствие
}

// метод Адамска третьего порядка
void method_Adams_Three(vector<double>& X, double h, vector<double>& Y, double y_1, double y_2)
{
    // y_n-2, y_n-1, y_n, y_n+1
    double y_0 = 2, y_n = y_1, y_n1 = y_2, y_n2;

    // заносим первые три Y
    Y.push_back(y_0);
    Y.push_back(y_n);
    Y.push_back(y_n1);

    for (size_t i = 2; i < X.size(); ++i)
    {
        y_n2 = y_n1 + h * (23 * f(X[i], y_n1) - 16 * f(X[i - 1], y_n) + 5 * f(X[i - 2], y_0)) / 12;
        Y.push_back(y_n2);
        y_0 = y_n;
        y_n = y_n1;
        y_n1 = y_n2;
    }

    Y.pop_back(); // ибо мы находим лишний последний Y, когда у нас уже нет X чтобы поставить ему в соответствие
}

// вывод массива
void print_vector(vector<double>& vec, const string& name, int precision)
{
    cout << "Массив " << name << ": (";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i != vec.size() - 1)
            cout << fixed << setprecision(precision) << vec[i] << "; ";
        else
            cout << fixed << setprecision(precision) << vec[i] << ")";
    }
}

// создание точек h (для погрешностей)     начало    конец           шаг       число точек
void create_h(vector<double>& h_vec, double h_min, double h_max, double h_step, double n)
{
    double temp = h_min;
    h_vec.push_back(temp); // h_0
    for (size_t i = 0; i < n - 2; ++i)
    {
        temp += h_step;
        h_vec.push_back(temp); // h_i
    }
    h_vec.push_back(h_max); // h_n
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ГЛАВНАЯ ФУНКЦИЯ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
    setlocale(LC_ALL, "rus");

    // входные данные
    const double a = 1;
    const double b = 4;
    double h; // шаг разбиения

    // ВАРИАНТ 1
    cout << "Введите шаг разбиения (h) (от 0 до 1.5): ";
    try
    {
        cin >> h;
        if (h <= 0 || h > (b - a) / 2) throw runtime_error("\nНевалидный шаг разбиения!\n");
    }
    catch (const runtime_error& error) { cout << error.what(); return 0; }
    cout << '\n';

    // ВАРИАНТ 2
    /*double h_min = (b - a) / 1000;
    double h_max = (b - a) / 10;
    int h_count = 15; // число точек для графика погрешностей
    double h_step = (h_max - h_min) / --h_count; // шаг разброса h
    vector<double> h_vector; // точки h
    create_h(h_vector, h_min, h_max, h_step, ++h_count);
    print_vector(h_vector, "h", 5);
    int id;
    cout << "\n\nДля какого h выполнить вычисления? (от 1 до 15): ";
    try
    {
        cin >> id;
        if (id < 1 || id > 15) throw runtime_error("\nВыбранного h не существует!\n");
    }
    catch (const runtime_error& error) { cout << error.what(); return 0; }
    h = h_vector[--id];
    cout << '\n';*/

    // получившееся число отрезков
    long long m = (b - a) / h;

    // точки x_n
    vector<double> X;
    create_X(X, m, h, a);
    print_vector(X, "X", 5);
    cout << "\n\n";

    // аналитическое решение
    vector<double> Y_analytical;
    method_Analitical(X, Y_analytical);
    print_vector(Y_analytical, "Y_analytical", 5);
    cout << "\n\n";

    // метод Эйлера
    vector<double> Y_Euler;
    method_Euler(X, h, Y_Euler);
    print_vector(Y_Euler, "Y_Euler", 5);
    cout << "\n\n";

    // метод Рунге-Кутта
    vector<double> Y_Runge_Kutta;
    method_Runge_Kutta(X, h, Y_Runge_Kutta);
    print_vector(Y_Runge_Kutta, "Y_Runge_Kutta", 5);
    cout << "\n\n";

    // метод Адамса второго порядка
    vector<double> Y_Adams_Two;
    method_Adams_Two(X, h, Y_Adams_Two, Y_Euler[1]);
    print_vector(Y_Adams_Two, "Y_Adams_Two", 5);
    cout << "\n\n";

    // метод Адамса третьего порядка
    vector<double> Y_Adams_Three;
    method_Adams_Three(X, h, Y_Adams_Three, Y_Euler[1], Y_Euler[2]);
    print_vector(Y_Adams_Three, "Y_Adams_Three", 5);
    cout << "\n\n";

    // массивы погрешностей
    vector<double> inaccuracy_euler;
    vector<double> inaccuracy_runge_kutta;
    vector<double> inaccuracy_adams_two;
    vector<double> inaccuracy_adams_three;

    // заполнение
    for (size_t i = 0; i < X.size(); ++i)
    {
        inaccuracy_euler.push_back(abs(Y_Euler[i] - Y_analytical[i]));
        inaccuracy_runge_kutta.push_back(abs(Y_Runge_Kutta[i] - Y_analytical[i]));
        inaccuracy_adams_two.push_back(abs(Y_Adams_Two[i] - Y_analytical[i]));
        inaccuracy_adams_three.push_back(abs(Y_Adams_Three[i] - Y_analytical[i]));
    }

    // максимальные погрешности при заданном h
    cout << "При h = " << h << ":";
    cout << "\nМаксимальная погрешность Эйлера: " << *max_element(inaccuracy_euler.begin(), inaccuracy_euler.end());
    cout << "\nМаксимальная погрешность Рунге-Кутта: " << *max_element(inaccuracy_runge_kutta.begin(), inaccuracy_runge_kutta.end());
    cout << "\nМаксимальная погрешность Адамса_2: " << *max_element(inaccuracy_adams_two.begin(), inaccuracy_adams_two.end());
    cout << "\nМаксимальная погрешность Адамса_3: " << *max_element(inaccuracy_adams_three.begin(), inaccuracy_adams_three.end());
    cout << '\n';

    return 0;
}
