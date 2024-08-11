#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <locale.h>
using namespace std ;


bool checkUp(double norma){ //¬ыполнение услови€
    return norma < 1;
}

double* Approximation0(double A[3][3], double f[3]) //0 приближение
{
    double* arr = new double[3];
    for(int i = 0; i < 3; ++i){
        arr[i] = f[i]/A[i][i];
    }
    return arr;
}

double* Approximation(double A[3][3], double B[3], double C[3]) { //B - f, C - x prev
    int n = 3;
    vector<vector<double>> mainUpper = {{0,0,0}, //L
                                    {0,0,0},
                                    {0,0,0}};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;j++){
            if(j > i){mainUpper[i][j] = A[i][j];}
            else {mainUpper[i][j] = 0;}
        }
    }
    vector<vector<double>> mainLower =  {{0,0,0}, //U
                                        {0,0,0},
                                        {0,0,0}};;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;j++) {
            if(j <i ) {mainLower[i][j] = A[i][j];}
            else {mainLower[i][j]  = 0;}
        }
    }

    vector<vector<double>> main = {{0,0,0}, //D
                                   {0,0,0},
                                   {0,0,0}};;;//главна€ диагональ
    double* result = new double[3];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j == i) {main[i][j] = 1/A[i][j];}
        }
    }
    for(int i = 0; i < n; i++){ //L + U
        for(int j = 0; j < n; j++){
            mainUpper[i][j] = mainUpper[i][j] + mainLower[i][j];
        }
    }

    double mainKf;
    for(int i = 0; i < n; i++){ //D * (L + U)
        mainKf = main[i][i];
        for(int j = 0; j < n; j++){
            mainLower[i][j] = mainKf * mainUpper[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        float sum = 0;
        for(int j= 0; j < n; j++){
            sum += mainLower[i][j] * C[j]; //D * (L + U) * x
        }
        result[i] = sum;
    }

    for(int i = 0; i < n ; i++){
        result[i] = main[i][i] * B[i] -result[i];
    }
    return result;
}

double norma(double A[3][3])  //норма матрицы по строке
{
    double result = 0;
    for (int i = 0; i < 3; ++i) {
        double sum = 0;
        for (int j = 0; j < 3; ++j) {
            if (j != i) {
                sum += abs(A[i][j]);
            }
        }
        if(result < (1 / A[i][i]) * sum)
            result = (1 / A[i][i]) * sum;
    }
    return result;
}

double max(double apr_1[3], double apr_2[3]) //проверка результата итерации
{
    double max = 0;
    for(int i =0; i < 3; ++i)
        if(max < abs(apr_2[i] - apr_1[i]))
            max = abs(apr_2[i] - apr_1[i]);
    return max;
}

int main()
{
setlocale(LC_ALL,"RUS");

double f[3] = {-1.252, -0.361, -1.052};

double A[3][3] = {
    1.211, 1.103, -2.112,
    1.177, 0.085, -2.979,
    0.245, 2.431, 3.141
};

double D[3][3] = {
    A[0][0], 0, 0,
    0, A[1][1], 0,
    0, 0, A[2][2]
};

for(int i = 0; i < 3; i++){ //D^(-1)
    D[i][i] = 1/D[i][i];
}
double result = 1,  acc = pow(10,-3);

double *apr0 = Approximation0(A, f); //0 приближение, итераци€


double q = norma(A), kf = q / (double)(1-q);

if(checkUp(norma(A))) //ѕроверка на сходимость
{
cout << "q = " << q << endl;
double *apr_2 = Approximation(A,f,apr0);

double *apr_1 = apr0;
while(result >= acc)
    {
         result = kf*max(apr_1,apr_2);

         apr_1 = apr_2;
         apr_2 = Approximation(A,f, apr_2);

         if(result < acc){

             cout << "ѕогрешность при E = 10**(-3): " << round(result*1000)/1000 << endl;
             cout << "ѕриближение значени€ корней при таком E: " << endl;

         }
    }


for(int i = 0; i < 3; ++i){
    cout << "\t" << round(apr_2[i]*1000)/1000 << endl;//до 4х знаков
}
} else cout << "q = " << q;
}
