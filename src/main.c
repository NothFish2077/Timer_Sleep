#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const char* ART[] = { 
"███████╗██╗     ███████╗███████╗██████╗ ██████╗\n" ,
"██╔════╝██║     ██╔════╝██╔════╝██╔══██╗██╔══██╗\n",
"███████╗██║     █████╗  █████╗  ██████╔╝██████╔╝\n",
"╚════██║██║     ██╔══╝  ██╔══╝  ██╔═══╝ ██╔══██╗\n",
"███████║███████╗███████╗███████╗██║     ██║  ██║\n",
"╚══════╝╚══════╝╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝\n"
};
                                                

int main() {
  system("clear");

  for (int i = 0; i < 6; i++) {
    printf("%s",ART[i]);
  }

  int segundos;

  printf("Em quanto tempo o computador vai suspender? (segundos): ");
  scanf("%d", &segundos);

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
