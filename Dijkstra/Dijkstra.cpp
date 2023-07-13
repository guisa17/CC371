#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> fpair;

void printT(vector<int> T);
void printFranja(vector<fpair> F);


// Estructura de datos Arista
struct arista
{
    int datoDestino;
    arista *sgteArista;
    int peso;
};
typedef arista *parista;


// Estructura de datos Vertice
struct vertice
{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
    bool visited = false;
    int distancia = INT_MAX;
};
typedef vertice *pvertice;


// Clase grafo
class grafo
{
    private:
        pvertice pGrafo;
        int numVerts;
        int numAristas;
    public:
        grafo();
        void insertarVertice(int);
        void insertaArista(int,int, int);
        pvertice buscaVertice(int);
        parista buscaArista(int, int);
        void imprimirGrafo();
        void printDistancias();
        grafo Dijkstra(int);
};


// Constructor
grafo::grafo()
{
    pGrafo = NULL;
    numVerts = 0;
    numAristas = 0;
}


// Insertar vertice
void grafo::insertarVertice(int x)
{
    pvertice p;
    p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgteVertice = pGrafo;
    pGrafo = p;
    numVerts++;
}


// Busca el pvertice dado el dato origen
pvertice grafo::buscaVertice(int n)
{
    pvertice p = pGrafo;

    if (p != NULL)
    {
        while (p->datoOrigen != n && p != NULL)
            p = p->sgteVertice;
    }
    return p;
} 


// Busca el parista dado dos vertices
parista grafo::buscaArista(int x, int y)
{
    pvertice p = buscaVertice(x);
    parista a = p->adyacente;

    while (a != NULL)
    {
        if (a->datoDestino == y) return a;
        a = a->sgteArista;
    }
    return NULL;
}


// Insertar arista
void grafo::insertaArista(int x, int y, int peso)
{
    pvertice p;
    parista a;
    p = buscaVertice(x);

    if (p != NULL)
    {
        a = new arista;
        a->datoDestino = y;
        a->sgteArista = p->adyacente;
        a->peso = peso;
        p->adyacente = a;
    }
}


// Imprime vertices y aristas del grafo
void grafo::imprimirGrafo()
{
    pvertice p;
    parista a;
    p = pGrafo;
    cout << "\nVert || Aristas (Peso)" << endl;

    if (p == NULL)
        cout << "Grafo vacio" << endl;
    else
    {
        while (p != NULL)
        {
            cout << "  " << p->datoOrigen << "  || ";
            a = p->adyacente;

            while (a != NULL)
            {
                cout << a->datoDestino << " (" << a->peso << ")  ";
                a = a->sgteArista;
            }
            cout << endl;
            p = p->sgteVertice;
        }
    }
}


// Encuentra el SPT de Dijkstra
grafo grafo::Dijkstra(int s)
{
    // Creamos el arbol de caminos minimos
    grafo SPT;
    SPT.insertarVertice(s);

    // Vertice que recorrera el grafo dado
    pvertice p;
    p = pGrafo;
    p->distancia = 0;
    p->visited = true;

    // Vectores para T y Franja
    vector<int> T;
    vector<fpair> Franja;

    T.push_back(s);

    do 
    {
        printT(T);
        int v = T.back();
        p = buscaVertice(v);
        parista a = p->adyacente;

        while (a != NULL)
        {
            pvertice verDes = buscaVertice(a->datoDestino);
            int pesoDes = a->peso;
            int camino = p->distancia + pesoDes;

            if (!verDes->visited && camino < verDes->distancia)
            {
                // Buscamos la franja
                verDes->distancia = camino;
                Franja.push_back(make_pair(make_pair(v, verDes->datoOrigen), camino));
            }
            a = a->sgteArista;
        }
        printFranja(Franja);

        p = pGrafo;
        int minDist = INT_MAX;
        fpair tmp;

        // Buscamos el camino minimo
        for (auto fp : Franja)
        {
            int minCam = fp.second;
            if (minCam < minDist)
            {
                minDist = minCam;
                tmp = fp;
            }
        }

        // El camino minimo, agregamos a T
        pii vTemp = tmp.first;
        int v1 = vTemp.first;
        int v2 = vTemp.second;
        T.push_back(v2);
        buscaVertice(v2)->distancia = tmp.second;

        // Eliminamos elementos cuyo segundo elemento sea v2
        Franja.erase(remove_if(Franja.begin(), Franja.end(), [v2](const fpair& fp) {
            return fp.first.second == v2;
        }), Franja.end());

        /*
        // Eliminamos dicho elemento de la Franja
        for (auto fp : Franja)
        {
            if (fp.first.second == v2)
            {
                auto pos = find(Franja.begin(), Franja.end(), fp);
                Franja.erase(pos);
            }
        }*/
        
        p = buscaVertice(v2);
        parista tmpA = buscaArista(v1, v2);
        SPT.insertarVertice(v2);
        SPT.insertaArista(v1, v2, tmpA->peso);
    }
    while (!Franja.empty());

    printT(T);
    printFranja(Franja);

    return SPT;
}


void grafo::printDistancias()
{
    pvertice p = pGrafo;
    while (p != NULL)
    {
        cout << "Hacia " << p->datoOrigen << " es: " << p->distancia << endl;
        p = p->sgteVertice;
    }
}



void printT(vector<int> T)
{
    cout << "T: ";
    for (int v : T) cout << v << " ";
    cout << "\n";
}

void printFranja(vector<fpair> F)
{
    cout << "Franja: ";
    for (auto p : F) 
        cout << p.first.first << "-" << p.first.second << " (" << p.second << ")  ";
    cout << "\n\n";
}


int main()
{
    // Declarar grafo
    grafo g;

    // Insertar los vertices (0-5)
    for (int i = 5; i >= 0; i--)
        g.insertarVertice(i);

    // Insertar las aristas para grafo dirigido
    g.insertaArista(0, 1, 41);
    g.insertaArista(1, 2, 51);
    g.insertaArista(2, 3, 50);
    g.insertaArista(4, 3, 36);
    g.insertaArista(3, 5, 38);
    g.insertaArista(3, 0, 45);
    g.insertaArista(0, 5, 29);
    g.insertaArista(5, 4, 21);
    g.insertaArista(1, 4, 32);
    g.insertaArista(4, 2, 32);
    g.insertaArista(5, 1, 24);
    

    // Se imprime el grafo insertado
    cout << "\nGrafo Original" << endl;
    cout << "==============" << endl;
    g.imprimirGrafo();

    // Buscar el SPT por el algoritmo de Dijkstra
    cout << "\n\nSPT de Dijkstra" << endl;
    cout << "==================" << endl;
    grafo SPT = g.Dijkstra(0);

    cout << "\nDistancias" << endl;
    cout << "==========" << endl;
    g.printDistancias();
    SPT.imprimirGrafo();

    return 0;
}
