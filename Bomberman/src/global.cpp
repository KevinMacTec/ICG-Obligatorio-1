#include "../lib/global.h"

float velocidad_juego = 1.0f;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];
objeto*** bonificadores = new objeto * *[largoTablero];

list<objeto*> borde = list<objeto*>();
list<particula*> particulas = list<particula*>();
list<enemigo*> enemigos = list<enemigo*>();

bomberman* jugador;

puerta* door;

GLfloat tiempo_entre_frames;
chrono::high_resolution_clock::time_point marca_tiempo_anterior, marca_tiempo_actual;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

bool pausa = true;
bool pararTiempo = false;
bool wireframe = false;
bool texturas_habilitadas = true;
bool mute = false; //cambiar a false para que inicie con sonido
bool mostrarHud = true;
bool inmortal = false;
bool pantallaCompleta = false;

bool tipoLuz = true; //false = facetado, true = interpolado
bool atravesar_paredes = false;
bool musica = true;

bool fin = false;
bool finJuego = false;

int nivel = 1;
int puntaje = 0;
int tiempoJuego = 200000; //milisegundos
int cantidad_enemigos_actual = 4;
bool puertaAbierta = false;
bool temporizador = false;

void inicializarAtributosJuego() {
    moverArriba = false;
    moverAbajo = false;
    moverDerecha = false;
    moverIzquierda = false;

    pausa = true;
    pararTiempo = false;
    wireframe = false;
    texturas_habilitadas = true;
    mute = false; //cambiar a false para que inicie con sonido
    mostrarHud = true;
    inmortal = false;
    pantallaCompleta = false;

    tipoLuz = true; //false = facetado, true = interpolado
    atravesar_paredes = false;
    musica = true;

    fin = false;
    finJuego = false;
    nivel = 1;
    puntaje = 0;
    tiempoJuego = 200000; //milisegundos
    cantidad_enemigos_actual = 4;
    puertaAbierta = false;
    temporizador = false;

    particulas.clear();
    particulas = list<particula*>();
    enemigos.clear();
    enemigos = list<enemigo*>();
}

int getIndiceTablero(GLfloat coord) {
    return int(floor(coord / tile_size));
}

void toggle(bool &valor){
    valor = !valor;
}

void aumentarNivel() {
    tiempoJuego = 200000;
    if (nivel <= INT_MAX - 1) {
        nivel++;
        cantidad_enemigos_actual++;
    } else {
        nivel = INT_MAX;
    }
}

void sumarPuntaje(int puntos) {
    if (puntaje <= INT_MAX - puntos) {
        puntaje += puntos;
    } else {
        puntaje = INT_MAX;
    }
}

void disminuirTiempo(GLfloat milisegundos){
    tiempoJuego -= int(tiempo_entre_frames);
    if (tiempoJuego <= 0) {
        tiempoJuego = 0;
        finJuego = true;
    }
}