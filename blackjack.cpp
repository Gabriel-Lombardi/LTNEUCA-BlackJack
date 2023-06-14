#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Carta {        // estructura de datos de la carta que se muestra, su palo (naipe) y valor
  char palo;
  char valor;
};

struct Ficha {        // estructura de datos de las fichas para "apuestas"
  int valor;
};

// funcion para asignar el valor de las cartas para la suma de puntos

int obtenerValorCarta(Carta* carta) {
  if (strcmp(carta->valor, "As") == 0)
    return 11; // el As puede valer 11 o 1, dependiendo si favorece a la suma de puntos.
  if (strcmp(carta->valor, "Rey") == 0 || strcmp(carta->valor, "Reina") == 0 || strcmp(carta->valor, "Jota") == 0)
    return 10; // la K, Q y J valen 10 en la suma de puntos.
  return atoi(carta->valor); // devolvemos un numero entero
}

// repartir cartas de manera aleatoria

void barajarMazo(Carta** mazo, int dimension) {
  srand(time(NULL));
  for (int i = 0; i < dimension - 1; ++i) {
    int j = i + rand() % (dimension - i);
    Carta* temp = mazo[i];
    mazo[i] = mazo[j];
    mazo[j] = temp;
  }
}

// funcion para mostrar las fichas (9) con valor:
// 1, 5, 25, 50, 100, 500, 1000, 2000, 5000, 10000
void mostrarFichasDisponibles(Ficha** fichas) {
  printf("Fichas disponibles:\n");
  for (int i = 0; i < 9; ++i) {
    printf("Ficha %d: $%d\n", i + 1, fichas[i]->valor);
  }
}

// funcion para guardar el dinero apostado dentro de un archivo "dinero.txt"
void guardarDinero(int dinero) {       // funcion para guardar el dinero
  FILE* fp = fopen("dinero.txt", "w"); // abrimos el archivo para escribir en él (w de write)
  if (fp != NULL) {
    fprintf(fp, "%d", dinero);
    fclose(fp);
    printf("¡Dinero guardado exitosamente!\n");
  } else {
    printf("No se pudo guardar el dinero dentro del archivo :(\n");
  }
}

// funcion para determinar cuanto dinero se tiene, leyendo el archivo anteriormente creado
int cargarDinero() {
  FILE* fp = fopen("dinero.txt", "r"); // abrimos el archivo solo para leerlo (r de read)
  if (fp != NULL) {
    int dinero;
    fscanf(fp, "%d", dinero);
    fclose(fp);
    printf("¡Dinero cargado exitosamente!\n");
    return dinero;
  } else {
    printf("No se pudo cargar el dinero dentro del archivo ;(\n");
    return 1000; // valor predeterminado
  }
}

void dibujarCarta(char* palo, int valor) {
  int  n_palo;           // variable para asignar el numero del palo que coincida con el simbolo ASCII de las cartas (♥ ♦ ♣ ♠)
  char valor_palo = 'N'; // variable con un caracter base para determinar si el valor a imprimir es A, J, Q, K o un numero del 2 al 10

  if (strcmp(palo,"Corazones") == 0) n_palo = 3;
  if (strcmp(palo,"Diamantes") == 0) n_palo = 4;
  if (strcmp(palo,"Treboles")  == 0) n_palo = 5;
  if (strcmp(palo,"Picas")     == 0) n_palo = 6;

  if (valor == 0)  valor_palo = 'A';
  if (valor == 10) valor_palo = 'J';
  if (valor == 11) valor_palo = 'Q';
  if (valor == 12) valor_palo = 'K';

  printf("%c", 218);
  for (int i = 0; i < 10; i++) {
    printf("%c", 196);
  }
  printf("%c\n", 191);

  for (int j = 0; j < 4; j++) {
    if (j == 0 || j == 3) {
      if (valor_palo == 'N') printf("%c %d \t %d %c\n", 179, valor, valor, 179);
      else                   printf("%c %c \t %c %c\n", 179, valor_palo, valor_palo, 179);

                             printf("%c %c \t %c %c\n", 179, n_palo, n_palo, 179);
    }
    if (j == 3) break;
    printf("%c  \t   %c\n", 179, 179);
  }

  printf("%c", 192);
  for (int k = 0; k < 10; k++) {
    printf("%c", 196);
  }
  printf("%c\n", 217);
}

