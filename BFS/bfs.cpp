
// Implementacion del algoritmo BFS para un grafo no dirigido sin peso

#include <iostream>
#include <queue>
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
    int ord = -1;
};
typedef vertice *pvertice;


class grafo
{
    private:
        pvertice pGrafo;
        int cont;
        queue<pvertice> cola;
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
        void BFS(int);
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


void grafo::BFS(int r)
{
    // Inicializar contador del grafo
    cont = 0;

    pvertice p;
    parista a;
    p = buscarVertice(r);

    // Insertar a la cola
    cola.push(p);

    // Mientras la cola no este vacia
    while (!cola.empty())
    {
        // Sacar el elemento que este primero
        pvertice v = cola.front();
        cola.pop();

        // Si vertice no visitado
        if (v->ord == -1)
        {
            // Imprimir el recorrido
            cout << v->datoOrigen << "  ";

            // Actualizar ord
            v->ord = cont++;
            a = v->adyacente;

            // Iterar sobre los vecinos de v
            while (a != NULL)
            {
                // Vecino w
                pvertice w = buscarVertice(a->datoDestino);
                
                if (w != NULL)
                {
                    // Insertar a la cola
                    if (w->ord == -1)
                        cola.push(w);
                    
                    // Siguiente arista
                    a = a->sgtArista;
                }
            }
        }
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
    g.insertarAristas(0, 4);
    g.insertarAristas(0, 1);
    g.insertarAristas(1, 5);
    g.insertarAristas(3, 6);
    g.insertarAristas(3, 5);
    g.insertarAristas(4, 6);
    g.insertarAristas(5, 6);
  

    // Se imprime el grafo insertado
    print_format("Grafo Original");
    g.imprimirGrafo();

    // Se imprime el camino generado BFS
    print_format("BFS del grafo dado");
    cout << "Camino obtenido: ";
    g.BFS(0);

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
