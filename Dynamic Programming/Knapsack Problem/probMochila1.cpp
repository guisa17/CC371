#include <bits/stdc++.h>

using namespace std;

// Estructura de los objetos a evaluar
struct Objeto
{
    int peso;
    int valor;
};


// Prototipos
void print_format(const string &str);


int probMochilaRec(int W, Objeto obj[], int i, int** dp)
{
    // Casos base
	if (i < 0) return 0;	
    if (dp[i][W] != -1) return dp[i][W];

    // Peso mayor a la capacidad
	if (obj[i].peso > W) 
    {
        // Evaluamos el caso en el que no se considera ese objeto
		dp[i][W] = probMochilaRec(W, obj, i - 1, dp);
		return dp[i][W];
	}

	else 
    {
        // Evaluamos para ambos objetos y elegimos el de mayor valor
		dp[i][W] = max(obj[i].valor + probMochilaRec(W - obj[i].peso, obj, i - 1, dp),
					            probMochilaRec(W, obj, i - 1, dp));
		return dp[i][W];
	}
}


int probMochila(int W, Objeto obj[], int n)
{
    // Crear dinamicamente la tabla
    int **dp;
    dp = new int*[n];
    for (int i = 0; i < n; i++) dp[i] = new int[W + 1];

    // Inicializar con -1
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < W + 1; j++)
            dp[i][j] = -1;
    }

    return probMochilaRec(W, obj, n - 1, dp);
}


int main()
{
    // Cantidad y capacidad
    int n, W;

    // Solicitar los valores
    print_format("El Problema de la Mochila");
    cout << "[>] Cantidad de objetos: ";
    cin >> n;
    cout << "[>] Capacidad de la mochila: ";
    cin >> W;

    Objeto obj[n];

    cout << "\n[>] Pesos de los objetos: ";
    for (int i = 0; i < n; i++) cin >> obj[i].peso;

    cout << "[>] Valores de los objetos: ";
    for (int i = 0; i < n; i++) cin >> obj[i].valor;

    // Resolver el problema
    cout << "\n\n";
    print_format("Maximo valor posible");
    cout << "[>] El valor maximo que se puede llevar en la mochila es ";
    cout << probMochila(W, obj, n) << ".\n\n";
    return 0;
}


// Imprimir con formato
void print_format(const string &str)
{
    int n = str.length();
    cout << "+" <<  setfill('-') << setw(n + 3) << "+";
    cout << "\n| " + str + " |\n";
    cout << "+" << setfill('-') << setw(n + 5) << "+\n\n";
}
