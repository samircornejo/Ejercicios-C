// El Validador de Palíndromos (Strings)
// Escribe un programa que pida al usuario una frase y determine si es un palíndromo (se lee igual al derecho que al revés).
// El reto: Debes ignorar los espacios y las mayúsculas/minúsculas.
// Ejemplo: "Anita lava la tina" debería devolver que sí es palíndromo.

#include <iostream>
using namespace std;
 
    int main() {
    string str, output;
    cout << "Enter a string: ";
    cin >> str;
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        if (str[i]!= str[n - i - 1]) {
            output = "Given string is not a Palindrome";
            break;
        }
        else {
            output = "Given string is a Palindrome";
        }
    }
    cout << output << endl;
return 0;
}


