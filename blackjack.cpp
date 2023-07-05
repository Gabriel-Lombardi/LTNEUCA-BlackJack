#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

// #define PERFILES_MAXIMOS 10

struct Carta {        // Estructura de datos de la carta que se muestra, su palo (naipe) y valor
  char* palo;
  int valor;
};

struct Ficha {        // Estructura de datos de las fichas para "apuestas"
  int valor;
};

// Prototipos de funciones
void mostrarFichasDisponibles();
void imprimirBLACKJACK();
void imprimirLTNEUCA();
void guardarDinero();
void mostrarMano();
void mostrarMenu();
void barajarMazo();
int  mostrarDineroGuardado();
int  obtenerValorCarta();
int  cargarDinero();

// Funcion que imprime "LTNEUCA" en la pantalla con caracteres ASCII
void imprimirLTNEUCA() {
  system("cls");
  printf("%c   %c%c%c%c%c %c%c   %c  %c%c%c%c  %c   %c   %c%c%c  %c%c%c%c\n", 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
  printf("%c     %c   %c %c  %c  %c     %c   %c  %c     %c  %c\n", 219,219,219,219,219,219,219,219,219,219,219);
  printf("%c     %c   %c  %c %c  %c%c%c   %c   %c  %c     %c%c%c%c\n", 219,219,219,219,219,219,223,223,219,219,219,219,223,223,219);
  printf("%c%c%c%c  %c   %c   %c%c  %c%c%c%c  %c%c%c%c%c  %c%c%c%c  %c  %c\n", 219,220,220,220,219,219,223,219,219,220,220,220,223,220,220,220,223,223,220,220,220,219,219);
  printf("\n\n");
  Sleep(1000);
}

// Funcion que imprime "BLACKJACK" en la pantalla con caracteres ASCII
void imprimirBLACKJACK() {
  system("cls");
  printf("%c%c%c  %c    %c%c   %c%c%c %c  %c    %c  %c%c   %c%c%c %c  %c\n", 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
  printf("%c  %c %c   %c  %c %c    %c %c%c    %c %c  %c %c    %c %c%c\n", 219,219,219,219,219,219,219,220,223,219,219,219,219,219,220,223);
  printf("%c%c%c%c %c   %c%c%c%c %c    %c%c%c     %c %c%c%c%c %c    %c%c%c\n", 219,223,223,220,219,219,220,220,219,219,219,223,220,219,219,220,220,219,219,219,223,220);
  printf("%c%c%c%c %c%c%c %c  %c %c%c%c%c %c  %c %c%c%c%c %c  %c %c%c%c%c %c  %c\n", 219,220,220,223,219,220,220,219,219,223,220,220,220,219,219,223,220,220,223,219,219,223,220,220,220,219,219);
  printf("\n\n");
  Sleep(1000);
}

// Menu interactivo, casos en la funcion main
void mostrarMenu() {
  printf("\n=== La Timba NO Es Una Cosa Alegre ===\n");
  printf("1. Jugar partida\n");
  printf("2. Borrar dinero guardado\n");
  printf("3. Salir\n");
  printf("Ingrese su opcion: ");
}


// Funcion para asignar el valor de las cartas para la suma de puntos
int obtenerValorCarta(Carta* carta, int totalJugador) {
  if (carta->valor == 1) {
    if (totalJugador + 11 > 21) return 1;
    else                        return 11;
  }
  // El As puede valer 11 o 1, dependiendo si favorece a la suma de puntos (si los puntos del jugador + 11 da mas de 21 pasa a valer 1).
  if (carta->valor == 13 || carta->valor == 12 || carta->valor == 11)
    return 10;          // La K, Q y J valen 10 en la suma de puntos.
  return carta->valor; // Devolvemos el valor de la carta
}

// Mezclar el mazo de manera aleatoria
void barajarMazo(Carta** mazo, int dimension) {
  srand(time(NULL));                        // funcion para cambiar la semilla de los numeros aleatorios y dentro la hora del momento, siempre va cambiando asi que los numeros siempre son aleatorios
  for (int i = 0; i < dimension - 1; ++i) { // ciclo for hasta que terminen las cartas (52 en este caso)
    int j = i + rand() % (dimension - i);   // asignamos a j un numero aleatorio entre 0 y 51, 1 y 50, etc
    Carta* temp = mazo[i];
    mazo[i] = mazo[j];
    mazo[j] = temp;       // hacemos un swap entre i (carta) y j (valor)
  }
}

// Funcion para mostrar las fichas (9) con valor:
// 50, 100, 500, 1000, 2000, 5000, 10000
void mostrarFichasDisponibles(Ficha** fichas) {
  printf("\nFichas disponibles:\n");
  for (int i = 0; i < 7; ++i) {
    printf("Ficha %d: $%d\n", i + 1, fichas[i]->valor);
  }
}

// Funcion para guardar el dinero apostado dentro de un archivo "dinero.txt"
void guardarDinero(int dinero) {       // Funcion para guardar el dinero
  // FILE* fp = fopen("dinero.txt", "r"); // Abrimos el archivo para escribir en él (a de append)
  // int prev_dinero;
  // fscanf(fp, "%d", &prev_dinero);      // guardamos el dinero que habia dentro del archivo para luego poder sumarlo al dinero que ingresa
  // fclose(fp);
  FILE* fp = fopen("dinero.txt", "w"); // Abrimos el archivo para escribir en él (w de write)
  // dinero += prev_dinero; // sumamos el dinero que habia en el archivo y el dinero que gano el jugador
  if (fp != NULL) {
    fprintf(fp, "%d", dinero);
    fclose(fp);
    printf("\nDinero guardado exitosamente!\n");
  } else {
    printf("\nNo se pudo guardar el dinero dentro del archivo.\n");
  }
}

// Funcion para determinar cuanto dinero se tiene, leyendo el archivo anteriormente creado
int cargarDinero() {
  FILE* fp = fopen("dinero.txt", "r"); // Abrimos el archivo solo para leerlo (r de read)
  if (fp != NULL) {
    int dinero;
    fscanf(fp, "%d", &dinero);
    fclose(fp);
    if (dinero < 50) {
      printf("No tenes nada! Toma $1000 ;)\n");
      return 1000;
    }
    printf("\nDinero cargado exitosamente!\n");
    return dinero;
  } else {
    printf("\nNo se pudo cargar el dinero dentro del archivo. Su dinero es $1000\n");
    return 1000; // Valor predeterminado
  }
}

// int mostrarDineroGuardado(const char* dineroGuardado, int* perfiles) {
//   FILE* fp = fopen("dinero.txt", "r");
//   if (fp == NULL) {
//     printf("No hay perfiles.\n");
//     return -1;
//   }

//   int elemento;
//   int contador = 0;

//   while (fscanf(fp, "%d", &elemento) == 1) {
//     if (contador >= PERFILES_MAXIMOS) {
//       printf("Demasiados perfiles, desea eliminar alguno? S/N:");
//       break;
//     }

//     perfiles[contador] = elemento;
//     contador++;
//   }

//   fclose(fp);

//   return contador;
// }

void mostrarMano(char* palo, int valor) {
  int  n_palo;           // Variable para asignar el numero del palo que coincida con el simbolo ASCII de las cartas (♥ ♦ ♣ ♠)
  char valor_palo = 'N'; // Variable con un caracter base para determinar si el valor a imprimir es A, J, Q, K o un numero del 2 al 10

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
      if (valor == 10)            printf("%c %d    %d %c\n", 179, valor, valor, 179);
      else if (valor_palo == 'N') printf("%c %d \t %d %c\n", 179, valor, valor, 179);
      else                        printf("%c %c \t %c %c\n", 179, valor_palo, valor_palo, 179);

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
  imprimirLTNEUCA();
  imprimirBLACKJACK();
  imprimirLTNEUCA();
  imprimirBLACKJACK();

  // int perfiles[PERFILES_MAXIMOS];
  // const char* dineroGuardado = "dinero.txt";

  // int cantidadPerfiles = mostrarDineroGuardado(dineroGuardado, perfiles);

  menu:
  mostrarMenu();
  int opcion, eleccion;
  scanf("%d", &opcion);

  switch (opcion) {
    case 1:
      printf("\nEmpecemos!\n");
      sleep(3);
      system("cls");
      break;
    case 2:
      printf("Seguro que quiere borrar todos los registros de dinero guardados? s/n:");
      scanf(" %d", &eleccion);
      if (eleccion == 's') {
        FILE *fp = fopen("dinero.txt", "w");
        printf("Dinero quemado con exito.");
        break;
      } else if (eleccion == 'n') {
        break;
      } else {
        printf("Opcion invalida, es si (s), o no (n)");
        break;
      }
      // printf("Cuentas con dinero guardado:\n");

      // if (cantidadPerfiles == -1) return 1;
      
      // for (int i = 0; i < cantidadPerfiles; i++) printf("%d. %d ", i+1, perfiles[i]);
      // printf("\n");
      // scanf(" %d", &partida);
      // break;
    case 3:
      // Salir del programa
      printf("Saliendo del programa...\n");
      exit(0);
    default:
      printf("Opcion invalida. Intente nuevamente.\n");
      break;
  }
  Carta* mazo[52];
  const char *palos[] = {"Corazones", "Diamantes", "Treboles", "Picas"};
  // char *valores[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jota", "Reina", "Rey"};
  int valores[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  Ficha* fichas[7];
  int valoresFichas[] = {50, 100, 500, 1000, 2000, 5000, 10000};
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
  bool plantar       = false;

  while (1){
  // Turno del jugador
  // Realizar apuesta
    apuesta:
    printf("\nTienes $%d\n", dinero);
    mostrarFichasDisponibles(fichas);
    int fichaElegida;
    printf("\nElige el numero de la ficha para apostar: ");
    scanf("%d", &fichaElegida);
    if (fichaElegida >= 1 && fichaElegida <= 9) {
      valorFicha = fichas[fichaElegida - 1]->valor;
      dineroApostado = valorFicha;
      if (valorFicha > dinero) {
        system("cls");
        printf("\nNo tenes suficiente dinero como para realizar esa apuesta.\n");
        goto apuesta;
      }
      dinero -= valorFicha;
      printf("\nHas realizado una apuesta de $%d.\n", valorFicha);
    } else {
      printf("\nOpcion invalida.\n");
      return 0;
    }

    while (totalJugador <= 21) {
      Carta* cartaActual = mazo[indice];
      totalJugador += obtenerValorCarta(cartaActual,totalJugador);
      turnoJugador:
      mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
      if (mazo[indice]->valor == 1) {
        printf("\nEl jugador obtuvo As de %s.\n", cartaActual->palo);
      } else if (mazo[indice]->valor == 11) {
        printf("\nEl jugador obtuvo J de %s.\n", cartaActual->palo);
      } else if (mazo[indice]->valor == 12) {
        printf("\nEl jugador obtuvo Q de %s.\n", cartaActual->palo);
      } else if (mazo[indice]->valor == 13) {
        printf("\nEl jugador obtuvo K de %s.\n", cartaActual->palo);
      } else {
        printf("\nEl jugador obtuvo un %d de %s.\n", mazo[indice]->valor, cartaActual->palo);
      }
      printf("\nTotal del jugador: %d\n", totalJugador);
      if (totalJugador == 21) {
        int ganancias = valorFicha * 2;
        printf("\nBlackjack! Vos ganas. Has gando $%d", ganancias);
        dinero += valorFicha * 2; // Dar al jugador lo acordado de la apuesta
        goto fin;
      } else if (totalJugador > 21) {
        int perdidas = dineroApostado;
        printf("\nTe has pasado de 21. Crupier gana! Has perdido $%d\n", perdidas);
        goto fin;
      }
      printf("\nPodes agarrar otra carta, doblar la apuesta o plantarte (1: +1 carta | 2: doblar apuesta | 3: plantarte): ");
      int opcion;
      scanf(" %d", &opcion);
      if (opcion == 1) {        // Repartir otra carta al jugador
        mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
        Carta* cartaActual = mazo[indice];
        indice++;
      } else if (opcion == 2) { // Doblar apuesta
        if (dineroApostado * 2 > dinero) {
          system("cls");
          printf("\nNo tenes suficiente dinero como para doblar la apuesta.\n");
          goto turnoJugador;
        }
        mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
        Carta* cartaActual = mazo[indice];
        indice++;
        dineroApostado *= 2;
      } else if (opcion == 3) { // Plantarse
        plantar = true;
        break;
      } else {
        printf("\nOpcion invalida.\n");
        continue;
      }
    }
    // Turno del crupier
    if (totalJugador <= 21 || plantar == true) {
      printf("\nTurno del crupier:\n");
      sleep(2);

      indice++;
      while (totalCrupier < 17) {
        Carta* cartaActual = mazo[indice];
        mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
        if (mazo[indice]->valor == 1) {
          printf("\nEl crupier obtuvo As de %s.\n", cartaActual->palo);
        } else if (mazo[indice]->valor == 11) {
          printf("\nEl crupier obtuvo J de %s.\n", cartaActual->palo);
        } else if (mazo[indice]->valor == 12) {
          printf("\nEl crupier obtuvo Q de %s.\n", cartaActual->palo);
        } else if (mazo[indice]->valor == 13) {
          printf("\nEl crupier obtuvo K de %s.\n", cartaActual->palo);
        } else {
          printf("\nEl crupier obtuvo un %d de %s.\n", mazo[indice]->valor, cartaActual->palo);
        }
        sleep(2);
        totalCrupier += obtenerValorCarta(cartaActual,totalCrupier);
        printf("\nTotal del crupier: %d\n", totalCrupier);
        if (totalCrupier > totalJugador) {
          int perdidas = dineroApostado;
          printf("\nCrupier gana. Has perdido $%d\n", perdidas);
          goto fin;
        }
        indice ++;
      }

      if (totalCrupier > 21) {
        int ganancias = dineroApostado;
        printf("\nEl crupier se paso de 21. Jugador gana! Has ganado $%d\n", ganancias);
        dinero += dineroApostado * 2; // Dar al jugador lo acordado de la apuesta
      } else if (totalCrupier > totalJugador) {
        int perdidas = dineroApostado;
        printf("\nCrupier gana. Has perdido $%d\n", perdidas);
      } else if (totalCrupier < totalJugador) {
        int ganancias = dineroApostado * 2;
        dinero += ganancias; // Dar al jugador lo acordado de la apuesta
        printf("\nJugador gana. Has ganado $%d\n", ganancias);
      } else {
        dinero += dineroApostado; // Devolver dinero apostado al jugador
        printf("\nEmpate. Se le devuelve el dinero apostado ($%d).\n", dineroApostado);
      }
    }

    fin:
    sleep(5);
    guardarDinero(dinero);
    if(dinero == 0){printf("\nTe has quedado sin dinero. Fin del juego.\n"); return 0;}
    sleep(6);
    int fin;
    system("cls");
    printf("\nQue desea hacer?\n");
    printf("1. Seguir jugando\n");
    printf("2. Ir al menu\n");
    printf("3. Salir del juego\n");
    printf("Su upcion: ");
    scanf("%d", &fin);
    switch (fin) {
      case 1:
        totalJugador = 0;
        totalCrupier = 0;
        continue;
      case 2:
        goto menu;
      case 3:
        printf("\nHasta luego!\n");
        exit(0);
    }
  }
}
