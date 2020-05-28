// laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <iostream>
using namespace std;

int** readmat(int N, const char* filename, int &k)
{
    k = 0;
    {
        ifstream f;
        f.open(filename, ios::in);
        char ryad[3000];
        for (int i = 0; i < N; i++)
        {
            f.getline(ryad, 3000);

            cout << ryad << endl;
            for (int i = 0; i < N * 2 - 1; i++)
            {
                if ((ryad[i] != '0') && (ryad[i] != ' '))
                {
                    k += 1;
                }
            }
        }
        f.close();
    }
    ifstream f;
    f.open(filename, ios::in);

    cout << k << endl;
    char ryad[3000];
    int** mat = new int* [k];
    for (int i = 0; i < k; i++)
    {
        mat[i] = new int[3];
    }
    int c = 0;
    for (int i = 0; i < N; i++)
    {
        f.getline(ryad, 3000);

        for (int j = 0; j < N * 2 - 1; j++)
        {
            if ((ryad[j] != '0') && (ryad[j] != ' '))
            {
                mat[c][0] = ryad[j] - int('0'); // znachennya
                mat[c][1] = j / 2; // kolonka de znahodytsya znachennya
                mat[c][2] = i; // ryadok de znahodytsya znachennya
                ++c;
            }
        }
    }
    return mat;
}

void print_row(const int r, int** mat, const int N, const int k)
{
    int j = 0;

    for (int i = 0; i < k; i++)
    {
        if (mat[i][2] == r)
        {
            while (j < mat[i][1])
            {
                cout << '0' << ' ';
                j++;
            }
            cout << mat[i][0] << ' ';
            ++j;
        }

    }
    while (j < N)
    {
        cout << '0' << ' ';
        j++;
    }
    cout << endl;
}
void print_col(const int s, int** mat, const int N, const int k)
{
    int j = 0;
    for (int i = 0; i < k; i++)
    {

        if (mat[i][1] == s)
        {
            while (j < mat[i][2])
            {
                cout << '0' << endl;
                j++;
            }
            cout << mat[i][0] << endl;
            ++j;
        }

    }
    while (j < N)
    {
        cout << '0' << endl;
        j++;
    }
    cout << endl;
}
void print_mat(int** mat, const int N, const int k)
{
    for (int r = 0; r < N; ++r)
    {
       print_row(r, mat, N, k);
    }
}
void get_col(const int s, int** mat, const int N, const int k, int* res_col)
{
    int j = 0;
    for (int i = 0; i < k; i++)
    {

        if (mat[i][1] == s)
        {
            while (j < mat[i][2])
            {
                res_col[j] = 0;
                j++;
            }
            res_col[j] = mat[i][0];
            ++j;
        }

    }
    while (j < N)
    {
        res_col[j] = 0;
        j++;
    }
}
void get_row(const int r, int** mat, const int N, const int k, int* res_row)
{
    int j = 0;
    
    for (int i = 0; i < k; i++)
    {
        
        if (mat[i][2] == r)
        {
            while (j < mat[i][1])
            {
                //cout << '0' << ' ';
                res_row[j] = 0;
                j++;
            }
            res_row [j] = mat[i][0];
            ++j;
        }

    }
    while (j < N)
    {
        res_row[j] = 0;
        j++;
    }
}

int main()
{
    int N = 10;
    int k1 = 0, k2 = 0;

    int** mat1 = readmat(N, "C:\\programuvannya\\10_10.txt", k1);
    int** mat2 = readmat(N, "C:\\programuvannya\\10_10_2.txt", k2);

    for (int i = 0; i < k1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << mat1[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Mat1:" << endl;
    print_mat(mat1, N, k1);
    /*int* res_col = new int[N];
    int r = 0;
    get_col(1, mat1, N, k1, res_col);
    for (int i = 0; i < N; i++)
    {
        cout << res_col[i] << endl;
    }*/

    cout << "Mat2:" << endl;
    print_mat(mat2, N, k2);

    cout << "Mat1 + Mat2" << endl;
    int* res_row1_0 = new int[N];
    int* res_row2_0 = new int[N];
    int* res_sum = new int[N];
    for (int r = 0; r < N; r++)
    {
        get_row(r, mat1, N, k1, res_row1_0); // 1 2 3 
        get_row(r, mat2, N, k2, res_row2_0); // 3 4 5 

        for (int i = 0; i < N; i++)
        {
            res_sum[i] = res_row1_0[i] + res_row2_0[i];
            cout << res_sum[i] << ' ';
        }
        cout << endl;
    }
    delete[] res_sum;
    delete[] res_row1_0;
    delete[] res_row2_0;
    cout << "dobutok matrits " << endl;
    
    int* res_row = new int[N];
    int* res_col = new int[N];
    for (int r = 0; r < N; r++)
    {
        get_row(r, mat1, N, k1, res_row);
        for (int c = 0; c < N; ++c) {
            get_col(c, mat2, N, k2, res_col);
            int sum = 0;
            for (int i = 0; i < N; i++)
            {
                sum = sum + res_row[i] * res_col[i];
            }
            cout << sum << " ";
        }
        cout << endl;
    }
    delete[] res_row;
    delete[] res_col;

    for (int i = 0; i < k1; ++i)
    {
        delete[] mat1[i];
    }
    delete[] mat1;
    for (int i = 0; i < k2; ++i)
    {
        delete[] mat2[i];
    }
    delete[] mat2;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
