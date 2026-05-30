#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Clase Paciente
class Paciente {
private:
    string nombre;
    string sintoma;

public:
    Paciente(string nombre, string sintoma) {
        this->nombre = nombre;
        this->sintoma = sintoma;
    }

    string getNombre() const {
        return nombre;
    }

    string getSintoma() const {
        return sintoma;
    }

    void mostrarPaciente() const {
        cout << "Nombre: " << nombre << " | Sintoma: " << sintoma << endl;
    }
};

// Clase Consultorio
class Consultorio {
private:
    queue<Paciente> colaPacientes;

public:
    void nuevoPaciente(string nombre, string sintoma) {
        Paciente paciente(nombre, sintoma);
        colaPacientes.push(paciente);
        cout << "Paciente agregado correctamente a la lista de espera." << endl;
    }

    void atender() {
        if (colaPacientes.empty()) {
            cout << "No hay pacientes en espera." << endl;
            return;
        }

        Paciente paciente = colaPacientes.front();
        colaPacientes.pop();

        cout << "Atendiendo paciente:" << endl;
        paciente.mostrarPaciente();
    }

    void listaEspera() const {
        if (colaPacientes.empty()) {
            cout << "La lista de espera esta vacia." << endl;
            return;
        }

        queue<Paciente> copiaCola = colaPacientes;
        int posicion = 1;

        cout << "\nLista de pacientes en espera:" << endl;

        while (!copiaCola.empty()) {
            cout << posicion << ". ";
            copiaCola.front().mostrarPaciente();
            copiaCola.pop();
            posicion++;
        }
    }

    bool estaVacia() const {
        return colaPacientes.empty();
    }
};

// Funcion principal
int main() {
    Consultorio consultorio;
    int opcion;
    string nombre;
    string sintoma;

    do {
        cout << "\n===== TRIAGE CONSULTORIO MEDICO =====" << endl;
        cout << "1. Nuevo paciente" << endl;
        cout << "2. Atender paciente" << endl;
        cout << "3. Lista de espera" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << "Ingrese el nombre del paciente: ";
            getline(cin, nombre);

            cout << "Ingrese el sintoma del paciente: ";
            getline(cin, sintoma);

            consultorio.nuevoPaciente(nombre, sintoma);
            break;

        case 2:
            consultorio.atender();
            break;

        case 3:
            consultorio.listaEspera();
            break;

        case 4:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 4);

    return 0;
}
