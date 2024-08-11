#include <iostream>
#include <vector>
#include <math.h>
#include <locale.h>
using namespace std;

double h = 0.2;

double Q(double x, double x0)
{
    return (x - x0)/ h;
}

double D1(double q, vector<double> y)
{
    return (1/h) * ((1/(double)24) * y[0] * (2 * q - 5) * (2 * pow(q,2) - 10 * q + 10) - (1/(double)6) * y[1] * (4 * pow(q,3) - 27 * pow(q,2) + 52* q - 24) + (1/(double)4) *y[2] * (2*(q - 2) * (2 * pow(q,2) - 8 * q + 3)) - (1/(double)6) * y[3] * (4 * pow(q,3) - 21 * pow(q,2) + 28* q - 8) + (1/(double)24) * y[4]  * (4 * pow(q,3) - 18 * pow(q,2) + 22 * q - 6));
}

double D2 (double q, vector<double> y)
{
     return (1/pow(h,2)) *((1/(double)2) * y[0] * (12*pow(q,2) - 60 * q  + 70)- (1/(double)3) * y[1] * (6 * pow(q,2) - 27 * q + 26) + (1/(double)2) *y[2] * (6 * pow(q,2) - 24 * q + 19) - (1/(double)3) * y[3] * (6 * pow(q,2) - 21 * q + 14) + (1/(double)12) * y[4]  * (6 * pow(q,2) - 18 * q + 11));
}

int main()
{
    setlocale(LC_ALL, "RUS");
    vector<double> x(5);
    vector<double> y(5);
    x[0] = 13.5; x[1] = 13.7; x[2] = 13.9; x[3] = 14.1; x[4] = 14.3;
    y[0] = 4.90583; y[1] = 4.92007; y[2] = 4.93459; y[3] = 4.94882; y[4] = 4.96571;
    cout << "Узел: " << "\tПервая производная: " << "\t" << "Вторая производная:" << endl;
    for(unsigned i = 0; i < x.size(); ++i)
    {
       double q = Q(x[i],x[0]);

       cout << i+1 << "\t"<< round(D1(q,y)*100)/100 << "\t\t\t" << round(D2(q,y)*100)/100 << endl;
    }
    return 0;
}
