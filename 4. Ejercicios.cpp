// Ejercicio 2: El Portero de Discoteca (Nivel: Fácil)
// Objetivo: Aprender el uso de condicionales if y else.
// Reto: Pide al usuario su edad.
// Si es menor de 18, imprime "Acceso denegado".
// Si tiene entre 18 y 64, imprime "Bienvenido".
// Si tiene 65 o más, imprime "Bienvenido, tiene descuento de jubilado".
// Lo que aprendes: Estructuras de control de flujo.
#include <iostream>
using namespace std;

int main() {
    int edad;
    cout << "Ingrese su edad: ";
    cin >> edad;

    if (edad < 18) {
        cout << "Acceso denegado" << endl;
    } else if (edad >= 18 && edad < 65) {
        cout << "Bienvenido" << endl;
    } else {
        cout << "Bienvenido, tiene descuento de jubilado" << endl;
    }

    return 0;
}