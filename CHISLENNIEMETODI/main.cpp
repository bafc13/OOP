#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <locale.h>
using namespace std ;


//double* Approximation(double D[4][4], double L[4][4], double U[4][4], double apr[4], double f[4]) //Все остальные приближения
//{
//    double* arr = new double[4];

////    for(int i = 0; i < 4; ++i){
////        for(int j = 0; j < 4; ++j){
////            cout << L[i][j] << "\t";
//////            cout << U[i][j] << endl;
////        }cout << endl;
////    }cout << endl;

////    for(int i = 0; i < 4; ++i){
////        for(int j = 0; j < 4; ++j){
//////            cout << L[i][j] << "\t";
////            cout << U[i][j] << "\t";
////        }cout << endl;
////    }cout << endl;



//    double mainarr1[4][4], mainarr2[4]; // L + U
//    for(int i = 0; i < 4; ++i){
//        for(int j = 0; j < 4; ++j){
//            mainarr1[i][j] = L[i][j] + U[i][j];
//        }
//    }



////    for(int i = 0; i < 4; ++i){
////        for(int j = 0; j < 4; ++j){
////            cout << mainarr1[i][j] << "\t";
//////            cout << L[i][j] + U[i][j] << endl;
////        }cout << endl;
////    }

//    //D * (L + U)
//    for(int i = 0; i < 4; i++){
//        for(int j = 0; j <4; j++){
//            mainarr1[i][j] += D[i][i] * mainarr1[i][j];
//        }
//    }


//    double mainarr3[4];
//    for (int i = 0; i < 4; ++i){ //D * (L + U) * x
//        double main = 0;
//        for (int j = 0; j < 4; ++j){
//            main += mainarr1[i][j]*apr[i];
//        }
//        mainarr3[i] = main;
//    }

//    for(int i = 0; i < 4; ++i){ //D * f
//        mainarr2[i] = D[i][i] * f[i];
//    }

//    for(int i = 0; i < 4; ++i){ //result
//        arr[i] = mainarr2[i] - mainarr3[i];
//    }

//    return arr;
//}



bool checkUp(double norma){ //Выполнение условия
    return norma < 1;
}

double* Aproximation0(double linSystem[4][5]) //0 приближение
{
    double* arr = new double[4];
    for(int i = 0; i < 4; ++i){
        arr[i] = linSystem[i][4]/linSystem[i][i];
    }
    return arr;
}

double* Aproximation(double linSystem[4][5], double apr[4]) //Все остальные приближения
{
    double* arr = new double[4];
    for (int i = 0; i < 4; ++i) {
        double sum = 0;
        for (int j = 0; j < 4; ++j) {
            if (j != i) {
                sum += linSystem[i][j] * apr[j];
            }
        }
        arr[i] = (1 / linSystem[i][i]) * (linSystem[i][4] - sum);
    }
    return arr;
}

double norma(double linSystem[4][5])  //норма матрицы по строке
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

double max(double apr_1[4], double apr_2[4]) //проверка результата итерации
{
    double max = 0;
    for(int i =0; i < 4; ++i)
        if(max < abs(apr_2[i] - apr_1[i]))
            max = abs(apr_2[i] - apr_1[i]);
    return max;
}

//            14, 6, 3, 5, 12,
//            9, 12, 2, 0, 5,       начальная
//            5, 1, 13, 5, 2,       система
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

double *apr0 = Aproximation0(linSystem); //0 приближение, итерация

int it1, it2, it3 = 0; //кол-во итераций для достижения 1, 2 и 3 точностей
bool flag1 = true, flag2 = true;

double q = norma(linSystem), kf = q / (1-q);

if(checkUp(norma(linSystem))) //Проверка на сходимость
{
cout << "q = " << q << endl;
double *apr_2 = Aproximation(linSystem, apr0);
double *apr_1 = apr0;
while(result >= acc3)
    {
         result = kf*max(apr_1,apr_2);
         apr_1 = apr_2;
         apr_2 = Aproximation(linSystem, apr_2);
         if(result < acc1 && flag1 == true){
             it1 = it3;
             cout << "Погрешность при E = 10**(-2): " << round(result*1000)/1000 << endl;
             cout << "Приближение значения корней при таком E: " << endl;

             for(int i = 0; i < 4; ++i){
                cout << "\t" << round(apr_2[i]*1000)/1000 << endl; //округлять до 2х знаков тут
             }
             flag1 = false;
        }
        if(result < acc2 && flag2 == true){
             it2 = it3;
             cout << "Погрешность при E = 10**(-3): " << round(result*10000)/10000 << endl;
             cout << "Приближение значения корней при таком E: " << endl;

             for(int i = 0; i < 4; ++i){
                 cout << "\t" << round(apr_2[i]*10000)/10000 << endl; //до 3х знаков
             }
             flag2 = false;
        }
        it3++;
    }

cout << "Погрешность при E = 10**(-4): " << round(result*100000)/100000<< endl;
cout << "Приближение значения корней при таком Е: " << endl;

for(int i = 0; i < 4; ++i){
    cout << "\t" << round(apr_2[i]*100000)/100000 << endl;//до 4х знаков
}
cout << "Количество итераций до E = 10**(-4): " << it3-1 << endl;
cout << "Количество итераций до E = 10**(-3): " << it2 << endl;
cout << "Количество итераций до E = 10**(-2): " << it1 << endl;
} else cout << "q = " << q;
}
