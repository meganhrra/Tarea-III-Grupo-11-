#include <iostream>
#include <stack>
#include <string>

using namespace std;

class ConversorExpresiones
{
private:

    /*
        =================================================
        VERIFICAR PRIORIDAD DE OPERADORES
        =================================================

        Prioridades:

        +  -  => 1
        *  /  => 2
    */
    int prioridad(char operador)
    {
        if (operador == '+' || operador == '-')
        {
            return 1;
        }

        if (operador == '*' || operador == '/')
        {
            return 2;
        }

        return 0;
    }

    /*
        =================================================
        VERIFICAR SI ES OPERADOR
        =================================================
    */
    bool esOperador(char caracter)
    {
        return

            caracter == '+' ||

            caracter == '-' ||

            caracter == '*' ||

            caracter == '/';
    }

public:

    /*
        =================================================
        CONVERTIR INFIX A POSTFIX
        =================================================

        Algoritmo:
        Shunting Yard

        Complejidad:
        O(n)
    */
    string convertirPostfix(string expresion)
    {
        // Pila para operadores
        stack<char> pilaOperadores;

        // Resultado final
        string resultado = "";

        /*
            =============================================
            RECORRER EXPRESION
            =============================================
        */
        for (char caracter : expresion)
        {
            // Ignorar espacios
            if (caracter == ' ')
            {
                continue;
            }

            /*
                =========================================
                SI ES OPERANDO
                =========================================

                Ejemplo:
                A, B, C, D
            */
            if (isalnum(caracter))
            {
                resultado += caracter;
                resultado += ' ';
            }

            /*
                =========================================
                SI ES PARENTESIS DE APERTURA
                =========================================
            */
            else if (caracter == '(')
            {
                pilaOperadores.push(caracter);
            }

            /*
                =========================================
                SI ES PARENTESIS DE CIERRE
                =========================================
            */
            else if (caracter == ')')
            {
                /*
                    Sacar operadores
                    hasta encontrar '('
                */
                while (

                    !pilaOperadores.empty()

                    &&

                    pilaOperadores.top() != '('
                )
                {
                    resultado += pilaOperadores.top();

                    resultado += ' ';

                    pilaOperadores.pop();
                }

                // Eliminar '('
                if (!pilaOperadores.empty())
                {
                    pilaOperadores.pop();
                }
            }

            /*
                =========================================
                SI ES OPERADOR
                =========================================
            */
            else if (esOperador(caracter))
            {
                /*
                    Mientras exista un operador
                    con mayor o igual prioridad
                    en la pila.
                */
                while (

                    !pilaOperadores.empty()

                    &&

                    prioridad(pilaOperadores.top())

                    >=

                    prioridad(caracter)
                )
                {
                    resultado += pilaOperadores.top();

                    resultado += ' ';

                    pilaOperadores.pop();
                }

                // Insertar operador actual
                pilaOperadores.push(caracter);
            }
        }

        /*
            =============================================
            VACIAR PILA
            =============================================
        */
        while (!pilaOperadores.empty())
        {
            resultado += pilaOperadores.top();

            resultado += ' ';

            pilaOperadores.pop();
        }

        return resultado;
    }

    /*
        =================================================
        MOSTRAR EJEMPLOS PRECARGADOS
        =================================================
    */
    void mostrarEjemplos()
    {
        cout << "\n========== EJEMPLOS PRECARGADOS ==========" << endl;

        string ejemplo1 = "A + B * (C - D)";

        string ejemplo2 = "(A + B) * C";

        string ejemplo3 = "A * B + C / D";

        cout << "\nExpresion Infix: "
             << ejemplo1 << endl;

        cout << "Expresion Postfix: "
             << convertirPostfix(ejemplo1)
             << endl;

        cout << "\nExpresion Infix: "
             << ejemplo2 << endl;

        cout << "Expresion Postfix: "
             << convertirPostfix(ejemplo2)
             << endl;

        cout << "\nExpresion Infix: "
             << ejemplo3 << endl;

        cout << "Expresion Postfix: "
             << convertirPostfix(ejemplo3)
             << endl;
    }

    /*
        =================================================
        CONVERTIR EXPRESION INGRESADA POR EL USUARIO
        =================================================
    */
    void convertirExpresionUsuario()
    {
        cout << "\n========== CONVERTIR EXPRESION ==========" << endl;

        string expresion;

        cin.ignore();

        cout << "Ingrese expresion infix: ";

        getline(cin, expresion);

        string resultado = convertirPostfix(expresion);

        cout << "\nExpresion Postfix: "
             << resultado
             << endl;
    }
};


/*
    =====================================================
    FUNCION PRINCIPAL
    =====================================================
*/
int main()
{
    ConversorExpresiones conversor;

    int opcion;

    do
    {
        cout << "\n======================================================" << endl;

        cout << "     SISTEMA CONVERSOR INFIX A POSTFIX" << endl;

        cout << "======================================================" << endl;

        cout << "1. Mostrar ejemplos precargados" << endl;

        cout << "2. Convertir expresion" << endl;

        cout << "0. Salir" << endl;

        cout << "\nSeleccione una opcion: ";

        cin >> opcion;

        switch (opcion)
        {
            case 1:

                conversor.mostrarEjemplos();

                break;

            case 2:

                conversor.convertirExpresionUsuario();

                break;

            case 0:

                cout << "\nSaliendo del sistema..." << endl;

                break;

            default:

                cout << "\nOpcion invalida." << endl;
        }

    } while (opcion != 0);

    return 0;
}