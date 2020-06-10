#include <stdio.h>

int function1(void) {
  static int i, state = 0;
  switch (state) {
    case 0: /* start of function */
      for (i = 0; i < 10; i++) {
        state = 1; /* so we will come back to "case 1" */
        return i;
        case 1:; /* resume control straight after the return */
      }
  }
}

int function2(void) {
  static int i, state = 0;
  switch (state) {
    case 0: /* start of function */
      for (i = 0; i < 10; i++) {
        state = __LINE__ + 2; /* so we will come back to "case 1" */
        return i;
        case __LINE__:; /* resume control straight after the return */
      }
  }
}

#define Begin()         \
  static int state = 0; \
  switch (state) {      \
    case 0:

#define Yield(x)      \
  do {                \
    state = __LINE__; \
    return x;         \
    case __LINE__:;   \
  } while (0)

#define End() }

int function3(void) {
  static int i;
  Begin();
  for (i = 0; i < 10; i++) Yield(i);
  End();
}

int main() {
  for (int i = 0; i < 10; i++) {
    printf("%d\n", function2());
  }
  return 0;
}
