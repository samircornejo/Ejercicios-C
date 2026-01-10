#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// --- UTILIDADES ---
void esperar(int milisegundos) {
    this_thread::sleep_for(chrono::milliseconds(milisegundos));
}

void limpiarPantalla() {
    system("clear"); 
}

// --- ESTRUCTURAS DE DATOS ---
enum Tipo { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO };

string nombreTipo(Tipo t) {
    switch(t) {
        case NORMAL: return "Normal";
        case FUEGO: return "Fuego";
        case AGUA: return "Agua";
        case PLANTA: return "Planta";
        case ELECTRICO: return "Electrico";
        default: return "???";
    }
}

// Estructura para un Ataque
struct Movimiento {
    string nombre;
    int poder;
    Tipo tipo;
};

// --- CLASE POKEMON ---
class Pokemon {
private:
    string nombre;
    int vidaMax;
    int vidaActual;
    Tipo tipo;
    vector<Movimiento> movimientos;

public:
    Pokemon(string n, int vida, Tipo t) : nombre(n), vidaMax(vida), vidaActual(vida), tipo(t) {}

    void agregarMovimiento(string n, int poder, Tipo t) {
        movimientos.push_back({n, poder, t});
    }

    string getNombre() { return nombre; }
    int getVida() { return vidaActual; }
    int getVidaMax() { return vidaMax; }
    Tipo getTipo() { return tipo; }
    bool estaDebilitado() { return vidaActual <= 0; }

    void recibirDanio(int danio) {
        vidaActual -= danio;
        if (vidaActual < 0) vidaActual = 0;
    }

    Movimiento getMovimiento(int index) {
        if (index >= 0 && index < movimientos.size())
            return movimientos[index];
        return {"Lucha", 10, NORMAL}; // Default
    }

    int numeroMovimientos() { return movimientos.size(); }

    // Dibuja la barra de vida estilo GameBoy
    void mostrarBarraVida() {
        cout << nombre << " (Nv.50)" << endl;
        cout << "HP: ";
        
        int porcentaje = (vidaActual * 10) / vidaMax; // Escala de 1 a 10
        cout << "[";
        for (int i = 0; i < 10; i++) {
            if (i < porcentaje) cout << "=";
            else cout << " ";
        }
        cout << "] " << vidaActual << "/" << vidaMax << endl;
    }
};

// --- LOGICA DE BATALLA ---

// Tabla de efectividad simple
float calcularEfectividad(Tipo ataque, Tipo defensor) {
    if (ataque == FUEGO && defensor == PLANTA) return 2.0;
    if (ataque == FUEGO && defensor == AGUA) return 0.5;
    if (ataque == AGUA && defensor == FUEGO) return 2.0;
    if (ataque == AGUA && defensor == PLANTA) return 0.5;
    if (ataque == PLANTA && defensor == AGUA) return 2.0;
    if (ataque == PLANTA && defensor == FUEGO) return 0.5;
    if (ataque == ELECTRICO && defensor == AGUA) return 2.0;
    if (ataque == ELECTRICO && defensor == PLANTA) return 0.5;
    return 1.0;
}

