/*
 * ENUNCIADO:
 * 1. Define una estructura 'Nodo' que contenga un valor entero y un puntero al siguiente nodo.
 * 2. Implementa una función 'insertarAlFinal' que recorra la lista hasta encontrar el 
 * último elemento y anexe uno nuevo.
 * 3. Implementa una función 'mostrarLista' para imprimir todos los valores.
 * 4. IMPORTANTE: Implementar una función 'liberarMemoria' que elimine cada nodo
 * uno por uno para evitar fugas de memoria (Memory Leaks).
 */
#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

void insertarAlFinal(Nodo*& cabeza, int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo* aux = cabeza;
        while (aux->siguiente != nullptr) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevoNodo;
    }
}

void mostrarLista(Nodo* cabeza) {
    Nodo* aux = cabeza;
    while (aux != nullptr) {
        cout << "[" << aux->dato << "] -> ";
        aux = aux->siguiente;
    }
    cout << "NULL" << endl;
}

void liberarMemoria(Nodo*& cabeza) {
    while (cabeza != nullptr) {
        Nodo* aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
}

int main() {
    Nodo* lista = nullptr;
    int numero;

    cout << "Ingrese numeros (0 para finalizar):" << endl;
    while (cin >> numero && numero != 0) {
        insertarAlFinal(lista, numero);
    }

    cout << "\nLista generada:" << endl;
    mostrarLista(lista);
    liberarMemoria(lista);
    return 0;
}