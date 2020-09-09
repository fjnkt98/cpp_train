#include <iostream>
#include <cstdlib>

namespace unistd {
  extern "C" {
    #include <unistd.h>
  }
} // namespace unistd

namespace sys {
  extern "C" {
    #include <sys/wait.h>
  }
} // namespace sys

int main() {
  pid_t pid = 0;


  pid = unistd::fork();

  if (pid < 0) {
    std::cerr << "Error: failed to fork subprocess." << std::endl;
    std::exit(-1);
  } else if (pid == 0) {
    unistd::execlp("echo", "echo", "abc", "def", NULL);
    std::exit(-1);
  }

  int status = 0;
  pid_t result = sys::waitpid(pid, &status, 0);

  if (result < 0) {
    std::cerr << "Error: failed to wait." << std::endl;
    std::exit(-1);
  }

  if (WIFEXITED(status)) {  // 子プロセスが正常終了の場合
    std::cout << "Child process exited with code:" << WEXITSTATUS(status) << std::endl;
  } else {  // 子プロセスが異常終了した場合
    std::cout << "Child status is " << status << std::endl;
  }

  return 0;
}