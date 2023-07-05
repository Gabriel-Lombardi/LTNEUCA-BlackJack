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
void mensajeError();
void mostrarMano();
void mostrarMenu();
void barajarMazo();
int  mostrarDineroGuardado();
int  obtenerValorCarta();
int  cargarDinero();

// Funcion que pone en pantalla completa el juego
void AltEnter()
{
    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}

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

void reglas() {
  printf("=== REGLAS ===\n");
  printf("Esta version de BlackJack es distinta a las ya existentes, en este juego, la idea es no superar los 21, si llegas a 21, ganaste!\n");
  printf("El juego le dará una carta para empezar, debe tener en cuenta el número de esta\n");
  printf("\n");
  printf("=== VALOR DE LAS CARTAS ===\n");
  printf("El valor de las cartas en el Blackjack es muy importante ya que debemos de saber en todo momento la suma de nuestra mano para saber qué decisión tomar.\n");
  printf("Si no sabemos cuánto vale nuestra mano, nunca podremos aplicar una estrategia que nos permita ganar.\n");
  printf("Los valores que toman las cartas son los siguientes:\n  %cDe la carta dos (2) hasta la carta diez (10), el valor de la carta es su propio número.\n", 175);
  printf("  %cLas figuras valen diez (10).\n", 175);
  printf("  %cLos Ases pueden valer uno (1) u once (11), eso depende de usted, usted elige cual le conviene.\n", 175);
  printf("=== TURNO DEL CRUPIER ===\n");
  printf("En esta version del juego, el crupier juega en base a tu puntuacion, y no al reves como lo suele ser.\n");
  printf("Esto supone una gran desventaja, ya que la banca siempre tiene las de ganar y mas en este caso.\n");
  printf("\n\nSi desea continuar, toque cualquier tecla");
  getch();
  printf("\n\n== Buena suerte! ==\n");
  sleep(5);
  system("cls");
}

// Menu interactivo, casos en la funcion main
void mostrarMenu() {
  printf("\n=== La Timba NO Es Una Cosa Alegre ===\n");
  printf("1. Jugar partida\n");
  printf("2. Ver dinero guardado.\n");
  printf("3. Borrar dinero guardado\n");
  printf("4. Salir\n");
  printf("Ingrese su opcion: ");
}

void opcionInvalida() {
  for (int i = 0; i < 3; i++) {
    printf("\nOpcion invalida! Ingrese un numero...\n");
    sleep(1);
    system("cls");
    sleep(1);
  }
}


// Funcion para asignar el valor de las cartas para la suma de puntos
int obtenerValorCarta(Carta* carta, int totalJugador) {
  int opcion;
  if (carta->valor == 1) {
    valorAs:
    printf("Le ha tocado un As, prefiere que su valor sea 1 u 11?\n");
    if (scanf(" %d", &opcion) == 1) {
      if (opcion == 1) {
        printf("Su eleccion fue 1, este As vale 1 ahora.\n");
        return 1;
      } else if (opcion == 11) {
        printf("Su eleccion fue 11, este As vale 11 ahora.\n");
        return 11;
      }
    } else {
      opcionInvalida();
      goto valorAs;
    }
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
      printf("\nNo tenes nada! Toma $1000 ;)\n");
      return 1000;
    }
    printf("\nBilletera virtual guardada exitosamente!\n");
    return dinero;
  } else {
    printf("\nNo se pudo cargar el dinero dentro del archivo. Su dinero es $1000\n");
    return 1000; // Valor predeterminado
  }
}

void verDinero() {
  FILE* fp = fopen("dinero.txt", "r"); // Abrimos el archivo solo para leerlo (r de read)
  if (fp != NULL) {
    int dinero;
    fscanf(fp, "%d", &dinero);
    fclose(fp);
    printf("\nDinero guardado: $%d\n", dinero);
  } else {
    printf("\nNo hay dinero dentro del archivo.\n");
  }
}

