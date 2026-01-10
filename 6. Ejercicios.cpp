// Ejercicio 4: El Adivinador de Números (Nivel: Avanzado)
// Objetivo: Introducir aleatoriedad y lógica de juegos.
// Reto: El programa genera un número aleatorio entre 1 y 100 (investiga rand() y srand()). El usuario debe intentar adivinarlo.
// Si el usuario falla, el programa dice "Más alto" o "Más bajo".
// Al final, debe decir en cuántos intentos lo logró.
// Lo que aprendes: Generación de números aleatorios y contadores.

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    srand(time(0));
    int numeroSecreto = rand() %100 + 1;
    int intento, contador = 0;

    cout << "Adivina el numero (1-100)" << endl;

    do {
        cout << "Introduce tu numero: ";
        cin >> intento;
        contador ++;

        if(intento >numeroSecreto)cout << "Un poco mas bajo " << endl;
        else if (intento < numeroSecreto) cout << "Un poco mas alto "<< endl;
    } while (intento != numeroSecreto);
    cout <<"Felicidades, si es el numero, te ganaste 1000$ , te tomo " <<contador <<  " intentos. "<< endl;
    return 0;

}
