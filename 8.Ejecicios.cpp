// Ordenamiento por Selección (Algoritmos)
// No uses funciones automáticas. Pide al usuario 6 números, guárdalos en un arreglo y ordénalos de 
//menor a mayor usando el método de selección.

// Lógica: Busca el número más pequeño de la lista y ponlo al principio, luego busca el 
//segundo más pequeño y ponlo en la segunda posición, y así sucesivamente.
#include <iostream>
using namespace std;

int main()
{
    const int tamaño = 6;
    int numeros[tamaño];
    cout << "Ingresa 6 numeros enteros:" << endl;
    for (int i = 0; i < tamaño; i++) {
        cout << "Numero " << (i + 1) << ": ";
        cin >> numeros[i];
    }

    for (int i = 0; i < tamaño; i++) {
        int min = i;
        for (int j = i + 1; j < tamaño; j++) {
            if (numeros[j] < numeros[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = numeros[i];
            numeros[i] = numeros[min];
            numeros[min] = temp;
        }
    }


    cout << "Numeros ordenados de menor a mayor: ";
    for (int i = 0; i < tamaño; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    return 0;
}


