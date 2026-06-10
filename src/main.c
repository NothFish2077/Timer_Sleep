#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

/*
 * Logo exibida na inicialização do programa.
 */
static const char *ART[] = {
  " ",
  "███████╗██╗     ███████╗███████╗██████╗ ██████╗",
  "██╔════╝██║     ██╔════╝██╔════╝██╔══██╗██╔══██╗",
  "███████╗██║     █████╗  █████╗  ██████╔╝██████╔╝",
  "╚════██║██║     ██╔══╝  ██╔══╝  ██╔═══╝ ██╔══██╗",
  "███████║███████╗███████╗███████╗██║     ██║  ██║",
  "╚══════╝╚══════╝╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝",
  " "
};

static const int ART_WIDTH  = 50;
static const int ART_HEIGHT = 8;

/*
 * Suspende a execução por uma quantidade de milissegundos.
 */
static void sleep_ms(long ms) {
  struct timespec ts = {
    .tv_sec  = ms / 1000,
    .tv_nsec = (ms % 1000) * 1000000L
  };

  nanosleep(&ts, NULL);
}

/*
 * Aplica um efeito visual de glitch na logo.
 */
static void aplicar_glitch(int start_row, int start_col) {
  for (int frame = 0; frame < 12; frame++) {
    printf("\033[2J");

    int offset =
      (rand() % 5 == 0)
        ? (rand() % 7 - 3)
        : 0;

    for (int i = 0; i < ART_HEIGHT; i++) {
      char linha[256];

      strcpy(linha, ART[i]);

      /*
       * Corrompe alguns caracteres aleatoriamente para
       * criar o efeito de glitch.
       */
      if (rand() % 10 < 3 && strlen(linha) > 1) {
        int len = (int)strlen(linha);

        for (int c = 0; c < len / 4; c++) {
          int pos = rand() % len;

          if (linha[pos] != ' ' &&
              (unsigned char)linha[pos] > 127) {
            linha[pos] = "▒░█#@?"[rand() % 6];
          }
        }
      }

      int coluna = start_col + offset;

      if (rand() % 20 == 0) {
        coluna += (rand() % 10 - 5);
      }

      printf(
        "\033[%d;%dH%s",
        start_row + i + 1,
        coluna,
        linha
      );
    }

    fflush(stdout);

    sleep_ms(20 + rand() % 60);
  }
}

/*
 * Centraliza e exibe a arte na tela.
 */
static void print_centered_art(void) {
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int term_width  = w.ws_col;
  int term_height = w.ws_row;

  int start_row = (term_height - ART_HEIGHT) / 2;
  int start_col = (term_width  - ART_WIDTH)  / 2;

  struct timespec delay = {
    .tv_sec  = 0,
    .tv_nsec = 150000000
  };

  aplicar_glitch(start_row, start_col);

  printf("\033[2J");

  for (int i = 0; i < ART_HEIGHT; i++) {
    printf(
      "\033[%d;%dH%s",
      start_row + i + 1,
      start_col,
      ART[i]
    );

    fflush(stdout);
    nanosleep(&delay, NULL);
  }
}

/*
 * Exibe um contador regressivo até a suspensão.
 */
static void iniciar_contagem(int segundos) {
  puts("\nSuspendendo o computador em:");

  while (segundos > 0) {
    printf(
      "\r%02d:%02d",
      segundos / 60,
      segundos % 60
    );

    fflush(stdout);

    sleep(1);
    segundos--;
  }

  putchar('\n');
}

/*
 * Ponto de entrada do programa.
 */
int main(void) {
  /* Inicializa o gerador de números aleatórios. */
  srand((unsigned int)time(NULL));

  print_centered_art();

  sleep(2);
  system("clear");

  int segundos;

  printf(
    "\n\nEm quanto tempo o computador vai suspender? "
    "(segundos): "
  );

  if (scanf("%d", &segundos) != 1 || segundos < 0) {
    fprintf(stderr, "Valor inválido.\n");
    return EXIT_FAILURE;
  }

  iniciar_contagem(segundos);

  system("systemctl suspend");

  return EXIT_SUCCESS;
}
