#include <iostream>
#include <time.h>
#include <random>
using namespace std;




float RandomDouble(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

int N = 1000;

int main()
{   
    srand(time(NULL));
    double a[N][N], b[N][N], mult[N][N];
    int i, j, k;

    // Storing elements of first matrix.
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
        {
            //cout << "Enter element a" << i + 1 << j + 1 << " : ";
            //cin >> a[i][j];
            a[i][j] = RandomDouble(1, 5);
        }

    // Storing elements of second matrix.
    //cout << endl << "Enter elements of matrix 2:" << endl;
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
        {
            //cout << "Enter element b" << i + 1 << j + 1 << " : ";
            //cin >> b[i][j];
            b[i][j] = RandomDouble(0, 1);
        }

    // Initializing elements of matrix mult to 0.
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
        {
            mult[i][j]=0;
        }

    // Multiplying matrix a and b and storing in array mult.
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
            for(k = 0; k < N; ++k)
            {
                mult[i][j] += a[i][k] * b[k][j];
            }

    // Displaying the multiplication of two matrix.
    cout << endl << "Output Matrix: " << endl;
    for(i = 0; i < N; ++i)
    for(j = 0; j < N; ++j)
    {
        cout << " " << mult[i][j];
        if(j == N - 1)
            cout << endl;
    }

    return 0;
}