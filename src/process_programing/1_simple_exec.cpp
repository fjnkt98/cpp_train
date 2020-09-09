#include <iostream>

#include <unistd.h>

int main() {
  execl("/bin/echo", "/bin/echo", "abc", "def", NULL);

  perror("/bin/echo");
  return -1;
}