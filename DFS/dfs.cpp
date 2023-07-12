
// Implementacion del algoritmo DFS para un grafo no dirigido sin peso

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// Prototipos
void print_format(const string &str);

struct arista 
{
    int datoDestino;
    arista *sgtArista;
    int peso;
};
typedef arista *parista;


struct vertice
{
    int datoOrigen;
    arista *adyacente;
    vertice *sgtVertice;
    int pre;
};
typedef vertice *pvertice;


class grafo
{
    private:
        pvertice pGrafo;
        int cont;
        int numVerts;
        int numAristas;
        
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarAristas(int, int);
        void insertarArista(int, int);
        pvertice buscarVertice(int);
        parista buscarArista(int, int);
        void imprimirGrafo();

        // --- Depth First Search ---
        void algBusqueda(int);
        void DFS(int, string);
};


// Constructor
grafo::grafo()
{
    pGrafo = NULL;
    numVerts = 0;
    numAristas = 0;
}


// Destructor
grafo::~grafo()
{
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;

    while (p != NULL)
    {
        r = p->adyacente;
        while (r != NULL)
        {
            ra = r;
            r = r->sgtArista;
            delete ra;
        }
        rp = p;
        p = p->sgtVertice;
        delete rp;
    }
}


// --- Metodos ---

void grafo::insertarVertice(int x)
{
    pvertice p;
    p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgtVertice = pGrafo;
    pGrafo = p;
    numVerts++;
}


void grafo::insertarAristas(int x, int y)
{
    insertarArista(x, y);
    insertarArista(y, x);
    numAristas++;
}


void grafo::insertarArista(int x, int y)
{
    pvertice p;
    parista a;
    p = buscarVertice(x);
        
    if (p != NULL)
    {
        a = new arista;
        a->datoDestino = y;
        a->sgtArista = p->adyacente;
        p->adyacente = a;
    } 
}


pvertice grafo::buscarVertice(int x)
{
    pvertice p = pGrafo;

    if (p != NULL)
    {
        while (p->datoOrigen != x && p != NULL)
            p = p->sgtVertice;
    }
    return p;
}


parista grafo::buscarArista(int x, int y)
{
    pvertice p;
    parista a;
    p = buscarVertice(x);
    a = p->adyacente;

    while (a != NULL)
    {
        if (a->datoDestino == y)
            return a;
        a = a->sgtArista;
    }
    return nullptr;
}


void grafo::imprimirGrafo()
{
    pvertice p;
    parista a;
    p = pGrafo;

    cout << " Vertice  |  Aristas\n";

    if (p == NULL)
        cout << "Grafo vacio" << endl;
    else
    {
        while (p != NULL)
        {
            cout << "    " <<  setw(2) <<p->datoOrigen << setw(5) << "|";
            a = p->adyacente;

            while (a != NULL)
            {
                cout << "  " << a->datoDestino << "  ";
                a = a->sgtArista;
            }
            cout <<"\n";
            p = p->sgtVertice;
        }
        cout << "\n";
    }
}


void grafo::algBusqueda(int v)
{
    // Inicializar contador del gafo
    cont = 0;

    pvertice p;
    p = pGrafo;

    // Inicializar pre a -1
    while (p != NULL)
    {
        p->pre = -1;
        p = p->sgtVertice;
    }

    // Volver al vertice inicial
    p = buscarVertice(v);

    // Para cada nodo no visitado
    while (p != NULL)
    {
        // DFS para los vertices no visitados
        if (p->pre == -1)
        {
            DFS(p->datoOrigen, "");
        }
        p = p->sgtVertice;
    }
}


void grafo::DFS(int v, string str)
{
    pvertice p;
    parista a;
    p = buscarVertice(v);

    // Actualizar pre
    p->pre = cont++;
    a = p->adyacente;

    cout << str << p->datoOrigen << "\n";

    // Iterar sobre los vecinos de v
    while (a != NULL)
    {
        pvertice w = buscarVertice(a->datoDestino);

        if (w != NULL)
        {
            // DFS para los vecinos no visitados
            if (w->pre == -1)
                DFS(w->datoOrigen, str + "  ");
        }
        a = a->sgtArista;
    }
}



int main()
{
    // Declarar grafo
    grafo g;

    // Insertar los vertices (0-6)
    for (int i = 6; i >= 0; i--)
        g.insertarVertice(i);
    

    // Insertar las aristas para grafo dirigido
    g.insertarAristas(0, 5);
    g.insertarAristas(0, 4);
    g.insertarAristas(0, 3);
    g.insertarAristas(0, 2);
    g.insertarAristas(1, 6);
    g.insertarAristas(4, 6);
    g.insertarAristas(2, 4);
    g.insertarAristas(3, 4);
    g.insertarAristas(1, 4);
    g.insertarAristas(5, 6);
  

    // Se imprime el grafo insertado
    print_format("Grafo Oricginal");
    g.imprimirGrafo();

    // Se imprime el arbol generado DFS
    print_format("DFS del grafo dado");
    g.algBusqueda(0);

    return 0;
}


// Imprimir con formato
void print_format(const string &str)
{
    int n = str.length();
    cout << "+" <<  setfill('-') << setw(n + 3) << "+";
    cout << "\n| " + str + " |\n";
    cout << "+" << setfill('-') << setw(n + 5) << "+\n\n";
    cout << setfill(' ');
}
