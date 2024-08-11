#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double f(double x)
{
    return pow(log(x),1/(double)2);
}

double LaGrangee(vector<double> x, vector<double> y, double number )
{
    double sum = 0.0;
    double search;
    for(int i = 0; i < 3; ++i)
    {
        search = 1.0;
        for(int j = 0; j < 3; ++j)
        {
            if(j != i)
            {
                search *= ((number - x[j]) / (x[i] - x[j]));//расчет слагаемого
            }
        }
        sum += y[i]*search;//суммирование слагаемых
    }
    return sum;
}

double Derpivate(double x, double delta = 0.0001) //Подсчёт последней производной
{
    return fabs((f(x+3*delta) - 3*f(x+2*delta) + 3*f(x+delta) - f(x))/(double) pow(delta,3));
}

double max(vector<double> x) //Поиск максимальной погрешности
{
    double first = 0;
    double temp;
    for(double i =x[0]; i < x[x.size()-1]; i+= 0.01)
    {
        temp = Derpivate(i);
        if(temp > first)
            first = temp;
    }
    return first;
}

double R(vector<double> x, double number) //Подсчет погрешности
{
    double kf = max(x)/6.00; //вычисление коэфф. погрешности
    double sum = 0;
    cout << "MAX = " << max(x) << endl;
    for(int i = 0; i < x.size(); ++i)
    {
        sum += (number - x[i]);
    }
    return sum*kf;
}

int main()
{

    double a = 7.5;

    vector<double> x = {7.0, 8.0, 9.0}; //Узлы
    vector<double> y;

    for(int i = 0; i < x.size(); ++i)
    {
        y.push_back(f(x[i])); //Заполнили массив функций
    }
    string elem;
    string F;
    string L;
    cout << "F(a) = " << round(f(a)*100)/100 << endl;
    cout << "L(a) = " << round(LaGrangee(x,y,a)*100)/100 << endl;
    cout << "R(a) = " << round(fabs(f(a) - LaGrangee(x,y,a))*100)/100 << endl;
    cout << "R(a) <= " << round(R(x,a)*100)/100 << endl;
    for(double i =x[0]; i < x[x.size()-1]; i+= 0.01)
    {
        elem = std::to_string(i);
        F = std::to_string(f(i));
        L = std::to_string(LaGrangee(x,y,i));

        elem.replace(elem.find(string(".")),1,string(","));
        F.replace(F.find(string(".")),1,string(","));
        L.replace(L.find(string(".")),1,string(","));
        cout << "= " << elem << "\t= "<< F << "\t= " <<L << endl;
    }

    return 0;}
