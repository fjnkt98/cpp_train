#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = 0;

  pid = fork();

  if (pid < 0) {
    const int err = errno;
    std::cout << "failed to fork process." 
              << std::strerror(err)
              << std::endl;
    std::exit(-1);
  } else if (pid == 0) {
    //execlp("/home/wisteria/cpp_train/src/process_programing/dummy.out",
    //"/home/wisteria/cpp_train/src/process_programing/dummy.out",
    //NULL);
    execlp("./dummy.out", "./dummy.out", NULL);
    std::exit(-1);
  }

  int status = 0;
  pid_t result = waitpid(pid, &status, 0);

  if (result < 0) {
    std::perror("waitpid");
    std::exit(-1);
  }

  if (WIFEXITED(status)) {  // 子プロセスが正常終了の場合
    std::cout << "Child process exited with code:" << WEXITSTATUS(status) << std::endl;
  } else {  // 子プロセスが異常終了した場合
    std::cout << "Child status is " << status << std::endl;
  }

  return 0;
}