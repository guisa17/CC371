#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef vector<vector<int>> matrix;
typedef pair<int, int> pi;


/*
    Idea para la implementacion de divide y 
    venceras para multiplicacion de matrices

    [1 2 3 4]       [1 2 | 3 4]
    [5 6 7 8]   ->  [5 6 | 7 8]
    [9 0 1 2]       -----------
    [2 1 3 4]       [9 0 | 1 2]
                    [2 1 | 3 4]

    [1 2]       ->  [1 | 2]
    [5 6]           -------
                    [5 | 6]

    Y asi sucesivamente

    e.g.
    1 2 3 4
    5 6 7 8

    0 1
    9 7
    2 -1
    1 2

    28 20
    76 56
*/


// Prototipos
matrix mult_matrix(const matrix &A, const matrix &B, int dim);
vector<matrix> get_submatrices(const matrix &A, int dim);
matrix get_submatrix(const matrix &A, int iniRow, int endRow, int iniCol, int endCol);
matrix sum_matrix(const matrix &A, const matrix &B, int n);
void fill_matrix(matrix &A, const pi &dim, const string &str);
void print_matrix(const matrix &A, const pi &dim, const string &str);
void print_format(const string &str);

    
int main()
{
    // Matrices a ser multiplicadas
    matrix A, B, C;
    pi dimA, dimB, dimC;

    // Solicitar las dimensiones de las matrices
    print_format("Ingrese las dimensiones");
    cout << "Dimensiones de A: ";
    cin >> dimA.first >> dimA.second;
    cout << "Dimensiones de B: ";
    cin >> dimB.first >> dimB.second;
    cout << "\n";

    // Verificar si es posible multiplicar
    if (dimA.second != dimB.first)
    {
        print_format("Dimensiones invalidas");
        return 1;
    }
    dimC = make_pair(dimA.first, dimB.second);


    // Definimos dimension potencia de 2
    int dim = pow(2, (max({dimA.first, dimA.second, 
                            dimB.first, dimB.second}) + 1) / 2);

    // Inicializar las matrices
    A.resize(dim, vector<int>(dim, 0));
    B.resize(dim, vector<int>(dim, 0));

    // Llenar con valores
    print_format("Llenamos las matrices");
    fill_matrix(A, dimA, "Matriz A");
    fill_matrix(B, dimB, "Matriz B");

    // Imprimir las matrices
    print_format("Multiplicacion de Matrices A x B = C");
    print_matrix(A, dimA, "Matriz A");
    print_matrix(B, dimB, "Matriz B");

    // Calcular la multiplicacion
    C = mult_matrix(A, B, dim);
    print_matrix(C, dimC, "Matriz C");

    return 0;
}


// Funcion que multiplica matrices por "divide y venceras"
matrix mult_matrix(const matrix &A, const matrix &B, int dim)
{
    // Caso base de matrices 1x1 
    if (dim == 1)
    {
        matrix C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;        
    }

    // Hallar las submatrices
    int half = dim / 2;
    vector<matrix> Aij = get_submatrices(A, dim);
    vector<matrix> Bij = get_submatrices(B, dim);

    // Aij[0] = A11, Aij[1] = A12, Aij[2] = A21, Aij[3] = A22

    // Realizar las multiplicaciones de forma recursiva
    matrix C11 = sum_matrix(mult_matrix(Aij[0], Bij[0], half), 
                            mult_matrix(Aij[1], Bij[2], half), half);
    
    matrix C12 = sum_matrix(mult_matrix(Aij[0], Bij[1], half), 
                            mult_matrix(Aij[1], Bij[3], half), half);

    matrix C21 = sum_matrix(mult_matrix(Aij[2], Bij[0], half), 
                            mult_matrix(Aij[3], Bij[2], half), half);   

    matrix C22 = sum_matrix(mult_matrix(Aij[2], Bij[1], half), 
                            mult_matrix(Aij[3], Bij[3], half), half);

    // Combinar los resultados
    matrix C(dim, vector<int>(dim, 0));
    
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
    return C;
}


// Funcion que devuelve todas las submatrices de una matriz
vector<matrix> get_submatrices(const matrix &A, int dim)
{
    vector<matrix> submatrices;
    int half = dim / 2;

    matrix A11 = get_submatrix(A, 0, half - 1, 0, half - 1);
    matrix A12 = get_submatrix(A, 0, half - 1, half, dim - 1);
    matrix A21 = get_submatrix(A, half, dim - 1, 0, dim - 1);
    matrix A22 = get_submatrix(A, half, dim - 1, half, dim - 1);

    submatrices.push_back(A11);
    submatrices.push_back(A12);
    submatrices.push_back(A21);
    submatrices.push_back(A22);

    return submatrices;
}


// Funcion que devuelve una submatriz dada las posiciones
matrix get_submatrix(const matrix &A, int iniRow, int endRow, int iniCol, int endCol)
{
    matrix submatrix;

    for (int i = iniRow; i <= endRow; i++)
    {
        vector<int> row;
        for (int j = iniCol; j <= endCol; j++)
        {
            row.push_back(A[i][j]);
        }
        submatrix.push_back(row);
    }
    return submatrix;
}


// Funcion que suma dos matrices en otra
matrix sum_matrix(const matrix &A, const matrix &B, int n)
{
    matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}
    

// Funcion que llena los valores de la matriz
void fill_matrix(matrix &A, const pi &dim, const string &str)
{
    cout << "Para la " + str + ":\n";
    for (int i = 0; i < dim.first; i++)
    {
        for (int j = 0; j < dim.second; j++)
            cin >> A[i][j];
    }
    cout << "\n";
}


// Funcion que imprime los valores de la matriz
void print_matrix(const matrix &A, const pi &dim, const string &str)
{
    cout << str << "\n";
    for (int i = 0; i < dim.first; i++)
    {
        cout << "[ ";
        for (int j = 0; j < dim.second; j++)
            cout << setfill(' ') << setw(3) << A[i][j] << "  ";
        cout << " ]\n";
    }
    cout << "\n";
}


// Imprimir con formato
void print_format(const string &str)
{
    int n = str.length();
    cout << "+" <<  setfill('-') << setw(n + 3) << "+";
    cout << "\n| " + str + " |\n";
    cout << "+" << setfill('-') << setw(n + 5) << "+\n\n";
}
