#include <bits/stdc++.h>

using namespace std;

// Estructura de los objetos a evaluar
struct Objeto
{
    int peso;
    int valor;
};

typedef vector<vector<int>> table;

// Prototipos
void print_format(const string &str);


int probMochila(int W, Objeto obj[], int n)
{
    // Crear e inicializar tabla con 0s
    table dp(n + 1, vector<int>(W + 1, 0));

    // Se itera sobre los objetos y la capacidad
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            // Verifica si peso actual menor o igual a la capacidad
            if (obj[i - 1].peso <= j)
            {
                // Maximo valor entre tomar o no tomar el objeto
                dp[i][j] = max(obj[i - 1].valor + dp[i - 1][j - obj[i - 1].peso], dp[i - 1][j]);
            }
            else
            {
                // Peso mayor, no se toma
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Devolver maximo valor alcanzable
    return dp[n][W];
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