// --- POOL DE 10 POKEMONS ---
vector<Pokemon> crearPokedex() {
    vector<Pokemon> p;
    // 0
    p.push_back(Pokemon("Charizard", 150, FUEGO));
    p.back().agregarMovimiento("Lanzallamas", 40, FUEGO);
    p.back().agregarMovimiento("Garra Dragon", 30, NORMAL);
    // 1
    p.push_back(Pokemon("Blastoise", 160, AGUA));
    p.back().agregarMovimiento("Hidrobomba", 45, AGUA);
    p.back().agregarMovimiento("Mordisco", 25, NORMAL);
    // 2
    p.push_back(Pokemon("Venusaur", 160, PLANTA));
    p.back().agregarMovimiento("Rayo Solar", 50, PLANTA);
    p.back().agregarMovimiento("Placaje", 20, NORMAL);
    // 3
    p.push_back(Pokemon("Pikachu", 100, ELECTRICO));
    p.back().agregarMovimiento("Rayo", 40, ELECTRICO);
    p.back().agregarMovimiento("Ataque Rapido", 20, NORMAL);
    // 4
    p.push_back(Pokemon("Snorlax", 200, NORMAL));
    p.back().agregarMovimiento("Golpe Cuerpo", 35, NORMAL);
    p.back().agregarMovimiento("Descanso", 0, NORMAL);
    // 5
    p.push_back(Pokemon("Arcanine", 140, FUEGO));
    p.back().agregarMovimiento("Colmillo Igneo", 35, FUEGO);
    p.back().agregarMovimiento("Velocidad Extrema", 30, NORMAL);
    // 6
    p.push_back(Pokemon("Gyarados", 155, AGUA));
    p.back().agregarMovimiento("Cascada", 35, AGUA);
    p.back().agregarMovimiento("Furia Dragon", 40, NORMAL);
    // 7
    p.push_back(Pokemon("Exeggutor", 145, PLANTA));
    p.back().agregarMovimiento("Bomba Huevo", 35, NORMAL);
    p.back().agregarMovimiento("Gigadrenado", 30, PLANTA);
    // 8
    p.push_back(Pokemon("Jolteon", 110, ELECTRICO));
    p.back().agregarMovimiento("Trueno", 50, ELECTRICO);
    p.back().agregarMovimiento("Doble Patada", 25, NORMAL);
    // 9
    p.push_back(Pokemon("Eevee", 90, NORMAL));
    p.back().agregarMovimiento("Rapidez", 25, NORMAL);
    p.back().agregarMovimiento("Mordisco", 20, NORMAL);

    return p;
}

// --- SISTEMA DE JUEGO ---
class Juego {
    vector<Pokemon> equipoJugador;
    vector<Pokemon> equipoRival;
    int indiceActualJugador = 0;
    int indiceActualRival = 0;

public:
    Juego() {
        vector<Pokemon> pokedex = crearPokedex();
        srand(time(0));
        
        // Seleccion aleatoria para ejemplo rapido (3 vs 3)
        // Jugador recibe los indices 0, 1, 2
        equipoJugador.push_back(pokedex[0]);
        equipoJugador.push_back(pokedex[1]);
        equipoJugador.push_back(pokedex[3]);

        // Rival recibe indices aleatorios
        equipoRival.push_back(pokedex[rand() % 10]);
        equipoRival.push_back(pokedex[rand() % 10]);
        equipoRival.push_back(pokedex[rand() % 10]);
    }

    void turnoAtaque(Pokemon& atacante, Pokemon& defensor, Movimiento mov, bool esJugador) {
        cout << "------------------------------------------------" << endl;
        cout << atacante.getNombre() << " uso " << mov.nombre << "!" << endl;
        esperar(1000);

        float mult = calcularEfectividad(mov.tipo, defensor.getTipo());
        int danioFinal = (int)(mov.poder * mult);

        if (mult > 1.0) cout << "Es muy eficaz!" << endl;
        if (mult < 1.0) cout << "No es muy eficaz..." << endl;

        defensor.recibirDanio(danioFinal);
        cout << defensor.getNombre() << " recibio " << danioFinal << " puntos de danio." << endl;
        esperar(1000);
    }

    bool cambiarPokemon() {
        limpiarPantalla();
        cout << "--- TU EQUIPO ---" << endl;
        for(int i=0; i<equipoJugador.size(); i++) {
            cout << i+1 << ". " << equipoJugador[i].getNombre();
            if(equipoJugador[i].estaDebilitado()) cout << " [DEBILITADO]";
            else cout << " (HP: " << equipoJugador[i].getVida() << ")";
            if(i == indiceActualJugador) cout << " [EN CAMPO]";
            cout << endl;
        }
        cout << "0. Cancelar" << endl;
        cout << "Elige un Pokemon: ";
        
        int opcion;
        cin >> opcion;

        if (opcion > 0 && opcion <= equipoJugador.size()) {
            int indiceNuevo = opcion - 1;
            if (equipoJugador[indiceNuevo].estaDebilitado()) {
                cout << "Ese Pokemon no puede luchar!" << endl;
                esperar(1500);
                return false;
            }
            if (indiceNuevo == indiceActualJugador) {
                cout << "Ya esta en combate!" << endl;
                esperar(1500);
                return false;
            }
            indiceActualJugador = indiceNuevo;
            cout << "Adelante " << equipoJugador[indiceActualJugador].getNombre() << "!" << endl;
            esperar(1500);
            return true;
        }
        return false;
    }

