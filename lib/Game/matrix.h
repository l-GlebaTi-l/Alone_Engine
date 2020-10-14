bool MatrixObratnaya(double *Matrix);
double* MatrixObratnaya_3d_to_2d(double *Matrix);
bool MatrixObratnaya_3d_to_2d_no_mem_lost(double *Matrix);


bool MatrixObratnaya(double *Matrix)    //  == 1 - succsesfull
{
    double *obrmat = new double[9];
    double MatrixDet;
    MatrixDet = Matrix[0]*Matrix[4]*Matrix[8]
                +Matrix[1]*Matrix[5]*Matrix[6]
                +Matrix[2]*Matrix[3]*Matrix[7]
                -Matrix[2]*Matrix[4]*Matrix[6]
                -Matrix[1]*Matrix[3]*Matrix[8]
                -Matrix[0]*Matrix[5]*Matrix[7];
    if(MatrixDet == 0)
        return 0;
    MatrixDet = 1/MatrixDet;
    obrmat[0] = MatrixDet * (Matrix[4]*Matrix[8] - Matrix[5]*Matrix[7]);
    obrmat[1] = MatrixDet * (Matrix[2]*Matrix[7] - Matrix[1]*Matrix[8]);
    obrmat[2] = MatrixDet * (Matrix[1]*Matrix[5] - Matrix[2]*Matrix[4]);
    obrmat[3] = MatrixDet * (Matrix[5]*Matrix[6] - Matrix[3]*Matrix[8]);
    obrmat[4] = MatrixDet * (Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6]);
    obrmat[5] = MatrixDet * (Matrix[2]*Matrix[3] - Matrix[0]*Matrix[5]);
    obrmat[6] = MatrixDet * (Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6]);
    obrmat[7] = MatrixDet * (Matrix[1]*Matrix[6] - Matrix[0]*Matrix[7]);
    obrmat[8] = MatrixDet * (Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3]);
    for(int i = 0; i < 9; i++)
        Matrix[i] = obrmat[i];
    delete(obrmat);
    return 1;
}

bool MatrixObratnaya(double *Matrix, double *Result)    //  == 1 - succsesfull
{
    double MatrixDet;
    MatrixDet = Matrix[0]*Matrix[4]*Matrix[8]
                +Matrix[1]*Matrix[5]*Matrix[6]
                +Matrix[2]*Matrix[3]*Matrix[7]
                -Matrix[2]*Matrix[4]*Matrix[6]
                -Matrix[1]*Matrix[3]*Matrix[8]
                -Matrix[0]*Matrix[5]*Matrix[7];
    if(MatrixDet == 0)
        return 0;
    MatrixDet = 1/MatrixDet;
    Result[0] = MatrixDet * (Matrix[4]*Matrix[8] - Matrix[5]*Matrix[7]);
    Result[1] = MatrixDet * (Matrix[2]*Matrix[7] - Matrix[1]*Matrix[8]);
    Result[2] = MatrixDet * (Matrix[1]*Matrix[5] - Matrix[2]*Matrix[4]);
    Result[3] = MatrixDet * (Matrix[5]*Matrix[6] - Matrix[3]*Matrix[8]);
    Result[4] = MatrixDet * (Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6]);
    Result[5] = MatrixDet * (Matrix[2]*Matrix[3] - Matrix[0]*Matrix[5]);
    Result[6] = MatrixDet * (Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6]);
    Result[7] = MatrixDet * (Matrix[1]*Matrix[6] - Matrix[0]*Matrix[7]);
    Result[8] = MatrixDet * (Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3]);
    return 1;
}

double* MatrixObratnaya_3d_to_2d(double *Matrix)    //  == 1 - succsesfull
{
    double *obrmat = new double [6];
    double MatrixDet;
    MatrixDet = Matrix[0]*Matrix[4]*Matrix[8]
                +Matrix[1]*Matrix[5]*Matrix[6]
                +Matrix[2]*Matrix[3]*Matrix[7]
                -Matrix[2]*Matrix[4]*Matrix[6]
                -Matrix[1]*Matrix[3]*Matrix[8]
                -Matrix[0]*Matrix[5]*Matrix[7];
    if(MatrixDet == 0)
        return NULL;
    MatrixDet = 1/MatrixDet;
    obrmat[0] = MatrixDet * (Matrix[5]*Matrix[6] - Matrix[3]*Matrix[8]);
    obrmat[1] = MatrixDet * (Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6]);
    obrmat[2] = MatrixDet * (Matrix[2]*Matrix[3] - Matrix[0]*Matrix[5]);
    obrmat[3] = MatrixDet * (Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6]);
    obrmat[4] = MatrixDet * (Matrix[1]*Matrix[6] - Matrix[0]*Matrix[7]);
    obrmat[5] = MatrixDet * (Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3]);
    return obrmat;                                                      /// MEMLOST???  Очень вероятна утечка памяти!!!!!!!!!!!!!!!!
}

