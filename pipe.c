#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  Charles Weng
  Systems - 4
  HW 13 - Check Your Pipes For Leaks
*/

int main() {
  // create the two pipes
  int fds1[2], fds2[2];
  // fds1 - parent -> child
  pipe(fds1);
  // fds2 - child -> parent
  pipe(fds2);

  // if parent else child
  if (fork() != 0){
    close(fds2[1]);
    close(fds1[0]);

    // sending number
    int pass = 5;
    printf("Parent: Sending %d to child\n", pass);
    write(fds1[1], &pass, sizeof(int));

    // recieving number
    int x;
    read(fds2[0], &x, sizeof(int));
    printf("Parent: Recieved %d from child\n", x);
  }else{
    close(fds1[1]);
    close(fds2[0]);

    // recieving number
    int x;
    read(fds1[0], &x, sizeof(int));
    printf("Child: Recieved %d from parent\n", x);

    // sending number
    x = x % 2;
    printf("Child: Modding by two and sending %d to parent\n", x);
    write(fds2[1], &x, sizeof(int));
  }
  return 0;
}
