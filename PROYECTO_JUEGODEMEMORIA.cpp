#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Jugador {
    string nombre;
    int puntaje;
};

void mezclar_tablero(char matriz[][5], const char tablero_base[], int filas, int columnas) {
    int mostrador = 0;
    int total_celdas = filas * columnas;
    
    char tablero_mezclado[total_celdas];
    for (int i = 0; i < total_celdas; i++) {
        tablero_mezclado[i] = tablero_base[i];
    }

    for (int i = total_celdas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(tablero_mezclado[i], tablero_mezclado[j]);
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = tablero_mezclado[mostrador];
            mostrador++;
        }
    }
}

void imprimir_tablero(char matriz[][5], bool revelado[][5], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (revelado[i][j]) {
                cout << "[   " << matriz[i][j] << "   ]";
            } else {
                cout << "[   ?   ]";
            }
        }
        cout << endl;
    }
}

bool mostrar_posicion(char matriz[][5], bool revelado[][5], int f, int c, int f2, int c2, int filas, int columnas) {
    char valor1, valor2;
    bool primera_posicion_revelada = revelado[f][c];
    bool segunda_posicion_revelada = revelado[f2][c2];
    bool posiciones_validas = true;

    if (primera_posicion_revelada) {
        cout << "La primera posicion ya esta revelada." << endl;
        posiciones_validas = false;
    }
    if (segunda_posicion_revelada) {
        cout << "La segunda posicion ya esta revelada." << endl;
        posiciones_validas = false;
    }
    if (!posiciones_validas) {
        return false;
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            bool mostrar_valor = false;

            if (i == f) {
                if (j == c) {
                    valor1 = matriz[i][j];
                    mostrar_valor = true;
                }
            }
            if (i == f2) {
                if (j == c2) {
                    valor2 = matriz[i][j];
                    mostrar_valor = true;
                }
            }
            
            if (mostrar_valor) {
                cout << "[   " << matriz[i][j] << "   ]";
            } else {
                cout << "[   ?   ]";
            }
        }
        cout << endl;
    }

    if (valor1 == valor2) {
        cout << "¡CORRECTO! :)" << endl;
        revelado[f][c] = true;
        revelado[f2][c2] = true;
        return true;
    } else {
        cout << "INCORRECTO :(" << endl;
        return false;
    }
}

void inicializar_jugadores(Jugador jugadores[], int num_jugadores) {
    for (int i = 0; i < num_jugadores; i++) {
        cout << "Ingrese el nombre del jugador " << (i + 1) << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].puntaje = 0;
    }
}

void mostrar_puntajes(Jugador jugadores[], int num_jugadores) {
    for (int i = 0; i < num_jugadores; i++) {
        cout << "Jugador: " << jugadores[i].nombre << ". Puntaje: " << jugadores[i].puntaje << endl;
    }
}

void mostrar_creditos() {
    cout << "\nCreditos:" << endl;
    cout << "Derek Cahuate" << endl;
    cout << "Joseph Cruz" << endl;
}

void jugar_turno(Jugador &jugador, char matriz[][5], bool revelado[][5], int filas, int columnas) {
    int f, c, f2, c2;

    imprimir_tablero(matriz, revelado, filas, columnas);

    cout << "Turno de " << jugador.nombre << endl;

    cout << "Ingrese las coordenadas X y Y de la primera posicion que quiere ver (0-3),(0-4) " << endl;
    cin >> f >> c;

    cout << "Ingrese las coordenadas X y Y de la segunda posicion que quiere ver (0-3),(0-4) " << endl;
    cin >> f2 >> c2;

    bool fuera_de_rango = false;

    if (f < 0 || f >= filas) {
        fuera_de_rango = true;
    }
    if (c < 0 || c >= columnas) {
        fuera_de_rango = true;
    }
    if (f2 < 0 || f2 >= filas) {
        fuera_de_rango = true;
    }
    if (c2 < 0 || c2 >= columnas) {
        fuera_de_rango = true;
    }
    if (fuera_de_rango) {
        cout << "Posiciones fuera de rango." << endl;
    } else if (f == f2) {
        if (c == c2) {
            cout << "Posicion repetida." << endl;
        } else {
            if (mostrar_posicion(matriz, revelado, f, c, f2, c2, filas, columnas)) {
                jugador.puntaje += 10;
            }
        }
    } else {
        if (mostrar_posicion(matriz, revelado, f, c, f2, c2, filas, columnas)) {
            jugador.puntaje += 10;
        }
    }
}

void jugar(Jugador jugadores[], int num_jugadores) {
    const int FILAS = 4;
    const int COLUMNAS = 5;
    const int TOTAL_CELDAS = FILAS * COLUMNAS;
    const int NUM_LETRAS = 10;

    char tablero_base[TOTAL_CELDAS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K', 'M',
                                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K', 'M'};

    char matriz[FILAS][COLUMNAS];
    bool revelado[FILAS][COLUMNAS] = {false};

    int turno = 0;
    bool seguir = true;

    srand(static_cast<unsigned>(time(0))); 
    mezclar_tablero(matriz, tablero_base, FILAS, COLUMNAS);

    while (seguir) {
        Jugador jugador_actual = jugadores[turno];
        jugar_turno(jugador_actual, matriz, revelado, FILAS, COLUMNAS);
        jugadores[turno] = jugador_actual; 

        turno = (turno + 1) % num_jugadores;
        if (turno == 0) {
            char respuesta;
            cout << "Desea volver al menu (s/n): ";
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                seguir = false;
            }
        }
    }
}

int main() {
    int opcion;
    int JUGADORES = 3;
    Jugador jugadores[JUGADORES];

    inicializar_jugadores(jugadores, JUGADORES);

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Puntajes" << endl;
        cout << "3. Salir" << endl;
        cout << "4. Creditos" << endl;

        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugar(jugadores, JUGADORES);
                break;
            case 2:
                mostrar_puntajes(jugadores, JUGADORES);
                break;
            case 3:
                cout << "Saliendo del juego...." << endl;
                break;
            case 4:
                mostrar_creditos();
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}