bool MatrixObratnaya_3d_to_2d_no_mem_lost(double *Matrix)    //  == 1 - succsesfull
{
    double *obrmat = new double[6];
    double MatrixDet;
    MatrixDet = Matrix[0]*Matrix[4]*Matrix[8]
                +Matrix[1]*Matrix[5]*Matrix[6]
                +Matrix[2]*Matrix[3]*Matrix[7]
                -Matrix[2]*Matrix[4]*Matrix[6]
                -Matrix[1]*Matrix[3]*Matrix[8]
                -Matrix[0]*Matrix[5]*Matrix[7];
    if(MatrixDet == 0)
        return 0;
    MatrixDet = 1/MatrixDet;
    obrmat[0] = MatrixDet * (Matrix[5]*Matrix[6] - Matrix[3]*Matrix[8]);
    obrmat[1] = MatrixDet * (Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6]);
    obrmat[2] = MatrixDet * (Matrix[2]*Matrix[3] - Matrix[0]*Matrix[5]);
    obrmat[3] = MatrixDet * (Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6]);
    obrmat[4] = MatrixDet * (Matrix[1]*Matrix[6] - Matrix[0]*Matrix[7]);
    obrmat[5] = MatrixDet * (Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3]);
    for(int i = 0; i < 6; i++)
        Matrix[i] = obrmat[i];
    delete(obrmat);
    Matrix = (double*)realloc(Matrix,sizeof(double)*6);
    return 1;
}

/**
1)

0 1 2
3 4 5
6 7 8

2)

 0 -1  2
-3  4 -5
 6 -7  8

3)

 0 -3  6
-1  4 -7
 2 -5  8

    obrmat[0] = Matrix[4]*Matrix[8] - Matrix[5]*Matrix[7];
    obrmat[1] = -(Matrix[3]*Matrix[8] - Matrix[5]*Matrix[6]);
    obrmat[2] = Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6];
    obrmat[3] = -(Matrix[1]*Matrix[8] - Matrix[2]*Matrix[7]);
    obrmat[4] = Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6];
    obrmat[5] = -(Matrix[0]*Matrix[7] - Matrix[1]*Matrix[6]);
    obrmat[6] = Matrix[1]*Matrix[5] - Matrix[2]*Matrix[4];
    obrmat[7] = -(Matrix[0]*Matrix[5] - Matrix[2]*Matrix[3]);
    obrmat[8] = Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3];



//    obrmat[0] = Matrix[4]*Matrix[8] - Matrix[5]*Matrix[7];
    obrmat[1] = -(Matrix[1]*Matrix[8] - Matrix[2]*Matrix[7]);   = 3
    obrmat[2] = Matrix[1]*Matrix[5] - Matrix[2]*Matrix[4];      = 6
    obrmat[3] = -(Matrix[3]*Matrix[8] - Matrix[5]*Matrix[6]);   = 1
//    obrmat[4] = Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6];
    obrmat[5] = -(Matrix[0]*Matrix[5] - Matrix[2]*Matrix[3]);   = 7
    obrmat[6] = Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6];      = 2
    obrmat[7] = -(Matrix[0]*Matrix[7] - Matrix[1]*Matrix[6]);   = 5
//    obrmat[8] = Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3];

//    obrmat[0] = Matrix[4]*Matrix[8] - Matrix[5]*Matrix[7];
    obrmat[1] = -(Matrix[1]*Matrix[8] - Matrix[2]*Matrix[7]);   = 1
    obrmat[2] = Matrix[1]*Matrix[5] - Matrix[2]*Matrix[4];      = 2
    obrmat[3] = -(Matrix[3]*Matrix[8] - Matrix[5]*Matrix[6]);   = 3
//    obrmat[4] = Matrix[0]*Matrix[8] - Matrix[2]*Matrix[6];
    obrmat[5] = -(Matrix[0]*Matrix[5] - Matrix[2]*Matrix[3]);   = 5
    obrmat[6] = Matrix[3]*Matrix[7] - Matrix[4]*Matrix[6];      = 6
    obrmat[7] = -(Matrix[0]*Matrix[7] - Matrix[1]*Matrix[6]);   = 7
//    obrmat[8] = Matrix[0]*Matrix[4] - Matrix[1]*Matrix[3];
**/














