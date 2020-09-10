#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <thread>
#include <chrono>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
  pid_t pid = 0;

  // 子プロセスを作成する
  pid = fork();

  // 正常に作成できたかどうかチェック
  if (pid < 0) {
    std::perror("fork failed");
    std::exit(-1);
  } else if (pid == 0) {
    // 子プロセスでダミープログラムを実行
    execlp("./dummy_loop.out", "./dummy_loop.out", NULL);
    std::exit(-1);
  }

  // 3秒待つ
  std::this_thread::sleep_for(std::chrono::seconds(3));

  // 子プロセスを殺す
  if (pid > 0) {
    std::cout << "Killing child process..." << std::endl;
    kill(pid, SIGINT);
  }

  int status = 0;
  pid_t result = waitpid(pid, &status, 0);

  std::cout << "Child process was killed." << std::endl;

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