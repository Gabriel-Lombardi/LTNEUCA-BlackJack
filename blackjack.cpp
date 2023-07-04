#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

struct Carta {        // estructura de datos de la carta que se muestra, su palo (naipe) y valor
  char* palo;
  int valor;
};

struct Ficha {        // estructura de datos de las fichas para "apuestas"
  int valor;
};

void menu() {
  printf("%c%c%c  %c    %c%c   %c%c%c %c  %c    %c  %c%c   %c%c%c %c  %c\n", 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
  printf("%c  %c %c   %c  %c %c    %c %c%c    %c %c  %c %c    %c %c%c\n", 219,219,219,219,219,219,219,220,223,219,219,219,219,219,220,223);
  printf("%c%c%c%c %c   %c%c%c%c %c    %c%c%c     %c %c%c%c%c %c    %c%c%c\n", 219,223,223,220,219,219,220,220,219,219,219,223,220,219,219,220,220,219,219,219,223,220);
  printf("%c%c%c%c %c%c%c %c  %c %c%c%c%c %c  %c %c%c%c%c %c  %c %c%c%c%c %c  %c\n", 219,220,220,223,219,220,220,219,219,223,220,220,220,219,219,223,220,220,223,219,219,223,220,220,220,219,219);
  printf("\n\n");
}

// funcion para asignar el valor de las cartas para la suma de puntos

int obtenerValorCarta(Carta* carta) {
  if (carta->valor == 1)
    return 11; // el As puede valer 11 o 1, dependiendo si favorece a la suma de puntos.
  if (carta->valor == 13 || carta->valor == 12 || carta->valor == 11)
    return 10; // la K, Q y J valen 10 en la suma de puntos.
  return carta->valor; // devolvemos el valor de la carta
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

// funcion para dibujar ficha de apuesta tipo poker
void dibujarFicha(int valor) {
  system("cls");
  for(int i = 0; i < 9; i++) {
    // Imprimir la ficha en la consola
    printf("\033[0;31m");
    printf(" ________ \n");
    printf("%c        %c\n", 47,92);
    printf("|    %d   |\n", valor);
    printf("|         |\n");
    printf("%c_______%c\n", 92,47);
    printf("\033[0m");
  }
}

// funcion para mostrar las fichas (9) con valor:
// 1, 5, 25, 50, 100, 500, 1000, 2000, 5000, 10000
void mostrarFichasDisponibles(Ficha** fichas) {
  printf("\nFichas disponibles:\n");
  for (int i = 0; i < 9; ++i) {
    printf("Ficha %d: $%d\n", i + 1, fichas[i]->valor);
    dibujarFicha(fichas[i]->valor);
  }
}

// funcion para guardar el dinero apostado dentro de un archivo "dinero.txt"
void guardarDinero(int dinero) {       // funcion para guardar el dinero
  FILE* fp = fopen("dinero.txt", "w"); // abrimos el archivo para escribir en él (w de write)
  if (fp != NULL) {
    fprintf(fp, "%d", dinero);
    fclose(fp);
    printf("Dinero guardado exitosamente!\n");
  } else {
    printf("No se pudo guardar el dinero dentro del archivo.\n");
  }
}

// funcion para determinar cuanto dinero se tiene, leyendo el archivo anteriormente creado
int cargarDinero() {
  FILE* fp = fopen("dinero.txt", "r"); // abrimos el archivo solo para leerlo (r de read)
  if (fp != NULL) {
    int dinero;
    fscanf(fp, "%d", &dinero);
    fclose(fp);
    printf("Dinero cargado exitosamente!\n");
    return dinero;
  } else {
    printf("No se pudo cargar el dinero dentro del archivo. Su dinero es $1000\n");
    return 1000; // valor predeterminado
  }
}

void mostrarMano(char* palo, int valor) {
  int  n_palo;           // variable para asignar el numero del palo que coincida con el simbolo ASCII de las cartas (♥ ♦ ♣ ♠)
  char valor_palo = 'N'; // variable con un caracter base para determinar si el valor a imprimir es A, J, Q, K o un numero del 2 al 10

  if (strcmp(palo,"Corazones") == 0) n_palo = 3;
  if (strcmp(palo,"Diamantes") == 0) n_palo = 4;
  if (strcmp(palo,"Treboles")  == 0) n_palo = 5;
  if (strcmp(palo,"Picas")     == 0) n_palo = 6;

  if (valor == 1)  valor_palo = 'A';
  if (valor == 11) valor_palo = 'J';
  if (valor == 12) valor_palo = 'Q';
  if (valor == 13) valor_palo = 'K';

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
  menu();
  Carta* mazo[52];
  const char *palos[] = {"Corazones", "Diamantes", "Treboles", "Picas"};
  // char *valores[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jota", "Reina", "Rey"};
  int valores[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  Ficha* fichas[9];
  int valoresFichas[] = {1, 5, 25, 50, 100, 500, 1000, 2000, 5000, 10000};
  int dinero;

  dinero = cargarDinero();

  int contador = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 13; ++j) {
      mazo[contador] = (Carta*)malloc(sizeof(Carta)); // Asignar memoria para la estructura de la carta
      mazo[contador]->palo  = (char*)malloc(strlen(palos[i]) + 1);  // Asignar memoria para el palo
      strcpy(mazo[contador]->palo, palos[i]);
      mazo[contador]->valor = valores[j]; // Asignar valor correspondiente
      contador++;
    }
  }

  barajarMazo(mazo, 52);

  for(int i = 0; i < 9; i++) {
    fichas[i] = (Ficha*)malloc(sizeof(Ficha));
    fichas[i]->valor = valoresFichas[i];
  }

  int dineroApostado = 0;
  int totalJugador   = 0;
  int totalCrupier   = 0;
  int valorFicha     = 0;
  int indice         = 0;

  //turno del jugador
  // realizar apuesta
  mostrarFichasDisponibles(fichas);
  int fichaElegida;
  printf("\nElige el numero de la ficha para apostar: ");
  scanf("%d", &fichaElegida);
  if (fichaElegida >= 1 && fichaElegida <= 9) {
    valorFicha = fichas[fichaElegida - 1]->valor;
    dineroApostado = valorFicha;
    if (valorFicha > dinero) {
      printf("\nNo tenes suficiente dinero como para realizar esa apuesta.\n");
      return 0;
    }
    dinero -= valorFicha;
    printf("\nHas realizado una apuesta de $%d.\n", valorFicha);
  } else {
    printf("\nOpcion invalida.\n");
    return 0;
  }

  while (totalJugador <= 21) {
    Carta* cartaActual = mazo[indice];
    mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
    if (mazo[indice]->valor == 11) {
      printf("\nEl jugador obtuvo J de %s.\n", cartaActual->valor, cartaActual->palo);
    } else if (mazo[indice]->valor == 12) {
      printf("\nEl jugador obtuvo Q de %s.\n", cartaActual->valor, cartaActual->palo);
    } else if (mazo[indice]->valor == 13) {
      printf("\nEl jugador obtuvo K de %s.\n", cartaActual->valor, cartaActual->palo);
    } else {
      printf("\nEl jugador obtuvo un %d de %s.\n", cartaActual->valor, cartaActual->palo);
    }
    totalJugador += obtenerValorCarta(cartaActual);
    printf("\nTotal del jugador: %d\n", totalJugador);
    if (totalJugador == 21) {
      int ganancias = valorFicha * 2;
      printf("Blackjack! El jugador gana. Has gando $%d", ganancias);
      dinero += valorFicha * 2; // dar al jugador lo acordado de la apuesta
    } else if (totalJugador > 21) {
      int perdidas = dineroApostado;
      printf("\nEl jugador se pasó de 21. Crupier gana! Has perdido $%d\n", perdidas);
      break;
    }
    printf("\nPodes agarrar otra carta, doblar la apuesta o plantarte (q: quedarte | d: doblar apuesta | p: plantarte): ");
    char opcion;
    scanf("%c", &opcion);
    if (opcion == 'q') {        // repartir otra carta al jugador
      indice++;
    } else if (opcion == 'd') { // doblar apuesta
      dineroApostado *= 2;
    } else if (opcion = 'p') { // plantarse
      break;
    } else {
      printf("\nOpcion invalida.\n");
    }
  }
  // turno del crupier
  if (totalJugador <= 21) {
    sleep(2);
    printf("\nTurno del crupier:\n");

    while (totalCrupier < 17) {
      Carta* cartaActual = mazo[indice];
      mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
      printf("\nEl crupier obtuvo un %d de %s\n", cartaActual->valor, cartaActual->palo);
      totalCrupier += obtenerValorCarta(cartaActual);
      printf("\nTotal del crupier: %d\n", totalCrupier);
      indice ++;
    }

    if (totalCrupier > 21) {
      int ganancias = valorFicha * 2;
      printf("\nEl crupier se paso de 21. Jugador gana! Has ganado $%d\n", ganancias);
      dinero += valorFicha * 2; // dar al jugador lo acordado de la apuesta
    } else if (totalCrupier > totalJugador) {
      int perdidas = dineroApostado;
      printf("\nCrupier gana. Has perdido $%d\n", perdidas);
    } else if (totalCrupier < totalJugador) {
      int ganancias = valorFicha * 2;
      dinero += ganancias; // dar al jugador lo acordado de la apuesta
      printf("\nJugador gana. Has ganado $%d\n", ganancias);
    } else {
      dinero += dineroApostado; // devolver dinero apostado al jugador
      printf("\nEmpate. Se le devuelve el dinero apostado ($%d).\n", dineroApostado);
    }
  }

  guardarDinero(dinero);

  if(dinero == 0) printf("\nTe has quedado sin dinero. Fin del juego.\n");

  return 0;
}
