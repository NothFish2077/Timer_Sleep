#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int segundos = 3600;

  puts("Suspendendo o computador em");

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
