#include <unistd.h>
#include <sys/wait.h>

#include <cstdio>
#include <iostream>

int main() {
  int status = 0;
  int code = 0;
  pid_t pid = 0;
  pid_t result = 0;

  pid = fork();

  if (pid == -1) {
    std::fprintf(stderr, "Error: failed to fork process!\n\n");
  } else if (pid == 0) {
    std::printf("Child Process\n");
  } else {
    std::printf("Parent Process\n");

    result = wait(&status);

    if (result < 0) {
      std::fprintf(stderr, "Error: failed to wait!\n\n");
      exit(-1);
    }

    if (WIFEXITED(status)) {
      std::printf("Terminated child process.");
      code = WEXITSTATUS(status);
      std::printf("code: %d\n", code);
    } else {
      std::printf("Failed to wait.");
      std::printf("Exit with code: %d\n", status);
    }

    if (WIFSIGNALED(status)) {
      std::printf("Exit with signal number: %d\n", WTERMSIG(status));
    }

    std::printf("Parent process exited.\n");
  }

  return 0;
}