int main() {
  Carta* mazo[52];
  char palos[] = {"Corazones", "Diamantes", "Treboles", "Picas"};
  char valores[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jota", "Reina", "Rey"};
  Ficha* fichas[9];
  int valoresFichas[] = {1, 5, 25, 50, 100, 500, 1000, 2000, 5000, 10000};
  int dinero;

  dinero = cargarDinero();

  int contador = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 13; ++j) {
      mazo[contador] = (Carta*)malloc(sizeof(Carta));
      strcpy(mazo[contador]->palo, palos[i]);
      strcpy(mazo[contador]->valor, valores[j]);
      contador++;
    }
  }

  barajarMazo(mazo, 52);

  for(int i = 0; i < 9; i++) {
    fichas[i] = (Ficha*)malloc(sizeof(Ficha));
    fichas[i]->valor = valoresFichas[i];
  }

  int totalJugador = 0;
  int totalCrupier = 0;
  int indice       = 0;

  //turno del jugador
  while (1) {
    Carta* cartaActual = mazo[indice];
    printf("El jugador obtuvo un %s de %s.\n", cartaActual->valor, cartaActual->palo);
    totalJugador += obtenerValorCarta(cartaActual);
    printf("Total del jugador: %d\n", totalJugador);
    if (totalJugador > 21) {
      printf("El jugador se pasó de 21. ¡Crupier gana!\n");
      break;
    }
    printf("¿Querés agarrar otra carta, realizar una apuesta o plantarte (quedarte con las cartas que tenes)? (c: carta | a: apuesta | p: plantarte): ");
    char opcion;
    scanf(" %c", &opcion);
    if (opcion == 'c') {        // repartir otra carta al jugador
      indice++;
    } else if (opcion == 'a') { // realizar apuesta
      mostrarFichasDisponibles(fichas);
      int fichaElegida;
      printf("Elige el número de la ficha para apostar: ");
      scanf("%d", &fichaElegida);
      if (fichaElegida >= 1 && fichaElegida <= 9) {
        int valorFicha = fichas[fichaElegida - 1]->valor;
        if (valorFicha > dinero) {
          printf("No tenes suficiente dinero como para realizar esa apuesta.\n");
          continue;
        }
        dinero -= valorFicha;
        printf("Has realizado una apuesta de %d.\n", valorFicha);
        indice++;
      } else {
        printf("Opcion invalida.\n");
        continue;
      }
    } else if (opcion = 'p') { // plantarse
      break;
    } else {
      printf("Opcion invalida.\n");
      continue;
    }
  }

  // turno del crupier
  if (totalJugador <= 21) {
    printf("\nTurno del crupier:\n");

    while (totalCrupier < 17) {
      Carta* cartaActual = mazo[indice];
      printf("El crupier obtuvo un %s de %s\n", cartaActual->valor, cartaActual->palo);
      totalCrupier += obtenerValorCarta(cartaActual);
      printf("Total del crupier: %d\n", totalCrupier);
      indice ++;
    }

    if (totalCrupier > 21) {
      printf("El crupier se paso de 21. ¡Jugador gana!\n");
      dinero += valorFicha * 2;
    } else if (totalCrupier > totalJugador) {
      printf("Crupier gana.\n");
    } else if (totalCrupier < totalJugador) {
      printf("Jugador gana.\n");
    } else {
      printf("Empate.\n");
      dinero += valorFicha;
    }
  }

  guardarDinero(dinero);

  // liberar memoria
  for (int i = 0; i < 52; ++i) {
    free(mazo[i]);
  }

  for (int i = 0; i < 9; ++i) {
    free(fichas[i]);
  }

  return 0;
}
