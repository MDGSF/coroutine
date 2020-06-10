#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

void function(void * arg) {
  for (int i = 0; i < 10; i++) {
    printf("%d ", i);
  }
  printf("\n");
}

int main() {

  ucontext_t child;
  getcontext(&child); // 获取当前上下文，并保存到 child

  char stack[128 * 1024] = {0};
  child.uc_stack.ss_sp = stack; // 指定栈空间
  child.uc_stack.ss_size = sizeof(stack); // 指定栈空间大小
  child.uc_stack.ss_flags = 0;

  ucontext_t main;
  child.uc_link = &main; // 设置后继上下文

  // 修改 child 上下文指向 function 函数
  makecontext(&child, (void (*)(void))function, 0);

  // 切换到 child 上下文，并保存当前上下文到 main 中
  swapcontext(&main, &child);

  // 如果 child 设置了后继上下文，function 函数指向完之后，会回到这里。
  printf("main end\n");

  return 0;
}
