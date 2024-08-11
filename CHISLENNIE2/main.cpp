#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <locale.h>
using namespace std ;


bool checkUp(double norma){ //���������� �������
    return norma < 1;
}

double* Aproximation0(double linSystem[4][5]) //0 �����������
{
    double* arr = new double[4];
    for(int i = 0; i < 4; ++i){
        arr[i] = linSystem[i][4]/linSystem[i][i];
    }
    return arr;
}

double* Aproximation(double linSystem[4][5], double apr[4]) //��� ��������� �����������
{
    double* arr = new double[4];
    double temp[4] = {0,0,0,0};
    for (int i = 0; i < 4; ++i) {
        double sum = 0;
        for (int j = 0; j < 4; ++j) {
            if (j != i) {
                if(temp[j] != 0){sum += linSystem[i][j] * temp[j];}
                else {sum += linSystem[i][j] * apr[j];}

            }
        }
        arr[i] = (1 / linSystem[i][i]) * (linSystem[i][4] - sum);
        temp[i] = arr[i];
    }
    return arr;
}

double norma(double linSystem[4][5])  //����� ������� �� ������
{
    double result = 0;
    for (int i = 0; i < 4; ++i) {
        double sum = 0;
        for (int j = 0; j < 4; ++j) {
            if (j != i) {
                sum += abs(linSystem[i][j]);
            }
        }
        if(result < (1 / linSystem[i][i]) * sum)
            result = (1 / linSystem[i][i]) * sum;
    }
    return result;
}

double max(double apr_1[4], double apr_2[4]) //�������� ���������� ��������
{
    double max = 0;
    for(int i =0; i < 4; ++i)
        if(max < abs(apr_2[i] - apr_1[i]))
            max = abs(apr_2[i] - apr_1[i]);
    return max;
}

//            14, 6, 3, 5, 12,
//            9, 12, 2, 0, 5,       ���������
//            5, 1, 13, 5, 2,       �������
//            4, 5, 5, 15, 10


//    28 12 6 10 24 (2 * 1 stroka)
//    24 7 1 -5 14 ((2 * 1 stroka - 4 stroka))

//            24, 7, 1, -5, 14, +
//            9, 12, 2, 0, 5, +
//            5, 1, 13, 5, 2, +
//            4, 5, 5, 15, 10 +

int main()
{
    setlocale(LC_ALL,"RUS");

double linSystem[4][5] = {
    24, 7, 1, -5, 14,
    9, 12, 2, 0, 5,
    5, 1, 13, 5, 2,
    4, 5, 5, 15, 10
};

double result = 1, acc1 = pow(10,-2), acc2 = pow(10,-3), acc3 = pow(10,-4);

double *apr0 = Aproximation0(linSystem); //0 �����������, ��������

int it1, it2, it3 = 0; //���-�� �������� ��� ���������� 1, 2 � 3 ���������
bool flag1 = true, flag2 = true; //

double q = norma(linSystem), kf = q / (1-q);

if(checkUp(norma(linSystem))) //�������� �� ����������
{
cout << "q = " << q << endl;
double *apr_2 = Aproximation(linSystem, apr0); //1 ��������
double *apr_1 = apr0; //0 ��������
while(result >= acc3) //���, ���� �� ����� �� ���������� �����������
    {
         result = kf*max(apr_1,apr_2); //��������� ���������� �������� ������� ��������
         apr_1 = apr_2; //��������������� ������� �������� ��� k
         apr_2 = Aproximation(linSystem, apr_2); //������������ ����� �������� k + 1
         if(result < acc1 && flag1 == true){
             it1 = it3;
             cout << "����������� ��� E = 10**(-2): " << "\t" << round(result*100)/100<< endl;
             cout << "����������� �������� ������ ��� ����� E: " << endl;

             for(int i = 0; i < 4; ++i){
                cout << "\t" << apr_2[i] << endl;
             }
             flag1 = false;
        }
        if(result < acc2 && flag2 == true){
             it2 = it3;
             cout << "����������� ��� E = 10**(-3): " << "\t" << round(result*1000)/1000 << endl;
             cout << "����������� �������� ������ ��� ����� E: " << endl;

             for(int i = 0; i < 4; ++i){
                 cout << "\t" << apr_2[i] << endl;
             }
             flag2 = false;
        }
        it3++;
    }

cout << "����������� ��� E = 10**(-4): " << "\t" << round(result*10000)/10000<< endl;
cout << "����������� �������� ������ ��� ����� �: " << endl;

for(int i = 0; i < 4; ++i){
    cout << "\t" << apr_2[i] << endl;
}
cout << "���������� �������� �� E = 10**(-4): " << it3-1 << endl;
cout << "���������� �������� �� E = 10**(-3): " << it2 << endl;
cout << "���������� �������� �� E = 10**(-2): " << it1 << endl;
} else cout << "q = " << q;
}
