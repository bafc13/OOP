#include <iostream>
#include <vector>
#include <cmath>
#include <locale.h>

using namespace std;

double F(double x){
    return (1 - 6 * x) * exp(2 * x);
}

double Derivative3(double a, double delta){

    return (F(a+3*delta) - 3 * F(a+2*delta) + 3 * F(a+delta) - F(a)) / (double) (pow(delta,3));
}

double Approximate(double a, double h, int n) {
    double result = 0;
    double x1, x2;
    for(int i = 0; i < n; i++) {
        x1 = a + i*h;
        x2 = a + (i+1)*h;
        result += (x2-x1)/6.0*(F(x1) + 4.0*F(0.5*(x1+x2)) + F(x2));
    }
    return result;
}

double M3(double a, double b)
{
    double delta = 0.0001;
    double max = Derivative3(a,delta);

    for(int i = a + delta; i < b; i++){
        if(max < Derivative3(i,delta)){ max = Derivative3(i, delta);}
    }
    return max;
}

double Inaccuracy(double a, double b,double h,  int n)
{
    return fabs(M3(a,b) * pow(h,4) * n / 192.0);
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int n = 1000;
    double exact_value = -2.0, a = 0.0, b = 2.0/3.0, h = (b-a) / (double)n;
    cout << "Вычисленное значение: " << Approximate(a,h,n) << endl;
    cout << "Разница между точным и вычисленным значениями: " << fabs(exact_value -  Approximate(a,h,n)) << endl;
    cout << "Таблица погрешностей:" << "\t" << "h" << endl;
    for(int i = n; i <= 10000; i += 1000){
        h = (b-a) / (double)i;
        cout << Inaccuracy(a,b,h,i) << "\t\t" << round(h*10000)/10000 << endl;
    }
    return 0;
}
