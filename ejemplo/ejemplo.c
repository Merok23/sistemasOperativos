#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
  srandom(time(NULL));
  printf("%li", random());
  return 0;
}




