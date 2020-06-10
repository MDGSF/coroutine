#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main() {
  ucontext_t context;

  getcontext(&context);
  printf("Hello World\n");
  sleep(1);
  setcontext(&context);

  return 0;
}
