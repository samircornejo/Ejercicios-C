// Escribe una función planShippingRoute que toma legDistances y initialFuel y devuelve un objeto con los puertos alcanzados y el combustible restante.

// La función procesa los tramos de envío uno por uno, saltándose los tramos con distancias que son múltiplos de 5 (rutas especiales afectadas por el clima) y deteniéndose cuando se agota el combustible.

// Lógica:

// Salta cualquier tramo cuya distancia sea un múltiplo de 5 usando continue
// Para otros tramos, consume combustible igual a la distancia
// Detén el procesamiento usando break si el combustible es insuficiente para un tramo
// Cuenta cuántos puertos fueron alcanzados con éxito
// Parámetros:

// legDistances (array): Array de distancias entre puertos consecutivos
// initialFuel (number): Cantidad inicial de combustible
// Devuelve: Objeto con los puertos alcanzados y el combustible restante. Formato: {"portsReached": 3, "remainingFuel": 15}

#include <iostream>
#include <vector>

struct RouteResult {
    int portsReached;
    int remainingFuel;
};

RouteResult planShippingRoute(const std::vector<int>& legDistances, int initialFuel) {
    int remainingFuel = initialFuel;
    int portsReached = 0;

    for (int distance : legDistances) {
       if (distance % 5 == 0) {
            continue;
        }

        if (remainingFuel < distance) {
            break;
        }

        remainingFuel -= distance;
        portsReached++;
    }

    return {portsReached, remainingFuel};
}
