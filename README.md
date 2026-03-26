## The Mind

![UMLFinal](https://github.com/user-attachments/assets/fb61b002-e074-48a6-af75-8a49290f5bde)


Proyecto para la materia **Estructura de Datos** — Universidad, tercer semestre.

Implementación del juego de cartas *The Mind* en **C++**, desarrollado como trabajo en equipo.

---

##  Integrantes

| Nombre | Rol |
|---|---|
| Juan Diego Muriel Bedoya | Motor del juego — `Tablero`, `Juego`, `main.cpp` |
| Santiago Herrera Oquendo | Cartas y Mazo — `Carta`, `Mazo` |
| Julian Zapata Gallego | Jugadores — `Jugador` |

---

## ¿Qué es The Mind?

The Mind es un juego de cartas cooperativo. Las reglas son simples:

- Cada jugador recibe cartas con números del **1 al 100**
- El objetivo es jugarlas **en orden de menor a mayor**, sin hablar ni comunicarse
- Si alguien juega una carta fuera de orden, el equipo **pierde una vida**
- El juego tiene **12 niveles**: en el nivel 1 cada jugador recibe 1 carta, en el nivel 2 recibe 2, y así sucesivamente
- El equipo empieza con **3 vidas** y **1 estrella ninja** (que descarta la carta más baja de todos los jugadores)
- Si completan los 12 niveles sin quedarse sin vidas, **ganan**

---

##  Estructura del proyecto

```
TheMind/
└── src/
    ├── Carta.h / Carta.cpp           → Una carta del juego (número del 1 al 100)
    ├── Jugador.h / Jugador.cpp       → Un jugador y las cartas que tiene en la mano
    ├── Mazo.h / Mazo.cpp             → La baraja completa: mezcla y reparte cartas
    ├── EstadoJuego.h                 → Las etiquetas que describen en qué momento está el juego
    ├── Tablero.h / Tablero.cpp       → La mesa: guarda las cartas jugadas y valida el orden
    ├── Juego.h / Juego.cpp           → El cerebro del juego: niveles, vidas y estrellas ninja
    └── main.cpp                      → La puerta de entrada: es lo primero que corre al iniciar
```

---

##  Descripción de cada clase

### `Carta`
Representa una sola carta del juego. Guarda su número (del 1 al 100) y sabe si ya fue jugada o no. También puede compararse con otras cartas para saber cuál es menor.

### `Jugador`
Representa a una persona que juega. Guarda su nombre y las cartas que tiene en la mano. Puede recibir cartas nuevas, jugar la más baja de su mano, y mostrar lo que tiene.

### `Mazo`
Es la baraja completa del juego. Se encarga de mezclar las 100 cartas al azar y repartirlas a los jugadores al inicio de cada nivel.

### `EstadoJuego`
Es una lista de "etiquetas" que describen en qué momento está el juego: si está esperando, en curso, si el equipo perdió, ganó, o subió de nivel.

### `Tablero`
Es la mesa del juego: lleva el registro de todas las cartas que ya se jugaron y verifica si una carta nueva puede jugarse (tiene que ser mayor que la última).

### `Juego`
Es el cerebro de todo. Coordina los niveles, descuenta vidas cuando se comete un error, activa las estrellas ninja y decide cuándo el equipo gana o pierde.

### `main.cpp`
Es la puerta de entrada al programa. Pregunta cuántos jugadores van a jugar y luego arranca el juego. Todo lo demás ocurre dentro de `Juego`.

---

##  ¿Cómo compilar y ejecutar?

Es recomendado refrescar el clon del repositorio en el archivo local:

```bash
git pull origin main
```

Desde la carpeta `src/`, ejecutar en la terminal:

```bash
g++ -o themind main.cpp Juego.cpp Tablero.cpp Jugador.cpp Mazo.cpp Carta.cpp
./themind.exe
```

> Requiere un compilador de C++ (g++ versión 11 o superior recomendada).
