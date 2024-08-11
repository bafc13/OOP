#include <iostream>
#include <iomanip>
#include <math.h>
using std::cout;
using std::cin;
using std::setw;
using std::fixed;
using std::setprecision;

#define M_PI 3.1415926535897932384626433832795

double f(double x, double y) {
    return 3 * cos(2 * M_PI * x);
}

void KuttaMerson4(double x_0, double y_0, double x_end, double h, double e_lock, double e_glob) {
    double k1, k2, k3, k4, k5;
    double x_i = x_0, y_i = y_0;
    double y_, h_ = h; // Используйте h_ для отслеживания изменения шага
    double local_error = 0;
    double global_error = 0;
    const double MIN_H = 1e-6; // Минимальный допустимый шаг

    cout << setw(12) << "X" << setw(16) << "Y" << setw(20) << "E_лок" << setw(20) << "E_глоб" << '\n';
    cout << fixed << setprecision(10);
    cout << setw(12) << x_i << setw(16) << y_i << setw(20) << local_error << setw(20) << global_error << '\n';

    do {
        x_i += h_; // Используйте h_ для изменения позиции x

        k1 = h_ * f(x_i, y_i);
        k2 = h_ * f(x_i + h_ / 3, y_i + k1 / 3);
        k3 = h_ * f(x_i + h_ / 3, y_i + k1 / 6 + k2 / 6);
        k4 = h_ * f(x_i + h_ / 2, y_i + k1 / 8 + 3 * k3 / 8);
        k5 = h_ * f(x_i + h_, y_i + k1 / 8 - 3 * k3 / 8 + 2 * k4);
        y_ = y_i;
        y_i = y_i + k1 / 6 + 2 * k4 / 3 + k5 / 6;

        local_error = abs(y_i - y_);
        {
            do {
                local_error -= e_lock;
            } while (local_error >= e_lock);
            if (local_error < 0)
                local_error = abs(local_error);
        }

        if (local_error >= e_lock) {
            h_ /= 2;
            // Проверка на минимальный шаг
            if (h_ < MIN_H) {
                cout << "Превышен минимальный шаг. Прерывание вычислений." << '\n';
                break; // Прерываем цикл, если шаг становится слишком маленьким
            }
        }

        global_error += local_error;

        if (global_error >= e_glob) {
            h_ /= 2;
            // Проверка на минимальный шаг
            if (h_ < MIN_H) {
                cout << "Превышен минимальный шаг. Прерывание вычислений." << '\n';
                break; // Прерываем цикл, если шаг становится слишком маленьким
            }
            {
                do {
                    global_error -= e_glob;
                } while (global_error >= e_glob);
            }
        }

        {
            y_i = y_ + local_error;
            x_i = asin((y_i * 2 * M_PI) / 3) / (2 * M_PI);
        }

        cout << setw(12) << x_i << setw(16) << y_i << setw(20) << local_error << setw(20) << global_error << '\n';
    } while (x_i <= x_end + h_);
}

int main() {
    setlocale(LC_ALL, "rus");

    double x_0, y_0, x_end, h, E_lock, E_glob;
    cout << "x_0: ";
    cin >> x_0;
    cout << "y_0: ";
    cin >> y_0;
    cout << "x_end: ";

 cin >> x_end;
 cout << "h: ";
 cin >> h;
 cout << "E_lock: ";
 cin >> E_lock;
 cout << "E_glob: ";
 cin >> E_glob;
 cout << '\n';

 KuttaMerson4(x_0, y_0, x_end, h, E_lock, E_glob);

 return 0;
}
