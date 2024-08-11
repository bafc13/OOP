#include <iostream>
#include <vector>
#include <cmath>
#include <locale.h>

using namespace std;

double F(double x){ return (1 - 6 * x) * exp(2 * x); }

double Derivative(double x, double delta){ return (F(x+delta) - F(x))/(double)delta; }

double Approximate(double a, double h, int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += F(a);
        a += h;
    }
    return sum * h;
}

double M(double a, double b){
    double delta = 0.0001;
    double max = Derivative(a,delta);
    for(int i = a + delta; i < b; i++){
        if(max < Derivative(i,delta)){ max = Derivative(i, delta);}
    }
    return max;
}

double Inaccuracy(double a, double b,double h,  int n){ return M(a,b) * pow(h,2) * n / 2.0; }

int main(){
    setlocale(LC_ALL, "RUS");
    int n = 1000;
    double exact_value = -2.0, a = 0.0, b = 2/3.0, h = (b-a) / (double)n;
    cout << "Вычисленное значение: " << round(Approximate(a,h,n)*1000)/1000 << endl;
    cout << "Разница между точным и вычисленным значениями: " << round(fabs(exact_value -  Approximate(a,h,n))*1000)/1000 << endl;
    cout << "Таблица погрешностей:" << "\t" << "n" << endl;
    for(int i = n; i <= 10000; i += 1000){
        cout << round(Inaccuracy(a,b,h,i)*1000)/1000 << "\t\t" << i << endl;
    }
    return 0;
}
