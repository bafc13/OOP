#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

double func(double x){return pow(log(x),13/(double)4);}

double LagranjeFunc(vector<double> x, vector<double> y, double number ){
double sum = 0.0;
double prod;
for(int i = 0; i < 3; ++i){ //суммирование
    prod = 1.0;
    for(int j = 0; j < 3; ++j){ //(x-xi)/(xi-xj)
        if(j != i)
        {prod *= ((number - x[j]) / (x[i] - x[j]));}
    } sum += y[i]*prod;
}return sum;}

double lastDeriv(double x, double delta = 0.0001) //Подсчёт последней производной
{return fabs((func(x+3*delta) - 3*func(x+2*delta) + 3*func(x+delta) - func(x))/(double) pow(delta,3));}

double max(vector<double> x){//Выбор максимальной погрешности
double maxR = 0;
double temp;
for(double i =x[0]; i < x[x.size()-1]; i+= 0.01){
    temp = lastDeriv(i);
    if(temp > maxR)
        maxR = temp;
}return maxR;}

double R(vector<double> x, double number){//Погрешность
double kf = max(x)/6.00;
double sum = 0;
cout << "MAX =    \t" << round(max(x)*100)/100 << endl;
for(int i = 0; i < x.size(); ++i){
    sum += (number - x[i]);
}return sum*kf;}

int main(){
double a = 2.5;
vector<double> x = {2.0, 3.0, 4.0}; //Узлы
vector<double> y;
for(int i = 0; i < x.size(); ++i){
    y.push_back(func(x[i])); //Заполнили массив функций
}
string elem, F, L;
cout << "Function \t" << round(func(a)*100)/100 << endl;
cout << "Lagrange \t " << round(LagranjeFunc(x,y,a)*100)/100 << endl;
cout << "R(a) <=  \t" << fabs(R(x,a)) << endl;
for(double i =x[0]; i < x[x.size()-1]; i+= 0.01)
{
    elem = std::to_string(i);
    F = std::to_string(func(i));
    L = std::to_string(LagranjeFunc(x,y,i));
    elem.replace(elem.find(string(".")),1,string(","));
    F.replace(F.find(string(".")),1,string(","));
    L.replace(L.find(string(".")),1,string(","));
    cout << "= " << elem << "\t= "<< F << "\t= " <<L << endl;
}
return 0;}
