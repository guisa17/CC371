#include <iostream>
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
};
typedef vertice *pvertice;


class grafo
{
    private:
        pvertice pGrafo;
        int numVerts;
        int numAristas;
        
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarAristas(int, int, int);
        void insertarArista(int, int, int);
        pvertice buscarVertice(int);
        parista buscarArista(int, int);
        void imprimirGrafo();
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


// Para grafo no dirigido
void grafo::insertarAristas(int x, int y, int peso)
{
    insertarArista(x, y, peso);
    insertarArista(y, x, peso);
    numAristas++;
}


void grafo::insertarArista(int x, int y, int peso)
{
    pvertice p;
    parista a;
    p = buscarVertice(x);
        
    if (p != NULL)
    {
        a = new arista;
        a->datoDestino = y;
        a->sgtArista = p->adyacente;
        a->peso = peso;
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

    cout << " Vertice  |  Aristas (Peso)\n";

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
                cout << "  " << a->datoDestino << "  (" << setw(2) << a->peso << ")   ";
                a = a->sgtArista;
            }
            cout <<"\n";
            p = p->sgtVertice;
        }
        cout << "\n";
    }
}


int main()
{
    // Declarar grafo
    grafo g;

    // Insertar los vertices
    g.insertarVertice(4);
    g.insertarVertice(6);
    g.insertarVertice(3);
    g.insertarVertice(1);
    g.insertarVertice(2);

    // Insertar las aristas para grafo dirigido
    g.insertarArista(4, 6, 4);
    g.insertarArista(3, 6, 10);
    g.insertarArista(3, 4, 5);
    g.insertarArista(1, 3, 7);
    g.insertarArista(2, 6, 10);
    g.insertarArista(1, 2, 1);
  

    // Se imprime el grafo insertado
    print_format("Grafo Original");
    g.imprimirGrafo();

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
