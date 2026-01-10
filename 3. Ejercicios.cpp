// Ejercicio 1: El Convertidor de Temperatura (Nivel: Muy Fácil)Objetivo: Practicar variables de tipo decimal (float/double) 
// y operaciones matemáticas.Reto: Pide al usuario una temperatura en grados Celsius y conviértela a Fahrenheit usando la 
// fórmula: $F = (C \times 9/5) + 32$.Lo que aprendes: Lectura de datos y operadores aritméticos.
#include <iostream>

#include <iostream>
using namespace std;

int main() {
    float celsius;
    cout << "Ingrese la temperatura en grados Celsius: ";
    cin >> celsius;
    float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    cout << "La temperatura en grados Fahrenheit es: " << fahrenheit << "°F" << endl;
    return 0;
} 