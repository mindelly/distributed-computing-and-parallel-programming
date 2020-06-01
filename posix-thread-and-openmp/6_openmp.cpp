#include <iostream>
#include <cstdlib> // для system
#include <string.h>
#include <stdio.h>
#include <omp.h>
using namespace std;

int NUM_THREADS = 8;

float RandomDouble(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

int main() {
    omp_set_num_threads(NUM_THREADS);
    double s = 1;
    const int n = 500; // размерность матрицы
    double A[n][n]; // матрица коэффициентов
    double sum = 0, sum1;
    double b[n]; // вектор-столбец свободных членов

    // Ввод столбца свободных членов
    //cout << "b: ";
    #pragma omp parallel for
        for (int i = 0; i < n; i++){
            b[i] = RandomDouble(1, 10);
        }

    
    // Ввод матрицы A
    #pragma omp parallel for
        for (int i = 0; i < n; i++) { 
            for (int j = 0; j < n; j++){
                A[i][j] = RandomDouble(1, 10);

            }
        }
    

    double L[n][n];
    double U[n][n];

    int i, j, k;

    #pragma omp parallel for firstprivate (j, k, sum) lastprivate(i) shared(A, L, U)
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                U[0][i] = A[0][i];
                L[i][0] = A[i][0] / U[0][0];
                sum = 0;
                for (int k = 0; k < i; k++){
                    sum += L[i][k] * U[k][j];
                }
                U[i][j] = A[i][j] - sum;
                if (i > j){
                    L[j][i] = 0;
                }
                else{
                    sum = 0;
                    for (int k = 0; k < i; k++){
                        sum += L[j][k] * U[k][i];
                    }
                    L[j][i] = (A[j][i] - sum) / U[i][i];
                }
            }
        }
    // Печать матрицы U
    /*cout << endl;
    for (int i = 0; i < n; i++) { //перебор строк
        for (int j = 0; j < n; j++) { //вывод одной строки
        cout << U[i][j] << " ";
    }
    
    cout << endl; 
    }
    // Печать матрицы L
    cout << endl;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
        cout << L[i][j] << " ";
    }
    
    cout << endl; 
    }*/


// Объявление векторов и сумм для их вычисления
double y[n];
double x[n];
double sum2, sum3;
// Вычисление y

y[0] = b[0];

#pragma omp parallel for
    for (int h = 1; h < n; h++){
        sum2 = 0;
        for (int p = 0; p < h; p++){
            sum2 += L[h][p] * y[p];
        }
        y[h] = b[h] - sum2;
    }

// Вычисление x
x[n - 1] = y[n - 1] / U[n - 1][n - 1];

#pragma omp parallel for
    for (int i = 2; i <= n; i++){
        sum3 = 0;
        for (int p = 0; p < i; p++){
            sum3 += U[n - i][n - p] * x[n - p];
        }
        x[n - i] = (1 / U[n - i][n - i])*(y[n - i] - sum3);
    }


//cout << endl;

// Вывод искомого вектора x
//cout << "X: ";


/*for (int j = 0; j < n; j++){
    cout << " " << x[j] << " ";
}*/



return 0;
}