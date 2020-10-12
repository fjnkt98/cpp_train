#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

#include <thread>
#include <chrono>

extern "C" {
  #include <unistd.h>
  #include <sys/wait.h>
  #include <signal.h>
}

class DummyLauncher {
  public:
    DummyLauncher()
    : is_launched_(false)
    {

    }

    ~DummyLauncher() {
      if (pid_ > 0 && processIsAlive() == true) {
        try {
          terminate();
        }
        catch (std::runtime_error &e){
          std::cerr << "Runtime Error: " << e.what() << std::endl;
          std::exit(EXIT_FAILURE);
        }
      }
    }

    void launch() {
      if (is_launched_ == false) {
        pid_ = fork();

        if (pid_ < 0) {
          throw(std::runtime_error("Failed to fork process."));
        }

        if (pid_ == 0) {
          execlp("./dummy_loop.out", "./dummy_loop.out", NULL);
          throw(std::runtime_error("Failed to start dummy_loop."));
        }

        is_launched_ = true;
      }
    }

    void terminate() {
      if (is_launched_ == true && pid_ != -1) {
        kill(pid_, SIGINT);

        int status = 0;
        pid_t result = waitpid(pid_, &status, 0);

        if (result < 0) {
          throw(std::runtime_error("Failed to terminate subprocess."));
        }

        if (WIFEXITED(status)) {
          std::cout << "dummy_loop is exited with code: " << WEXITSTATUS(status) << std::endl;
        } else {
          std::cout << "dummy_loop is terminated with status: " << static_cast<int>(status) << std::endl;
        }
      
        is_launched_ = false;
      }
    }

  private:
    pid_t pid_;
    bool is_launched_;

    bool processIsAlive() {
      // Check if the process exists by sending signal number 0
      int result = kill(pid_, 0);

      // if 0 is returned, the process exists
      if (result == 0) {
        return true;
      }

      // The process exists but is not authorized to send signals
      if (EPERM == errno) {
        return true;
      }

      // The process doesn't exist
      return false;
    }
};

int main() {
  DummyLauncher launcher;

  try {
    launcher.launch();
  }
  catch(std::runtime_error &e) {
    std::cerr << "Runtime Error: " << e.what() << std::endl;
    std::exit(-1);
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));

  try {
    launcher.terminate();
  }
  catch(std::runtime_error &e) {
    std::cerr << "Runtime Error: " << e.what() << std::endl;
    std::exit(-1);
  }

  return 0;
}