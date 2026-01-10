// Ejercicio 3: Cajero Automático Simple (Nivel: Intermedio)
// Objetivo: Usar el bucle while y la estructura switch.
// Reto: Crea un programa con un saldo inicial de 1000. Muestra un menú:
// Consultar saldo.
// Retirar dinero (valida que tenga suficiente).
// Salir.
// El programa debe repetirse hasta que el usuario elija "Salir".
// Lo que aprendes: Bucles infinitos controlados y menús interactivos.

#include <iostream>
using namespace std;

int main() {
    int saldo = 1000, opcion, retiro;
    bool ejecutando = true;
    
    while (ejecutando){
        cout << "\n--- Cajero Automatico ---\n1. Ver su saldo\n2. Retirar\n3.Salir\n >";
        cin >>opcion;

        switch (opcion)
        {
        case 1: cout << "Saldo actual: $" << saldo << endl; break;
        case 2:
            cout << "Cantidad a retirar: "; cin >> retiro;
            if (retiro <= saldo)
            {
                saldo -= retiro;
                cout << "Retiro exitoso." << endl;
            }
            break;
        case 3: ejecutando = false; break;
        default: cout << "Opcion no valida huevon. "<< endl;
            
        }
    }
    return 0;
}