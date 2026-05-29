/*
   Simulador de Equipaje en una Bodega de Avion
   Ejercicio 2 utilizando pilas (Equipo Azul).
*/

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <cctype>
using namespace std;

// Pasa el texto a mayusculas para que "m01" y "M01" sean la misma maleta.
string aMayusculas(string texto)
{
    for (int i = 0; i < (int)texto.length(); i++)
        texto[i] = toupper((unsigned char)texto[i]);
    return texto;
}

// Fecha y hora actual ajustada a Republica Dominicana (UTC-4). El ajuste
// manual evita depender de la zona horaria del servidor (ej. OnlineGDB).
string fechaHoraActual()
{
    time_t ahora = time(0);
    ahora = ahora - 4 * 3600;
    tm* t = gmtime(&ahora);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", t);

    return string(buffer);
}

// Cada maleta es un nodo de la pila. Guarda su ID, la fecha y hora en
// que fue cargada y el puntero a la maleta que esta debajo de ella.
class Maleta
{
public:
    string id;
    string fechaHora;
    Maleta* siguiente;

    Maleta(string i, string fh)
    {
        id = i;
        fechaHora = fh;
        siguiente = nullptr;
    }
};

// La bodega funciona como una pila (LIFO). Para sacar una maleta que no
// esta en el tope se apartan las de encima en una pila auxiliar y luego
// se devuelven a su lugar.
class Bodega
{
private:
    Maleta* tope;       // Punta de la pila (maleta de arriba)
    int cantidad;       // Cantidad actual de maletas en la bodega

public:
    Bodega()
    {
        tope = nullptr;
        cantidad = 0;
    }

    // Complejidad: O(1) - solo revisa el tope
    bool estaVacia()
    {
        return tope == nullptr;
    }

    // Complejidad: O(1) - devuelve el contador ya guardado
    int contarMaletas()
    {
        return cantidad;
    }

    // Devuelve true si ya hay una maleta con ese ID.
    // Complejidad: O(n) - recorre la pila comparando los IDs
    bool existe(string id)
    {
        Maleta* temp = tope;
        while (temp != nullptr)
        {
            if (temp->id == id)
                return true;
            temp = temp->siguiente;
        }
        return false;
    }

    // Apila una maleta nueva. Rechaza IDs vacios o repetidos.
    // Complejidad: O(n) - usa existe() para revisar duplicados
    void agregar(string id)
    {
        id = aMayusculas(id);

        if (id == "")
        {
            cout << " El ID de la maleta no puede estar vacio." << endl;
            return;
        }

        if (existe(id))
        {
            cout << " Ya hay una maleta con el ID " << id << " registrada en el sistema." << endl;
            return;
        }

        // La nueva maleta queda en el tope, apuntando a la que estaba encima
        string fh = fechaHoraActual();
        Maleta* nueva = new Maleta(id, fh);
        nueva->siguiente = tope;
        tope = nueva;
        cantidad++;

        cout << " Maleta " << id << " agregada a la bodega (" << fh << ")." << endl;
    }

    // Saca la maleta indicada sin importar su posicion. Si esta tapada,
    // aparta las de encima en una pila auxiliar, cuenta las maniobras y
    // al final las devuelve a su lugar.
    // Complejidad: O(n) - en el peor caso mueve toda la pila
    void retirar(string id)
    {
        id = aMayusculas(id);

        if (estaVacia())
        {
            cout << " La bodega esta vacia, no hay maletas para retirar." << endl;
            return;
        }

        Maleta* auxiliar = nullptr;   // Aqui se apartan las maletas que bloquean
        int maniobras = 0;

        // Sacamos del tope y apartamos en la auxiliar hasta dar con la buscada
        while (tope != nullptr && tope->id != id)
        {
            Maleta* temp = tope;
            tope = tope->siguiente;
            temp->siguiente = auxiliar;
            auxiliar = temp;
            maniobras++;
        }

        // Si llegamos al fondo sin encontrarla, no existe: devolvemos todo
        if (tope == nullptr)
        {
            while (auxiliar != nullptr)
            {
                Maleta* temp = auxiliar;
                auxiliar = auxiliar->siguiente;
                temp->siguiente = tope;
                tope = temp;
            }

            cout << " La maleta " << id << " no se encuentra en la bodega." << endl;
            return;
        }

        Maleta* retirada = tope;
        tope = tope->siguiente;
        cantidad--;

        cout << " Maleta " << retirada->id << " retirada con " << maniobras;

        if (maniobras == 1)
            cout << " maniobra." << endl;
        else
            cout << " maniobras." << endl;

        delete retirada;

        // Devolvemos las apartadas a la bodega en su orden original
        while (auxiliar != nullptr)
        {
            Maleta* temp = auxiliar;
            auxiliar = auxiliar->siguiente;

            temp->siguiente = tope;
            tope = temp;
        }
    }

