#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
using namespace std;


double f(double x)
{
    return pow(log(x),1/(double)2);
}

double Polynom(vector<double> x, vector<double> A, double number) //������� �������
{
    double P = 0.0;
    for(int i = 0; i < 4; i++)
    {
        double kf = 1.0;
        for(int j = 0; j < i; j++)
        {
            kf *= double(number - x[j]);//���������� ���������
        }
        P += A[i]*kf;//������������
    }
    return P;
}

vector<double> A(vector<double> x, vector<double> y)
{
    vector<double> a;
    a.push_back(y[0]);//������ �����.
    int n = x.size();
    double sum, prodUp, prodDown;
    for(int m = 1; m < n; m++)
    {
        sum = 0.0, prodUp = 1.0, prodDown = 1.0;

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < i; j++) //���������� ���������
            {
                prodUp *= x[m] - x[j];
            }
            sum += a[i]*prodUp; //����� ���������
        }
        for(int i = 0; i < m; i++) //���������� �����������
        {
            prodDown *= x[m] - x[i];
        }

        a.push_back((y[m] - sum) / prodDown); //�������������� �������
    }

    return a;
}

double Derpivate(double x, double delta = 0.0001) //������� ��������� �����������
{
    return fabs((f(x+3*delta) - 3*f(x+2*delta) + 3*f(x+delta) - f(x))/(double) pow(delta,3));
}

double max(vector<double> x) //����� ������������ �����������
{
    double dal = 0;
    double temp;
    for(double i = x[0]; i < x[x.size()-1]; i+= 0.01)
    {
        temp = Derpivate(i);
        if(temp > dal)
            dal = temp;
    }
    return dal;
}

double R(vector<double> x, double number) //�����������
{
    double kf = max(x)/6.00; //3! == 6
    double sum = 0;
    for(int i = 0; i < x.size(); ++i)
    {
        sum += (number - x[i]);
    }
    return sum*kf;
}

int main()
{
    double a = 7.5;

    vector<double> x = {7.0, 8.0, 9.0}; //����
    vector<double> y;
    string elem, F, P;

    for(int i = 0; i < x.size(); i++)
    {
        y.push_back(f(x[i])); //���������� ������� �������
    }

    cout << "P(a) = " << round(Polynom(x, A(x,y),a)*1000)/1000 << endl;//���� �������� � �
    cout << "R(a) <= " << round(fabs(R(x,a)*1000))/1000 << endl;//����� ���� ������
    for(double i = x[0]; i < x[x.size()-1]; i+= 0.01) //����� ��� �������
    {
        elem = std::to_string(i);
        F = std::to_string(f(i));
        P = std::to_string(Polynom(x, A(x,y),i));

        elem.replace(elem.find(string(".")),1,string(","));
        F.replace(F.find(string(".")),1,string(","));
        P.replace(P.find(string(".")),1,string(","));
        cout << "= " << elem << "\t= "<< F << "\t= " << P << endl;
    }
    return 0;
}
