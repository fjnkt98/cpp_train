#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main() {
  pid_t pid = 0;

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(-1);
  } else if (pid == 0) {
    // 子プロセスで別プログラムを実行
    execlp("echo", "echo", "abc", "def", NULL);
    perror("echo");
    exit(-1);
  }

  // ここからは親プロセス
  int status = 0;
  pid_t result = waitpid(pid, &status, 0); // 子プロセスの終了待ち

  if (result < 0) {
    perror("waitpid");
    exit(-1);
  }

  if (WIFEXITED(status)) {  // 子プロセスが正常終了の場合
    std::cout << "Child process exited with code:" << WEXITSTATUS(status) << std::endl;
  } else {  // 子プロセスが異常終了した場合
    std::cout << "Child status is " << status << std::endl;
  }

  return 0;
}