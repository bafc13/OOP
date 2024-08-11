#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
using namespace std;


double f(double x){return pow(log(x),13/(double)4);}

double newTonPolynom(vector<double> x, vector<double> A, double number){
double P = 0.0;
for(int i = 0; i < 4; i++){
    double kf = 1.0;
    for(int j = 0; j < i; j++){
        kf *= double(number - x[j]);
    }P += A[i]*kf;
}return P;}

vector<double> A(vector<double> x, vector<double> y){
vector<double> a;
a.push_back(y[0]);
int n = x.size();
double sum, prodUp, prodDown;
for(int m = 1; m < n; m++){
    sum = 0.0, prodUp = 1.0, prodDown = 1.0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < i; j++){ //Числитель
            prodUp *= x[m] - x[j];
        }sum += a[i]*prodUp; //Сумма числителя
        }for(int i = 0; i < m; i++){ //Знаменатель
            prodDown *= x[m] - x[i];
        }
    a.push_back((y[m] - sum) / prodDown);}
return a;}

double lastDeriv(double x, double delta = 0.0001) //Подсчёт последней производной
{return fabs((f(x+3*delta) - 3*f(x+2*delta) + 3*f(x+delta) - f(x))/(double) pow(delta,3));}

double max(vector<double> x){ //Выбор максимальной погрешности
double dal = 0;
double temp;
for(double i = x[0]; i < x[x.size()-1]; i+= 0.01){
    temp = lastDeriv(i);
    if(temp > dal)
        dal = temp;
}return dal;}

double R(vector<double> x, double number){ //Погрешность
double kf = max(x)/6.00; //3! == 6
double sum = 0;
for(int i = 0; i < x.size(); ++i){
    sum += (number - x[i]);
}return sum*kf;}

int main()
{
double a = 2.5;
vector<double> x = {2.0, 3.0, 4.0}; //Узлы
vector<double> y;
string elem, stringFunc, stringPol;
for(int i = 0; i < x.size(); i++){
    y.push_back(f(x[i])); //Заполнение массива функций
}
cout << "Polynom = \t" << round(newTonPolynom(x, A(x,y),a)*10)/10 << endl;
cout << "R(a) <= \t" << round(fabs(R(x,a)*10))/10 << endl;
for(double i = x[0]; i < x[x.size()-1]; i+= 0.01){ //Вывод для таблицы
    elem = std::to_string(i);
    stringFunc = std::to_string(f(i));
    stringPol = std::to_string(newTonPolynom(x, A(x,y),i));
    elem.replace(elem.find(string(".")),1,string(","));
    stringFunc.replace(stringFunc.find(string(".")),1,string(","));
    stringPol.replace(stringPol.find(string(".")),1,string(","));
    cout << "= " << elem << "\t= "<< stringFunc << "\t= " << stringPol << endl;
}return 0;}