/*
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

template <typename T> void FreeMem(T **matr, int n);
template <typename T> void PrintMtx(T **matr, int n);
template <typename T> void SetMtx(T **matr, int n);
template <typename T> void TransponMtx(T **matr, T **tMatr, int n);
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol);
int Det(int **matr, int n);

void matrix()
{
    srand((unsigned)time(NULL));
    setlocale(0, "");
    int n, det;
    cout << "Введите размер матрицы: ";
    cin >> n;
    int **matr = new int * [n];
    double **obr_matr = new double * [n];
    double **tobr_matr = new double * [n];
    for(int i = 0; i < n; i++){
        matr[i] = new int[n];
        obr_matr[i] = new double[n];
        tobr_matr[i] = new double[n];
    }
    SetMtx(matr, n);
    PrintMtx(matr, n);
    det = Det(matr, n);
    cout << "Определитель матрицы = " << det << endl;
    if(det){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int m = n - 1;
                int **temp_matr = new int * [m];
                for(int k = 0; k < m; k++)
                    temp_matr[k] = new int[m];
                Get_matr(matr, n, temp_matr, i, j);
                obr_matr[i][j] = pow(-1.0, i + j + 2) * Det(temp_matr, m) / det;
                FreeMem(temp_matr, m);
            }
        }
    }
    else
        cout << "Т.к. определитель матрицы = 0,\nто матрица вырожденная и обратной не имеет!!!" << endl;
    //Транспонирование матрицы
    TransponMtx(obr_matr, tobr_matr, n);
    //Печать обратной матрицы после транспонирования
    PrintMtx(tobr_matr, n);
    FreeMem(tobr_matr, n);
    FreeMem(matr, n);
    FreeMem(obr_matr, n);
}
//Функция транспонирования матрицы
template <typename T> void TransponMtx(T **matr, T **tMatr, int n){//
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tMatr[j][i] = matr[i][j];
}
//Функция освобождения памяти
template <typename T> void FreeMem(T **matr, int n)
{
    for(int i = 0; i < n; i++)
        delete [] matr[i];
    delete [] matr;
}

//функция заполнения матрицы
template <typename T> void SetMtx(T **matr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand()%9 + 1;
}

//функция печати матрицы
template <typename T> void PrintMtx(T **matr, int n)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << matr[i][j] << " ";
        cout << endl;
    }
}
//функция вычеркивания строки и столбца
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol)
{
    int ki = 0;
    for (int i = 0; i < n; i++){
        if(i != indRow){
            for (int j = 0, kj = 0; j < n; j++){
                if (j != indCol){
                    temp_matr[ki][kj] = matr[i][j];
                    kj++;
                }
            }
            ki++;
        }
    }
}

//==============================================================================================================
//                              вычисление определителя
//==============================================================================================================
//функция вычисления определителя матрицы
int Det(int **matr, int n)
{
    int temp = 0;   //временная переменная для хранения определителя
    int k = 1;      //степень
    if(n < 1){
        cout<<"Не верный размер матрицы!!!" << endl;
        return 0;
    }
    else if (n == 1)
        temp = matr[0][0];
    else if (n == 2)
        temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
    else{
        for(int i = 0; i < n; i++){
            int m = n - 1;
            int **temp_matr = new int * [m];
            for(int j = 0; j < m; j++)
                temp_matr[j] = new int [m];
            Get_matr(matr, n, temp_matr, 0, i);
            temp = temp + k * matr[0][i] * Det(temp_matr, m);
            k = -k;
            FreeMem(temp_matr, m);
        }
    }
    return temp;
}
*/
