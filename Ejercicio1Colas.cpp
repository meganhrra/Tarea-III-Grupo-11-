/*

Ejercicio 1
Sistema de Turnos para Banco
Simule un sistema de atención al cliente por orden de llegada. Se deben registrar clientes con nombre y asunto, y atenderlos en orden FIFO.
--- Entrada: “registrar “, “atender”, “mostrar” ---
--- Salida esperada: “Atendiendo a Juan: Retiro de efectivo” ---

*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Estructura para almacenar los datos del cliente
struct Cliente {
    string nombre;
    string asunto;
};

int main() {
    queue<Cliente> cola;
    string opcion;

    // Datos de prueba
    cola.push({"Juan", "Retiro de efectivo"});
    cola.push({"Maria", "Deposito"});
    cola.push({"Carlos", "Pago de tarjeta"});
    cola.push({"Ana", "Solicitud de prestamo"});

    do {
        cout << "\n--- SISTEMA DE TURNOS BANCO ---" << endl;
        cout << "1. registrar" << endl;
        cout << "2. atender" << endl;
        cout << "3. mostrar" << endl;
        cout << "4. salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == "registrar" || opcion == "1") {
            Cliente cliente;

            cin.ignore();

            cout << "Ingrese el nombre del cliente: ";
            getline(cin, cliente.nombre);

            cout << "Ingrese el asunto: ";
            getline(cin, cliente.asunto);

            cola.push(cliente);

            cout << "Cliente registrado correctamente." << endl;
        }
        else if (opcion == "atender" || opcion == "2") {

            if (!cola.empty()) {
                Cliente cliente = cola.front();

                cout << "Atendiendo a "
                     << cliente.nombre
                     << ": "
                     << cliente.asunto
                     << endl;

                cola.pop();
            }
            else {
                cout << "No hay clientes en espera." << endl;
            }
        }
        else if (opcion == "mostrar" || opcion == "3") {

            if (!cola.empty()) {

                queue<Cliente> temp = cola;

                cout << "\nClientes en espera:" << endl;

                while (!temp.empty()) {
                    cout << "- "
                         << temp.front().nombre
                         << " | "
                         << temp.front().asunto
                         << endl;

                    temp.pop();
                }
            }
            else {
                cout << "No hay clientes registrados." << endl;
            }
        }
        else if (opcion == "salir" || opcion == "4") {
            cout << "Saliendo del sistema..." << endl;
        }
        else {
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != "salir" && opcion != "4");

    return 0;
}