    void iniciarBatalla() {
        cout << "Un entrenador rival quiere luchar!" << endl;
        esperar(1500);
        
        while (true) {
            limpiarPantalla();
            Pokemon& pJugador = equipoJugador[indiceActualJugador];
            Pokemon& pRival = equipoRival[indiceActualRival];

            // 1. Mostrar HUD
            cout << "RIVAL: " << endl;
            pRival.mostrarBarraVida();
            cout << endl;
            cout << "TU EQUIPO: " << endl;
            pJugador.mostrarBarraVida();
            cout << "------------------------------------------------" << endl;

            // 2. Menu de opciones
            cout << "1. Atacar  2. Pokemon  3. Huir" << endl;
            int opcion;
            cout << "> ";
            cin >> opcion;

            bool turnoJugadorHecho = false;

            if (opcion == 1) {
                // Elegir ataque
                cout << "Ataques:" << endl;
                for(int i=0; i<pJugador.numeroMovimientos(); i++) {
                    cout << i+1 << ". " << pJugador.getMovimiento(i).nombre << endl;
                }
                int opAtaque;
                cin >> opAtaque;
                Movimiento mov = pJugador.getMovimiento(opAtaque - 1);
                turnoAtaque(pJugador, pRival, mov, true);
                turnoJugadorHecho = true;
            } else if (opcion == 2) {
                if(cambiarPokemon()) {
                    turnoJugadorHecho = true; 
                    // Cambiar gasta turno
                }
            } else if (opcion == 3) {
                cout << "Escapaste sin problemas!" << endl;
                break;
            }

            // Verificar si Rival murio
            if (pRival.estaDebilitado()) {
                cout << pRival.getNombre() << " se debilito!" << endl;
                esperar(1500);
                // Cambiar rival
                bool quedanRivales = false;
                for(int i=0; i<equipoRival.size(); i++) {
                    if(!equipoRival[i].estaDebilitado()) {
                        indiceActualRival = i;
                        quedanRivales = true;
                        cout << "El rival envia a " << equipoRival[i].getNombre() << endl;
                        esperar(1500);
                        break;
                    }
                }
                if (!quedanRivales) {
                    cout << "Ganaste la batalla!" << endl;
                    break;
                }
                turnoJugadorHecho = false; // Reset para nuevo turno limpio
                continue; 
            }

            // 3. Turno Rival (IA simple)
            if (turnoJugadorHecho && !pRival.estaDebilitado()) {
                Movimiento movRival = pRival.getMovimiento(rand() % pRival.numeroMovimientos());
                turnoAtaque(pRival, pJugador, movRival, false);

                if (pJugador.estaDebilitado()) {
                    cout << pJugador.getNombre() << " se debilito!" << endl;
                    esperar(1500);
                    // Forzar cambio
                    if (!cambiarPokemon()) {
                        // Comprobar si perdio
                         bool quedanMios = false;
                         for(auto& p : equipoJugador) if(!p.estaDebilitado()) quedanMios = true;
                         
                         if(!quedanMios) {
                             cout << "Te has quedado sin Pokemon..." << endl;
                             cout << "Fin del juego." << endl;
                             break;
                         }
                         // Si aun quedan y cancelo el menu, forzar loop
                         while(!cambiarPokemon()); 
                    }
                }
            }
        }
    }
};

int main() {
    Juego juego;
    juego.iniciarBatalla();
    return 0;
}