    // Lista las maletas de la primera ingresada a la ultima, en una linea.
    // Usa una pila auxiliar para invertir el recorrido sin perder el orden.
    // Complejidad: O(n) - recorre toda la pila
    void mostrar()
    {
        if (estaVacia())
        {
            cout << " La bodega esta vacia." << endl;
            return;
        }

        Maleta* auxiliar = nullptr;

        // Al pasar todo a la auxiliar el orden se invierte (la primera arriba)
        while (tope != nullptr)
        {
            Maleta* temp = tope;
            tope = tope->siguiente;
            temp->siguiente = auxiliar;
            auxiliar = temp;
        }

        cout << " Estado actual: ";

        bool primera = true;   // Para separar con comas

        // Las mostramos y de paso las devolvemos (la bodega queda como estaba)
        while (auxiliar != nullptr)
        {
            if (!primera)
                cout << ", ";

            cout << auxiliar->id;

            Maleta* temp = auxiliar;
            auxiliar = auxiliar->siguiente;
            temp->siguiente = tope;
            tope = temp;

            primera = false;
        }

        cout << endl;
    }

    // Busca una maleta por su ID y muestra sus datos y su posicion.
    // Complejidad: O(n) - recorre hasta encontrarla o llegar al fondo
    void buscar(string id)
    {
        id = aMayusculas(id);

        if (estaVacia())
        {
            cout << " La bodega esta vacia." << endl;
            return;
        }

        Maleta* temp = tope;
        int posicion = 1;

        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                cout << " Maleta encontrada:" << endl;
                cout << "   ID       : " << temp->id << endl;
                cout << "   Cargada  : " << temp->fechaHora << endl;
                cout << "   Posicion : " << posicion << " (1 = tope / arriba)" << endl;
                return;
            }
            temp = temp->siguiente;
            posicion++;
        }

        cout << " La maleta " << id << " no se encuentra en la bodega." << endl;
    }

    // Libera la memoria de todas las maletas al cerrar.
    // Complejidad: O(n) - elimina cada maleta una por una
    ~Bodega()
    {
        Maleta* temp = tope;
        while (temp != nullptr)
        {
            Maleta* aux = temp;
            temp = temp->siguiente;
            delete aux;
        }
    }
};

int main()
{
    Bodega bodega;
    int opcion;
    string id;

    do
    {
        cout << "\n==================================================" << endl;
        cout << "          SISTEMA DE CONTROL DE EQUIPAJE" << endl;
        cout << "                EN BODEGA DE AVION" << endl;
        cout << "==================================================" << endl;
        cout << "   Maletas en la bodega: " << bodega.contarMaletas() << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "   [1] Agregar maleta" << endl;
        cout << "   [2] Retirar maleta" << endl;
        cout << "   [3] Buscar maleta" << endl;
        cout << "   [4] Mostrar estado de la bodega" << endl;
        cout << "   [0] Salir" << endl;
        cout << "==================================================" << endl;
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Entrada invalida. Debe ingresar un numero." << endl;
            opcion = -1;   // Evita que el 0 que deja cin al fallar se confunda con Salir
            continue;
        }

        switch (opcion)
        {
            case 1:
                cout << " >> AGREGAR MALETA" << endl;

                // Agrega maletas seguidas; con 0 vuelve al menu
                while (true)
                {
                    cout << " Ingrese el ID de la maleta (0 para volver al menu): ";
                    cin >> id;

                    if (id == "0")
                        break;

                    bodega.agregar(id);
                    cout << endl;
                }
                break;

            case 2:
                cout << " >> RETIRAR MALETA" << endl;

                // Retira maletas seguidas; con 0 vuelve al menu
                while (true)
                {
                    cout << " Ingrese el ID de la maleta a retirar (0 para volver al menu): ";
                    cin >> id;

                    if (id == "0")
                        break;

                    bodega.retirar(id);
                    cout << endl;

                    // Si ya no quedan maletas, vuelve al menu solo
                    if (bodega.estaVacia())
                    {
                        cout << " La bodega quedo vacia. Volviendo al menu." << endl;
                        break;
                    }
                }
                break;

            case 3:
                cout << " >> BUSCAR MALETA" << endl;

                // Busca maletas seguidas; con 0 vuelve al menu
                while (true)
                {
                    cout << " Ingrese el ID de la maleta a buscar (0 para volver al menu): ";
                    cin >> id;

                    if (id == "0")
                        break;

                    bodega.buscar(id);
                    cout << endl;
                }
                break;

            case 4:
                cout << " >> ESTADO DE LA BODEGA" << endl;
                bodega.mostrar();
                break;

            case 0:
                cout << " Cerrando el sistema de bodega." << endl;
                break;

            default:
                cout << " Opcion invalida, intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}

/*
   Analisis de complejidad (Big O)

   Aqui n es la cantidad de maletas que hay en la bodega.

   Hay funciones que no recorren la pila, solo hacen una operacion directa,
   asi que su tiempo no cambia aunque haya mas maletas. Esas son O(1):
   estaVacia, contarMaletas, fechaHoraActual y aMayusculas.

   Otras si tienen que recorrer la pila de principio a fondo, por lo que su
   tiempo crece con la cantidad de maletas. Esas son O(n): existe, agregar,
   retirar, mostrar, buscar y el destructor. Dos detalles: "agregar" apila en
   un solo paso, pero llama a "existe()" para no repetir IDs y ese recorrido
   lo vuelve O(n); y "retirar" es la mas costosa, porque cuando la maleta esta
   al fondo mueve toda la pila a la auxiliar y luego la devuelve.

   El programa funciona con un menu que se repite mientras el usuario opera.
   Si hace k operaciones y cada una cuesta hasta O(n), el total lo marca:

   Tiempo total = O(k * n)

   Es decir, el costo crece con la cantidad de maletas (n) y con cuantas
   veces se use el menu (k).
*/