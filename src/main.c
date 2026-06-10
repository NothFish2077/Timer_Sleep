#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>

const char* ART[] = { 
" ",
"███████╗██╗     ███████╗███████╗██████╗ ██████╗" ,
"██╔════╝██║     ██╔════╝██╔════╝██╔══██╗██╔══██╗",
"███████╗██║     █████╗  █████╗  ██████╔╝██████╔╝",
"╚════██║██║     ██╔══╝  ██╔══╝  ██╔═══╝ ██╔══██╗",
"███████║███████╗███████╗███████╗██║     ██║  ██║",
"╚══════╝╚══════╝╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝",
" "
};

void print_centered_art(void) {
  struct timespec ts = {
    .tv_sec = 0,
    .tv_nsec = 150000000
  };

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int term_width = w.ws_col;
  int term_heigth = w.ws_row;

  int art_width = 50;
  int art_height = 8;

  int start_row = (term_heigth - art_height) / 2;
  int start_col = (term_width - art_width) / 2;

  printf("\033[2J");

  for (int i = 0; i < art_height; i++) {
    printf("\033[%d;%dH%s",
        start_row + i + 1,
        start_col,
        ART[i]);

    fflush(stdout);
    nanosleep(&ts, NULL);
  }


}

int main() {
  // system("clear");

  print_centered_art();
  sleep(2);

  system("clear");

  int segundos;

  printf("\n\nEm quanto tempo o computador vai suspender? (segundos): ");
  scanf("%d", &segundos);

  puts("\nSuspendendo o computador em");

  while (segundos > 0) {
    printf("\r%02d:%02d", segundos / 60, segundos % 60);
    fflush(stdout);

    sleep(1);
    
    segundos--;
  }

  printf("\n");

  system("systemctl suspend");

  return 0;
}