void borrarDinero() {
  int dinero = 0;
  FILE *fp = fopen("dinero.txt", "w");
  fprintf(fp, "%d", dinero);
  fclose(fp);
  printf("\nDinero quemado con exito.");
  printf("\nVolviendo al menu...\n");
  sleep(2);
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
  AltEnter();
  imprimirLTNEUCA();
  imprimirBLACKJACK();
  imprimirLTNEUCA();
  imprimirBLACKJACK();

  reglas();

  // int perfiles[PERFILES_MAXIMOS];
  // const char* dineroGuardado = "dinero.txt";

  // int cantidadPerfiles = mostrarDineroGuardado(dineroGuardado, perfiles);

  menu:
  mostrarMenu();
  int opcion, salirAlMenu;
  char eleccion;
  scanf("%d", &opcion);

  switch (opcion) {
    case 1:
      printf("\nEmpecemos!\n");
      sleep(3);
      system("cls");
      break;
    case 2:
      verDinero();
      printf("\nPresione cualquier tecla para ir al menu ");
      getch();
      system("cls");
      goto menu;
    case 3:
      quemar:
      verDinero();
      printf("\nSeguro que quiere borrar todos los registros de dinero guardados? s/n: ");
      scanf(" %c", &eleccion);
      if (eleccion == 's' || eleccion == 'S' || eleccion == 'y' || eleccion == 'Y') {
        borrarDinero();
        sleep(2);
        system("cls");
        goto menu;
      } else if (eleccion == 'n' || eleccion == 'N') {
        printf("\nVolviendo al menu...\n");
        sleep(2);
        system("cls");
        goto menu;
      } else {
        printf("\nOpcion invalida, es si (s), o no (n)\n");
        goto quemar;
        break;
      }
      // printf("Cuentas con dinero guardado:\n");

      // if (cantidadPerfiles == -1) return 1;
      
      // for (int i = 0; i < cantidadPerfiles; i++) printf("%d. %d ", i+1, perfiles[i]);
      // printf("\n");
      // scanf(" %d", &partida);
      // break;
    case 4:
      // Salir del programa
      printf("\nSaliendo del programa...\n");
      exit(0);
    default:
      printf("\nOpcion invalida. Intente nuevamente.\n");
      break;
  }

  reinicio:
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

  for(int i = 0; i < 7; i++) {
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
    printf("\nTenes $%d\n", dinero);
    mostrarFichasDisponibles(fichas);
    int fichaElegida;
    printf("\nElige el numero de la ficha para apostar: ");
    scanf("%d", &fichaElegida);
    if (fichaElegida >= 1 && fichaElegida <= 9) {
      valorFicha = fichas[fichaElegida - 1]->valor;
      dineroApostado = valorFicha;
      if (valorFicha > dinero) {
        for (int i = 0; i < 3; i++) {
          printf("\nNo tenes suficiente dinero como para realizar esa apuesta!\n");
          sleep(2);
          system("cls");
          sleep(1);
        }
        goto apuesta;
      }
      dinero -= valorFicha;
      printf("\nHas realizado una apuesta de $%d.\n", valorFicha);
    } else {
      opcionInvalida();
      goto apuesta;
    }

    while (totalJugador <= 21) {
      bool esNum = false;
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
      opcionC:
      printf("\nPodes agarrar otra carta, doblar la apuesta o plantarte (1: +1 carta | 2: doblar apuesta | 3: plantarte): ");
      int opcion;
      char opcionChar;
      if (scanf(" %d", &opcion) == 1) {
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
          printf("\nIngrese un numero valido, vamos de nuevo...\n");
          sleep(2);
          system("cls");
          goto opcionC;
          mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
        }
      } else {
        scanf(" %c", &opcionChar);
        if (opcionChar == 'c' || opcionChar == 'q') {        // Repartir otra carta al jugador
          mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
          Carta* cartaActual = mazo[indice];
          indice++;
          esNum = true;
        } else if (opcionChar == 'd') { // Doblar apuesta
          if (dineroApostado * 2 > dinero) {
            system("cls");
            printf("\nNo tenes suficiente dinero como para doblar la apuesta.\n");
            goto turnoJugador;
          }
          mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
          Carta* cartaActual = mazo[indice];
          indice++;
          dineroApostado *= 2;
        } else if (opcionChar == 'p') { // Plantarse
          plantar = true;
          break;
        } else {
          printf("\nIngrese un numero valido, vamos de nuevo...\n");
          sleep(2);
          system("cls");
          goto opcionC;
          mostrarMano(mazo[indice]->palo, mazo[indice]->valor);
        }
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
        totalCrupier += obtenerValorCarta(cartaActual,totalCrupier);
        printf("\nTotal del crupier: %d\n", totalCrupier);
        sleep(2);
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
    if(dinero == 0){
      for (int i = 0; i < 3; i++) {
        printf("\nTe has quedado sin dinero. Fin del juego.\n");
        sleep(2);
        system("cls");
        sleep(1);
      }
      goto menuFin;
      }
    menuFin:  
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
        goto reinicio;
      case 2:
        goto menu;
      case 3:
        printf("\nHasta luego!\n");
        sleep(3);
        exit(0);
    }
  }
}
